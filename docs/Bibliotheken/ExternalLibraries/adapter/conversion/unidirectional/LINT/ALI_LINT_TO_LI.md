# ALI_LINT_TO_LI

```{index} single: ALI_LINT_TO_LI
```

## Einleitung
Der ALI_LINT_TO_LI Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines LINT-Werts in das ALI-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: LINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **ALI_OUT**: Plug vom Typ `ALI`

## Funktionsweise
Der Funktionsblock empfängt einen LINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das ALI-Adapterformat um.