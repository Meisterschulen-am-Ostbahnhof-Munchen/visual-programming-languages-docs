# F_TIME_IN_NS_TO_UDINT

<img width="1538" height="212" alt="F_TIME_IN_NS_TO_UDINT" src="https://github.com/user-attachments/assets/cd46fa62-6fda-4f4a-8e2f-92db543f9c19" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_NS_TO_UDINT` dient der Konvertierung eines Zeitwertes in Nanosekunden (`TIME`) in einen vorzeichenlosen 32-Bit-Integer-Wert (`UDINT`). Diese Konvertierung ist insbesondere dann nützlich, wenn Zeitwerte für weitere Berechnungen oder Steuerungszwecke in einem numerischen Format benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Ereigniseingang ausgelöst, führt der Funktionsblock die Umwandlung des an `IN` anliegenden Zeitwertes durch.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird ausgelöst, sobald der konvertierte Wert an `OUT` ausgegeben wurde.

### **Daten-Eingänge**
- **IN** (`TIME`): Der Eingang für den Zeitwert in Nanosekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`UDINT`): Der Ausgang, an dem der konvertierte vorzeichenlose 32-Bit-Integer-Wert ausgegeben wird.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den an `IN` anliegenden Zeitwert in Nanosekunden (`TIME`) mittels der Funktion `TIME_IN_NS_TO_UDINT` in einen vorzeichenlosen 32-Bit-Integer-Wert (`UDINT`) umwandelt. Die Konvertierung erfolgt synchron zum Auslösen des `REQ`-Ereignisses. Nach erfolgreicher Umwandlung wird das `CNF`-Ereignis ausgelöst und der konvertierte Wert an `OUT` ausgegeben.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne Verzögerung.
- Der Funktionsblock ist für die Verwendung in Echtzeitanwendungen geeignet.
- Es werden keine zusätzlichen Parameter oder Konfigurationen benötigt.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Bei Auslösen von `REQ` wird der Zeitwert konvertiert.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Umwandlung von Zeitstempeln für die Verwendung in numerischen Berechnungen.
- Integration in Steuerungslogik, die Zeitwerte in einem numerischen Format verarbeiten muss.
- Verwendung in Diagnosesystemen zur Darstellung von Zeitdauern in einem lesbaren Format.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsbausteinen ist dieser Funktionsblock speziell auf die Umwandlung von Zeitwerten in Nanosekunden optimiert.
- Ähnliche Bausteine könnten zusätzliche Parameter oder Konfigurationsmöglichkeiten bieten, dieser Funktionsblock ist jedoch auf Einfachheit und Effizienz ausgelegt.

## Fazit
Der `F_TIME_IN_NS_TO_UDINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeitwerte in Nanosekunden in vorzeichenlose 32-Bit-Integer-Werte umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise eignet er sich ideal für Anwendungen, die eine schnelle und zuverlässige Konvertierung erfordern.
