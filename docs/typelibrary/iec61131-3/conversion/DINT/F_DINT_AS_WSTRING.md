# F_DINT_AS_WSTRING

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_AS_WSTRING` dient der Konvertierung eines 32-Bit-Ganzzahlwerts (DINT) in eine Unicode-Zeichenkette (WSTRING). Diese Funktionalität ist besonders nützlich, wenn numerische Werte für die Anzeige oder Weiterverarbeitung als Text benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des Eingabewerts. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (DINT): Der zu konvertierende 32-Bit-Ganzzahlwert.

### **Daten-Ausgänge**
- **OUT** (WSTRING): Die resultierende Unicode-Zeichenkette nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert am Eingang `IN` gelesen und mittels der Funktion `DINT_AS_WSTRING` in eine Unicode-Zeichenkette umgewandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Algorithmus ohne Zustandsautomaten.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -verwaltung.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textform.
- Vorbereitung von Daten für Text-basierte Kommunikationsprotokolle.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_INT_AS_WSTRING` verarbeitet dieser Block 32-Bit statt 16-Bit Ganzzahlen.
- Ähnliche Blöcke wie `F_DINT_AS_STRING` konvertieren in ASCII- statt Unicode-Zeichenketten.

## Fazit
Der `F_DINT_AS_WSTRING`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, 32-Bit-Ganzzahlen in Unicode-Zeichenketten umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die numerische Daten in Textform benötigen.