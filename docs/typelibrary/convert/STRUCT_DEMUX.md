# STRUCT_DEMUX

<img width="1196" height="182" alt="STRUCT_DEMUX" src="https://github.com/user-attachments/assets/2420186b-20ea-4920-85e4-746488942325" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock STRUCT_DEMUX dient zum Demultiplexen von strukturierten Daten. Er ermöglicht die Verarbeitung von beliebigen strukturierten Datentypen (ANY_STRUCT) und gibt diese über seine Ausgänge weiter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die normale Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang IN verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung des Funktionsblocks.

### **Daten-Eingänge**
- **IN**: Erwartet einen beliebigen strukturierten Datentyp (ANY_STRUCT) als Eingabe.

### **Daten-Ausgänge**
(Der Funktionsblock hat keine explizit definierten Daten-Ausgänge in der Schnittstelle)

### **Adapter**
(Der Funktionsblock verwendet keine Adapter)

## Funktionsweise
Der STRUCT_DEMUX Funktionsblock empfängt strukturierte Daten über den Eingang IN, wenn das REQ-Ereignis ausgelöst wird. Nach der Verarbeitung bestätigt er die Ausführung durch das CNF-Ereignis. Die genaue Verarbeitungslogik hängt von der konkreten Implementierung ab.

## Technische Besonderheiten
- Unterstützt beliebige strukturierte Datentypen (ANY_STRUCT)
- Generische Implementierung (GEN_STRUCT_DEMUX)
- Service Interface Function Block Type

## Zustandsübersicht
1. Wartezustand: Auf REQ-Ereignis warten
2. Verarbeitungszustand: Daten von IN verarbeiten
3. Bestätigungszustand: CNF-Ereignis auslösen

## Anwendungsszenarien
- Verteilung von strukturierten Daten an verschiedene Verarbeitungskomponenten
- Demultiplexing von komplexen Datentypen
- Als Teil von Datenverarbeitungsketten in Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen DEMUX-Blöcken kann STRUCT_DEMUX mit komplexen strukturierten Datentypen umgehen, während einfache DEMUX-Blöcke typischerweise nur mit grundlegenden Datentypen arbeiten.

## Fazit
STRUCT_DEMUX ist ein flexibler Funktionsblock für die Verarbeitung strukturierter Daten in 4diac-basierten Automatisierungssystemen. Seine generische Implementierung ermöglicht den Einsatz in verschiedenen Szenarien, die komplexe Datenstrukturen erfordern.
