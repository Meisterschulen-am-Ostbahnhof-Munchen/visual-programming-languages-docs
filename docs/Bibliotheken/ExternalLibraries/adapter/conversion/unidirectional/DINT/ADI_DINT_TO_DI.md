# ADI_DINT_TO_DI

```{index} single: ADI_DINT_TO_DI
```

## Einleitung
Der ADI_DINT_TO_DI Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines DINT-Werts in das ADI-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: DINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **ADI_OUT**: Plug vom Typ `ADI`

## Funktionsweise
Der Funktionsblock empfängt einen DINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das ADI-Adapterformat um.