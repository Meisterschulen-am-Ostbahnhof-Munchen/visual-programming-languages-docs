# SchieberAuxInStruct

```{index} single: SchieberAuxInStruct
```

* * * * * * * * * *
## Einleitung
Der strukturierte Datentyp `SchieberAuxInStruct` dient der Bündelung von Informationen zur visuellen Darstellung eines Hilfselements (AUX) in einer Schieber-Steuerung. Er kombiniert die Angabe eines Bildes mit einer Hintergrundfarbe, um die grafische Repräsentation eines Hilfseingangs oder -elements zu definieren.

## Schnittstellenstruktur
Dieser Baustein ist ein strukturierter Datentyp (Struct) und besitzt daher keine Ereignis- oder Adapterschnittstellen. Seine Struktur besteht aus den folgenden zwei Datenelementen:

### **Daten-Eingänge**
Da es sich um einen Datentyp handelt, existieren keine direkten Eingänge. Die Struktur wird als Ganzes an Daten-Eingängen anderer Funktionsblöcke verwendet.

### **Daten-Ausgänge**
Da es sich um einen Datentyp handelt, existieren keine direkten Ausgänge. Die Struktur wird als Ganzes an Daten-Ausgängen anderer Funktionsblöcke verwendet.

### **Strukturierte Elemente**
*   **`Picture`** (`logiBUS::utils::sequence::schieber::SchieberStruct`):
    *   **Kommentar:** `u16ObjId for Picture`
    *   **Beschreibung:** Enthält die Kennung (Object ID) für das anzuzeigende Bild des Hilfselements. Der zugrundeliegende Typ `SchieberStruct` stellt vermutlich die notwendigen Informationen zur Referenzierung und Handhabung des Bildobjekts bereit.

*   **`u8Colour`** (`logiBUS::utils::sequence::schieber::SchieberColorStruct`):
    *   **Kommentar:** `Background Color of the AUX`
    *   **Beschreibung:** Definiert die Hintergrundfarbe des Hilfselements. Der Typ `SchieberColorStruct` spezifiziert die verwendete Farbe, wahrscheinlich in einem für das Zielsystem (z.B. ein HMI) geeigneten Format.

## Funktionsweise
Der Datentyp `SchieberAuxInStruct` ist eine passive Datenstruktur. Seine Funktion besteht ausschließlich darin, die beiden Eigenschaften `Picture` (Bild) und `u8Colour` (Hintergrundfarbe) logisch zu einem einzigen, wiederverwendbaren Datensatz zusammenzufassen. Er wird verwendet, um diese visuellen Attribute konsistent zwischen verschiedenen Funktionsblöcken innerhalb einer Anwendung zu transportieren.

## Technische Besonderheiten
*   **Namespaces:** Der Datentyp und seine Komponenten sind im Paket `logiBUS::utils::sequence::schieber` definiert, was auf eine spezifische Anwendung in der Steuerungstechnik für Landmaschinen (Agrartechnik) hindeutet.
*   **Typisierung:** Die Verwendung spezifischer, benutzerdefinierter Typen (`SchieberStruct`, `SchieberColorStruct`) für die Mitglieder fördert die Typsicherheit und Wiederverwendbarkeit im gesamten Projekt.

## Zustandsübersicht
Als reiner Datentyp besitzt `SchieberAuxInStruct` keinen internen Zustand oder Zustandsautomaten.

## Anwendungsszenarien
Dieser Datentyp wird typischerweise in SPS-Steuerungen (speicherprogrammierbare Steuerungen) für mobile Arbeitsmaschinen verwendet, insbesondere in:
*   **HMI-Konfiguration:** Zur Definition des Erscheinungsbildes von Bedien- oder Anzeigeelementen (z.B. Schieber, Taster, Statusleuchten) auf einem Bedienpanel.
*   **Sequenzsteuerungen:** Innerhalb von Ablaufsteuerungen, bei denen sich die Darstellung eines Elements (Farbe, Bild) in Abhängigkeit vom Prozesszustand ändern soll.
*   **Datenkapselung:** Vereinfachung der Parametrisierung von Funktionsblöcken, die das Aussehen eines "AUX"-Elements steuern, indem alle visuellen Parameter in einer einzigen Variable übergeben werden können.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken (FBs) besitzt dieser Baustein keinerlei Algorithmus oder Verhaltenslogik. Er ist mit einem `STRUCT` in der IEC 61131-3 oder einer `class`/`struct` in höheren Programmiersprachen vergleichbar. Andere ähnliche Elemente wären einfache Datentypen (z.B. `ARRAY` von Einzelwerten), die jedoch die semantische Gruppierung und Typsicherheit dieses strukturierten Typs nicht bieten.

## Fazit
Der `SchieberAuxInStruct` ist ein grundlegender, wiederverwendbarer Datentyp zur Modellierung der visuellen Eigenschaften eines Hilfselements in einer spezifischen Steuerungsumgebung. Durch die Kapselung von Bild- und Farbinformationen trägt er zur besseren Strukturierung, Lesbarkeit und Wartbarkeit des Anwendungscodes bei. Seine Verwendung ist vor allem in Projekten mit komplexen Benutzerschnittstellen oder statusabhängigen Visualisierungen vorteilhaft.