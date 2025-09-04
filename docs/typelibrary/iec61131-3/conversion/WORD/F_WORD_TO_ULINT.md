# F_WORD_TO_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_ULINT` dient der Konvertierung eines `WORD`-Datentyps in einen `ULINT`-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Erweiterung oder Umwandlung von Datenformaten erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Erwartet einen `WORD`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten `ULINT`-Wert aus.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `WORD` nach `ULINT` durch, sobald das `REQ`-Ereignis eintritt. Die Konvertierung erfolgt mittels der integrierten Funktion `WORD_TO_ULINT`. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Baustein ist Teil des Pakets `iec61131::conversion`.
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Einstellungen.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Done**: Sendet das `CNF`-Ereignis und gibt das Ergebnis aus.

## Anwendungsszenarien
- Datenverarbeitung in Steuerungssystemen, wo unterschiedliche Datentypen kompatibel gemacht werden müssen.
- Erweiterung von Daten für weitere Berechnungen oder Speicherung.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine könnten direkte Konvertierungen zwischen anderen Datentypen anbieten, z.B. `F_WORD_TO_INT`.
- Dieser Baustein spezialisiert sich auf die Konvertierung zu `ULINT`, was besonders für große, vorzeichenlose Zahlen relevant ist.

## Fazit
Der `F_WORD_TO_ULINT`-Funktionsblock ist ein einfacher, aber effektiver Baustein für die Konvertierung von `WORD` zu `ULINT`. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einer zuverlässigen Lösung in vielen Automatisierungsszenarien.