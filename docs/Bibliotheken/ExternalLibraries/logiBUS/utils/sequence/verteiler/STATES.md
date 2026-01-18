# STATES

```{index} single: STATES
```

* * * * * * * * * *
## Einleitung
Die globale Konstanten-Deklaration `STATES` definiert eine Sammlung von vordefinierten Zustandsbezeichnungen als Zeichenketten (STRING). Diese Konstanten werden typischerweise verwendet, um Betriebszustände in einer Steuerungssequenz zu benennen, insbesondere für Prozesse mit wechselnder Richtung (Linkslauf/Rechtslauf) und integrierten Pausen. Sie dient als zentrale und konsistente Quelle für diese Zustandsnamen innerhalb eines Projekts.

## Schnittstellenstruktur
Bei globalen Konstanten handelt es sich nicht um einen Funktionsbaustein mit Ereignis- oder Datenschnittstellen. Stattdessen werden Konstantenwerte deklariert, die projektweit zur Verfügung stehen.

### **Daten-Deklarationen**
Die folgenden Konstanten werden definiert:
*   `Rechtslauf`: Zeichenkette mit dem Wert `'Rechtslauf'`
*   `Linkslauf`: Zeichenkette mit dem Wert `'Linkslauf'`
*   `Linkslauf_Pause`: Zeichenkette mit dem Wert `'Linkslauf_Pause'`
*   `Rechtslauf_Pause`: Zeichenkette mit dem Wert `'Rechtslauf_Pause'`

## Funktionsweise
Die Konstanten selbst besitzen keine aktive Funktionalität. Sie stellen lediglich benannte Werte bereit. Ihr Hauptzweck ist die Vermeidung von "Magic Numbers" oder hartkodierten Zeichenketten im Programmcode. Durch die Verwendung dieser Konstanten wird der Code lesbarer, wartbarer und weniger fehleranfällig, da Änderungen an den Zustandsnamen nur an einer zentralen Stelle vorgenommen werden müssen.

## Technische Besonderheiten
*   **Typ:** Alle deklarierten Konstanten sind vom Datentyp `STRING`.
*   **Gültigkeitsbereich:** Als globale Konstanten sind sie innerhalb des gesamten Namensraums `logiBUS::utils::sequence::verteiler::LinksRechts` und in davon abhängigen Komponenten verfügbar.
*   **Initialisierung:** Die Werte werden direkt bei der Deklaration mit dem `InitialValue`-Attribut festgelegt.

## Zustandsübersicht
Nicht zutreffend, da es sich um eine statische Datendeklaration und nicht um einen zustandsbehafteten Baustein handelt.

## Anwendungsszenarien
Typische Anwendungen für diese Konstanten sind:
*   **Zustandsautomaten (State Machines):** Die Konstanten können als eindeutige Bezeichner für die verschiedenen Zustände eines Automaten dienen, der einen Prozess mit Richtungswechsel und Pausen steuert (z. B. einen Verteilertisch).
*   **Dokumentation und Logging:** Sie können verwendet werden, um den aktuellen Betriebszustand in Meldungen, Logdateien oder auf Bedienpanels anzuzeigen.
*   **Vergleiche und Schaltlogik:** In der Programmlogik können Variablen oder Ausgänge mit diesen Konstanten verglichen werden, um Entscheidungen basierend auf dem aktuellen Zustand zu treffen.

## Vergleich mit ähnlichen Bausteinen
*   **Globale Variablen (VAR_GLOBAL):** Im Gegensatz zu globalen Variablen können die Werte von Konstanten (`CONSTANT`) zur Laufzeit nicht verändert werden.
*   **Enumerations (ENUM):** Während ENUM-Datentypen in einigen Programmiersprachen ähnliche Zwecke erfüllen, bietet die IEC 61499-Standardbibliothek keinen eingebauten ENUM-Typ. Die Verwendung von STRING-Konstanten ist eine gängige Methode, um semantisch benannte Werte in dieser Umgebung zu definieren.
*   **Funktionsbaustein-internen Konstanten:** Konstanten können auch innerhalb von Funktionsbausteinen definiert werden. Globale Konstanten sind jedoch über Bausteingrenzen hinweg sichtbar und fördern so die Wiederverwendbarkeit und Konsistenz über ein gesamtes Projekt hinweg.

## Fazit
Die globale Konstanten-Deklaration `STATES` ist ein einfaches aber nützliches Konstrukt zur Strukturierung von Steuerungssoftware. Sie erhöht die Codequalität, indem sie zentrale und unveränderliche Zustandsbezeichnungen bereitstellt, die speziell für Sequenzen mit Links-/Rechtslauf und Pausenzuständen zugeschnitten sind. Ihre Verwendung macht Programme verständlicher und erleichtert zukünftige Anpassungen.
