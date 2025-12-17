# Aux_QD

<img width="1484" height="176" alt="image" src="https://github.com/user-attachments/assets/ddafadb6-6b79-43d3-9d30-dc888d6fca95" />

* * * * * * * * * *

## Einleitung
Der Aux_QD Funktionsblock ist ein Ausgabeservice-Interface-Baustein für die Verarbeitung von Doppelwort-Ausgabedaten (DWORD). Er dient als Schnittstelle für Auxiliary-Ausgabefunktionen und unterstützt verschiedene Auxiliary-Typen zur flexiblen Datenausgabe.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **OUT** (DWORD): Ausgabedaten für die Ressource
- **iInpNr** (INT): Nummer des Auxiliary-Arrays (entspricht der Reihenfolge im Pool, Startwert: 0)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Aux_QD-Block verarbeitet Doppelwort-Daten (32-Bit) und gibt diese über Auxiliary-Schnittstellen aus. Bei der Initialisierung (INIT) werden die Service-Parameter konfiguriert. Über das REQ-Ereignis werden die Ausgabedaten an die entsprechende Ressource gesendet. Der Block unterstützt mehrere Auxiliary-Typen und ermöglicht die parallele Ausgabe beider Werte in einer Operation.

## Technische Besonderheiten
- Unterstützt Auxiliary-Typen: 0, 1, 2, 3, 4, 6, 11, 12, 13
- Verarbeitet 32-Bit DWORD-Daten
- Initialwert für iInpNr ist 0 (erstes Auxiliary-Array im Pool)
- Parallele Ausgabe beider Werte in einer Operation möglich

## Zustandsübersicht
Der Block verfügt über zwei Hauptzustände:
1. **Initialisierungszustand**: Verarbeitung der INIT-Anfrage mit Parameterkonfiguration
2. **Betriebszustand**: Verarbeitung von REQ-Anfragen mit Datenausgabe

## Anwendungsszenarien
- ISOBUS-kompatible Steuerungssysteme
- Landwirtschaftliche Maschinensteuerungen
- Industrielle Automatisierungssysteme
- Embedded Systems mit Auxiliary-Schnittstellen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Ausgabeblöcken bietet Aux_QD erweiterte Funktionen für Auxiliary-Schnittstellen und unterstützt spezifische ISOBUS-kompatible Datentypen. Die parallele Ausgabefähigkeit unterscheidet ihn von sequenziellen Ausgabeblöcken.

## Fazit
Der Aux_QD Funktionsblock stellt eine leistungsstarke Lösung für die Ausgabe von Doppelwort-Daten über Auxiliary-Schnittstellen dar. Seine ISOBUS-Kompatibilität und die Unterstützung verschiedener Auxiliary-Typen machen ihn besonders geeignet für anspruchsvolle Automatisierungsanwendungen in industriellen und mobilen Systemen.
