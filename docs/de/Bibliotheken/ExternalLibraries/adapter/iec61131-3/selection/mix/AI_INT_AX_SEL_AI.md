# AI_INT_AX_SEL_AI


![AI_INT_AX_SEL_AI](./AI_INT_AX_SEL_AI.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AI_INT_AX_SEL_AI` dient der binären Auswahl (Selektion) zwischen zwei analogen Ganzzahl-Eingangswerten (Typ `INT`). Der Baustein kombiniert dabei klassische Steuerungsschnittstellen (direkte Ereignis- und Dateneingänge) mit modernen, adapterbasierten Verbindungskonzepten. Die Auswahl, welcher der beiden Werte an den Ausgang weitergeleitet wird, erfolgt über ein binäres Auswahlsignal an einer dedizierten Adapter-Schnittstelle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Löst die Aktualisierung und Übernahme des direkt anliegenden Daten-Eingangswerts `IN1` aus.

### **Ereignis-Ausgänge**

*   *(Keine direkten Ereignis-Ausgänge deklariert; die Ereignisweiterleitung erfolgt gekapselt über den Adapter-Ausgang `OUT`)*

### **Daten-Eingänge**

*   **IN1** (`INT`): Direkt anliegender, auswählbarer Ganzzahl-Eingangswert (wird an den Ausgang durchgeschaltet, wenn das Auswahlsignal `G` aktiv/`TRUE` ist).

### **Daten-Ausgänge**

*   *(Keine direkten Daten-Ausgänge deklariert; die Datenausgabe erfolgt gekapselt über den Adapter-Ausgang `OUT`)*

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AI`): Der ausgewählte Ausgangsanschluss (Analog Output). Über diesen Adapter werden der selektierte Datenwert und das dazugehörige Aktualisierungsereignis ausgegeben.
*   **IN0** (Socket, Typ: `adapter::types::unidirectional::AI`): Der erste auswählbare Eingangskanal (wird an den Ausgang durchgeschaltet, wenn das Auswahlsignal `G` inaktiv/`FALSE` ist).
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Eingang (Analog Selector). Steuert, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang `OUT` geschaltet wird.

---

## Funktionsweise

Der Baustein ist intern als Composite-Funktionsbaustein (FB-Netzwerk) realisiert. Die Kernlogik basiert auf dem Standard-Auswahlglied `F_SEL` nach IEC 61131-3.

1.  **Datenerfassung und Synchronisation**:
    Sobald an einer der Schnittstellen (`IN0`, `IN1` via `EI1` oder am Selektor `G`) ein neues Ereignis eintrifft, wird der entsprechende Datenwert über flankengetriggerte Speicherglieder (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert und mittels Datenkonverter (`F_MOVE`) an den zentralen Auswahlbaustein `F_SEL` übergeben.
2.  **Selektionslogik**:
    Der Zustand des Selektors `G` steuert den Durchgang:
    *   Ist das Signal am Adapter `G` gleich `FALSE` (0), wird der Wert von `IN0` an den Ausgang `OUT` durchgereicht.
    *   Ist das Signal am Adapter `G` gleich `TRUE` (1), wird der Wert des Direkteingangs `IN1` an den Ausgang `OUT` durchgereicht.
3.  **Ausgabe**:
    Der selektierte Wert wird an den Ausgangs-Plug `OUT` übergeben, gefolgt von einem synchronen Ausgangsereignis (`OUT.E1`), um nachfolgende Programmteile über die Datenaktualisierung zu informieren.

---

## Technische Besonderheiten

*   **Hybrides Design**: Der Baustein ermöglicht eine elegante Brücke zwischen klassischen IEC 61499-Anschlüssen (`IN1`/`EI1`) und strukturierten Adaptern (`IN0`, `G`, `OUT`). Dies erleichtert die Integration in bestehende Applikationen, die verschiedene Signalstandards nutzen.
*   **Ereignisgesteuerte Verarbeitung**: Es findet keine zyklische Verarbeitung statt. Der Baustein reagiert ausschließlich auf Wertänderungen bzw. Ereignisse an den Eingängen, was die Systemressourcen schont und für deterministische Reaktionszeiten sorgt.

---

## Zustandsübersicht

Da es sich um ein reines Datenfluss- und Selektionsnetzwerk (Composite-FB) handelt, besitzt der Baustein keinen eigenen Execution Control Chart (ECC). Der Zustand des Bausteins ist rein kombinatorisch und wird direkt durch den Zustand der Eingänge und der internen Speicherglieder (Flip-Flops) bestimmt.

---

## Anwendungsszenarien

*   **Hand-/Automatik-Umschaltung**: Übernahme eines Sensorsignals im Normalbetrieb (`IN0` via Adapter) oder Aufschalten eines manuell vorgegebenen Festwerts (`IN1`) über eine Steuerungsvorgabe an Adapter `G`.
*   **Sensorredundanz / Signal-Fallback**: Umschaltung auf einen Ersatzwert (`IN1`), falls der Hauptsensor (`IN0`) einen Fehler meldet (Auswertung der Fehlerbedingung erfolgt extern und steuert `G` an).

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard `F_SEL`**: Der Standard-Auswahlbaustein arbeitet rein datenbasiert ohne Adapterunterstützung und ohne ereignisgesteuerte Speicherung. `AI_INT_AX_SEL_AI` erweitert diese Funktionalität um die direkte Integration in adapterbasierte Kommunikationsstrukturen und sorgt für die nötige Event-Synchronisation in IEC 61499-Systemen.

---

## Fazit

Der `AI_INT_AX_SEL_AI` ist ein robuster und flexibler Hilfsbaustein für die Signalvorverarbeitung. Er eignet sich hervorragend für modulare Steuerungsarchitekturen, bei denen analoge Ganzzahlwerte basierend auf logischen Bedingungen dynamisch und ereignisgesteuert umgeschaltet werden müssen.