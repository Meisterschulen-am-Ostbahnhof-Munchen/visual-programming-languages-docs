# F_STRING_TO_WSTRING

<img width="1509" height="212" alt="F_STRING_TO_WSTRING" src="https://github.com/user-attachments/assets/4ece7977-3ec9-493b-8cb5-e1ba73c202f8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_TO_WSTRING` dient der Konvertierung eines `STRING`-Datentyps in einen `WSTRING`-Datentyp. Dies ist besonders nützlich in Umgebungen, wo eine Umwandlung zwischen schmalen (8-Bit) und breiten (16-Bit) Zeichenketten erforderlich ist, beispielsweise bei der Internationalisierung von Anwendungen oder der Kommunikation mit Systemen, die unterschiedliche Zeichenkodierungen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Initiert die Konvertierung. Bei Auslösung dieses Ereignisses wird der Eingabewert `IN` gelesen und verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Ausgabewert `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (`STRING`): Die Eingabezeichenkette, die in einen `WSTRING` umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (`WSTRING`): Die resultierende breite Zeichenkette nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis eintrifft. Dabei wird der `STRING`-Wert von `IN` mittels der Funktion `STRING_TO_WSTRING` in einen `WSTRING` umgewandelt und das Ergebnis an `OUT` ausgegeben. Gleichzeitig wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Block ist als einfacher Funktionsblock (`SimpleFB`) implementiert, was eine effiziente Ausführung garantiert.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- **Internationalisierung**: Umwandlung von lokalen Zeichenketten in Unicode-fähige `WSTRING`-Werte.
- **Systemkommunikation**: Austausch von Daten zwischen Systemen, die unterschiedliche Zeichensätze verwenden.
- **Datenverarbeitung**: Verarbeitung von Textdaten, die in verschiedenen Kodierungen vorliegen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_STRING_TO_WSTRING` spezialisiert auf die Umwandlung zwischen `STRING` und `WSTRING`.
- Andere Blöcke wie `F_WSTRING_TO_STRING` bieten die umgekehrte Funktionalität.

## Fazit
Der `F_STRING_TO_WSTRING`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von Zeichenketten zwischen unterschiedlichen Kodierungen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn besonders geeignet für Anwendungen, die eine schnelle und zuverlässige Umwandlung erfordern.
