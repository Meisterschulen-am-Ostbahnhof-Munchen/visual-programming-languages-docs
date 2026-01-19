# AS_SINT_TO_S

```{index} single: AS_SINT_TO_S
```

## Einleitung
Der AS_SINT_TO_S Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines SINT-Werts in das AS-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: SINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AS_OUT**: Plug vom Typ `AS`

## Funktionsweise
Der Funktionsblock empfängt einen SINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AS-Adapterformat um.