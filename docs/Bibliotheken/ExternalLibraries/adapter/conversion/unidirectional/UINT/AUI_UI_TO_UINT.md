# AUI_UI_TO_UINT

## Einleitung
Der AUI_UI_TO_UINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AUI-Adapterformats in einen UINT-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: UINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **AUI_IN**: Socket vom Typ `AUI`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AUI-Adapter-Socket und stellt den enthaltenen UINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).
