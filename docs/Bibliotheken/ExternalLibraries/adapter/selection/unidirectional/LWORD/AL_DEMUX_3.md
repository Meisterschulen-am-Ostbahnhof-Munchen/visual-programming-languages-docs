# AL_DEMUX_3


![AL_DEMUX_3](./AL_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_DEMUX_3** ist ein generischer Demultiplexer für unidirektionale AL‑Adapterdaten. Er leitet einen eingehenden Adapter‑Datenstrom (über den Socket **IN**) wahlweise an einen von drei Ausgangs‑Adaptern (**OUT1**, **OUT2**, **OUT3**) weiter. Die Umschaltung erfolgt über einen Dateneingang **K** und wird durch ein Ereignis **REQ** ausgelöst. Der Baustein eignet sich besonders für Anwendungen, bei denen ein Signal je nach Index auf verschiedene Pfade verteilt werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Setzt den Index K und leitet die Daten um |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung der erfolgreichen Umschaltung |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| K | UINT | Index (1, 2 oder 3) für den zu aktivierenden Ausgang |

### **Daten-Ausgänge**
– Keine –

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug | **OUT1** | adapter::types::unidirectional::AL | Erster Ausgangskanal |
| Plug | **OUT2** | adapter::types::unidirectional::AL | Zweiter Ausgangskanal |
| Plug | **OUT3** | adapter::types::unidirectional::AL | Dritter Ausgangskanal |
| Socket | **IN** | adapter::types::unidirectional::AL | Eingangssignal, das demultiplext wird |

## Funktionsweise

1. Der Adapter **IN** liefert kontinuierlich Daten (z. B. einen Messwert oder ein Steuersignal).
2. Ein externer Aufruf löst das Ereignis **REQ** aus.
3. Der Funktionsblock liest den aktuellen Wert des Dateneingangs **K**. Dieser muss im Bereich 1..3 liegen.
4. Abhängig von **K** wird der Eingangsadapter **IN** mit dem entsprechenden Ausgangsadapter (**OUT1**, **OUT2** oder **OUT3**) verbunden.
   - Für **K=1** werden die Daten an **OUT1** weitergeleitet.
   - Für **K=2** werden die Daten an **OUT2** weitergeleitet.
   - Für **K=3** werden die Daten an **OUT3** weitergeleitet.
5. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben.

> **Hinweis:** Der Wert von **K** wird nur bei einem **REQ**‑Ereignis ausgewertet. Eine Änderung des Dateneingangs zwischen zwei Ereignissen hat keine sofortige Wirkung.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generischer Typ (GenericClassName `GEN_AL_DEMUX`) definiert und kann in verschiedenen Projekten mit dem Adapter‑Typ **AL** verwendet werden.
- **Keine Datenausgänge:** Die Ausgangsdaten werden ausschließlich über die Adapter‑Plugs transportiert. Dies ermöglicht eine flexible Weiterverarbeitung in nachgeschalteten Bausteinen.
- **Unidirektionale Adapter:** Sowohl der Eingang als auch die Ausgänge verwenden den Adaptertyp `adapter::types::unidirectional::AL`. Dies setzt voraus, dass der Datenfluss nur in eine Richtung erfolgt.
- **Indexbegrenzung:** Der Funktionsblock erwartet für **K** Werte zwischen 1 und 3. Werte außerhalb dieses Bereichs führen zu keinem definierten Verhalten (oder werden möglicherweise ignoriert).

## Zustandsübersicht

Der **AL_DEMUX_3** besitzt einen einfachen internen Ablauf ohne dauerhafte Zustandsmaschine. Die einzige Aktion erfolgt synchron zum Ereignis **REQ**:

| Zustand | Ereignis | Aktion |
|---------|----------|--------|
| Bereit | REQ | Lesen von K, Verbindung umschalten, CNF senden |

Nach dem Senden von **CNF** kehrt der Baustein sofort in den Bereit‑Zustand zurück.

## Anwendungsszenarien

- **Sensor‑Multiplexing:** Ein einzelner Sensor (z. B. Temperatur, Druck) wird abwechselnd an verschiedene Auswerteeinheiten weitergeleitet.
- **Steuerungsrouting:** In einer Maschinensteuerung werden Steuersignale je nach Betriebsmodus auf verschiedene Aktoren verteilt.
- **Test‑ und Prüfstände:** Ein Testsignal kann wahlweise auf verschiedene Messstellen geschaltet werden.
- **Landtechnik:** In der Agrar‑Elektronik (z. B. ISOBUS‑Anwendungen) kann ein Datensignal auf unterschiedliche Anbaugeräte aufgeteilt werden.

## Vergleich mit ähnlichen Bausteinen

| FB | Unterschied |
|----|-------------|
| **AL_DEMUX_2** | Bietet nur zwei Ausgangsadapter anstelle von drei |
| **AL_MUX** | Führt die umgekehrte Funktion aus (Multiplexer: mehrere Eingänge → ein Ausgang) |
| **E_SWITCH** | Arbeitet mit Einzelsignalen (Bit/Byte), nicht mit Adaptern |
| **FBD_DEMUX** | Daten‑Demultiplexer auf Ebene elementarer Datentypen (z. B. INT, REAL), ohne Adapterunterstützung |

Der **AL_DEMUX_3** zeichnet sich durch die direkte Adapter‑Schnittstelle aus, die eine nahtlose Integration in adapterbasierte Kommunikationspfade ermöglicht.

## Fazit

Der **AL_DEMUX_3** ist ein kompakter und effizienter Funktionsblock zum Verteilen von unidirektionalen AL‑Adapterdaten auf drei Kanäle. Die indexgesteuerte Umschaltung über ein Ereignis macht ihn einfach handhabbar und für vielfältige Routing‑Aufgaben geeignet. Durch seinen generischen Aufbau kann er ohne Anpassung in unterschiedlichen Projekten eingesetzt werden.