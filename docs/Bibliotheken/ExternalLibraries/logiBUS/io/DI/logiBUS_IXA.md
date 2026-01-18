# logiBUS_IXA

```{index} single: logiBUS_IXA
```

<img width="1838" height="367" alt="image" src="https://github.com/user-attachments/assets/fcf18e0e-a542-4642-a00f-1438f4caf5fb" />

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
Der logiBUS_IXA ist ein Composite-Funktionsblock zur Verarbeitung von booleschen Eingangsdaten. Er dient als Schnittstelle für digitale Eingänge und ermöglicht die Initialisierung und Abfrage von Eingangssignalen über standardisierte Service-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis mit den zugehörigen Daten QI, PARAMS und Input
- **REQ**: Service-Anfrageereignis mit dem zugehörigen Datenwert QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den zugehörigen Datenwerten QO und STATUS

### **Daten-Eingänge**
- **QI**: Boolescher Ereignis-Eingangsqualifizierer
- **PARAMS**: Service-Parameter als Zeichenkette
- **Input**: Identifiziert die Eingänge Q1 bis Q8 mit dem Typ logiBUS_DI_S und Initialwert "Invalid"

### **Daten-Ausgänge**
- **QO**: Boolescher Ereignis-Ausgangsqualifizierer
- **STATUS**: Service-Status als Zeichenkette

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ AX für die Eingangsdatenverarbeitung

## Funktionsweise
Der Composite-Funktionsblock logiBUS_IXA kapselt den Basisfunktionsblock logiBUS_IX und erweitert dessen Funktionalität durch zusätzliche Adapter-Schnittstellen. Bei INIT-Ereignissen werden die Parameter an den internen IX-Block weitergeleitet, der die Initialisierung durchführt. Die IND-Ereignisse des IX-Blocks werden an den Eingangsadapter IN weitergegeben, während die Datenverbindungen die entsprechende Signalverarbeitung sicherstellen.

## Technische Besonderheiten
- Verwendet den spezifischen Datentyp logiBUS_DI_S für die Eingangsidentifikation
- Implementiert standardisierte Service-Schnittstellen gemäß 61499-2
- Unterstützt Parameterübergabe via STRING-Datentyp
- Bietet Statusrückmeldungen über STATUS-Ausgang

## Zustandsübersicht
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Nicht initialisiert**: Vor dem INIT-Ereignis
2. **Initialisiert und betriebsbereit**: Nach erfolgreicher INIT-Bestätigung

## Anwendungsszenarien
- Anbindung digitaler Eingänge in Automatisierungssystemen
- Integration in logiBUS-basierte Steuerungsarchitekturen
- Verwendung in SPS-Systemen mit booleschen Signalverarbeitungsanforderungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Eingangsblöcken bietet logiBUS_IXA erweiterte Service-Funktionalitäten mit Parametrierungsmöglichkeiten und Statusrückmeldungen. Die Composite-Struktur ermöglicht eine bessere Wiederverwendbarkeit und erweiterte Diagnosefähigkeiten.

## Fazit
Der logiBUS_IXA Funktionsblock stellt eine robuste und flexible Lösung für die Verarbeitung digitaler Eingangssignale in 4diac-basierten Automatisierungssystemen dar. Durch seine standardisierten Schnittstellen und erweiterten Service-Funktionen eignet er sich besonders für komplexe Anwendungen mit hohen Anforderungen an Diagnose und Parametrierbarkeit.