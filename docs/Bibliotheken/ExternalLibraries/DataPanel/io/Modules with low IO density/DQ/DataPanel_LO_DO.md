# DataPanel_LO_DO

```{index} single: DataPanel_LO_DO
```

* * * * * * * * * *
## Einleitung
DataPanel_LO_DO ist eine globale Konstantendefinition für DataPanel-Module mit niedriger I/O-Dichte für digitale Ausgänge (DO). Die Konstante definiert eine strukturierte Zuordnung von Pin-Nummern zu spezifischen digitalen Ausgangskanälen und stellt einen ungültigen Zustand für Fehlerbehandlung bereit.

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
Die globale Konstante DataPanel_LO_DO definiert eine Sammlung von strukturierten Konstanten vom Typ `DataPanel_LO_DO_S`, die digitale Ausgangskanäle eines DataPanel-Moduls mit niedriger I/O-Dichte repräsentieren. Jede Konstante enthält eine Pin-Zuordnung für spezifische Ausgangskanäle.

## Technische Besonderheiten
- **Datentyp**: Verwendet den strukturierten Datentyp `DataPanel_LO_DO_S`
- **Pin-Zuordnung**: Definiert 8 digitale Ausgangskanäle (1A-4B) mit fortlaufenden Pin-Nummern 1-8
- **Fehlerbehandlung**: Enthält eine spezielle `Invalid`-Konstante mit Pin-Wert 255 für ungültige Zustände
- **Modulare Struktur**: Kanalbenennung folgt dem Muster "DigitalOutput_XY" für klare Identifikation

## Zustandsübersicht
*Nicht zutreffend - Es handelt sich um eine statische Konstantendefinition ohne Zustandsautomaten*

## Anwendungsszenarien
- Konfiguration von DataPanel-Modulen mit niedriger I/O-Dichte
- Vereinfachte Pin-Zuordnung in Steuerungsprogrammen
- Typsichere Verwendung von digitalen Ausgangskanälen
- Fehlerbehandlung durch definierte ungültige Zustände

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen I/O-Konstantendefinitionen bietet DataPanel_LO_DO:
- Spezifische Anpassung für Module mit niedriger I/O-Dichte
- Strukturierte Datentypen für bessere Typsicherheit
- Klare Benennungskonvention für bessere Lesbarkeit
- Integrierte Fehlerkonstante für robustere Programmierung

## Fazit
DataPanel_LO_DO stellt eine effiziente und typsichere Lösung für die Konfiguration digitaler Ausgangskanäle in DataPanel-Modulen mit niedriger I/O-Dichte dar. Durch die strukturierte Definition und klare Pin-Zuordnung ermöglicht sie eine wartungsfreundliche und fehlerresistente Programmierung von Steuerungsanwendungen.