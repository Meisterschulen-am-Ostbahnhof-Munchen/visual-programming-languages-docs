# Datentyp-Detail: STRING

## Beschreibung

Der Datentyp **STRING** repräsentiert eine Zeichenfolge, die aus 8-Bit-Zeichen (üblicherweise ISO/IEC 10646-1 oder ASCII) besteht.

## Normative Definition

Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 16a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 8 Bit pro Zeichen |
| **Voreingestellter Wert** | '' (leere Zeichenfolge) |
| **Maximale Länge** | Herstellerspezifisch (Standard oft 255) |

## Literaldarstellung

Zeichenfolge-Literale werden in **einfache Anführungszeichen** (`'`) eingeschlossen.

### Sonderzeichen (Escape-Sequenzen)

Sonderzeichen werden durch ein Dollar-Zeichen (`$`) eingeleitet:

| Sequenz | Bedeutung |
| :--- | :--- |
| `$$` | Dollar-Zeichen |
| `$'` | Einfaches Anführungszeichen |
| `$L` oder `$l` | Zeilenvorschub (Line Feed) |
| `$N` oder `$n` | Neue Zeile (Newline) |
| `$P` oder `$p` | Seitenvorschub (Page Feed) |
| `$R` oder `$r` | Wagenrücklauf (Carriage Return) |
| `$T` oder `$t` | Tabulator |
| `$hh` | Zeichen mit Hex-Code `hh` (z.B. `$41` für 'A') |

### Beispiele

- `'Hallo Welt'` (Einfacher Text)
- `'Zeile 1$NZeile 2'` (Mit Zeilenumbruch)
- `'Zahl: $R$L100'` (Wagenrücklauf und Zeilenvorschub)
- `'STRING#''Abc'''` (Mit explizitem Typ-Präfix)

## 🛠️ Zugehörige Übungen

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
