# AX_FB_SR

[Bild des Funktionsbausteins AX_FB_SR, falls vorhanden]


![AX_FB_SR](.././AX_FB_SR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AX_FB_SR** realisiert ein bistabiles Kippglied (Latch) mit **Setz-Dominanz** (SR-Flip-Flop). Im Gegensatz zu herkömmlichen IEC 61131-3 Bausteinen verwendet dieser FB jedoch keine diskreten Ereignis- und Datenanschlüsse, sondern **Adapter** für die Signalübertragung. Dies ermöglicht eine kompaktere Darstellung und vereinfachte Verdrahtung in komplexen Steuerungsanwendungen, die auf dem Adapter-Konzept basieren.

Der Baustein speichert einen binären Zustand. Wenn sowohl das Setz- (SET) als auch das Rücksetzsignal (RESET) gleichzeitig aktiv sind, hat das Setzsignal Vorrang (Setz-Dominanz).

## Schnittstellenstruktur

Der Baustein kommuniziert ausschließlich über Adapter-Schnittstellen. Klassische diskrete Ein- und Ausgänge sind nicht vorhanden, da diese innerhalb der Adapter gekapselt sind.

### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge vorhanden (diese sind in den Sockets `SET1` und `RESET` enthalten).*

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden (diese sind im Plug `Q1` enthalten).*

### **Daten-Eingänge**
*Keine direkten Daten-Eingänge vorhanden (diese sind in den Sockets `SET1` und `RESET` enthalten).*

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden (diese sind im Plug `Q1` enthalten).*

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Q1** | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Der Ausgangsadapter, der den aktuellen Zustand (Q) und das zugehörige Ereignis bereitstellt. |
| **SET1** | `adapter::types::unidirectional::AX` | Socket (Eingang) | Der Setz-Eingangsadapter. Ein `TRUE`-Signal hier setzt den Ausgang auf `TRUE`. |
| **RESET** | `adapter::types::unidirectional::AX` | Socket (Eingang) | Der Rücksetz-Eingangsadapter. Ein `TRUE`-Signal hier setzt den Ausgang auf `FALSE` (sofern SET1 nicht aktiv ist). |

*Hinweis: Der Adapter-Typ `AX` impliziert typischerweise eine Kombination aus einem booleschen Datenpunkt (`D1`) und einem Ereignis (`E1`).*

## Funktionsweise

Der interne Algorithmus implementiert die Logik eines SR-Flip-Flops mit Vorrang auf Setzen. Die Logik wird ausgeführt, sobald ein Ereignis an einem der Adapter-Eingänge (`SET1.E1` oder `RESET.E1`) empfangen wird.

Die logische Gleichung lautet (in ST-Syntax):
```st
Q1.D1 := SET1.D1 OR ((NOT RESET.D1) AND Q1.D1);
```

Dies bedeutet:
1.  Ist der Dateneingang von **SET1** `TRUE`, wird der Ausgang **Q1** auf `TRUE` gesetzt (unabhängig von RESET).
2.  Ist **SET1** `FALSE` und **RESET** `TRUE`, wird der Ausgang **Q1** auf `FALSE` gesetzt.
3.  Sind beide Eingänge `FALSE`, behält **Q1** seinen vorherigen Zustand bei (Speicherfunktion).

Nach der Berechnung des neuen Zustands wird das Ereignis am Ausgangsadapter (`Q1.E1`) ausgelöst, um nachfolgende Bausteine über die Aktualisierung zu informieren.

## Technische Besonderheiten

*   **Adapter-basiert:** Der Hauptvorteil dieses Bausteins ist die Reduktion von Verbindungslinien im Funktionsplan, da Daten und Ereignisse über eine einzige Adapter-Verbindung gebündelt werden.
*   **Ereignisgesteuert:** Der Baustein reagiert sofort auf eingehende Ereignisse an den `SET1` oder `RESET` Adaptern und leitet das Ergebnis sofort weiter.
*   **Zustandsmaschine (ECC):** Die Execution Control Chart (ECC) ist minimal gehalten. Sie besteht aus einem einzigen Zustand `REQ`, der auf Eingangsereignisse wartet und den Algorithmus `REQ` ausführt.

## Zustandsübersicht

Die folgende Wahrheitstabelle beschreibt das Verhalten des Bausteins (wobei `Q_n` der alte Zustand und `Q_n+1` der neue Zustand ist):

| SET1.D1 | RESET.D1 | Q_n (Alter Zustand) | Q_n+1 (Neuer Zustand) | Beschreibung |
| :---: | :---: | :---: | :---: | :--- |
| 0 | 0 | 0 | 0 | Zustand halten |
| 0 | 0 | 1 | 1 | Zustand halten |
| 0 | 1 | X | 0 | Rücksetzen |
| 1 | 0 | X | 1 | Setzen |
| 1 | 1 | X | 1 | **Setzen (Dominant)** |

## Anwendungsszenarien

*   **Adapter-basierte Steuerungssysteme:** Ideal für Projekte, die konsequent die Adapter-Technologie von 4diac nutzen, um den "Spaghetti-Code" von parallelen Event- und Datenleitungen zu vermeiden.
*   **Start/Stop-Logik:** Realisierung von Maschinensteuerungen, bei denen das "Ein"-Signal (Setzen) Priorität hat oder eine dauerhafte Aktivierung sichergestellt werden muss, solange der Taster gedrückt ist.
*   **Alarm-Handling:** Speichern von Alarmzuständen, die manuell quittiert (zurückgesetzt) werden müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

*   **SR (Standard):** Der `AX_FB_SR` entspricht logisch dem Standard-`SR` Baustein der IEC 61131-3, unterscheidet sich jedoch durch die Nutzung von `AX`-Adaptern anstelle von diskreten `BOOL`- und `EVENT`-Pins.
*   **AX_FB_RS:** Dies ist das Gegenstück mit **Rücksetz-Dominanz**. Beim `AX_FB_RS` würde bei gleichzeitigem Anliegen von SET und RESET der Ausgang auf `FALSE` gehen.
*   **E_SR:** Ein ereignisgesteuertes Standard-SR-Flip-Flop ohne Adapter.

## Fazit

Der **AX_FB_SR** ist ein spezialisierter Baustein für die strukturierte, adapterbasierte Programmierung in 4diac. Er bietet die klassische Funktionalität eines setz-dominanten Speicherglieds, optimiert jedoch die grafische Darstellung und Handhabung durch die Kapselung von Signalen in Adaptern. Er ist unverzichtbar in Anwendungen, die auf modularen und übersichtlichen Schnittstellendefinitionen basieren.