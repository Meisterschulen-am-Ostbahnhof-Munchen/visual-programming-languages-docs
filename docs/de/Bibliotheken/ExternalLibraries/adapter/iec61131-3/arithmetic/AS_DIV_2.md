# AS_DIV_2


![AS_DIV_2](./AS_DIV_2.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein (FB) `AS_DIV_2` ist ein generischer Baustein zur Durchführung einer arithmetischen Division im Kontext der IEC 61499-Architektur. Er nutzt ein adapterbasiertes Konzept zur Datenübertragung und ermöglicht eine saubere und strukturierte Signalverarbeitung, indem er Eingangsdaten über standardisierte Adapter entgegennimmt, die Division berechnet und das Ergebnis an einen Ausgangsadapter übergibt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung und Triggerung erfolgt implizit über die angebundenen Adapter.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::AS`): 
    *   Repräsentiert den ersten Eingangswert der Division (Dividend).
*   **IN2** (Typ: `adapter::types::unidirectional::AS`): 
    *   Repräsentiert den zweiten Eingangswert der Division (Divisor).

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::AS`): 
    *   Gibt das Ergebnis der Division (Quotient) aus.

---

## Funktionsweise

Der Funktionsbaustein `AS_DIV_2` führt eine mathematische Division der übergebenen Eingangswerte durch. Die grundlegende Berechnungsformel lautet:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Sobald sich die Werte an den Eingangs-Adaptern `IN1` oder `IN2` ändern bzw. ein entsprechendes Event über die Adapter übertragen wird, wird die Division durchgeführt und das Ergebnis über den Ausgangs-Adapter `OUT` bereitgestellt.

---

## Technische Besonderheiten

*   **Generischer Baustein:** Durch das Attribut `GenericClassName = 'GEN_AS_DIV'` ist der Baustein als generischer Typ definiert. Dies erlaubt eine hohe Flexibilität bei der Verarbeitung unterschiedlicher numerischer Datentypen.
*   **Kapselung durch Adapter:** Anstelle von losen Daten- und Ereignisleitungen nutzt dieser Baustein ausschließlich unidirektionale Adapter des Typs `AS`. Dies sorgt für ein aufgeräumtes und übersichtliches Anwendungsdiagramm in der 4diac-IDE.
*   **Division durch Null:** Bei der Implementierung und Verwendung ist darauf zu achten, dass der Divisor (`IN2`) ungleich Null sein muss, um einen Laufzeitfehler (Division by Zero) zu vermeiden.

---

## Zustandsübersicht

Da es sich um einen rein mathematischen/arithmetischen Funktionsbaustein handelt, besitzt der `AS_DIV_2` keinen komplexen internen Zustandsautomaten (ECC). Die Ausgangswerte werden direkt in Abhängigkeit der an den Adaptern anliegenden Eingangssignale berechnet.

---

## Anwendungsszenarien

*   **Messwert-Skalierung:** Umrechnung und Normierung von analogen Sensorwerten (z. B. Division eines Rohwerts zur Umrechnung in eine physikalische Einheit).
*   **Prozentuale Berechnungen:** Bestimmung von Verhältnissen oder prozentualen Anteilen in industriellen Prozessen.
*   **Signalvorverarbeitung:** Mathematische Reduktion von Prozessdaten direkt an der Feldebene vor der Weiterleitung an übergeordnete Systeme.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu klassischen IEC 61131-3 `DIV`-Bausteinen, die mit direkten Daten-Pins arbeiten, bietet der `AS_DIV_2` durch die Nutzung von Adaptern eine wesentlich bessere Kapselung. Die Anzahl der Verbindungslinien im CFC (Continuous Function Chart) wird signifikant reduziert, was besonders bei großen und komplexen Steuerungsprogrammen die Wartbarkeit erhöht.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AS_DIV_2` ist ein robuster und flexibel einsetzbarer Baustein für arithmetische Divisionen in verteilten Steuerungssystemen. Durch die konsequente Nutzung des Adapter-Konzepts unterstützt er modernes, modulares Softwaredesign nach dem IEC 61499-Standard.