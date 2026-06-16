# AR_DEMUX_4


![AR_DEMUX_4](./AR_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AR_DEMUX_4` ist ein generischer Demultiplexer für den AR‑Adaptertyp. Er nimmt über einen einzigen AR‑Adapter‑Socket (Eingang) einen Datenwert entgegen und leitet diesen auf einen von vier AR‑Adapter‑Plugs (Ausgänge) weiter. Die Auswahl des Zielausgangs erfolgt über den Index K, der beim Eintreffen des Ereignisses `REQ` ausgewertet wird. Der Baustein wird typischerweise in der Automatisierungstechnik, insbesondere in der Landwirtschaft, eingesetzt, um einen Datenstrom an verschiedene nachgelagerte Verbraucher zu verteilen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Set Index K und löse Demultiplexing aus |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung der Verarbeitung von K |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K | UINT | Index des gewünschten Ausgangskanals (1..4) |

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Name | Richtung | Typ | Kommentar |
|------|----------|-----|-----------|
| IN | Socket (Eingang) | `adapter::types::unidirectional::AR` | Eingangswert, der demultiplext werden soll |
| OUT1 | Plug (Ausgang) | `adapter::types::unidirectional::AR` | Ausgangskanal 1 |
| OUT2 | Plug (Ausgang) | `adapter::types::unidirectional::AR` | Ausgangskanal 2 |
| OUT3 | Plug (Ausgang) | `adapter::types::unidirectional::AR` | Ausgangskanal 3 |
| OUT4 | Plug (Ausgang) | `adapter::types::unidirectional::AR` | Ausgangskanal 4 |

## Funktionsweise
Ein Demultiplexer verteilt den an `IN` anliegenden AR‑Adapterwert auf einen der vier Ausgangsadapter `OUT1` … `OUT4`. Die Zuordnung erfolgt über den Daten‑Eingang `K` (Index). Beim Eintreffen des Ereignisses `REQ` wird der aktuelle Wert von `K` ausgelesen, und der momentane Zustand des Eingangs‑Adapters `IN` wird auf den durch `K` bezeichneten Ausgangs‑Adapter kopiert. Die übrigen drei Ausgänge bleiben unverändert (ihr Wert wird nicht zurückgesetzt). Nach erfolgreicher Weiterleitung wird das Ereignis `CNF` gesendet. Gültige Werte für `K` sind **1 bis 4**. Werte außerhalb dieses Bereichs oder nicht definiertes Verhalten werden im Standard‑FB nicht spezifiziert; in der Praxis sollte die Anwendung sicherstellen, dass nur gültige Indizes übergeben werden.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AR_DEMUX`) deklariert, sodass er für verschiedene AR‑Adapter‑Varianten eingesetzt werden kann.
- **Unidirektionale Adapter**: Sämtliche Adapter sind vom Typ `adapter::types::unidirectional::AR`. Dies bedeutet, dass die Daten nur in eine Richtung fließen (vom Eingang zu den Ausgängen).
- **Lizenz**: Der Baustein unterliegt der Eclipse Public License 2.0 (EPL‑2.0) und wurde von der HR Agrartechnik GmbH erstellt.
- **Kein impliziter Zustandsautomat**: Der FB besitzt kein ECC (Execution Control Chart) – die Logik ist ereignisgesteuert und rein funktional.

## Zustandsübersicht
Ein expliziter Zustandsautomat ist nicht definiert. Der Baustein arbeitet zustandslos: Bei jedem `REQ`‑Ereignis wird die Weiterleitung einmalig ausgeführt. Es gibt keine Initialisierung oder spezielle interne Zustände.

## Anwendungsszenarien
- **Datenverteilung in landwirtschaftlichen Maschinen**: Z.B. Verteilen von Sensordaten (z.B. Felddaten, CAN‑Nachrichten) an verschiedene Steuereinheiten.
- **Selektive Aktivierung von Aktoren**: Ein zentraler AR‑Datenstrom kann wahlweise an vier unterschiedliche Aktor‑Anschlüsse weitergeleitet werden.
- **Umschaltung von Signalquellen** (in Kombination mit einem Multiplexer): Kann zur Konfiguration von Bus‑ oder Kommunikationspfaden verwendet werden.

## Vergleich mit ähnlichen Bausteinen
- **`AR_MUX_4` (Multiplexer)**: Nimmt mehrere AR‑Eingänge entgegen und gibt einen ausgewählten aus – das Gegenstück zum `DEMUX`.
- **`DEMUX` für einfache Datentypen (z.B. `BOOL_DEMUX_4`)**: Funktionsprinzip identisch, aber statt AR‑Adaptern werden elementare Datentypen verwendet.
- **`AR_DEMUX_n` mit variabler Kanalzahl**: `AR_DEMUX_4` ist auf vier Kanäle festgelegt; andere Varianten (z.B. `AR_DEMUX_2`, `AR_DEMUX_8`) existieren für abweichende Anzahlen.

## Fazit
Der `AR_DEMUX_4` ist ein spezialisierter, aber dennoch generisch nutzbarer Demultiplexer für den AR‑Adaptertyp. Er eignet sich hervorragend zur einfachen und effizienten Verteilung eines Datenstroms auf bis zu vier Ausgänge. Dank des klaren ereignisgesteuerten Interfaces und der Trennung von Index und Daten lässt er sich gut in industrielle Steuerungsarchitekturen integrieren.