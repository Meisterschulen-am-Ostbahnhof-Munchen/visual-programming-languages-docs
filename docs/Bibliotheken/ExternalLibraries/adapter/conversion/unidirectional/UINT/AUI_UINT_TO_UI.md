# AUI_UINT_TO_UI

## Einleitung
Der AUI_UINT_TO_UI Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines UINT-Werts in das AUI-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: UINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AUI_OUT**: Plug vom Typ `AUI`

## Funktionsweise
Der Funktionsblock empfängt einen UINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AUI-Adapterformat um.
