# logiBUS_IE

```{index} single: logiBUS_IE
```

<img width="2037" height="313" alt="image" src="https://github.com/user-attachments/assets/3cb31c53-ac68-4483-bfc4-834776122b60" />

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
Der logiBUS_IE Funktionsblock ist ein Eingabeservice-Schnittstellenbaustein für Ereigniseingabedaten. Er dient als Interface zwischen dem logiBUS-System und der 4diac-Laufzeitumgebung zur Verarbeitung von digitalen Eingangssignalen mit erweiterten Ereigniserkennungsfunktionen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung
  - Verknüpft mit: QI, PARAMS, Input, InputEvent
- **REQ**: Service-Anfrage
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **CNF**: Bestätigung der angeforderten Services
  - Verknüpft mit: QO, STATUS
- **IND**: Indikation von der Ressource
  - Verknüpft mit: QO, STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **Input** (logiBUS_DI_S): Identifiziert den Eingang (I1..I8)
  - Initialwert: Invalid
- **InputEvent** (logiBUS_DI_Events_S): Identifiziert das Ereignis (Down, Up, Single-Click, Double-Click etc.)
  - Initialwert: Invalid

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock ermöglicht die Verarbeitung digitaler Eingangssignale mit erweiterter Ereigniserkennung. Über die INIT-Initialisierung können spezifische Parameter konfiguriert werden. Der Baustein erkennt verschiedene Eingabeereignisse wie Tastendrücke, Loslassen, Einzelklicks und Doppelklicks und signalisiert diese über die entsprechenden Ausgangsereignisse.

## Technische Besonderheiten
- Unterstützt multiple Ereignistypen (Down, Up, Single-Click, Double-Click)
- Flexible Eingangskonfiguration über PARAMS-String
- Statusrückmeldung über STATUS-Ausgang
- Initialisierung mit Invalid-Werten für sicheren Start

## Zustandsübersicht
Der Baustein verfügt über einen initialisierten und einen Betriebszustand. Nach erfolgreicher INIT-Initialisierung wechselt er in den Betriebszustand, in dem Ereignisverarbeitung und Service-Anfragen verarbeitet werden können.

## Anwendungsszenarien
- Bedienpanel-Steuerungen
- Tastatureingabe-Verarbeitung
- Mechanische Schalter-Überwachung
- Benutzerinteraktionssysteme
- Industrielle Steuerungstaster

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsbausteinen bietet logiBUS_IE erweiterte Ereigniserkennungsfunktionen und kann komplexe Eingabemuster wie Doppelklicks erkennen. Die parametrierbare Konfiguration ermöglicht eine flexible Anpassung an verschiedene Hardware-Schnittstellen.

## Fazit
Der logiBUS_IE Funktionsblock stellt eine leistungsstarke Schnittstelle für digitale Eingabegeräte mit erweiterter Ereigniserkennung bereit. Seine flexible Konfigurierbarkeit und die Unterstützung verschiedener Ereignistypen machen ihn ideal für Anwendungen, die komplexe Benutzerinteraktionen erfordern.