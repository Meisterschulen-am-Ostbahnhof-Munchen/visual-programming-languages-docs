# AE_AX_SWITCH


![AE_AX_SWITCH](./AE_AX_SWITCH.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_AX_SWITCH** realisiert ein ereignisgesteuertes Umschalten (Demultiplexing). Ein eingehendes Ereignis wird an einen von zwei Ereignisausgängen weitergeleitet – abhängig vom booleschen Wert eines separaten Dateneingangs.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Ereignisse werden über den **Adapter `EI`** (Typ `adapter::types::unidirectional::AE`) empfangen.

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Ereignisse werden über die **Adapter `EO0` und `EO1`** (beide Typ `adapter::types::unidirectional::AE`) ausgegeben.

### **Daten-Eingänge**

- **`G`** (Adapter Typ `adapter::types::unidirectional::AX`) – Boolescher Wert, der die Umschaltung steuert.  
  * `G=0` → Ereignis wird an `EO0` geleitet  
  * `G=1` → Ereignis wird an `EO1` geleitet

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Die Ausgabe erfolgt ausschließlich über die Ereignis-Adapter.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `EI` | `AE` (Ereignis-Adapter) | Socket | Empfängt das zu schaltende Ereignis. |
| `G`  | `AX` (Daten-Adapter)   | Socket | Liefert den Schaltzustand (boolesch). |
| `EO0`| `AE` | Plug | Gibt das Ereignis aus, wenn `G=0` war. |
| `EO1`| `AE` | Plug | Gibt das Ereignis aus, wenn `G=1` war. |

## Funktionsweise

Der FB befindet sich stets im Zustand `START`. Sobald am Adapter `EI` ein Ereignis eintrifft (Signal `EI.E1`), wird der aktuelle Wert des Bool-Adapter `G.D1` ausgewertet:

- **`G.D1 = 0`** → Der FB wechselt in den Zustand `G0` und sendet ein Ereignis über den Adapter `EO0.E1`. Danach kehrt er sofort nach `START` zurück.
- **`G.D1 = 1`** → Der FB wechselt in den Zustand `G1` und sendet ein Ereignis über den Adapter `EO1.E1`. Danach kehrt er sofort nach `START` zurück.

Ein zusätzliches Ereignis am Adapter `G` (Signal `G.E1`) führt zu keiner Aktion – der FB verbleibt im Zustand `START`. Dies verhindert unerwünschte Schaltvorgänge bei Änderungen des Datenwerts.

## Technische Besonderheiten

- **Adapter-basierte Schnittstelle** – Der FB nutzt lose gekoppelte Adapter der Typen `AE` (Ereignis) und `AX` (Daten). Dies ermöglicht eine flexible Verbindung mit anderen Bausteinen im 4diac-Framework.
- **Deterministische Umschaltung** – Die Entscheidung, welcher Ausgang aktiviert wird, fällt im selben Schritt wie der Empfang des Ereignisses, wodurch keine zusätzliche Verzögerung entsteht.
- **Kein Speicherverhalten** – Nach der Ausgabe kehrt der FB sofort in den Grundzustand zurück. Der Zustand `G` wird nicht zwischengespeichert – er wird bei jedem Ereignis neu gelesen.

## Zustandsübersicht

| Zustand | Beschreibung | Ausgabeaktion |
|---------|--------------|--------------|
| `START` | Wartet auf ein Ereignis an `EI`. | – |
| `G0`    | Ereignis von `EI` bei `G.D1=0` verarbeitet. | `EO0.E1` |
| `G1`    | Ereignis von `EI` bei `G.D1=1` verarbeitet. | `EO1.E1` |

Die Zustände `G0` und `G1` werden unmittelbar nach der Ausgabe wieder verlassen (automatische Transition nach `START`).

## Anwendungsszenarien

- **Ereignis-Routing** – Weiterleitung eines Ereignisses an verschiedene nachgeschaltete Logikzweige, abhängig von einer Bedingung.
- **Zustandsabhängige Steuerung** – In Automatisierungssystemen kann ein Sensorereignis je nach Betriebsart an unterschiedliche Verarbeitungsblöcke gesendet werden.
- **Multiplexing-Umkehrung** – Als Demultiplexer für asynchrone Ereignisströme, z.B. in Kommunikationsprotokollen.

## Vergleich mit ähnlichen Bausteinen

- **E_SWITCH** – Der Standard-FB `E_SWITCH` arbeitet mit direkten Ereignis-Ein-/Ausgängen. Der `AE_AX_SWITCH` erweitert dieses Konzept durch Adapter, wodurch eine losere Kopplung und Wiederverwendbarkeit in verschiedenen Kontexten ermöglicht wird.
- **E_DEMUX** – Andere Demultiplexer-Bausteine verwenden oft mehrere Eingänge oder Zustände. Der `AE_AX_SWITCH` fokussiert auf die einfache, boolesche Umschaltung eines einzelnen Ereignisses – ohne Pufferung oder Verzögerung.

## Fazit

Der `AE_AX_SWITCH` ist ein kompakter, effizienter Demultiplexer für Ereignisse auf Basis eines booleschen Schaltsignals. Seine adapterbasierte Schnittstelle erlaubt eine flexible Integration in IEC 61499-Systeme, während das deterministische Verhalten eine zuverlässige Weiterleitung gewährleistet. Er eignet sich besonders für Anwendungen, in denen ein Ereignis je nach Zustand einer Bedingung an unterschiedliche Verarbeitungspfade gesendet werden muss.