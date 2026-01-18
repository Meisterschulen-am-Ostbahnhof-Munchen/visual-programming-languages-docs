# RT_Bridge_10

```{index} single: RT_Bridge_10
```

* * * * * * * * * *

## Einleitung
Der RT_Bridge_10 Funktionsblock dient als Entkopplungsbrücke für 10 Datenverbindungen zwischen Echtzeit-Ereignisketten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **RD**: Daten lesen.
- **WR**: Daten schreiben.

### **Ereignis-Ausgänge**
- **RDO**: Lese-Bestätigung.

### **Daten-Eingänge**
- **SD_1** - **SD_10** (ANY): Eingangsdaten.

### **Daten-Ausgänge**
- **RD_1** - **RD_10** (ANY): Ausgangsdaten.

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2023 Johannes Kepler University Linz |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac-Paket | eclipse4diac::rtevents |