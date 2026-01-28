# Datentyp-Detail: LDATE

```{index} single: Datentyp-Detail: LDATE
```

## Beschreibung
Der Datentyp **LDATE** (Long Date) repräsentiert ein Kalenderdatum mit einer Breite von 64 Bit und ermöglicht einen wesentlich größeren Zeitrahmen.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 13b):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 64 Bit |
| **Voreingestellter Wert** | `LD#1970-01-01` |
| **Einheit** | Nanosekunden seit 1970-01-01 |

## Literaldarstellung
LDATE-Literale beginnen mit dem Präfix `LD#` oder `LDATE#`.

### Beispiele
- `LD#2026-01-17`
- `LDATE#2012-02-29` (Schaltjahr-Unterstützung)