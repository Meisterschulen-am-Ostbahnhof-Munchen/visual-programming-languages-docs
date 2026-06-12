# AI_DEMUX_4


![AI_DEMUX_4](./AI_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung
AI_DEMUX_4 ist ein generischer Funktionsbaustein (FB) zur Demultiplexierung eines analogen Eingangssignals (AI) auf einen von vier Ausgängen. Er wird typischerweise in IEC‑61499‑basierten Automatisierungssystemen eingesetzt, um einen eingehenden Datenstrom gezielt an eine von mehreren Senken weiterzuleiten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Ereignis, das die Demultiplexierung auslöst. Der Zielausgang wird über den Dateneingang K bestimmt.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung, dass der Index K übernommen und die Weiterleitung des Signals abgeschlossen wurde.

### **Daten-Eingänge**
- **K** (UINT): Index des Zielausgangs. Gültige Werte sind 0 (OUT1), 1 (OUT2), 2 (OUT3), 3 (OUT4). Bei ungültigen Werten wird kein Ausgang gesetzt.

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Ausgabe erfolgt ausschließlich über die Adapter.

### **Adapter**
**Socket (Eingang)**
- **IN**: Adapter vom Typ `adapter::types::unidirectional::AI` für das eingehende analoge Signal.

**Plugs (Ausgänge)**
- **OUT1, OUT2, OUT3, OUT4**: Vier Adapter desselben Typs (`adapter::types::unidirectional::AI`). Nur der durch K ausgewählte Ausgang erhält den Wert von IN; die übrigen Ausgänge bleiben unverändert.

## Funktionsweise
Der Baustein arbeitet als 1‑zu‑4‑Demultiplexer. Beim Eintreffen eines REQ‑Ereignisses wird der aktuelle Wert des Eingangsadapters IN auf den durch den Dateneingang K spezifizierten Ausgangsadapter (OUT1…OUT4) kopiert. Nach erfolgreicher Zuweisung wird das CNF‑Ereignis gesendet. Die nicht adressierten Ausgänge behalten ihren bisherigen Wert. Die Funktionslogik wird durch die Laufzeitumgebung bereitgestellt; der FB ist als generischer Baustein (GenericClassName `GEN_AI_DEMUX`) deklariert.

## Technische Besonderheiten
- Unidirektionale AI‑Adapter gemäß der Schnittstellendefinition `adapter::types::unidirectional::AI`.
- Generischer Baustein (GenericClassName = `'GEN_AI_DEMUX'`) – ermöglicht Wiederverwendung in verschiedenen Applikationen.
- Keine explizite ECC (Zustandsmaschine) in der XML‑Beschreibung; die Steuerung erfolgt rein ereignisgesteuert.
- Veröffentlicht unter der Eclipse Public License 2.0 (EPL‑2.0).

## Zustandsübersicht
In der XML‑Deklaration ist keine Zustandsmaschine definiert. Der FB verhält sich wie ein einfacher Ein‑Zustands‑Automat:
1. **Warten** auf REQ.
2. Bei REQ: Index K auswerten, Wert von IN auf OUT[K] übertragen, CNF senden.
3. Zurück in den Wartezustand.

## Anwendungsszenarien
- Verteilen eines analogen Sensorsignals an mehrere Steuerungseinheiten (z. B. parallele Regelkreise).
- Umschalten zwischen verschiedenen Signalpfaden in der Prozessautomatisierung.
- Test‑ und Simulationsumgebungen, in denen ein Signal nacheinander an unterschiedliche Auswerteeinheiten geleitet wird.

## Vergleich mit ähnlichen Bausteinen
- **AI_MUX_4**: Führt die umgekehrte Operation aus – mehrere Eingänge auf einen Ausgang (Multiplexer).
- **AI_DEMUX_2 / AI_DEMUX_8**: Bausteine mit zwei bzw. acht Ausgängen; AI_DEMUX_4 stellt eine spezifische Anzahl von vier Ausgängen bereit.
- **Generische Demultiplexer**: Andere Implementierungen erlauben oft eine konfigurierbare Kanalanzahl; AI_DEMUX_4 ist auf vier Kanäle festgelegt.

## Fazit
AI_DEMUX_4 ist ein einfacher und zuverlässiger Baustein zur Signaldemultiplexierung in IEC‑61499‑Systemen. Er ermöglicht die flexible Verteilung analoger Signale auf bis zu vier Kanäle und eignet sich durch seinen generischen Aufbau für vielfältige Automatisierungsaufgaben.