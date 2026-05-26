import html
import re
from pathlib import Path


class TemplateRenderer:
    """Render the small Mustache subset used by the HTML templates."""

    __section_pattern = re.compile(r"{{#\s*([\w.]+)\s*}}(.*?){{/\s*\1\s*}}", re.DOTALL)
    __html_pattern = re.compile(r"{{{\s*([\w.]+)\s*}}}")
    __variable_pattern = re.compile(r"{{\s*([\w.]+)\s*}}")

    def render_file(self, path: Path, context: dict[str, object]) -> str:
        """Render a template file with the provided context."""
        return self.render(path.read_text(encoding="utf-8"), [context])

    def render(self, template: str, stack: list[object]) -> str:
        """Render a template string with a context stack."""
        template = self.__render_sections(template, stack)
        template = self.__html_pattern.sub(
            lambda match: self.__stringify(self.__resolve(match.group(1), stack)),
            template,
        )
        return self.__variable_pattern.sub(
            lambda match: html.escape(
                self.__stringify(self.__resolve(match.group(1), stack))
            ),
            template,
        )

    def __render_sections(self, template: str, stack: list[object]) -> str:
        """Expand truthy and repeated sections recursively."""
        while True:
            match = self.__section_pattern.search(template)
            if match is None:
                return template
            name = match.group(1)
            body = match.group(2)
            value = self.__resolve(name, stack)
            rendered = self.__render_section_value(body, value, stack)
            template = template[: match.start()] + rendered + template[match.end() :]

    def __render_section_value(
        self, body: str, value: object, stack: list[object]
    ) -> str:
        """Render a section according to Mustache-like truthiness rules."""
        if isinstance(value, list):
            return "".join(self.render(body, stack + [item]) for item in value)
        if isinstance(value, dict):
            return self.render(body, stack + [value]) if value else ""
        if value:
            return self.render(body, stack)
        return ""

    def __resolve(self, path: str, stack: list[object]) -> object:
        """Resolve a dotted path from the nearest context."""
        if path == ".":
            return stack[-1] if stack else ""
        parts = path.split(".")
        for scope in reversed(stack):
            value: object = scope
            found = True
            for part in parts:
                if isinstance(value, dict) and part in value:
                    value = value[part]
                else:
                    found = False
                    break
            if found:
                return value
        return ""

    def __stringify(self, value: object) -> str:
        """Convert template values to strings."""
        if value is None:
            return ""
        return str(value)


def inline_html(value: object, lang: str) -> str:
    """Localize and render a small inline Markdown subset as HTML."""
    text = normalize_inline_text(localize(value, lang), lang)
    escaped = html.escape(text, quote=True)
    escaped = re.sub(
        r"\[([^\]]+)\]\(([^)]+)\)",
        r'<a href="\2" target="_blank" rel="noopener">\1</a>',
        escaped,
    )
    return re.sub(r"\*\*(.+?)\*\*", r"<strong>\1</strong>", escaped)


def normalize_inline_text(text: str, lang: str) -> str:
    """Remove layout whitespace that is visible in CJK prose."""
    if lang != "zh-cn":
        return text
    text = re.sub(r"(?<=[\u3400-\u9fff])\s+(?=[\u3400-\u9fff])", "", text)
    text = re.sub(r"\s+([，。；：？！、）】》])", r"\1", text)
    text = re.sub(r"([（【《])\s+", r"\1", text)
    return text


def localize(value: object, lang: str) -> str:
    """Pick a localized scalar, falling back to English or the first value."""
    if isinstance(value, dict):
        if lang in value:
            return localize(value[lang], lang)
        if "en" in value:
            return localize(value["en"], lang)
        for item in value.values():
            return localize(item, lang)
        return ""
    if value is None:
        return ""
    return str(value)
