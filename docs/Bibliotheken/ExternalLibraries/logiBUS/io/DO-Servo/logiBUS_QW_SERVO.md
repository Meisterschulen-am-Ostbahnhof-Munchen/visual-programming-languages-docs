# logiBUS_QW_SERVO

```{index} single: logiBUS_QW_SERVO
```

<img width="1341" height="240" alt="image" src="https://github.com/user-attachments/assets/a0a3a085-d2e5-4393-893f-f377b4a3f346" />

* * * * * * * * * *

## Einleitung
Der logiBUS_QW_SERVO ist ein Ausgabeservice-Schnittstellen-Funktionsblock für Wort-Ausgabedaten, der speziell für die Ansteuerung von logiBUS-Servoausgängen entwickelt wurde. Der Baustein ermöglicht die Initialisierung und Steuerung von digitalen Ausgängen über eine standardisierte Schnittstelle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis mit den zugehörigen Daten QI, PARAMS und Output
- **REQ**: Service-Anfrageereignis mit den zugehörigen Daten QI und OUT

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den zugehörigen Daten QO und STATUS
- **CNF**: Bestätigung der angeforderten Service-Operation mit den zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Ereigniseingangs-Qualifier
- **PARAMS** (STRING): Service-Parameter für die Konfiguration
- **OUT** (WORD): Ausgabedaten zur Ressource
- **Output** (logiBUS::io::DQ::logiBUS_DO_S): Identifiziert den Ausgang Output_Q1..Q8, initial mit Wert "Invalid"

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignisausgangs-Qualifier
- **STATUS** (STRING): Service-Statusinformation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock ermöglicht die Initialisierung und Steuerung von logiBUS-Servoausgängen. Bei der INIT-Initialisierung werden die Service-Parameter konfiguriert und der spezifische Ausgang identifiziert. Über das REQ-Ereignis können Ausgabedaten im WORD-Format an die Ressource gesendet werden. Der Baustein bestätigt beide Operationen durch entsprechende Ausgangsereignisse (INITO und CNF) mit Statusinformationen.

## Technische Besonderheiten
- Verwendet WORD-Datentyp für Ausgabedaten (16-Bit)
- Unterstützt spezifische logiBUS-Ausgangsidentifikation über den Output-Parameter
- Initialisierung mit "Invalid"-Wert für den Output-Parameter
- String-basierte Parameter- und Statusübertragung

## Zustandsübersicht
Der Baustein verfügt über zwei Hauptbetriebszustände:
1. **Nicht initialisiert**: Vor der INIT-Initialisierung
2. **Initialisiert und betriebsbereit**: Nach erfolgreicher INIT-Initialisierung, bereit für REQ-Anfragen

## Anwendungsszenarien
- Ansteuerung von digitalen Ausgängen in logiBUS-Systemen
- Servosteuerungen mit Wort-Datenausgabe
- Industrielle Automatisierungsanwendungen mit präziser Ausgangsansteuerung
- Embedded-Systeme mit logiBUS-Interface

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgabeblöcken bietet logiBUS_QW_SERVO erweiterte Funktionalität durch:
- Wort-basierte Datenausgabe (16-Bit statt einzelner Bits)
- Spezifische Servo-Steuerungsfunktionen
- Detaillierte Statusrückmeldungen
- Parametrierbare Initialisierung

## Fazit
Der logiBUS_QW_SERVO ist ein spezialisierter Funktionsblock für anspruchsvolle Ausgabeanwendungen in logiBUS-Systemen. Durch seine Wort-basierte Datenverarbeitung und umfassende Statusrückmeldung eignet er sich besonders für präzise Steuerungsaufgaben in industriellen Automatisierungslösungen.
