# Funk_DI

```{index} single: Funk_DI
```

* * * * * * * * * *
## Einleitung
Funk_DI ist ein GlobalConstants-Paket für die 4diac-IDE, das Konstanten für digitale Eingänge in Funksystemen definiert. Das Paket stellt vordefinierte Pin-Konfigurationen für verschiedene digitale Eingangssignale zur Verfügung, die in Steuerungsanwendungen verwendet werden können.

## Schnittstellenstruktur
Da es sich bei Funk_DI um ein GlobalConstants-Paket handelt, verfügt es über keine klassischen Funktionsblock-Schnittstellen. Stattdessen werden globale Konstanten bereitgestellt.

### **Ereignis-Eingänge**
Nicht verfügbar - GlobalConstants-Paket

### **Ereignis-Ausgänge**
Nicht verfügbar - GlobalConstants-Paket

### **Daten-Eingänge**
Nicht verfügbar - GlobalConstants-Paket

### **Daten-Ausgänge**
Nicht verfügbar - GlobalConstants-Paket

### **Adapter**
Nicht verfügbar - GlobalConstants-Paket

## Funktionsweise
Das Funk_DI-Paket definiert eine Sammlung von globalen Konstanten vom Typ `Funk_DI_S`, die digitale Eingangspins repräsentieren. Jede Konstante enthält eine Pin-Nummer, die den physischen oder logischen Eingang identifiziert. Die Konstanten können in anderen Funktionsblöcken verwendet werden, um auf spezifische digitale Eingänge zu verweisen.

## Technische Besonderheiten
- **Pin-Zuordnungen**: Die Pin-Nummern folgen einem spezifischen Schema:
  - Standard-Eingänge: Pin 1-15
  - Spezielle Funktionen: Pin 0 (STOP), Pin 25 (START)
  - Systemfunktionen: Pin -1 (STATUS), Pin -6 (COUNTER)
  - Ungültiger Wert: Pin 127 (Invalid)

- **Datentyp**: Alle Konstanten verwenden den strukturierten Datentyp `Funk_DI_S`

- **Paketstruktur**: Organisiert im Namespace `Funk::io::DI`

## Zustandsübersicht
Da es sich um ein Konstanten-Paket handelt, gibt es keine Zustandsübergänge. Alle Werte sind zur Kompilierzeit fest definiert und unveränderlich.

## Anwendungsszenarien
- **Konfiguration digitaler Eingänge**: Vereinfachte Konfiguration von digitalen Eingängen in Steuerungsanwendungen
- **Standardisierung**: Sicherstellung konsistenter Pin-Zuordnungen über verschiedene Projekte hinweg
- **Wartbarkeit**: Zentrale Verwaltung aller digitaler Eingangskonfigurationen
- **Funksysteme**: Speziell für Anwendungen in drahtlosen Steuerungssystemen entwickelt

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen digitalen Eingangs-Konstantenpaketen bietet Funk_DI:
- Spezifische Pin-Zuordnungen für Funksysteme
- Vordefinierte Konstanten für spezielle Funktionen (START, STOP, STATUS, COUNTER)
- Strukturierte Organisation im IO-Bereich des Funk-Namespace

## Fazit
Das Funk_DI GlobalConstants-Paket bietet eine praktische Sammlung vordefinierter Konstanten für digitale Eingänge in Funksystemen. Durch die standardisierten Pin-Zuordnungen und die klare Namensgebung ermöglicht es eine effiziente und wartungsfreundliche Konfiguration von Steuerungsanwendungen. Die speziellen Funktionen wie START, STOP und STATUS machen es besonders geeignet für industrielle Steuerungsanwendungen mit drahtlosen Komponenten.
