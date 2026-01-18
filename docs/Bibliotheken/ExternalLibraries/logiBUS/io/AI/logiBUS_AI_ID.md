# logiBUS_AI_ID

```{index} single: logiBUS_AI_ID
```

<img width="1998" height="363" alt="image" src="https://github.com/user-attachments/assets/c03aec55-c580-46c1-8d13-7cfd30b77783" />

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
Der logiBUS_AI_ID ist ein Service Interface Function Block für die Verarbeitung von Double-Word-Eingabedaten. Dieser Baustein dient als Schnittstelle für analoge Eingänge und bietet Funktionen zur Initialisierung, Abfrage und Indikation von Eingabedaten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
- **REQ**: Service-Anfrageereignis

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
- **CNF**: Bestätigung der angeforderten Service-Operation
- **IND**: Indikation vom Resource

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Aktiviert/Deaktiviert den Service
- **PARAMS** (STRING): Service-Parameter für Konfiguration
- **Input** (logiBUS_AI_S): Identifiziert den Eingang (I1..I8) mit Initialwert "Invalid"
- **AnalogInput_hysteresis** (DWORD): Hysterese-Wert für analoge Eingänge

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Status des Service-Ausgangs
- **STATUS** (STRING): Service-Statusinformationen
- **IN** (DWORD): Eingabedaten vom Resource

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Function Block ermöglicht die Kommunikation mit analogen Eingabegeräten über das logiBUS-System. Bei der INIT-Initialisierung werden die Service-Parameter konfiguriert und der Eingang identifiziert. Über REQ können Daten abgefragt werden, während IND asynchrone Datenankündigungen vom Resource verarbeitet. Die Hysterese-Funktion unterstützt bei der Filterung von Signalrauschen.

## Technische Besonderheiten
- Verwendet spezielle Datentypen aus dem logiBUS::io::AI-Package
- Unterstützt Hysterese-Funktionalität für analoge Signale
- Bietet sowohl synchrone (CNF) als auch asynchrone (IND) Betriebsmodi
- Initialisiert Eingänge mit einem definierten "Invalid"-Zustand

## Zustandsübersicht
Der Baustein verfügt über folgende Betriebszustände:
- Nicht initialisiert (vor INIT)
- Initialisiert und bereit (nach INITO)
- Datenabfrage aktiv (bei REQ/CNF)
- Indikationsmodus (bei IND)

## Anwendungsszenarien
- Industrielle Automatisierungssysteme mit analogen Sensoren
- Prozessleittechnik mit Hysterese-Anforderungen
- Embedded-Systeme mit logiBUS-Kommunikation
- Anlagen mit mehreren analogen Eingängen (I1-I8)

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen analogen Eingangsbausteinen bietet logiBUS_AI_ID erweiterte Funktionen wie Hysterese-Steuerung, detaillierte Statusrückmeldungen und eine strukturierte Initialisierungsprozedur. Die Integration in das logiBUS-System ermöglicht eine standardisierte Kommunikation.

## Fazit
Der logiBUS_AI_ID Function Block stellt eine robuste und flexible Lösung für die Anbindung analoger Eingabegeräte in industriellen Steuerungssystemen dar. Durch die umfangreiche Parametrierungsmöglichkeit und die integrierte Hysterese-Funktionalität eignet er sich besonders für anspruchsvolle Automatisierungsanwendungen.