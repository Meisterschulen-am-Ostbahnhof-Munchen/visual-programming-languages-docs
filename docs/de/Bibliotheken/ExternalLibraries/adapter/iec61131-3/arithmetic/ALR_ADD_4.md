# ALR_ADD_4


![ALR_ADD_4](./ALR_ADD_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein (FB) **ALR_ADD_4** ist ein generischer arithmetischer Baustein zur Durchführung einer Additionsoperation. Er ist gemäß dem Standard IEC 61131-3 als Standard-Arithmetikfunktion klassifiziert. Der Baustein ermöglicht es, bis zu vier Eingangswerte, die über unidirektionale Adapter vom Typ `ALR` bereitgestellt werden, zu addieren und das Ergebnis an einen entsprechenden Ausgangsadapter zu übergeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Synchronisation und Ereignissteuerung erfolgt implizit über die verwendeten Adapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Weiterleitung von Ereignissen erfolgt implizit über den Ausgangsadapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt vollständig über die Adapter-Schnittstellen.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden. Die Datenübergabe erfolgt vollständig über die Adapter-Schnittstelle.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::ALR`): Erster Eingangswert (Summand 1) für die Addition.
-   **IN2** (Typ: `adapter::types::unidirectional::ALR`): Zweiter Eingangswert (Summand 2) für die Addition.
-   **IN3** (Typ: `adapter::types::unidirectional::ALR`): Dritter Eingangswert (Summand 3) für die Addition.
-   **IN4** (Typ: `adapter::types::unidirectional::ALR`): Vierter Eingangswert (Summand 4) für die Addition.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::ALR`): Das berechnete Ergebnis der Addition (Summe).

## Funktionsweise

Der Baustein `ALR_ADD_4` arbeitet intern als generischer Addierer (`GEN_ALR_ADD`). Sobald sich die Werte an den Eingangs-Adaptern `IN1` bis `IN4` ändern, berechnet der Baustein die Summe der anliegenden Werte:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

Das Ergebnis wird unmittelbar an den Ausgangs-Plug `OUT` übergeben. Da es sich um eine generische Implementierung handelt, hängt der konkrete Datentyp von der Spezifikation des verwendeten `ALR`-Adaptertyps ab.

## Technische Besonderheiten

-   **Generische Klasse:** Der Baustein ist über das Attribut `GenericClassName` mit dem Wert `'GEN_ALR_ADD'` verknüpft, was ihm eine hohe Flexibilität bei der Verarbeitung verschiedener kompatibler Datentypen innerhalb der Adapterstrukturen verleiht.
-   **Adapterbasierte Kopplung:** Durch die ausschließliche Nutzung von Adaptern wird die Anzahl der Verbindungslinien in der 4diac-IDE drastisch reduziert, was zu übersichtlicheren Applikationsdiagrammen führt.

## Zustandsübersicht

Da dieser Funktionsbaustein eine rein kombinatorische, mathematische Operation abbildet, besitzt er keine interne Zustandsmaschine (Execution Control Chart, ECC). Der Ausgang folgt direkt den Änderungen der Eingänge.

## Anwendungsszenarien

-   **Messwert-Aggregation:** Aufsummierung von bis zu vier Energie-, Durchfluss- oder Leistungswerten, die über standardisierte unidirektionale Adapter übertragen werden.
-   **Signalzusammenführung:** Strukturierte Bündelung von Sensorsignalen in komplexen Steuerungsarchitekturen vor der weiteren Datenverarbeitung.

## Vergleich mit ähnlichen Bausteinen

-   **Standard-ADD-Baustein:** Ein klassischer IEC 61131-3 `ADD`-Baustein nutzt direkte Dateneingänge (z. B. `REAL`, `INT`) und benötigt oft explizite Event-Verbindungen (`REQ` / `CNF`). `ALR_ADD_4` kapselt diese Daten und Events in Adaptern, was die Projektierung vereinfacht.
-   **Zwei-Wege-Addierer (z.B. ALR_ADD_2):** Bietet nur zwei Eingänge. `ALR_ADD_4` spart bei der Summierung von drei oder vier Werten das Kaskadieren mehrerer kleinerer Addierer-Bausteine ein.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALR_ADD_4`-Baustein ist eine effiziente und saubere Lösung für arithmetische Additionen in komponenten- und adapterbasierten Systemarchitekturen innerhalb von 4diac. Er fördert die Wiederverwendbarkeit und sorgt für ein aufgeräumtes Systemdesign.
