# logiBUS_QXA

```{index} single: logiBUS_QXA
```

<img width="2042" height="360" alt="image" src="https://github.com/user-attachments/assets/a209d37d-5012-4889-853b-e7a36dfc6644" />

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
Der logiBUS_QXA ist ein zusammengesetzter Funktionsblock für die Ausgabe von booleschen Daten. Er dient als Schnittstelle für digitale Ausgabefunktionen und ermöglicht die Steuerung von bis zu 8 digitalen Ausgängen über ein standardisiertes Protokoll.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis mit den zugehörigen Daten QI, PARAMS und Output

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den Daten QO und STATUS
- **CNF**: Bestätigung des angeforderten Services mit den Daten QO und STATUS

### **Daten-Eingänge**
- **QI**: Boolescher Ereigniseingangsqualifizierer
- **PARAMS**: Service-Parameter als Zeichenkette
- **Output**: Identifizierung der Ausgänge Q1 bis Q8 vom Typ logiBUS_DO_S mit Initialwert "Invalid"

### **Daten-Ausgänge**
- **QO**: Boolescher Ereignisausgangsqualifizierer
- **STATUS**: Service-Status als Zeichenkette

### **Adapter**
- **OUT**: Unidirektionaler Adapter vom Typ AX für die Ausgabekommunikation

## Funktionsweise
Der logiBUS_QXA fungiert als Wrapper für den logiBUS_QX-Funktionsblock und bietet eine vereinheitlichte Schnittstelle für digitale Ausgabefunktionen. Bei Initialisierung (INIT-Ereignis) werden die Konfigurationsparameter übergeben und die Ausgänge entsprechend konfiguriert. Der Block ermöglicht die Steuerung von bis zu 8 digitalen Ausgängen über die Output-Datenstruktur.

## Technische Besonderheiten
- Verwendet den logiBUS_QX-Kernfunktionsblock für die eigentliche Ausgabelogik
- Unterstützt bis zu 8 digitale Ausgänge (Q1 bis Q8)
- Initialisierung mit spezifischen Parametern über die PARAMS-Eingabe
- Rückmeldung des Betriebszustands über STATUS-Ausgabe

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor dem INIT-Ereignis
2. **Initialisierung**: Während der Verarbeitung des INIT-Ereignis
3. **Betriebsbereit**: Nach erfolgreicher Initialisierung (INITO-Bestätigung)
4. **Aktiver Betrieb**: Verarbeitung von Ausgabeanforderungen über den OUT-Adapter

## Anwendungsszenarien
- Steuerung von digitalen Aktoren in Automatisierungssystemen
- Anbindung von Ausgabemodulen in verteilten Steuerungssystemen
- Integration in logiBUS-basierte Steuerungsarchitekturen
- Industrielle Automatisierung mit booleschen Ausgabesignalen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgabeblöcken bietet logiBUS_QXA:
- Erweiterte Parametrierungsmöglichkeiten
- Statusrückmeldungen für Fehlerdiagnose
- Standardisierte Schnittstelle über Adapter
- Unterstützung für multiple Ausgänge in einer Struktur

## Fazit
Der logiBUS_QXA ist ein robuster und flexibler Funktionsblock für digitale Ausgabefunktionen in industriellen Automatisierungssystemen. Durch seine standardisierte Schnittstelle und umfassende Parametrierungsmöglichkeiten eignet er sich ideal für den Einsatz in komplexen Steuerungsarchitekturen mit hohen Anforderungen an Zuverlässigkeit und Diagnosefähigkeit.