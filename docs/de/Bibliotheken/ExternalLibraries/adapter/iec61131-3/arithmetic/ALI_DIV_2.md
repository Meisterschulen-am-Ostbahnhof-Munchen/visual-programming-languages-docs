# ALI_DIV_2


![ALI_DIV_2](./ALI_DIV_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ALI_DIV_2` ist ein generischer arithmetischer Funktionsbaustein für die IEC 61499, der für die Durchführung von Divisionsoperationen entwickelt wurde. Die Besonderheit dieses Bausteins liegt in der Verwendung von unidirektionalen Adaptern (`ALI`) anstelle von klassischen Daten- und Ereignis-Schnittstellen. Dies ermöglicht eine modulare und übersichtliche Strukturierung von Datenflüssen innerhalb der 4diac-IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung der Ausführung erfolgt über die angebundenen Adapter.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::ALI`): Der Dividend (Zähler) der Division.
*   **IN2** (Typ: `adapter::types::unidirectional::ALI`): Der Divisor (Nenner) der Division.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::ALI`): Das Ergebnis der mathematischen Division ($OUT = IN1 / IN2$).

## Funktionsweise

Der Baustein `ALI_DIV_2` berechnet den Quotienten aus den Werten, die über die Eingangs-Adapter `IN1` und `IN2` bereitgestellt werden. Das Ergebnis wird an den Ausgangs-Adapter `OUT` übergeben. 

Da es sich um einen generischen Funktionsbaustein (`GEN_ALI_DIV`) handelt, kann der Baustein flexibel mit verschiedenen Datentypen arbeiten, sofern die verwendeten `ALI`-Adapter diese unterstützen (z. B. Ganzzahlen oder Gleitkommazahlen). Die eigentliche Berechnung wird durch die im Adapter definierten Ereignisse getriggert. Sobald neue Daten an den Eingängen anliegen und ein entsprechendes Trigger-Signal über die Adapter-Schnittstelle empfangen wird, wird die Division ausgeführt und das Ergebnis am Ausgang bereitgestellt.

## Technische Besonderheiten

*   **Generische Implementierung:** Durch die Zuordnung zur generischen Klasse `GEN_ALI_DIV` ist der Baustein nicht auf einen festen Datentyp (wie z.B. `REAL` oder `INT`) beschränkt. Er passt sich dynamisch den Typdefinitionen der verbundenen Adapter an.
*   **Kapselung durch Adapter:** Die Verwendung unidirektionaler `ALI`-Adapter reduziert den Verkabelungsaufwand in der 4diac-IDE drastisch, da Daten und zugehörige Trigger-Ereignisse in einer einzigen Verbindung gebündelt übertragen werden.
*   **Division durch Null:** Bei der Implementierung und Laufzeitumgebung muss darauf geachtet werden, wie mit einem Wert von `0` am Eingang `IN2` umgegangen wird, um Systemabstürze zu vermeiden (z. B. durch standardmäßige Rückgabe von `NaN`, Unendlich oder das Abfangen über die Adapter-Fehlerbehandlung).

## Zustandsübersicht

Da es sich bei `ALI_DIV_2` um einen daten- und ereignisgesteuerten Rechenbaustein handelt, besitzt er keine komplexe interne Zustandsmaschine (keinen klassischen ECC). Er verhält sich wie ein funktionaler Block:
1. **Warten auf Trigger:** Der Baustein wartet auf ein Aktualisierungsereignis an den Eingangs-Adaptern `IN1` oder `IN2`.
2. **Berechnung:** Bei Signalempfang werden die Daten ausgelesen und dividiert.
3. **Ausgabe:** Das Ergebnis wird an `OUT` angelegt und das zugehörige Ereignis über den Ausgangs-Adapter signalisiert.

## Anwendungsszenarien

*   **Signalnormierung und Skalierung:** Division von Sensorwerten durch konstante Faktoren zur Einheitenumrechnung innerhalb einer Adapter-basierten Steuerungsarchitektur.
*   **Verhältnisberechnung:** Bestimmung von Verhältnissen (z. B. Kraftstoff-Luft-Gemisch, Durchflussverhältnisse) in verfahrenstechnischen Anlagen.
*   **Verteilte Steuerungssysteme:** Einsatz in komplexen IEC 61499 Applikationen, bei denen ein sauberer, modularer Signalfluss mittels Adaptern erzwungen wird.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-`DIV`-Baustein der IEC 61131-3 bzw. IEC 61499, welcher mit klassischen Daten-Pins (`IN1`, `IN2`, `OUT`) und separaten Event-Pins (`REQ`, `CNF`) arbeitet, bietet der `ALI_DIV_2` durch die Nutzung von Adaptern eine deutlich aufgeräumtere Oberfläche im Funktionsplan. Er eignet sich besonders für fortgeschrittene Software-Architekturen, die konsequent auf die Vorteile von Adaptern zur Strukturierung setzen.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALI_DIV_2` ist ein hocheffizienter und flexibel einsetzbarer Divisionsbaustein für moderne IEC 61499 Anwendungen. Durch die konsequente Nutzung generischer Typen und des `ALI`-Adapter-Konzepts trägt er maßgeblich zur Übersichtlichkeit, Wiederverwendbarkeit und Wartbarkeit von Steuerungssoftware in der 4diac-IDE bei.