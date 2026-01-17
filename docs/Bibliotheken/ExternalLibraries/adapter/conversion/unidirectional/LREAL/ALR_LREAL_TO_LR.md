# ALR_LREAL_TO_LR

## Einleitung
Der ALR_LREAL_TO_LR Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines LREAL-Werts in das ALR-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: LREAL-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **ALR_OUT**: Plug vom Typ `ALR`

## Funktionsweise
Der Funktionsblock empfängt einen LREAL-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das ALR-Adapterformat um.
