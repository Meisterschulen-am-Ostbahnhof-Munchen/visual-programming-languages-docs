# Aux_QXA

<img width="1474" height="164" alt="image" src="https://github.com/user-attachments/assets/d340aff6-bc76-425a-b4a7-5e628255f4a6" />

* * * * * * * * * *

## Einleitung
Der Aux_QXA ist ein zusammengesetzter Funktionsblock für die Ausgabe von booleschen Daten. Er dient als Schnittstelle für Hilfsausgänge (Auxiliary Outputs) in ISOBUS-kompatiblen Systemen und ermöglicht die Steuerung von booleschen Ausgabesignalen über standardisierte Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
  - Verknüpft mit: QI, PARAMS, iInpNr

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **CNF**: Bestätigung des angeforderten Services
  - Verknüpft mit: QO, STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **iInpNr** (INT): Nummer des Hilfsausgangs-Arrays (entspricht der Reihenfolge im Pool, wobei der erste Hilfseingang iInpNr = 0 hat)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Status

### **Adapter**
- **OUT**: Unidirektionaler Adapter vom Typ AX
  - Position: x="-400", y="1000"

## Funktionsweise
Der Aux_QXA Funktionsblock fungiert als Wrapper für den internen Aux_QX Baustein. Bei Initialisierung (INIT-Ereignis) werden die Konfigurationsparameter übergeben und der interne Baustein initialisiert. Über den OUT-Adapter können Ausgabeanforderungen gesendet werden, die dann vom internen Baustein verarbeitet werden. Die Bestätigung erfolgt über die CNF- und INITO-Ausgangsereignisse.

## Technische Besonderheiten
- Verwendet einen unidirektionalen Adapter für die Ausgabekommunikation
- Unterstützt parametrierbare Service-Konfiguration über STRING-Parameter
- Ermöglicht die Adressierung mehrerer Hilfsausgänge über den iInpNr-Parameter
- Implementiert standardisierte Initialisierungs- und Bestätigungsprotokolle

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor dem INIT-Ereignis
2. **Initialisierung**: Während der INIT-Verarbeitung
3. **Bereit**: Nach erfolgreicher Initialisierung (INITO)
4. **Aktiv**: Während der Ausgabeverarbeitung (CNF)

## Anwendungsszenarien
- Steuerung von booleschen Aktoren in landwirtschaftlichen Maschinen
- ISOBUS-kompatible Hilfsausgänge in Traktoren und Anbaugeräten
- Automatisierte Steuerungssysteme in der Agrartechnik
- Vernetzte Steuerung von Peripheriegeräten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen booleschen Ausgabeblöcken bietet Aux_QXA:
- Erweiterte Parametrierbarkeit über STRING-Parameter
- ISOBUS-Kompatibilität
- Standardisierte Initialisierungsprozeduren
- Adapter-basierte Schnittstelle für erweiterte Kommunikation

## Fazit
Der Aux_QXA Funktionsblock stellt eine robuste und standardkonforme Lösung für die Steuerung von booleschen Hilfsausgängen in ISOBUS-Systemen dar. Durch seine modulare Architektur und erweiterte Parametrierungsmöglichkeiten eignet er sich besonders für komplexe Steuerungsaufgaben in der modernen Agrartechnik.
