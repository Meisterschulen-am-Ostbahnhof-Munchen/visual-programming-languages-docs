# AR_DEMUX_2


![AR_DEMUX_2](./AR_DEMUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AR_DEMUX_2** ist ein generischer Demultiplexer für unidirektionale AR‑Adapter. Er leitet einen eingehenden AR‑Adapter-Wert (über den Socket `IN`) auf einen von zwei möglichen Ausgangsadaptern (`OUT1` oder `OUT2`) weiter. Die Auswahl des Zielausgangs erfolgt über einen Index `K`, der durch ein Ereignis `REQ` gesetzt wird. Der Baustein wird typischerweise eingesetzt, um einen Daten- oder Signalpfad gezielt auf verschiedene nachfolgende Funktionsbausteine zu schalten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Fordert die Übernahme des Index `K` an und löst die Demultiplex-Operation aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigt die erfolgreiche Ausführung der Demultiplex-Operation. |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung             |
|------|-------|--------------------------|
| `K`  | UINT  | Ganzzahliger Index (1‑basiert) zur Auswahl des Ausgangs (1 → OUT1, 2 → OUT2). |

### **Daten-Ausgänge**

Keine eigenen Datenausgänge; die Ausgabe erfolgt ausschließlich über die Adapter `OUT1` und `OUT2`.

### **Adapter**

| Typ    | Name  | Richtung | Beschreibung                                    |
|--------|-------|----------|-------------------------------------------------|
| Socket | `IN`  | Eingang  | Unidirektionaler AR‑Adapter, der demultiplext wird. |
| Plug   | `OUT1`| Ausgang  | Erster Zieladapter für den demultiplexten Wert.   |
| Plug   | `OUT2`| Ausgang  | Zweiter Zieladapter für den demultiplexten Wert.  |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Mit dem Ereignis wird der aktuelle Wert des Daten‑Eingangs `K` eingelesen.
3. Der Wert des an `IN` anliegenden AR‑Adapters wird auf den durch `K` bestimmten Ausgangsadapter übertragen:
   - `K = 1` → Ausgang `OUT1`
   - `K = 2` → Ausgang `OUT2`
   - Bei anderen Werten von `K` (z. B. 0 oder >2) wird keine Aktion ausgeführt (der Zustand der Ausgänge bleibt unverändert).
4. Nach erfolgreicher Übertragung wird das Ereignis `CNF` ausgegeben.

Die Operation ist ereignisgesteuert und arbeitet ohne internen Puffer – jeder `REQ`-Aufruf führt sofort zur Demultiplexung des aktuellen `IN`-Werts.

## Technische Besonderheiten

- Der Baustein ist als **generic FB** deklariert (GenericClassName = `GEN_AR_DEMUX`), d. h. er kann durch typspezifische Parametrisierung an verschiedene AR‑Adapter‑Typen angepasst werden.
- Die Schnittstelle verwendet ausschließlich unidirektionale Adapter, was eine klare Trennung von Datenflussrichtung gewährleistet.
- Der Index `K` wird als `UINT` abgebildet; die Zählung beginnt bei 1 für den ersten Ausgang.
- Die Laufzeitumgebung muss die Adapter‑Typen zur Verfügung stellen (`adapter::types::unidirectional::AR`).

## Zustandsübersicht

Der Funktionsblock besitzt kein explizites Zustandsdiagramm (ECC) in der bereitgestellten Definition. Er verhält sich wie ein **kombinatorischer** FB mit ereignisgesteuertem Auslösen:

- **IDLE** – Warten auf `REQ`
- **ACTIVE** – Verarbeitung des Index und Übertragung des Adapters (dauert einen einzigen Zyklus)
- **DONE** – Ausgabe von `CNF`, Rückkehr in IDLE

Da keine internen Zustandsvariablen existieren, ist das Verhalten deterministisch und nebenläufig sicher.

## Anwendungsszenarien

- **Routenumschaltung**: In einer industriellen Steuerung kann der AR_DEMUX_2 dazu verwendet werden, einen einkommenden Sensor‑ oder Aktor‑Adapter wahlweise an zwei unterschiedliche Verarbeitungslogiken weiterzuleiten.
- **Redundanz‑Umschaltung**: Ein primäres Signal wird im Fehlerfall auf einen sekundären Pfad umgeschaltet.
- **Test‑/Produktionsmodus**: Je nach Betriebsmodus wird derselbe Datenstrom an eine Test‑ oder eine Produktionseinheit weitergegeben.

## Vergleich mit ähnlichen Bausteinen

- **AR_MUX_2** (Multiplexer): Ein Multiplexer wählt aus mehreren Eingangsadaptern einen aus und leitet ihn an einen einzelnen Ausgang weiter. Der AR_DEMUX_2 arbeitet genau umgekehrt: ein Eingang wird auf mehrere Ausgänge verteilt.
- **AR_SELECTOR**: Ein einfacher Schalter, der ebenfalls zwischen zwei Pfaden wählt, jedoch oft ohne Index‑Ereignis (z. B. über einen booleschen Eingang). Der AR_DEMUX_2 bietet durch den UINT‑Index eine erweiterte Auswahlmöglichkeit und ist auf mehrere Ausgänge skalierbar (hier: zwei).
- **SWITCH‑Bausteine (IEC 61499‑Standard)**: Viele Standard‑Bibliotheken enthalten generische Demultiplexer für einfache Datentypen (z. B. ANY). Der AR_DEMUX_2 abstrahiert den Adapter‑Typ und ist speziell für unidirektionale AR‑Schnittstellen optimiert.

## Fazit

Der **AR_DEMUX_2** ist ein kompakter, generischer Demultiplexer für unidirektionale AR‑Adapter. Er eignet sich hervorragend, um in IEC‑61499‑basierten Systemen einen eingehenden Adapter‑Pfad auf bis zu zwei Ausgänge zu schalten. Die klar definierte Schnittstelle mit Index‑Eingang und Bestätigungsereignis ermöglicht eine zuverlässige und deterministische Umschaltung in Automatisierungs‑ und Steuerungsanwendungen. Durch die Generik kann der Baustein ohne Anpassung des inneren Verhaltens für verschiedene AR‑Typen wiederverwendet werden.