# F_TIME_IN_S_TO_UDINT

<img width="1520" height="212" alt="F_TIME_IN_S_TO_UDINT" src="https://github.com/user-attachments/assets/9fd11a62-281e-43ec-9520-98d7cc20671c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_S_TO_UDINT` dient der Konvertierung eines TIME-Werts in Sekunden in einen UDINT-Wert. Diese Konvertierung ist nützlich, wenn Zeitwerte in numerischen Operationen oder für weitere Verarbeitungsschritte benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: TIME-Wert in Sekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Konvertierter UDINT-Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock konvertiert den eingehenden TIME-Wert (IN) in Sekunden in einen UDINT-Wert (OUT). Die Konvertierung erfolgt durch den Aufruf der Funktion `TIME_IN_S_TO_UDINT(IN)` im Algorithmus. Bei Auslösung des REQ-Ereignisses wird die Konvertierung durchgeführt und das CNF-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient, da er direkt die eingebaute Funktion `TIME_IN_S_TO_UDINT` nutzt.
- Keine zusätzlichen Zustände oder komplexe Logik erforderlich.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt sofort bei Auslösung des REQ-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Zeitwerten für numerische Berechnungen.
- Integration in Steuerungssysteme, wo Zeitwerte als numerische Werte benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist dieser speziell für die Umwandlung von TIME in UDINT optimiert.
- Andere Bausteine könnten zusätzliche Funktionen wie Skalierung oder Grenzwertprüfung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_TIME_IN_S_TO_UDINT` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von TIME-Werten in UDINT. Er eignet sich ideal für Anwendungen, bei denen Zeitwerte in numerischer Form benötigt werden.
