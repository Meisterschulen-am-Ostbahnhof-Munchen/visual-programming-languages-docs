# ALR_D_FF


![ALR_D_FF](./ALR_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_D_FF** implementiert ein datengesteuertes Flip-Flop (D-Latch) mit Adapter‑basierter Schnittstelle. Er übernimmt einen Datenwert bei einem Taktereignis und stellt diesen am Ausgang zur Verfügung. Der Baustein kapselt die IEC‑61499‑Standardfunktion `E_D_FF_ANY` und bietet eine unidirektionale Adapter‑Anbindung für eine modulare Systemintegration.

## Schnittstellenstruktur
Der FB besitzt keine direkten Ereignis‑ oder Dateneingänge/-ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter:

### **Ereignis-Eingänge**
- **I.E1** (über Socket `I`): Taktereignis – bei einer steigenden Flanke wird der aktuelle Datenwert übernommen.

### **Ereignis-Ausgänge**
- **Q.E1** (über Plug `Q`): Bestätigungsereignis – wird nach erfolgreicher Übernahme des Datenwertes gesendet.

### **Daten-Eingänge**
- **I.D1** (über Socket `I`): Dateneingang – der zu latchende Wert (Datentyp wird durch den Adapter `ALR` definiert).

### **Daten-Ausgänge**
- **Q.D1** (über Plug `Q`): Datenausgang – der gespeicherte, latched Wert.

### **Adapter**
| Adapter  | Typ                      | Richtung | Beschreibung                     |
|----------|--------------------------|----------|----------------------------------|
| `I`      | adapter::types::unidirectional::ALR | Socket (Eingang) | Liefert das Taktereignis und den Datenwert. |
| `Q`      | adapter::types::unidirectional::ALR | Plug (Ausgang)   | Gibt das Ausgangsereignis und den latched Wert aus. |

## Funktionsweise
1. Der FB erwartet ein Taktereignis am Adapter‑Eingang `I.E1`.
2. Gleichzeitig wird der Datenwert von `I.D1` gelesen.
3. Der interne Baustein `E_D_FF_ANY` übernimmt den Datenwert bei der steigenden Flanke des Taktes.
4. Der übernommene Wert wird unverändert auf `Q.D1` ausgegeben.
5. Ein Ausgangsereignis auf `Q.E1` signalisiert, dass der neue Wert bereitsteht.

Der Vorgang wiederholt sich bei jedem weiteren Taktereignis. Zwischen den Takten bleibt der Ausgangswert stabil (Latch‑Verhalten).

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle**: Der FB nutzt den unidirektionalen Adapter `ALR`, der genau ein Ereignis und einen Datenwert transportiert. Dies ermöglicht eine lose Kopplung und einfaches Zusammenschalten mit anderen Adapter‑Bausteinen.
- **Delegation an IEC‑61499‑Standard**: Die eigentliche Flip‑Flop‑Logik wird durch den Standard‑FB `E_D_FF_ANY` realisiert, der für beliebige Datentypen ausgelegt ist („ANY“). Der `ALR_D_FF` erbt dadurch dessen Robustheit und Typneutralität.
- **Keine eigene Zustandsmaschine**: Der FB besitzt keinen internen Zustandsautomaten – die Zustandsverwaltung erfolgt vollständig innerhalb des eingebetteten `E_D_FF_ANY`.

## Zustandsübersicht
Der Baustein hat keine expliziten Zustände. Die interne Logik (Flip‑Flop) kennt lediglich zwei implizite Zustände:
- **Warten auf Taktereignis**: Der Ausgang behält den zuletzt gelatchten Wert.
- **Latch‑Moment**: Bei einem Taktereignis wird der Eingangswert übernommen und der Ausgang aktualisiert.

## Anwendungsszenarien
- **Datenspeicherung**: Festhalten eines digitalen Signals (z. B. Schalterstellung) bis zur nächsten Abfrage.
- **Synchronisation**: Übernahme von asynchronen Daten in einen getakteten Kontext.
- **Puffern**: Zwischenspeichern von Werten in Steuerungsabläufen, z. B. in Zustandsautomaten oder Sequenzsteuerungen.

## Vergleich mit ähnlichen Bausteinen
- **`ALR_SR_FF`** (Set‑Reset‑Flip‑Flop): Bietet zwei Steuereingänge (Set/Reset) statt einem Takteingang. Geeignet für prioritätsgesteuerte Anwendungen.
- **`ALR_JK_FF`** (JK‑Flip‑Flop): Komplexeres Schaltverhalten mit Toggeln und Halten. Flexibler, aber aufwändiger.
- **`E_D_FF_ANY`** (direkt): Bietet die gleiche Funktionalität, jedoch mit separaten Ereignis‑ und Dateneingängen/-ausgängen anstelle eines Adapters. Der `ALR_D_FF` vereinfacht die Kopplung in Adapter‑basierten Frameworks.

## Fazit
Der `ALR_D_FF` ist ein schlanker, aber zuverlässiger D‑Flip‑Flop‑Baustein für den Einsatz in adapterorientierten 4diac‑Anwendungen. Er kombiniert die bewährte IEC‑61499‑Standardlogik mit einer klar strukturierten Adapter‑Schnittstelle und eignet sich besonders für modulare, wiederverwendbare Steuerungssysteme.