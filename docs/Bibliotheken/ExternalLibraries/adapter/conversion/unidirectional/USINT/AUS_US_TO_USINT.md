# AUS_US_TO_USINT

```{index} single: AUS_US_TO_USINT
```

## Einleitung
Der AUS_US_TO_USINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AUS-Adapterformats in einen USINT-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: USINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **AUS_IN**: Socket vom Typ `AUS`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AUS-Adapter-Socket und stellt den enthaltenen USINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).