# ButtonActivationCode_S

* * * * * * * * * *
## Einleitung
Der Datentyp `ButtonActivationCode_S` ist eine strukturierte Datenstruktur (Struct), die zur Konfiguration der Aktivierung eines Tasters (Buttons) in einem Steuerungssystem verwendet wird. Er definiert einen Aktivierungscode und ein Steuerungsflag für die Wiederholungslogik. Dieser Datentyp ist Teil des Pakets `isobus::UT::io::Button`.

## Schnittstellenstruktur
Da es sich um einen Datentyp und nicht um einen Funktionsblock handelt, gibt es keine Ereignis- oder Adapterschnittstellen. Die Struktur besteht ausschließlich aus Datenfeldern.

### **Daten-Eingänge**
*(Nicht anwendbar - Dies ist ein Datentyp, kein Funktionsblock)*

### **Daten-Ausgänge**
*(Nicht anwendbar - Dies ist ein Datentyp, kein Funktionsblock)*

### **Strukturierte Datenfelder**
Die folgenden Felder bilden die interne Struktur des Datentyps `ButtonActivationCode_S`:

| Name     | Datentyp | Initialwert | Kommentar |
| :------- | :------- | :---------- | :-------- |
| `code`   | `USINT`  | 255         | Definiert den spezifischen Aktivierungscode für den Taster. |
| `bCyclic`| `BOOL`   | TRUE        | Steuert das zyklische Verhalten. Wenn auf `FALSE` gesetzt, wird die Aktivierung nicht alle 200 ms wiederholt. |

## Funktionsweise
Die Struktur `ButtonActivationCode_S` dient als Container für Konfigurationsdaten.
*   Das Feld `code` identifiziert den Taster eindeutig innerhalb des Systems. Der Standardwert 255 kann als inaktiver oder undefinierter Zustand interpretiert werden.
*   Das Feld `bCyclic` bestimmt das Zeitverhalten bei einer dauerhaften Betätigung des Tasters. Bei `TRUE` (Standard) wird das zugehörige Ereignis in einem festen Intervall (z.B. alle 200 ms) wiederholt ausgelöst. Bei `FALSE` wird das Ereignis nur einmalig beim Drücken (und ggf. beim Loslassen) ausgelöst, auch wenn der Taster gedrückt gehalten wird.

## Technische Besonderheiten
*   **Initialwerte:** Beide Felder der Struktur haben vordefinierte Initialwerte, was eine sichere Initialisierung gewährleistet.
*   **Kommentar:** Das Feld `bCyclic` enthält einen hilfreichen Kommentar, der die konkrete Auswirkung (`do not repeat every 200ms`) direkt in der Deklaration erklärt.
*   **Typ-Hash:** Der Datentyp enthält ein Attribut (`eclipse4diac::core::TypeHash`), das für die Typprüfung und Versionierung innerhalb der 4diac-Umgebung genutzt wird.

## Zustandsübersicht
*(Nicht anwendbar - Dies ist ein statischer Datentyp ohne Zustandsautomaten.)*

## Anwendungsszenarien
Dieser Struct wird typischerweise als Eingangs- oder Konfigurationsparameter für Funktionsblöcke verwendet, die Tastereingänge verarbeiten, z.B.:
*   In einer Bedienoberfläche (HMI) zur Konfiguration von Softkeys.
*   In Maschinensteuerungen zur Parametrierung von physischen Steuertastern.
*   Überall dort, wo zwischen einmaliger und wiederholter Aktion bei Tastendruck unterschieden werden muss.

## Vergleich mit ähnlichen Bausteinen
Als reiner Datentyp ist `ButtonActivationCode_S` mit anderen strukturierten Datentypen (STRUCTs) in 4diac vergleichbar, wie z.B. `DATE_AND_TIME`. Sein spezifischer Zweck ist die Bündelung der für die Tastersteuerung relevanten Parameter (`code` für Identifikation, `bCyclic` für Zeitverhalten) in einer einzigen, wiederverwendbaren Einheit.

## Fazit
Der Datentyp `ButtonActivationCode_S` ist eine einfache, aber wesentliche Struktur zur standardisierten Konfiguration von Tasterverhalten in 4diac-basierten Steuerungsapplikationen. Durch die Kapselung des Codes und des Wiederholungsflags fördert er die Wiederverwendbarkeit und Lesbarkeit von Code. Die integrierten Initialwerte und der klare Kommentar tragen zur Robustheit und einfachen Handhabung bei.