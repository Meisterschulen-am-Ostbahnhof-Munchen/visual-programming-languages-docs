# ALI_DEMUX_5


![ALI_DEMUX_5](./ALI_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_DEMUX_5** ist ein generischer Demultiplexer für ALI‑Schnittstellen (Application Level Interface). Er verteilt einen ankommenden ALI‑Datenstrom auf einen von fünf unidirektionalen Ausgangsadaptern, gesteuert durch einen ganzzahligen Index. Der Baustein eignet sich besonders für Anwendungen, bei denen eine einzelne Datenquelle wahlweise an mehrere Empfänger weitergeleitet werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ` | Mit dem Ereignis wird der Index `K` übernommen und die Demultiplex‑Operation ausgelöst. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF` | Bestätigt, dass der Index `K` gesetzt und die Zuweisung des Eingangsadapter `IN` auf den gewählten Ausgangsadapter erfolgt ist. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `K`      | UINT  | Auswahlindex (1 … 5). Legt fest, welcher Ausgangsadapter (`OUT1` … `OUT5`) aktiviert wird. |

### **Daten-Ausgänge**

Keine eigenständigen Datenausgänge; die Ausgabe erfolgt über die Adapter.

### **Adapter**

| Richtung | Bezeichnung | Typ | Beschreibung |
|----------|-------------|-----|--------------|
| Eingang (Socket) | `IN` | `adapter::types::unidirectional::ALI` | Unidirektionaler ALI‑Eingang, der den zu multiplexenden Datenstrom liefert. |
| Ausgang (Plug) | `OUT1` … `OUT5` (5 Ausgänge) | `adapter::types::unidirectional::ALI` | Jeweils ein unidirektionaler ALI‑Ausgang; nur der durch `K` ausgewählte Ausgang wird mit dem Eingang `IN` verbunden. |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis `REQ`.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Daten‑Eingangs `K` ausgewertet.
3. Je nach Wert von `K` (gültig im Bereich 1 bis 5) wird der ALI‑Adapter `IN` auf den entsprechenden Ausgangsadapter `OUT1` … `OUT5` durchgeschaltet.  
   * Für `K=1` wird `IN` mit `OUT1` verbunden, für `K=2` mit `OUT2` usw.
4. Nach erfolgreicher Zuweisung wird das Ereignis `CNF` gesendet, um den Vorgang zu bestätigen.
5. Bei ungültigen Indexwerten (z. B. `K=0` oder `K>5`) bleibt die Verbindung unverändert oder es wird kein Ausgang aktiviert – die genaue Reaktion ist applikationsabhängig zu definieren.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_ALI_DEMUX`) deklariert und kann bei Bedarf für andere Ausgangsanzahlen instanziiert werden.
- **Unidirektionale Adapter**: Sämtliche ALI‑Schnittstellen arbeiten nur in eine Richtung – vom Eingang zu den Ausgängen.
- **Diskrete Indexauswahl**: Der Index `K` vom Typ `UINT` erlaubt Werte von 0 bis 65535, sinnvoll genutzt werden jedoch nur die Werte 1 bis 5. Eine Plausibilisierung ist im FB nicht enthalten und muss im aufrufenden Code erfolgen.
- **Ereignisgesteuerte Umschaltung**: Die Zuweisung erfolgt ausschließlich durch das Ereignis `REQ`; ohne Ereignis bleibt die aktuelle Verbindung bestehen.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten. Das Verhalten lässt sich jedoch in zwei Phasen beschreiben:

| Zustand | Beschreibung |
|---------|--------------|
| Warten | Es wurde kein `REQ` empfangen; die aktuelle Verbindung bleibt bestehen. |
| Verarbeitung | Nach `REQ` wird der Index ausgewertet und die Verbindung umgeschaltet. Anschließend wird `CNF` gesendet und der FB kehrt in den Wartezustand zurück. |

## Anwendungsszenarien

- **Signalverteilung**: Ein Sensor (z. B. ALI‑Encoder) liefert Daten, die wahlweise an fünf verschiedene Steuerungen oder Anzeigen weitergeleitet werden sollen.
- **Kanalschalter**: In einer modularen Maschinensteuerung kann über einen Index zwischen fünf unterschiedlichen Aktor‑Gruppen umgeschaltet werden.
- **Test‑ und Simulationsumgebungen**: Ein simulierter Datenstrom wird gezielt an verschiedene Test‑Instanzen geroutet.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
|----------|-------------|
| **ALI_DEMUX_2, _3, _4** | Gleiches Prinzip, aber mit zwei, drei bzw. vier Ausgängen. |
| **ALI_MUX** (Multiplexer) | Ein Multiplexer wählt einen von mehreren Eingängen aus und gibt ihn an einen einzigen Ausgang weiter – genau umgekehrte Richtung. |
| **Standard‑DEMUX** (Daten‑Demux) | Arbeitet oft mit skalaren Datentypen statt mit Adaptern; ALI_DEMUX_5 verwendet komplexe Adapter‑Schnittstellen. |

## Fazit

Der **ALI_DEMUX_5** ermöglicht eine flexible und ereignisgesteuerte Weiterleitung von ALI‑Datenströmen auf fünf unidirektionale Ausgänge. Durch die generische Deklaration und die klare Schnittstellenstruktur fügt er sich nahtlos in IEC‑61499‑Systeme ein und eignet sich für eine Vielzahl von Anwendungen in der Automatisierungstechnik.