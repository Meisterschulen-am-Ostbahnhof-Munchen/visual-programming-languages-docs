# F_LREAL_TO_UINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_UINT` dient der Konvertierung eines LREAL-Wertes (64-Bit Gleitkommazahl) in einen UINT-Wert (vorzeichenlose 16-Bit Ganzzahl). Dieser Baustein ist Teil der `iec61131::conversion`-Bibliothek und ermöglicht eine einfache und effiziente Typumwandlung in Automatisierungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Beim Auftreten dieses Ereignisses wird der Algorithmus zur Umwandlung des Eingabewertes ausgeführt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird nach erfolgreicher Umwandlung des Wertes ausgegeben.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet eine LREAL-Zahl (64-Bit Gleitkommazahl), die in einen UINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt das Ergebnis der Konvertierung als UINT-Wert (vorzeichenlose 16-Bit Ganzzahl) aus.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Beim Auftreten des `REQ`-Ereignisses wird der Algorithmus zur Konvertierung des LREAL-Wertes am Eingang `IN` in einen UINT-Wert ausgeführt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert den erfolgreichen Abschluss der Operation.

Der Algorithmus verwendet die Funktion `LREAL_TO_UINT` zur direkten Umwandlung des Eingabewertes. Es ist zu beachten, dass bei der Konvertierung von Gleitkommazahlen in Ganzzahlen eine mögliche Abrundung oder Überlauf auftreten kann.

## Technische Besonderheiten
- **Datentypen**: Der Funktionsblock verarbeitet 64-Bit Gleitkommazahlen (LREAL) und gibt 16-Bit vorzeichenlose Ganzzahlen (UINT) aus.
- **Algorithmus**: Die Konvertierung erfolgt direkt durch die eingebaute `LREAL_TO_UINT`-Funktion.
- **Fehlerbehandlung**: Der Baustein verfügt über keine integrierte Fehlerbehandlung für Überlauf oder ungültige Eingabewerte.

## Zustandsübersicht
1. **Wartezustand**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Ausführungszustand**: Bei `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgegeben und der Baustein kehrt in den Wartezustand zurück.

## Anwendungsszenarien
- Konvertierung von Sensorwerten (z.B. Temperaturmessungen) in ganzzahlige Werte für die weitere Verarbeitung.
- Typumwandlung in Steuerungsanwendungen, wo Gleitkommazahlen in Ganzzahlen für bestimmte Operationen benötigt werden.
- Schnittstellenanpassung zwischen Systemkomponenten mit unterschiedlichen Datentypen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_LREAL_TO_UINT` spezialisiert auf die Umwandlung von LREAL zu UINT.
- Andere Konvertierungsblöcke könnten zusätzliche Funktionen wie Bereichsprüfung oder Fehlerbehandlung bieten, sind aber komplexer in der Handhabung.

## Fazit
Der `F_LREAL_TO_UINT` Funktionsblock bietet eine einfache und effiziente Lösung für die spezifische Konvertierung von 64-Bit Gleitkommazahlen in 16-Bit vorzeichenlose Ganzahlen. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, wo eine schnelle Typumwandlung ohne zusätzliche Funktionen benötigt wird. Für Anwendungen mit kritischen Werten sollten jedoch zusätzliche Überprüfungen implementiert werden.