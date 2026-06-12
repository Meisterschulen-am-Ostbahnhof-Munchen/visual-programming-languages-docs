# ADI_SPLIT_4


![ADI_SPLIT_4](./ADI_SPLIT_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ADI_SPLIT_4** dient als generischer Verteiler (Splitter) für einen einzelnen ADI-Datenstrom. Er empfängt einen ADI-Eingang über die Socket-Schnittstelle `IN` und stellt diesen auf vier identische ADI-Ausgänge über die Plug-Schnittstellen `OUT1`, `OUT2`, `OUT3` und `OUT4` zur Verfügung. Dieser Baustein ist ideal, wenn ein ADI-Signal parallel an mehrere nachfolgende Komponenten weitergeleitet werden soll.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Typ       | Name   | Richtung | Beschreibung |
|-----------|--------|----------|--------------|
| `ADI` (unidirektional) | `IN`   | Socket   | Empfang des zu verteilenden ADI-Datenstroms. |
| `ADI` (unidirektional) | `OUT1` | Plug     | Erster Ausgang – identische Kopie des Eingangssignals. |
| `ADI` (unidirektional) | `OUT2` | Plug     | Zweiter Ausgang – identische Kopie des Eingangssignals. |
| `ADI` (unidirektional) | `OUT3` | Plug     | Dritter Ausgang – identische Kopie des Eingangssignals. |
| `ADI` (unidirektional) | `OUT4` | Plug     | Vierter Ausgang – identische Kopie des Eingangssignals. |

## Funktionsweise

Der Baustein arbeitet als reine **Vervielfältigung** des ADI-Signals. Sobald ein gültiger ADI-Datenstrom am Socket `IN` anliegt, wird dieser unverändert und ohne Verzögerung an alle vier Plugs (`OUT1` … `OUT4`) weitergegeben. Es findet keinerlei Logik, Filterung oder Datenmanipulation statt – das Verhalten entspricht einem passiven Signalverteiler.

Da es sich um einen generischen Funktionsblock (generic FB) handelt, wird der zugrundeliegende ADI-Typ erst zur Laufzeit oder beim Einbinden in ein Projekt konkret bestimmt. Die Schnittstellendefinition selbst ist typunabhängig.

## Technische Besonderheiten

- **Generischer Typ** – Der Baustein wird als `GEN_ADI_SPLIT` deklariert und kann mit jedem konkreten ADI-Adaptertyp instanziiert werden.
- **Keine Ereignisse** – Die Signalverteilung erfolgt rein über die Adapter-Schnittstellen; es sind keine Ereigniseingänge oder -ausgänge vorhanden.
- **Skalierbarkeit** – Der Baustein ist auf genau vier Ausgänge festgelegt. Für andere Anzahlen stehen abweichende Varianten (z. B. `ADI_SPLIT_2`) zur Verfügung.

## Zustandsübersicht

Der Funktionsblock besitzt keine explizite Zustandsmaschine (ECC). Da er ausschließlich eine passive Signalweitergabe realisiert, ist kein interner Zustand erforderlich.

## Anwendungsszenarien

- **Parallelbetrieb** – Ein von einem Sensor oder Vorgängerbaustein bereitgestellter ADI-Datenstrom soll gleichzeitig von mehreren Aktoren, Logikblöcken oder Visualisierungskomponenten genutzt werden.
- **Prototyping** – In der Entwicklungsphase können mit dem Splitter mehrere Pfade desselben Signals auf einfache Weise getestet werden.
- **Redundanz** – Das ADI-Signal kann an mehrere redundante Auswertepfade verteilt werden.

## Vergleich mit ähnlichen Bausteinen

- **ADI_SPLIT_2** – Verteilt ein ADI-Signal auf zwei Ausgänge. Identische Funktionsweise, aber geringere Anzahl an Ausgängen.
- **ADI_MERGE** – Führt mehrere ADI-Eingänge zu einem Ausgang zusammen (Gegenstück zum Splitter).
- **Manuelle Verdrahtung** – Alternativ könnte die Verteilung auch durch mehrfaches Anschließen des gleichen Ausgangs erfolgen, jedoch ist der Splitter in der 4diac-IDE die sauberere und wiederverwendbare Lösung.

## Fazit

Der **ADI_SPLIT_4** ist ein einfacher, aber nützlicher generischer Funktionsblock zur Vervielfachung eines ADI-Datenstroms. Er erfordert keine Konfiguration und fügt sich nahtlos in modulare Automatisierungsprojekte ein. Durch die Adapter-basierte Schnittstelle bleibt er flexibel und lässt sich ohne Änderungen an der internen Logik in unterschiedliche Umgebungen einbinden.