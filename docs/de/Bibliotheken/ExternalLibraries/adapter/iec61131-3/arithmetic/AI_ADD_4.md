# AI_ADD_4

```
        +-------------------------+
   IN1 =| [Socket]                |
   IN2 =| [Socket]         [Plug] |= OUT
   IN3 =| [Socket]                |
   IN4 =| [Socket]                |
        +-------------------------+
```


![AI_ADD_4](./AI_ADD_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AI_ADD_4` ist ein generischer Arithmetik-Baustein für die 4diac-IDE, der zur Addition von vier analogen bzw. numerischen Werten dient. Die Besonderheit dieses Bausteins liegt in der Verwendung von unidirektionalen Adaptern des Typs `AI` (Analog Input/Arithmetic Input) anstelle von klassischen diskreten Daten- und Ereigniseingängen. Dies ermöglicht eine saubere, modulare und übersichtliche Strukturierung von Signalflüssen in IEC 61499 Anwendungen.

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen ereignis- oder datenbasierten Ein- und Ausgänge auf der obersten Ebene. Die gesamte Kommunikation wird über Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung ist in den Adaptern gekapselt.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung ist in den Adaptern gekapselt.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::AI`): Erster Summand für die Additionsoperation.
*   **IN2** (Typ: `adapter::types::unidirectional::AI`): Zweiter Summand für die Additionsoperation.
*   **IN3** (Typ: `adapter::types::unidirectional::AI`): Dritter Summand für die Additionsoperation.
*   **IN4** (Typ: `adapter::types::unidirectional::AI`): Vierter Summand für die Additionsoperation.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::AI`): Ausgangsadapter, der das Ergebnis der Addition (`IN1 + IN2 + IN3 + IN4`) bereitstellt.

## Funktionsweise

Sobald an einem der Eingangs-Adapter (`IN1` bis `IN4`) ein neues Ereignis signalisiert, dass sich ein Wert geändert hat, führt der Baustein intern die Addition durch:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

Das Ergebnis wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben, und das entsprechende Aktualisierungsereignis des Ausgangs-Adapters wird ausgelöst. Da es sich um einen generischen Baustein (`GEN_AI_ADD`) handelt, richtet sich der tatsächliche Datentyp (z. B. `REAL`, `INT`, `LREAL`) nach der konkreten Implementierung und Instanziierung des verwendeten Adaptertyps.

## Technische Besonderheiten

*   **Generisches Design:** Der Baustein nutzt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AI_ADD'`. Er ist dadurch hochflexibel und kann auf unterschiedliche numerische Datentypen angewendet werden, sofern die verwendeten Adapter dies unterstützen.
*   **Unidirektionale Adapter:** Durch die Verwendung von `unidirectional::AI`-Adaptern wird der Verdrahtungsaufwand im Funktionsplan drastisch reduziert, da Daten und Trigger-Ereignisse in einer einzigen Verbindung gebündelt sind.

## Zustandsübersicht

Der Baustein verhält sich rein reaktiv (ereignisgesteuert):

1.  **Wartezustand (Idle):** Der Baustein wartet auf ein Aktualisierungsereignis an einem der Sockets (`IN1` bis `IN4`).
2.  **Berechnung:** Bei Eintreffen eines Ereignisses werden die aktuellen Werte aller vier Eingänge gelesen und addiert.
3.  **Ausgabe:** Der berechnete Wert wird an den Plug `OUT` geschrieben und das dortige Ausgangsereignis getriggert. Der Baustein kehrt sofort in den Wartezustand zurück.

## Anwendungsszenarien

*   **Messwert-Agggregation:** Summierung von Strömen, Leistungen oder Durchflussmengen aus vier verschiedenen Quellen oder Sensoren.
*   **Mittelwertvorbereitung:** Zusammenführung von vier analogen Messwerten zur anschließenden Division (z. B. zur gleitenden Mittelwertbildung oder Redundanzprüfung).
*   **Sollwert-Offset-Berechnung:** Addition von Basis-Sollwerten, Korrekturwerten und Benutzer-Offsets in verfahrenstechnischen Anlagen.

## Vergleich mit ähnlichen Bausteinen

| Feature / Baustein | `AI_ADD_4` | Standard `ADD` (IEC 61131-3) |
| :--- | :--- | :--- |
| **Schnittstellentyp** | Adapter-basiert (`AI`) | Standard-Daten- und Ereignispins |
| **Anzahl Eingänge** | Fest (4) | Variabel / Fest (meist 2) |
| **Verdrahtungsaufwand** | Sehr gering (nur 5 Verbindungen) | Hoch (separate Event- und Datenlinien) |
| **Typisierung** | Generisch über Adapter | Explizit über FB-Typisierung (z.B. `ADD_REAL`) |

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AI_ADD_4` ist ein hocheffizienter und moderner Funktionsbaustein, der die Vorteile der adapterbasierten Kopplung in IEC 61499 voll ausschöpft. Er eignet sich hervorragend für komplexe Steuerungsarchitekturen, bei denen Übersichtlichkeit im Applikationsdiagramm und eine klare Signalstruktur im Vordergrund stehen.