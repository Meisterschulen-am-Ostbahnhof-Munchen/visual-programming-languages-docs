# AI_DEMUX_2


![AI_DEMUX_2](./AI_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AI_DEMUX_2** ist ein generischer Demultiplexer für unidirektionale Analog-Input (AI)-Adapter. Er verteilt einen über den Socket **IN** ankommenden AI-Wert wahlweise auf einen der beiden Ausgangsadapter **OUT1** oder **OUT2**, basierend auf einem am Ereigniseingang **REQ** übergebenen Index **K**. Der Baustein ist als generischer FB (`GEN_AI_DEMUX`) realisiert und ermöglicht so die flexible Anpassung an unterschiedliche AI-Datentypen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K (mit Daten-Eingang **K** verbunden) |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der Indexauswahl (nach erfolgter Weiterleitung) |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index für die Auswahl des Ausgangs (1 oder 2) |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Datenweitergabe erfolgt über die nachgeschalteten Adapter.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket   | IN   | Adapter `adapter::types::unidirectional::AI` | Eingangswert, der demultiplext werden soll |
| Plug     | OUT1 | Adapter `adapter::types::unidirectional::AI` | Erster Ausgang (Index 1) |
| Plug     | OUT2 | Adapter `adapter::types::unidirectional::AI` | Zweiter Ausgang (Index 2) |

## Funktionsweise
1. Der FB wartet auf ein Ereignis am Eingang **REQ**.
2. Gleichzeitig mit dem Ereignis wird der Index **K** ausgewertet.
   - **K = 1**: Der aktuelle Wert des Socket-Adapters **IN** wird an den Plug **OUT1** weitergeleitet.
   - **K = 2**: Der Wert wird an den Plug **OUT2** weitergeleitet.
   - Bei anderen Werten für **K** bleibt das Verhalten undefiniert (keine Auswahl).
3. Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben.

Die interne Logik ist ereignisgesteuert und rein kombinatorisch – es werden keine Zwischenzustände gespeichert.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist mit dem Attribut `GenericClassName = 'GEN_AI_DEMUX'` versehen und kann für verschiedene Ausprägungen des AI-Adapters instanziiert werden.
- **Typüberprüfung**: Der Adaptertyp (`adapter::types::unidirectional::AI`) muss von den verwendeten Quellen und Senken unterstützt werden. Die Kompatibilität wird zur Entwicklungszeit geprüft.
- **Copyright**: Der Baustein unterliegt der Eclipse Public License 2.0 (EPL-2.0) und wurde ursprünglich von der HR Agrartechnik GmbH entwickelt.

## Zustandsübersicht
Der FB besitzt keine expliziten Zustände im Sinne einer Zustandsmaschine. Die Verarbeitung erfolgt ereignisgesteuert und ist vollständig determiniert durch die aktuelle Kombination von **REQ** und **K**.

## Anwendungsszenarien
- **Mehrere Sensoren an einem Bus**: Ein einzelner AI-Wert (z. B. von einem Messumformer) soll je nach Betriebsmodus auf zwei unterschiedliche Steuerungspfade geschaltet werden.
- **Redundanzumschaltung**: Auswahl zwischen zwei unterschiedlichen Signalquellen (z. B. Primär- und Sekundärsensor), die über den gleichen Socket hereinkommen.
- **Parametrierbare Signalverteilung**: In einer Maschinensteuerung kann über einen Index zwischen zwei Ausgängen gewählt werden, z. B. für Heizung oder Kühlung.

## Vergleich mit ähnlichen Bausteinen
- **AI_DEMUX_1**: Ein einfacherer Demultiplexer mit nur einem Ausgang – dieser FB dient eher als Durchschalter (MUX) denn als DEMUX.
- **AI_SWITCH**: Ein Schalter auf Ereignisebene, der zwischen zwei Ereignispfaden umschaltet, aber keine Adapterdaten weitergibt.
- **Demultiplexer mit mehr als zwei Ausgängen**: Könnten durch Erweiterung des Indexbereichs und zusätzlicher Plugs realisiert werden, sind aber nicht als vordefinierte FB verfügbar.

Im Vergleich zu einem softwarebasierten Demultiplexer (z. B. in IEC 61499 mit mehreren SEND-Ereignissen) zeichnet sich **AI_DEMUX_2** durch die enge Kopplung an den AI-Adaptertyp und die saubere Aufteilung in Socket/Plug aus.

## Fazit
Der **AI_DEMUX_2** ist ein spezialisierter Baustein zur gerichteten Verteilung analoger Adaptersignale. Seine generische Natur und die klare Schnittstelle machen ihn zu einem nützlichen Werkzeug in modularen Automatisierungsprojekten, insbesondere bei der Signalumschaltung oder -verteilung auf zwei parallele Pfade. Durch die Verwendung von Adaptern bleibt die Datenintegrität gewahrt, und die einfache Indexsteuerung ermöglicht eine flexible Integration in übergeordnete Steuerungslogiken.