# CommunicationPartners




![CommunicationPartners](./CommunicationPartners.svg)

* * * * * * * * * *
## Einleitung
`CommunicationPartners` ist ein globaler Konstanten-Datensatz, der im Kontext der ISOBUS PGN-Kommunikation (Parameter Group Number) verwendet wird. Er dient dazu, einen vordefinierten Kommunikationspartner, in diesem Fall die globale Adresse, als konstante Konfiguration für andere Funktionsblöcke bereitzustellen. Dies vereinfacht die Konfiguration von ISOBUS-Netzwerkkomponenten, indem häufig benötigte Adressen zentral und wiederverwendbar definiert werden.

## Schnittstellenstruktur
Da es sich um einen globalen Konstanten-Datensatz handelt, besitzt `CommunicationPartners` keine ereignisgesteuerten oder datenflussbasierten Schnittstellen im herkömmlichen Sinne eines Funktionsblocks. Stattdessen stellt er eine benannte, konstante Variable für die gesamte Applikation bereit.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Adapter**
Keine.

## Funktionsweise
Der Datensatz `CommunicationPartners` deklariert eine globale Konstante namens `GLOBAL` vom Datentyp `isobus::pgn::CF_INFO_T`. Diese Struktur wird mit einem Initialwert belegt, der das Feld `s16Handle` auf den vordefinierten Wert `GLOBAL_A` aus der importierten Konstante `isobus::pgn::ADDRESS::GLOBAL_A` setzt.

Bei der Kompilierung und Ausführung der Applikation wird diese Konstante im Speicher abgelegt und kann von jedem Funktionsblock innerhalb des Projekts referenziert werden, der eine ISOBUS-Adresse vom Typ `CF_INFO_T` benötigt. Die Verwendung dieser Konstante stellt sicher, dass die globale Adresse konsistent und ohne Tippfehler im gesamten Code verwendet wird.

## Technische Besonderheiten
*   **Datentyp:** Die Konstante ist vom Typ `isobus::pgn::CF_INFO_T`. Dies ist vermutlich eine strukturierte (STRUCT) oder Aufzählungstyp (ENUM), die speziell für die ISOBUS-Kommunikationskonfiguration definiert ist.
*   **Initialisierung:** Die Initialisierung erfolgt direkt in der Deklaration mittels Strukturinitialisierung `(s16Handle := GLOBAL_A)`.
*   **Import:** Der Datensatz importiert eine externe Konstante (`GLOBAL_A`) aus dem Paket `isobus::pgn::ADDRESS`. Dies zeigt eine modulare Architektur, bei der Adressdefinitionen an einer zentralen Stelle gepflegt werden.
*   **Kompilierung:** Das `CompilerInfo`-Tag weist darauf hin, dass dieses Element Teil des Pakets `isobus::pgn` ist und für die Codegenerierung relevant ist.

## Zustandsübersicht
Da es sich um eine statische, konstante Definition handelt, gibt es keine Zustandsmaschine oder veränderlichen Zustände.

## Anwendungsszenarien
*   **ISOBUS-Netzwerkkonfiguration:** Wird verwendet, wenn ein Funktionsblock eine Nachricht an alle Teilnehmer im ISOBUS-Netzwerk (Broadcast) senden soll. Die Konstante `GLOBAL` repräsentiert diese Broadcast-Adresse.
*   **Vereinfachung der Parametrierung:** In komplexen Applikationen mit vielen kommunizierenden Blöcken ersetzt die Verwendung von `CommunicationPartners.GLOBAL` die wiederholte, hartkodierte Eingabe der globalen Adresse und erhöht so die Wartbarkeit.
*   **Referenz für andere Konstanten:** Kann als Basis für die Definition weiterer, spezifischerer Kommunikationspartner-Konstanten dienen (z.B. `IMPLEMENT`, `TOOL`).

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **Direkte Wertzuweisung:** Anstatt `CommunicationPartners.GLOBAL` zu verwenden, könnte ein Entwickler den Wert `GLOBAL_A` auch direkt in jedem Daten-Eingang eines Funktionsblocks eintragen. Die Verwendung der Konstanten ist jedoch sauberer, typsicherer und änderungsfreundlicher.
*   **Andere Adresskonstanten:** Innerhalb des gleichen Pakets (`isobus::pgn::ADDRESS`) existieren vermutlich ähnliche Konstanten für andere Adressen (z.B. `NULL_A`, `TOOL_A`). `CommunicationPartners` kapselt eine spezifische Auswahl oder Kombination dieser Adressen in einem für die Applikation sinnvollen Kontext.
*   **Parameter-FBs vs. Globale Konstanten:** Ein alternativer Ansatz wäre ein Funktionsblock, der seine Zieladresse als konfigurierbaren Parameter erhält. Globale Konstanten sind hingegen einfacher und direkter, wenn der Wert für die gesamte Laufzeit der Applikation unveränderlich ist.

## Fazit
Der globale Konstanten-Datensatz `CommunicationPartners` ist ein einfaches, aber nützliches Hilfskonstrukt für die Entwicklung von ISOBUS-fähigen Steuerungen in 4diac. Er fördert den Prinzipien des "Don't Repeat Yourself" (DRY) und der zentralen Konfigurationsverwaltung, indem er die häufig benötigte globale ISOBUS-Adresse an einer einzigen, gut sichtbaren Stelle definiert. Seine Verwendung reduziert potenzielle Fehlerquellen und erleichtert zukünftige Anpassungen der Netzwerkkonfiguration.