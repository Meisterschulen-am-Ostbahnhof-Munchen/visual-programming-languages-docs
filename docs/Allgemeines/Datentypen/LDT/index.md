# Datentyp-Detail: LDT

```{index} single: Datentyp-Detail: LDT
```

## Beschreibung
Der Datentyp **LDT** (Long Date and Time) kombiniert Datum und hochauflösende Uhrzeit in einem 64-Bit-Element.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 15b):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 64 Bit |
| **Voreingestellter Wert** | `LDT#1970-01-01-00:00:00` |

## Literaldarstellung
Literale beginnen mit dem Präfix `LDT#` oder `LONG_DATE_AND_TIME#`.

### Beispiele
- `LDT#2026-01-17-12:00:00.000000000`
- `LONG_DATE_AND_TIME#1984-06-25-15:36:55.360227400`