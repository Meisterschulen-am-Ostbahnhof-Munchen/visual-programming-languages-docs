# logiBUS_QX

```{index} single: logiBUS_QX
```

<img width="2048" height="379" alt="image" src="https://github.com/user-attachments/assets/be731935-05c6-402b-9703-aa2d97f347b6" />

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
Der logiBUS_QX Funktionsblock ist ein Ausgabeservice-Interface-Baustein für boolesche Ausgabedaten. Er dient als Schnittstelle zur Steuerung von digitalen Ausgängen über das logiBUS-System und ermöglicht die Kommunikation zwischen der Steuerungsanwendung und den physischen Ausgangskanälen.

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
- **OUT** (BOOL): Ausgabedaten zur Ressource
- **Output** (logiBUS_DO_S): Identifiziert den Ausgang (Output_Q1..Q8), Initialwert: Invalid

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Statusinformation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der logiBUS_QX-Block verwaltet die Kommunikation mit digitalen Ausgangskanälen des logiBUS-Systems. Bei Initialisierung (INIT-Event) werden die Service-Parameter konfiguriert und der spezifische Ausgangskanal identifiziert. Über das REQ-Event können boolesche Werte (OUT) an den konfigurierten Ausgangskanal gesendet werden. Der Block bestätigt jede Operation über die entsprechenden Ausgangsereignisse INITO und CNF.

## Technische Besonderheiten
- Verwendet spezifische logiBUS-Datentypen für die Ausgangsidentifikation
- Unterstützt bis zu 8 digitale Ausgangskanäle (Q1-Q8)
- Bietet detaillierte Statusrückmeldungen über den STATUS-Ausgang
- Initialisiert Ausgänge mit einem ungültigen Zustand (Invalid)

## Zustandsübersicht
Der Block durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Vor der ersten INIT-Operation
2. **Initialisiert**: Nach erfolgreicher INIT-Operation, bereit für REQ-Operationen
3. **Aktiv**: Während der Verarbeitung von REQ-Operationen

## Anwendungsszenarien
- Steuerung von digitalen Aktoren (Relais, Ventile, Lampen)
- Anbindung an logiBUS-Hardwareausgänge
- Automatisierungssysteme mit verteilten E/A-Komponenten
- Sicherheitsrelevante Schaltvorgänge mit Statusrückmeldung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu standardmäßigen digitalen Ausgangsblöcken bietet logiBUS_QX:
- Spezifische Integration in logiBUS-Systeme
- Erweiterte Statusrückmeldungen
- Parametrierbare Ausgangskonfiguration
- Höhere Abstraktionsebene für Hardwarezugriffe

## Fazit
Der logiBUS_QX Funktionsblock stellt eine robuste und zuverlässige Schnittstelle für die Ansteuerung digitaler Ausgänge in logiBUS-basierten Automatisierungssystemen dar. Durch seine klare Ereignisstruktur und umfassende Statusrückmeldungen eignet er sich besonders für Anwendungen, die hohe Zuverlässigkeit und Nachverfolgbarkeit der Ausgabeoperationen erfordern.