# RT_Bridge_1

* * * * * * * * * *

## Einleitung
Der RT_Bridge_1 Funktionsblock dient als Entkopplungsbrücke für eine Datenverbindung zwischen Echtzeit-Ereignisketten. Er ermöglicht den sicheren Datenaustausch zwischen verschiedenen Ausführungskontexten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **RD**: Daten aus der Brücke lesen.
- **WR**: Daten in die Brücke schreiben.

### **Ereignis-Ausgänge**
- **RDO**: Benachrichtigung über gelesene Daten.

### **Daten-Eingänge**
- **SD_1** (ANY): Daten, die in die Brücke geschrieben werden sollen.

### **Daten-Ausgänge**
- **RD_1** (ANY): Daten, die aus der Brücke gelesen wurden.

## Funktionsweise
Der Baustein speichert die über `WR` empfangenen Daten zwischen und stellt sie bei `RD` am Ausgang zur Verfügung. Dies entkoppelt den Schreib- vom Leseprozess zeitlich.

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2023 Johannes Kepler University Linz |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac-Paket | eclipse4diac::rtevents |
