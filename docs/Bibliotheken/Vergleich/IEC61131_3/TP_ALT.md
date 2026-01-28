# TP (Puls) - IEC 61131-3

Der Funktionsbaustein **TP** (Timer Pulse) implementiert einen Impulsgeber (Monoflop). Er erzeugt einen Ausgangsimpuls definierter Dauer.

## Schnittstelle

| Typ | Name | Datentyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Eingang** | IN | BOOL | Startsignal (steigende Flanke löst Impuls aus) |
| **Eingang** | PT | TIME | Preset Time (Impulsdauer) |
| **Ausgang** | Q | BOOL | Ausgangssignal |
| **Ausgang** | ET | TIME | Elapsed Time (verstrichene Zeit seit Impulsstart) |

## Funktion

Das Verhalten entspricht der **Tabelle 46** (Standardfunktionsbausteine Zeitgeber) und dem **Bild 15 a)** (Puls (TP) Zeitverhalten) der Norm DIN EN 61131-3.

- **Start:** Wenn `IN` von `FALSE` auf `TRUE` wechselt (steigende Flanke), wird der Ausgang `Q` auf `TRUE` gesetzt und die Zeitmessung `ET` startet.
- **Dauer:** Der Ausgang `Q` bleibt für die Zeitdauer `PT` auf `TRUE`, unabhängig davon, ob `IN` währenddessen wieder auf `FALSE` wechselt.
- **Rücksetzen:** Nachdem die Zeit `PT` abgelaufen ist (d.h. `ET` >= `PT`), fällt `Q` auf `FALSE` zurück.
- **Re-Trigger:** Der Impuls ist **nicht** nachtriggerbar. Flanken am Eingang `IN` während der Impulsausgabe (solange `ET` < `PT` und `Q` = `TRUE`) werden ignoriert.
- **Initialisierung:** `ET` wird zurückgesetzt, wenn `IN` `FALSE` ist und die Zeit abgelaufen ist oder noch nicht gestartet wurde.

## Zeitdiagramm (Prinzip)

```text
      +--------+
IN    |        |
    --+        +--------------------------
      :   PT   :
      +--------+
Q     |        |
    --+        +--------------------------
      :        :
ET    /--------\
    -/          \-------------------------
```
