# ADI_TO_AULI


![ADI_TO_AULI](./ADI_TO_AULI.svg)

* * * * * * * * * *
## Einleitung
Der Baustein **ADI_TO_AULI** ist ein Composite-Funktionsblock (FB) gemäß IEC 61499. Er dient der Umwandlung eines DINT-Wertes (vorzeichenbehaftete 32‑Bit‑Ganzzahl), der über einen ADI‑Adapter (Input‑Schnittstelle) eingeht, in einen ULINT‑Wert (vorzeichenlose 64‑Bit‑Ganzzahl), der über einen AULI‑Adapter (Output‑Schnittstelle) ausgegeben wird. Intern wird der standardisierte Konvertierungsbaustein `F_DINT_TO_ULINT` aus der IEC‑61131‑Bibliothek verwendet. Der Baustein vereinfacht die Integration von Adaptern und die Typumwandlung in Automatisierungslösungen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Bezeichnung | Typ | Beschreibung |
|-------------|-----|--------------|
| ADI_IN.E1   | Ereignis (implizit) | Auslöser für die Konvertierung; wird vom ADI‑Adapter bereitgestellt. |

### **Ereignis-Ausgänge**

| Bezeichnung | Typ | Beschreibung |
|-------------|-----|--------------|
| AULI_OUT.E1 | Ereignis (implizit) | Signalisiert den Abschluss der Konvertierung; wird an den AULI‑Adapter weitergegeben. |

### **Daten-Eingänge**

| Bezeichnung | Typ   | Beschreibung |
|-------------|-------|--------------|
| ADI_IN.D1   | DINT  | Eingangswert, der in ULINT konvertiert werden soll. |

### **Daten-Ausgänge**

| Bezeichnung | Typ    | Beschreibung |
|-------------|--------|--------------|
| AULI_OUT.D1 | ULINT  | Konvertierter Ausgangswert (vorzeichenlos). |

### **Adapter**

| Name      | Typ (Schnittstelle)   | Richtung | Beschreibung |
|-----------|-----------------------|----------|--------------|
| ADI_IN    | ADI (Socket)          | Input    | Nimmt den DINT‑Wert über einen unidirektionalen ADI‑Adapter entgegen. |
| AULI_OUT  | AULI (Plug)           | Output   | Stellt den konvertierten ULINT‑Wert über einen unidirektionalen AULI‑Adapter bereit. |

## Funktionsweise
Der Baustein wartet auf ein Ereignis am Eingangsadapter `ADI_IN.E1`. Sobald dieses eintrifft, wird der aktuelle Datenwert `ADI_IN.D1` (Typ DINT) an den internen Konvertierungs‑FB `F_DINT_TO_ULINT` übergeben. Nach erfolgreicher Umwandlung wird das Ergebnis (Typ ULINT) an den Ausgang `AULI_OUT.D1` weitergeleitet und ein Ereignis am Ausgang `AULI_OUT.E1` ausgelöst. Die gesamte Logik ist rein kombinatorisch – es gibt keine Verzögerungen oder Zustände außer der Signalverarbeitung des internen Bausteins.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle:** Der Baustein verwendet ausschließlich Adapter‑Plugs und ‑Sockets für die Ein‑ und Ausgabe. Dies erlaubt eine saubere Kapselung und Wiederverwendung in modularen Steuerungsarchitekturen.
- **Unidirektionale Adapter:** Sowohl der ADI‑ als auch der AULI‑Adapter sind als unidirektional deklariert und übertragen nur in eine Richtung (Eingang oder Ausgang).
- **Interne Konvertierung:** Der für die eigentliche Wandlung zuständige FB `F_DINT_TO_ULINT` ist dem Paket `iec61131::conversion` entnommen und stellt eine standardisierte, ablaufinvariante Funktion bereit.
- **Namensraum:** Der Composite‑FB gehört zum Paket `adapter::conversion::unidirectional`, was seine Rolle als Adapter‑Wrapper deutlich macht.

## Zustandsübersicht
Als Composite‑Baustein besitzt `ADI_TO_AULI` keine eigene Zustandsmaschine. Sein Verhalten wird vollständig durch die interne Verknüpfung der Ereignis‑ und Datenflüsse zwischen dem Socket `ADI_IN`, dem Konvertierungs‑FB und dem Plug `AULI_OUT` bestimmt. Die Zustandslogik des internen Bausteins `F_DINT_TO_ULINT` ist für die Funktionsweise transparent.

## Anwendungsszenarien
- **Übergang zwischen Steuerungssystemen:** Wenn ein System mit DINT‑Signalen (z. B. SPS‑Daten) mit einem anderen System kommunizieren muss, das ULINT‑Werte erwartet (z. B. Visualisierung oder Langzeitarchivierung mit 64‑Bit‑Zeitstempeln).
- **Adapter‑Brücke:** In einer modularen Automatisierungsumgebung, in der Adapter für unterschiedliche Datentypen definiert sind, dient der Baustein als einfaches „Übersetzungsglied” zwischen ADI‑ und AULI‑Schnittstellen.
- **Prototypen oder Migration:** Schnelle Integration von Komponenten mit unterschiedlichen Integer‑Darstellungen ohne anwendungsspezifische Konvertierungslogik.

## Vergleich mit ähnlichen Bausteinen
- **Separater `F_DINT_TO_ULINT`:** Der hier verwendete interne FB ist direkt für die reine Typumwandlung zuständig, erfordert jedoch separate Ereignis‑ und Datenverbindungen. `ADI_TO_AULI` kapselt diese Verbindungen und die Adapter‑Anbindung in einem einzigen Baustein.
- **Andere Adapter‑Wrapper:** Es existieren ähnliche Composite‑Bausteine für andere Typumwandlungen (z. B. `ADI_TO_AUDI`, `ASI_TO_AULI`), die nach demselben Muster aufgebaut sind. Sie unterscheiden sich lediglich durch die beteiligten Datentypen.
- **Direkte Typkonvertierung ohne Adapter:** Manche Systeme bieten Konvertierungsfunktionen als reine Funktionsbausteine ohne Adapter‑Schicht. Der vorliegende Baustein ist speziell auf den Einsatz mit Adaptern ausgelegt.

## Fazit
Der `ADI_TO_AULI`‑Baustein ist ein kompakter, adapterbasierter Wrapper zur Umwandlung von DINT‑ in ULINT‑Werte. Durch die saubere Trennung von Adapter‑ und Konvertierungslogik erhöht er die Wiederverwendbarkeit und Lesbarkeit von Steuerungsprogrammen. Er eignet sich besonders für modulare Automatisierungslösungen, die auf unidirektionale Adapter setzen und eine standardisierte Typumwandlung benötigen.