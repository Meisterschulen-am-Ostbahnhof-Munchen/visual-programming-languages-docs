# ST16B

* * * * * * * * * *
## Einleitung
Der Datentyp `ST16B` ist eine strukturierte Datenkomponente, die im 4diac-Framework definiert ist. Im Gegensatz zu einem Funktionsblock (FB) hat `ST16B` keine eigene Logik oder ausführbaren Funktionen, sondern dient als fester Container für 16 einzelne Byte-Werte. Sein Hauptzweck ist die Bereitstellung einer klar definierten Struktur für die Handhabung von Rohdatenpaketen fester Größe, was besonders in Kommunikationsprotokollen oder bei der Interaktion mit hardwarenahen Schnittstellen von Bedeutung ist.

## Schnittstellenstruktur
Da `ST16B` ein Datentyp und kein Funktionsblock ist, besitzt er keine Ereignis- oder Daten-Schnittstellen im herkömmlichen Sinne. Seine "Struktur" bezieht sich auf die Definition seiner internen Komponenten, d.h. der einzelnen Bytes, aus denen er besteht.

### **Ereignis-Eingänge**
Nicht zutreffend, da `ST16B` ein Datentyp und kein Funktionsblock ist und daher keine Ereignisse verarbeitet.

### **Ereignis-Ausgänge**
Nicht zutreffend, da `ST16B` ein Datentyp und kein Funktionsblock ist und daher keine Ereignisse generiert.

### **Daten-Eingänge**
Nicht zutreffend, da `ST16B` ein Datentyp und kein Funktionsblock ist und daher keine direkten Daten-Eingänge im Kontext von FB-Verbindungen besitzt.

### **Daten-Ausgänge**
Nicht zutreffend, da `ST16B` ein Datentyp und kein Funktionsblock ist und daher keine direkten Daten-Ausgänge im Kontext von FB-Verbindungen besitzt.

### **Adapter**
Nicht zutreffend, da `ST16B` ein Datentyp und kein Funktionsblock ist und daher keine Adapter-Schnittstellen implementiert.

### Datenstruktur der Komponente
`ST16B` besteht aus 16 einzelnen Variablen vom Typ `BYTE`, die sequenziell angeordnet sind:

| Name | Typ    | Beschreibung |
| :--- | :----- | :----------- |
| B_00 | BYTE   | BYTE 00      |
| B_01 | BYTE   | BYTE 01      |
| B_02 | BYTE   | BYTE 02      |
| B_03 | BYTE   | BYTE 03      |
| B_04 | BYTE   | BYTE 04      |
| B_05 | BYTE   | BYTE 05      |
| B_06 | BYTE   | BYTE 06      |
| B_07 | BYTE   | BYTE 07      |
| B_08 | BYTE   | BYTE 08      |
| B_09 | BYTE   | BYTE 09      |
| B_10 | BYTE   | BYTE 10      |
| B_11 | BYTE   | BYTE 11      |
| B_12 | BYTE   | BYTE 12      |
| B_13 | BYTE   | BYTE 13      |
| B_14 | BYTE   | BYTE 14      |
| B_15 | BYTE   | BYTE 15      |

## Funktionsweise
`ST16B` selbst besitzt keine aktive Funktionsweise. Es ist ein passiver Datencontainer. Seine Funktion besteht darin, eine definierte Speichervorlage für 16 Byte zu bieten. Jedes Byte (`B_00` bis `B_15`) kann individuell gelesen und beschrieben werden. Dieser strukturierte Zugriff auf einzelne Bytes ermöglicht eine granulare Datenmanipulation und die einfache Zuordnung zu Kommunikationsfeldern oder Speicherbereichen.

## Technische Besonderheiten
*   **Feste Größe:** Der Datentyp `ST16B` hat eine feste Größe von exakt 16 Bytes. Dies ist vorteilhaft für die Vorhersagbarkeit des Speicherverbrauchs und die Kompatibilität mit Protokollen, die feste Längen erwarten.
*   **Direkter Byte-Zugriff:** Jedes der 16 Bytes ist über seinen spezifischen Namen (z.B. `MyVariable.B_00`) direkt zugänglich.
*   **Rohdatenbehälter:** Ideal für die Speicherung und den Transport von Rohdaten, deren Inhalt erst später interpretiert werden soll.
*   **Architekturunabhängigkeit:** Als Sammlung von BYTEn ist die grundlegende Struktur relativ plattformunabhängig, auch wenn die Interpretation der Bytes in verschiedenen Systemen variieren kann (z.B. Endianness bei größeren Werten, die über mehrere Bytes verteilt sind).

## Zustandsübersicht
Nicht zutreffend, da `ST16B` ein Datentyp ist und keine internen Zustände im Sinne eines Funktionsblocks (z.B. Initialisierung, Ausführung, Fehler) besitzt. Die "Zustände" von `ST16B` sind lediglich die aktuellen Werte, die in seinen 16 Byte-Komponenten gespeichert sind.

## Anwendungsszenarien
*   **Kommunikationsprotokolle:** Ideal zum Verpacken oder Entpacken von Nachrichten für Protokolle wie Modbus, CAN-Bus, oder proprietäre seriellen Protokollen, bei denen Datenpakete eine feste Größe von 16 Bytes haben.
*   **Hardware-Schnittstellen:** Abbildung von Registern oder Datenblöcken in hardwarenahen Schnittstellen, die in festen Byte-Mustern arbeiten.
*   **Puffer für binäre Daten:** Verwendung als Puffer für binäre Daten, die von externen Quellen gelesen oder an diese gesendet werden.
*   **Zwischenspeicherung von Hashes oder IDs:** Für Anwendungen, die 128-Bit-Hashes (z.B. MD5) oder lange IDs speichern müssen, die genau 16 Bytes umfassen.

## Vergleich mit ähnlichen Bausteinen
*   **`ARRAY[0..15] OF BYTE`:** `ST16B` ähnelt einem Array von 16 Bytes. Der Hauptunterschied liegt im Zugriff: Bei `ST16B` erfolgt der Zugriff über benannte Komponenten (`B_00`, `B_01`, etc.), während ein Array den Zugriff über Indizes (`MyArray[0]`, `MyArray[1]`) ermöglicht. Die benannten Komponenten können die Lesbarkeit verbessern, wenn jedes Byte eine spezifische semantische Bedeutung innerhalb der 16 Bytes hat.
*   **Andere strukturierte Datentypen:** Im Vergleich zu benutzerdefinierten Strukturen, die verschiedene Datentypen (INT, REAL, BOOL) mischen, ist `ST16B` auf reine Byte-Sammlungen spezialisiert. Es bietet eine flache, gleichartige Struktur.

## Fazit
Der Datentyp `ST16B` ist eine einfache, aber effektive Struktur zum Umgang mit Datenblöcken fester Größe von 16 Bytes. Er bietet eine klare und lesbare Möglichkeit, auf individuelle Bytes innerhalb eines solchen Blocks zuzugreifen. Obwohl er kein Funktionsblock ist und keine eigene Logik implementiert, ist er ein wertvolles Werkzeug in 4diac für Anwendungen, die eine genaue Kontrolle über die Byte-Ebene erfordern, insbesondere in der Kommunikation und Hardware-Interaktion.