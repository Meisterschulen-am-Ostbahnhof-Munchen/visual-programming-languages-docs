# RS (Bistabil, vorrangig rücksetzen) - IEC 61131-3

Der Funktionsbaustein **RS** ist ein bistabiles Element (Flip-Flop), bei dem das Rücksetzen Vorrang vor dem Setzen hat.

## Schnittstelle

| Typ | Name | Datentyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Eingang** | S | BOOL | Setz-Eingang (Set) |
| **Eingang** | R1 | BOOL | Rücksetz-Eingang (Reset) |
| **Ausgang** | Q1 | BOOL | Ausgangszustand |

## Funktion

Das Verhalten entspricht der **Tabelle 43** (Bistabile Standardfunktionsbausteine) der Norm DIN EN 61131-3.

Die Logik wird durch folgende Wahrheitstabelle beschrieben:

| S | R1 | Q1 (aktuell) | Beschreibung |
| :---: | :---: | :---: | :--- |
| 0 | 0 | Q1 (alt) | Zustand halten |
| 0 | 1 | 0 | Rücksetzen |
| 1 | 0 | 1 | Setzen |
| 1 | 1 | 0 | **Vorrangig Rücksetzen** |

*Anmerkung: Der Anfangszustand der Ausgangsvariable `Q1` ist standardmäßig `0` (FALSE).*

## Logische Gleichung

Gemäß dem Funktionsbaustein-Rumpf in der Norm (Tabelle 43, 2a):

```text
Q1 := NOT R1 AND (S OR Q1);
```


## Siehe auch

*   [E_RS (IEC 61499)](../../StandardLibraries/events/E_RS.md): Das ereignisgesteuerte Äquivalent in der IEC 61499. Beachten Sie, dass dort keine garantierte "Dominanz" bei gleichzeitigen Ereignissen existiert.
