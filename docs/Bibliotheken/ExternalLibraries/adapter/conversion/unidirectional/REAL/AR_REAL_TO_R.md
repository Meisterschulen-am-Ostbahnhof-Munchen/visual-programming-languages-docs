# AR_REAL_TO_R

```{index} single: AR_REAL_TO_R
```

## Einleitung
Der AR_REAL_TO_R Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines REAL-Werts in das AR-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: REAL-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AR_OUT**: Plug vom Typ `AR`

## Funktionsweise
Der Funktionsblock empfängt einen REAL-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AR-Adapterformat um.
