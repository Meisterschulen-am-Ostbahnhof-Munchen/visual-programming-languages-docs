# AS_S_TO_SINT

```{index} single: AS_S_TO_SINT
```

## Einleitung
Der AS_S_TO_SINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AS-Adapterformats in einen SINT-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: SINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **AS_IN**: Socket vom Typ `AS`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AS-Adapter-Socket und stellt den enthaltenen SINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
