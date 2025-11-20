# ST08B_TO_BYTE

![ST08B_TO_BYTE](https://github.com/user-attachments/assets/e4d143e0-d49f-4eb3-bc48-fc4a4bc49984)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ST08B_TO_BYTE` dient der Konvertierung einer Struktur vom Typ `ST08B` (bestehend aus 8 einzelnen BOOL-Werten) in einen BYTE-Datentyp. Jedes Bit des resultierenden BYTES entspricht einem der BOOL-Werte der Eingangsstruktur.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Auslöseereignis für die Konvertierung. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigungsereignis nach erfolgreicher Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (ST08B): Eingangsstruktur mit 8 BOOL-Werten (`B_00` bis `B_07`), die in ein BYTE konvertiert werden.

### **Daten-Ausgänge**
- `OUT` (BYTE): Ergebnis der Konvertierung, wobei jedes Bit des BYTES (`OUT.0` bis `OUT.7`) dem entsprechenden BOOL-Wert der Eingangsstruktur zugeordnet ist.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` liest der Funktionsblock die Werte der Eingangsstruktur `IN` und weist sie den entsprechenden Bits des Ausgangs-BYTE `OUT` zu. Die Zuordnung erfolgt wie folgt:
- `OUT.0` = `IN.B_00`
- `OUT.1` = `IN.B_01`
- ...
- `OUT.7` = `IN.B_07`

Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Berechnungen.
- Der Funktionsblock ist für die Verwendung in Echtzeitumgebungen geeignet, da er deterministisch arbeitet.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Verarbeitet die Eingangsdaten und setzt die Ausgangsbits.
3. **Bestätigungszustand**: Löst `CNF` aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Umwandlung von strukturierten BOOL-Werten in ein BYTE für kompakte Speicherung oder Übertragung.
- Schnittstellenanpassung zwischen Systemen, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke könnten einzelne BOOL-Eingänge direkt in ein BYTE umwandeln, jedoch bietet `ST08B_TO_BYTE` eine strukturierte und klar definierte Schnittstelle durch Verwendung der `ST08B`-Struktur.

## Fazit
Der `ST08B_TO_BYTE`-Funktionsblock ist ein effizientes Werkzeug zur Konvertierung von strukturierten BOOL-Werten in ein BYTE. Seine einfache und deterministische Funktionsweise macht ihn besonders geeignet für Echtzeitanwendungen und Systemintegrationen.
