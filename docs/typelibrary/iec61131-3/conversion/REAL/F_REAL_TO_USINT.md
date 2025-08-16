# F_REAL_TO_USINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_USINT` dient der Konvertierung eines REAL-Wertes (Fließkommazahl) in einen USINT-Wert (vorzeichenlose 8-Bit Ganzzahl). Diese Konvertierung ist besonders nützlich, wenn Fließkommazahlen in einem Bereich verarbeitet werden müssen, der nur ganzzahlige Werte erfordert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Wird ausgelöst, sobald der konvertierte Wert am Daten-Ausgang `OUT` verfügbar ist.

### **Daten-Eingänge**
- **IN**: REAL-Wert, der in einen USINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte USINT-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt eine direkte Konvertierung des REAL-Wertes am Eingang `IN` in einen USINT-Wert durch. Die Konvertierung erfolgt durch den Aufruf der internen Funktion `REAL_TO_USINT`. Sobald die Konvertierung abgeschlossen ist, wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung schneidet den Nachkommaanteil ab (keine Rundung).
- Der Eingangswert sollte im Bereich von 0 bis 255 liegen, da USINT nur Werte in diesem Bereich darstellen kann. Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten oder Überlauf.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das Ereignis `CNF` und stellt den konvertierten Wert bereit.

## Anwendungsszenarien
- Konvertierung von Sensorwerten (z.B. Temperatur, Druck) in ganzzahlige Werte für die weitere Verarbeitung.
- Vorverarbeitung von Daten für Systeme, die nur Ganzzahlen verarbeiten können.

## Vergleich mit ähnlichen Bausteinen
- **F_REAL_TO_INT**: Konvertiert REAL in INT (vorzeichenbehaftete 16-Bit Ganzahl).
- **F_REAL_TO_UINT**: Konvertiert REAL in UINT (vorzeichenlose 16-Bit Ganzahl).
- **F_REAL_TO_ULINT**: Konvertiert REAL in ULINT (vorzeichenlose 64-Bit Ganzahl).

## Fazit
Der Funktionsblock `F_REAL_TO_USINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von Fließkommazahlen in vorzeichenlose 8-Bit Ganzzahlen. Er eignet sich besonders für Anwendungen, bei denen Speicherplatz oder Verarbeitungsressourcen begrenzt sind.