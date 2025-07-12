# INT2INT

<img width="1147" height="182" alt="INT2INT" src="https://github.com/user-attachments/assets/fc234992-1349-449a-b5c1-a33bafbd3b68" />

* * * * * * * * * *
## Einleitung
Der INT2INT Funktionsblock dient zur direkten Konvertierung eines Integer-Wertes (INT) in einen anderen Integer-Wert (INT). Es handelt sich um einen einfachen Baustein ohne zusätzliche Verarbeitungslogik, der hauptsächlich zur Typumwandlung oder Wertweiterleitung verwendet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingabewert vom Typ INT, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgabewert vom Typ INT, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingabewertes `IN` an den Ausgabewert `OUT` durch. Es findet keine zusätzliche Verarbeitung oder Transformation statt. Die Ausführung wird durch das `REQ`-Ereignis gestartet und mit dem `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- **Einfache Implementierung**: Der Algorithmus besteht lediglich aus einer Zuweisung.
- **Keine zusätzliche Logik**: Es werden keine Bedingungen oder Berechnungen durchgeführt.
- **Schnelle Ausführung**: Da keine komplexen Operationen stattfinden, ist der Baustein sehr effizient.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand. Jede Ausführung ist unabhängig von vorherigen Aufrufen.

## Anwendungsszenarien
- **Typumwandlung**: Kann verwendet werden, um sicherzustellen, dass ein Wert als INT behandelt wird.
- **Wertweiterleitung**: Nützlich in Pipelines, wo Werte zwischen verschiedenen Blöcken weitergeleitet werden müssen.
- **Debugging**: Hilfreich zur Überprüfung von Werten in komplexen Systemen.

## Vergleich mit ähnlichen Bausteinen
- **INT2REAL**: Konvertiert einen Integer-Wert in einen Real-Wert, während INT2INT den Typ beibehält.
- **REAL2INT**: Konvertiert einen Real-Wert in einen Integer-Wert, mit potenzieller Datenverlust durch Rundung.

## Fazit
Der INT2INT Funktionsblock ist ein einfacher, aber nützlicher Baustein für die direkte Weitergabe oder Typumwandlung von Integer-Werten. Seine Einfachheit macht ihn zuverlässig und effizient in verschiedenen Anwendungsszenarien.
