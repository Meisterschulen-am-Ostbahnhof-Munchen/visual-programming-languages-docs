# ATM_DEMUX_4


![ATM_DEMUX_4](./ATM_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ATM_DEMUX_4** ist ein generischer ATM-Demultiplexer. Er verteilt einen über einen eingehenden Adapter (Socket) ankommenden Datenstrom auf einen von vier ausgehenden Adaptern (Plugs). Die Auswahl des Ausgangskanals erfolgt über einen Index `K`, der beim Eintreffen eines Ereignisses ausgewertet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Set Index K – löst die Weiterleitung aus |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigung der erfolgten Weiterleitung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K`   | UINT | Index des gewünschten Ausgangskanals (1…4) |

### **Daten-Ausgänge**

*Keine direkten Datenausgänge* – die Ausgabe erfolgt über die Adapter.

### **Adapter**

| Rolle | Name | Typ | Kommentar |
|-------|------|-----|-----------|
| Socket | `IN`  | `adapter::types::unidirectional::ATM` | Eingangswert, der demultiplext wird |
| Plug   | `OUT1` | `adapter::types::unidirectional::ATM` | Ausgangskanal 1 |
| Plug   | `OUT2` | `adapter::types::unidirectional::ATM` | Ausgangskanal 2 |
| Plug   | `OUT3` | `adapter::types::unidirectional::ATM` | Ausgangskanal 3 |
| Plug   | `OUT4` | `adapter::types::unidirectional::ATM` | Ausgangskanal 4 |

## Funktionsweise

1. Der Baustein erwartet ein Ereignis am Eingang `REQ`. Dieses Ereignis **muss** mit dem Daten-Eingang `K` synchronisiert sein („With“-Deklaration).
2. Beim Eintreffen von `REQ` wird der aktuelle Wert von `K` ausgewertet. Gültige Werte liegen im Bereich 1…4.
3. Der über den Adapter `IN` anstehende Wert (bzw. die empfangene Nachricht) wird auf den Adapter `OUTX` weitergeleitet, wobei `X` dem Index `K` entspricht.
4. Nach erfolgreicher Weiterleitung wird das Ereignis `CNF` ausgegeben.
5. Ist der Index `K` ungültig (z. B. 0 oder >4), wird keine Weiterleitung durchgeführt – das Verhalten ist dann implementierungsabhängig (typischerweise Fehler oder Ausgabe des Ereignisses ohne Aktion).

## Technische Besonderheiten

- **Generischer Baustein** – der FB ist als generische Klasse (`GEN_ATM_DEMUX`) deklariert und kann in verschiedenen Kontexten instanziiert werden, solange die verwendeten Adapter vom Typ `ATM` sind.
- **Adapter-basierte Kopplung** – die Ein‑ und Ausgänge sind als unidirektionale Adapter realisiert, was eine lose Kopplung der Komponenten ermöglicht.
- **Ereignisgesteuerte Auswahl** – der Index `K` wird nur bei einem Ereignis ausgewertet; ein statisches Setzen des Eingangs allein löst keine Aktion aus.
- **Keine interne Pufferung** – der Baustein leitet den aktuell anliegenden Wert am `IN`-Adapter weiter. Für zeitlich versetzte Daten muss die aufrufende Applikation sorgen.

## Zustandsübersicht

Eine Zustandsmaschine ist in der bereitgestellten XML nicht explizit enthalten. Aus dem typischen Verhalten eines Demultiplexers ergibt sich folgender Ablauf:

- **IDLE** – Warten auf Ereignis `REQ`.
- **WEITERLEITEN** – Sobald `REQ` kommt und `K` im gültigen Bereich liegt, wird der Wert von `IN` auf den entsprechenden `OUTK` kopiert.
- **BESTAETIGEN** – Nach erfolgter Weiterleitung wird `CNF` gesendet, der Baustein kehrt in den IDLE-Zustand zurück.

Ein fehlerhafter Index kann in einem eigenen **FEHLER**-Zustand münden (nicht in der XML definiert, aber üblich).

## Anwendungsszenarien

- **Signalverteilung** – ein von einem Sensor kommendes Signal soll wahlweise an verschiedene Aktoren oder Steuerungen weitergeleitet werden.
- **Routing** – in einer modularen Maschinensteuerung können Datenpakete je nach Betriebszustand an unterschiedliche Module gesendet werden.
- **Test‑/Simulationsumgebungen** – Umschalten zwischen realem und simuliertem Datenstrom durch Auswahl des entsprechenden Ausgangs.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften |
|----------|---------------|
| **ATM_DEMUX_4** | Spezifisch für den Adapter-Typ `ATM`, feste Anzahl von vier Ausgängen, ereignisgesteuert. |
| **DEMUX (allgemein)** | Oft als Daten-Multiplexer/Demultiplexer mit variabler Kanalzahl und ohne Adapter-Anbindung realisiert. |
| **MUX_4** | Multiplexer (mehrere Eingänge → ein Ausgang) – inverser Betrieb. |

Der vorliegende Baustein ist auf die Verwendung in einer Umgebung zugeschnitten, in der Kommunikation über `ATM`-Adapter erfolgt, und bietet eine kompakte Lösung für 1‑aus‑4‑Selektion.

## Fazit

Der **ATM_DEMUX_4** ist ein spezialisierter, generischer Demultiplexer für Adapter-basierte Steuerungsarchitekturen. Er ermöglicht eine saubere, ereignisgesteuerte Auswahl eines von vier Ausgangskanälen und lässt sich aufgrund seiner generischen Deklaration flexibel in verschiedenen Projekten wiederverwenden. Für Anwendungen, die eine standardisierte Punkt‑zu‑Punkt‑Verteilung von ATM-Nachrichten benötigen, stellt er ein effizientes und klares Bauelement dar.