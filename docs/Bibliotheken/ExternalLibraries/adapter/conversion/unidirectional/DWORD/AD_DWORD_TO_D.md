# AD_DWORD_TO_D

```{index} single: AD_DWORD_TO_D
```

## Einleitung
Der AD_DWORD_TO_D Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines DWORD-Werts in das AD-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: DWORD-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AD_OUT**: Plug vom Typ `AD`

## Funktionsweise
Der Funktionsblock empfängt einen DWORD-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AD-Adapterformat um.