# ISONETEVENT_T

* * * * * * * * * *
## Einleitung
Der Datentyp `ISONETEVENT_T` ist eine Struktur (Structured Type), die zur Beschreibung eines Netzwerkereignisses innerhalb eines ISOBUS-Netzwerks dient. Er kapselt alle relevanten Informationen, die benötigt werden, um ein Ereignis im Zusammenhang mit der Verwaltung von Netzwerkteilnehmern (Control Functions) zu identifizieren und zu verarbeiten. Dieser Typ wird typischerweise in Callback-Funktionen verwendet, um über Zustandsänderungen im Netzwerk zu informieren.

## Schnittstellenstruktur
Die Struktur `ISONETEVENT_T` besteht aus den folgenden sechs Elementen:

### **Daten-Elemente**
*   **`eNetEvent`** (Typ: `USINT`, Initialwert: `ISO_NETEVENT_e::Isonet_Last`)
    *   **Beschreibung:** Gibt an, welches spezifische Ereignis in der Netzwerk-Mitgliederverwaltung aufgetreten ist (z.B. Verbindungsaufbau, -abbruch, Adressänderung).
*   **`eMemberRefer`** (Typ: `SINT`, Initialwert: `ISOUSERHOME_e::notdef`)
    *   **Beschreibung:** Identifiziert, welches Netzwerkmitglied von dem Ereignis betroffen ist. Spezifiziert, ob es sich um den Besitzer des Callbacks, eine andere interne oder eine externe Control Function (CF) handelt.
*   **`s16OwnCfHnd`** (Typ: `INT`)
    *   **Beschreibung:** Das CF-Handle des Eintrags, für den der Callback ausgelöst wurde. Dies identifiziert die lokale Repräsentation des betroffenen Netzwerkteilnehmers.
*   **`s16Handle`** (Typ: `INT`)
    *   **Beschreibung:** Das Netzwerk-Mitglieder-Handle der beteiligten Control Function bzw. des Benutzers. Dies ist das Handle der CF, die das Ereignis verursacht hat (Event Source CF Handle).
*   **`u8SAMember`** (Typ: `USINT`)
    *   **Beschreibung:** Die aktuelle Quelladresse (Source Address, SA) des Netzwerkmitglieds zum Zeitpunkt des Ereignisses.
*   **`cfName`** (Typ: `isobus::pgn::CF_NAME_T`)
    *   **Beschreibung:** Der ISOBUS-Name der beteiligten Control Function. Dieser Name ist eine eindeutige Identifikation gemäß ISOBUS-Standard.

## Funktionsweise
Die Struktur `ISONETEVENT_T` fungiert als ein Container oder Nachrichtenobjekt. Wenn ein relevantes Netzwerkereignis eintritt (definiert durch `eNetEvent`), wird eine Instanz dieser Struktur mit den aktuellen Daten gefüllt und an eine registrierte Callback-Funktion übergeben. Die enthaltenen Daten ermöglichen es der empfangenden Softwarekomponente, das Ereignis genau zu klassifizieren und die betroffenen Netzwerkentitäten zu identifizieren (`eMemberRefer`, `s16OwnCfHnd`, `s16Handle`), deren aktuelle Adresse (`u8SAMember`) und ihren ISOBUS-Namen (`cfName`) zu kennen.

## Technische Besonderheiten
*   **Typisierung:** Es handelt sich um einen `StructuredType` innerhalb der 4diac IDE.
*   **Initialwerte:** Zwei Elemente (`eNetEvent`, `eMemberRefer`) besitzen definierte Initialwerte, die auf enumerierte Typen (`ISO_NETEVENT_e`, `ISOUSERHOME_e`) verweisen. Dies stellt einen definierten Ausgangszustand sicher.
*   **ISOBUS-Integration:** Die Struktur ist spezifisch für den ISOBUS-Kontext entworfen, was sich in der Verwendung des typspezifischen `CF_NAME_T` und der Parameterbezeichnungen (SA, CF) zeigt.
*   **Compiler-Paket:** Der Datentyp ist dem Paket `isobus::pgn` zugeordnet, was auf seine Zugehörigkeit zur ISOBUS Parameter Group Number (PGN) Verarbeitung hindeutet.

## Anwendungsszenarien
Dieser Datentyp wird primär in Szenarien verwendet, in denen eine Applikation über dynamische Änderungen im ISOBUS-Netzwerk informiert werden muss. Beispiele sind:
*   Überwachung des Erscheinens oder Verschwindens von Steuergeräten (ECUs) im Netzwerk.
*   Reaktion auf Adressänderungen von Netzwerkteilnehmern.
*   Implementierung von benutzerdefinierter Logik beim Verbindungsaufbau oder -abbau zu einer bestimmten CF.
*   Protokollierung von Netzwerkaktivitäten für Diagnosezwecke.

## Vergleich mit ähnlichen Bausteinen
Innerhalb der 4diac-Typbibliothek existieren verschiedene strukturierte Datentypen für Kommunikationsprotokolle. Im Gegensatz zu generischen Kommunikationsstrukturen (wie z.B. für TCP/IP) ist `ISONETEVENT_T` hochspezialisiert auf die Ereignismeldungen des ISOBUS-Protokollstapels, insbesondere den Teil der Netzwerkverwaltung (NM). Andere ISOBUS-bezogene Typen könnten sich eher auf den Austausch von Prozessdaten (PGN-Daten) konzentrieren.

## Fazit
Der Datentyp `ISONETEVENT_T` ist ein essentielles Hilfsmittel für die Entwicklung von ISOBUS-fähigen Applikationen in 4diac, die auf Netzwerkereignisse reagieren müssen. Er bietet eine standardisierte, informationsreiche Schnittstelle, um Callback-basierte Ereignisbenachrichtigungen aus dem ISOBUS-Netzwerkstack zu empfangen und zu verarbeiten. Seine Verwendung fördert eine entkoppelte und ereignisgesteuerte Architektur in der Steuerungssoftware.