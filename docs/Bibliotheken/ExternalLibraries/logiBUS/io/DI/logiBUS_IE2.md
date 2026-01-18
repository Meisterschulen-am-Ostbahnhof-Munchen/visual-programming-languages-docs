# logiBUS_IE2

```{index} single: logiBUS_IE2
```

<img width="1746" height="283" alt="image" src="https://github.com/user-attachments/assets/ac2845b6-9709-446e-9377-bd61a000862d" />

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
Der logiBUS_IE2 ist ein Eingabeservice-Schnittstellen-Funktionsblock für Ereigniseingabedaten. Er dient als Interface für die Verarbeitung von Eingabeereignissen in logiBUS-Systemen und ermöglicht die Verarbeitung verschiedener Eingabeereignistypen wie Tastendrücke, Klicks und zeitbasierte Ereignisse.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (Service Initialization) - Initialisiert den Service mit folgenden Daten:
  - QI
  - PARAMS
  - Input
  - InputEvent
  - arg

- **REQ** (Service Request) - Fordert einen Service an mit:
  - QI

### **Ereignis-Ausgänge**
- **INITO** (Initialization Confirm) - Bestätigt die Initialisierung mit:
  - QO
  - STATUS

- **CNF** (Confirmation of Requested Service) - Bestätigt den angeforderten Service mit:
  - QO
  - STATUS

- **IND** (Indication from Resource) - Meldung von der Ressource mit:
  - QO
  - STATUS

### **Daten-Eingänge**
- **QI** (BOOL) - Event Input Qualifier
- **PARAMS** (STRING) - Service Parameters
- **Input** (logiBUS_DI_S) - Identifiziert den Eingang Input_I1..I8 (Initialwert: Invalid)
- **InputEvent** (logiBUS_DI_Events_S) - Identifiziert das Ereignis (Down, Up, Single-Click, Double Click etc.) (Initialwert: Invalid)
- **arg** (UINT) - Langdruck-Zeitereignisdaten ODER Mehrfachklick-Ereignisdaten (abhängig vom Input Event) (Initialwert: 65535)

### **Daten-Ausgänge**
- **QO** (BOOL) - Event Output Qualifier
- **STATUS** (STRING) - Service Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der logiBUS_IE2 Funktionsblock verarbeitet Eingabeereignisse von logiBUS-Eingängen und wandelt diese in standardisierte Ereignismeldungen um. Er unterstützt verschiedene Ereignistypen wie Tastendrücke (Down/Up), Einzelklicks, Doppelklicks und zeitbasierte Ereignisse wie Langdruck. Der Block kann über den INIT-Eingang konfiguriert werden und liefert über die Ausgänge Statusinformationen und Bestätigungen zurück.

## Technische Besonderheiten
- Unterstützt multiple Eingänge (I1 bis I8)
- Verarbeitet verschiedene Ereignistypen über die InputEvent-Variable
- Kann zeitbasierte Ereignisse (Langdruck) und zählbasierte Ereignisse (Mehrfachklicks) verarbeiten
- Initialisierung mit spezifischen Parametern über PARAMS-Eingang
- Liefert detaillierte Statusinformationen über STATUS-Ausgang

## Zustandsübersicht
Der Funktionsblock verfügt über einen Initialisierungszustand (INIT/INITO) und operative Zustände für Service-Anfragen (REQ/CNF) sowie asynchrone Ereignismeldungen (IND). Die genaue Zustandsmaschine ist implementierungsabhängig.

## Anwendungsszenarien
- Bedienpanel-Steuerungen mit Tasteneingaben
- Maschinensteuerung mit Ereignis-basierten Eingaben
- Systeme mit komplexen Tasteneingabe-Sequenzen
- Anwendungen mit Langdruck- und Mehrfachklick-Erkennung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingabeblöcken bietet logiBUS_IE2 erweiterte Funktionalität für komplexe Ereigniserkennung und unterstützt verschiedene Eingabeereignistypen mit konfigurierbaren Parametern.

## Fazit
Der logiBUS_IE2 ist ein leistungsstarker Funktionsblock für die Verarbeitung von Ereigniseingabedaten in logiBUS-Systemen, der durch seine Flexibilität bei der Ereigniserkennung und umfangreiche Konfigurationsmöglichkeiten für anspruchsvolle Steuerungsanwendungen geeignet ist.