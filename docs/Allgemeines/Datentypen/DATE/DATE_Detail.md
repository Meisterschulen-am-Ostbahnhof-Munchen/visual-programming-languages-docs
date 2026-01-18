# Datentyp-Detail: DATE

```{index} single: Datentyp-Detail: DATE
```

## Beschreibung
Der Datentyp **DATE** wird zur Darstellung eines Kalenderdatums verwendet.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 13a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | Meist 32 Bit (Implementierungsabhängig) |
| **Voreingestellter Wert** | `D#1970-01-01` |

## Literaldarstellung
DATE-Literale beginnen mit dem Präfix `D#` oder `DATE#`. Das Format folgt dem Schema `YYYY-MM-DD`.

### Beispiele
- `D#2026-01-17`
- `DATE#1984-06-25`
- `d#2010-09-22` (Kleinschreibung des Präfix ist zulässig)