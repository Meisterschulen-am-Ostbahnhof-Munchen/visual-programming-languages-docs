# IDs

```{index} single: IDs
```

* * * * * * * * * *

## Einleitung
Das globale Konstantenpaket `IDs` stellt eine Sammlung von vordefinierten, unveränderlichen Werten (Konstanten) bereit, die innerhalb von Funktionsbausteinen der IEC 61499-Laufzeitumgebung verwendet werden können. Diese Konstanten dienen primär der Verbesserung der Lesbarkeit und Wartbarkeit des Quellcodes, indem sie magische Zahlen durch aussagekräftige Bezeichner ersetzen. Das Paket ist im Namensraum `isobus::UT::Q::const` definiert.

## Schnittstellenstruktur
Da es sich um ein Paket mit globalen Konstanten handelt, besitzt es keine ereignis- oder datenflussbasierten Schnittstellen im herkömmlichen Sinne eines Funktionsbausteins. Die Konstanten sind statisch und können direkt über ihren Namen referenziert werden.

### **Ereignis-Eingänge**
Nicht vorhanden.

### **Ereignis-Ausgänge**
Nicht vorhanden.

### **Daten-Eingänge**
Nicht vorhanden.

### **Daten-Ausgänge**
Nicht vorhanden.

### **Adapter**
Nicht vorhanden.

## Funktionsweise
Die Konstanten werden beim Kompilieren der Anwendung durch ihre fest definierten Werte ersetzt. Sie verhalten sich wie Literale, besitzen jedoch einen semantischen Namen. Die im Paket enthaltenen Konstanten sind:

*   `ID_NULL`: Repräsentiert einen ungültigen oder nicht initialisierten Bezeichner (ID) vom Typ `UINT` mit dem Hexadezimalwert `16#FFFF` (dezimal 65535).
*   `ID_OFF`: Repräsentiert einen speziellen Bezeichnerwert, der "Aus" oder "Inaktiv" signalisiert, vom Typ `UINT` mit dem Wert `16#0` (dezimal 0).
*   `GLOBAL`: Ein Bezeichner vom Typ `USINT` mit dem Wert `16#FF` (dezimal 255), der typischerweise für globale oder broadcast-Adressierung verwendet wird.
*   `OFF`: Ein einfacher Statuswert vom Typ `USINT` für den Zustand "Aus" mit dem Wert `16#0` (dezimal 0).

## Technische Besonderheiten
*   **Typisierung:** Die Konstanten sind streng typisiert (`UINT`, `USINT`). Dies gewährleistet Typsicherheit bei ihrer Verwendung in Zuweisungen und Vergleichen.
*   **Initialwert:** Jede Konstante wird bei ihrer Deklaration mit einem festen, unveränderlichen Initialwert versehen.
*   **Namensraum:** Die Konstanten sind im Paket `isobus::UT::Q::const` gekapselt, was Namenskonflikte mit anderen Bibliotheken verhindert.

## Zustandsübersicht
Da es sich um statische, konstante Werte handelt, existiert kein Zustandsautomat.

## Anwendungsszenarien
*   **Initialisierung:** Zuweisung eines definierten Startwerts (z.B. `ID_NULL`) an Variablen, die später eine gültige ID erhalten.
*   **Vergleich:** Prüfung, ob eine empfangene oder gelesene ID einem speziellen Wert entspricht (z.B., `IF receivedID = IDs.ID_OFF THEN ...`).
*   **Parameterisierung:** Verwendung der Konstanten als aussagekräftige Parameter in Funktionsbausteinen, anstelle von direkten numerischen Werten.
*   **Kommando- und Statuswerte:** Verwendung von `OFF` und `GLOBAL` zur Steuerung von Prozessen oder zur Adressierung von Geräten in einem Netzwerk.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsbausteinen (FBs) mit Algorithmen und Ereignissteuerung stellt dieses Paket lediglich Datenbereitstellung dar. Es ist vergleichbar mit:
*   **ENUM-Datentypen:** Während ENUMs eine Liste von benannten Ganzzahlwerten eines Typs definieren, definiert dieses Paket einzelne, lose Konstanten verschiedener Typen.
*   **#define-Präprozessor-Direktiven (in C):** Beide ersetzen einen Namen durch einen Wert. Die Konstanten in `IDs` sind jedoch typsicher und in der 4diac-IDE verwaltbar.

## Fazit
Das globale Konstantenpaket `IDs` ist ein einfaches, aber nützliches Hilfswerkzeug für die strukturierte Programmierung in 4diac. Es erhöht die Code-Qualität, reduziert Fehler durch Tippfehler in numerischen Werten und macht die Absicht des Programmierers explizit. Seine Verwendung wird insbesondere in größeren Projekten oder bei der Arbeit mit Protokollen wie ISOBUS empfohlen, wo spezielle Bezeichnerwerte häufig vorkommen.