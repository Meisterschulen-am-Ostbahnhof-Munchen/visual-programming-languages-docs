# AS_SUB_2


![AS_SUB_2](./AS_SUB_2.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AS_SUB_2` ist ein generischer Funktionsbaustein (Generic FB) für die Entwicklungsumgebung 4diac-ide. Er dient der Durchführung einer arithmetischen Subtraktion ($OUT = IN1 - IN2$). 

Im Gegensatz zu klassischen arithmetischen Bausteinen, die direkt mit standardmäßigen Daten- und Ereignis-Schnittstellen arbeiten, nutzt dieser Baustein unidirektionale Adapterverbindungen zur Kapselung von Daten und Steuerungsereignissen. Dies ermöglicht eine strukturierte und übersichtliche Verdrahtung in komplexen IEC 61499-Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsbaustein besitzt keine direkten, eigenständigen Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die angeschlossenen Adapter abgewickelt.

### **Ereignis-Ausgänge**

Der Funktionsbaustein besitzt keine direkten, eigenständigen Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge auf dem Baustein definiert. Die Eingangsdaten werden über die Adapter-Schnittstellen bereitgestellt.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge auf dem Baustein definiert. Das Ergebnis wird über den Ausgangs-Adapter übergeben.

### **Adapter**

Die gesamte Kommunikation des Funktionsbausteins wird über Adapter realisiert:

* **Sockets (Eingangs-Adapter):**
  * `IN1` (Typ: `adapter::types::unidirectional::AS`): Der erste Eingang (Minuend) für die Subtraktion.
  * `IN2` (Typ: `adapter::types::unidirectional::AS`): Der zweite Eingang (Subtrahend) für die Subtraktion.
* **Plugs (Ausgangs-Adapter):**
  * `OUT` (Typ: `adapter::types::unidirectional::AS`): Das Ergebnis (Differenz) der arithmetischen Subtraktion.

## Funktionsweise

Sobald an den Eingangs-Adaptern `IN1` und `IN2` gültige Werte und die entsprechenden Trigger-Ereignisse anliegen, führt der Baustein die Berechnung aus. 

Die mathematische Operation lautet:
$$\text{Ergebnis} = \text{Wert von } IN1 - \text{Wert von } IN2$$

Das Ergebnis der Berechnung sowie das zugehörige Ausgangs-Ereignis werden anschließend über den Ausgangs-Adapter `OUT` an nachfolgende Bausteine weitergeleitet. Da es sich um einen generischen Baustein (`GenericClassName="GEN_AS_SUB"`) handelt, ist er flexibel bezüglich der zugrundeliegenden Datentypen, sofern diese vom Adaptertyp unterstützt werden.

## Technische Besonderheiten

* **Generisches Verhalten:** Durch die Deklaration als generischer Baustein kann er für verschiedene numerische Datentypen (z. B. INT, REAL, LREAL) eingesetzt werden, abhängig von der Definition des verwendeten Adapters `adapter::types::unidirectional::AS`.
* **Kompakte Struktur:** Durch die Verwendung von Adaptern wird die visuelle Komplexität im 4diac-Application-Editor stark reduziert, da Ereignis- und Datenleitungen in einer einzigen Adapterverbindung gebündelt sind.
* **Unidirektionaler Datenfluss:** Die verwendeten Adapter weisen einen strikt unidirektionalen Signalfluss auf (von den Sockets zum Plug).

## Zustandsübersicht

Die Ausführungslogik wird typischerweise durch Ereignisse auf den Eingangs-Adaptern getriggert:

1. **Wartezustand (Idle):** Der Baustein wartet auf ein Ereignis an `IN1` oder `IN2`.
2. **Berechnung (Calculation):** Nach dem Eintreffen eines Triggers werden die Daten aus den Adaptern gelesen und die Differenz gebildet.
3. **Ausgabe (Dispatch):** Das Ergebnis wird in den Ausgangs-Adapter geschrieben und das Ausgangs-Ereignis an `OUT` ausgelöst. Der Baustein kehrt in den Wartezustand zurück.

## Anwendungsszenarien

* **Messwertkorrektur:** Subtraktion von Nullpunktfehlern oder Offsets bei analogen Sensorwerten.
* **Soll-Ist-Vergleich:** Berechnung der Regelabweichung ($e = w - x$) in Regelungskreisen, bei denen Soll- und Istwerte über standardisierte Adapterstrukturen übertragen werden.
* **Füllstands- und Mengenberechnung:** Ermittlung von Differenzmengen in Prozessanlagen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Subtraktionsbaustein (z. B. `SUB` aus der IEC 61131-3-Bibliothek), der mit expliziten Eingängen wie `REQ`, `IN1` und `IN2` arbeitet, bietet der `AS_SUB_2` durch die Kapselung in Adaptern eine wesentlich höhere Modularität. Er eignet sich besonders für fortgeschrittene Softwarearchitekturen in IEC 61499, bei denen Daten- und Signalflüsse als logische Einheiten (Schnittstellen) zusammengefasst werden sollen.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AS_SUB_2` ist ein hocheffizienter, wiederverwendbarer und übersichtlicher Funktionsbaustein zur Realisierung von Subtraktionsaufgaben. Seine Stärke liegt in der konsequenten Nutzung von Adaptern, was zu saubereren Software-Designs und einer verbesserten Wartbarkeit innerhalb der 4diac-ide führt.