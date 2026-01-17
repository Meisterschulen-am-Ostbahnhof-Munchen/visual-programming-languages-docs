# Datentyp-Detail: LTOD

## Beschreibung
Der Datentyp **LTOD** (Long Time of Day) repräsentiert die Tageszeit mit einer hohen Auflösung von 64 Bit (Nanosekunden-Präzision).

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 14b):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 64 Bit |
| **Voreingestellter Wert** | `LTOD#00:00:00` |

## Literaldarstellung
Literale beginnen mit dem Präfix `LTOD#` oder `LONG_TIME_OF_DAY#`.

### Beispiele
- `LTOD#15:36:55.360227400`
- `LONG_TIME_OF_DAY#00:00:00.000000001`
