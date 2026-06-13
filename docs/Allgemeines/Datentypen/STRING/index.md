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

