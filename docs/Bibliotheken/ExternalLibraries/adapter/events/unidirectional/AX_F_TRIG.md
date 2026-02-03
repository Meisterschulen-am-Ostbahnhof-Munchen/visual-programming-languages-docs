# AX_F_TRIG


![AX_F_TRIG](.././AX_F_TRIG.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AX_F_TRIG** (Boolean falling edge detection) dient der Erkennung einer fallenden Flanke (Wechsel von TRUE auf FALSE) basierend auf einem Adapter-Interface. Er ist speziell für die Verwendung mit dem unidirektionalen Adaptertyp `AX` ausgelegt.

Der Baustein überprüft den booleschen Wert, der über den Adapter empfangen wird, und löst ein Ausgabeereignis aus, wenn dieser Wert `FALSE` ist. Im Kontext von Ereignisketten, bei denen das Ereignis des Adapters eine Wertänderung signalisiert, entspricht dies der Detektion einer fallenden Flanke.

## Schnittstellenstruktur

Der Baustein verfügt über eine Adapter-Schnittstelle (Socket) für den Eingang und einen Ereignis-Ausgang.

### **Ereignis-Eingänge**
Dieser Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Adapter.

### **Ereignis-Ausgänge**
*   **EO** (Event Output): Dieses Ereignis wird ausgelöst, wenn eine fallende Flanke (oder ein logischer FALSE-Zustand) am Adapter erkannt wurde.

### **Daten-Eingänge**
Dieser Baustein besitzt keine direkten Daten-Eingänge. Die Daten werden über den Adapter bezogen.

### **Daten-Ausgänge**
Dieser Baustein besitzt keine direkten Daten-Ausgänge.

### **Adapter**
*   **QI** (Typ: `adapter::types::unidirectional::AX`): Der Eingangs-Socket. Über diesen Adapter empfängt der Baustein sowohl das Trigger-Ereignis als auch den zu prüfenden booleschen Wert.
    *   *Kommentar:* Wert, der auf eine fallende Flanke geprüft werden soll.

## Funktionsweise

Der **AX_F_TRIG** ist als zusammengesetzter Funktionsbaustein (Composite FB) realisiert. Seine interne Logik basiert auf der Verarbeitung der Signale aus dem `QI`-Adapter:

1.  Der Adapter `QI` liefert ein Ereignis (`E1`) und ein boolesches Datum (`D1`).
2.  Diese Signale werden an ein D-Flip-Flop (`E_D_FF`) weitergeleitet. Das Ereignis fungiert als Takt (CLK), das Datum als Eingang (D).
3.  Das Flip-Flop speichert den Wert und löst ein Bestätigungsereignis aus.
4.  Ein nachgeschalteter `E_SWITCH`-Baustein wertet den Ausgangszustand (`Q`) des Flip-Flops aus.
5.  Ist der Wert `FALSE` (logisch 0), schaltet der `E_SWITCH` das Ereignis auf den Ausgang **EO** durch.
6.  Ist der Wert `TRUE` (logisch 1), wird kein Ereignis am Ausgang **EO** erzeugt.

Zusammenfassend: Wenn der Adapter ein Ereignis sendet und der dabei übertragene Datenwert `FALSE` ist, feuert der Baustein `EO`.

## Technische Besonderheiten

*   **Adapter-Integration:** Der Baustein kapselt die Logik zur Aufspaltung des `AX`-Adapters in Einzelereignisse und Daten, um diese logisch zu verarbeiten.
*   **Composite Network:** Die Implementierung erfolgt rein durch Verschaltung von Standard-IEC-61499-Bausteinen (`E_D_FF`, `E_SWITCH`) und enthält keine eigenen Algorithmen in ST oder C++.

## Zustandsübersicht

Da es sich um einen Composite Function Block handelt, besitzt der **AX_F_TRIG** kein eigenes ECC (Execution Control Chart). Der Zustand wird implizit durch den Zustand der internen Bausteine (insbesondere des D-Flip-Flops `E_D_FF`) bestimmt.

## Anwendungsszenarien

*   **Signalverarbeitung:** Einsatz in Systemen, die `AX`-Adapter nutzen, um binäre Zustandsänderungen zu kommunizieren.
*   **Ausschalt-Logik:** Auslösen von Aktionen, wenn ein Sensor oder Signal, das über einen Adapter angebunden ist, in den Zustand `FALSE` (Aus/Low) wechselt.
*   **Event-Filterung:** Blockieren von Ereignissen, solange das zugehörige Datensignal `TRUE` ist, und Passierenlassen, wenn es `FALSE` ist.

## Vergleich mit ähnlichen Bausteinen

*   **E_F_TRIG:** Der Standard-Baustein für fallende Flankenerkennung in IEC 61499. Er nutzt separate Ereignis- (`EI`) und Daten-Eingänge (`QI`) anstelle eines Adapters.
*   **AX_R_TRIG:** Das direkte Gegenstück zu diesem Baustein. Es detektiert eine steigende Flanke (Wechsel auf `TRUE`) unter Verwendung desselben Adapter-Typs.
*   **E_SWITCH:** Ein generischer Schalter, der Ereignisse basierend auf einem booleschen Wert routet. **AX_F_TRIG** ist im Wesentlichen eine Spezialisierung hiervon für Adapter.

## Fazit

Der **AX_F_TRIG** ist ein spezialisierter Utility-Baustein für die strukturierte Ereignisverarbeitung in 4diac. Er vereinfacht den Umgang mit `AX`-Adaptern erheblich, indem er die Logik zur Erkennung des "Low"-Zustands (fallende Flanke) abstrahiert und direkt als Ereignis `EO` zur Verfügung stellt, ohne dass der Anwender das Adapter-Signal manuell aufspalten und prüfen muss.