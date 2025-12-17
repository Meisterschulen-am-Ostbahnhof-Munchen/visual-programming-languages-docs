# SoftKeyActivationCode_S

* * * * * * * * * *
## Einleitung
Der Datentyp `SoftKeyActivationCode_S` ist eine strukturierte Datenstruktur (Struct), die zur Konfiguration der Aktivierung eines Softkeys in einem ISOBUS-konformen System dient. Er definiert den spezifischen Aktivierungscode und ein Steuerflag für die Wiederholungsfrequenz der Tasteneingabe.

## Schnittstellenstruktur
Dies ist ein Datentyp und besitzt daher keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne eines Funktionsbausteins. Die Struktur besteht aus den folgenden Datenfeldern:

### **Daten-Eingänge**
*(Nicht anwendbar – dies ist ein Datentyp)*

### **Daten-Ausgänge**
*(Nicht anwendbar – dies ist ein Datentyp)*

### **Datenfelder (Strukturkomponenten)**
| Name     | Datentyp | Initialwert | Kommentar |
| :------- | :------- | :---------- | :-------- |
| `code`   | `USINT`  | 255         | Definiert den numerischen Code, der den spezifischen Softkey identifiziert. |
| `bCyclic`| `BOOL`   | TRUE        | Steuert das zyklische Senden des Tastencodes. Bei `FALSE` wird die Taste nicht alle 200ms wiederholt gesendet. |

## Funktionsweise
Die Struktur `SoftKeyActivationCode_S` dient als Container für Konfigurationsdaten. Der Wert im Feld `code` korrespondiert mit einer spezifischen Taste auf einem virtuellen oder physischen Terminal. Das Feld `bCyclic` ermöglicht es, das Verhalten bei gedrückt gehaltener Taste zu steuern. Ist es auf `TRUE` gesetzt (Standard), wird der Tastendruck in einem definierten Intervall (z.B. alle 200ms) wiederholt gesendet, solange die Taste gedrückt bleibt. Bei `FALSE` wird nur ein einzelnes Ereignis beim initialen Drücken der Taste ausgelöst.

## Technische Besonderheiten
*   **Initialwerte:** Beide Felder besitzen vordefinierte Initialwerte. Der Standardwert `255` für `code` kann als "ungültiger" oder "nicht konfigurierter" Code interpretiert werden.
*   **ISOBUS-Kontext:** Der Datentyp ist Teil des Pakets `isobus::UT::io::Softkey`, was auf seine Verwendung in ISOBUS Virtual Terminal (VT) oder ähnlichen IO-Kontexten hindeutet.
*   **Zyklussteuerung:** Die präzise Steuerung der Wiederholungsrate über `bCyclic` ist entscheidend für eine benutzerfreundliche und zuverlässige Tastatureingabe, insbesondere bei langen Datenfeldern oder Listensteuerungen.

## Zustandsübersicht
*(Nicht anwendbar – dies ist ein passiver Datentyp ohne Zustandsmaschine.)*

## Anwendungsszenarien
Diese Datenstruktur wird typischerweise als Eingabe- oder Konfigurationsparameter für Funktionsbausteine verwendet, die:
1.  Die virtuelle Tastatureingabe eines ISOBUS-Terminals emulieren oder steuern.
2.  Softkey-Ereignisse in einer Anwendungslogik verarbeiten (z.B. Menünavigation, Werteingabe).
3.  Die Tastenbelegung oder das Tastenverhalten eines Geräts dynamisch konfigurieren.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einem Funktionsbaustein (FB) ist `SoftKeyActivationCode_S` ein reiner **Datentyp** (Struct). Er enthält keine Algorithmen oder ereignisgesteuerte Logik.
*   **Ähnlichkeit zu `E_SR` oder `E_RS`:** Diese sind Funktionsbausteine mit Speicherfunktion und besitzen eine interne Zustandslogik. `SoftKeyActivationCode_S` ist hingegen ein reiner Datenträger.
*   **Vergleich mit einfachen Datentypen:** Im Gegensatz zu atomaren Typen wie `INT` oder `BOOL` bündelt dieser Struct zwei logisch zusammengehörige Informationen (`code` und Verhalten `bCyclic`) zu einer einzigen, wiederverwendbaren Einheit.

## Fazit
Der Datentyp `SoftKeyActivationCode_S` ist eine essentielle Hilfsstruktur für die Steuerung von Softkey-Eingaben in ISOBUS-Umgebungen. Durch die Kapselung des Tastencodes und des Wiederholungsverhaltens in einem einzigen Struct wird die Konfiguration vereinfacht und die Wiederverwendbarkeit des Codes erhöht. Seine klare Struktur und die sinnvollen Standardwerte machen ihn zu einem robusten Baustein für die Entwicklung von Terminal-IO-Logik.