# DataPanel_MI_QX

* * * * * * * * * *

## Einleitung
Der DataPanel_MI_QX ist ein Service Interface Function Block für die Ausgabe von booleschen Daten. Dieser Baustein dient als Schnittstelle zwischen der Steuerungslogik und physischen Ausgabegeräten und ermöglicht die Steuerung von digitalen Ausgängen über definierte Service-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifikator
- **PARAMS** (STRING): Service-Parameter
- **OUT** (BOOL): Ausgabedaten an die Ressource
- **u8SAMember** (USINT): Knoten SA 224..239, Initialwert: MI::MI_00
- **Output** (DataPanel_MI_DO_S): Identifiziert den Ausgang (DigitalOutput_1A..8B und Input_Power_Port_5..8), Initialwert: DataPanel_MI_DO::Invalid

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifikator
- **STATUS** (STRING): Service-Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der DataPanel_MI_QX Function Block verarbeitet Service-Anfragen für die Ausgabe boolescher Daten. Bei der Initialisierung (INIT-Event) werden die Service-Parameter konfiguriert und der Baustein für den Betrieb vorbereitet. Über das REQ-Event können Ausgabeoperationen angefordert werden, wobei die booleschen Daten über den OUT-Eingang bereitgestellt werden. Der Baustein bestätigt erfolgreiche Operationen über die entsprechenden Ausgangsereignisse INITO und CNF.

## Technische Besonderheiten
- Unterstützt spezifische Ausgangskonfigurationen über den Output-Datentyp
- Ermöglicht die Adressierung verschiedener Knoten über u8SAMember
- Bietet detaillierte Statusrückmeldungen über den STATUS-Ausgang
- Initialisierung mit spezifischen Standardwerten für robusten Betrieb

## Zustandsübersicht
Der Baustein verfügt über folgende Hauptzustände:
- **Nicht initialisiert**: Vor der ersten INIT-Operation
- **Initialisiert**: Nach erfolgreicher INIT-Operation, bereit für REQ-Operationen
- **Aktiv**: Während der Verarbeitung von Service-Anfragen

## Anwendungsszenarien
- Steuerung digitaler Ausgänge in Automatisierungssystemen
- Anbindung an physische Aktoren über definierte Service-Schnittstellen
- Integration in verteilte Steuerungssysteme mit spezifischen Knotenadressen
- Überwachung und Steuerung von Leistungsports

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen booleschen Ausgabeblöcken bietet DataPanel_MI_QX erweiterte Service-Funktionalität mit parametrierbaren Konfigurationen und detaillierten Statusrückmeldungen. Die spezifische Ausgangsidentifikation ermöglicht präzisere Steuerung als generische Ausgabeblöcke.

## Fazit
Der DataPanel_MI_QX Function Block stellt eine leistungsfähige und flexible Lösung für die Steuerung boolescher Ausgabedaten in industriellen Automatisierungssystemen dar. Durch seine Service-orientierte Architektur und umfangreiche Konfigurationsmöglichkeiten eignet er sich besonders für anspruchsvolle Anwendungen mit spezifischen Hardware-Anforderungen.