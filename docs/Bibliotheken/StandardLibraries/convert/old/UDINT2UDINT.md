# UDINT2UDINT

<img width="1197" height="182" alt="UDINT2UDINT" src="https://github.com/user-attachments/assets/70126ff5-611e-4c8e-b27e-05f464e1386c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `UDINT2UDINT` dient der einfachen Datentypkonvertierung von einem UDINT-Wertyp auf einen anderen UDINT-Wert. Es handelt sich um einen grundlegenden Baustein, der in verschiedenen Steuerungs- und Automatisierungsanwendungen eingesetzt werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird dieser Ereigniseingang ausgelöst, wird der Algorithmus zur Konvertierung der Daten gestartet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Dieses Ereignis wird nach der Ausführung des Algorithmus ausgelöst.

### **Daten-Eingänge**
- **IN** (UDINT): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (UDINT): Der Ausgangswert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `UDINT2UDINT` führt eine direkte Zuweisung des Eingangswerts `IN` zum Ausgangswert `OUT` durch. Der Algorithmus wird durch das Ereignis `REQ` gestartet und gibt nach Abschluss der Operation das Ereignis `CNF` aus.

## Technische Besonderheiten
- Der Funktionsblock ist für den Datentyp UDINT (Unsigned Double Integer) ausgelegt.
- Die Konvertierung erfolgt ohne weitere Bearbeitung oder Transformation der Daten.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Bei Empfang von `REQ` wird der Algorithmus ausgeführt und der Wert von `IN` an `OUT` zugewiesen.
3. **Bestätigungszustand**: Nach erfolgreicher Ausführung wird das Ereignis `CNF` ausgelöst.

## Anwendungsszenarien
- Datentypkonvertierung in Steuerungssystemen.
- Weiterleitung von Werten ohne Änderung in Automatisierungsprozessen.
- Verwendung als Platzhalter oder zur Signalweiterleitung in komplexeren Funktionsblocknetzwerken.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen bietet `UDINT2UDINT` keine zusätzliche Funktionalität wie Skalierung oder Formatierung, sondern dient lediglich der direkten Zuweisung.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Typumwandlung oder Datenmanipulation bieten.

## Fazit
Der `UDINT2UDINT` Funktionsblock ist ein einfacher, aber effektiver Baustein für die direkte Zuweisung von UDINT-Werten. Seine Einfachheit macht ihn zu einem vielseitig einsetzbaren Element in verschiedenen Automatisierungsanwendungen, insbesondere dort, wo keine weitere Datenmanipulation erforderlich ist.
