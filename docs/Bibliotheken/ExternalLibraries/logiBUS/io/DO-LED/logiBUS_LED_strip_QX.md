# logiBUS_LED_strip_QX

```{index} single: logiBUS_LED_strip_QX
```

<img width="1879" height="394" alt="image" src="https://github.com/user-attachments/assets/3a675690-c734-4d38-bc52-a9ff1d611d4f" />

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
Der Funktionsblock logiBUS_LED_strip_QX ist ein Ausgabeservice-Interface-Funktionsblock für boolesche Ausgabedaten, der speziell für die Ansteuerung von LED-Streifen entwickelt wurde. Er bietet umfangreiche Konfigurationsmöglichkeiten für verschiedene LED-Parameter wie Farbe, Frequenz und Ausgangsnummer.

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
- **OUT** (BOOL): Ausgabedaten an die Ressource
- **Output** (USINT): Identifiziert die Ausgangsnummer des Streifens (Initialwert: LED_strip::Output_strip)
- **Colour** (UINT): Identifiziert die Farbe (Initialwert: LED_COLOURS::LED_GREEN)
- **FREQ** (UINT): Definiert die LED-Frequenz und Priorität (Initialwert: LED_FREQ::LED_OFF)

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock ermöglicht die Steuerung von LED-Streifen über eine standardisierte Schnittstelle. Bei der Initialisierung (INIT) werden die Konfigurationsparameter wie Ausgangsnummer, Farbe und Frequenz gesetzt. Über das REQ-Ereignis können Ausgabedaten (OUT) an den LED-Streifen gesendet werden. Der Block bestätigt jede Operation über die entsprechenden Ausgangsereignisse INITO und CNF.

## Technische Besonderheiten
- Unterstützung verschiedener LED-Farben über den Colour-Parameter
- Konfigurierbare Frequenzeinstellungen für Blinkfunktionen
- Mehrfachausgänge über den Output-Parameter unterstützt
- Initialwerte für schnelle Inbetriebnahme vordefiniert
- Statusrückmeldung über STRING-Parameter

## Zustandsübersicht
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Initialisierungszustand**: Wird durch INIT-Ereignis aktiviert
2. **Betriebszustand**: Verarbeitet REQ-Anfragen nach erfolgreicher Initialisierung

## Anwendungsszenarien
- Industrielle Beleuchtungssteuerung
- Statusanzeigen in Automatisierungsanlagen
- Warn- und Signallichtsteuerung
- Visualisierung von Prozesszuständen
- Gebäudeautomation mit LED-Beleuchtung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgabeblöcken bietet logiBUS_LED_strip_QX erweiterte Funktionalität für LED-spezifische Anwendungen, insbesondere durch die integrierte Farb- und Frequenzsteuerung sowie die Möglichkeit, mehrere LED-Streifen unabhängig zu adressieren.

## Fazit
Der logiBUS_LED_strip_QX ist ein leistungsstarker Funktionsblock für die professionelle LED-Streifen-Steuerung in industriellen Automatisierungslösungen. Seine flexible Parametrierung und zuverlässige Statusrückmeldung machen ihn ideal für anspruchsvolle Beleuchtungsanwendungen.