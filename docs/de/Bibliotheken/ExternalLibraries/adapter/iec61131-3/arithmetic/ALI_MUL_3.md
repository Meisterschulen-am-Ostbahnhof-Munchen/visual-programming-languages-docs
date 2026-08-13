# ALI_MUL_3


![ALI_MUL_3](./ALI_MUL_3.svg)

*Kein Bild verfügbar. Der Funktionsblock wird grafisch mit drei eingangsseitigen Sockets (IN1, IN2, IN3) und einem ausgangsseitigen Plug (OUT) dargestellt.*

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ALI_MUL_3` ist ein generischer Arithmetik-Baustein für die 4diac-IDE, der zur Multiplikation von drei Eingangswerten dient. Er zeichnet sich dadurch aus, dass die Ein- und Ausgänge nicht über klassische Daten- und Ereignis-Pins, sondern vollständig über unidirektionale Adapter des Typs `ALI` realisiert sind. Dies ermöglicht eine strukturierte, modulare und übersichtliche Kapselung von Signal- und Datenflüssen in IEC 61499-Anwendungen.

## Schnittstellenstruktur

Da dieser Funktionsblock vollständig auf der Adapter-Technologie basiert, besitzt er keine direkten, klassischen Ereignis- oder Datenkanäle auf der Hauptelebene.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (Signalverarbeitung erfolgt über die Adapter).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (Signalweiterleitung erfolgt über den Ausgangs-Adapter).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingänge)**

* **IN1** (Typ: `adapter::types::unidirectional::ALI`): Der erste Faktor (Multiplikand 1) für die arithmetische Multiplikation.
* **IN2** (Typ: `adapter::types::unidirectional::ALI`): Der zweite Faktor (Multiplikand 2) für die arithmetische Multiplikation.
* **IN3** (Typ: `adapter::types::unidirectional::ALI`): Der dritte Faktor (Multiplikand 3) für die arithmetische Multiplikation.

#### **Plugs (Ausgänge)**

* **OUT** (Typ: `adapter::types::unidirectional::ALI`): Das Ergebnis der Multiplikation (Produkt).

---

## Funktionsweise

Die primäre Aufgabe von `ALI_MUL_3` ist die Berechnung des Produkts aus drei Werten:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3}$$

Die Steuerung des Berechnungszeitpunkts und die Übergabe der Werte erfolgen gekapselt über die `ALI`-Adapter. Sobald ein entsprechendes Trigger-Ereignis über die Eingangs-Adapter signalisiert wird, liest der Baustein die Werte aus den Sockets `IN1`, `IN2` und `IN3` aus, berechnet das mathematische Produkt und stellt das Ergebnis am Plug `OUT` bereit, woraufhin ein entsprechendes Ausgangsereignis initiiert wird.

---

## Technische Besonderheiten

* **Generischer Baustein:** Durch das Attribut `GenericClassName` mit dem Wert `'GEN_ALI_MUL'` ist der Funktionsblock datentypunabhängig konzipiert. Er kann (je nach Ausprägung des verwendeten `ALI`-Adapters) für verschiedene numerische Datentypen (z. B. `INT`, `REAL`, `LREAL`) eingesetzt werden.
* **Sauberes Design:** Die Verwendung von Adaptern reduziert den Verdrahtungsaufwand im Funktionsplan (FBD) erheblich, da Kontroll- und Datenfluss in einer einzigen Verbindung gebündelt werden.
* **Unidirektionale Adapter:** Da es sich um das Paket `adapter::types::unidirectional` handelt, fließen Daten und Trigger gerichtet von den Sockets (`IN1`-`IN3`) zum Plug (`OUT`).

---

## Zustandsübersicht

Der Funktionsblock verhält sich wie ein klassischer, zustandsloser mathematischer Operator (kombinatorisches Verhalten):
* **Bereitschaft:** Der Baustein wartet auf eingehende Aktualisierungsereignisse an den Adaptern `IN1`, `IN2` oder `IN3`.
* **Berechnung:** Bei Triggerung wird die Multiplikation ausgeführt.
* **Ausgabe:** Das Ergebnis wird direkt an den Ausgang `OUT` übergeben und der nachfolgende Baustein getriggert.

---

## Anwendungsszenarien

* **Berechnung physikalischer Größen:** Bestimmung von Volumina (Länge $\times$ Breite $\times$ Höhe) oder dreidimensionalen Skalierungen in der Fabrikautomatisierung.
* **Kaskadierte Verstärkungsfaktoren:** Multiplikation von drei verschiedenen Gain-Faktoren oder Korrekturwerten in Regelungskreisen (z. B. Sensorwert $\times$ Kalibrierfaktor $\times$ Skalierungsfaktor).
* **Signalverarbeitung:** Kombination mehrerer Gewichtungsfaktoren in der Prozessüberwachung.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-`MUL`-Baustein der IEC 61131-3:
* **Klassischer `MUL`-Block:** Benötigt explizite `REQ`- und `CNF`-Ereignisse sowie einzelne Daten-Pins für jeden Operanden. Das führt bei mehreren Eingängen schnell zu unübersichtlichen Plänen.
* **`ALI_MUL_3`:** Bündelt die Schnittstellen in vier übersichtliche Adapter-Anschlüsse. Zudem ist er fest auf genau drei Eingänge ausgelegt, was eine Zwischenstufe (Kaskadierung von zwei 2-fach Multiplizierern) einspart.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALI_MUL_3` ist ein moderner und hocheffizienter Funktionsblock für mathematische Operationen in der 4diac-Umgebung. Durch die konsequente Nutzung von unidirektionalen Adaptern fördert er ein sauberes, modularisiertes Softwaredesign und eignet sich hervorragend für komplexe Berechnungen mit drei Eingangsvariablen.