# CF_INFO_T

* * * * * * * * * *
## Einleitung
Der Datentyp `CF_INFO_T` (Control Function Information Type) ist eine strukturierte Datenkomponente, die innerhalb der ISO 11783 (ISOBUS)-Kommunikation verwendet wird. Er dient der standardisierten Abbildung und Verwaltung von Informationen über einen Teilnehmer (Control Function oder User) im ISOBUS-Netzwerk. Dieser Typedef fasst alle wesentlichen Merkmale und Zustände eines Netzwerkteilnehmers in einer einzigen Datenstruktur zusammen.

## Schnittstellenstruktur
`CF_INFO_T` ist ein strukturierter Datentyp (StructuredType) und verfügt über keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne eines Funktionsbausteins. Seine Struktur besteht ausschließlich aus Daten-Elementen (Variablen).

### **Daten-Eingänge**
Nicht vorhanden, da es sich um einen reinen Datentyp handelt.

### **Daten-Ausgänge**
Nicht vorhanden, da es sich um einen reinen Datentyp handelt.

### **Daten-Elemente (Struktur)**
Die interne Struktur des Typs `CF_INFO_T` besteht aus den folgenden Elementen:

| Name | Typ | Kommentar / Beschreibung | Initialwert |
| :--- | :--- | :--- | :--- |
| `s16Handle` | `INT` | Netzwerk-Member-Handle der Control Function (CF) / des Users. Dient als eindeutiger Identifikator innerhalb der Anwendung. | `UNVALID` |
| `u8SourceAddress` | `BYTE` | Quelladresse (Source Address, SA) der Control Function (CF) / des Users im ISOBUS-Netzwerk. | `NULL_A` |
| `u8CanIdx` | `BYTE` | CAN-Bus Node / Index der Control Function (CF) / des Users. Identifiziert den physischen Bus-Knoten. | – |
| `au8Name` | `isobus::pgn::CF_NAME_T` | Der ISOBUS-NAME der Control Function. Dies ist eine 64-bit eindeutige Kennung gemäß ISO 11783-5. | – |
| `eIsoUserFunct` | `SINT` | Intern verwendeter CF-Funktionstyp (z.B. Arbeitsgerät, Terminal, Task-Controller). | `undefined` |
| `bExternalCf` | `BOOL` | Kennzeichnet, ob es sich um eine externe CF im CAN-Netzwerk handelt (`TRUE`) oder nicht. | – |
| `bIsAnnounced` | `BOOL` | `TRUE`, wenn die CF aktiv und vollständig im Netzwerk angekündigt (announced) ist. | – |
| `bIsActive` | `BOOL` | NIU-spezifisch (Network Interface Unit): `TRUE`, wenn sich die CF nicht in einem Fehlerzustand befindet oder abgemeldet (logged off) ist. | – |

## Funktionsweise
Der Datentyp `CF_INFO_T` ist eine passive Datenhaltungsstruktur. Er wird verwendet, um den Zustand und die Identität eines ISOBUS-Netzwerkteilnehmers zu speichern und zwischen verschiedenen Komponenten einer Steuerungsanwendung auszutauschen. Die enthaltenen Informationen werden typischerweise durch andere Funktionsbausteine gelesen, geschrieben und interpretiert, die für die Netzwerkverwaltung (z.B. Adressvergabe, NAME-Verwaltung) oder die Applikationslogik zuständig sind.

## Technische Besonderheiten
*   **Typedef für ISOBUS:** Speziell für die Anwendung in ISO 11783-Umgebungen (Landtechnik) konzipiert.
*   **Zustandsflags:** Enthält mehrere boolesche Flags (`bIsAnnounced`, `bIsActive`), die den Lebenszyklus und Betriebszustand einer CF abbilden.
*   **Initialwerte:** Kritische Identifikatoren wie `s16Handle` und `u8SourceAddress` werden mit definierten Konstanten (`UNVALID`, `NULL_A`) initialisiert, um einen ungültigen Ausgangszustand sicherzustellen.
*   **Integration:** Verwendet den benutzerdefinierten Typ `isobus::pgn::CF_NAME_T` für die Abbildung des 64-bit ISOBUS-NAMEN.

## Zustandsübersicht
Da es sich um einen Datentyp und keinen aktiven Baustein handelt, existiert keine Zustandsmaschine. Der "Zustand" wird durch die Kombination der enthaltenen Datenfelder beschrieben, insbesondere durch die Flags:
*   **Ungültig/Inaktiv:** `s16Handle == UNVALID`, `bIsAnnounced == FALSE`
*   **Gültig & Aktiv:** `s16Handle != UNVALID`, `bIsAnnounced == TRUE`, `bIsActive == TRUE`
*   **Gültig & Fehlerhaft/Inaktiv:** `s16Handle != UNVALID`, `bIsActive == FALSE`

## Anwendungsszenarien
*   **Teilnehmerverwaltung:** In einem ISOBUS-Manager-Baustein, der eine Liste aller bekannten Netzwerkteilnehmer (`CF_INFO_T[]`) verwaltet.
*   **Diagnose und Anzeige:** Weitergabe von Teilnehmerinformationen an ein Diagnose- oder Display-System, um den Netzwerkstatus anzuzeigen.
*   **Kommando-Weiterleitung:** Als Parameter für Kommunikationsbausteine, um Nachrichten gezielt an eine bestimmte CF (identifiziert durch `u8SourceAddress` und `au8Name`) zu adressieren.
*   **Filterung:** Logikbausteine können anhand der Felder `eIsoUserFunct` oder `bExternalCf` entscheiden, ob Nachrichten einer bestimmten CF verarbeitet werden sollen.

## Vergleich mit ähnlichen Bausteinen
`CF_INFO_T` ist kein Funktionsbaustein und kann daher nicht direkt mit Blöcken wie `E_SR` oder `E_CYCLE` verglichen werden. Innerhalb der ISOBUS-Kommunikation ist er vergleichbar mit anderen strukturierten Datentypen, die Netzwerk- oder Geräteinformationen bündeln (z.B. `PGN_INFO_T` für Parameter Group Numbers). Seine Besonderheit liegt in der spezifischen Zusammenstellung von Daten, die für die Identifikation und das Zustandsmanagement einer Control Function erforderlich sind.

## Fazit
Der Datentyp `CF_INFO_T` ist ein grundlegender und wesentlicher Bestandteil für die Implementierung von ISOBUS-fähigen Steuerungsapplikationen in 4diac. Er bietet eine standardisierte, typsichere Methode, um alle relevanten Informationen eines Netzwerkteilnehmers zu gruppieren und zu transportieren. Durch seine Verwendung wird die Wiederverwendbarkeit von Code erhöht und die Konsistenz in der Netzwerkkommunikationslogik sichergestellt.