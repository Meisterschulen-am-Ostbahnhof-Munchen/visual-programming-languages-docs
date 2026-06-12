# AE_SWITCH


![AE_SWITCH](./AE_SWITCH.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_SWITCH** dient als Demultiplexer für Ereignisse. Er leitet ein eingehendes Ereignis je nach dem Wert eines booleschen Eingangs `G` an einen von zwei unidirektionalen Event-Adapter-Ausgängen weiter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **EIG** (Event): Setzt den Wert von `G`. Wird dieses Ereignis ausgelöst, wird der zugehörige Daten-Eingang `G` übernommen – es erfolgt keine Weiterleitung an die Ausgänge.

### **Ereignis-Ausgänge**

- Keine eigenständigen Ereignis-Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die Adapter `EO0` und `EO1`.

### **Daten-Eingänge**

| Name | Typ   | Kommentar                                      |
|------|-------|------------------------------------------------|
| `G`  | BOOL  | Schalter: 0 → Ausgabe über `EO0`, 1 → Ausgabe über `EO1` |

### **Daten-Ausgänge**

- Keine Datenausgänge.

### **Adapter**

| Richtung  | Name  | Typ (unidirektional)                        | Kommentar                                      |
|-----------|-------|---------------------------------------------|------------------------------------------------|
| **Socket** (Eingang) | `EI`  | `adapter::types::unidirectional::AE`        | Ereignis-Eingang, der umgeschaltet wird.       |
| **Plug** (Ausgang)   | `EO0` | `adapter::types::unidirectional::AE`        | Ereignis-Ausgang, aktiv bei `G = 0`            |
| **Plug** (Ausgang)   | `EO1` | `adapter::types::unidirectional::AE`        | Ereignis-Ausgang, aktiv bei `G = 1`            |

## Funktionsweise

Der Baustein befindet sich initial im Zustand **START**.

1. **Setzen des Schalters**: Ein Ereignis an `EIG` übernimmt den aktuellen Wert von `G`. Der Baustein bleibt danach im Zustand **START**.
2. **Weiterleiten des Eingangsereignisses**: Trifft ein Ereignis über den Adapter-Eingang `EI` ein, wird der Wert von `G` ausgewertet:
   - Ist `G = 0` → Zustandswechsel nach **G0**: Der Adapter-Ausgang `EO0` wird mit seinem Ereignis `E1` ausgelöst.
   - Ist `G = 1` → Zustandswechsel nach **G1**: Der Adapter-Ausgang `EO1` wird mit seinem Ereignis `E1` ausgelöst.
3. Nach Auslösen des jeweiligen Ausgangs kehrt der Baustein automatisch in den Zustand **START** zurück.

## Technische Besonderheiten

- Die Ereignisweiterleitung erfolgt ausschließlich über **unidirektionale Adapter** vom Typ `AE`. Dadurch wird eine saubere Trennung von Ereignisquellen und -senken erreicht.
- Der Baustein realisiert ein **Demultiplexing** (1-zu-2) auf Ereignisebene: Ein eingehendes Ereignis wird je nach boolescher Bedingung an einen von zwei Ausgängen geroutet.
- Der Setz-Eingang `EIG` erlaubt es, den Schaltwert unabhängig von einem anstehenden Ereignis am Eingang `EI` zu ändern.

## Zustandsübersicht

| Zustand | Beschreibung                                                | Aktion bei Eintritt |
|---------|-------------------------------------------------------------|---------------------|
| START   | Warten auf ein Ereignis an `EI` oder `EIG`                  | –                   |
| G0      | Ereignis an `EI` mit `G = 0` – leite an `EO0` weiter       | `EO0.E1`            |
| G1      | Ereignis an `EI` mit `G = 1` – leite an `EO1` weiter       | `EO1.E1`            |

**Transitionen:**

- START → G0 : `EI.E1[NOT G]`
- START → G1 : `EI.E1[G]`
- G0 → START : `1` (sofort)
- G1 → START : `1` (sofort)
- START → START : `EIG` (nur Setzen von G, keine Weiterleitung)

## Anwendungsszenarien

- **Ereignis-Routing** in Automatisierungssystemen, bei dem ein zentraler Auslöser (z. B. ein Sensorereignis) je nach Betriebsmodus unterschiedliche Aktoren ansteuert.
- **Zustandsabhängige Verarbeitung**: Ein eingehendes Ereignis soll nur in einer bestimmten Betriebsart verarbeitet werden; die andere Betriebsart erhält ein separates Ereignis.
- **Test- und Diagnoseaufgaben**: Umschalten zwischen Normalbetrieb und Testmodus durch Setzen von `G`.

## Vergleich mit ähnlichen Bausteinen

- **E_SWITCH** (Standard 61499): Ähnliche Funktionalität, jedoch über reguläre Ereignisausgänge. `AE_SWITCH` verwendet Adapter, was eine bessere Kapselung und Wiederverwendbarkeit in Komponenten mit standardisierten Schnittstellen ermöglicht.
- **E_MUX** (Multiplexer): Führt mehrere Ereignisse zu einem Ausgang zusammen – gegensätzliche Richtung. `AE_SWITCH` demultiplext ein Eingangsereignis auf zwei Ausgänge.

## Fazit

Der `AE_SWITCH` bietet eine schlanke, adapterbasierte Lösung zum bedingten Weiterleiten von Ereignissen. Durch die Verwendung unidirektionaler Adapter ist er ideal für modulare und typsichere IEC‑61499-Anwendungen geeignet. Seine einfache Zustandsmaschine macht ihn effizient und leicht verständlich.