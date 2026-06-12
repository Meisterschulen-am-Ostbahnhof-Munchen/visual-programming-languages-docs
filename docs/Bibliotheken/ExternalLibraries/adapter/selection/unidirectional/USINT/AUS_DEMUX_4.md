# AUS_DEMUX_4


![AUS_DEMUX_4](./AUS_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AUS_DEMUX_4** realisiert einen Demultiplexer für den Adaptertyp `AUS`. Er leitet den eingehenden Wert vom Adapter `IN` auf einen von vier Ausgangsadaptern (`OUT1`–`OUT4`) weiter. Die Auswahl des Zielausgangs erfolgt über den Index `K`, der bei einem Ereignis am Eingang `REQ` ausgewertet wird. Der Baustein ist für die Verwendung in IEC 61499‑Anwendungen konzipiert und eignet sich besonders zur dynamischen Verteilung eines Datenstroms auf mehrere Verbraucher.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|-------------|
| `REQ` | Startet die Demultiplex‑Operation. Der Index `K` wird eingelesen und der Wert des `IN`‑Adapters auf den entsprechenden Ausgangsadapter weitergeleitet. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|-------------|
| `CNF` | Bestätigung, dass der Demultiplexvorgang abgeschlossen ist und der gewählte Ausgang den aktuellen Wert des `IN`‑Adapters trägt. |

### **Daten-Eingänge**
| Variable | Typ   | Beschreibung |
|----------|-------|-------------|
| `K`      | UINT  | Index des gewünschten Ausgangs (1 = OUT1, 2 = OUT2, 3 = OUT3, 4 = OUT4). Werte außerhalb dieses Bereichs werden ignoriert oder führen zu keinem Ausgangswechsel (implementierungsabhängig). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Werte werden über die Adapterausgänge bereitgestellt.

### **Adapter**
| Adapter  | Richtung | Typ   | Beschreibung |
|----------|----------|-------|-------------|
| `IN`     | Eingang  | `adapter::types::unidirectional::AUS` | Wert, der demultiplext werden soll. |
| `OUT1`   | Ausgang  | `adapter::types::unidirectional::AUS` | Erster Ausgangskanal. |
| `OUT2`   | Ausgang  | `adapter::types::unidirectional::AUS` | Zweiter Ausgangskanal. |
| `OUT3`   | Ausgang  | `adapter::types::unidirectional::AUS` | Dritter Ausgangskanal. |
| `OUT4`   | Ausgang  | `adapter::types::unidirectional::AUS` | Vierter Ausgangskanal. |

Alle Adapter sind vom unidirektionalen Typ `AUS` und übertragen Daten in die angegebene Richtung.

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Im Ruhezustand wartet er auf ein `REQ`‑Ereignis.
2. Beim Eintreffen von `REQ` wird der Wert des Daten‑Eingangs `K` ausgelesen.
3. Der aktuelle Wert des `IN`‑Adapters wird auf den durch `K` bestimmten Ausgangsadapter kopiert. Die übrigen drei Ausgänge behalten ihren bisherigen Zustand.
4. Anschließend wird das Ereignis `CNF` gesendet, um den Abschluss der Operation zu signalisieren.

Die verwendeten Adapter vom Typ `AUS` sind unidirektional, d. h. Daten fließen nur von der Quelle zum Ziel. Typischerweise enthält ein `AUS`‑Adapter eine oder mehrere Daten‑ und/oder Ereignis‑Schnittstellen – die genaue Struktur ist in der jeweiligen Adapterdefinition festgelegt.

## Technische Besonderheiten
- **Generischer Ursprung**: Der FB basiert auf dem generischen Typ `GEN_AUS_DEMUX`. Für die konkrete Instanzierung mit vier Ausgängen wurde die Ausprägung `AUS_DEMUX_4` erzeugt. Dadurch kann der Demultiplexer leicht auf andere Kanalzahlen skaliert werden (z. B. `AUS_DEMUX_2`, `AUS_DEMUX_8`).
- **Indexbereich**: `K` wird als vorzeichenloser 16‑Bit‑Wert (UINT) interpretiert. Gültige Werte sind 1 bis 4. Werte außerhalb dieses Bereichs sollten vermieden werden; das Verhalten ist nicht spezifiziert.
- **Keine Zwischenspeicherung**: Der Demultiplexer arbeitet ohne interne Zustandsspeicher – der `IN`‑Wert wird zum Zeitpunkt des `REQ`‑Ereignisses direkt durchgereicht.
- **Adapter‑Typ `AUS`**: Die Schnittstelle des Bausteins wird über Adapter definiert. Dies fördert die Wiederverwendbarkeit und kapselt komplexe Datentypen.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine im Sinne eines ECC (Execution Control Chart). Dennoch lassen sich zwei Betriebszustände identifizieren:

| Zustand | Beschreibung |
|---------|-------------|
| **IDLE** | Warten auf ein `REQ`‑Ereignis. Keine Demultiplex‑Operation aktiv. |
| **BUSY** | Bearbeitung des aktuellen `REQ`‑Ereignisses. Der `IN`‑Adapter wird ausgelesen, der passende Ausgangsadapter gesetzt und `CNF` erzeugt. Der Zustand wechselt sofort zurück zu IDLE. |

Die Umschaltung erfolgt innerhalb desselben Zyklus; der Baustein ist nicht blockierend.

## Anwendungsszenarien
- **Steuerungsanwendungen**: Verteilung eines Sensorsignals (z. B. Temperatur, Druck) an mehrere nachgelagerte Regelmodule, je nach aktueller Betriebsart.
- **Routing von Datenströmen**: In einer modularen Maschinensteuerung kann ein gemeinsamer Datenkanal auf verschiedene Aktuatoren umgeschaltet werden.
- **Testumgebungen**: Gezieltes Einschleusen von Testwerten in unterschiedliche Verarbeitungspfade.
- **Multiplexing‑Gegenstück**: Zusammen mit einem Multiplexer (`AUS_MUX_4`) lassen sich flexible Umschaltnetzwerke aufbauen.

## Vergleich mit ähnlichen Bausteinen
- **AUS_SWITCH**: Ein Wechselschalter für zwei Kanäle. `AUS_DEMUX_4` erweitert diese Idee auf vier Kanäle.
- **Standard‑Demultiplexer**: In gängigen FB‑Bibliotheken existieren oft Demultiplexer mit fester Kanalzahl (z. B. DEMUX_4). Der hier beschriebene Baustein nutzt jedoch Adaptertypen und ist auf den spezifischen Datentyp `AUS` zugeschnitten.
- **Generische Varianten**: Der generische Ansatz (`GEN_AUS_DEMUX`) erlaubt die Erzeugung von Bausteinen mit beliebiger Kanalzahl, was die Wiederverwendbarkeit erhöht.

## Fazit
`AUS_DEMUX_4` ist ein spezialisierter Demultiplexer für den IEC‑61499‑Adaptertyp `AUS`. Er ermöglicht die flexible, ereignisgesteuerte Verteilung eines Eingangssignals auf vier Ausgangskanäle. Die Verwendung von Adaptern macht den Baustein kompatibel mit anderen Komponenten desselben Typs und fördert eine saubere, modulare Systemarchitektur. Durch die generische Basis kann er leicht auf andere Kanalzahlen angepasst werden.