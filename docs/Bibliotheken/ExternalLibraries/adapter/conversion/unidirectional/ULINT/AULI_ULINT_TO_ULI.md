# AULI_ULINT_TO_ULI

```{index} single: AULI_ULINT_TO_ULI
```

## Einleitung
Der AULI_ULINT_TO_ULI Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines ULINT-Werts in das AULI-Adapterformat dient.

![AULI_ULINT_TO_ULI](AULI_ULINT_TO_ULI.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: ULINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AULI_OUT**: Plug vom Typ `AULI`

## Funktionsweise
Der Funktionsblock empfängt einen ULINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AULI-Adapterformat um.