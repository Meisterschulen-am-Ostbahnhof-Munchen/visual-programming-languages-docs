# AX_AUDI_SEL_AUDI


![AX_AUDI_SEL_AUDI](./AX_AUDI_SEL_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_AUDI_SEL_AUDI` realisiert eine binäre Auswahl (binary selection) zwischen zwei Eingangswerten. Er wird über zwei Ereignisse gesteuert, die jeweils einen der beiden Dateneingänge übernehmen können. Die eigentliche Auswahl erfolgt über einen angeschlossenen **Adapter G** (Typ `AX`), der den Selektionswert liefert. Das ausgewählte Ergebnis wird über den **Adapter OUT** (Typ `AUDI`) an die Umgebung weitergegeben. Der Baustein kapselt die Logik des IEC‑61131‑Standardbausteins `F_SEL` in einer adapterbasierten Form.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `EI0` | Event | Setzt den Wert von `IN0` (übernimmt ihn in die interne Verarbeitung) |
| `EI1` | Event | Setzt den Wert von `IN1` (übernimmt ihn in die interne Verarbeitung) |

### **Ereignis-Ausgänge**
Die Ereignisausgabe erfolgt ausschließlich über den Adapter `OUT`. Sobald die Auswahl abgeschlossen ist, wird das Ereignis `E1` am Adapter `OUT` gesendet.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN0` | UDINT | Erster auswählbarer Wert |
| `IN1` | UDINT | Zweiter auswählbarer Wert |

### **Daten-Ausgänge**
Der Ausgangswert wird ausschließlich über den Adapter `OUT` als Datenelement `D1` bereitgestellt.

### **Adapter**

| Name | Typ | Rolle |
|------|-----|-------|
| `G` | `adapter::types::unidirectional::AX` | Liefert den Selektionssteuerwert (Ereignis `E1` + Daten `D1`) |
| `OUT` | `adapter::types::unidirectional::AUDI` | Gibt das ausgewählte Ergebnis als Ereignis `E1` und Daten `D1` aus |

## Funktionsweise
1. **Eingangswerte bereitstellen** – Über die Ereigniseingänge `EI0` bzw. `EI1` werden die aktuellen Werte von `IN0` bzw. `IN1` in den Baustein übernommen.  
2. **Selektion auslösen** – Der externe Adapter `G` sendet über sein Ereignis `E1` ein Auswahlsignal.  
3. **Interne Selektion** – Das Ereignis `E1` sowie der Dateneingang `G.D1` (als Auswahlkriterium) werden an den internen Funktionsblock `F_SEL` weitergeleitet. `F_SEL` wählt nach IEC‑61131‑Logik: Wenn `G.D1` = FALSE (0), wird `IN0` ausgegeben; wenn `G.D1` = TRUE (ungleich 0), wird `IN1` ausgegeben.  
4. **Ergebnis ausgeben** – Das bestätigende Ereignis (`CNF`) von `F_SEL` wird an den Adapter `OUT.E1` weitergegeben. Gleichzeitig wird der Ausgangswert `F_SEL.OUT` an `OUT.D1` übertragen.

## Technische Besonderheiten
- Die Datenbreite der Ein- und Ausgänge ist **UDINT** (unsigned double integer, 32 Bit).  
- Die Auswahl erfolgt **ereignisgesteuert** – erst durch ein Ereignis am Adapter `G` wird die Selektion ausgelöst.  
- Der Baustein puffert die Eingangswerte nicht automatisch; er übernimmt sie nur bei den entsprechenden Ereignissen (`EI0`, `EI1`).  
- Die Adapter basieren auf dem **unidirektionalen** Protokoll (je eine Daten‑ und Ereignisverbindung).  
- Die eigentliche Selektionslogik wird durch den standardisierten IEC‑Baustein `F_SEL` realisiert, was eine hohe Kompatibilität und Vorhersagbarkeit sicherstellt.

## Zustandsübersicht
Der Funktionsblock besitzt keinen eigenen Zustandsautomaten. Sein Verhalten ergibt sich vollständig aus dem internen Sub‑Baustein `F_SEL`, der die IEC‑Normlogik abbildet.  
- **Init** – Nach dem Einschalten sind keine Werte übernommen; `OUT.D1` enthält keinen definierten Wert, bis ein Selektionszyklus durchlaufen wurde.  
- **Arbeitsphase** – Bei Auftreten von `EI0`/`EI1` werden die Eingangswerte gesetzt, bei `G.E1` wird die Auswahl durchgeführt und das Ergebnis über `OUT.E1` signalisiert.  
Es gibt keine weiteren internen Zustände.

## Anwendungsszenarien
- **Adapter‑orientierte Signalumschaltung** – In einem modularen Automatisierungssystem kann `AX_AUDI_SEL_AUDI` verwendet werden, um zwischen zwei Sensorwerten oder Sollwerten umzuschalten, gesteuert durch einen übergeordneten Selektor‑Adapter.  
- **Quellenauswahl in Datenpfaden** – Wenn zwei Datenquellen mit unterschiedlicher Aktualisierungsrate zur Verfügung stehen, kann dieser Baustein die jeweils aktuelle auswählen.  
- **Parametrierbare Entscheidungslogik** – Der Selektionswert (G.D1) kann aus einer externen Berechnung oder einem Zustandsautomaten stammen, wodurch eine flexible Umschaltung realisiert wird.

## Vergleich mit ähnlichen Bausteinen
- **F_SEL (direkt)** – Standardmäßig würde man `F_SEL` als FB ohne Adapter verwenden. `AX_AUDI_SEL_AUDI` kapselt ihn in eine adapterbasierte Schnittstelle, was die Anbindung an andere Adapter‑Typen (z.B. aus der `AX`‑ oder `AUDI`‑Familie) erleichtert.  
- **MUX‑Bausteine** – Klassische Multiplexer (z.B. `MUX2`) bieten eine größere Anzahl von Eingängen, während dieser Baustein auf genau zwei Eingänge und eine unidirektionale Adapterschnittstelle spezialisiert ist.  
- **Adapter‑basierte Wandler** – Andere Adapter‑Bausteine konvertieren oder skalieren Werte; dieser Baustein führt keine arithmetische Operation aus, sondern wählt nur aus.

## Fazit
`AX_AUDI_SEL_AUDI` ist ein kompakter, ereignisgesteuerter Selektionsbaustein, der die IEC‑Selektionslogik in eine adapterbasierte Umgebung einbettet. Durch die klare Trennung von Dateneingängen, Steueradapter und Ausgabeadapter eignet er sich besonders für modulare, wiederverwendbare Automatisierungslösungen im Umfeld der 4diac‑IDE. Die Beschränkung auf zwei Eingänge und die Verwendung von Standard‑Typen garantieren eine einfache Integration und vorhersagbares Laufzeitverhalten.