# ADI_DIV_2


![ADI_DIV_2](./ADI_DIV_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ADI_DIV_2` dient zur Durchführung einer arithmetischen Division (DIV) von zwei Eingangswerten über Adapterverbindungen. Es handelt sich hierbei um einen generischen Funktionsbaustein (Generic FB), der auf dem Typ `GEN_ADI_DIV` basiert. Durch die konsequente Nutzung von unidirektionalen Adaptern des Typs `ADI` wird eine saubere Kapselung von Daten und Ereignissen erreicht. Dies vereinfacht das Applikationsdesign in der 4diac-IDE, da die Anzahl der sichtbaren Verbindungslinien signifikant reduziert wird.

## Schnittstellenstruktur

Da dieser Funktionsbaustein vollständig adapterbasiert arbeitet, verfügt er auf der obersten Ebene nicht über klassische, diskrete Ereignis- oder Datenanschlüsse. Die gesamte Interaktion findet über die Adapter-Schnittstellen statt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird über die Eingangs-Adapter (`IN1`, `IN2`) abgewickelt.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe wird über den Ausgangs-Adapter (`OUT`) abgewickelt.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

-   **Sockets (Eingangs-Adapter):**
    -   **`IN1`** (Typ: `adapter::types::unidirectional::ADI`): Erster Eingangswert (Dividend / Zähler) für die Division.
    -   **`IN2`** (Typ: `adapter::types::unidirectional::ADI`): Zweiter Eingangswert (Divisor / Nenner) für die Division.
-   **Plugs (Ausgangs-Adapter):**
    -   **`OUT`** (Typ: `adapter::types::unidirectional::ADI`): Das berechnete Ergebnis (Quotient) der Division.

## Funktionsweise

Der Baustein dividiert den über den Adapter `IN1` empfangenen Wert durch den über den Adapter `IN2` empfangenen Wert:

$$\text{Ergebnis (OUT)} = \frac{\text{Wert von IN1}}{\text{Wert von IN2}}$$

Die Berechnung wird getriggert, sobald an den Eingangs-Adaptern entsprechende Aktualisierungsereignisse eingehen. Nach erfolgreicher Berechnung wird der neue Quotient zusammen mit einem Ausgangsereignis über den Adapter `OUT` weitergegeben. Aufgrund der generischen Natur des Bausteins (`GEN_ADI_DIV`) passt sich das Verhalten an die zugrunde liegenden Datentypen der genutzten `ADI`-Adapter an.

## Technische Besonderheiten

-   **Generische Instanziierung:** Der Baustein nutzt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_ADI_DIV'`. Dies erlaubt eine flexible Typisierung je nach verwendetem Adaptersubtyp zur Laufzeit.
-   **Kapselung durch Adapter:** Daten und die dazugehörigen Trigger-Ereignisse sind im Adaptertyp `ADI` gebündelt, was eine lose Kopplung der Softwarekomponenten begünstigt.
-   **Division durch Null:** Bei der Implementierung und Anwendung muss darauf geachtet werden, dass der Wert am Adapter `IN2` (Divisor) ungleich Null ist. Eine Division durch Null muss anwendungsorientiert vor dem Baustein abgefangen werden, um Laufzeitfehler zu vermeiden.

## Zustandsübersicht

Der Funktionsbaustein verhält sich zustandslos (bzw. rein reaktiv):

1.  **Wartezustand:** Der Baustein wartet auf Ereignisse an den Sockets `IN1` oder `IN2`.
2.  **Berechnung:** Nach Erhalt gültiger Daten/Ereignisse an den Eingängen wird die Division ausgeführt.
3.  **Aktualisierung:** Das Ergebnis wird an den Ausgangs-Plug `OUT` übergeben und das dortige Sende-Ereignis ausgelöst.

## Anwendungsszenarien

-   **Messwertskalierung:** Normierung von analogen Sensorwerten (z. B. Division eines Rohwerts durch einen Skalierungsfaktor).
-   **Berechnung von Verhältnissen:** Bestimmung von Mischungsverhältnissen oder Prozentwerten in verfahrenstechnischen Anlagen.
-   **Mittelwertberechnungen:** Division einer Summe durch die Anzahl der erfassten Werte in einfachen mathematischen Berechnungsnetzwerken.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen, standardmäßigen `DIV`-Funktionsbaustein (nach IEC 61131-3), der mit diskreten Daten-Pins (`IN1`, `IN2`, `OUT`) und expliziten Event-Pins (`REQ`, `CNF`) arbeitet:

-   **Vorteile von `ADI_DIV_2`:** Deutlich aufgeräumteres Erscheinungsbild im Funktionsplan (FBD) von 4diac. Datenkonsistenz wird durch die Kopplung im Adapter direkt erzwungen.
-   **Nachteile:** Ein direkter Einsatz mit Standard-Datenströmen ohne Adapter-Kapselung ist nicht möglich. Es müssen dedizierte Konverterbausteine verwendet werden, falls die Signalquelle keine Adapter unterstützt.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

`ADI_DIV_2` ist ein spezialisierter und effizienter Baustein für moderne IEC 61499 Architekturen innerhalb von 4diac. Er eignet sich hervorragend für Entwickler, die auf eine saubere, adapterbasierte und modulare Softwarearchitektur setzen und mathematische Divisionen übersichtlich implementieren möchten.
