# Data Type Details: WSTRING

## Description

The **WSTRING** (Wide String) data type represents a string of "wide" characters (16 bits), usually in Unicode format (UTF-16).

## Normative Definition

According to **DIN EN 61131-3** (Table 10, No. 16b):

| Property | Value |
| :--- | :--- |
| **Bits** | 16 bits per character |
| **Default Value** | "" (empty string) |

## Literal Representation

WSTRING literals are enclosed in **double quotation marks** (`"`).

### Special Characters (Escape Sequences)

Similar to STRING, but with support for 16-bit hex codes:

| Sequence | Meaning |
| :--- | :--- |
| `$" ` | Double quotation mark |
| `$hhhh` | Character with 16-bit hex code (e.g., `$00C4` for 'Ä') |

### Examples

- `"Dies ist ein WSTRING"`
- `"Sonderzeichen: $00D6"` (for 'Ö')
- `"WSTRING#"Unicode-Text""` (With explicit type prefix)
