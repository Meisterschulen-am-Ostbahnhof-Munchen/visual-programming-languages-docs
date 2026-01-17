# Datentyp-Detail: DATE_AND_TIME (DT)

## Beschreibung
Der Datentyp **DATE_AND_TIME** (kurz **DT**) kombiniert Kalenderdatum und Tageszeit in einem einzigen Element.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 15a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | Meist 32 Bit (Implementierungsabhängig) |
| **Voreingestellter Wert** | `DT#1970-01-01-00:00:00` |

## Literaldarstellung
Literale beginnen mit dem Präfix `DT#` oder `DATE_AND_TIME#`. Das Format folgt dem Schema `YYYY-MM-DD-hh:mm:ss.ss`.

### Beispiele
- `DT#2026-01-17-12:00:00`
- `DATE_AND_TIME#1984-06-25-15:36:55.36`
- `dt#2010-09-22-00:00:00`