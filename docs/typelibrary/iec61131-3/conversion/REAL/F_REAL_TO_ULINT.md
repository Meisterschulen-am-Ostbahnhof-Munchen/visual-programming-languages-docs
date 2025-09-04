# F_REAL_TO_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_ULINT` dient der Konvertierung eines `REAL`-Wertes (Fließkommazahl) in einen `ULINT`-Wert (64-Bit vorzeichenlose Ganzzahl). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingang für den `REAL`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten `ULINT`-Wert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der `REAL`-Wert am Eingang `IN` in einen `ULINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung wird mit dem Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `REAL_TO_ULINT`.
- Der Baustein ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Umwandlung durch und gibt das Ergebnis aus.
3. **Bestätigungszustand**: Sendet das `CNF`-Ereignis zur Bestätigung der Konvertierung.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo Fließkommazahlen in vorzeichenlose Ganzzahlen umgewandelt werden müssen.
- Datenverarbeitung in industriellen Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_REAL_TO_INT` oder `F_REAL_TO_LINT` führen Konvertierungen in andere Ganzzahltypen durch. `F_REAL_TO_ULINT` ist spezifisch für 64-Bit vorzeichenlose Ganzzahlen.

## Fazit
Der `F_REAL_TO_ULINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `REAL`-Werte in `ULINT`-Werte umzuwandeln. Seine klare Schnittstellenstruktur und einfache Funktionsweise machen ihn zu einem wertvollen Baustein in der industriellen Automatisierung.