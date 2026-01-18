# logiBUS_IB

```{index} single: logiBUS_IB
```

<img width="1903" height="313" alt="image" src="https://github.com/user-attachments/assets/56357e8e-ea36-427f-8c9a-3e990b8f634c" />

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
Der logiBUS_IB ist ein Service Interface Function Block für die Verarbeitung von Byte-Eingabedaten. Dieser Baustein dient als Eingabeschnittstelle für logiBUS-Systeme und ermöglicht die Kommunikation mit digitalen Eingängen. Er unterstützt spezielle Ereignisbehandlungen wie Tastendruck-Wiederholungen und bietet eine standardisierte Schnittstelle für die Initialisierung und den Betrieb von Eingabegeräten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis
  - Verknüpft mit: QI, PARAMS, Input, InputEvent
- **REQ**: Service-Anfrageereignis
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **CNF**: Bestätigung der angeforderten Service-Operation
  - Verknüpft mit: QO, STATUS, IN
- **IND**: Indikation vom Ressourcen-Interface
  - Verknüpft mit: QO, STATUS, IN

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Steuert die Ausführung der Service-Operationen
- **PARAMS** (STRING): Service-Parameter für die Konfiguration
- **Input** (logiBUS_DI_S): Identifiziert den Eingang (I1..I8), Initialwert: Invalid
- **InputEvent** (logiBUS_DI_Events_S): Identifiziert das Ereignis (aktuell nur REPEAT unterstützt), Initialwert: Invalid

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Status der Service-Operation
- **STATUS** (STRING): Service-Statusinformationen
- **IN** (BYTE): Eingabedaten von der Ressource

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der logiBUS_IB Function Block arbeitet als Eingabeservice-Interface für logiBUS-Systeme. Bei der Initialisierung (INIT-Event) werden die Service-Parameter konfiguriert und die Eingänge definiert. Der Baustein kann sowohl auf explizite Anfragen (REQ-Event) als auch auf asynchrone Ereignisse von der Hardware reagieren. Besondere Unterstützung bietet er für wiederholte Tastendruck-Ereignisse (BUTTON_PRESS_REPEAT).

## Technische Besonderheiten
- Unterstützt spezielle Ereignistypen wie BUTTON_PRESS_REPEAT und BUTTON_PRESS_REPEAT_DONE
- Byte-basierte Dateneingabe (8-Bit)
- Flexible Eingangskonfiguration über PARAMS-String
- Separate Ereignisausgänge für Bestätigungen (CNF) und Hardware-Indikationen (IND)
- Initialwert "Invalid" für nicht konfigurierte Eingänge

## Zustandsübersicht
Der Baustein verfügt über folgende Betriebszustände:
- **Nicht initialisiert**: Vor INIT-Event
- **Initialisiert**: Nach erfolgreicher INIT-Operation
- **Bereit**: Für REQ-Anfragen und IND-Ereignisse
- **Fehlerzustand**: Bei fehlerhaften Operationen (über STATUS meldbar)

## Anwendungsszenarien
- Digitale Eingabebaugruppen mit 8 Eingängen
- Tastatur-Interface mit Wiederholfunktion
- Allgemeine digitale Eingabeschnittstellen in logiBUS-Systemen
- Hardware-nahe Eingabeoperationen mit Event-Behandlung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingabebausteinen bietet logiBUS_IB erweiterte Service-Funktionalität mit:
- Parametrierbarer Konfiguration
- Ereignisbasierter Kommunikation
- Statusrückmeldungen
- Spezieller Unterstützung für Tastendruck-Wiederholungen

## Fazit
Der logiBUS_IB Function Block stellt eine leistungsfähige und flexible Lösung für Byte-Eingabedaten in logiBUS-Systemen dar. Durch seine Service-orientierte Architektur und die Unterstützung spezieller Ereignistypen eignet er sich besonders für Anwendungen, die erweiterte Eingabefunktionalitäten wie Tastendruck-Wiederholungen benötigen.