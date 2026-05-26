import html
import logging
from datetime import date
from pathlib import Path

from sitegen.loader import DataLoader
from sitegen.logging_utils import setup_logger
from sitegen.render import TemplateRenderer, inline_html, localize


LANGUAGES = ("en", "zh-cn")

LABELS: dict[str, dict[str, str]] = {
    "en": {
        "about": "About",
        "awards": "Honors & Awards",
        "conference_publications": "Conference/Symposium Publications",
        "contact_links": "Contact and academic links",
        "details": "Details",
        "education": "Education & Work",
        "email": "Email",
        "email_note": "No response for 72h -> Failed to receive or accidentally omit your email, you can try to resend it.",
        "full_publications": "Full Publications",
        "full_publications_link": "full publication list",
        "full_publications_prefix": "See the",
        "hobbies": "Hobbies",
        "journal_publications": "Journal/Magazine Publications",
        "last_updated": "Last updated",
        "primary_navigation": "Primary navigation",
        "projects": "Selected Projects",
        "publications": "Publications",
        "selected_publications": "Selected Publications",
        "skip": "Skip to content",
        "switch_lang": "简体中文",
        "talks": "Talks",
        "teaching": "Teaching",
        "workshops": "Workshops",
    },
    "zh-cn": {
        "about": "关于",
        "awards": "荣誉和奖项",
        "conference_publications": "会议论文",
        "contact_links": "联系方式和学术链接",
        "details": "查看细节",
        "education": "教育和工作经历",
        "email": "电邮",
        "email_note": "超过 72 小时未回复 -> 我可能未收到或不慎遗漏邮件，您可尝试重发。",
        "full_publications": "全部论文发表",
        "full_publications_link": "全部论文发表",
        "full_publications_prefix": "查看我的",
        "hobbies": "兴趣爱好",
        "journal_publications": "期刊论文",
        "last_updated": "最后更新",
        "primary_navigation": "主导航",
        "projects": "工程项目",
        "publications": "论文发表",
        "selected_publications": "论文发表",
        "skip": "跳转到正文",
        "switch_lang": "English",
        "talks": "报告",
        "teaching": "助教经历",
        "workshops": "研讨会报告",
    },
}


class SiteBuilder:
    """Build localized static HTML pages from YAML data and templates."""

    def __init__(self, root: Path | None = None) -> None:
        self.__root = root or Path.cwd()
        self.__loader = DataLoader(self.__root)
        self.__renderer = TemplateRenderer()
        self.__logger = setup_logger("builder")

    def build(self) -> None:
        """Build all localized pages from templates and root-level assets."""
        logging.getLogger().setLevel(logging.INFO)
        site = self.__loader.load_site()
        about = self.__loader.load_about()
        publication_order = self.__loader.load_publication_order()
        publications = self.__ordered_publications(
            self.__loader.load_publications(),
            publication_order,
        )

        for lang in LANGUAGES:
            self.__build_language(lang, site, about, publications)
        self.__logger.info("site build completed")

    def __build_language(
        self,
        lang: str,
        site_data: dict[str, object],
        about_data: dict[str, object],
        publications: dict[str, list[dict[str, object]]],
    ) -> None:
        """Build every page for a language."""
        output_dir = self.__root if lang == "en" else self.__root / lang
        output_dir.mkdir(parents=True, exist_ok=True)
        asset_prefix = "" if lang == "en" else "../"

        context = self.__page_context(
            lang, site_data, about_data, publications, asset_prefix
        )
        pages = {
            "index.html": output_dir / "index.html",
            "about.html": output_dir / "about.html",
            "publications.html": output_dir / "publications.html",
        }
        for template_name, output_path in pages.items():
            self.__logger.info("rendering %s", output_path)
            html_text = self.__renderer.render_file(
                self.__root / "templates" / template_name,
                context
                | {"page": template_name, "urls": self.__urls(lang, template_name)},
            )
            output_path.write_text(html_text, encoding="utf-8", newline="\n")

    def __page_context(
        self,
        lang: str,
        site_data: dict[str, object],
        about_data: dict[str, object],
        publications: dict[str, list[dict[str, object]]],
        asset_prefix: str,
    ) -> dict[str, object]:
        """Create the shared page context for one language."""
        site = site_data.get("site", {})
        if not isinstance(site, dict):
            raise ValueError("site.yaml must define site as a mapping")
        return {
            "asset_prefix": asset_prefix,
            "lang": lang,
            "labels": LABELS[lang],
            "site": self.__localized_site(site, lang),
            "profile": self.__localized_profile(about_data.get("profile", {}), lang),
            "urls": self.__urls(lang, "index.html"),
            "selected_publications": [
                self.__localized_publication(publication, lang)
                for publication in publications["all"]
                if publication.get("selected")
            ],
            "talks": self.__localized_talks(
                about_data.get("talks", []), lang
            ),
            "conference_publications": [
                self.__localized_publication(publication, lang)
                for publication in publications["conference"]
            ],
            "journal_publications": [
                self.__localized_publication(publication, lang)
                for publication in publications["journal"]
            ],
            "workshop_publications": [
                self.__localized_publication(publication, lang)
                for publication in publications["workshop"]
            ],
            "awards": self.__localized_awards(
                about_data.get("awards", []), lang, False
            ),
            "education": self.__localized_timeline(
                about_data.get("education", []), lang
            ),
            "teaching": self.__localized_timeline(about_data.get("teaching", []), lang),
            "projects": self.__localized_projects(about_data.get("projects", []), lang),
            "hobbies": self.__localized_text_list(about_data.get("hobbies", []), lang),
        }

    def __ordered_publications(
        self,
        entries: dict[str, dict[str, object]],
        order: list[str],
    ) -> dict[str, list[dict[str, object]]]:
        """Apply explicit publication ordering and split by publication kind."""
        ordered: dict[str, list[dict[str, object]]] = {
            "all": [],
            "conference": [],
            "journal": [],
            "workshop": [],
        }
        referenced: set[str] = set()
        for key in order:
            if key not in entries:
                raise ValueError(f"Publication order references missing key: {key}")
            if key in referenced:
                raise ValueError(f"Publication order contains duplicate key: {key}")
            publication = entries[key]
            actual_kind = str(publication.get("kind", ""))
            if actual_kind not in ordered or actual_kind == "all":
                self.__logger.warning(
                    "publication %s has unknown kind: %s", key, actual_kind
                )
                continue
            ordered["all"].append(publication)
            ordered[actual_kind].append(publication)
            referenced.add(key)
        missing = sorted(set(entries) - referenced)
        if missing:
            self.__logger.warning(
                "publication files not referenced by data/publications.yaml: %s",
                ", ".join(missing),
            )
        return ordered

    def __localized_site(self, site: dict[object, object], lang: str) -> dict[str, str]:
        """Localize site metadata."""
        last_updated = site.get("last_updated", "")
        if isinstance(last_updated, date):
            last_updated_text = last_updated.isoformat()
        else:
            last_updated_text = str(last_updated)
        return {
            "description": localize(site.get("description", ""), lang),
            "last_updated": last_updated_text,
            "title": localize(site.get("title", ""), lang),
        }

    def __localized_profile(
        self, profile_value: object, lang: str
    ) -> dict[str, object]:
        """Localize profile fields."""
        if not isinstance(profile_value, dict):
            raise ValueError("profile must be a mapping")
        links = profile_value.get("links", [])
        return {
            "bio_html": inline_html(profile_value.get("bio", ""), lang),
            "email": str(profile_value.get("email", "")),
            "handle": str(profile_value.get("handle", "")),
            "links": links if isinstance(links, list) else [],
            "name": str(profile_value.get("name", "")),
            "native_name": str(profile_value.get("native_name", "")),
            "role": localize(profile_value.get("role", ""), lang),
        }

    def __localized_publication(
        self, publication: dict[str, object], lang: str
    ) -> dict[str, object]:
        """Localize and normalize a publication entry."""
        links = self.__localized_publication_links(publication, lang)
        badges = self.__localized_publication_badges(publication, lang)
        venue = publication.get("venue", {})
        if not isinstance(venue, dict):
            raise ValueError(f"{publication.get('key')} venue must be a mapping")
        rank = venue.get("rank")
        if rank and not any(badge["label"] == localize(rank, lang) for badge in badges):
            badges.append({"label": localize(rank, lang), "tone_class": ""})
        return {
            "authors_html": self.__authors_html(str(publication.get("authors", ""))),
            "badges": badges,
            "kind": str(publication.get("kind", "")),
            "links": links,
            "note_links": [link for link in links if not link.get("has_url")],
            "primary_url": self.__primary_url(links, venue),
            "selected": bool(publication.get("selected", False)),
            "title": localize(publication.get("title", ""), lang),
            "url_links": [link for link in links if link.get("has_url")],
            "venue": {
                "short": localize(venue.get("short", ""), lang),
                "title": localize(venue.get("title", ""), lang),
                "url": str(venue.get("url", "")),
            },
        }

    def __localized_talks(
        self,
        talks_value: object,
        lang: str,
    ) -> list[dict[str, object]]:
        """Localize manually maintained talk topics sorted by latest date."""
        topics: list[dict[str, object]] = []
        if isinstance(talks_value, list):
            for topic in talks_value:
                if isinstance(topic, dict):
                    localized_topic = self.__localized_regular_talk_topic(topic, lang)
                    if localized_topic["items"]:
                        topics.append(localized_topic)
        return sorted(topics, key=lambda topic: topic["sort_key"], reverse=True)

    def __localized_regular_talk_topic(
        self, topic: dict[object, object], lang: str
    ) -> dict[str, object]:
        """Localize one manually configured talk topic."""
        items: list[dict[str, object]] = []
        topic_items = topic.get("items", [])
        if isinstance(topic_items, list):
            for item in topic_items:
                if isinstance(item, dict):
                    items.append(self.__localized_regular_talk_item(item, lang))
        items.sort(key=lambda item: item["sort_key"], reverse=True)
        return {
            "items": items,
            "sort_key": items[0]["sort_key"] if items else (0, 0, 0),
            "title_html": inline_html(topic.get("title", ""), lang),
        }

    def __localized_regular_talk_item(
        self, talk: dict[object, object], lang: str
    ) -> dict[str, object]:
        """Localize one non-workshop talk."""
        notes = self.__localized_note_badges(talk.get("notes", []), lang)
        return {
            "date": self.__format_timepoint(talk.get("date"), lang),
            "host_html": inline_html(talk.get("host", ""), lang),
            "notes_text": self.__notes_text(notes),
            "sort_key": self.__timepoint_sort_key(talk.get("date")),
        }

    def __localized_badges(
        self, badges_value: object, lang: str
    ) -> list[dict[str, str]]:
        """Localize publication badges."""
        badges: list[dict[str, str]] = []
        if not isinstance(badges_value, list):
            return badges
        for badge in badges_value:
            if isinstance(badge, dict):
                badges.append(
                    {
                        "label": localize(badge.get("label", ""), lang),
                        "tone_class": localize(badge.get("tone", ""), lang),
                    }
                )
            else:
                badges.append({"label": localize(badge, lang), "tone_class": ""})
        return badges

    def __localized_publication_badges(
        self, publication: dict[str, object], lang: str
    ) -> list[dict[str, str]]:
        """Build publication badges with award/status priority."""
        badges: list[dict[str, str]] = []
        award = publication.get("award")
        status = publication.get("status")
        if award:
            badges.append({"label": localize(award, lang), "tone_class": "award"})
        elif status:
            badges.append({"label": localize(status, lang), "tone_class": "status"})
        badges.extend(self.__localized_badges(publication.get("badges", []), lang))
        return badges

    def __localized_publication_links(
        self, publication: dict[str, object], lang: str
    ) -> list[dict[str, object]]:
        """Localize publication links and infer workshop PDFs by key."""
        links = self.__localized_links(publication.get("links", []), lang)
        if publication.get("kind") != "workshop":
            return links
        if any(link.get("label") == "PDF" for link in links):
            return links
        key = publication.get("key")
        if not isinstance(key, str) or not key:
            return links
        pdf_path = Path("pdfs") / "workshops" / f"{key}.pdf"
        if (self.__root / pdf_path).is_file():
            links.append(
                {
                    "has_url": True,
                    "label": "PDF",
                    "url": self.__page_url(pdf_path.as_posix(), lang),
                }
            )
        return links

    def __localized_links(
        self, links_value: object, lang: str
    ) -> list[dict[str, object]]:
        """Localize publication action links."""
        links: list[dict[str, object]] = []
        if not isinstance(links_value, list):
            return links
        for link in links_value:
            if not isinstance(link, dict):
                continue
            label = localize(link.get("label", ""), lang)
            if not label:
                continue
            url = self.__page_url(str(link.get("url", "")), lang)
            links.append(
                {
                    "has_url": bool(url),
                    "label": label,
                    "url": url,
                }
            )
        return links

    def __localized_awards(
        self, awards_value: object, lang: str, featured_only: bool
    ) -> list[dict[str, object]]:
        """Localize award groups."""
        groups: list[dict[str, object]] = []
        if not isinstance(awards_value, list):
            return groups
        for group in awards_value:
            if not isinstance(group, dict):
                continue
            if featured_only and not group.get("featured", False):
                continue
            items = group.get("items", [])
            groups.append(
                {
                    "items": self.__localized_text_list(items, lang),
                    "title": localize(group.get("title", ""), lang),
                }
            )
        return groups

    def __localized_timeline(
        self, items_value: object, lang: str
    ) -> list[dict[str, str]]:
        """Localize timeline items with rendered periods."""
        items: list[dict[str, str]] = []
        if not isinstance(items_value, list):
            return items
        for item in items_value:
            if not isinstance(item, dict):
                continue
            items.append(
                {
                    "period": self.__format_period(item, lang),
                    "text_html": inline_html(item.get("text", ""), lang),
                }
            )
        return items

    def __localized_projects(
        self, groups_value: object, lang: str
    ) -> list[dict[str, object]]:
        """Localize project groups and their detail lists."""
        groups: list[dict[str, object]] = []
        if not isinstance(groups_value, list):
            return groups
        for group in groups_value:
            if not isinstance(group, dict):
                continue
            projects: list[dict[str, object]] = []
            group_items = group.get("items", [])
            if isinstance(group_items, list):
                for item in group_items:
                    if isinstance(item, dict):
                        projects.append(self.__localized_project(item, lang))
            groups.append(
                {"items": projects, "title": localize(group.get("title", ""), lang)}
            )
        return groups

    def __localized_project(
        self, item: dict[object, object], lang: str
    ) -> dict[str, object]:
        """Localize one project item."""
        name = localize(item.get("name", ""), lang)
        url = str(item.get("url", ""))
        details = self.__localized_text_list(item.get("details", []), lang)
        if url:
            name_html = f'<a href="{html.escape(url)}" target="_blank" rel="noopener">{html.escape(name)}</a>'
        else:
            name_html = html.escape(name)
        return {
            "details": details,
            "has_details": bool(details),
            "name_html": name_html,
            "note": localize(item.get("note", ""), lang),
            "period": self.__format_period(item, lang),
            "summary_html": inline_html(item.get("summary", ""), lang),
        }

    def __localized_text_list(self, value: object, lang: str) -> list[dict[str, str]]:
        """Localize a list of inline text values."""
        if not isinstance(value, list):
            return []
        return [{"text_html": inline_html(item, lang)} for item in value]

    def __localized_note_badges(self, value: object, lang: str) -> list[dict[str, str]]:
        """Localize short talk notes as neutral badges."""
        if not isinstance(value, list):
            return []
        return [
            {"label": localize(item, lang), "tone_class": ""}
            for item in value
            if localize(item, lang)
        ]

    def __notes_text(self, notes: list[dict[str, str]]) -> str:
        """Render talk notes as restrained inline text."""
        return ", ".join(note["label"] for note in notes if note.get("label"))

    def __format_period(self, item: dict[object, object], lang: str) -> str:
        """Render structured start and end values for display."""
        start = self.__format_timepoint(item.get("start"), lang)
        end_value = item.get("end")
        end = self.__format_timepoint(end_value, lang)
        separator = str(item.get("separator", " - "))
        if not start and not end:
            return ""
        if start and not end:
            return start
        if end_value == "present" and lang == "zh-cn":
            return f"{start} 至今"
        return f"{start}{separator}{end}"

    def __format_timepoint(self, value: object, lang: str) -> str:
        """Render one structured timepoint."""
        if value == "present":
            return "present" if lang == "en" else "至今"
        if not isinstance(value, dict):
            return ""
        year = value.get("year")
        month = value.get("month")
        if not year:
            return ""
        if month:
            return f"{year}.{month}"
        return str(year)

    def __timepoint_sort_key(self, value: object) -> tuple[int, int, int]:
        """Return a sortable date key for structured timepoints."""
        if not isinstance(value, dict):
            return (0, 0, 0)
        year = value.get("year")
        month = value.get("month", 0)
        day = value.get("day", 0)
        if not isinstance(year, int):
            return (0, 0, 0)
        return (
            year,
            month if isinstance(month, int) else 0,
            day if isinstance(day, int) else 0,
        )

    def __urls(self, lang: str, page: str) -> dict[str, str]:
        """Return localized page URLs for the navigation header."""
        switch_page = "" if page == "index.html" else page
        if lang == "en":
            return {
                "about": "about.html",
                "home": ".",
                "publications": "publications.html",
                "switch_lang": f"zh-cn/{switch_page}",
            }
        return {
            "about": "about.html",
            "home": ".",
            "publications": "publications.html",
            "switch_lang": f"../{switch_page}",
        }

    def __page_url(self, url: str, lang: str) -> str:
        """Adjust local asset URLs for localized output directories."""
        if not url or "://" in url or url.startswith(("mailto:", "#")):
            return url
        return url if lang == "en" else f"../{url}"

    def __primary_url(
        self, links: list[dict[str, object]], venue: dict[object, object]
    ) -> str:
        """Choose the main publication link from action links and venue URL."""
        for preferred in ("DOI", "PDF", "Tool"):
            for link in links:
                if link.get("label") == preferred:
                    return link.get("url", "")
        return str(venue.get("url", ""))

    def __authors_html(self, authors: str) -> str:
        """Escape authors and emphasize the homepage owner."""
        escaped = html.escape(authors)
        return escaped.replace("Hanzhi Liu", "<strong>Hanzhi Liu</strong>")
