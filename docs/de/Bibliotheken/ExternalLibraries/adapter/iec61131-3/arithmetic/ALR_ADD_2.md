# ALR_ADD_2


![ALR_ADD_2](./ALR_ADD_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ALR_ADD_2` ist ein generischer, arithmetischer Additionsbaustein für die 4diac-IDE, der der Norm IEC 61131-3 entspricht. Er dient dazu, zwei Eingangswerte mathematisch zu addieren. Die Besonderheit dieses Bausteins liegt in der Verwendung von unidirektionalen Adaptern (`ALR`), die sowohl Daten als auch die zugehörige Kontrolllogik kapseln, um eine saubere und modulare Signalverarbeitung zu ermöglichen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Eingänge. Die Ereignissteuerung wird über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Ausgänge. Die Ereignissteuerung wird über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge definiert, da die Datenübergabe vollständig über die Adapter erfolgt.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge definiert, da das Ergebnis über den Ausgangs-Adapter bereitgestellt wird.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

* **IN1** (Typ: `adapter::types::unidirectional::ALR`): Der erste Summand der Additionsoperation.
* **IN2** (Typ: `adapter::types::unidirectional::ALR`): Der zweite Summand der Additionsoperation.

#### **Plugs (Ausgangs-Adapter)**

* **OUT** (Typ: `adapter::types::unidirectional::ALR`): Das Ergebnis der Addition ($OUT = IN1 + IN2$).

---

## Funktionsweise

Der `ALR_ADD_2` liest die Werte über die beiden Eingangs-Adapter `IN1` und `IN2` ein. Sobald ein entsprechendes Ereignis über die Adapter signalisiert, dass neue Daten vorliegen, führt der Baustein die Addition aus:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

Das berechnete Ergebnis wird anschließend über den Ausgangs-Adapter `OUT` zusammen mit dem entsprechenden Ausgangsereignis an nachfolgende Bausteine weitergeleitet. Da es sich um einen generischen Funktionsbaustein (`GEN_ALR_ADD`) handelt, kann er flexibel mit verschiedenen numerischen Datentypen arbeiten, die durch das ALR-Adapter-Interface unterstützt werden.

---

## Technische Besonderheiten

* **Generischer Typ (`GEN_ALR_ADD`):** Der Baustein ist datentypunabhängig implementiert und passt sich den im ALR-Adapter definierten Datentypen an.
* **Adapter-Kapselung:** Durch die Verwendung unidirektionaler Adapter wird die Anzahl der sichtbaren Verbindungen im Control-Flow-Diagramm der 4diac-IDE drastisch reduziert, was die Übersichtlichkeit und Wartbarkeit des Gesamtsystems erhöht.
* **Konformität:** Entspricht den mathematischen Standards nach IEC 61131-3 für Standard-Arithmetikfunktionen.

---

## Zustandsübersicht

Da die Logik dieses Bausteins rein daten- und ereignisgesteuert über die Adapter abläuft, besitzt der Baustein keine komplexe interne Zustandsmaschine (ECC). Er reagiert unmittelbar auf eingehende Datenänderungen/Ereignisse an den Sockets `IN1` und `IN2` und leitet das Ergebnis an den Plug `OUT` weiter.

---

## Anwendungsszenarien

* **Signalzusammenführung:** Addition von zwei analogen Sensorwerten (z. B. Ermittlung eines Gesamtvolumenstroms aus zwei einzelnen Durchflussmessern).
* **Sollwert-Offset-Berechnung:** Beaufschlagung eines Basis-Sollwerts mit einem Korrekturoffset in verfahrenstechnischen Anlagen.
* **Kompakte Programmierung:** Verwendung in komplexen Regelungsschleifen, bei denen ein übersichtliches Routing mittels Adaptern bevorzugt wird.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-`ADD`-Funktionsbaustein (der separate Event-Eingänge wie `REQ`, Event-Ausgänge wie `CNF` sowie klassische Daten-Pins besitzt) verzichtet `ALR_ADD_2` vollständig auf diese klassischen Pins. Er ersetzt sie durch standardisierte `ALR`-Adapter. Dies vereinfacht die Verdrahtung in der 4diac-IDE erheblich, da Event und Daten in einer einzigen Verbindung gebündelt sind.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALR_ADD_2` ist eine moderne und hocheffiziente Variante des klassischen Additionsbausteins. Er eignet sich hervorragend für serviceorientierte Architekturen und verteilte Steuerungssysteme innerhalb der 4diac-Umgebung, bei denen Übersichtlichkeit und standardisierte Adapter-Schnittstellen im Vordergrund stehen.