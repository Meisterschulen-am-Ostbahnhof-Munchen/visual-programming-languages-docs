# ALI_DEMUX_3


![ALI_DEMUX_3](./ALI_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_DEMUX_3** ist ein generischer Demultiplexer für den Datentyp ALI (Application Layer Interface). Er verteilt einen eingehenden ALI-Datenstrom auf drei getrennte Ausgangsadapter, wobei die Auswahl des aktiven Ausgangs über einen Index `K` gesteuert wird. Der Baustein eignet sich für Anwendungen, bei denen eine Datenquelle sequenziell an verschiedene Senken weitergeleitet werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mitgeführt |
|----------|--------------|------------|
| `REQ`    | Ausführung des Demultiplexing-Vorgangs | `K` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigung, dass der Umschaltvorgang abgeschlossen ist |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `K`      | UINT  | Index des zu aktivierenden Ausgangs (1–3) |

### **Daten-Ausgänge**

Der Baustein besitzt keine klassischen Datenausgänge. Die Ausgangsdaten werden über die Adapter bereitgestellt.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `IN`    | ALI | Socket   | Eingangsdatenstrom, der demultiplext werden soll |
| `OUT1`  | ALI | Plug     | Erster Ausgang (aktiv bei `K = 1`) |
| `OUT2`  | ALI | Plug     | Zweiter Ausgang (aktiv bei `K = 2`) |
| `OUT3`  | ALI | Plug     | Dritter Ausgang (aktiv bei `K = 3`) |

## Funktionsweise

Der Baustein arbeitet nach dem Prinzip eines 1‑aus‑3‑Demultiplexers. Sobald ein Ereignis `REQ` eintrifft, wird der Index `K` ausgewertet. Abhängig vom Wert von `K` wird der eingehende ALI‑Datenstrom **des Sockets `IN`** auf den entsprechenden Plug (`OUT1`, `OUT2` oder `OUT3`) durchgeschaltet. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben.

- Bei `K = 1` leitet der Baustein die Daten an `OUT1` weiter.
- Bei `K = 2` leitet er die Daten an `OUT2` weiter.
- Bei `K = 3` leitet er die Daten an `OUT3` weiter.
- Alle anderen Werte von `K` (insbesondere 0 oder >3) führen zu keinem definierten Verhalten; der Baustein sollte in der aufrufenden Applikation auf gültige Werte begrenzt werden.

Der Baustein ist als **generischer Funktionsblock** (`GEN_ALI_DEMUX`) implementiert. Dadurch kann die Anzahl der Ausgänge durch Typparametrisierung variiert werden. Für die konkrete Instanz `ALI_DEMUX_3` sind genau drei Ausgänge festgelegt.

## Technische Besonderheiten

- **Generische Klasse:** Der Baustein basiert auf dem generischen Typ `GEN_ALI_DEMUX`. Dies ermöglicht eine einfache Wiederverwendung für verschiedene Kanalzahlen.
- **Adapterbasierte Kommunikation:** Alle Datenschnittstellen sind als ALI‑Adapter ausgeführt, was eine lose Kopplung und modulare Integration in Adapter‑Netzwerke erlaubt.
- **Unidirektionale Datenrichtung:** Der Socket `IN` und die Plugs `OUT1..OUT3` sind unidirektional (eingehend/ausgehend), was die Datenflussrichtung klar definiert.
- **Keine Zustandsmaschine:** Der FB arbeitet rein ereignisgesteuert und verfügt über keinen expliziten internen Zustandsautomaten. Die Umschaltung erfolgt bei jedem `REQ`‑Ereignis synchron.

## Zustandsübersicht

Der Baustein besitzt **keine explizite Zustandsmaschine**. Der Ablauf ist deterministisch:

1. Warten auf `REQ`.
2. Bei `REQ`: Auswerten von `K`, Durchschalten des ALI‑Datenstroms auf den entsprechenden Ausgang.
3. Senden von `CNF`.
4. Rückkehr in den Wartezustand.

Eine Unterscheidung mehrerer interner Zustände ist nicht erforderlich.

## Anwendungsszenarien

- **Steuerung mehrerer Aktoren:** Ein Sensor liefert ALI‑Daten, die wahlweise an drei verschiedene Aktoren weitergeleitet werden sollen. Der Index wird durch eine übergeordnete Steuerlogik gesetzt.
- **Kanalwahl in Kommunikationssystemen:** Verteilung eines eingehenden Datenstroms auf drei parallele Empfänger, z. B. für Test- oder Monitoringzwecke.
- **Ressourcenumschaltung:** In einer Fertigungsanlage kann ein Messwert je nach Betriebsmodus an eine von drei Auswerteeinheiten gesendet werden.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einem **Multiplexer** (z. B. `ALI_MUX`), der mehrere Eingänge auf einen Ausgang zusammenführt, verteilt der `ALI_DEMUX_3` einen einzelnen Eingang auf mehrere Ausgänge. Gegenüber einem **statischen Splitter** (der alle Eingänge parallel kopiert) erlaubt der Demux eine indexbasierte Selektion und reduziert so die Buslast. Ähnliche Bausteine existieren für andere Datentypen (z. B. `GEN_DEMUX` für generische Daten), jedoch ist dieser FB speziell für den ALI‑Adaptertyp optimiert.

## Fazit

Der **ALI_DEMUX_3** ist ein kompakter, generischer Demultiplexer für ALI‑Datenströme mit drei Ausgängen. Er eignet sich besonders für modulare Architekturen, die eine flexible Signalumleitung erfordern. Durch die Adapter‑Schnittstelle lässt er sich nahtlos in bestehende IEC‑61499‑Applikationen integrieren und bietet dank seiner generischen Basis eine hohe Wiederverwendbarkeit.