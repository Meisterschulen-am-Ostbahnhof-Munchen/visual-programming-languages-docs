# LO

```{index} single: LO
```

* * * * * * * * * *
## 🎧 Podcast

* [4diac IDE: Dein "Hello World" der Automatisierung – Das Blinking Tutorial Lokal](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)
* [Eclipse 4diac and FORTE: Unlocking Next-Gen Industrial Automation with Open-Source Power](https://podcasters.spotify.com/pod/show/eclipse-4diac-en/episodes/Eclipse-4diac-and-FORTE-Unlocking-Next-Gen-Industrial-Automation-with-Open-Source-Power-e3682iu)
* [Feldgeräte: Augen, Ohren und Hände der industriellen Automatisierung – Warum diese unsichtbare Technologie so entscheidend ist](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Feldgerte-Augen--Ohren-und-Hnde-der-industriellen-Automatisierung--Warum-diese-unsichtbare-Technologie-so-entscheidend-ist-e375g6u)
* [Future Automation Unlocked: Powering "Plug & Produce" and Protecting Your Privacy](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Future-Automation-Unlocked-Powering-Plug--Produce-and-Protecting-Your-Privacy-e376pbc)
* [Industrial Revolution Reloaded: Unpacking Plug & Produce, Data Privacy, and ETFA 2025](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Industrial-Revolution-Reloaded-Unpacking-Plug--Produce--Data-Privacy--and-ETFA-2025-e376pid)

## 📺 Video

* [06. Mai 2025 Tag 6 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=g-LuUu-QFcI)
* [15. Apr. 2025  Tag 1 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=tlZC5rN_CUI)
* [17. Apr. 2025 Tag 2 von logiBUS® Schulungsreihe (D)](https://www.youtube.com/watch?v=hy2S94jOVi0)
* [2025 11 15 12 35 11 Montage Hutschienenmoped logiBUS® -- Teil 3 -- Gehäuse](https://www.youtube.com/watch?v=MPm4vLmD5RE)
* [2025 11 15 12 52 26 Montage Hutschienenmoped logiBUS® -- Teil 4 -- Aufbauten](https://www.youtube.com/watch?v=WeowCxZW70Y)

## Einleitung
LO ist eine globale Konstantendefinition für Module mit geringer I/O-Dichte. Diese Konstanten definieren spezifische Adressbereiche für I/O-Module und werden in der 4diac-IDE zur Konfiguration von Steuerungssystemen verwendet.

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
Bei LO handelt es sich um globale Konstanten, die als statische Werte definiert sind. Die Konstanten repräsentieren Adressbereiche für I/O-Module mit geringer Dichte und werden zur Kompilierzeit in die Anwendung integriert.

## Technische Besonderheiten
- Alle Konstanten sind vom Typ USINT (Unsigned Short Integer)
- Wertebereich: 217 bis 224
- Statische Initialisierung zur Kompilierzeit
- Konstanten sind unveränderlich während der Laufzeit

## Zustandsübersicht
*Keine Zustandsübergänge vorhanden, da es sich um statische Konstanten handelt*

## Anwendungsszenarien
- Adressierung von I/O-Modulen mit geringer Dichte
- Konfiguration von Hardware-Schnittstellen
- Verwendung in Verbindung mit spezifischen I/O-Treibern
- Vereinfachung der Hardware-Konfiguration durch zentrale Konstantendefinition

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen globalen Konstanten-Bausteinen bietet LO spezifische Adressbereiche für Module mit geringer I/O-Dichte, während andere Bausteine möglicherweise andere Adressbereiche oder Konstantentypen definieren.

## Fazit
Die LO-Konstanten bieten eine strukturierte und zentrale Möglichkeit zur Definition von Hardware-Adressen für I/O-Module mit geringer Dichte. Durch die Verwendung dieser globalen Konstanten wird die Wartbarkeit und Lesbarkeit von Steuerungsprogrammen verbessert.