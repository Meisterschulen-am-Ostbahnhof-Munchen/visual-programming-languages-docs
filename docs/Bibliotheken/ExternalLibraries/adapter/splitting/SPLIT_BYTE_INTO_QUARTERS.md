# SPLIT_BYTE_INTO_QUARTERS

Bild nicht verfügbar


![SPLIT_BYTE_INTO_QUARTERS](./SPLIT_BYTE_INTO_QUARTERS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_BYTE_INTO_QUARTERS` dient der Aufteilung eines eingehenden Byte-Datenwerts in vier separate Quarter-Ausgänge. Er realisiert eine logische Zerlegung eines Bytes (8 Bit) in vier 2‑Bit‑Gruppen, die über unidirektionale Adapter nach außen geführt werden. Die interne Implementierung nutzt eine Kombination aus Flipflops und einer rekursiven Instanz des gleichen Bausteins, um die Aufteilung synchron und datengetrieben zu steuern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Nicht vorhanden. Der Baustein besitzt keine eigenständigen Ereignis-Eingänge; die Steuerung erfolgt ausschließlich über die Adapter‑Schnittstellen.

### **Ereignis-Ausgänge**
Nicht vorhanden.

### **Daten-Eingänge**
Nicht vorhanden.

### **Daten-Ausgänge**
Nicht vorhanden.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AB` | Byte‑Eingang, der die aufzuteilenden Daten liefert. |
| **Plug** (Ausgang) | `QUARTER_BYTE_00` | `adapter::types::unidirectional::AQ` | Ausgang für das erste Quarter (niederwertigste 2 Bit). |
| **Plug** (Ausgang) | `QUARTER_BYTE_01` | `adapter::types::unidirectional::AQ` | Ausgang für das zweite Quarter (Bit 2‑3). |
| **Plug** (Ausgang) | `QUARTER_BYTE_02` | `adapter::types::unidirectional::AQ` | Ausgang für das dritte Quarter (Bit 4‑5). |
| **Plug** (Ausgang) | `QUARTER_BYTE_03` | `adapter::types::unidirectional::AQ` | Ausgang für das vierte Quarter (höchstwertigste 2 Bit). |

## Funktionsweise
Der Baustein arbeitet als **Composite‑FB** mit einem inneren Netzwerk. Sobald der Socket `IN` ein Ereignis (über `E1`) und die zugehörigen Daten empfängt, werden diese an eine interne Instanz des gleichen Bausteins (`SPLIT_BYTE_INTO_QUARTERS`) weitergeleitet. Deren Ausgänge (ebenfalls vier Quarter‑Adapter) werden in vier parallel geschalteten **E_D_FF_ANY‑Flipflops** zwischengespeichert. Die Flipflops übernehmen die Daten mit dem durch die interne `CNF`‑Eventkette getakteten Takt und geben sie synchron an die äußeren Plug‑Adapter (`QUARTER_BYTE_00` … `QUARTER_BYTE_03`) weiter. Die genaue Abbildung der Bits auf die Quarters erfolgt implizit über die interne Verkabelung; es wird angenommen, dass das Byte in vier aufeinanderfolgende 2‑Bit‑Gruppen (von LSB nach MSB) unterteilt wird.

## Technische Besonderheiten
- **Rekursive Typverwendung**: Die interne Netztopologie enthält eine weitere Instanz des Bausteins `SPLIT_BYTE_INTO_QUARTERS`, wodurch eine mehrstufige oder iterative Zerlegung ermöglicht wird. Die konkrete Tiefe bleibt jedoch durch die feste Verdrahtung auf eine Stufe beschränkt.
- **Adapter basiertes Design**: Statt herkömmlicher Datenports werden ausschließlich unidirektionale Adapter eingesetzt, die sowohl Ereignis‑ als auch Datenkanäle kapseln. Dies fördert lose Kopplung und Wiederverwendbarkeit.
- **Synchronisation durch Flipflops**: Die vier Ausgangs‑Flipflops gewährleisten, dass alle Quarter gleichzeitig mit einem gemeinsamen Takt aktualisiert werden, sobald die interne Aufteilung abgeschlossen ist.

## Zustandsübersicht
Der Baustein besitzt **keinen expliziten Zustandsautomaten** (ECC). Seine Funktionsweise ergibt sich allein aus der Daten‑ und Ereignisverdrahtung der inneren Komponenten. Das Systemverhalten ist daher rein kombinatorisch mit einer Taktflanke der Flipflops.

## Anwendungsszenarien
- **Parallelisierung von Byte‑Daten**: Zerlegung eines empfangenen Bytes in vier unabhängige 2‑Bit‑Kanäle, z. B. zur Ansteuerung von vier parallelen Ausgabegeräten oder zur verteilten Verarbeitung.
- **Serielle‑ zu Parallel‑Wandlung**: Umwandlung eines seriellen Byte‑Datenstroms in vier parallele Quarter‑Signale.
- **Protokoll‑Aufbereitung**: Extrahieren von Teilinformationen aus einem Byte, wenn jedes Quarter eine separate Bedeutung trägt (z. B. Status‑Flags, Konfigurationswerte).

## Vergleich mit ähnlichen Bausteinen
- **SPLIT_WORD_INTO_HALF_WORDS**: Analoger Baustein zur Aufteilung eines 16‑Bit‑Worts in zwei 8‑Bit‑Hälften, arbeitet meist mit direkten Datenports.
- **EXTRACT_BITS_4TO1**: Standard‑Splitting‑Bausteine arbeiten oft bitweise oder mit wählbaren Indexbereichen. Der vorliegende Baustein ist speziell auf die feste Quarter‑Aufteilung eines Bytes optimiert und nutzt Adapter anstelle von einfachen Daten‑Ein‑/Ausgängen.
- **MUX/DEMUX‑Bausteine**: Multiplexer und Demultiplexer bieten generische Aufteilung, benötigen jedoch zusätzliche Steuerleitungen. Der `SPLIT_BYTE_INTO_QUARTERS` ist spezialisierter und einfacher konfigurierbar.

## Fazit
Der Funktionsblock `SPLIT_BYTE_INTO_QUARTERS` stellt eine kompakte, adapterbasierte Lösung zur Zerlegung eines Bytes in vier Quarter‑Ausgänge dar. Durch die Kombination aus rekursiver Struktur und Flipflop‑Synchronisation wird eine zuverlässige, parallele Datenbereitstellung erreicht. Er eignet sich für Anwendungen, die eine feste Aufteilung eines 8‑Bit‑Werts in vier 2‑Bit‑Einheiten erfordern, und bietet durch die einheitliche Adapter‑Schnittstelle eine gute Integrationsfähigkeit in modulare 4diac‑Projekte.