# AL_L_TO_LWORD

```{index} single: AL_L_TO_LWORD
```

## Einleitung
Der AL_L_TO_LWORD Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AL-Adapterformats in einen LWORD-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: LWORD-Ausgangswert der konvertierten Daten

### **Adapter**
- **AL_IN**: Socket vom Typ `AL`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AL-Adapter-Socket und stellt den enthaltenen LWORD-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).