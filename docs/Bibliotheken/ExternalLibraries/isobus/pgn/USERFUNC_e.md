# USERFUNC_e

```{index} single: USERFUNC_e
```

* * * * * * * * * *
## Einleitung
Die globale Konstante `USERFUNC_e` definiert eine Aufzählung (Enumeration) von numerischen Werten, die spezifische Gerätefunktionen oder Rollen innerhalb eines ISOBUS-Netzwerks repräsentieren. Sie dient der standardisierten und lesbaren Identifikation verschiedener ISOBUS-Gerätetypen und -Funktionen in Steuerungsanwendungen.

## Schnittstellenstruktur
Bei `USERFUNC_e` handelt es sich um eine Sammlung globaler Konstanten und nicht um einen Funktionsblock. Daher existieren keine Ereignis- oder Datenschnittstellen im herkömmlichen Sinne. Die Struktur besteht ausschließlich aus benannten Konstanten vom Typ `SINT` (Short Integer).

### **Daten-Eingänge**
*Nicht zutreffend.* Diese Ressource stellt Konstanten zur Verfügung und besitzt keine Eingänge.

### **Daten-Ausgänge**
*Nicht zutreffend.* Die Konstanten werden direkt im Anwendungscode referenziert.

### **Adapter**
*Nicht zutreffend.*

## Funktionsweise
`USERFUNC_e` ist eine Sammlung vordefinierter, konstanter Werte. Jeder Name (z.B. `task_controller`) ist mit einem festen numerischen Wert (z.B. `1`) verknüpft. Diese Konstanten können in der gesamten Anwendung verwendet werden, um Geräterollen zu identifizieren, Vergleiche durchzuführen oder Parameter zu setzen, was die Code-Wartbarkeit und Lesbarkeit im Vergleich zur direkten Verwendung von "Magic Numbers" erheblich verbessert.

## Technische Besonderheiten
*   **Datentyp:** Alle Konstanten sind vom Typ `SINT` (8-Bit vorzeichenbehaftete Ganzzahl).
*   **Bereich:** Die definierten Werte liegen im Bereich von `-1` (`undefined`) bis `21`.
*   **ISOBUS-Konformität:** Die Bezeichnungen und Werte orientieren sich an den im ISOBUS-Standard (ISO 11783) definierten Gerätefunktionen.
*   **Spezielle Werte:**
    *   `undefined` (-1): Kennzeichnet eine undefinierte oder unbekannte Funktion.
    *   `all_clients` (20) & `all_server` (21): Werte für Broadcast- oder Gruppenadressierung.

## Zustandsübersicht
*Nicht zutreffend.* Konstanten besitzen keinen Zustand.

## Anwendungsszenarien
*   **Geräteidentifikation:** In einem Task-Controller kann mit `IF device_function = USERFUNC_e.virtual_terminal THEN ...` geprüft werden, ob eine Verbindung zu einem Terminal besteht.
*   **Nachrichtenfilterung:** Filterung von ISOBUS-Nachrichten (PGNs) basierend auf der Quell- oder Zielgerätefunktion.
*   **Konfiguration:** Parametrierung von Netzwerkdiensten, die nur für bestimmte Geräterollen (z.B. `file_server`) verfügbar sein sollen.
*   **Diagnose:** Lesbare Ausgabe von Geräterollen in Diagnoseprotokollen oder auf Benutzeroberflächen.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken, die eine aktive Logik enthalten, ist `USERFUNC_e` eine passive Datentyp-/Konstantendefinition. Sie ist vergleichbar mit einem `ENUM`-Datentyp in höheren Programmiersprachen oder einer `CONSTANT`-Sektion in strukturiertem Text (ST). Ihr primärer Zweck ist die Bereitstellung semantisch bedeutsamer Namen für numerische Werte, die im ISOBUS-Kontext verwendet werden.

## Fazit
Die globale Konstante `USERFUNC_e` ist ein essentielles Hilfsmittel für die Entwicklung lesbarer und wartbarer ISOBUS-Anwendungen in 4diac. Sie abstrahiert die rohen, im Standard definierten numerischen Werte für Gerätefunktionen durch aussagekräftige Bezeichner und trägt so maßgeblich zur Vermeidung von Fehlern und zur Verbesserung der Codequalität bei. Ihre Verwendung wird für alle Projekte empfohlen, die mit ISOBUS-Gerätekommunikation arbeiten.