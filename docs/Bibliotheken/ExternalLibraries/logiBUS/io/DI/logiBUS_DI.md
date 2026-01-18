# logiBUS_DI

```{index} single: logiBUS_DI
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

Die logiBUS_DI GlobalConstants-Definition stellt eine Sammlung von vordefinierten Konstanten für digitale Eingänge des logiBUS-Systems bereit. Diese Konstanten definieren die Pin-Zuordnungen für verschiedene digitale Eingangskanäle und werden zur Konfiguration von logiBUS-DI-Funktionsblöcken verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine Ereigniseingänge vorhanden - handelt sich um eine Konstantendefinition*

### **Ereignis-Ausgänge**
*Keine Ereignisausgänge vorhanden - handelt sich um eine Konstantendefinition*

### **Daten-Eingänge**
*Keine Dateneingänge vorhanden - handelt sich um eine Konstantendefinition*

### **Daten-Ausgänge**
*Keine Datenausgänge vorhanden - handelt sich um eine Konstantendefinition*

### **Adapter**
*Keine Adapter vorhanden - handelt sich um eine Konstantendefinition*

## Funktionsweise

Die GlobalConstants-Definition logiBUS_DI stellt strukturierte Konstanten vom Typ `logiBUS_DI_S` bereit, die jeweils einen spezifischen Pin-Wert enthalten:

- **Input_I1** bis **Input_I9**: Definiert die digitalen Eingänge 1 bis 9 mit entsprechenden Pin-Nummern
- **Invalid**: Definiert einen ungültigen Pin mit dem Wert 255

Diese Konstanten werden als Initialisierungswerte für die Konfiguration von digitalen Eingängen im logiBUS-System verwendet.

## Technische Besonderheiten

- **Strukturtyp**: Alle Konstanten verwenden den strukturierten Datentyp `logiBUS_DI_S`
- **Pin-Bereich**: Gültige Pins reichen von 1-9, ungültige Konfiguration wird durch Pin 255 gekennzeichnet
- **Package-Zugehörigkeit**: Die Konstanten sind im Package `logiBUS::io::DI` organisiert
- **Initialisierung**: Alle Konstanten werden bei der Deklaration mit ihren Pin-Werten initialisiert

## Zustandsübersicht

Da es sich um eine reine Konstantendefinition handelt, gibt es keine Zustandsübergänge oder Zustandsautomaten.

## Anwendungsszenarien

- Konfiguration von digitalen Eingangsmodulen in logiBUS-Systemen
- Parametrierung von Funktionsblöcken, die digitale Eingänge verarbeiten
- Typsichere Pin-Zuordnungen in Steuerungsprogrammen
- Fehlerbehandlung durch Verwendung der Invalid-Konstante

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu Funktionsblöcken mit aktiver Logik handelt es sich hier um eine reine Konstantendefinition, die:
- Keine aktive Verarbeitung durchführt
- Keine Ereignisse verarbeitet
- Ausschließlich Konfigurationsdaten bereitstellt
- Zur Compile-Zeit ausgewertet wird

## Fazit

Die logiBUS_DI GlobalConstants bieten eine strukturierte und typsichere Methode zur Konfiguration digitaler Eingänge im logiBUS-System. Durch die vordefinierten Konstanten wird die Fehleranfälligkeit bei der Pin-Zuordnung reduziert und die Wartbarkeit der Steuerungsprogramme verbessert.