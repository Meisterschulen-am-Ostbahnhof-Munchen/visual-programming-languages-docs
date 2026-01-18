# DataPanel_LO_QX

```{index} single: DataPanel_LO_QX
```

<img width="1457" height="259" alt="image" src="https://github.com/user-attachments/assets/80fc4f29-178a-42f5-a007-1361dfa8834e" />

* * * * * * * * * *

## Einleitung
Der DataPanel_LO_QX ist ein Ausgabeservice-Schnittstellen-Funktionsblock für boolesche Ausgabedaten, der speziell für die Kommunikation mit Digitalausgängen in Automatisierungssystemen entwickelt wurde. Der Baustein ermöglicht die sichere und kontrollierte Ausgabe von binären Signalen an angeschlossene Hardware-Ressourcen.

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
- **OUT** (BOOL): Ausgabedaten zur Ressource
- **u8SAMember** (USINT): Knoten SA 217..224 (Initialwert: LO::LO_00)
- **Output** (DataPanel_LO_DO_S): Identifiziert den Digitalausgang 1A..4B (Initialwert: Invalid)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock arbeitet nach einem typischen Service-Interface-Muster. Bei der Initialisierung (INIT-Event) werden die Service-Parameter und Hardware-Konfiguration übergeben. Die eigentliche Datenausgabe erfolgt über das REQ-Event, wobei der boolesche Wert am OUT-Eingang an die konfigurierte Hardware-Ressource ausgegeben wird. Jede Operation wird durch entsprechende Bestätigungsereignisse (INITO, CNF) quittiert.

## Technische Besonderheiten
- Unterstützt spezifische Hardware-Adressierung über u8SAMember (SA-Knoten 217-224)
- Flexible Ausgangskonfiguration über Output-Parameter (DigitalOutput_1A bis 4B)
- Initialisierung mit Standardwerten für schnellen Einsatz
- String-basierte Statusrückmeldungen für detaillierte Fehlerdiagnose

## Zustandsübersicht
Der Baustein verfügt über zwei Hauptzustände:
1. **Nicht initialisiert**: Wartet auf INIT-Event
2. **Initialisiert**: Bereit für REQ-Operationen

Nach erfolgreicher Initialisierung können kontinuierlich Ausgabeanforderungen verarbeitet werden.

## Anwendungsszenarien
- Steuerung von Digitalausgängen in Prozessautomation
- Anbindung von Binärsignalen an Feldgeräte
- Integration in verteilte Steuerungssysteme
- Sicherheitskritische Schaltvorgänge

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Digitalausgangsblöcken bietet DataPanel_LO_QX erweiterte Funktionalitäten wie parametrierbare Hardware-Adressierung, detaillierte Statusrückmeldungen und eine strukturierte Initialisierungsprozedur. Die spezifische SA-Member-Adressierung macht ihn besonders für komplexe verteilte Systeme geeignet.

## Fazit
Der DataPanel_LO_QX ist ein robuster und flexibler Funktionsblock für die Ansteuerung von Digitalausgängen in industriellen Automatisierungssystemen. Seine strukturierte Schnittstelle und umfangreiche Konfigurationsmöglichkeiten machen ihn besonders für anspruchsvolle Anwendungen mit spezifischen Hardware-Anforderungen geeignet.
