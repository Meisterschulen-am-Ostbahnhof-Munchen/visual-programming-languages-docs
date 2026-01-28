# TON (Einschaltverzögerung) - IEC 61131-3

Der Funktionsbaustein **TON** (Timer On-Delay) implementiert eine Einschaltverzögerung. Der Ausgang wird erst aktiviert, wenn das Eingangssignal für eine definierte Zeit anliegt.

## Schnittstelle

| Typ | Name | Datentyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Eingang** | IN | BOOL | Startsignal |
| **Eingang** | PT | TIME | Preset Time (Verzögerungszeit) |
| **Ausgang** | Q | BOOL | Ausgangssignal |
| **Ausgang** | ET | TIME | Elapsed Time (verstrichene Zeit) |

## Funktion

Das Verhalten entspricht der **Tabelle 46** (Standardfunktionsbausteine Zeitgeber) und dem **Bild 15 b)** (Einschalt-Verzögerung (TON) Zeitverhalten) der Norm DIN EN 61131-3.

- **Start:** Wenn `IN` `TRUE` ist, beginnt die Zeitmessung `ET`.
- **Ablauf:** Wenn `ET` den Wert von `PT` erreicht hat und `IN` immer noch `TRUE` ist, wird der Ausgang `Q` auf `TRUE` gesetzt.
- **Halten:** `Q` bleibt `TRUE`, solange `IN` `TRUE` ist.
- **Abbruch:** Wenn `IN` auf `FALSE` wechselt (bevor oder nachdem `PT` abgelaufen ist), wird `ET` auf 0 zurückgesetzt und `Q` wird `FALSE`.

## Zeitdiagramm (Prinzip)

```text
      +---------------------+
IN    |                     |
    --+                     +-------
      :   PT   :
               +------------+
Q              |            |
    -----------+            +-------
      :        :
ET    /--------X------------\
    -/                       \------
```
