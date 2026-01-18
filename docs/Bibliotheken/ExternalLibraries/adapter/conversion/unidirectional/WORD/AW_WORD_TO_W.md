# AW_WORD_TO_W

```{index} single: AW_WORD_TO_W
```

## Einleitung
Der AW_WORD_TO_W Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines WORD-Werts in das AW-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: WORD-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AW_OUT**: Plug vom Typ `AW`

## Funktionsweise
Der Funktionsblock empfängt einen WORD-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AW-Adapterformat um.
