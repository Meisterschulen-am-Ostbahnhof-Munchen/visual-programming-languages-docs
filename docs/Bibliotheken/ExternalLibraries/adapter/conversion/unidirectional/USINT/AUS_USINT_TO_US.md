# AUS_USINT_TO_US

```{index} single: AUS_USINT_TO_US
```

## Einleitung
Der AUS_USINT_TO_US Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines USINT-Werts in das AUS-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: USINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AUS_OUT**: Plug vom Typ `AUS`

## Funktionsweise
Der Funktionsblock empfängt einen USINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AUS-Adapterformat um.