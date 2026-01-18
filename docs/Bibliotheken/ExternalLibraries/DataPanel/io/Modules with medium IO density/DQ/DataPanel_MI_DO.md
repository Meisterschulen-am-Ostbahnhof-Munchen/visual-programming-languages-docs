# DataPanel_MI_DO

```{index} single: DataPanel_MI_DO
```

* * * * * * * * * *

## Einleitung
DataPanel_MI_DO ist eine globale Konstantendefinition für DataPanel-Module mit mittlerer I/O-Dichte für digitale Ausgänge (Digital Output). Die Konstante definiert eine strukturierte Zuordnung von Pins für verschiedene digitale Ausgangskanäle und Stromversorgungsports.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Nicht vorhanden - Es handelt sich um eine globale Konstantendefinition*

### **Ereignis-Ausgänge**
*Nicht vorhanden - Es handelt sich um eine globale Konstantendefinition*

### **Daten-Eingänge**
*Nicht vorhanden - Es handelt sich um eine globale Konstantendefinition*

### **Daten-Ausgänge**
*Nicht vorhanden - Es handelt sich um eine globale Konstantendefinition*

### **Adapter**
*Nicht vorhanden - Es handelt sich um eine globale Konstantendefinition*

## Funktionsweise
Die globale Konstante DataPanel_MI_DO definiert feste Pin-Zuordnungen für ein DataPanel-Modul mit mittlerer I/O-Dichte. Jede Konstante repräsentiert einen spezifischen Ausgangskanal oder Stromversorgungsport und weist diesem einen festen Pin-Wert zu. Die Struktur basiert auf dem Datentyp `DataPanel_MI_DO_S` mit einem Pin-Feld.

## Technische Besonderheiten
- Definiert 16 digitale Ausgangskanäle (1A-8B) mit Pin-Zuordnungen 1-16
- Enthält 4 Stromversorgungsports (Input_Power_Port_5-8) mit Pin-Zuordnungen 17-20
- Bereitstellung einer Invalid-Konstante mit Pin-Wert 255 für Fehlerbehandlung
- Strukturierte Organisation in Paaren (A/B) für bessere Übersichtlichkeit
- Feste Pin-Zuordnungen garantieren konsistente Hardware-Ansteuerung

## Zustandsübersicht
*Nicht zutreffend - Es handelt sich um statische Konstantendefinitionen*

## Anwendungsszenarien
- Hardware-Konfiguration von DataPanel-Modulen mit mittlerer I/O-Dichte
- Vereinfachung der Pin-Zuordnung in Steuerungsprogrammen
- Wiederverwendbare Konstantendefinitionen in größeren Automatisierungsprojekten
- Hardware-abstrakte Programmierung durch symbolische Pin-Namen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einzelnen Pin-Definitionen bietet diese globale Konstante:
- Zentrale Verwaltung aller Pin-Zuordnungen
- Typisierte Zugriffsmöglichkeiten durch strukturierte Datentypen
- Bessere Wartbarkeit und Lesbarkeit des Codes
- Konsistente Namenskonventionen über das gesamte Projekt

## Fazit
DataPanel_MI_DO bietet eine effiziente und strukturierte Möglichkeit, die Pin-Zuordnungen für DataPanel-Module mit mittlerer digitaler Ausgangsdichte zu verwalten. Durch die Verwendung globaler Konstanten wird die Code-Wartbarkeit verbessert und Hardware-Änderungen können zentral verwaltet werden.
