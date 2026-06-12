# AD_DEMUX_4

Kein Bild verfügbar.


![AD_DEMUX_4](./AD_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AD_DEMUX_4` ist ein generischer AD‑Demultiplexer (engl. „AD demultiplexor“). Er verteilt einen über einen Socket‑Adapter anliegenden Eingang auf einen von vier Ausgangs‑Adapter. Die Auswahl des aktiven Ausgangs erfolgt ereignisgesteuert über einen Index.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Beschreibung |
|------|--------------|
| `REQ` | Setzen des Index `K` und Auslösen der Umschaltung. |

### **Ereignis-Ausgänge**

| Name | Beschreibung |
|------|--------------|
| `CNF` | Bestätigt die erfolgreiche Umschaltung auf den durch `K` bestimmten Ausgang. |

### **Daten-Eingänge**

| Name   | Typ    | Beschreibung |
|--------|--------|--------------|
| `K`    | `UINT` | Index, der den aktiven Ausgang bestimmt (Wertebereich abhängig von der konkreten Parametrisierung – typischerweise 0 bis 3 oder 1 bis 4). |

### **Daten-Ausgänge**

Keine separaten Datenausgänge vorhanden.

### **Adapter**

#### Socket (Eingang)

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `IN`  | `adapter::types::unidirectional::AD` | Eingangsadapter, dessen Verbindung auf den gewählten Ausgang umgeleitet wird. |

#### Plugs (Ausgänge)

| Name  | Typ | Beschreibung |
|-------|-----|--------------|
| `OUT1` | `adapter::types::unidirectional::AD` | Erster Ausgang. |
| `OUT2` | `adapter::types::unidirectional::AD` | Zweiter Ausgang. |
| `OUT3` | `adapter::types::unidirectional::AD` | Dritter Ausgang. |
| `OUT4` | `adapter::types::unidirectional::AD` | Vierter Ausgang. |

## Funktionsweise

Sobald ein Ereignis am Eingang `REQ` eintrifft, wird der aktuelle Wert des Index `K` ausgewertet. Der Funktionsblock verbindet den Eingangs‑Adapter `IN` mit dem durch `K` bezeichneten Ausgangs‑Adapter (`OUT1` … `OUT4`). Nach der erfolgreichen Umschaltung wird das Ereignis `CNF` ausgegeben. Die nicht ausgewählten Ausgänge sind zu diesem Zeitpunkt inaktiv bzw. getrennt.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generisch deklariert (`GenericClassName = 'GEN_AD_DEMUX'`). Dadurch kann er mit unterschiedlichen Adapter‑Typen parametrisiert werden.  
- **Unidirektional**: Sowohl der Socket als auch die Plugs sind vom Typ `unidirectional::AD`, d.h. die Datenflussrichtung ist festgelegt.  
- **Ereignisgesteuerte Umschaltung**: Die Umschaltung erfolgt ausschließlich auf das `REQ`‑Ereignis hin – es wird kein zyklischer Abtastbetrieb durchgeführt.

## Zustandsübersicht

Eine explizite Zustandsmaschine ist im Quelltext des Bausteins nicht hinterlegt. Das Verhalten beschränkt sich auf:

1. Warten auf ein `REQ`‑Ereignis.  
2. Auswerten des Index `K`.  
3. Verbinden von `IN` mit dem entsprechenden `OUTX`.  
4. Senden von `CNF`.  
5. Rückkehr in den Wartezustand.

## Anwendungsszenarien

- Umschalten eines analogen Messsignals zwischen verschiedenen Verarbeitungseinheiten.  
- Ansteuerung mehrerer Aktoren aus einer gemeinsamen Signalquelle.  
- Auswahl einer von mehreren Adapter‑basierten Kommunikationsstrecken (1‑zu‑N‑Weiche).  
- Flexibles Routing in modularen Automatisierungssystemen auf Basis der IEC 61499.

## Vergleich mit ähnlichen Bausteinen

Der `AD_DEMUX_4` ist das Gegenstück zum Multiplexer‑Baustein (z.B. `AD_SELECT`), der mehrere Eingänge auf einen Ausgang zusammenführt. Während ein Multiplexer also eine **N‑zu‑1**‑Funktion realisiert, bildet der Demultiplexer eine **1‑zu‑N**‑Funktion. Im Unterschied zu klassischen Demultiplexern für elementare Datentypen arbeitet dieser Baustein mit **Adapter‑Schnittstellen**, wodurch er komplexe, zusammengesetzte Signale oder Protokolle in einer strukturierten Form routen kann.

## Fazit

Der `AD_DEMUX_4` ist ein vielseitiger, generischer Adapter‑Demultiplexer für die IEC‑61499‑Umgebung. Durch die ereignisgesteuerte Umschaltung und die Nutzung von Adaptern eignet er sich besonders für flexible Signalweichen in modularen Automatisierungs- und Steuerungssystemen.