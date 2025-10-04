# F_BYTE_TO_DINT

<img width="1234" height="183" alt="F_BYTE_TO_DINT" src="https://github.com/user-attachments/assets/33fb3b6c-7400-46dd-b1bd-7f5031adddf3" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_DINT` dient der Konvertierung eines `BYTE`-Wertes in einen `DINT`-Wert. Er ist Teil der `iec61131::conversion`-Bibliothek und ermöglicht eine einfache und effiziente Typumwandlung zwischen diesen beiden Datentypen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Ausführung des Funktionsblocks aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ausgang signalisiert die erfolgreiche Ausführung des Funktionsblocks. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `BYTE`-Wert, der in einen `DINT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `DINT`-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BYTE` zu `DINT` durch, sobald das Ereignis `REQ` empfangen wird. Die Umwandlung erfolgt mittels der Funktion `BYTE_TO_DINT(IN)`, die den Wert des Eingangs `IN` in den entsprechenden `DINT`-Wert umwandelt und am Ausgang `OUT` bereitstellt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verarbeitungsschritte.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt einmalig bei jedem Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `BYTE`-Daten in `DINT`-Daten umgewandelt werden müssen.
- Integration in größere Systeme, die eine Typkompatibilität zwischen verschiedenen Datenformaten erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_WORD_TO_DINT` oder `F_INT_TO_DINT` ist dieser Funktionsblock speziell auf die Umwandlung von `BYTE` zu `DINT` ausgelegt.
- Er bietet eine einfache und direkte Lösung für diese spezifische Konvertierung.

## Fazit
Der `F_BYTE_TO_DINT`-Funktionsblock ist ein nützliches Werkzeug für die Typumwandlung in IEC 61131-3-basierten Steuerungssystemen. Seine einfache und effiziente Funktionsweise macht ihn zu einer zuverlässigen Lösung für Anwendungen, die eine Konvertierung von `BYTE` zu `DINT` erfordern.
