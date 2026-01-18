# colours

```{index} single: colours
```

* * * * * * * * * *
## Einleitung
Das globale Konstantenpaket `colours` definiert eine Reihe von benannten Konstanten für Farbwerte. Diese Konstanten repräsentieren einen Satz von 16 vordefinierten Farben, die durch numerische Werte des Typs `USINT` (Unsigned Short Integer) kodiert sind. Die Verwendung solcher Konstanten verbessert die Lesbarkeit und Wartbarkeit von IEC 61499-Anwendungen, da anstelle von magischen Zahlen aussagekräftige Bezeichner wie `COLOR_RED` oder `COLOR_BLUE` verwendet werden können.

## Schnittstellenstruktur
Bei einem globalen Konstantenpaket handelt es sich nicht um einen Funktionsblock im klassischen Sinne, daher existieren keine Ereignis- oder Datenschnittstellen. Stattdessen stellt das Paket eine Sammlung von Konstantendeklarationen zur Verfügung, die in anderen Funktionsblöcken oder Programmen innerhalb desselben Projekts oder Namensraums importiert und genutzt werden können.

### **Ereignis-Eingänge**
*Nicht zutreffend.* Globale Konstanten besitzen keine Ereigniseingänge.

### **Ereignis-Ausgänge**
*Nicht zutreffend.* Globale Konstanten besitzen keine Ereignisausgänge.

### **Daten-Eingänge**
*Nicht zutreffend.* Globale Konstanten besitzen keine Dateneingänge.

### **Daten-Ausgänge**
*Nicht zutreffend.* Globale Konstanten besitzen keine Datenausgänge.

### **Adapter**
*Nicht zutreffend.* Globale Konstanten besitzen keine Adapterschnittstellen.

## Funktionsweise
Das Paket `colours` deklariert 16 Konstanten vom Datentyp `USINT`. Jeder Konstanten wird ein fester numerischer Wert zugewiesen, der eine spezifische Farbe repräsentiert. Die Werte reichen von `USINT#0` bis `USINT#15`. Sobald das Paket in eine Anwendung oder einen Funktionsblock importiert ist, können diese Konstantennamen überall dort verwendet werden, wo ein `USINT`-Wert erwartet wird. Der Compiler ersetzt den Konstantennamen bei der Übersetzung durch den zugewiesenen numerischen Wert.

## Technische Besonderheiten
*   **Datentyp:** Alle Konstanten sind vom Typ `USINT` (Unsigned Short Integer), einem vorzeichenlosen 8-Bit-Datentyp.
*   **Wertebereich:** Die definierten Werte liegen im Bereich von 0 bis 15 und passen somit gut in den Wertebereich des `USINT`-Typs.
*   **Namenskonvention:** Die Konstantennamen folgen der Konvention `COLOR_<FARBNAME>` (z.B., `COLOR_GREEN`), was sie leicht identifizierbar macht.
*   **Kompilierung:** Als `CONSTANT` deklarierte Werte werden zur Kompilierzeit festgelegt und können zur Laufzeit nicht verändert werden.

## Zustandsübersicht
*Nicht zutreffend.* Da es sich um statische, unveränderliche Werte handelt, besitzen globale Konstanten keinen Zustandsautomaten.

## Anwendungsszenarien
Dieses Konstantenpaket ist besonders nützlich in Anwendungen, die eine begrenzte Palette von Farben für Benutzeroberflächen, visuelle Statusanzeigen (z.B. auf HMIs oder Bedienterminals) oder zur Kennzeichnung von Prozesszuständen benötigen. Typische Einsatzgebiete sind:
*   **Visualisierung:** Zuweisung von Farben zu verschiedenen Maschinenzuständen (z.B. Grün = Betrieb, Rot = Fehler, Gelb = Warnung).
*   **ISOBUS-konforme Anwendungen (UT/Universal Terminal):** Standardisierung von Farbwerten in landwirtschaftlichen Anwendungen, die das ISOBUS-Protokoll verwenden, um eine konsistente Darstellung auf verschiedenen Terminalgeräten zu gewährleisten.
*   **Code-Verbesserung:** Ersetzen von undurchsichtigen Zahlenwerten in Algorithmen oder Konfigurationen durch selbsterklärende Bezeichner.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken, die Logik ausführen oder Daten verarbeiten, stellt ein globales Konstantenpaket lediglich benannte Werte bereit. Alternativen wären:
1.  **Direkte Verwendung numerischer Werte:** Führt zu schlechter lesbarem und schwerer wartbarem Code ("Magic Numbers").
2.  **Definition von Konstanten innerhalb jedes Funktionsblocks:** Führt zu Redundanz und erschwert die zentrale Änderung von Werten.
3.  **Verwendung von Aufzählungstypen (ENUM):** Bietet eine noch stärkere Typsicherheit, ist in der IEC 61499-Standardbibliothek jedoch nicht direkt als globales Konstrukt verfügbar. Die Verwendung von `USINT`-Konstanten ist eine praktische und weit verbreitete Alternative.

## Fazit
Das globale Konstantenpaket `colours` ist ein einfaches aber effektives Werkzeug zur Strukturierung und Verbesserung von IEC 61499-Applikationen. Durch die Bereitstellung einer standardisierten Farbpalette als benannte Konstanten fördert es die Code-Qualität, erleichtert die Wartung und unterstützt die Entwicklung konsistenter und verständlicher Steuerungsanwendungen, insbesondere im Umfeld von ISOBUS und visuellen Schnittstellen.