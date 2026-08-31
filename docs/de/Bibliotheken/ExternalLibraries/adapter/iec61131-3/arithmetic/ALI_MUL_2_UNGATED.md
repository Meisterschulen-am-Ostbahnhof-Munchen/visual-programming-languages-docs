# ALI_MUL_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`ALI_MUL_2`](ALI_MUL_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![ALI_MUL_2_UNGATED](./ALI_MUL_2_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALI_MUL_2_UNGATED` dient zur Durchführung einer arithmetischen Multiplikation zweier Werte. Es handelt sich um einen generischen Funktionsbaustein, der für eine saubere und modulare Architektur in IEC 61499-Systemen konzipiert ist. Anstelle von klassisch diskreten Daten- und Ereignisports nutzt dieser Baustein unidirektionale Adapter, um Steuerungsereignisse und Datenwerte gebündelt zu übertragen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung ist in den Eingangs-Adaptern integriert.

### **Ereignis-Ausgänge**

Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung ist im Ausgangs-Adapter integriert.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübertragung erfolgt gekoppelt über die Adapter.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenübertragung erfolgt gekoppelt über den Ausgangs-Adapter.

### **Adapter**

-   **Sockets (Eingangs-Adapter):**
    -   `IN1` (Typ: `adapter::types::unidirectional::ALI`): Erster Eingang für die Multiplikation (Multiplikand).
    -   `IN2` (Typ: `adapter::types::unidirectional::ALI`): Zweiter Eingang für die Multiplikation (Multiplikator).
-   **Plugs (Ausgangs-Adapter):**
    -   `OUT` (Typ: `adapter::types::unidirectional::ALI`): Ausgang für das Ergebnis der Multiplikation (Produkt).

## Funktionsweise

Der Funktionsbaustein `ALI_MUL_2_UNGATED` multipliziert die über die Adapter-Sockets `IN1` und `IN2` bereitgestellten Werte. Sobald ein entsprechendes Trigger-Ereignis über die Eingangs-Adapter signalisiert wird, führt der Baustein die Berechnung aus:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

Das berechnete Ergebnis sowie das zugehörige Ausgangs-Ereignis werden anschließend über den Ausgangs-Plug `OUT` an die nachfolgenden Bausteine weitergeleitet.

## Technische Besonderheiten

-   **Generischer Charakter:** Der Baustein ist über das Attribut `GenericClassName` als `GEN_ALI_MUL` deklariert. Dies ermöglicht eine flexible Handhabung verschiedener Datentypen, die durch das übergeordnete System oder den verwendeten Adaptertyp spezifiziert werden.
-   **Adapter-Kopplung:** Durch die Verwendung des unidirektionalen Adaptertyps `ALI` werden Daten und Trigger-Events in einer einzigen Verbindung gebündelt, was den Verdrahtungsaufwand in der Entwicklungsumgebung erheblich minimiert.

## Zustandsübersicht

Da es sich um einen rein datenfluss- und adapterbasierten Funktionsbaustein handelt, besitzt der Baustein keine komplexe interne Zustandsmaschine (Execution Control Chart - ECC). Die Abarbeitung erfolgt ereignisgesteuert und direkt gekoppelt an die über die Adapter eingehenden Trigger.

## Anwendungsszenarien

-   **Messwertskalierung:** Multiplikation von Sensorwerten mit Kalibrierungs- oder Skalierungsfaktoren.
-   **Leistungsberechnung:** Ermittlung von physikalischen Größen wie der elektrischen Leistung ($P = U \times I$) in adapterbasierten Steuerungsnetzwerken.
-   **Kompakte Berechnungsnetzwerke:** Einsatz in komplexen mathematischen Berechnungen, bei denen die visuelle Übersichtlichkeit des Steuerungsdiagramms durch den Einsatz von Adaptern gewahrt bleiben soll.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu klassischen mathematischen Bausteinen der IEC 61131-3 (wie z. B. einem Standard-`MUL`-Baustein mit diskreten `REQ` / `CNF` Events und separaten Datenleitungen) entfällt beim `ALI_MUL_2_UNGATED` das manuelle Verknüpfen von Event- und Datenpfaden. Dies verhindert Fehler bei der Event-Daten-Zuordnung und führt zu einem wesentlich aufgeräumteren und lesbareren Applikationsdiagramm in 4diac-ide.

- **[`ALI_MUL_2_UNGATED`](ALI_MUL_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

- **[`ALI_MUL_2`](ALI_MUL_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `ALI_MUL_2_UNGATED` ist ein moderner und effizienter Funktionsbaustein zur Multiplikation. Durch die konsequente Nutzung von unidirektionalen Adaptern eignet er sich hervorragend für serviceorientierte und modular aufgebaute Steuerungssysteme, bei denen Übersichtlichkeit und einfache Wartbarkeit im Vordergrund stehen.
