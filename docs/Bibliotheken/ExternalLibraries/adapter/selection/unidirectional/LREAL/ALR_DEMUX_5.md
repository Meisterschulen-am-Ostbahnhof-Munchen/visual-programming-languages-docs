# ALR_DEMUX_5


![ALR_DEMUX_5](./ALR_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALR_DEMUX_5** ist ein generischer Demultiplexer für ALR-Daten (Adapter Typ `unidirectional`). Er verteilt die an seinem Eingang `IN` anliegenden Daten wahlweise auf einen von fünf Ausgängen (`OUT1`...`OUT5`). Die Auswahl des aktiven Ausgangs erfolgt über den Index `K`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Auslösen des Demultiplex-Vorgangs mit dem aktuellen Index `K` |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigung, dass der ausgewählte Ausgang gesetzt wurde |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K`   | UINT | Index des zu aktivierenden Ausgangs (1...5) |

### **Daten-Ausgänge**

Keine direkten Datenausgänge vorhanden. Die Datenweitergabe erfolgt über die Adapter.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | `IN`   | `adapter::types::unidirectional::ALR` | Eingangswert, der demultiplext werden soll |
| Plug (Ausgang)   | `OUT1`...`OUT5` | `adapter::types::unidirectional::ALR` | Ausgänge für den demultiplexten Wert |

## Funktionsweise

1. Der FB erwartet ein Ereignis am Eingang `REQ`.
2. Bei Eintreffen von `REQ` wird der aktuell gültige Wert des Index `K` ausgelesen (Wertebereich typischerweise 1 bis 5).
3. Der am Adapter `IN` anliegende Wert wird auf den Adapter `OUT<K>` übertragen.
4. Nach erfolgreicher Übertragung wird das Bestätigungsereignis `CNF` gesendet.

Der Demultiplexer arbeitet nach dem Prinzip „Copy‑on‑Event“ – nur bei einem `REQ` werden die Daten weitergeschaltet. Außerhalb dieses Ereignisses bleiben alle Ausgänge unverändert.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als „generic FB“ markiert (`GEN_ALR_DEMUX`), sodass er für unterschiedliche ALR‑Adaptervarianten verwendet werden kann.
- **Unidirektionale Adapter**: Sowohl der Eingang als auch die Ausgänge verwenden den unidirektionalen ALR‑Adaptertyp, d.h. die Daten fließen nur in einer Richtung (vom Socket zum Plug).
- **Feste Ausgangsanzahl**: Der FB bietet genau fünf Adapterausgänge. Ein Index außerhalb des Bereichs (z.B. 0 oder >5) sollte vermieden werden – das Verhalten ist nicht spezifiziert.
- **Ereignisgesteuert**: Die gesamte Logik wird durch das Ereignis `REQ` getriggert; es erfolgt keine zyklische oder kontinuierliche Kopie.

## Zustandsübersicht

Der FB besitzt keine expliziten Zustände mit Zustandsmaschine. Seine Funktionsweise lässt sich auf zwei Phasen reduzieren:

1. **Warten** – Der FB wartet auf ein `REQ`‑Ereignis.  
2. **Weiterleiten** – Nach dem `REQ` wird der Wert auf den gewählten Ausgang kopiert und `CNF` gesendet.

Damit handelt es sich um einen rein ereignisgesteuerten Baustein ohne internes Gedächtnis (abgesehen von den Adapterwerten).

## Anwendungsszenarien

- **Verteilung eines Sensorsignals an mehrere Aktoren** – Je nach Index `K` wird ein Messwert an einen von fünf nachgeschalteten ALR‑Empfängern weitergegeben.
- **Umschaltung zwischen verschiedenen Betriebsmodi** – Ein zentraler Wert (z.B. Sollwert) wird auf unterschiedliche Regelkreise geschaltet.
- **Testroutinen** – Ein Prüfsignal wird nacheinander an verschiedene Ausgänge angelegt, um die Funktion der nachfolgenden Glieder zu testen.

## Vergleich mit ähnlichen Bausteinen

- **ALR_MUX** – Ein Multiplexer, der mehrere Eingänge auf einen Ausgang zusammenführt. Der `ALR_DEMUX_5` ist die logische Umkehrung.
- **ALR_SWITCH** – Ein 1‑zu‑1‑Umschalter, der einen einzelnen Ausgang aus mehreren Eingängen auswählt, aber keine Verteilung auf mehrere Ausgänge vornimmt.
- **Bausteine mit festerer Ausgangsanzahl** (z.B. `ALR_DEMUX_2`, `ALR_DEMUX_8`) unterscheiden sich nur in der Anzahl der verfügbaren Adapter‑Plugs.

## Fazit

Der `ALR_DEMUX_5` ist ein kompakter, ereignisgesteuerter Demultiplexer für ALR‑Adapter. Er eignet sich besonders für Anwendungen, in denen ein einzelner Datenstrom auf eine von mehreren Leitungen umgeschaltet werden muss. Durch seine generische Auslegung und die unidirektionale Adapterschnittstelle ist er flexibel in verschiedenste Steuerungsumgebungen integrierbar.