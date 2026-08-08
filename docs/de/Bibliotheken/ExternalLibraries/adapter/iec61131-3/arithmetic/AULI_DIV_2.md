# AULI_DIV_2


![AULI_DIV_2](./AULI_DIV_2.svg)

*Kein Bild vorhanden*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AULI_DIV_2` ist ein generischer Funktionsbaustein (Generic FB), der für die Durchführung einer arithmetischen Division (DIV) entwickelt wurde. Er basiert auf der IEC 61499-Norm und nutzt das Konzept von Adaptern, um Daten und die dazugehörige Steuerungslogik effizient zu übertragen. Der Baustein ist im Namensraum `adapter::iec61131::arithmetic` definiert und verwendet die generische Klasse `GEN_AULI_DIV`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Eingänge. Die Steuerung des Signalflusses und die Ereignisverarbeitung werden vollständig über die angeschlossenen Adapter abgewickelt.

### **Ereignis-Ausgänge**
Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt gekoppelt über den Ausgangs-Adapter.

### **Daten-Eingänge**
Es sind keine direkten Daten-Eingänge vorhanden. Die Werte für die Berechnung werden über die Eingangs-Adapter bereitgestellt.

### **Daten-Ausgänge**
Es sind keine direkten Daten-Ausgänge vorhanden. Das Berechnungsergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**
Die gesamte Kommunikation des Bausteins wird über Adapter vom Typ `AULI` (unidirektional) realisiert:

*   **IN1 (Socket / Buchse)**:
    *   **Typ**: `adapter::types::unidirectional::AULI`
    *   **Beschreibung**: Erster Eingang der Division (Dividend / Zähler).
*   **IN2 (Socket / Buchse)**:
    *   **Typ**: `adapter::types::unidirectional::AULI`
    *   **Beschreibung**: Zweiter Eingang der Division (Divisor / Nenner).
*   **OUT (Plug / Stecker)**:
    *   **Typ**: `adapter::types::unidirectional::AULI`
    *   **Beschreibung**: Ausgang, der das Ergebnis der Division (Quotient) liefert.

## Funktionsweise

Der Baustein führt eine mathematische Division der über die Adapter bereitgestellten Eingangswerte aus. Die Formel lautet:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Da es sich um einen generischen Funktionsbaustein (`GEN_AULI_DIV`) handelt, kann er sich zur Laufzeit oder während der Instanziierung in der 4diac-IDE an verschiedene numerische Datentypen anpassen, sofern diese vom Typ `AULI` unterstützt werden. Die Ausführung der Berechnung wird typischerweise durch ein Aktualisierungsereignis auf einem der Eingangs-Adapter (`IN1` oder `IN2`) getriggert. Das Ergebnis wird anschließend am Ausgangs-Adapter `OUT` zusammen mit einem entsprechenden Ausgabeereignis bereitgestellt.

## Technische Besonderheiten

*   **Generische Natur**: Durch das Attribut `GenericClassName` mit dem Wert `'GEN_AULI_DIV'` ist der Baustein flexibel einsetzbar und nicht starr auf einen einzigen Datentyp (wie z. B. nur `REAL` oder `INT`) festgelegt.
*   **Kapselung durch Adapter**: Da keine klassischen Event- und Data-Ports genutzt werden, bleibt das visuelle Design im Funktionsplan (FBD) sehr übersichtlich. Die logische Zusammengehörigkeit von Daten und Triggern ist im `AULI`-Adapter gekapselt.
*   **Unidirektionale Adapter**: Die Verwendung von `unidirectional::AULI` deutet darauf hin, dass der Informationsfluss strikt in eine Richtung (von den Sockets zum Baustein und vom Baustein zum Plug) verläuft.

## Zustandsübersicht

Da es sich bei diesem Baustein um einen grundlegenden arithmetischen Baustein handelt, besitzt er in der Regel ein einfaches, zustandsloses Verhalten (bzw. verhält sich wie ein klassischer Execution Control Chart (ECC) mit einem Standard-Zustand, der auf Eingangsereignisse reagiert):

1.  **Warten auf Ereignis**: Der Baustein wartet auf ein Aktualisierungsereignis an `IN1` oder `IN2`.
2.  **Berechnung**: Bei Eintreffen eines Ereignisses wird die Division durchgeführt.
3.  **Ergebnisübergabe**: Der berechnete Wert wird an `OUT` angelegt und das entsprechende Ausgangsereignis am Plug getriggert.
4.  **Rückkehr**: Der Baustein kehrt in den Wartezustand zurück.

*Hinweis zur Division durch Null:* Je nach Implementierung der Laufzeitumgebung (Runtime) für den generischen Typ `GEN_AULI_DIV` sollten Mechanismen zur Vermeidung einer Division durch Null (z. B. Ausgabe von `NaN`, Unendlich oder das Abfangen über den Adapterstatus) beachtet werden.

## Anwendungsszenarien

*   **Skalierung von Sensorwerten**: Division von analogen Rohwerten durch einen Skalierungsfaktor zur Umrechnung in physikalische Einheiten.
*   **Verhältnismessung**: Berechnung von Verhältnissen in der Prozessautomatisierung (z. B. Durchflussverhältnis von zwei Medien).
*   **Mittelwertbildung**: Verwendung in Berechnungsnetzwerken, bei denen Summenwerte durch eine Anzahl geteilt werden müssen.
*   **Strukturierte Architekturen**: Einsatz in Systemen, die konsequent auf Adapter-basierte Kommunikation setzen, um die Anzahl der sichtbaren Verbindungslinien im Systemmodell zu minimieren.

## Vergleich mit ähnlichen Bausteinen

*   **Standard `DIV`-Baustein**: Ein klassischer IEC 61131-3 / IEC 61499 `DIV`-Baustein nutzt direkte Dateneingänge (`IN1`, `IN2`) und Event-Ports (`REQ`, `CNF`). Der `AULI_DIV_2` hingegen bündelt diese Signale in Adaptern, was die Verdrahtung bei komplexen Signalstrukturen erheblich vereinfacht.
*   **Andere AULI-Arithmetikbausteine** (z. B. `AULI_ADD`, `AULI_SUB`): Nutzen dieselbe Schnittstellenphilosophie mit Sockets und Plugs, führen jedoch andere mathematische Operationen aus.

## Fazit

Der `AULI_DIV_2` ist ein moderner, modularer Funktionsbaustein für arithmetische Divisionen in Eclipse 4diac. Durch die konsequente Nutzung von unidirektionalen Adaptern fördert er ein sauberes und übersichtliches Softwaredesign in verteilten Steuerungssystemen nach IEC 61499, indem er Daten und Steuerereignisse elegant bündelt.