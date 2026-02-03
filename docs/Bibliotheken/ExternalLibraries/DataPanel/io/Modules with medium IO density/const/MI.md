# MI

```{index} single: MI
```
## 🎧 Podcast

* [Eclipse 4diac 3.0: ST-Interpreter, FBE und 7200 Commits – Der Turbo für verteilte Automatisierung](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Eclipse-4diac-3-0-ST-Interpreter--FBE-und-7200-Commits--Der-Turbo-fr-verteilte-Automatisierung-e3a5cpl)
* [Industrie 4.0: Die Magie selbstkonfigurierender Systeme mit fortiss, IEC 61499 und Eclipse 4diac](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Industrie-4-0-Die-Magie-selbstkonfigurierender-Systeme-mit-fortiss--IEC-61499-und-Eclipse-4diac-e368lv5)
* [From Pyramid to Plug-and-Play: The Rise of Self-Configurable Industrial Automation](https://podcasters.spotify.com/pod/show/eclipse-4diac-en/episodes/From-Pyramid-to-Plug-and-Play-The-Rise-of-Self-Configurable-Industrial-Automation-e368lvk)
* [Der E_CTU in der IEC 61499: Ereignisgesteuertes Zählen und warum der Minimalist im Maschinenbau überzeugt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_CTU-in-der-IEC-61499-Ereignisgesteuertes-Zhlen-und-warum-der-Minimalist-im-Maschinenbau-berzeugt-e3a9qnq)
* [Der E_PERMIT-Baustein: Der "Türsteher" für Ereignisse in IEC 61499-Systemen entschlüsselt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_PERMIT-Baustein-Der-Trsteher-fr-Ereignisse-in-IEC-61499-Systemen-entschlsselt-e3681m5)

## 📺 Video

* [Die große Migration](https://www.youtube.com/watch?v=XcBu7y6ch4E)

## Einleitung
Die MI Global Constants stellen eine Sammlung von Konstanten für Module mit mittlerer I/O-Dichte dar. Diese Konstantendefinitionen werden in der 4diac-IDE verwendet, um einheitliche und wiederverwendbare Adressierungsinformationen für I/O-Module bereitzustellen.

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
Bei den MI Global Constants handelt es sich um eine reine Konstantendeklaration ohne aktive Funktionalität. Die Konstanten definieren Adressbereiche für 16 verschiedene I/O-Module (MI_00 bis MI_15) mit jeweils einem eindeutigen numerischen Wert im Bereich von 224 bis 239.

## Technische Besonderheiten
- Alle Konstanten sind vom Typ USINT (Unsigned Short Integer)
- Die Werte bilden einen fortlaufenden Bereich von 224 bis 239
- Konstanten sind als global und konstant deklariert
- Package-Zuordnung: DataPanel::io::MI::const

## Zustandsübersicht
*Keine Zustandsübergänge vorhanden, da es sich um statische Konstantendefinitionen handelt*

## Anwendungsszenarien
- Adressierung von I/O-Modulen in Steuerungsanwendungen
- Wiederverwendung in verschiedenen Funktionsblöcken
- Zentrale Verwaltung von Moduladressen
- Vereinfachung der Projektkonfiguration

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konstantendefinitionen bietet MI spezifische Adressen für Module mit mittlerer I/O-Dichte. Andere Konstantensammlungen könnten unterschiedliche Adressbereiche oder Modultypen abdecken.

## Fazit
Die MI Global Constants bieten eine praktische und zentrale Möglichkeit, Adressinformationen für I/O-Module zu verwalten. Durch die Verwendung dieser Konstanten wird die Wartbarkeit und Lesbarkeit von Steuerungsprogrammen verbessert, da Änderungen an Moduladressen zentral vorgenommen werden können.