# logiBUS_DO_S

* * * * * * * * * *
## Einleitung
Der Funktionsblock `logiBUS_DO_S` ist ein strukturierter Datentyp (Struct), der zur Konfiguration eines digitalen Ausgangs (DO) innerhalb des logiBUS-Systems dient. Er definiert die notwendigen Parameter, um einen physischen Ausgangspin eines logiBUS I/O-Moduls eindeutig zu adressieren und zu steuern. Dieser Datentyp wird typischerweise als Eingabe für Funktionsblöcke verwendet, die die eigentliche Ausgabefunktionalität bereitstellen.

## Schnittstellenstruktur
Als strukturierter Datentyp besitzt `logiBUS_DO_S` keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne eines Funktionsblocks. Stattdessen definiert er eine Datenstruktur, die als Ganzes an andere Blöcke übergeben wird.

### **Daten-Eingänge**
Die Struktur selbst enthält folgendes Datenfeld, das bei der Instanziierung des Typs befüllt wird:

| Name | Datentyp | Initialwert | Beschreibung |
| :--- | :--- | :--- | :--- |
| `Pin` | `USINT` (Unsigned Short Integer) | 255 | Definiert die Nummer des physischen Ausgangspins, der angesteuert werden soll. Der Wert 255 stellt einen ungültigen/undefinierten Zustand dar und dient als Standardinitialisierung. |

### **Ereignis-Eingänge**
*Nicht vorhanden.* Dieser Typ ist eine reine Datenstruktur.

### **Ereignis-Ausgänge**
*Nicht vorhanden.* Dieser Typ ist eine reine Datenstruktur.

### **Daten-Ausgänge**
*Nicht vorhanden.* Dieser Typ ist eine reine Datenstruktur.

### **Adapter**
*Nicht vorhanden.* Dieser Typ ist eine reine Datenstruktur.

## Funktionsweise
Der `logiBUS_DO_S`-Struct fungiert als Konfigurations-Container. Seine Hauptaufgabe ist es, die Information über die gewünschte Pin-Nummer (`Pin`) gebündelt und typisiert zu transportieren. Ein übergeordneter Funktionsblock (z.B. ein `logiBUS_DO`-Block) empfängt eine Instanz dieses Structs, liest den `Pin`-Wert aus und verwendet diese Information, um den entsprechenden physischen Ausgang des logiBUS-Hardwaremoduls zu schalten.

Der Initialwert von 255 für `Pin` signalisiert, dass der Pin noch nicht konfiguriert ist. Gültige Pin-Nummern liegen im Bereich, der vom jeweiligen logiBUS-I/O-Modul unterstützt wird (z.B. 0-7 für ein 8-Kanal-Modul).

## Technische Besonderheiten
*   **Typisierung:** Die Verwendung eines strukturierten Datentyps anstelle eines einfachen `USINT` erhöht die Typsicherheit und Lesbarkeit der Anwendung. Es ist klar, dass der Wert einen logiBUS-Ausgangspin repräsentiert.
*   **Initialwert:** Der Initialwert 255 dient als "Safe State"-Indikator. Bevor die Struktur korrekt konfiguriert wird, zeigt dieser Wert einen inaktiven oder fehlerhaften Zustand an.
*   **Paketzuordnung:** Der Struct ist Teil des Pakets `logiBUS::io::DQ`, was seine Zugehörigkeit zur digitalen Ein-/Ausgabe (Digital I/O) des logiBUS-Frameworks kennzeichnet.

## Zustandsübersicht
Da es sich um einen passiven Datentyp handelt, besitzt `logiBUS_DO_S` keinen internen Zustandsautomaten. Der "Zustand" ist ausschließlich durch den gespeicherten Wert der `Pin`-Variable gegeben.

## Anwendungsszenarien
1.  **Konfiguration von Ausgängen:** Primär dient der Struct zur Parametrierung von Funktionsblöcken, die Lampen, Ventile, Relais oder andere binäre Aktoren über logiBUS-Module ansteuern.
2.  **Strukturierte Parameterübergabe:** In komplexeren Applikationen können mehrere `logiBUS_DO_S`-Instanzen in Arrays oder weiteren Strukturen organisiert werden, um die Konfiguration aller Ausgänge einer Station zentral zu verwalten.
3.  **Initialisierung:** Der Standardinitialwert ermöglicht es, Variablen dieses Typs zu deklarieren, ohne sie sofort befüllen zu müssen. Die eigentliche Konfiguration (Zuweisung einer gültigen Pin-Nummer) kann zu einem späteren Zeitpunkt im Programmablauf erfolgen.

## Vergleich mit ähnlichen Bausteinen
*   **Einfacher `USINT`:** Der direkte Einsatz eines `USINT`-Werts für die Pin-Nummer ist möglich, bietet aber weniger semantische Klarheit und Typsicherheit. Der `logiBUS_DO_S` macht die Absicht des Datenelements explizit.
*   **`logiBUS_DI_S`:** Dies ist das strukturelle Gegenstück für digitale Eingänge (DI). Es hat eine identische Struktur (ein `USINT`-Feld `Pin`), gehört aber konzeptionell zur Eingabeseite. Die Trennung in DO- und DI-Structs verbessert die Lesbarkeit und Wartbarkeit des Codes.

## Fazit
Der `logiBUS_DO_S`-Struct ist ein einfaches, aber wesentliches Hilfselement im logiBUS-Ökosystem der 4diac IDE. Er standardisiert und formalisiert die Adressierung von digitalen Ausgangspins, fördert die typsichere Programmierung und dient durch seinen definierten Initialwert als Grundlage für eine robuste Initialisierungslogik. Seine Verwendung ist empfohlen, wenn Funktionsblöcke der logiBUS-Bibliothek für digitale Ausgaben konfiguriert werden sollen.