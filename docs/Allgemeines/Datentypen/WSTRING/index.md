# Datentyp-Detail: WSTRING

## Beschreibung
Der Datentyp **WSTRING** (Wide String) repräsentiert eine Zeichenfolge aus "weiten" Zeichen (16-Bit), üblicherweise im Unicode-Format (UTF-16).

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 16b):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 16 Bit pro Zeichen |
| **Voreingestellter Wert** | "" (leere Zeichenfolge) |

## Literaldarstellung
WSTRING-Literale werden in **doppelte Anführungszeichen** (`"`) eingeschlossen.

### Sonderzeichen (Escape-Sequenzen)
Ähnlich wie bei STRING, jedoch mit Unterstützung für 16-Bit-Hex-Codes:

| Sequenz | Bedeutung |
| :--- | :--- |
| `$" ` | Doppeltes Anführungszeichen |
| `$hhhh` | Zeichen mit 16-Bit Hex-Code (z.B. `$00C4` für 'Ä') |

### Beispiele
- `"Dies ist ein WSTRING"`
- `"Sonderzeichen: $00D6"` (für 'Ö')
- `"WSTRING#"Unicode-Text""` (Mit explizitem Typ-Präfix)