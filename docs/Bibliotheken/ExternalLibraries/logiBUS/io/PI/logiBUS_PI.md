# logiBUS_PI

```{index} single: logiBUS_PI
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
Der Funktionsblock `logiBUS_PI` ist eine Sammlung globaler Konstanten für die Konfiguration von Puls-Eingängen (Pulse Inputs) in logiBUS-Systemen. Er definiert vorkonfigurierte Strukturen, die die physischen Eingangspins eines logiBUS I/O-Moduls repräsentieren. Diese Konstanten dienen der einfachen und fehlerfreien Zuweisung von Hardware-Pins in übergeordneten Funktionsblöcken oder Anwendungen.

## Schnittstellenstruktur
Bei `logiBUS_PI` handelt es sich um einen GlobalConstants-Block, nicht um einen klassischen Funktionsblock mit Ereignis- oder Datenschnittstellen. Daher besitzt er keine Ereignis-Eingänge, -Ausgänge, Daten-Eingänge, -Ausgänge oder Adapter.

Die Schnittstelle besteht ausschließlich aus den definierten globalen Konstanten. Jede Konstante ist vom Datentyp `logiBUS::io::PI::logiBUS_PI_S` und wird mit einem spezifischen Initialwert instanziiert.

### **Definierte Konstanten**
Die folgenden Konstanten werden bereitgestellt:
*   `PulseInput_I1` bis `PulseInput_I9`: Repräsentieren die physischen Puls-Eingänge 1 bis 9. Der Initialwert setzt das Strukturfeld `Pin` auf den entsprechenden Wert (1-9).
*   `Invalid`: Stellt einen ungültigen oder nicht belegten Eingang dar. Der Initialwert setzt das Strukturfeld `Pin` auf den Wert 255.

## Funktionsweise
Der Block `logiBUS_PI` selbst führt keine aktive Funktionalität aus. Er stellt lediglich eine Bibliothek von vordefinierten Werten bereit. Diese Werte sind vom Typ `logiBUS_PI_S`, einer Struktur, die vermutlich mindestens das Mitglied `Pin` enthält.

Die Konstanten werden zur Kompilierzeit in den Anwendungscode eingefügt. Wenn ein anderer Funktionsblock (z.B. ein Treiber- oder Messbaustein) einen Parameter vom Typ `logiBUS_PI_S` erwartet, kann eine dieser Konstanten übergeben werden, um eindeutig einen bestimmten Hardware-Eingang auszuwählen.

## Technische Besonderheiten
*   **Typisierung:** Alle Konstanten sind streng vom strukturierten Datentyp `logiBUS_PI_S`. Dies erzwingt eine typsichere Verwendung und verhindert die unbeabsichtigte Zuweisung einfacher Integer-Werte.
*   **Initialisierung:** Die Initialwerte werden in der ST-Syntax `(Pin := X)` angegeben, was auf eine strukturierte Initialisierung hindeutet.
*   **Ungültiger Zustand:** Die Konstante `Invalid` mit dem Pin-Wert 255 bietet eine standardisierte Möglichkeit, einen nicht genutzten oder fehlerhaften Kanal zu kennzeichnen.

## Zustandsübersicht
Da es sich um einen Konstanten-Block handelt, besitzt `logiBUS_PI` keinen internen Zustand oder Zustandsautomaten. Die Werte der Konstanten sind unveränderlich (read-only) und während der gesamten Laufzeit der Anwendung konstant.

## Anwendungsszenarien
*   **Hardware-Konfiguration:** Primärer Einsatz zur Konfiguration von logiBUS I/O-Modulen, die Puls-Eingänge (z.B. für Encoder, Frequenz- oder Drehzahlmessung) bereitstellen.
*   **Parametrierung von Funktionsblöcken:** Vereinfachte und lesbare Parametrierung von Funktionsblöcken, die einen spezifischen Puls-Eingang benötigen. Statt der magischen Zahl `3` wird die selbsterklärende Konstante `PulseInput_I3` verwendet.
*   **Wartung und Lesbarkeit:** Erhöht die Wartbarkeit und Lesbarkeit des Anwendungscodes, da die Hardware-Zuordnung direkt im Konstantennamen ersichtlich ist.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken wie `E_SR` (Flip-Flop) oder `E_CYCLE` (zyklischer Event-Generator) implementiert `logiBUS_PI` keine Logik oder Algorithmen. Er ist vergleichbar mit anderen Konstanten-Blöcken oder ENUM-Definitionen in der IEC 61499, die hardwarenahe Parameter kapseln (z.B. `GPIO_PIN_XX` Konstanten für Raspberry Pi). Sein Zweck ist rein deklarativ und konfigurativ.

## Fazit
Der `logiBUS_PI` GlobalConstants-Block ist ein essentielles Hilfsmittel für die hardwarenahe Programmierung von logiBUS-Systemen. Durch die Bereitstellung typsicher, vordefinierter Konstanten für Puls-Eingänge ermöglicht er eine saubere, fehlerresistente und gut wartbare Konfiguration der Ein-/Ausgabe-Hardware. Seine Verwendung fördert Best Practices in der industriellen Automatisierungsprogrammierung.