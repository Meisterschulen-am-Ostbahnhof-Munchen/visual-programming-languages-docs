# AX_FB_R_TRIG

![AX_FB_R_TRIG](AX_FB_R_TRIG.png)


![AX_FB_R_TRIG](.././AX_FB_R_TRIG.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AX_FB_R_TRIG** (Rising Trigger mit AX-Adapter) dient zur Erkennung einer steigenden Flanke eines booleschen Signals. Im Gegensatz zum Standard-`R_TRIG`-Baustein nach IEC 61131-3 verwendet dieser Baustein **AX-Adapter** für die Ein- und Ausgabe. Er kapselt die Logik zur Flankenerkennung in einer adapterbasierten Architektur, was die Verschaltung in Systemen vereinfacht, die `adapter::types::unidirectional::AX` verwenden.

Das Ziel ist es, ein `TRUE`-Signal am Ausgang zu erzeugen, wenn das Eingangssignal von `FALSE` auf `TRUE` wechselt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Dieser Baustein verfügt über keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Adapter `CLK`.*

### **Ereignis-Ausgänge**
*Dieser Baustein verfügt über keine direkten Ereignis-Ausgänge. Die Ereignisweitergabe erfolgt über den Adapter `Q`.*

### **Daten-Eingänge**
*Dieser Baustein verfügt über keine direkten Daten-Eingänge. Die Daten werden über den Adapter `CLK` empfangen.*

### **Daten-Ausgänge**
*Dieser Baustein verfügt über keine direkten Daten-Ausgänge. Die Daten werden über den Adapter `Q` ausgegeben.*

### **Adapter**

| Name | Typ | Kommentar |
| :--- | :--- | :--- |
| **CLK** | `adapter::types::unidirectional::AX` | **Socket (Eingang):** Der Takteingang (Clock), der überwacht wird. Enthält das Datensignal (D1) und das zugehörige Ereignis (E1). |
| **Q** | `adapter::types::unidirectional::AX` | **Plug (Ausgang):** Der Impulsausgang. Liefert `TRUE` nur bei einer positiven Flanke am Eingang `CLK`. |

## Funktionsweise
Der Baustein implementiert die klassische Logik eines "Rising Edge Detector" (Erkennung steigender Flanken):

1.  Der Baustein wartet auf ein Ereignis am Adapter-Eingang `CLK` (Signal `CLK.E1`).
2.  Sobald das Ereignis eintritt, wird der Algorithmus `REQ` ausgeführt.
3.  Der Algorithmus prüft den aktuellen Wert des Dateneingangs (`CLK.D1`) und vergleicht ihn mit dem gespeicherten Zustand aus dem vorherigen Zyklus (`MEM`).
    *   **Logik:** `Q.D1 := CLK.D1 AND NOT MEM`
4.  Wenn `CLK.D1` wahr (`TRUE`) ist und der gespeicherte Wert `MEM` falsch (`FALSE`) war, wird der Ausgang `Q.D1` auf `TRUE` gesetzt. In allen anderen Fällen ist `Q.D1` `FALSE`.
5.  Der interne Speicher `MEM` wird anschließend mit dem aktuellen Wert von `CLK.D1` aktualisiert.
6.  Abschließend wird das Ereignis am Ausgangsadapter `Q` (`Q.E1`) ausgelöst, um nachfolgende Bausteine zu informieren.

## Technische Besonderheiten
*   **Adapter-Kapselung:** Der Baustein ist speziell für den Typ `adapter::types::unidirectional::AX` ausgelegt. Dieser Adaptertyp bündelt typischerweise ein Ereignis (`E1`) und ein boolesches Datum (`D1`). Dies reduziert die sichtbare Verdrahtung im Anwendungsdiagramm, da Event- und Datenfluss in einer einzigen Verbindungslinie zusammengefasst sind.
*   **Interner Speicher:** Der Baustein nutzt eine interne boolesche Variable `MEM`, um den Zustand des Eingangssignals zwischen zwei Ausführungen zu speichern.

## Zustandsübersicht
Der Baustein basiert auf einer sehr einfachen Execution Control Chart (ECC) mit nur einem Zustand:

*   **Zustand `REQ`:** Dies ist der einzige Zustand.
    *   **Transition:** Der Baustein verbleibt in diesem Zustand und reagiert auf das Eingangsadapter-Ereignis `CLK.E1`.
    *   **Aktion:** Bei jedem Ereignis wird der Algorithmus `REQ` ausgeführt und das Ausgangsadapter-Ereignis `Q.E1` gesendet.

## Anwendungsszenarien
*   **Signalkonditionierung:** Umwandlung eines dauerhaften Signals (z.B. Schalter ist AN) in einen einzelnen Impuls, um eine Aktion genau einmal beim Einschalten auszulösen.
*   **Verdrahtungsvereinfachung:** Einsatz in Systemen, die konsequent auf Adapter-Technologie setzen, um die Anzahl der sichtbaren Verbindungen zwischen Funktionsblöcken zu minimieren.
*   **Start-Trigger:** Erkennung, wann ein Prozess oder eine Maschine gestartet wird (Übergang von 0 auf 1).

## Vergleich mit ähnlichen Bausteinen
*   **`R_TRIG` (Standard):** Der funktionale Kern ist identisch. Der Unterschied liegt in der Schnittstelle: `R_TRIG` nutzt separate `CLK` (BOOL) und `REQ` (Event) Eingänge sowie `Q` (BOOL) und `CNF` (Event) Ausgänge. `AX_FB_R_TRIG` nutzt Adapter.
*   **`AX_FB_F_TRIG`:** Das Gegenstück zu diesem Baustein, welches auf fallende Flanken (High-to-Low) reagiert.

## Fazit
Der **AX_FB_R_TRIG** ist ein essenzieller Utility-Baustein für Entwickler, die innerhalb der 4diac-Umgebung mit AX-Adaptern arbeiten. Er bietet die robuste Funktionalität der Standard-Flankenerkennung, verpackt in einer modernen, adapterbasierten Schnittstelle, was zu aufgeräumteren und modulareren Steuerungsanwendungen führt.