# logiBUS_QD_PWM

```{index} single: logiBUS_QD_PWM
```

<img width="1848" height="333" alt="image" src="https://github.com/user-attachments/assets/ea4b0496-56de-4eb9-a419-6cd8c9b095bb" />

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
Der Funktionsblock `logiBUS_QD_PWM` ist ein Ausgabeservice-Interface-Funktionsblock für doppelte Wort-Ausgabedaten. Er dient als Schnittstelle zur Steuerung von PWM-Ausgaben (Pulsweitenmodulation) über das logiBUS-System und ermöglicht die Ansteuerung von Ausgängen Q1 bis Q8.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung
  - Verknüpft mit: QI, PARAMS, Output
- **REQ**: Service-Anforderung
  - Verknüpft mit: QI, OUT

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **CNF**: Bestätigung der angeforderten Service-Operation
  - Verknüpft mit: QO, STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **OUT** (DWORD): Ausgabedaten zur Ressource
- **Output** (logiBUS_DO_S): Identifiziert den Ausgang Output_Q1..Q8
  - Initialwert: `logiBUS_DO::Invalid`

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Status

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock ermöglicht die PWM-Steuerung von Ausgängen über das logiBUS-System. Bei der Initialisierung (INIT) werden die Service-Parameter konfiguriert und der spezifische Ausgang identifiziert. Über die REQ-Anforderung können PWM-Daten (DWORD) an den konfigurierten Ausgang gesendet werden. Der Block bestätigt sowohl Initialisierung als auch Service-Anforderungen über die entsprechenden Ausgangsereignisse.

## Technische Besonderheiten
- Verwendet DWORD-Datentyp für PWM-Ausgabedaten
- Unterstützt bis zu 8 Ausgänge (Q1-Q8) über die Output-Konfiguration
- String-basierte Parameterkonfiguration für flexible Service-Einstellungen
- Statusrückmeldung über STRING-Variable für detaillierte Fehlerinformationen

## Zustandsübersicht
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert und betriebsbereit**: Block kann REQ-Anforderungen verarbeiten und PWM-Daten ausgeben

## Anwendungsszenarien
- Steuerung von PWM-gesteuerten Aktoren (Motoren, Heizelemente)
- Ansteuerung von LED-Beleuchtung mit Helligkeitssteuerung
- Regelung von Ventilen mit proportionaler Steuerung
- Industrielle Automatisierungsanwendungen mit logiBUS-Hardware

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen digitalen Ausgabeblöcken bietet `logiBUS_QD_PWM` erweiterte PWM-Funktionalität mit 32-Bit-Auflösung (DWORD). Gegenüber analogen Ausgabeblöcken ermöglicht er die direkte PWM-Steuerung ohne zusätzliche Wandlung.

## Fazit
Der `logiBUS_QD_PWM` Funktionsblock stellt eine leistungsstarke Schnittstelle für PWM-Ausgaben im logiBUS-System bereit. Durch die flexible Konfiguration und die Unterstützung für 32-Bit-PWM-Daten eignet er sich ideal für präzise Steuerungsanwendungen in industriellen Automatisierungssystemen.