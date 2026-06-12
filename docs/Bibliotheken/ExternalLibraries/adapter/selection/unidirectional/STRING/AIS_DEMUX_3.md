# AIS_DEMUX_3


![AIS_DEMUX_3](./AIS_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIS_DEMUX_3** ist ein generischer Demultiplexer für AIS‑Adapterdaten. Er leitet den am Socket `IN` anliegenden AIS‑Wert abhängig von einem Index `K` an einen der drei Ausgangs‑Adapter `OUT1`, `OUT2` oder `OUT3` weiter. Der Baustein eignet sich für die Verteilung von AIS‑Signalen in Steuerungssystemen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Beschreibung |
|----------|----------|--------------|
| REQ      | Event    | Startet die Weiterleitung. Der aktuelle Wert des Sockets `IN` wird an den durch `K` bestimmten Ausgangs‑Adapter gesendet. Der Eingang `K` wird gleichzeitig mit diesem Ereignis gelesen. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Beschreibung |
|----------|----------|--------------|
| CNF      | Event    | Bestätigt die erfolgreiche Durchführung der Demultiplex‑Operation. |

### **Daten-Eingänge**
| Variable | Datentyp | Beschreibung |
|----------|----------|--------------|
| K        | UINT     | Index des gewünschten Ausgangs (1, 2 oder 3). Werte außerhalb dieses Bereichs werden ignoriert oder führen zu keinem Ausgang (abhängig von der Implementierung). |

### **Daten-Ausgänge**
Keine Daten‑Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die Adapter‑Ausgänge.

### **Adapter**
| Typ | Richtung | Bezeichner | Beschreibung |
|-----|----------|------------|--------------|
| Socket (Eingang) | input | IN | Empfängt den AIS‑Wert, der demultiplext werden soll. Typ: `adapter::types::unidirectional::AIS`. |
| Plug (Ausgang) | output | OUT1 | Erster möglicher Ausgang für den demultiplexten AIS‑Wert. |
| Plug (Ausgang) | output | OUT2 | Zweiter möglicher Ausgang. |
| Plug (Ausgang) | output | OUT3 | Dritter möglicher Ausgang. |

## Funktionsweise
Bei einem Ereignis am Eingang `REQ` wird der am Socket `IN` anliegende AIS‑Wert ausgelesen. Anschließend wird dieser Wert an den durch den Daten‑Eingang `K` spezifizierten Ausgang (OUT1 für K=1, OUT2 für K=2, OUT3 für K=3) über den jeweiligen Plug weitergegeben. Nach erfolgter Weiterleitung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Baustein ist als **generischer Funktionsblock** implementiert (gekennzeichnet durch das Attribut `GenericClassName`).  
- Verwendet ausschließlich **unidirektionale AIS‑Adapter**, d.h. die Daten fließen nur vom Eingang zu den Ausgängen.  
- Die Anzahl der Ausgänge ist fest auf drei begrenzt.  
- Die Logik ist ereignisgesteuert: Eine Weiterleitung findet nur bei einem expliziten `REQ`-Ereignis statt.

## Zustandsübersicht
Da der FB keine eigene ablauforientierte Steuerung (ECC) besitzt, befindet er sich permanent in einem einzigen **Wartezustand**. Bei Eintreffen eines `REQ`-Ereignisses wird die Demultiplex‑Funktion ausgeführt und sofort das `CNF`-Ereignis erzeugt – der Baustein kehrt anschließend in den Wartezustand zurück.

## Anwendungsszenarien
- **Steuerung von A‑IS‑Sensordaten**: Ein Sensor liefert Daten über den Socket `IN`, und verschiedene Verbraucher (z.B. Aktoren oder Anzeigen) erhalten die Daten über die entsprechenden Ausgänge.  
- **Umschaltung zwischen mehreren A‑IS‑Datenquellen** (in Kombination mit einem Multiplexer).  
- **Prototyping**: In der frühen Entwicklungsphase können Ausgänge flexibel zugewiesen werden.

## Vergleich mit ähnlichen Bausteinen
- **AIS_DEMUX_2**: Besitzt nur zwei Ausgänge, entsprechend ist der Wertebereich von `K` auf 1..2 beschränkt.  
- **Generische Demultiplexer (z.B. für andere Datentypen)**: Diese arbeiten meist mit einfachen Daten‑Variablen (z.B. `ANY`) und nicht mit Adaptern. Der vorliegende Baustein ist speziell für AIS‑Adapter ausgelegt.  
- **AIS_MUX_3**: Der Multiplexer als Gegenstück fasst mehrere AIS‑Eingänge zu einem Ausgang zusammen.

## Fazit
**AIS_DEMUX_3** ist ein einfacher, aber funktionaler Demultiplexer für AIS‑Daten in IEC‑61499‑basierten Systemen. Er ermöglicht das gezielte Weiterleiten eines Adaptersignals an einen von drei Ausgängen. Durch die verwendeten Adapter ist er gut in bestehende AIS‑Kommunikationsstrukturen integrierbar. Die ereignisgesteuerte Ausführung sorgt für ein deterministisches Verhalten.