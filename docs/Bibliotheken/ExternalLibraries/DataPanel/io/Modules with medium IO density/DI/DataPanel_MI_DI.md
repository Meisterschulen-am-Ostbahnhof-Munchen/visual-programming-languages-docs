# DataPanel_MI_DI

```{index} single: DataPanel_MI_DI
```

* * * * * * * * * *

## Einleitung
DataPanel_MI_DI ist eine globale Konstantendefinition für DataPanel-Module mit mittlerer I/O-Dichte für digitale Eingänge (DI). Diese Konstante definiert die Pin-Zuordnungen für verschiedene digitale Eingangskanäle eines DataPanel-Systems.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereigniseingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignisausgänge vorhanden*

### **Daten-Eingänge**
*Keine Dateneingänge vorhanden*

### **Daten-Ausgänge**
*Keine Datenausgänge vorhanden*

### **Adapter**
*Keine Adapter vorhanden*

## Funktionsweise
Bei DataPanel_MI_DI handelt es sich um eine globale Konstantendefinition, die feste Werte für die Pin-Zuordnungen der digitalen Eingänge bereitstellt. Die Konstante definiert strukturierte Daten vom Typ `DataPanel_MI_DI_S` mit Pin-Nummern für verschiedene digitale Eingangskanäle.

## Technische Besonderheiten
- Definiert Pin-Zuordnungen für 8 digitale Eingangskanäle (5A, 5B, 6A, 6B, 7A, 7B, 8A, 8B)
- Pin-Nummern reichen von 9 bis 16
- Enthält eine spezielle "Invalid"-Konstante mit Pin-Wert 255 für Fehlerbehandlung
- Verwendet den strukturierten Datentyp `DataPanel_MI_DI_S`
- Organisiert im Package `DataPanel::io::MI::DI`

## Zustandsübersicht
*Keine Zustandsübergänge vorhanden - handelt es sich um eine statische Konstantendefinition*

## Anwendungsszenarien
- Konfiguration von DataPanel-Systemen mit mittlerer I/O-Dichte
- Hardware-Abstraktion für digitale Eingänge in Steuerungssystemen
- Vereinfachung der Pin-Zuordnung in IEC 61499-basierten Anwendungen
- Wiederverwendbare Konstantendefinition für mehrere Projekte

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konstantendefinitionen bietet DataPanel_MI_DI:
- Spezifische Pin-Zuordnungen für DataPanel-Hardware
- Strukturierte Datentypen für bessere Typsicherheit
- Vordefinierte Invalid-Konstante für Robustheit

## Fazit
DataPanel_MI_DI stellt eine standardisierte und typsichere Möglichkeit dar, digitale Eingangspins in DataPanel-Systemen mit mittlerer I/O-Dichte zu konfigurieren. Die Verwendung strukturierter Konstanten erhöht die Wartbarkeit und Reduziert Konfigurationsfehler in Automatisierungsprojekten.