# logiBUS_DI_S

```{index} single: logiBUS_DI_S
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
Der Funktionsblock `logiBUS_DI_S` ist ein strukturierter Datentyp (Struct), der zur Konfiguration eines digitalen Eingangs (DI) innerhalb des logiBUS-Frameworks dient. Er definiert die grundlegenden Parameter, die notwendig sind, um einen physischen oder logischen Eingangspunkt auf einem logiBUS-kompatiblen I/O-System anzusteuern. Dieser Datentyp wird typischerweise als Eingabe für spezifische I/O-Funktionsblöcke verwendet.

## Schnittstellenstruktur
Als strukturierter Datentyp besitzt `logiBUS_DI_S` keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne. Seine Struktur besteht aus einem einzelnen Datenelement.

### **Daten-Eingänge**
Die Struktur selbst stellt die konfigurierbaren Dateneingänge dar. Sie wird als Ganzes an einen übergeordneten Funktionsblock übergeben.

| Name | Datentyp | Initialwert | Kommentar |
| :--- | :--- | :--- | :--- |
| `Pin` | `USINT` (Unsigned Short Integer) | 255 | Definiert die Nummer des anzusteuernden Eingangspins oder Kanals. |

### **Daten-Ausgänge**
Dieser Datentyp hat keine eigenen Datenausgänge.

## Funktionsweise
Der Datentyp `logiBUS_DI_S` ist eine reine Datenhaltungsstruktur. Seine Funktionsweise beschränkt sich darauf, den Wert des Mitglieds `Pin` zu speichern. Der Initialwert `255` dient häufig als Standard- oder ungültiger Wert (z.B. "nicht konfiguriert"). Ein konkreter I/O-Funktionsblock, der diesen Struct als Eingang erwartet, liest den `Pin`-Wert aus und verwendet ihn, um die Hardware-Adressierung für den digitalen Eingang vorzunehmen.

## Technische Besonderheiten
*   **Datentyp `USINT`:** Die Verwendung eines `USINT` (0...255) für den Pin legt nahe, dass bis zu 256 verschiedene Eingangskanäle pro Gerät oder Modul adressierbar sind.
*   **Initialwert 255:** Dieser Wert liegt außerhalb des typischen Nutzbereichs (0...n, wobei n<255) und kann von der Anwendungslogik oder dem Treiber als Indikator für eine nicht vorgenommene Konfiguration interpretiert werden.
*   **StructuredType:** Als `StructuredType` ist dieser Baustein kein ausführbarer Funktionsblock, sondern ein reiner Datentyp, der in der Deklaration von Variablen und Schnittstellen anderer FBs verwendet wird.

## Zustandsübersicht
Da es sich um einen passiven Datentyp handelt, besitzt `logiBUS_DI_S` keinen Zustandsautomaten.

## Anwendungsszenarien
*   **Konfiguration von I/O-Blöcken:** Primär dient dieser Struct als Eingabeparameter für Funktionsblöcke wie `logiBUS_DI` oder ähnliche, die den eigentlichen Lesevorgang von einem digitalen Eingang durchführen.
*   **Parametrisierung über Netzwerke:** Die Struktur kann leicht in übergeordneten Steuerungen (z.B. einer SPS) instanziiert, konfiguriert (`Pin`-Nummer gesetzt) und an untergeordnete I/O-Knoten oder Treiberbausteine weitergegeben werden.
*   **Strukturierte Programmierung:** Ermöglicht eine saubere Kapselung der Konfigurationsdaten für digitale Eingänge, was die Wiederverwendbarkeit und Lesbarkeit des Codes erhöht.

## Vergleich mit ähnlichen Bausteinen
*   **Einfache `USINT` Variable:** Anstelle eines Structs könnte direkt eine `USINT`-Variable verwendet werden. Der Struct bietet jedoch semantische Klarheit (der Name `logiBUS_DI_S` beschreibt den Zweck) und ist leichter erweiterbar, falls zukünftig weitere Konfigurationsparameter (wie Filterzeit, Invertierung) hinzugefügt werden müssen.
*   **Gerätespezifische Structs:** Innerhalb des logiBUS-Ökosystems könnte es ähnliche Structs für andere Funktionen geben (z.B. `logiBUS_DO_S` für digitale Ausgänge, `logiBUS_AI_S` für analoge Eingänge). Diese würden eine einheitliche Konfigurationsphilosophie über verschiedene I/O-Typen hinweg ermöglichen.

## Fazit
Der `logiBUS_DI_S` ist ein grundlegender und spezifischer Konfigurationsbaustein für die logiBUS-I/O-Architektur. Als strukturierter Datentyp bietet er eine standardisierte und klare Methode, um die Zieladresse (Pin) für einen digitalen Eingang zu definieren. Seine Stärke liegt in der Einfachheit und der Vorbereitung auf mögliche Erweiterungen, was ihn zu einem nützlichen Bestandteil für die strukturierte Konfiguration von Feldbussystemen in 4diac FORTE macht.