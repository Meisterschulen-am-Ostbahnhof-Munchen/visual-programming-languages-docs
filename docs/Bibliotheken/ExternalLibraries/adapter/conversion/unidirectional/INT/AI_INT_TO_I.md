# AI_INT_TO_I

```{index} single: AI_INT_TO_I
```

## Einleitung
Der AI_INT_TO_I Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines INT-Werts in das AI-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: INT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AI_OUT**: Plug vom Typ `AI`

## Funktionsweise
Der Funktionsblock empfängt einen INT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AI-Adapterformat um.
