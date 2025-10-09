# F_WORD_TO_UDINT

<img width="1455" height="214" alt="F_WORD_TO_UDINT" src="https://github.com/user-attachments/assets/0620ecfb-f811-4aea-b442-967e54ac35c8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_UDINT` dient der Konvertierung eines `WORD`-Datentyps in einen `UDINT`-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Typumwandlung erforderlich ist, um Daten für weitere Verarbeitungsschritte vorzubereiten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Auslösung dieses Ereignisses wird der Eingangswert `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung und gibt das Ergebnis über den Ausgang `OUT` aus.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `WORD`, der in einen `UDINT` umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Das Ergebnis der Konvertierung als `UDINT`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus gestartet, der den `WORD`-Wert am Eingang `IN` in einen `UDINT`-Wert konvertiert. Das Ergebnis wird am Ausgang `OUT` bereitgestellt und das `CNF`-Ereignis signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Der Funktionsblock verwendet die eingebaute Funktion `WORD_TO_UDINT` zur Konvertierung.
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder komplexe Logik, was eine schnelle und effiziente Verarbeitung ermöglicht.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Verarbeitungszustand**: Führt die Konvertierung durch.
3. **Abschlusszustand**: Sendet das `CNF`-Ereignis und gibt das Ergebnis aus.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen.
- Vorbereitung von Daten für weitere Berechnungen oder Speicherung.
- Integration in größere Automatisierungslösungen, bei denen unterschiedliche Datentypen verarbeitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_REAL` oder `F_BOOL_TO_BYTE` bieten ähnliche Funktionalitäten für andere Datentypen.
- `F_WORD_TO_UDINT` ist spezialisiert auf die Konvertierung von `WORD` zu `UDINT` und bietet daher eine optimierte Lösung für diesen spezifischen Anwendungsfall.

## Fazit
Der `F_WORD_TO_UDINT`-Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von `WORD`- in `UDINT`-Werte. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einer zuverlässigen Komponente in Automatisierungsprojekten.
