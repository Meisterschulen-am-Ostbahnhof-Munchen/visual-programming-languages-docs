# ALR_ADD_3


![ALR_ADD_3](./ALR_ADD_3.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALR_ADD_3` ist ein generischer Arithmetik-Baustein für die 4diac-IDE, der zur Addition von drei Eingangswerten dient. Er entspricht den Standard-Arithmetikfunktionen nach IEC 61131-3, nutzt jedoch ein adapterbasiertes Schnittstellendesign. Anstatt mit einzelnen Daten- und Ereignispins arbeitet dieser Baustein mit unidirektionalen Adaptern, um eine saubere Kapselung und eine übersichtlichere Verdrahtung innerhalb der Anwendung zu ermöglichen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die ereignisbasierte Steuerung wird intern über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

- **IN1** (Typ: `adapter::types::unidirectional::ALR`): Erster Summand der Additionsoperation.
- **IN2** (Typ: `adapter::types::unidirectional::ALR`): Zweiter Summand der Additionsoperation.
- **IN3** (Typ: `adapter::types::unidirectional::ALR`): Dritter Summand der Additionsoperation.

#### **Plugs (Ausgangs-Schnittstellen)**

- **OUT** (Typ: `adapter::types::unidirectional::ALR`): Ausgangs-Adapter, der das Ergebnis der Addition (`IN1 + IN2 + IN3`) sowie das zugehörige Trigger-Ereignis bereitstellt.

## Funktionsweise

Der Baustein addiert die über die drei Eingangs-Adapter (`IN1`, `IN2` und `IN3`) bereitgestellten Werte.
Sobald an einem der Eingangs-Adapter ein neues Ereignis oder ein neuer Wert registriert wird, führt der Funktionsbaustein die Berechnung nach folgendem Schema aus:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Das Ergebnis wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben und ein entsprechendes Aktualisierungsereignis wird ausgelöst, um nachfolgende Bausteine im Datenfluss zu triggern.

## Technische Besonderheiten

- **Generischer Baustein:** Durch das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_ALR_ADD'` ist der Funktionsbaustein datentypunabhängig (generisch) aufgebaut. Er kann somit flexibel mit verschiedenen numerischen Datentypen (z. B. INT, REAL, LREAL) arbeiten, sofern der verwendete Adaptertyp `ALR` diese unterstützt.
- **Adapter-Kopplung:** Die Verwendung von Adaptern anstelle von klassischen Daten- und Ereignispins reduziert die Anzahl der sichtbaren Verbindungslinien im Application Editor von 4diac drastisch. Dies sorgt für eine wesentlich bessere Lesbarkeit komplexer Steuerungsdiagramme.

## Zustandsübersicht

Da es sich bei `ALR_ADD_3` um einen mathematischen, datenflussorientierten Funktionsbaustein handelt, besitzt er keinen komplexen internen Zustandsautomaten (ECC). Die Ausführung erfolgt rein reaktiv (ereignisgesteuert über die Eingangs-Adapter).

## Anwendungsszenarien

- **Messwert-Summierung:** Addition von drei analogen Teilströmen zur Ermittlung des Gesamtstroms in einer Energieverteilung.
- **Mischungsrechnungen:** Zusammenführung von drei Durchflussmengen in einer verfahrenstechnischen Anlage zur Berechnung des Gesamt-Zuflusses.
- **Sollwert-Generierung:** Berechnung eines Gesamtsollwerts aus einem Basiswert, einem Korrekturwert und einem Offset.

## Vergleich mit ähnlichen Bausteinen

- **Standard `ADD` (IEC 61131-3):** Der klassische `ADD`-Baustein verwendet separate Pins für Daten und Ereignisse (REQ/CNF). `ALR_ADD_3` hingegen bündelt diese Signale in Adaptern, was die Modularität und Wiederverwendbarkeit im projektübergreifenden Design erhöht.
- **`ALR_ADD_2`:** Ein ähnlicher adapterbasierter Baustein, der jedoch nur zwei Eingänge unterstützt. `ALR_ADD_3` spart bei der Addition von exakt drei Werten Kaskadierungen und somit zusätzlichen Speicher- und Berechnungsaufwand.

- **[`ALR_ADD_3_UNGATED`](ALR_ADD_3_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALR_ADD_3` ist ein flexibler und performanter Baustein zur Addition von drei Werten in 4diac-Umgebungen. Durch sein generisches Design und die konsequente Nutzung von unidirektionalen Adaptern trägt er maßgeblich zur Übersichtlichkeit, Strukturierung und Wartbarkeit moderner, verteilter Steuerungsprogramme bei.
