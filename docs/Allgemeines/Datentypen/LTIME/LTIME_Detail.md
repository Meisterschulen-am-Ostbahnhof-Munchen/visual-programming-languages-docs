# Datentyp-Detail: LTIME

```{index} single: Datentyp-Detail: LTIME
```

## Beschreibung
Der Datentyp **LTIME** (Long Time) dient zur Darstellung von hochauflösenden Zeitdauern mit einer Breite von 64 Bit.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 12b):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 64 Bit |
| **Voreingestellter Wert** | `LTIME#0s` |
| **Auflösung** | Nanosekunden |

## Literaldarstellung
LTIME-Literale beginnen mit dem Präfix `LT#` oder `LTIME#`.

### Einheiten (zusätzlich zu TIME)
- `us`: Mikrosekunden (microseconds)
- `ns`: Nanosekunden (nanoseconds)

### Beispiele
- `LT#10ns` (10 Nanosekunden)
- `LTIME#1000d12h30m5s12ms_450us_200ns` (Maximale Präzision)
- `LT#14.7s` (Dezimale Darstellung der kleinsten Einheit ist erlaubt)