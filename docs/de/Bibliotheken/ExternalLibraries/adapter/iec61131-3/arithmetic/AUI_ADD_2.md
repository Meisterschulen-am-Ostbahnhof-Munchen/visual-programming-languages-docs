# AUI_ADD_2


![AUI_ADD_2](./AUI_ADD_2.svg)

*Keine Abbildung verfügbar*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_ADD_2` ist ein generischer Funktionsbaustein (Generic FB), der für die Durchführung einer arithmetischen Addition entwickelt wurde. Er nutzt unidirektionale Adapter vom Typ `AUI` (Adapter Unidirectional Interface), um zwei Eingangswerte zu addieren und das Ergebnis auszugeben. Da es sich um einen generischen Baustein handelt, der auf der Klasse `GEN_AUI_ADD` basiert, kann er flexibel für verschiedene Datentypen eingesetzt werden, die von den entsprechenden Adaptern unterstützt werden.

## Schnittstellenstruktur

Da dieser Funktionsbaustein vollständig auf Adaptern basiert, besitzt er keine direkten, diskreten Daten- oder Ereigniskanäle auf der obersten Ebene. Die gesamte Kommunikation und Steuerung wird über die Adapter-Schnittstellen abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (die Steuerung erfolgt über die angebundenen Adapter).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (die Weiterleitung erfolgt über die angebundenen Adapter).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

* **Sockets (Eingangs-Adapter):**
  * **IN1** (Typ: `adapter::types::unidirectional::AUI`): Erster Eingang (Summand) für die arithmetische Addition.
  * **IN2** (Typ: `adapter::types::unidirectional::AUI`): Zweiter Eingang (Summand) für die arithmetische Addition.
* **Plugs (Ausgangs-Adapter):**
  * **OUT** (Typ: `adapter::types::unidirectional::AUI`): Ausgang für das Ergebnis der Addition (`IN1 + IN2`).

## Funktionsweise

Sobald an den Eingangsadaptern `IN1` und `IN2` Werte anliegen bzw. ein entsprechendes Aktualisierungsereignis über die Adapter getriggert wird, führt der Baustein die Addition aus. 
Die mathematische Operation lautet:
$$\text{OUT} = \text{IN1} + \text{IN2}$$
Das Ergebnis sowie das zugehörige Ausgangsereignis werden unmittelbar über den Ausgangsadapter `OUT` an die nachfolgenden Bausteine weitergegeben.

Durch die Definition als generischer Baustein (`GEN_AUI_ADD`) passt sich die interne Additionslogik dynamisch an die Datentypen der verbundenen Adapter an (z. B. Ganzzahl- oder Gleitkomma-Typen).

## Technische Besonderheiten

* **Generisches Design:** Der Baustein ist über das Attribut `eclipse4diac::core::GenericClassName` als `GEN_AUI_ADD` klassifiziert. Dies ermöglicht eine hohe Wiederverwendbarkeit für unterschiedliche numerische Datentypen.
* **Kapselung durch Adapter:** Die Verwendung des unidirektionalen Adapters `AUI` sorgt für ein sehr aufgeräumtes Design im 4diac-Application-Editor, da Ereignis- und Datenflüsse in einer einzigen Verbindung gebündelt sind.
* **Unidirektionaler Fluss:** Die Schnittstellen sind als rein unidirektionale Verbindungen konzipiert, was eine klare Richtung des Signal- und Datenflusses von den Sockets (`IN1`, `IN2`) zum Plug (`OUT`) vorgibt.

## Zustandsübersicht

Der Baustein besitzt keinen komplexen internen Zustandsautomaten (ECC). Die Verarbeitung erfolgt ereignisgesteuert und zustandslos (kombinatorisch) basierend auf den über die Adapter eingehenden Triggern.

## Anwendungsszenarien

* **Signal-Addition:** Zusammenführen von zwei Sensorwerten (z. B. zur Berechnung eines Gesamtvolumenstroms aus zwei einzelnen Durchflussmessern).
* **Sollwert-Offset:** Aufschalten eines konstanten oder variablen Korrekturwertes (Offsets) auf einen bestehenden Steuerungsparameter.
* **Strukturierte Signalverarbeitung:** Einsatz in komplexeren Regelkreisen innerhalb von IEC 61499, bei denen ein sauberer, adapterbasierter Verdrahtungsstil bevorzugt wird.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu Standard-Additionsbausteinen der IEC 61131-3 (wie z. B. einem klassischen `ADD`-Baustein mit diskreten Eingängen) entfällt beim `AUI_ADD_2` das separate Verdrahten von REQ/CNF-Ereignissen und den eigentlichen Datenleitungen. Dies reduziert die Fehleranfälligkeit bei der manuellen Erstellung von Event-Daten-Assoziationen (With-Verbindungen).

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUI_ADD_2` ist ein hocheffizienter, modularer Baustein für die mathematische Addition in modernen IEC 61499-Systemen. Durch den konsequenten Einsatz von Adaptern fördert er ein übersichtliches, fehlerresistentes und gut wartbares Anwendungsdesign in der 4diac-IDE.