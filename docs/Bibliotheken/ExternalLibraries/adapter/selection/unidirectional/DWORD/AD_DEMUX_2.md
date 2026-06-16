# AD_DEMUX_2


![AD_DEMUX_2](./AD_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AD_DEMUX_2` ist ein generischer AD-Demultiplexer. Er verteilt einen eingehenden AD-Adapter-Datenstrom auf einen von zwei möglichen Ausgangsadaptern, gesteuert durch einen Indexwert. Der Baustein arbeitet ereignisgesteuert und ermöglicht so eine flexible Kanalauswahl in der industriellen Automatisierung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ` | Setzt den Index `K` und löst die Weiterleitung des AD-Eingangs auf den entsprechenden Ausgang aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF` | Bestätigt die erfolgreiche Ausführung des Demultiplex-Vorgangs. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung                 |
|----------|-------|------------------------------|
| `K`      | UINT  | Index (0-basiert) zur Auswahl des Ausgangs (0 → OUT1, 1 → OUT2) |

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden.

### **Adapter**

| Richtung | Name | Typ                               | Beschreibung                        |
|----------|------|-----------------------------------|-------------------------------------|
| Socket   | `IN` | `adapter::types::unidirectional::AD` | Eingangs-Adapter (zu verteilendes Signal) |
| Plug     | `OUT1` | `adapter::types::unidirectional::AD` | Erster Ausgangs-Adapter (Index 0)   |
| Plug     | `OUT2` | `adapter::types::unidirectional::AD` | Zweiter Ausgangs-Adapter (Index 1)  |

## Funktionsweise
Wird das Ereignis `REQ` ausgelöst, wird der im Socket `IN` anliegende AD-Adapter entsprechend des aktuellen Werts von `K` an einen der beiden Plugs weitergeleitet:
- `K = 0` → Verbindung von `IN` nach `OUT1`
- `K = 1` → Verbindung von `IN` nach `OUT2`

Nach erfolgter Umschaltung wird das Ereignis `CNF` ausgegeben. Der FB arbeitet ohne interne Zustände und führt die Umschaltung innerhalb eines einzigen Ereigniszyklus aus.

## Technische Besonderheiten
- **Generischer Typ:** Der FB ist als generischer AD-Demultiplexer deklariert (`GEN_AD_DEMUX`). Er kann für beliebige `adapter::types::unidirectional::AD`-Adapter verwendet werden, solange der konkrete Typ zur Laufzeit übergeben wird.
- **Eclipse 4diac spezifisch:** Die Attribute `GenericClassName` und `TypeHash` dienen der Typprüfung und Laufzeitumgebung der Eclipse 4diac-IDE.
- **Keine Zustandsmaschine:** Die Verarbeitung erfolgt rein ereignisgesteuert ohne sequentielle Zustände; daher ist die Reaktionszeit minimal.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine (ECC). Die gesamte Logik beschränkt sich auf die Ereignisverarbeitung bei `REQ` und die unmittelbare Weiterleitung der Adapterdaten. Es gibt keine Warte- oder Betriebszustände.

## Anwendungsszenarien
- **Kanalselektion:** In einer Steuerung soll ein analoger oder digitaler Wert (via AD-Adapter) abhängig von einer Bedingung an unterschiedliche Verbraucher weitergegeben werden.
- **Redundanzumschaltung:** Ein Sensorwert kann bei Bedarf auf zwei verschiedene Auswerteeinheiten geschaltet werden.
- **Test- und Simulationsumgebungen:** Umschalten zwischen realen und simulierten Adaptern während der Inbetriebnahme.

## Vergleich mit ähnlichen Bausteinen
- **AD_MUX (Multiplexer):** Arbeitet umgekehrt – wählt aus mehreren Eingangsadaptern einen aus und leitet ihn an einen einzelnen Ausgang weiter.
- **AD_DEMUX mit mehr Ausgängen:** Für mehr als zwei Ausgänge sind Bausteine wie `AD_DEMUX_4` oder eine generischere Variante mit parametrisierbarer Kanalzahl verfügbar.
- **Manuelle Umschaltung über Logik:** Alternative könnte ein einfacher Selector-Baustein sein, der jedoch keine Adapter-Schnittstellen bietet und separate Daten- und Eventverbindungen erfordert.

## Fazit
Der `AD_DEMUX_2` ist ein kompakter, generischer Funktionsblock zur einfachen Demultiplexion von AD-Adaptern. Seine klare Schnittstelle, die rein ereignisgesteuerte Arbeitsweise und die Unterstützung generischer Typen machen ihn zu einem flexiblen Werkzeug für viele automatisierungstechnische Aufgaben, bei denen ein Signal wahlweise auf einen von zwei Wegen geschaltet werden muss.