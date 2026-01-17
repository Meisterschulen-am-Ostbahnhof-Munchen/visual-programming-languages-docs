# ALI_LI_TO_LINT

## Einleitung
Der ALI_LI_TO_LINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des ALI-Adapterformats in einen LINT-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: LINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **ALI_IN**: Socket vom Typ `ALI`

## Funktionsweise
Der Funktionsblock empfängt Daten über den ALI-Adapter-Socket und stellt den enthaltenen LINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
