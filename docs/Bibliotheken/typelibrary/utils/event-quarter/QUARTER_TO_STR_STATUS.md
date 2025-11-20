# QUARTER_TO_STR_STATUS

![QUARTER_TO_STR_STATUS](https://github.com/user-attachments/assets/0d2eac27-92a5-4c3e-ace2-942a671ca2a9)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTER_TO_STR_STATUS` dient der Konvertierung eines 2-Bit-Zustands (quarter Byte) in einen entsprechenden String. Dieser Block ist besonders nützlich, um Statusinformationen in einer lesbaren Form auszugeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IB` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung des Funktionsblocks. Der Ausgang ist mit dem Daten-Ausgang `STR` verknüpft.

### **Daten-Eingänge**
- `IB` (BYTE): Ein 2-Bit-Eingang, der vier verschiedene Zustände repräsentiert. Der Initialwert ist `quarter::COMMAND_DISABLE`.

### **Daten-Ausgänge**
- `STR` (STRING): Der Ausgang liefert eine String-Repräsentation des aktuellen Zustands. Der Initialwert ist `quarter::COMMAND_DISABLE_msg`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock reagiert auf das Ereignis `REQ` und überprüft den Wert des Eingangs `IB`. Abhängig vom Wert von `IB` wird einer der folgenden Algorithmen ausgeführt:
- `SET`: Wird ausgeführt, wenn `IB` den Wert `quarter::STATUS_ENABLED` hat.
- `RESET`: Wird ausgeführt, wenn `IB` den Wert `quarter::STATUS_DISABLED` hat.
- `ERROR`: Wird ausgeführt, wenn `IB` den Wert `quarter::STATUS_ERROR` hat.
- `NONE`: Wird ausgeführt, wenn `IB` den Wert `quarter::STATUS_NOT_AVAILABLE` hat.

Nach der Ausführung des entsprechenden Algorithmus wird das Ereignis `CNF` ausgelöst, und der Funktionsblock kehrt in den Startzustand zurück.

## Technische Besonderheiten
- Der Funktionsblock verwendet spezielle Konstanten (`quarter::COMMAND_ENABLE_msg`, `quarter::COMMAND_DISABLE_msg`, etc.), die in der zugrunde liegenden Implementierung definiert sein müssen.
- Die Zustandsübergänge sind deterministisch und hängen ausschließlich vom Wert des Eingangs `IB` ab.

## Zustandsübersicht
1. **START**: Initialzustand.
2. **SET**: Zustand für den Wert `quarter::STATUS_ENABLED`.
3. **RESET**: Zustand für den Wert `quarter::STATUS_DISABLED`.
4. **Error**: Zustand für den Wert `quarter::STATUS_ERROR`.
5. **none**: Zustand für den Wert `quarter::STATUS_NOT_AVAILABLE`.
6. **ok**: Zustand nach erfolgreicher Ausführung eines Algorithmus, der das Ereignis `CNF` auslöst.

## Anwendungsszenarien
- Konvertierung von Hardware-Statusbits in lesbare Strings für Benutzeroberflächen.
- Debugging und Protokollierung von Systemzuständen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Konvertierungsblöcken bietet `QUARTER_TO_STR_STATUS` eine spezialisierte Funktionalität für 2-Bit-Zustände mit vordefinierten String-Ausgaben.
- Andere Blöcke könnten allgemeinere Konvertierungen anbieten, sind aber möglicherweise weniger effizient oder spezifisch für diesen Anwendungsfall.

## Fazit
Der `QUARTER_TO_STR_STATUS`-Funktionsblock ist ein spezialisiertes Werkzeug zur Konvertierung von 2-Bit-Zuständen in lesbare Strings. Seine deterministische Funktionsweise und die klare Schnittstellenstruktur machen ihn zu einer zuverlässigen Komponente in Steuerungs- und Überwachungssystemen.
