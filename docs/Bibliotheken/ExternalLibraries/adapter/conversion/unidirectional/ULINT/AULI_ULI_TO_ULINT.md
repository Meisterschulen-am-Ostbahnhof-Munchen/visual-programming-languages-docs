# AULI_ULI_TO_ULINT

```{index} single: AULI_ULI_TO_ULINT
```

## Einleitung
Der AULI_ULI_TO_ULINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AULI-Adapterformats in einen ULINT-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: ULINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **AULI_IN**: Socket vom Typ `AULI`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AULI-Adapter-Socket und stellt den enthaltenen ULINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
