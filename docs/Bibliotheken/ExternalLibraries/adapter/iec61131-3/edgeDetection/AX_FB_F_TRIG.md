# AX_FB_F_TRIG


![AX_FB_F_TRIG](.././AX_FB_F_TRIG.svg)

*Hier Platzhalter für das Bild des Funktionsblocks einfügen, falls vorhanden*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_FB_F_TRIG** (Falling Edge Trigger mit AX-Adapter) dient zur Erkennung einer fallenden Flanke (Signalwechsel von TRUE auf FALSE) innerhalb einer adapterbasierten Architektur. Er implementiert die Logik eines Standard-IEC 61131-3 `F_TRIG`-Bausteins, nutzt jedoch **AX-Adapter** zur Kapselung von Daten- und Ereignissignalen, um die Verdrahtungskomplexität in IEC 61499-Anwendungen zu reduzieren.

## Schnittstellenstruktur

Der Baustein verzichtet auf klassische separate Ereignis- und Daten-Pins und nutzt stattdessen Adapter-Schnittstellen.

### **Ereignis-Eingänge**
*   *Keine direkten Ereignis-Eingänge (gekapselt im Adapter `CLK`).*

### **Ereignis-Ausgänge**
*   *Keine direkten Ereignis-Ausgänge (gekapselt im Adapter `Q`).*

### **Daten-Eingänge**
*   *Keine direkten Daten-Eingänge (gekapselt im Adapter `CLK`).*

### **Daten-Ausgänge**
*   *Keine direkten Daten-Ausgänge (gekapselt im Adapter `Q`).*

### **Adapter**

| Name | Typ | Komment | Beschreibung |
| :--- | :--- | :--- | :--- |
| **CLK** | `adapter::types::unidirectional::AX` | Clock | **Socket (Eingang):** Der Eingangsadapter, der das zu überwachende Signal liefert. Enthält typischerweise ein Ereignis (`E1`) und einen Booleschen Datenwert (`D1`). |
| **Q** | `adapter::types::unidirectional::AX` | Output | **Plug (Ausgang):** Der Ausgangsadapter, der das Ergebnis der Flankenerkennung sendet. |

## Funktionsweise

Der Baustein überwacht den logischen Zustand des Dateneingangs im Adapter `CLK` (Feld `D1`). Bei jedem Ereignis am Eingang `CLK` (`E1`) wird der Algorithmus ausgeführt:

1.  Der Baustein prüft, ob ein Wechsel von **TRUE** (High) auf **FALSE** (Low) stattgefunden hat.
2.  Dazu wird ein interner Speicher (`MEM`) genutzt, der den invertierten Zustand des letzten Zyklus speichert.
3.  Die Logik lautet: `Q.D1 := NOT CLK.D1 AND NOT MEM`.
4.  Der Speicher wird aktualisiert: `MEM := NOT CLK.D1`.

**Verhalten:**
*   Wenn das Eingangssignal von 1 auf 0 wechselt, wird der Ausgang `Q.D1` für genau einen Zyklus auf TRUE gesetzt.
*   In allen anderen Fällen (0->0, 0->1, 1->1) bleibt der Ausgang FALSE.
*   Das Ergebnis wird über das Ereignis `Q.E1` signalisiert.

## Technische Besonderheiten

*   **Adapter-Technologie:** Durch die Verwendung des `AX`-Adapters (allgemeiner Datentyp, hier boolesch interpretiert) werden Ereignisfluss und Datenfluss gebündelt. Dies führt zu übersichtlicheren Funktionsplan-Diagrammen.
*   **Interne Speicherung:** Der Baustein besitzt eine interne Variable `MEM` (Initialwert TRUE), um den vorherigen Zustand des Eingangssignals zu referenzieren.
*   **Minimalistisches ECC:** Die Zustandsmaschine (ECC) besteht nur aus einem einzigen Zustand, was eine sehr schnelle und direkte Abarbeitung des Algorithmus gewährleistet.

## Zustandsübersicht

Die Execution Control Chart (ECC) des Bausteins ist sehr einfach gehalten:

*   **REQ (Zustand):** Dies ist der einzige Zustand.
    *   **Transition:** Er wird durch das Ereignis `CLK.E1` (vom Eingangsadapter) ausgelöst.
    *   **Aktion:** Führt den Algorithmus `REQ` aus und triggert anschließend das Ausgabeereignis `Q.E1`.

## Anwendungsszenarien

Der **AX_FB_F_TRIG** eignet sich für diverse Steuerungsaufgaben, bei denen das "Abschalten" oder "Loslassen" erkannt werden muss:

*   **Taster-Auswertung:** Erkennen, wann ein Taster losgelassen wird (negative Flanke).
*   **Sensorik:** Auslösen einer Aktion, wenn ein Werkstück einen Sensorbereich verlässt (Lichtschranke wird frei).
*   **Alarm-Rücksetzung:** Erkennung, wenn ein Fehlersignal nicht mehr anliegt.
*   **Strukturierte Programmierung:** Einsatz in komplexen Anwendungen, die intensiv auf Adapter setzen, um "Spaghetti-Code" (viele einzelne Verbindungslinien) zu vermeiden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
| :--- | :--- |
| **F_TRIG** (Standard) | Nutzt separate `CLK` (BOOL) und `Q` (BOOL) Pins sowie separate `REQ`/`CNF` Ereignisse. Funktional identisch, aber andere Schnittstelle. |
| **AX_FB_R_TRIG** | Das Gegenstück zu diesem Baustein. Es erkennt die **steigende** Flanke (Rising Edge, 0 auf 1). |
| **E_F_TRIG** | Ereignisbasierter Trigger in IEC 61499, arbeitet oft rein auf Ereignisebene ohne gekapselte Datenadapter. |

## Fazit

Der **AX_FB_F_TRIG** ist ein essenzieller Baustein für Entwickler, die innerhalb der 4diac IDE und IEC 61499 auf adapterbasierte Designs setzen. Er bietet die verlässliche Funktionalität der klassischen Flankenerkennung, verpackt in einer modernen, verbindungssparenden Schnittstelle.