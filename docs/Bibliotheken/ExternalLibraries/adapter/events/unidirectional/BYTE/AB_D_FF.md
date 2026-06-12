# AB_D_FF

Kein Bild vorhanden.


![AB_D_FF](./AB_D_FF.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AB_D_FF** realisiert ein asynchrones Daten-Latch (D-Flipflop) auf Basis eines Adapter-Konzepts nach IEC 61499. Er übernimmt einen Datenwert über den Eingangsadapter **I**, sobald ein Ereignis anliegt, und gibt diesen Wert über den Ausgangsadapter **Q** aus. Der interne Zustand des Flipflops wird dabei durch einen standardisierten `E_D_FF_ANY`-Baustein abgebildet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **I.E1** (via Adapter `I`): Startet das Übernehmen des Datenwerts.

### **Ereignis-Ausgänge**
- **Q.E1** (via Adapter `Q`): Signalisiert die Ausgabe des gelatchten Datenwerts.

### **Daten-Eingänge**
- **I.D1** (via Adapter `I`): Der zu latchnde Datenwert (Typ beliebig, abhängig vom verwendeten Adaptertyp `adapter::types::unidirectional::AB`).

### **Daten-Ausgänge**
- **Q.D1** (via Adapter `Q`): Der gelatchte und ausgegebene Datenwert.

### **Adapter**
- **I** (Socket): Eingangsadapter vom Typ `adapter::types::unidirectional::AB` – nimmt den zu latchnden Wert und das Steuerereignis entgegen.
- **Q** (Plug): Ausgangsadapter vom selben Typ – gibt den gespeicherten Wert und das zugehörige Ereignis aus.

## Funktionsweise

Der Funktionsblock arbeitet ereignisgesteuert:
1. Sobald am Eingangsadapter **I.E1** ein Ereignis eintrifft, wird der aktuelle Wert am Daten-Eingang **I.D1** in das interne D-Flipflop (`E_D_FF_ANY`) übernommen.
2. Anschließend wird der gespeicherte Wert an **Q.D1** ausgegeben und gleichzeitig ein Ereignis am Ausgang **Q.E1** erzeugt.

Somit verhält sich der Baustein wie ein klassischer flankengesteuerter D-Latch, bei dem die Übernahme und Ausgabe synchron zum Eingangsereignis erfolgen.

## Technische Besonderheiten

- **Adapter-Schnittstelle**: Der Baustein verwendet ausschließlich Adapter (`adapter::types::unidirectional::AB`) für die Ein- und Ausgabe, was eine flexible Typisierung und lose Kopplung mit anderen Komponenten ermöglicht.
- **Interne Implementierung**: Der latchende Kern wird durch den standardisierten FB `E_D_FF_ANY` aus der IEC-61499-Bibliothek `iec61499::events` realisiert. Dieser speichert den Datenwert und erzeugt das Ausgangsereignis.
- **Ereignis- und Datenpfad** sind strikt getrennt: Das Ereignis löst die Datenübernahme aus, Daten fließen unabhängig.

## Zustandsübersicht

Der Funktionsblock besitzt keinen expliziten internen Zustandsautomaten, sondern vertraut auf den impliziten Zustand des eingebetteten `E_D_FF_ANY`:
- **Idle**: Warten auf ein Ereignis an `I.E1`.
- **Latchen**: Nach Empfang des Ereignisses wird der Datenwert übernommen und ausgegeben.
- Der interne gemerkte Wert bleibt bis zum nächsten Ereignis erhalten.

## Anwendungsszenarien

- **Datensynchronisation**: Sichere Übernahme von Messwerten oder Steuerdaten zu definierten Zeitpunkten (z. B. Taktimpuls).
- **Pufferung**: Zwischenspeichern von Werten in Ablaufsteuerungen zwischen verschiedenen Funktionsbausteinen.
- **Registerbildung**: Aufbau von Schieberegistern oder Speicherzellen in modularen Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung |
|----------|--------------|
| **AB_SR_FF** | Set-Reset-Flipflop, speichert zwei Zustände (Set/Reset) ohne Datenwert. |
| **AB_T_FF** | Toggle-Flipflop, wechselt den Ausgangszustand bei jedem Ereignis. |
| **E_D_FF** | Standard-D-Flipflop ohne Adapter-Schnittstelle, direkte Ereignis- und Daten-Pins. |

Der **AB_D_FF** bietet durch die Adapter-Schnittstelle eine typsichere und wiederverwendbare Kapselung, während vergleichbare Bausteine oft auf feste Datentypen angewiesen sind.

## Fazit

Der **AB_D_FF** ist ein kompakter und flexibler D-Latch-Baustein, der die Vorteile der IEC-61499-Architektur nutzt. Durch die Adapter-Schnittstelle kann er in unterschiedlichsten Kontexten eingesetzt werden, ohne sich auf einen bestimmten Datentyp festlegen zu müssen. Zusammen mit dem internen Standard-Flipflop gewährleistet er eine zuverlässige und ereignisgesteuerte Datenhaltung.