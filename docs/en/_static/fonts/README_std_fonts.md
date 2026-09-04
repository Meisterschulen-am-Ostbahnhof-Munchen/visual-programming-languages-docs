# TGL Normschrift – _std Font Variants

## Overview

The `_std` variants of the TGL Normschrift fonts fix the **U+0023 (#)** glyph, which in the original fonts incorrectly contains a "m/m" (millimeters) symbol instead of the standard number sign / hash character.

This makes the fonts usable in contexts where a proper `#` is required (e.g. programming, technical documentation, IEC 61499 function block diagrams).

## Fonts

| File | Style | Based on |
|---|---|---|
| `TGL 0-16_std.ttf` | Italic (75° slant) | TGL 0-16 |
| `TGL 0-17_std.ttf` | Upright | TGL 0-17 |
| `TGL 0-17 alt_std.ttf` | Upright (alternate) | TGL 0-17 Alt |

## Changes

### New glyph at U+0023 (`#`)

A number sign was designed from scratch to match each font's style:

- **Stroke width** matches the font (~207–208 units)
- **Round stroke caps** using the same quadratic Bézier curve pattern as the original glyphs (I, l, hyphen)
- **Height** is approximately 2/3 of the capital letter height, consistent with typical number sign proportions
- **TGL 0-16_std** (italic): vertical strokes are slanted at 75° from the baseline, matching the font's standard lean angle per DIN/TGL specification for slanted Normschrift
- **TGL 0-17_std / TGL 0-17 alt_std** (upright): all strokes are perpendicular to each other
- The glyph is constructed as a single non-overlapping outer contour with one inner counter (hole), avoiding rendering artifacts from overlapping paths

### Original m/m glyph preserved at U+E000

The original "m/m" symbol that previously occupied the `#` position has been moved to **U+E000** (Unicode Private Use Area) so it remains accessible if needed.

### Internal font names

All internal name table entries (family name, full name, PostScript name, unique ID) have `_std` appended to avoid conflicts when both original and modified fonts are installed on the same system.

## Technical Details

- Format: TrueType (.ttf)
- Units per em: 2048
- Modified using Python `fonttools` library
- No other glyphs were changed
- All original font metrics, hinting, and licensing information are preserved

## License

The original TGL Normschrift fonts are Copyright (c) 2010 by Peter Wiegel, released under GPL with font exception and OFL (Open Font License). The `_std` modifications are distributed under the same terms.
