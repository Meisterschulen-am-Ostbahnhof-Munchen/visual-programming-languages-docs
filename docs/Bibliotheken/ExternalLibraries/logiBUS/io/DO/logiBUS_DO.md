# logiBUS_DO

```{index} single: logiBUS_DO
```

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
Die logiBUS_DO GlobalConstants definieren eine Sammlung von Konstanten für die Konfiguration von digitalen Ausgängen (DO - Digital Output) im logiBUS-System. Diese Konstanten werden zur Pin-Zuweisung für digitale Ausgangskanäle verwendet und stellen eine standardisierte Schnittstelle für die Hardware-Konfiguration bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
*Keine Adapter vorhanden*

## Funktionsweise
Die logiBUS_DO GlobalConstants definieren strukturierte Konstanten vom Typ `logiBUS_DO_S`, die jeweils einen spezifischen Pin-Wert für digitale Ausgänge enthalten. Die Konstanten `Output_Q1` bis `Output_Q10` repräsentieren die verfügbaren Ausgangskanäle mit den entsprechenden Pin-Nummern 1 bis 10. Die Konstante `Invalid` mit dem Pin-Wert 255 dient als Kennzeichnung für ungültige oder nicht konfigurierte Ausgänge.

## Technische Besonderheiten
- **Konstantentyp**: Alle Konstanten sind vom strukturierten Datentyp `logiBUS_DO_S`
- **Pin-Zuordnung**: Klare Zuordnung von Ausgangsnamen zu physikalischen Pin-Nummern
- **Invalid-Kennzeichnung**: Spezielle Konstante mit Pin-Wert 255 für Fehlerbehandlung
- **Package-Struktur**: Organisiert im Package `logiBUS::io::DQ`

## Zustandsübersicht
Da es sich um Konstanten handelt, sind keine Zustandsübergänge vorhanden. Die Werte sind statisch und unveränderlich während der Laufzeit.

## Anwendungsszenarien
- Hardware-Konfiguration von logiBUS-Systemen
- Pin-Zuweisung in Funktionsblöcken für digitale Ausgänge
- Fehlerbehandlung bei ungültigen Ausgangskonfigurationen
- Standardisierung von Ausgangsbezeichnungen in Steuerungsanwendungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konstantendefinitionen bietet logiBUS_DO eine spezifische Struktur für digitale Ausgänge mit klarer Pin-Zuordnung und einer definierten Invalid-Konstante für robuste Fehlerbehandlung.

## Fazit
Die logiBUS_DO GlobalConstants bieten eine standardisierte und wartungsfreundliche Lösung für die Konfiguration digitaler Ausgänge in logiBUS-Systemen. Durch die strukturierte Definition der Ausgangskanäle und die bereitgestellte Invalid-Konstante wird eine zuverlässige und fehlertolerante Hardware-Konfiguration ermöglicht.