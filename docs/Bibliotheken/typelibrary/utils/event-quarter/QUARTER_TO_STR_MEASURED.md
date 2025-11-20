# QUARTER_TO_STR_MEASURED

![QUARTER_TO_STR_MEASURED](https://github.com/user-attachments/assets/bc383546-07b6-4c4c-97ca-5f3c14fb3b38)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTER_TO_STR_MEASURED` dient zur Konvertierung eines 2-Bit-Zustands (quarter Byte) in einen entsprechenden String. Dieser Block ist besonders nützlich, wenn Zustandsinformationen in einer menschenlesbaren Form ausgegeben werden sollen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit der Datenvariable `IB` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Der Ausgang ist mit der Datenvariable `STR` verknüpft.

### **Daten-Eingänge**
- `IB` (BYTE): Ein 2-Bit-Eingang, der vier verschiedene Zustände repräsentiert. Der Initialwert ist `quarter::STATUS_DISABLED`.

### **Daten-Ausgänge**
- `STR` (STRING): Der Ausgangsstring, der den aktuellen Zustand beschreibt. Der Initialwert ist `quarter::STATUS_DISABLED_msg`.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock empfängt über den `REQ`-Eingang eine Anfrage zur Konvertierung des Zustands `IB` in einen String. Abhängig vom Wert von `IB` wird einer der folgenden Algorithmen ausgeführt:
- **SET**: Setzt `STR` auf `quarter::STATUS_ENABLED_msg`.
- **RESET**: Setzt `STR` auf `quarter::STATUS_DISABLED_msg`.
- **ERROR**: Setzt `STR` auf `quarter::STATUS_ERROR_msg`.
- **NONE**: Setzt `STR` auf `quarter::STATUS_NOT_AVAILABLE_msg`.

Nach der Ausführung des entsprechenden Algorithmus wird das `CNF`-Ereignis ausgelöst, um die erfolgreiche Konvertierung zu bestätigen.

## Technische Besonderheiten
- Der Funktionsblock verwendet einen 2-Bit-Eingang (`IB`), um vier verschiedene Zustände zu repräsentieren.
- Die Ausgabe erfolgt als String, was die Interpretation der Zustände erleichtert.

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **START**: Initialzustand.
2. **SET**: Wird aktiviert, wenn `IB` den Wert `quarter::STATUS_ENABLED` hat.
3. **RESET**: Wird aktiviert, wenn `IB` den Wert `quarter::STATUS_DISABLED` hat.
4. **Error**: Wird aktiviert, wenn `IB` den Wert `quarter::STATUS_ERROR` hat.
5. **none**: Wird aktiviert, wenn `IB` den Wert `quarter::STATUS_NOT_AVAILABLE` hat.
6. **ok**: Wird nach erfolgreicher Ausführung des Algorithmus erreicht und löst das `CNF`-Ereignis aus.

## Anwendungsszenarien
- Anzeige von Maschinenzuständen in einer Benutzeroberfläche.
- Protokollierung von Zustandsänderungen in Logdateien.
- Kommunikation von Zustandsinformationen zwischen verschiedenen Systemkomponenten.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen bietet `QUARTER_TO_STR_MEASURED` eine spezialisierte Lösung für die Umwandlung von 2-Bit-Zuständen in Strings. Andere Bausteine könnten allgemeiner sein und mehr Flexibilität bieten, sind aber möglicherweise weniger effizient für diesen spezifischen Anwendungsfall.

## Fazit
Der `QUARTER_TO_STR_MEASURED`-Funktionsblock ist eine effiziente und spezialisierte Lösung für die Konvertierung von 2-Bit-Zuständen in menschenlesbare Strings. Er eignet sich besonders für Anwendungen, bei denen Zustandsinformationen klar und verständlich dargestellt werden müssen.
