# logiBUS_QW_SERVO

```{index} single: logiBUS_QW_SERVO
```

<img width="1341" height="240" alt="image" src="https://github.com/user-attachments/assets/a0a3a085-d2e5-4393-893f-f377b4a3f346" />

* * * * * * * * * *

## 🎧 Podcast

* [Digitale Gedächtnisse: Das SR-Flip-Flop im logiBUS®-System erklärt](https://podcasters.spotify.com/pod/show/logibus/episodes/Digitale-Gedchtnisse-Das-SR-Flip-Flop-im-logiBUS-System-erklrt-e36vksj)
* [ESP32 als Industrie-SPS: Revolution mit Eclipse 4diac und logiBUS®](https://podcasters.spotify.com/pod/show/logibus/episodes/ESP32-als-Industrie-SPS-Revolution-mit-Eclipse-4diac-und-logiBUS-e375dp6)
* [From Cable Chaos to Custom Control: How Logibus is Revolutionizing Agricultural Tech with Accessible ISOBUS](https://podcasters.spotify.com/pod/show/logibus/episodes/From-Cable-Chaos-to-Custom-Control-How-Logibus-is-Revolutionizing-Agricultural-Tech-with-Accessible-ISOBUS-e3767lq)
* [Logibus Revolution: Unpacking the "No Mapping" Future and Streamlined Development](https://podcasters.spotify.com/pod/show/logibus/episodes/Logibus-Revolution-Unpacking-the-No-Mapping-Future-and-Streamlined-Development-e375aph)
* [Logibus Unleashed: How Eliminating "Mapping" Simplifies Complex Systems and Boosts Usability](https://podcasters.spotify.com/pod/show/logibus/episodes/Logibus-Unleashed-How-Eliminating-Mapping-Simplifies-Complex-Systems-and-Boosts-Usability-e375a3m)

## 📺 Video

* [06. Mai 2025 Tag 6 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=g-LuUu-QFcI)
* [15. Apr. 2025  Tag 1 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=tlZC5rN_CUI)
* [17. Apr. 2025 Tag 2 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=hy2S94jOVi0)
* [2025 11 15 12 35 11 Montage Hutschienenmoped logiBUS® -- Teil 3 -- Gehäuse](https://www.youtube.com/watch?v=MPm4vLmD5RE)
* [2025 11 15 12 52 26 Montage Hutschienenmoped logiBUS® -- Teil 4 -- Aufbauten](https://www.youtube.com/watch?v=WeowCxZW70Y)

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