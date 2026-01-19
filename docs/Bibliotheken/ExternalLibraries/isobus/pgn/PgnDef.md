# PgnDef

```{index} single: PgnDef
```

* * * * * * * * * *
## Einleitung
`PgnDef` ist eine Sammlung globaler Konstanten für die 4diac-IDE, die Parameter Group Numbers (PGNs) für ISOBUS- und NMEA-2000-Kommunikationsprotokolle definiert. Diese Konstanten repräsentieren numerische Identifikatoren für spezifische Nachrichtentypen, die in der landwirtschaftlichen und maritimen Fahrzeugvernetzung verwendet werden. Die Sammlung dient als zentrale Referenzbibliothek, um in IEC 61499-Applikationen auf standardisierte PGNs zugreifen zu können, was die Lesbarkeit und Wartbarkeit des Codes verbessert.

## Schnittstellenstruktur
`PgnDef` ist ein `GlobalConstants`-Element und besitzt daher keine ereignis- oder datenflussbasierten Schnittstellen im herkömmlichen Sinne eines Funktionsblocks. Stattdessen stellt es eine Sammlung von Konstanten zur Verfügung, die in anderen Funktionsblöcken oder Programmen deklariert und verwendet werden können.

### **Ereignis-Eingänge**
Nicht vorhanden. Dies ist eine Konstantendefinition.

### **Ereignis-Ausgänge**
Nicht vorhanden. Dies ist eine Konstantendefinition.

### **Daten-Eingänge**
Nicht vorhanden. Dies ist eine Konstantendefinition.

### **Daten-Ausgänge**
Nicht vorhanden. Dies ist eine Konstantendefinition.

### **Adapter**
Nicht vorhanden. Dies ist eine Konstantendefinition.

## Funktionsweise
`PgnDef` selbst hat keine ausführbare Logik. Es definiert lediglich eine umfangreiche Liste von Konstanten vom Datentyp `UDINT` (Unsigned Double Integer). Jede Konstante ist ein PGN-Wert, der in hexadezimaler Notation (`UDINT#16#XXXX`) initialisiert wird und einen menschenlesbaren Kommentar mit dem PGN-Namen und oft einer Referenz zum entsprechenden Standard (z.B. ISO 11783-7) enthält. Andere Funktionsblöcke können diese Konstanten über ihren vollqualifizierten Namen (z.B. `isobus::pgn::PGN_HEARTBEAT`) importieren und in ihrer Logik verwenden, um Nachrichten zu identifizieren oder zu erzeugen.

## Technische Besonderheiten
*   **Umfangreiche Abdeckung:** Die Sammlung enthält PGNs aus einer Vielzahl von Standards, einschließlich ISO 11783 (ISOBUS, Teile 3-7, 12, 13), SAE J1939 (71, 73, 75) und NMEA 2000.
*   **Organisierte Struktur:** Die Konstanten sind in logischen Gruppen kommentiert (PDU1/Group Functions, PDU2, J1939-71, ISO 11783-7, Diagnose (J1939-73), Generator Sets (J1939-75), NMEA).
*   **Datentyp:** Alle PGNs sind als `UDINT` (32-Bit, vorzeichenlos) definiert, was dem adressierbaren Bereich der Protokolle entspricht.
*   **Paketzuordnung:** Die Konstanten sind dem Paket `isobus::pgn` zugeordnet, was eine klare Namensraumtrennung ermöglicht.

## Zustandsübersicht
Nicht zutreffend, da es sich um eine statische Konstantendeklaration handelt.

## Anwendungsszenarien
*   **ISOBUS-ECU-Entwicklung:** Bei der Entwicklung von Steuergeräten (ECUs) für Traktoren oder Anbaugeräte, die über ein ISOBUS-Netzwerk kommunizieren.
*   **NMEA-2000-Integration:** In maritimen Anwendungen zur Integration von Schiffselektronik wie GPS-Empfängern, Tiefenmessern oder Motorensteuerungen.
*   **Protokoll-Implementierung:** Als Grundlage für die Implementierung von Protokoll-Stacks (z.B. für Transportprotokolle wie TP/CM oder ETP/CM).
*   **Nachrichtenfilterung:** In Gateway- oder Bridge-Funktionsblöcken, um eingehende Nachrichten anhand ihrer PGN zu filtern und weiterzuleiten.
*   **Diagnose-Tools:** In Applikationen zur Diagnose und Überwachung von Fahrzeugnetzwerken, um empfangene Nachrichten korrekt zu benennen und anzuzeigen.

## Vergleich mit ähnlichen Bausteinen
*   **Einfache `VAR_GLOBAL CONSTANT`-Deklarationen:** `PgnDef` bietet gegenüber manuell im Funktionsblock deklarierten Konstanten den Vorteil der Zentralisierung, Wiederverwendbarkeit und Vermeidung von Redundanz und Tippfehlern.
*   **Enumerations (ENUM):** Während ENUMs in IEC 61499 für geordnete Listen verwendet werden können, ist `PgnDef` als Sammlung diskreter, nicht notwendigerweise aufeinanderfolgender Werte besser geeignet. Konstanten bieten zudem mehr Flexibilität bei der Wertzuweisung (hexadezimal).
*   **Spezifische Protokoll-FBs:** Im Gegensatz zu Funktionsblöcken, die eine bestimmte Protokollfunktion implementieren (z.B. ein `ADDRESS_CLAIM`-FB), ist `PgnDef` ein reines Hilfsmittel zur Referenzierung und enthält keine aktive Logik.

## Fazit
Die `PgnDef`-Konstantensammlung ist ein wesentliches Hilfsmittel für die Entwicklung von IEC 61499-basierten Applikationen in den Domänen der mobilen Arbeitsmaschinen (ISOBUS) und der maritimen Elektronik (NMEA 2000). Sie fördert die Standardisierung, verbessert die Codequalität durch verbesserte Lesbarkeit und reduziert Fehler durch die Verwendung zentral definierter und getesteter Werte. Für jeden Entwickler, der mit diesen Protokollen in 4diac arbeitet, stellt `PgnDef` eine wertvolle und wahrscheinlich unverzichtbare Ressource dar.