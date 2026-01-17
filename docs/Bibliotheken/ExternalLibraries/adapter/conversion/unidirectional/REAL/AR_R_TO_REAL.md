# AR_R_TO_REAL

## Einleitung
Der AR_R_TO_REAL Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AR-Adapterformats in einen REAL-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: REAL-Ausgangswert der konvertierten Daten

### **Adapter**
- **AR_IN**: Socket vom Typ `AR`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AR-Adapter-Socket und stellt den enthaltenen REAL-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
