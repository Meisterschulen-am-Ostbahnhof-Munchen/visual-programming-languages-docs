# AW_W_TO_WORD

```{index} single: AW_W_TO_WORD
```

## Einleitung
Der AW_W_TO_WORD Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AW-Adapterformats in einen WORD-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: WORD-Ausgangswert der konvertierten Daten

### **Adapter**
- **AW_IN**: Socket vom Typ `AW`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AW-Adapter-Socket und stellt den enthaltenen WORD-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
