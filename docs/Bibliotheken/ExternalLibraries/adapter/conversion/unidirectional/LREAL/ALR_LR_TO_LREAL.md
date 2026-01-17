# ALR_LR_TO_LREAL

## Einleitung
Der ALR_LR_TO_LREAL Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des ALR-Adapterformats in einen LREAL-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: LREAL-Ausgangswert der konvertierten Daten

### **Adapter**
- **ALR_IN**: Socket vom Typ `ALR`

## Funktionsweise
Der Funktionsblock empfängt Daten über den ALR-Adapter-Socket und stellt den enthaltenen LREAL-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
