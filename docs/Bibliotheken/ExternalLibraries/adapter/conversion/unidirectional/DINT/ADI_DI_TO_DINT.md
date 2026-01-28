# ADI_DI_TO_DINT

```{index} single: ADI_DI_TO_DINT
```

## Einleitung
Der ADI_DI_TO_DINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des ADI-Adapterformats in einen DINT-Wert dient.

![ADI_DI_TO_DINT](ADI_DI_TO_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: DINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **ADI_IN**: Socket vom Typ `ADI`

## Funktionsweise
Der Funktionsblock empfängt Daten über den ADI-Adapter-Socket und stellt den enthaltenen DINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).