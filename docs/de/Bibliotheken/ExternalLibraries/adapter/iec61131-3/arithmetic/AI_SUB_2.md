# AI_SUB_2


![AI_SUB_2](./AI_SUB_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AI_SUB_2` ist ein generischer, arithmetischer Funktionsbaustein zur Durchführung einer Subtraktion. Er ist speziell für den Einsatz mit analogen Schnittstellen-Adaptern konzipiert. Der Baustein berechnet die Differenz zwischen zwei analogen Eingangswerten und stellt das Ergebnis an einem analogen Ausgangs-Adapter zur Verfügung. Durch die Verwendung von Adaptern wird das Schnittstellendesign in der 4diac-ide übersichtlich gehalten.

## Schnittstellenstruktur

Da dieser Funktionsbaustein vollständig auf einer Adapter-Architektur basiert, besitzt er keine direkten, klassischen Ereignis- oder Datenkanäle auf der Bausteinoberfläche. Die gesamte Kommunikation wird über die Adapter abgewickelt.

### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge vorhanden (die Ereignissteuerung ist in den Adaptern gekapselt).*

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden (die Ereignissteuerung ist in den Adaptern gekapselt).*

### **Daten-Eingänge**
*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### Sockets (Eingangs-Adapter)
*   **IN1** (Typ: `adapter::types::unidirectional::AI`): Der erste analoge Eingangswert (Minuend) für die Subtraktionsoperation.
*   **IN2** (Typ: `adapter::types::unidirectional::AI`): Der zweite analoge Eingangswert (Subtrahend), der von `IN1` abgezogen wird.

#### Plugs (Ausgangs-Adapter)
*   **OUT** (Typ: `adapter::types::unidirectional::AI`): Das Ergebnis der Subtraktion (Differenz: `IN1 - IN2`).

## Funktionsweise

Der Baustein führt die grundlegende arithmetische Subtraktion aus:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

Sobald sich die Eingangswerte an den Sockets `IN1` oder `IN2` ändern bzw. ein entsprechendes Aktualisierungsereignis über die Adapter empfangen wird, berechnet der Baustein intern die Differenz. Das Ergebnis sowie das zugehörige Aktualisierungsereignis werden unmittelbar an den Ausgangs-Plug `OUT` weitergeleitet.

## Technische Besonderheiten

*   **Generischer Bausteintyp (`GEN_AI_SUB`)**: Der Baustein ist intern als generischer Typ definiert. Dies ermöglicht eine flexible Anpassung an die im System verwendeten analogen Datentypen der Adapter.
*   **Adapter-Kapselung**: Die Verwendung von unidirektionalen analogen Adaptern (`unidirectional::AI`) bündelt Daten- und Eventleitungen. Dies minimiert den Verdrahtungsaufwand im FBD (Function Block Diagram) und erhöht die Übersichtlichkeit signifikant.

## Zustandsübersicht

Der Baustein verhält sich wie ein rein funktionaler Baustein ohne internen Speicher (analog zu einem klassisch kombinatorischen Gatter). Er besitzt keine komplexe Execution Control Chart (ECC). Jede Aktivität an den Eingangs-Adaptern triggert direkt die Berechnung und aktualisiert den Ausgangs-Adapter.

## Anwendungsszenarien

*   **Differenzdruck- und Differenztemperaturmessung**: Berechnung von physikalischen Differenzwerten in der Prozesstechnik (z. B. Ermittlung des Druckabfalls über einem Filter oder der Temperaturdifferenz zwischen Vor- und Rücklauf).
*   **Regelungsabweichung**: Berechnung der Regelabweichung ($e = w - x$) in Regelungskreisen, bei denen Soll- und Istwert als Adapterstrukturen vorliegen.
*   **Nullpunktkorrektur / Offset-Abzug**: Subtraktion eines Kalibrier- oder Offset-Wertes von einem kontinuierlichen Messsignal.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu Standard-Subtraktionsbausteinen der IEC 61131-3 (wie z. B. einem klassischen `SUB`-Baustein mit diskreten Pins) entfällt beim `AI_SUB_2` das manuelle Verdrahten von separaten `REQ`- und `CNF`-Eventleitungen sowie einzelnen analogen Datenleitungen. Alle relevanten Informationen werden sauber in den `AI`-Adaptern übertragen.

## Fazit

Der `AI_SUB_2` ist ein spezialisierter und hocheffizienter Baustein für die moderne, adapterbasierte Programmierung in 4diac. Er eignet sich hervorragend für saubere Softwarearchitekturen im Bereich der analogen Signalvorverarbeitung, bei denen Übersichtlichkeit und Kapselung im Vordergrund stehen.