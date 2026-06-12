# NAMEFIELD_T



* * * * * * * * * *

## Einleitung
Der Datentyp `NAMEFIELD_T` repräsentiert eine strukturierte Datenkomponente zur Abbildung des ISO 11783 (ISOBUS) NAME-Feldes gemäß Teil 5 der Norm und den Konventionen der Implementierten Funktionsmodule (IFM). Dieser strukturierte Datentyp dient der eindeutigen Identifikation und Adressierung von Steuergeräten (ECUs) in einem ISOBUS-Netzwerk. Er fasst alle für die Geräteidentifikation erforderlichen Parameter in einer einzigen Datenstruktur zusammen.

## Schnittstellenstruktur
`NAMEFIELD_T` ist ein strukturierter Datentyp (STRUCT), der aus zehn einzelnen Variablen besteht. Jede Variable entspricht einem definierten Teil des 64-Bit-NAME-Feldes im ISOBUS-Protokoll.

### **Daten-Eingänge**
*(Als strukturierter Datentyp besitzt `NAMEFIELD_T` keine Ereignisse, sondern ausschließlich Datenfelder. Diese werden hier als Bestandteile der Struktur aufgeführt.)*

| Name | Datentyp | Initialwert | Kommentar |
| :--- | :--- | :--- | :--- |
| `bSelfConf` | `BOOL` | `TRUE` | Gibt an, ob es sich um eine selbstkonfigurierbare Adress-ECU handelt. |
| `bIndGroup` | `BYTE` | `16#FF` | Weist den NAME einer Industriegruppe zu (Bereich 0..7). |
| `bDevClassInst` | `BYTE` | `16#FF` | Identifikator, wenn eine Geräteklasse mehrfach im Netzwerk vorkommt (0..15). |
| `bDevClass` | `BYTE` | `16#FF` | ISO-definierte Geräteklasse (0..127). |
| `bReserved` | `BOOL` | `TRUE` | Reserviertes Bit (nicht verwendet). |
| `bFunction` | `BYTE` | `16#FF` | ISO-definierte Funktion, entspricht der Source Address (SA) (0..255). |
| `bFunctionInst` | `BYTE` | `16#FF` | Untergruppe einer Funktion (0..31). |
| `bEcuInstance` | `BYTE` | `16#FF` | Gibt an, welches Steuergerät einer bestimmten Funktion zugeordnet ist (0..7). |
| `wManufCode` | `WORD` | `16#FFFF` | ISO-definierter Herstellercode (0..2047). |
| `dwIdentNumb` | `DWORD` | `16#FFFFFFFF` | Eindeutige Seriennummer; wird verwendet, wenn der NAME im selben Netzwerk nicht eindeutig ist (0..2.097.151). |

### **Daten-Ausgänge**
*(Nicht zutreffend, da es sich um einen reinen Datentyp handelt.)*

### **Adapter**
*(Nicht zutreffend, da es sich um einen reinen Datentyp handelt.)*

## Funktionsweise
Der Datentyp `NAMEFIELD_T` ist eine passive Datenstruktur. Seine Hauptaufgabe ist die strukturierte Speicherung und Übertragung der Parameter, die zusammen den 64-Bit-ISOBUS-NAME bilden. Jede Variable innerhalb der Struktur belegt einen spezifischen Bitbereich innerhalb dieses Gesamtfeldes. Die Initialwerte (`16#FF`, `16#FFFF`, `16#FFFFFFFF`) repräsentieren typischerweise einen undefinierten oder nicht zugewiesenen Zustand.

## Technische Besonderheiten
*   **Bitgenaue Abbildung:** Die Struktur bildet das binäre Layout des ISO-NAME-Feldes direkt ab, was eine effiziente Serialisierung und Deserialisierung für die Kommunikation über das CAN-Bus-Protokoll ermöglicht.
*   **Initialwerte:** Die gewählten Initialwerte (maximale Werte für die jeweiligen Datentypen) signalisieren klar einen nicht initialisierten oder Platzhalter-Zustand.
*   **ISOBUS-Konformität:** Die Benennung und Aufteilung der Felder folgt strikt der ISO 11783-5 Spezifikation und den erweiterten IFM-Konventionen.

## Zustandsübersicht
Da es sich um einen Datentyp und nicht um einen Funktionsbaustein handelt, existiert keine Zustandsmaschine. Der "Zustand" ist durch die konkreten Werte der zehn enthaltenen Variablen definiert.

## Anwendungsszenarien
Der Datentyp `NAMEFIELD_T` wird primär in ISOBUS-konformen Steuerungsapplikationen verwendet, beispielsweise in der Land- und Forsttechnik oder im Baumaschinenbereich.
*   **Geräteidentifikation:** Als Teil von Nachrichten (z.B. im Address Claim Prozess) zur Identifikation eines Teilnehmers im Netzwerk.
*   **Datenhaltung:** Zur Speicherung der eigenen Geräteidentität innerhalb einer ECU-Software.
*   **Filterung:** Zur Konfiguration von Nachrichtenfiltern basierend auf Geräteklasse, Funktion oder Hersteller.
*   **Diagnose:** Zur eindeutigen Identifikation von Geräten in Diagnose- und Konfigurationstools.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsbausteinen (FBs) wie `E_SR` oder `E_CYCLE` ist `NAMEFIELD_T` ein reiner **Datentyp** (Structured Data Type). Er enthält keine Algorithmen, Ereignisse oder einen ausgeführten Code.
*   **Ähnlichkeit zu anderen STRUCTs:** Er ist vergleichbar mit anderen strukturierten Datentypen in 4diac (z.B. für komplexe Messwerte), jedoch spezialisiert auf das ISOBUS-Protokoll.
*   **Unterschied zu Basis-Datentypen:** Während Basistypen wie `INT` oder `BOOL` einzelne Werte halten, fasst `NAMEFIELD_T` mehrere logisch zusammengehörige Werte zu einer Einheit zusammen.

## Fazit
Der Datentyp `NAMEFIELD_T` ist ein essentielles Hilfsmittel für die Entwicklung von ISOBUS-konformen Steuerungsapplikationen mit 4diac FORTE. Er abstrahiert die komplexe Bitstruktur des ISO-NAME-Feldes in eine leicht handhabbare, stark typisierte Datenstruktur. Dies fördert die Code-Wiederverwendbarkeit, verbessert die Lesbarkeit und reduziert Fehler bei der Handhabung von Geräteidentifikationsdaten. Seine Verwendung ist standardkonform und empfiehlt sich für alle Projekte, die ISOBUS-Kommunikation implementieren.