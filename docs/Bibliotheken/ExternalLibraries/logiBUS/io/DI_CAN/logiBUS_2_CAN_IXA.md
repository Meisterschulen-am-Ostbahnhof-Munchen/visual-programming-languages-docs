# logiBUS_2_CAN_IXA

```{index} single: logiBUS_2_CAN_IXA
```

<img width="2031" height="363" alt="image" src="https://github.com/user-attachments/assets/d06a9404-82e0-4172-9321-7677d642f03f" />

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
Der logiBUS_2_CAN_IXA ist ein Composite-Funktionsblock zur Verarbeitung von booleschen Eingangsdaten über CAN-Bus-Schnittstellen. Der Baustein dient als Schnittstelle zwischen logiBUS-Systemen und CAN-basierten Eingabegeräten und ermöglicht die Initialisierung und Abfrage von digitalen Eingängen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung (mit QI und PARAMS)
- **REQ**: Service-Anfrage (mit QI)

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung (mit QO und STATUS)

### **Daten-Eingänge**
- **QI**: Ereignis-Eingangsqualifizierer (BOOL)
- **PARAMS**: Service-Parameter (STRING)
- **Input**: Identifizierung des Eingangs Input_Q1..Q8 (logiBUS_2_CAN_DI_S)

### **Daten-Ausgänge**
- **QO**: Ereignis-Ausgangsqualifizierer (BOOL)
- **STATUS**: Service-Status (STRING)

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ AX für die Datenkommunikation

## Funktionsweise
Der Composite-Funktionsblock nutzt intern den logiBUS_2_CAN_IX-Baustein zur Verarbeitung der CAN-basierten Eingangsdaten. Bei der INIT-Initialisierung werden die Service-Parameter übergeben und der Baustein konfiguriert. Über das REQ-Ereignis können Eingangsdaten abgefragt werden. Die Verarbeitung erfolgt über den Adapter IN, der die Kommunikation mit den CAN-Eingabegeräten ermöglicht.

## Technische Besonderheiten
- Verwendet spezifische logiBUS-Datentypen für CAN-Kommunikation
- Unterstützt bis zu 8 digitale Eingänge (Input_Q1 bis Input_Q8)
- Initialwert für Input ist "Invalid" (ungültig)
- Integriert Fehlerbehandlung über STATUS-Ausgang

## Zustandsübersicht
Der Baustein durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor INIT-Aufruf
2. **Initialisierung**: Während INIT-Verarbeitung
3. **Bereit**: Nach erfolgreicher Initialisierung (INITO bestätigt)
4. **Abfrage**: Während REQ-Verarbeitung

## Anwendungsszenarien
- Anbindung von CAN-basierten Sensoren und Schaltern an logiBUS-Systeme
- Industrielle Automatisierung mit digitalen Eingangssignalen
- Steuerungssysteme in der Agrartechnik
- Verteilte E/A-Systeme über CAN-Bus

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsbausteinen bietet logiBUS_2_CAN_IXA:
- CAN-Bus-Kommunikationsfähigkeit
- Erweiterte Parametrierungsmöglichkeiten
- Integrierte Statusrückmeldungen
- Spezifische logiBUS-Integration

## Fazit
Der logiBUS_2_CAN_IXA ist ein spezialisierter Composite-Funktionsblock für die zuverlässige Integration von CAN-basierten digitalen Eingängen in logiBUS-Systeme. Durch seine strukturierte Initialisierung und Abfragemechanismen eignet er sich besonders für industrielle Anwendungen, die robuste und konfigurierbare E/A-Schnittstellen erfordern.