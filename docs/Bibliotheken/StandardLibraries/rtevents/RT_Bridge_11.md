# RT_Bridge_11

```{index} single: RT_Bridge_11
```

* * * * * * * * * *

## Einleitung
Der RT_Bridge_11 Funktionsblock dient als Entkopplungsbrücke für 11 Datenverbindungen zwischen Echtzeit-Ereignisketten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **RD**: Daten lesen.
- **WR**: Daten schreiben.

### **Ereignis-Ausgänge**
- **RDO**: Lese-Bestätigung.

### **Daten-Eingänge**
- **SD_1** - **SD_11** (ANY): Eingangsdaten.

### **Daten-Ausgänge**
- **RD_1** - **RD_11** (ANY): Ausgangsdaten.

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2023 Johannes Kepler University Linz |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac-Paket | eclipse4diac::rtevents |