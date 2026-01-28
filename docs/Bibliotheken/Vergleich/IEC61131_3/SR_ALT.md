# SR (Bistabil, vorrangig setzen) - IEC 61131-3

Der Funktionsbaustein **SR** ist ein bistabiles Element (Flip-Flop), bei dem das Setzen Vorrang vor dem Rücksetzen hat.

## Schnittstelle

| Typ | Name | Datentyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Eingang** | S1 | BOOL | Setz-Eingang (Set) |
| **Eingang** | R | BOOL | Rücksetz-Eingang (Reset) |
| **Ausgang** | Q1 | BOOL | Ausgangszustand |

## Funktion

Das Verhalten entspricht der **Tabelle 43** (Bistabile Standardfunktionsbausteine) der Norm DIN EN 61131-3.

Die Logik wird durch folgende Wahrheitstabelle beschrieben:

| S1 | R | Q1 (aktuell) | Beschreibung |
| :---: | :---: | :---: | :--- |
| 0 | 0 | Q1 (alt) | Zustand halten |
| 0 | 1 | 0 | Rücksetzen |
| 1 | 0 | 1 | Setzen |
| 1 | 1 | 1 | **Vorrangig Setzen** |

*Anmerkung: Der Anfangszustand der Ausgangsvariable `Q1` ist standardmäßig `0` (FALSE).*

## Logische Gleichung

In der grafischen Darstellung (FBS) wird dies oft als ODER-Gatter am Setz-Eingang und einem Speicherglied dargestellt, aber logisch entspricht der Zustand:

```text
Q1 := S1 OR (Q1 AND NOT R);
```
*(Unter Berücksichtigung der Dominanz von S1 bei gleichzeitiger Aktivierung)*
Genauer laut Norm-Rumpf (Tabelle 43, 1a):
```text
Q1 := S1 OR (NOT R AND Q1);
```
Wenn `S1` TRUE ist, ist `Q1` TRUE, unabhängig von `R`.
