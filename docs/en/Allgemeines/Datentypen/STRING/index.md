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

`$R` or `$r` | Carriage Return |

`$T` or `$t` | Tab |

`$hh` | Character with Hex Code `hh` (e.g., `$41` for 'A') |

### Examples
- `'Hallo Welt'` (Plain Text)
- `'Zeile 1$NZeile 2'` (With line break)
- `'Zahl: $R$L100'` (carriage return and line feed)
- `'STRING#''Abc'''` (With explicit type prefix)

## 🛠️ Related exercises
* [Uebung_012a_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_012a_sub.md)
* [Uebung_020c2_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2_sub.md)
* [Uebung_051](../../../Uebungen/test_B/Uebungen_doc/Uebung_051.md)
* [Uebung_052](../../../Uebungen/test_B/Uebungen_doc/Uebung_052.md)
* [Uebung_120](../../../Uebungen/test_B/Uebungen_doc/Uebung_120.md)
* [Uebung_121](../../../Uebungen/test_B/Uebungen_doc/Uebung_121.md)
* [Uebung_122](../../../Uebungen/test_B/Uebungen_doc/Uebung_122.md)
* [Uebung_122b](../../../Uebungen/test_B/Uebungen_doc/Uebung_122b.md)
* [Uebung_123](../../../Uebungen/test_B/Uebungen_doc/Uebung_123.md)
* [Uebung_124](../../../Uebungen/test_B/Uebungen_doc/Uebung_124.md)
* [Uebung_125](../../../Uebungen/test_B/Uebungen_doc/Uebung_125.md)
* [Uebung_126](../../../Uebungen/test_B/Uebungen_doc/Uebung_126.md)
* [Uebung_126b2_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_126b2_sub.md)
* [Uebung_126b_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_126b_sub.md)
* [Uebung_127](../../../Uebungen/test_B/Uebungen_doc/Uebung_127.md)
* [Uebung_128](../../../Uebungen/test_B/Uebungen_doc/Uebung_128.md)
* [Uebung_128b](../../../Uebungen/test_B/Uebungen_doc/Uebung_128b.md)
* [Uebung_12x_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_12x_sub.md)
* [Uebung_130](../../../Uebungen/test_B/Uebungen_doc/Uebung_130.md)
* [Uebung_131](../../../Uebungen/test_B/Uebungen_doc/Uebung_131.md)
* [Uebung_132](../../../Uebungen/test_B/Uebungen_doc/Uebung_132.md)
* [Uebung_133](../../../Uebungen/test_B/Uebungen_doc/Uebung_133.md)
* [Uebung_134](../../../Uebungen/test_B/Uebungen_doc/Uebung_134.md)

