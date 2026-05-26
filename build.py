from sitegen.builder import SiteBuilder


def main() -> None:
    """Build the static homepage from YAML data and HTML templates."""
    SiteBuilder().build()


if __name__ == "__main__":
    main()
