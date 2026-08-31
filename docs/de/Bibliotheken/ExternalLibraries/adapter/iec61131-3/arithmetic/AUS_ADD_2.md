# AUS_ADD_2


![AUS_ADD_2](./AUS_ADD_2.svg)

*(Grafische Darstellung des Funktionsblocks nicht verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUS_ADD_2` ist ein generischer Baustein (Generic FB) zur Durchführung einer arithmetischen Addition. Er dient dazu, zwei Eingangssignale zu addieren und das Ergebnis auszugeben. Die Besonderheit dieses Bausteins liegt in der Verwendung von standardisierten, unidirektionalen Adaptern (`AUS`), wodurch die Signal- und Datenverdrahtung innerhalb von Eclipse 4diac stark vereinfacht und gekapselt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignissteuerung wird über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge.*

### **Adapter**

#### **Sockets (Eingangs-Adapter / Buchsen)**

- **IN1** (Typ: `adapter::types::unidirectional::AUS`): Der erste Summand der Addition.
- **IN2** (Typ: `adapter::types::unidirectional::AUS`): Der zweite Summand der Addition.

#### **Plugs (Ausgangs-Adapter / Stecker)**

- **OUT** (Typ: `adapter::types::unidirectional::AUS`): Das Ergebnis der Addition (Summe aus `IN1` und `IN2`).

---

## Funktionsweise

Der Baustein `AUS_ADD_2` arbeitet als arithmetischer Addierer auf Basis von Adaptern. Sobald an den Eingangs-Adaptern `IN1` oder `IN2` ein neues Ereignis samt Datenwert ankommt, führt der Baustein die Addition der beiden Werte durch:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

Das Ergebnis wird zusammen mit dem entsprechenden Trigger-Ereignis über den Ausgangs-Adapter `OUT` ausgegeben. Da es sich um unidirektionale Adapter handelt, fließt der Daten- und Kontrollfluss ausschließlich von den Eingängen zum Ausgang.

---

## Technische Besonderheiten

- **Generischer Baustein:** Durch das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AUS_ADD'` ist der Baustein als generischer Typ definiert. Dies ermöglicht eine flexible Anpassung an unterschiedliche Datentypen, die durch die Adapterstrukturen definiert werden.
- **Kapselung:** Durch die Verwendung von Adaptern anstelle von einzelnen Event- und Data-Pins wird das Systemdesign übersichtlicher und weniger fehleranfällig für Verdrahtungsfehler.

---

## Zustandsübersicht

Da es sich bei diesem Baustein im Wesentlichen um eine mathematische Verknüpfung handelt, besitzt er kein komplexes internes Zustandsdiagramm (ECC). Er reagiert ereignisgesteuert auf eintreffende Daten an den Adaptern `IN1` und `IN2`, berechnet die Summe und leitet das Ergebnis direkt an `OUT` weiter.

---

## Anwendungsszenarien

- **Messwertverarbeitung:** Addition von zwei Sensorwerten oder die Beaufschlagung eines Messwerts mit einem Offset, der über einen Adapter eingespeist wird.
- **Sollwertberechnung:** Zusammenführung von Basis-Sollwerten und Korrekturwerten in der Prozessautomatisierung.
- **Strukturierte Programmierung:** Einsatz in komplexen Steuerungen, bei denen Daten- und Eventleitungen zur Erhöhung der Übersichtlichkeit in Adaptern gebündelt sind.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Addition-Baustein (wie z. B. `ADD` aus der IEC 61131-3 Bibliothek), welcher diskrete Daten- und Ereignis-Pins (wie `REQ`, `CNF`, `IN1`, `IN2`, `OUT`) besitzt, kapselt `AUS_ADD_2` diese Schnittstellen vollständig in Adaptern. Dies reduziert die Anzahl der sichtbaren Verbindungslinien im 4diac-Editor drastisch und fördert ein objektorientiertes Design.

---

- **[`AUS_ADD_2_UNGATED`](AUS_ADD_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

`AUS_ADD_2` ist ein effizienter, generischer Hilfsbaustein für die arithmetische Addition in IEC 61499-Anwendungen. Durch die konsequente Nutzung von unidirektionalen Adaptern eignet er sich hervorragend für moderne, modulare Softwarearchitekturen in der industriellen Automatisierungstechnik.
