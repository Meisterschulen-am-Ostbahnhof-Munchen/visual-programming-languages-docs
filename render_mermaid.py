import re
import subprocess
import sys
from pathlib import Path


FENCE = "```"
MERMAID_BLOCK = re.compile(r"(?ms)^```mermaid\s*\n(.*?)^```\s*$")


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
        image_path = output_dir / f"mermaid-{counter:04d}.svg"
        source_path.write_text(match.group(1).strip() + "\n", encoding="utf-8")
        subprocess.run(
            ["mmdc", "-i", str(source_path), "-o", str(image_path), "--quiet"],
            check=True,
        )
        source_path.unlink()
        return f"![Mermaid diagram](img/mermaid/{image_path.stem}.svg)"

    rendered = MERMAID_BLOCK.sub(replace, source)
    combined.write_text(rendered, encoding="utf-8")
    print(f"Rendered {counter} Mermaid diagrams for {language}")


if __name__ == "__main__":
    for language in sys.argv[1:]:
        render_language(language)
