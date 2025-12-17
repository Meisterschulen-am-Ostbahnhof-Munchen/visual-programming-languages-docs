# F_WORD_TO_LINT

<img width="1438" height="214" alt="F_WORD_TO_LINT" src="https://github.com/user-attachments/assets/626d094f-fb66-471e-9668-d8d5be75042c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_LINT` dient der Konvertierung eines `WORD`-Datentyps in einen `LINT`-Datentyp. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht eine einfache und effiziente Typumwandlung innerhalb von IEC 61499-basierten Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `WORD`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `LINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `WORD` zu `LINT` durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `WORD_TO_LINT`, die den Eingabewert `IN` umwandelt und das Ergebnis an `OUT` ausgibt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Algorithmus ohne Zustandsmaschine.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Block ist für den Einsatz in Echtzeit-Steuerungssystemen optimiert.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder komplexe Zustandslogik. Die Ausführung erfolgt direkt bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `WORD`-Daten in `LINT` umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die unterschiedliche Datentypen verarbeiten.
- Verwendung in Datenverarbeitungsketten, wo eine Erweiterung der Bitbreite erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_WORD_TO_LINT` spezialisiert und daher effizienter.
- Andere Blöcke wie `F_INT_TO_LINT` oder `F_DWORD_TO_LINT` bieten ähnliche Funktionalität, aber für andere Datentypen.

## Fazit
Der `F_WORD_TO_LINT`-Funktionsblock ist ein einfacher und effizienter Baustein für die Typumwandlung von `WORD` zu `LINT`. Er eignet sich ideal für Anwendungen, die eine schnelle und direkte Konvertierung erfordern, und ist leicht in bestehende Steuerungssysteme integrierbar.
