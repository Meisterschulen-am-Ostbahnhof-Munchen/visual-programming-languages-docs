# iSTATES


![iSTATES](./iSTATES.svg)

* * * * * * * * * *

## Einleitung

Der Baustein **iSTATES** ist ein spezieller GlobalConstants-Baustein der 4diac-IDE. Er definiert einen Satz benannter Konstanten, die die möglichen Zustände eines (Schieber-)Aktors abbilden. Die Konstanten sind als `USINT`-Werte hinterlegt und ermöglichen eine einheitliche, menschenlesbare Referenz auf die Zustände in der Steuerungslogik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine. Der Baustein besitzt keine Ereignis-Eingänge.

### **Ereignis-Ausgänge**

Keine. Der Baustein besitzt keine Ereignis-Ausgänge.

### **Daten-Eingänge**

Keine. Der Baustein besitzt keine Daten-Eingänge.

### **Daten-Ausgänge**

Keine. Der Baustein besitzt keine Daten-Ausgänge. Die definierten Konstanten stehen als global verfügbare Symbole im Projektkontext zur Verfügung.

### **Adapter**

Keine.

## Funktionsweise

Der Baustein **iSTATES** stellt fünf symbolische Konstanten bereit, die in der gesamten Applikation verwendet werden können. Jede Konstante repräsentiert einen diskreten Zustand eines Schiebers oder ähnlichen Aktors. Die Werte sind als `USINT` (unsigned short integer) definiert und wie folgt belegt:

| Konstante  | Wert (USINT) | Bedeutung        |
|------------|--------------|------------------|
| Unknown    | 0            | Unbekannter Zustand |
| Closed     | 1            | Geschlossen      |
| Opening    | 2            | Öffnet           |
| Opened     | 3            | Geöffnet         |
| Closing    | 4            | Schließt         |

Diese Werte können in FB-Netzwerken direkt zur Initialisierung von Variablen oder zum Vergleich mit Zustandsrückmeldungen verwendet werden.

## Technische Besonderheiten

- **Typ: GlobalConstants** – Der Baustein wird nicht instanziiert, sondern als globale Konstantendefinition in das Projekt eingebunden.
- **Wertebereich**: Alle Zustände sind als `USINT` deklariert, was einen geringen Speicherbedarf garantiert und mit vielen Feldbus-Protokollen kompatibel ist.
- **Erweiterbarkeit**: Das Schema kann leicht um weitere Zustände ergänzt werden, sofern die Applikation dies erfordert.
- **Paket**: Der Baustein ist im Paket `logiBUS::utils::sequence::schieber::const` organisiert, was eine klare Strukturierung innerhalb des Projekts erlaubt.

## Zustandsübersicht

Die fünf Zustände decken einen vollständigen Lebenszyklus eines Schiebers ab:

1. **Unknown** (0) – Initialzustand oder Fehlerzustand, wenn die aktuelle Position nicht bekannt ist.
2. **Closed** (1) – Schieber ist geschlossen (Endlage zu).
3. **Opening** (2) – Schieber befindet sich im Öffnungsvorgang.
4. **Opened** (3) – Schieber ist vollständig geöffnet (Endlage auf).
5. **Closing** (4) – Schieber befindet sich im Schließvorgang.

## Anwendungsszenarien

- **Zustandsautomaten für Schieber, Ventile oder Tore** – Der Baustein liefert die Basis für die Zustandsverwaltung in sequentiellen Steuerungen.
- **Visualisierung** – Die symbolischen Namen können in HMI- oder SCADA-Systemen zur Anzeige des aktuellen Zustands verwendet werden.
- **Fehlererkennung** – Durch den `Unknown`-Zustand können ungültige oder initiale Zustände eindeutig identifiziert werden.

## Vergleich mit ähnlichen Bausteinen

Ähnliche GlobalConstants-Bausteine existieren oft in anderen Paketen (z.B. für Motorsteuerungen, Fördereinrichtungen). Der Unterschied liegt in der spezifischen Definition der Zustände – während andere Bausteine `Idle`, `Running`, `Error` etc. verwenden, ist **iSTATES** speziell auf die fünf typischen Schieberzustände zugeschnitten. Die Verwendung von `USINT` anstelle von `BOOL` oder `INT` ist plattformeffizient und standardkonform.

## Fazit

Der Baustein **iSTATES** ist ein einfaches, aber nützliches Hilfsmittel zur konsistenten Definition von Schieber-Zuständen. Durch die Verwendung globaler Konstanten wird der Code lesbarer, fehlerresistenter und wartbarer. Er eignet sich hervorragend für alle Applikationen, in denen ein Aktor die Zustandsfolge „Geschlossen → Öffnet → Geöffnet → Schließt → Geschlossen" durchläuft.