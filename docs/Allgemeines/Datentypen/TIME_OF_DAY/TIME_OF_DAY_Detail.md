# Datentyp-Detail: TIME_OF_DAY (TOD)

```{index} single: Datentyp-Detail: TIME_OF_DAY (TOD)
```

## Beschreibung
Der Datentyp **TIME_OF_DAY** (kurz **TOD**) wird zur Darstellung der Tageszeit verwendet.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 14a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | Meist 32 Bit (Implementierungsabhängig) |
| **Voreingestellter Wert** | `TOD#00:00:00` |

## Literaldarstellung
Literale beginnen mit dem Präfix `TOD#` oder `TIME_OF_DAY#`. Das Format folgt dem Schema `hh:mm:ss.ss`.

### Beispiele
- `TOD#15:36:55.36`
- `TIME_OF_DAY#08:00:00`
- `tod#23:59:59.999`
