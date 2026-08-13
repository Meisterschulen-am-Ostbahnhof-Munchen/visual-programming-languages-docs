# AR_DIV_2




![AR_DIV_2](./AR_DIV_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AR_DIV_2` ist ein generischer arithmetischer Baustein, der für die Durchführung von Divisionsoperationen (`DIV`) in IEC 61499-basierten Systemen entwickelt wurde. Im Gegensatz zu klassischen Funktionsbausteinen nutzt dieser Baustein Adapter (`unidirectional::AR`), um Daten und Ereignisse zu bündeln. Dies sorgt für eine übersichtlichere und modularere visuelle Programmierung innerhalb der 4diac-IDE.

## Schnittstellenstruktur

Da es sich um einen rein adapterbasierten Funktionsbaustein handelt, verfügt `AR_DIV_2` über keine direkten, klassischen Daten- oder Ereignis-Ein- und Ausgänge auf der Hauptebene. Die gesamte Kommunikation wird über Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden.* (Die Ereignissteuerung erfolgt implizit über die Eingangs-Adapter).

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden.* (Die Ereignissteuerung erfolgt implizit über den Ausgangs-Adapter).

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.* (Die Datenübergabe erfolgt über die Eingangs-Adapter).

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.* (Die Datenübergabe erfolgt über den Ausgangs-Adapter).

### **Adapter**

| Typ | Name | Adaptertyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Socket** (Eingang) | `IN1` | `adapter::types::unidirectional::AR` | Erster Eingangswert (Dividend) für die Division. |
| **Socket** (Eingang) | `IN2` | `adapter::types::unidirectional::AR` | Zweiter Eingangswert (Divisor) für die Division. |
| **Plug** (Ausgang) | `OUT` | `adapter::types::unidirectional::AR` | Das Ergebnis der Division (Quotient). |

## Funktionsweise

Der Baustein führt eine mathematische Division der über die Adapter bereitgestellten Werte aus. Sobald ein Aktualisierungsereignis an den Eingangs-Adaptern (`IN1` oder `IN2`) signalisiert, dass neue Daten vorliegen, wird die Berechnung getriggert:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Das berechnete Ergebnis wird anschließend an den Ausgangs-Adapter `OUT` übergeben und das entsprechende Sende-Ereignis des Adapters ausgelöst, um nachfolgende Bausteine über den neuen Wert zu informieren.

## Technische Besonderheiten

* **Generischer Typ (`GEN_AR_DIV`):** Der Baustein ist intern als generischer Typ deklariert. Dies ermöglicht eine flexible Anpassung an verschiedene Datentypen (z. B. `REAL`, `LREAL`, `INT`), je nachdem, wie der zugrunde liegende `AR`-Adaptertyp definiert ist.
* **Adapter-Kopplung:** Durch die Verwendung von unidirektionalen Adaptern (`unidirectional::AR`) wird die Anzahl der Verbindungslinien im Funktionsplan drastisch reduziert, was die Lesbarkeit komplexer mathematischer Berechnungen erhöht.
* **Schutz vor Division durch Null:** Systemintegrierte Schutzmaßnahmen hängen von der spezifischen Laufzeitumgebung (Runtime) ab. Bei der Verwendung des Bausteins ist darauf zu achten, dass der Divisor (`IN2`) ungleich Null ist, um Berechnungsfehler oder Laufzeitabstürze zu vermeiden.

## Zustandsübersicht

Der Baustein verhält sich im Wesentlichen zustandslos (stateless) und reagiert ereignisgesteuert:

1. **Wartezustand (Idle):** Der Baustein wartet auf ein Aktualisierungsereignis an den Adaptern `IN1` oder `IN2`.
2. **Berechnung:** Nach Eintreffen eines Ereignisses wird die Division ausgeführt.
3. **Aktualisierung:** Das Ergebnis wird an `OUT` angelegt und das Ausgangsereignis getriggert. Der Baustein kehrt sofort in den Wartezustand zurück.

## Anwendungsszenarien

* **Messwertskalierung:** Division von Sensorrohdaten durch einen festen Skalierungsfaktor zur Umrechnung in physikalische Einheiten.
* **Mittelwertberechnung:** Division einer Summe durch die Anzahl der Messwerte in komplexeren Berechnungsnetzwerken.
* **Verhältnisberechnungen:** Bestimmung von prozentualen Anteilen oder Verhältnissen in verfahrenstechnischen Anlagen.

## Vergleich mit ähnlichen Bausteinen

* **Klassischer `DIV`-Baustein:** Der klassische IEC 61131-3 `DIV`-Baustein besitzt dedizierte Pins für `IN1`, `IN2` und `OUT` sowie die dazugehörigen `REQ`- und `CNF`-Events. `AR_DIV_2` bündelt diese Signale in Adaptern, was die Verdrahtung in großen Projekten vereinfacht.
* **`AR_MUL_2` / `AR_ADD_2`:** Diese Bausteine teilen sich dieselbe Adapter-Philosophie, führen jedoch Multiplikationen bzw. Additionen durch. Sie lassen sich nahtlos mit `AR_DIV_2` zu mathematischen Berechnungsbäumen verketten.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AR_DIV_2` ist ein hocheffizienter, modularer Baustein für arithmetische Divisionen. Durch konsequenten Einsatz von Adaptern eignet er sich hervorragend für saubere, übersichtliche Software-Architekturen in der verteilten Automatisierung nach dem IEC 61499 Standard.