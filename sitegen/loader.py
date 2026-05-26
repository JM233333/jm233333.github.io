from pathlib import Path

import yaml

from sitegen.logging_utils import setup_logger


class DataLoader:
    """Load site metadata and publication entries from the repository."""

    def __init__(self, root: Path) -> None:
        self.__root = root
        self.__logger = setup_logger("loader")

    def load_site(self) -> dict[str, object]:
        """Load global site metadata."""
        return self.__load_yaml(self.__root / "data" / "site.yaml")

    def load_about(self) -> dict[str, object]:
        """Load profile and about-page content."""
        about = self.__load_yaml(self.__root / "data" / "about.yaml")
        for key in ("talks", "awards", "projects"):
            about[key] = self.__load_section_yaml(key)
        return about

    def load_publication_order(self) -> dict[str, list[str]]:
        """Load the explicit publication display order grouped by kind."""
        data = self.__load_yaml(self.__root / "data" / "publications.yaml")
        order = data.get("order", {})
        if not isinstance(order, dict):
            raise ValueError("data/publications.yaml must contain an order mapping")
        return {
            str(kind): [str(key) for key in keys]
            for kind, keys in order.items()
            if isinstance(keys, list)
        }

    def load_publications(self) -> dict[str, dict[str, object]]:
        """Load every publication YAML file by key."""
        publications: dict[str, dict[str, object]] = {}
        for path in sorted((self.__root / "publications").rglob("*.yaml")):
            data = self.__load_yaml(path)
            key = data.get("key")
            if not isinstance(key, str):
                raise ValueError(f"{path} must define a string key")
            if key in publications:
                raise ValueError(f"Duplicate publication key: {key}")
            publications[key] = data
        self.__logger.info("loaded %d publication entries", len(publications))
        return publications

    def __load_yaml(self, path: Path) -> dict[str, object]:
        """Read a YAML mapping from disk."""
        self.__logger.info("loading %s", path)
        with path.open("r", encoding="utf-8") as file:
            data = yaml.safe_load(file) or {}
        if not isinstance(data, dict):
            raise ValueError(f"{path} must contain a YAML mapping")
        return data

    def __load_section_yaml(self, key: str) -> object:
        """Read one split about-page section from data/<key>.yaml."""
        path = self.__root / "data" / f"{key}.yaml"
        data = self.__load_yaml(path)
        if key not in data:
            raise ValueError(f"{path} must define a {key} section")
        return data[key]
