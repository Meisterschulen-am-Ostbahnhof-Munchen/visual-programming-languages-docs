# F_INT_AS_WSTRING

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_AS_WSTRING` dient der Konvertierung eines ganzzahligen Wertes (`INT`) in eine breite Zeichenkette (`WSTRING`). Diese Funktionalität ist besonders nützlich, wenn numerische Werte für die Anzeige oder Weiterverarbeitung als Text benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Der ganzzahlige Wert (`INT`), der in eine breite Zeichenkette konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Die resultierende breite Zeichenkette (`WSTRING`) nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt die eingebaute Funktion `INT_AS_WSTRING`, um den ganzzahligen Eingabewert in eine breite Zeichenkette umzuwandeln. Die Konvertierung wird durch das Ereignis `REQ` initiiert und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und führt nur eine grundlegende Datentypkonvertierung durch.
- Es werden keine zusätzlichen Parameter oder komplexen Algorithmen benötigt.

## Zustandsübersicht
1. **Bereit**: Wartet auf das Ereignis `REQ`.
2. **Aktiv**: Führt die Konvertierung durch und setzt den Ausgang `OUT`.
3. **Bestätigt**: Sendet das Ereignis `CNF` und kehrt in den Bereitschaftszustand zurück.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textform.
- Vorbereitung von Daten für die Kommunikation mit Systemen, die Textformate erwarten.

## Vergleich mit ähnlichen Bausteinen
- **F_DINT_AS_WSTRING**: Konvertiert einen längeren ganzzahligen Wert (`DINT`) in eine breite Zeichenkette.
- **F_REAL_AS_WSTRING**: Konvertiert einen Fließkommawert (`REAL`) in eine breite Zeichenkette.
- **F_STRING_AS_INT**: Führt die umgekehrte Konvertierung durch (Zeichenkette zu Ganzzahl).

## Fazit
Der `F_INT_AS_WSTRING` Funktionsblock ist ein einfaches und effizientes Werkzeug für die Konvertierung von Ganzzahlen in breite Zeichenketten. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für grundlegende Datentypumwandlungen.