# CF_NAME_T

* * * * * * * * * *
## Einleitung
Der Datentyp `CF_NAME_T` ist ein strukturierter Datentyp, der in der 4diac-IDE zur Modellierung von ISO CF (Communication Function) oder Anwenderinformationsdaten-Arrays verwendet wird. Er dient als Typedef für ein Byte-Array fester Länge und wird typischerweise im Kontext von ISOBUS PGN (Parameter Group Number) Kommunikation eingesetzt.

## Schnittstellenstruktur
`CF_NAME_T` ist ein strukturierter Datentyp (STRUCT) und besitzt keine Ereignis- oder Adapterschnittstellen. Seine Struktur besteht aus einem einzelnen Datenfeld.

### **Daten-Eingänge**
Dieser Datentyp selbst hat keine Eingänge. Er definiert die Struktur für Daten.

### **Daten-Ausgänge**
Dieser Datentyp selbst hat keine Ausgänge. Er definiert die Struktur für Daten.

### **Strukturierte Elemente**
*   **`data`** (BYTE[0..7]): Ein Array aus genau 8 Bytes (`BYTE`). Jedes Element im Array wird bei der Initialisierung standardmäßig auf den Hexadezimalwert `16#FF` (dezimal 255) gesetzt. Dies repräsentiert einen typischen "ungültigen" oder "leeren" Anfangszustand in Kommunikationsprotokollen.

## Funktionsweise
Der Datentyp `CF_NAME_T` kapselt ein Byte-Array mit einer festen Länge von 8 Bytes. Seine Hauptfunktion besteht darin, eine typsichere und wiederverwendbare Definition für Datenpakete bereitzustellen, die in ISOBUS-basierten Steuerungssystemen ausgetauscht werden. Die vordefinierte Initialisierung aller Bytes auf `0xFF` stellt sicher, dass Instanzen dieses Typs in einem bekannten, neutralen Zustand beginnen.

## Technische Besonderheiten
*   **Feste Array-Größe:** Das Array ist auf die Indizes 0 bis 7 begrenzt, was einer festen Länge von 8 Bytes entspricht. Dies ist eine gängige Größe für viele Nachrichtenblöcke in Feldbussystemen.
*   **Vordefinierte Initialisierung:** Alle Array-Elemente werden bei der Deklaration einer Variable dieses Typs automatisch mit dem Wert `16#FF` initialisiert, sofern nicht anders angegeben.
*   **ISOBUS-Kontext:** Der Typ ist Teil des Pakets `isobus::pgn`, was auf seine spezifische Verwendung in landwirtschaftlichen und mobilen Maschinensteuerungen (ISOBUS, ISO 11783) hindeutet.

## Anwendungsszenarien
Dieser Datentyp wird primär verwendet, um die Nutzdaten von ISOBUS PGN-Nachrichten innerhalb von Funktionsbausteinen (FBs) zu repräsentieren. Typische Anwendungen sind:
*   Deklaration von Eingangs- oder Ausgangsvariablen in FBs, die ISOBUS-Nachrichten senden oder empfangen.
*   Strukturierung von Daten für die Kommunikation zwischen verschiedenen Steuergeräten (ECUs) in einer mobilen Maschine.
*   Verwendung als Teil eines größeren, strukturierten Datentyps, der mehrere Parameter einer komplexen Nachricht kombiniert.

## Vergleich mit ähnlichen Bausteinen
`CF_NAME_T` ist ein Datentyp und kein Funktionsbaustein. Er kann mit anderen strukturierten Datentypen (STRUCT) in 4diac verglichen werden, die Arrays definieren. Sein Unterscheidungsmerkmal ist die feste 8-Byte-Länge und die ISOBUS-spezifische Semantik. Ein generisches `ARRAY [0..7] OF BYTE` wäre funktional ähnlich, bietet aber nicht die typsichere Wiederverwendbarkeit und den kontextuellen Bezug.

## Fazit
Der Datentyp `CF_NAME_T` ist ein spezialisiertes, wiederverwendbares Konstrukt für die 4diac-IDE, das die Handhabung von 8-Byte-Datenblöcken in ISOBUS-Anwendungen standardisiert und vereinfacht. Durch seine feste Größe und vordefinierte Initialisierung erhöht er die Zuverlässigkeit und Lesbarkeit von Applikationscode, der auf dem ISO 11783-Standard basiert.