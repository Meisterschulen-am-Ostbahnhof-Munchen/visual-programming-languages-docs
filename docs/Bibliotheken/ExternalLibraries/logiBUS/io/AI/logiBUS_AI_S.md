# logiBUS_AI_S

```{index} single: logiBUS_AI_S
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
Der Funktionsblock `logiBUS_AI_S` ist ein strukturierter Datentyp (Struct), der zur Konfiguration eines analogen Eingangskanals (AI - Analog Input) innerhalb der logiBUS-Bibliothek dient. Er definiert die grundlegende Parameterstruktur, die benötigt wird, um einen physischen Pin eines logiBUS-Hardwaremoduls für die Erfassung analoger Signale zu adressieren.

## Schnittstellenstruktur
Dies ist ein strukturierter Datentyp (STRUCT), daher besitzt er keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne eines ausführbaren Funktionsblocks. Seine Struktur besteht aus einem einzelnen Datenelement.

### **Daten-Eingänge**
Die Struktur selbst enthält folgendes Datenelement, das als Eingabeparameter für einen konfigurierenden Funktionsblock (z.B. `logiBUS_AI`) dient:

*   **`Pin`** (`USINT`): Dieser Wert spezifiziert den physischen Hardware-Pin oder Kanal des logiBUS-Moduls, von dem das analoge Signal gelesen werden soll. Der Standardwert ist `255`, was typischerweise als ungültiger oder nicht konfigurierter Zustand interpretiert wird.

## Funktionsweise
Der Datentyp `logiBUS_AI_S` ist eine reine Datenstruktur und besitzt keine aktive Funktionsweise. Er dient als Container für Konfigurationsdaten. Seine Hauptaufgabe ist die parametrische Beschreibung eines analogen Eingangs. Ein übergeordneter IO-Manager- oder Gerätetreiber-Funktionsblock (wie `logiBUS_AI`) liest die in einer Instanz dieser Struktur gespeicherten Werte aus und verwendet sie, um die entsprechende Hardware-Schnittstelle korrekt einzurichten und anzusteuern.

## Technische Besonderheiten
*   **Initialwert:** Das Mitglied `Pin` ist mit dem Initialwert `255` vordefiniert. Dieser Wert liegt außerhalb des typischen Bereichs gültiger Pin-Nummern (oft 0..n) und kann daher zur Erkennung einer nicht initialisierten oder fehlerhaften Konfiguration genutzt werden.
*   **Typensicherheit:** Die Verwendung eines strukturierten Datentyps anstelle einzelner, unverbundener Parameter erhöht die Typsicherheit und Wartbarkeit des Codes in der 4diac IDE.
*   **Bibliothekszugehörigkeit:** Der Typ ist Teil des Pakets `logiBUS::io::AI`, was seine Zugehörigkeit zur logiBUS-IO-Bibliothek für analoge Eingänge klar kennzeichnet.

## Anwendungsszenarien
Dieser Struct wird ausschließlich in Szenarien verwendet, in denen logiBUS-Hardware mit analogen Eingangsmodulen (z.B. für Spannungs- oder Strommessung) in eine 4diac FORTE-Applikation integriert wird. Typische Anwendungen sind:
*   Prozessüberwachung (Temperatur, Druck, Füllstand via Sensoren)
*   Erfassung von Steuerspannungen
*   Konfiguration von Mehrkanal-Messsystemen, bei denen für jeden Kanal eine separate Instanz von `logiBUS_AI_S` angelegt wird.

## Vergleich mit ähnlichen Bausteinen
Innerhalb der logiBUS-Bibliothek existieren ähnliche strukturierte Datentypen für andere IO-Funktionen, wie z.B. `logiBUS_DI_S` für digitale Eingänge oder `logiBUS_AO_S` für analoge Ausgänge. Diese unterscheiden sich primär durch ihren kontextspezifischen Namen und sind für die jeweilige Art der Signalverarbeitung vorgesehen. Der grundlegende Aufbau (ein `Pin`-Feld) ist jedoch oft identisch oder sehr ähnlich.

## Fazit
Der `logiBUS_AI_S`-Datentyp ist ein essentielles Konfigurationselement für die Nutzung analoger Eingänge mit logiBUS in 4diac. Als einfache, gut definierte Struktur ermöglicht er eine klare und zentrale Verwaltung der Hardware-Parameter und bildet die Grundlage für eine zuverlässige Anbindung von Analogsensoren an ein IEC 61499-Steuerungssystem.