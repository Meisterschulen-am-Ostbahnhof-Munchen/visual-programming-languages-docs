"""Normalize Markdown unordered-list bullet markers (fixes markdownlint MD004).

Rewrites bullet markers (default: '*' -> '-') in all *.md files under a
given root, leaving fenced code blocks and thematic breaks (---, ***, ___)
untouched. Reusable across repos: point it at any docs tree.

Usage:
    python fix_ul_style.py [root] [--to -|*|+] [--dry-run]

    root        Directory to scan recursively (default: current directory)
    --to        Target bullet marker (default: -)
    --dry-run   Report which files would change without writing them
"""

import argparse
import re
import sys
from pathlib import Path

FENCE_RE = re.compile(r"^(\s*)(```|~~~)")
THEMATIC_BREAK_RE = re.compile(r"^\s*([-*_])(?:\s*\1){2,}\s*$")
BULLET_RE = re.compile(r"^(\s*)([-*+])(\s+)(\S.*)$")


def fix_text(text: str, target: str) -> tuple[str, int]:
    lines = text.splitlines(keepends=True)
    in_fence = False
    fence_marker = None
    changed = 0

    for i, line in enumerate(lines):
        body = line.rstrip("\r\n")
        line_ending = line[len(body) :]

        fence_match = FENCE_RE.match(body)
        if fence_match:
            marker = fence_match.group(2)
            if not in_fence:
                in_fence = True
                fence_marker = marker
            elif marker == fence_marker:
                in_fence = False
                fence_marker = None
            continue

        if in_fence:
            continue

        if THEMATIC_BREAK_RE.match(body):
            continue

        bullet_match = BULLET_RE.match(body)
        if bullet_match and bullet_match.group(2) != target:
            indent, _, space, content = bullet_match.groups()
            lines[i] = f"{indent}{target}{space}{content}{line_ending}"
            changed += 1

    return "".join(lines), changed


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("root", nargs="?", default=".", type=Path)
    parser.add_argument("--to", default="-", choices=["-", "*", "+"])
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args(argv)

    total_files = 0
    total_lines = 0
    for path in sorted(args.root.rglob("*.md")):
        original = path.read_text(encoding="utf-8")
        fixed, changed = fix_text(original, args.to)
        if changed:
            total_files += 1
            total_lines += changed
            print(f"{path}: {changed} bullet(s)")
            if not args.dry_run:
                path.write_text(fixed, encoding="utf-8")

    action = "Would change" if args.dry_run else "Changed"
    print(f"{action} {total_lines} bullet(s) in {total_files} file(s)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
