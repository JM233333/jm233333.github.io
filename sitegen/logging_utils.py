import logging
import sys
from pathlib import Path


def setup_logger(name: str) -> logging.Logger:
    """Create a console and file logger for a site generator subsystem."""
    logger = logging.getLogger(name)
    if logger.handlers:
        return logger

    logger.setLevel(logging.INFO)
    log_dir = Path("tmp/logs")
    log_dir.mkdir(parents=True, exist_ok=True)

    formatter = logging.Formatter("%(levelname)s:%(name)s:%(message)s")
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setFormatter(formatter)

    file_handler = logging.FileHandler(log_dir / f"{name}.log", encoding="utf-8")
    file_handler.setFormatter(formatter)

    logger.addHandler(console_handler)
    logger.addHandler(file_handler)
    return logger
