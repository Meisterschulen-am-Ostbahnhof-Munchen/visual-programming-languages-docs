# Datentyp-Detail: STRING

```{index} single: Datentyp-Detail: STRING
```

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