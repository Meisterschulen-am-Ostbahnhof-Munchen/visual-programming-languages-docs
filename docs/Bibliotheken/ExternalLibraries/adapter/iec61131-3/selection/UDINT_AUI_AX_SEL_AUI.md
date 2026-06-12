# UDINT_AUI_AX_SEL_AUI


![UDINT_AUI_AX_SEL_AUI](./UDINT_AUI_AX_SEL_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `UDINT_AUI_AX_SEL_AUI` realisiert eine binäre Auswahl zwischen zwei Eingangssignalen. Die Auswahl wird über einen externen Selektor (Adapter `G`) gesteuert, das ausgewählte Signal wird über einen Ausgangsadapter (`OUT`) bereitgestellt. Die Eingangswerte können separat über zwei Ereignisse aktualisiert werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Kommentar |
|----------|-----------|
| `EI0`    | Setzt den Wert von `IN0` |
| `EI1`    | Setzt den Wert von `IN1` |

### **Ereignis-Ausgänge**
Keine eigenen Ereignis-Ausgänge. Der Ausgang erfolgt über den Adapter `OUT` (siehe Abschnitt Adapter).

### **Daten-Eingänge**
| Name | Typ               | Kommentar                     |
|------|-------------------|-------------------------------|
| `IN0`| `ANY_ELEMENTARY`  | Erster auswählbarer Wert      |
| `IN1`| `UINT`            | Zweiter auswählbarer Wert     |

### **Daten-Ausgänge**
Keine eigenen Daten-Ausgänge. Der ausgewählte Wert wird über den Adapter `OUT` ausgegeben (siehe Abschnitt Adapter).

### **Adapter**
| Adapter | Typ                                  | Richtung | Kommentar                     |
|---------|--------------------------------------|----------|-------------------------------|
| `G`     | `adapter::types::unidirectional::AX` | Socket (Eingang) | Empfängt das binäre Selektorsignal und das Auslöseereignis |
| `OUT`   | `adapter::types::unidirectional::AUI`| Plug (Ausgang) | Gibt das ausgewählte Signal und ein Bestätigungsereignis aus |

**Adapter-Details:**
- **Socket `G`**: Stellt einen Ereignisausgang (`E1`) und einen Datenausgang (`D1`) bereit. `G.E1` löst die Selektion aus, `G.D1` dient als Selektor (0 → wähle `IN0`, ≠0 → wähle `IN1`).
- **Plug `OUT`**: Besitzt einen Ereigniseingang (`E1`) und einen Dateneingang (`D1`). Der FB sendet nach abgeschlossener Selektion ein Ereignis an `OUT.E1` und legt den ausgewählten Wert an `OUT.D1` an.

## Funktionsweise
1. **Wertaktualisierung** – Durch die Ereignisse `EI0` und `EI1` werden die Daten-Eingänge `IN0` bzw. `IN1` gesetzt. Ein Aufruf von `EI0` aktualisiert `IN0`, `EI1` aktualisiert `IN1`.
2. **Selektionstrigger** – Ein Ereignis am Socket `G.E1` startet die Auswahloperation. Dieses Ereignis stammt von einer externen Quelle, die den Selektionszeitpunkt vorgibt.
3. **Interne Verarbeitung** – Der interne Baustein `F_SEL` (Typ `iec61131::selection::F_SEL`) wertet das binäre Signal `G.D1` aus:
   - Ist `G.D1 = 0`, wird `IN0` ausgewählt.
   - Andernfalls wird `IN1` ausgewählt.
4. **Ausgabe** – Das Ergebnis wird an `OUT.D1` übergeben. Gleichzeitig wird ein Ereignis an `OUT.E1` gesendet, um die Verarbeitung nachgeschalteter Blöcke zu veranlassen.

## Technische Besonderheiten
- **Adapterbasierte Ein-/Ausgabe** – Die Schnittstelle zu anderen Bausteinen erfolgt ausschließlich über Adapter (`G`, `OUT`), was eine modulare und dienstorientierte Kommunikation ermöglicht.
- **Gemischte Datentypen** – Während `IN0` allgemein als `ANY_ELEMENTARY` definiert ist, ist `IN1` auf `UINT` festgelegt. Die Ausgabe folgt dem Typ des ausgewählten Signals, was eine implizite Typkonvertierung vermeidet.
- **Trennung von Wertaktualisierung und Selektion** – Das Setzen der Eingangswerte und der eigentliche Selektionsvorgang sind durch separate Ereignisse entkoppelt. Dies erlaubt eine flexible zeitliche Steuerung.

## Zustandsübersicht
Der Funktionsblock besitzt keinen expliziten Zustandsautomaten. Sein Verhalten ist ereignisgesteuert:
- Nach jedem `EI0`- oder `EI1`-Ereignis liegen die aktualisierten Werte an.
- Ein `G.E1`-Ereignis führt unmittelbar zur Auswahl und Ausgabe des Signals.
- Es existiert keine implizite Initialisierung – die Eingänge müssen vor der ersten Selektion gesetzt werden.

## Anwendungsszenarien
- **Sensorumschaltung** – Auswahl zwischen zwei analogen oder digitalen Sensoren in einer Steuerung, z. B. Umschaltung zwischen einem Nahbereichs- und einem Fernbereichssensor.
- **Parametermanagement** – Bereitstellung eines festen (UINT-)Werts oder eines dynamisch vorgegebenen Werts (ANY_ELEMENTARY) für Konfigurationszwecke.
- **Ressourcenschonende Redundanz** – In sicherheitskritischen Systemen kann zwischen einem Primär- und einem Ersatzsignal gewählt werden.

## Vergleich mit ähnlichen Bausteinen
- **Standard `F_SEL`** – Dieser einfache Selektor arbeitet mit direkten Ein-/Ausgängen ohne Adapter. `UDINT_AUI_AX_SEL_AUI` kapselt die Logik in einer adapterbasierten Schnittstelle und unterstützt die getrennte Aktualisierung der Eingänge.
- **`MUX`-Funktionen** – Ein Multiplexer wählt aus mehr als zwei Kanälen. Der hier beschriebene Baustein beschränkt sich auf zwei Eingänge, was für binäre Entscheidungen ausreicht.
- **`SWITCH`-Funktionsbausteine** – Diese besitzen oft zusätzliche Schaltzustände. Der vorgestellte Baustein ist auf eine einfache, schnelle binäre Selektion optimiert.

## Fazit
`UDINT_AUI_AX_SEL_AUI` ist ein spezialisierter Funktionsblock zur binären Auswahl zweier Signale. Die Kombination aus adapterbasierter Anbindung, getrennter Wertaktualisierung und externer Triggerung macht ihn besonders geeignet für modulare Automatisierungsprojekte, bei denen eine flexible und zeitlich entkoppelte Signalumschaltung erforderlich ist. Trotz der gemischten Datentypen bleibt die Funktionalität klar und einfach einsetzbar.