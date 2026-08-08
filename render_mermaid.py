import re
import subprocess
import sys
from pathlib import Path


FENCE = "```"
# Robust against both LF and CRLF line endings.
MERMAID_BLOCK = re.compile(
    r"(?ms)^```mermaid\s*$[ \t]*\r?\n(.*?)^```\s*$[ \t]*\r?\n"
)


def _mmdc_cmd(source_path: Path, image_path: Path) -> list[str]:
    """Return the mermaid-cli command, preferring a global mmdc and
    falling back to npx (handling the Windows .cmd wrapper)."""
    import shutil
    if shutil.which("mmdc"):
        return [
            "mmdc",
            "-i", str(source_path),
            "-o", str(image_path),
            "-p", "puppeteer-config.json",
            "--quiet",
        ]
    npx = shutil.which("npx") or shutil.which("npx.cmd") or "npx"
    cmd = [
        npx, "@mermaid-js/mermaid-cli",
        "-i", str(source_path),
        "-o", str(image_path),
        "-p", "puppeteer-config.json",
        "--quiet",
    ]
    if npx.lower().endswith(".cmd"):
        cmd = ["cmd", "/c"] + cmd
    return cmd


def render_language(language):
    root = Path("docs") / language
    combined = root / "combined.md"
    output_dir = root / "img" / "mermaid"
    output_dir.mkdir(parents=True, exist_ok=True)
    source = combined.read_text(encoding="utf-8")
    counter = 0

    def replace(match):
        nonlocal counter
        counter += 1
        source_path = output_dir / f"mermaid-{counter:04d}.mmd"
        image_path = output_dir / f"mermaid-{counter:04d}.png"
        source_path.write_text(match.group(1).strip() + "\n", encoding="utf-8")
        subprocess.run(
            _mmdc_cmd(source_path, image_path),
            check=True,
        )
        source_path.unlink()
        return f"![Mermaid diagram](img/mermaid/{image_path.name})\n\n"

    rendered = MERMAID_BLOCK.sub(replace, source)
    combined.write_text(rendered, encoding="utf-8")
    print(f"Rendered {counter} Mermaid diagrams for {language}")


if __name__ == "__main__":
    for language in sys.argv[1:]:
        render_language(language)
