# Datentyp-Detail: QUARTER

```{index} single: Datentyp-Detail: QUARTER
```

## Beschreibung
Der Datentyp **QUARTER** ist ein 2-Bit Datentyp, der vier Zustände repräsentiert. Er ist nicht normativ in der IEC 61131-3 oder IEC 61499 verankert, sondern lehnt sich an Definitionen aus der **SAE J1939** bzw. **ISO 11783-6** (ISOBUS) an.

## Definition und Wertebereich

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 2 |
| **Anzahl Zustände** | 4 |

### Standard-Zustandsdefinition (angelehnt an SAE J1939)

| Binärwert | Dezimal | Bedeutung (Typisch) |
| :--- | :--- | :--- |
| `00` | 0 | **Aus / OFF** |
| `01` | 1 | **Ein / ON** |
| `10` | 2 | **Fehler / Error** (oder Reserved) |
| `11` | 3 | **Nicht verfügbar / Not Available** (oder Don't Care) |

## Verwendung
Dieser Datentyp wird häufig zur effizienten Übertragung von Zustandsinformationen verwendet, bei denen neben dem reinen Schaltzustand (Ein/Aus) auch Diagnoseinformationen (Fehler, Nicht Verfügbar) relevant sind.

## Hinweise
Da **QUARTER** kein Standard-Datentyp der IEC-Normen ist, wird er in Programmierumgebungen oft als `BYTE` oder `USINT` abgebildet, wobei nur die unteren 2 Bits relevant sind oder mehrere QUARTER-Werte in ein Byte gepackt werden (Packing).
