# DataPanel_LO_QX

* * * * * * * * * *

## Einleitung
Der DataPanel_LO_QX ist ein Ausgabeservice-Schnittstellen-Funktionsblock für boolesche Ausgabedaten. Er dient als Schnittstelle zwischen der Steuerungslogik und physischen Ausgabegeräten und ermöglicht die sichere Übertragung von booleschen Signalen an Ressourcen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **QI**: Event Input Qualifier (BOOL) - Qualifiziert die Ereigniseingänge
- **PARAMS**: Service Parameters (STRING) - Konfigurationsparameter für den Service
- **OUT**: Output data to resource (BOOL) - Ausgabedaten für die Ressource
- **u8SAMember**: Node SA 217..224 (USINT) - Knoten-SA-Mitglied mit Initialwert "LO::LO_00"
- **Output**: Identify the Output DigitalOutput_1A..4B (DataPanel_LO_DO_S) - Identifiziert den digitalen Ausgang mit Initialwert "DataPanel_LO_DO::Invalid"

### **Daten-Ausgänge**
- **QO**: Event Output Qualifier (BOOL) - Qualifiziert die Ereignisausgänge
- **STATUS**: Service Status (STRING) - Statusinformationen des Services

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert sich über das INIT-Ereignis und bestätigt die Initialisierung mit INITO. Über das REQ-Ereignis können boolesche Ausgabedaten (OUT) an die angeschlossene Ressource gesendet werden. Die Bestätigung der Operation erfolgt über das CNF-Ereignis. Der Block ermöglicht die spezifische Adressierung von digitalen Ausgängen (1A bis 4B) über den Output-Parameter.

## Technische Besonderheiten
- Unterstützt spezifische SA-Knoten-Adressierung (217-224)
- Enthält umfangreiche Statusrückmeldungen
- Initialisierung mit definierten Standardwerten
- Typisierte Ausgangsidentifikation über DataPanel_LO_DO_S

## Zustandsübersicht
Der Block durchläuft typische Service-Interface-Zustände: Nicht initialisiert → Initialisiert → Betriebsbereit. Nach erfolgreicher Initialisierung können Ausgabeanfragen verarbeitet werden.

## Anwendungsszenarien
- Ansteuerung von digitalen Ausgängen in Automatisierungssystemen
- Schnittstelle zu physischen Aktoren und Signalleuchten
- Integration in Steuerungssysteme mit spezifischen SA-Adressierungsanforderungen
- Projekte mit fortiss-basierten Automatisierungslösungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen booleschen Ausgabeblöcken bietet DataPanel_LO_QX erweiterte Funktionalität durch spezifische SA-Adressierung, detaillierte Statusrückmeldungen und parametrierbare Ausgangskonfiguration.

## Fazit
Der DataPanel_LO_QX ist ein robustes Service-Interface für boolesche Ausgaben mit erweiterten Konfigurationsmöglichkeiten und zuverlässiger Statusrückmeldung, ideal für komplexe Automatisierungsanwendungen mit spezifischen Hardware-Anforderungen.