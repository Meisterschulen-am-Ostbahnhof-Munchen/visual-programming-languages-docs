# TOF (Ausschaltverzögerung) - IEC 61131-3

Der Funktionsbaustein **TOF** (Timer Off-Delay) implementiert eine Ausschaltverzögerung. Der Ausgang bleibt nach Wegfall des Eingangssignals noch für eine definierte Zeit aktiv.

## Schnittstelle

| Typ | Name | Datentyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Eingang** | IN | BOOL | Startsignal |
| **Eingang** | PT | TIME | Preset Time (Verzögerungszeit) |
| **Ausgang** | Q | BOOL | Ausgangssignal |
| **Ausgang** | ET | TIME | Elapsed Time (verstrichene Zeit seit fallender Flanke) |

## Funktion

Das Verhalten entspricht der **Tabelle 46** (Standardfunktionsbausteine Zeitgeber) und dem **Bild 15 c)** (Ausschalt-Verzögerung (TOF) Zeitverhalten) der Norm DIN EN 61131-3.

- **Aktivierung:** Wenn `IN` `TRUE` ist, wird der Ausgang `Q` sofort auf `TRUE` gesetzt und `ET` auf 0 gehalten.
- **Start Verzögerung:** Wenn `IN` von `TRUE` auf `FALSE` wechselt (fallende Flanke), startet die Zeitmessung `ET`. `Q` bleibt weiterhin `TRUE`.
- **Ablauf:** Wenn `ET` den Wert von `PT` erreicht, wird der Ausgang `Q` auf `FALSE` gesetzt.
- **Reset:** Wenn `IN` wieder `TRUE` wird, bevor die Zeit abgelaufen ist, wird `ET` wieder auf 0 gesetzt und `Q` bleibt `TRUE`.

## Zeitdiagramm (Prinzip)

```text
      +--------+
IN    |        |
    --+        +------------------------
      :        :   PT   :
      +-----------------+
Q     |                 |
    --+                 +---------------
      :        :        :
ET             /--------\
    -----------/         \--------------
```
