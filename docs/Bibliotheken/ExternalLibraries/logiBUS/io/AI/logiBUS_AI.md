# logiBUS_AI

```{index} single: logiBUS_AI
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
Die logiBUS_AI GlobalConstants definieren eine Sammlung von Konstanten für die Konfiguration von analogen Eingängen im logiBUS-System. Diese Konstanten werden zur einfachen und einheitlichen Referenzierung der analogen Eingangskanäle verwendet.

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
Die logiBUS_AI GlobalConstants stellen vordefinierte Konstanten vom Typ `logiBUS_AI_S` bereit, die jeweils einen spezifischen analogen Eingangskanal repräsentieren. Jede Konstante enthält eine Pin-Nummer, die den physikalischen Eingangskanal identifiziert.

## Technische Besonderheiten
- **Konstantentyp**: Alle Konstanten sind vom strukturierten Datentyp `logiBUS_AI_S`
- **Pin-Zuordnung**: Die Konstanten `AnalogInput_I1` bis `AnalogInput_I9` entsprechen den analogen Eingängen 1 bis 9
- **Ungültige Referenz**: Die Konstante `Invalid` mit Pin-Wert 255 dient als Marker für ungültige oder nicht vorhandene Eingänge
- **Initialisierung**: Alle Konstanten werden bei der Deklaration mit ihren entsprechenden Pin-Werten initialisiert

## Zustandsübersicht
Da es sich um Konstanten handelt, haben diese keine Zustandsänderungen. Die Werte sind während der gesamten Laufzeit unveränderlich.

## Anwendungsszenarien
- Konfiguration von analogen Eingängen in logiBUS-Systemen
- Parametrierung von Funktionsblöcken, die analoge Eingänge benötigen
- Typsichere Referenzierung von analogen Kanälen in der Programmierung
- Fehlerbehandlung durch Verwendung der Invalid-Konstante

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken mit dynamischem Verhalten bieten GlobalConstants:
- Keine Laufzeitberechnungen
- Keine Ereignisbehandlung
- Konstanten statt variabler Werte
- Direkte Initialisierung bei der Deklaration

## Fazit
Die logiBUS_AI GlobalConstants bieten eine effiziente und typsichere Methode zur Referenzierung analoger Eingänge im logiBUS-System. Durch die vordefinierten Konstanten wird die Programmierung vereinfacht und die Fehleranfälligkeit bei der Kanalkonfiguration reduziert.