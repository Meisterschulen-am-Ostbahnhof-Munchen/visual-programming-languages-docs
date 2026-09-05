# Data Type Details: STRING

## Description

The **STRING** data type represents a string consisting of 8-bit characters (usually ISO/IEC 10646-1 or ASCII).

## Normative Definition

According to **DIN EN 61131-3** (Table 10, No. 16a):

| Property | Value |
| :--- | :--- |
| **Bits** | 8 bits per character |
| **Default Value** | '' (empty string) |
| **Maximum Length** | Vendor-specific (standard often 255) |

## Literal Representation

String literals are enclosed in **single quotation marks** (`'`).

### Special Characters (Escape Sequences)

Special characters are introduced by a dollar sign (`$`):

| Sequence | Meaning |
| :--- | :--- |
| `$$` | Dollar sign |
| `$'` | Single quotation mark |
| `$L` or `$l` | Line feed |
| `$N` or `$n` | Newline |
| `$P` or `$p` | Page feed |
| `$R` or `$r` | Carriage Return |
| `$T` or `$t` | Tab |
| `$hh` | Character with Hex Code `hh` (e.g., `$41` for 'A') |

### Examples

- `'Hallo Welt'` (Plain Text)
- `'Zeile 1$NZeile 2'` (With line break)
- `'Zahl: $R$L100'` (carriage return and line feed)
- `'STRING#''Abc'''` (With explicit type prefix)

## 🛠️ Related exercises

- [Uebung_012a_sub](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_012a_sub/)
- [Uebung_020c2_sub](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_020c2_sub/)
- [Uebung_051](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_051/)
- [Uebung_052](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_052/)
- [Uebung_120](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_120/)
- [Uebung_121](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_121/)
- [Uebung_122](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_122/)
- [Uebung_122b](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_122b/)
- [Uebung_123](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_123/)
- [Uebung_124](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_124/)
- [Uebung_125](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_125/)
- [Uebung_126](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_126/)
- [Uebung_126b2_sub](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_126b2_sub/)
- [Uebung_126b_sub](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_126b_sub/)
- [Uebung_127](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_127/)
- [Uebung_128](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_128/)
- [Uebung_128b](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_128b/)
- [Uebung_12x_sub](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_12x_sub/)
- [Uebung_130](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_130/)
- [Uebung_131](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_131/)
- [Uebung_132](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_132/)
- [Uebung_133](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_133/)
- [Uebung_134](https://docs.ms-muc-docs.de/projects/4diac-exercises-docs/en/latest/test_B/Uebungen_doc/Uebung_134/)
