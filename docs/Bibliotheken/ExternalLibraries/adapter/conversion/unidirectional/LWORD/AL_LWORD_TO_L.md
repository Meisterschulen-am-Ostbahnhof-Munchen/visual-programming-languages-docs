# AL_LWORD_TO_L

```{index} single: AL_LWORD_TO_L
```

## Einleitung
Der AL_LWORD_TO_L Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines LWORD-Werts in das AL-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: LWORD-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AL_OUT**: Plug vom Typ `AL`

## Funktionsweise
Der Funktionsblock empfängt einen LWORD-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AL-Adapterformat um.