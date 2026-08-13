# ALI_SUB_2


![ALI_SUB_2](./ALI_SUB_2.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein (FB) `ALI_SUB_2` ist ein generischer, arithmetischer Funktionsbaustein zur Durchführung einer Subtraktion. Er entspricht dem IEC 61131-3-Standard für standardmäßige arithmetische Funktionen. Der Baustein verwendet Adapter-Verbindungen (`ALI` - Arithmetic Logical Interface), um die Eingangsdaten entgegenzunehmen und das Ergebnis der Subtraktion auszugeben. 

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung und die Ereignisverarbeitung werden über die angeschlossenen Adapter realisiert.

### **Ereignis-Ausgänge**

Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über die Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübertragung erfolgt gekapselt über die Eingangs-Adapter.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::ALI`): Der erste Eingang (Minuend) für die Subtraktionsberechnung.
*   **IN2** (Typ: `adapter::types::unidirectional::ALI`): Der zweite Eingang (Subtrahend) für die Subtraktionsberechnung.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::ALI`): Der Ausgang (Differenz) der Berechnung ($OUT = IN1 - IN2$).

---

## Funktionsweise

Der Baustein `ALI_SUB_2` führt eine mathematische Subtraktion aus. Sobald Werte über die Eingangs-Adapter anliegen bzw. aktualisiert werden, berechnet der Baustein die Differenz:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

Das Ergebnis wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben. Da es sich um einen generischen Funktionsbaustein handelt, der auf der internen Klasse `GEN_ALI_SUB` basiert, kann sich der Baustein flexibel an die im Adapter definierten Datentypen anpassen.

---

## Technische Besonderheiten

*   **Generische Implementierung:** Der Baustein nutzt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_ALI_SUB'`. Dies erlaubt eine flexible Handhabung verschiedener Datentypen, die durch die Adapter-Schnittstellen vorgegeben werden.
*   **Kapselung durch Adapter:** Durch die Verwendung von unidirektionalen `ALI`-Adaptern werden Daten und die dazugehörigen Steuerungsereignisse (wie z.B. Update-Events) in einer einzigen Verbindung gebündelt. Dies reduziert die Anzahl der sichtbaren Verbindungslinien im 4diac-Applikationseditor und erhöht die Übersichtlichkeit.

---

## Zustandsübersicht

Der Baustein verhält sich rein zustandslos und reaktiv. Es gibt keine interne Zustandsmaschine (Execution Control Chart - ECC). Die Verarbeitung wird direkt durch eingehende Datenänderungen oder Ereignisse auf den Eingangs-Adaptern `IN1` und `IN2` getriggert.

---

## Anwendungsszenarien

*   **Signalverarbeitung und Skalierung:** Berechnung von Abweichungen, wie beispielsweise der Differenz zwischen einem Sollwert und einem Istwert (Regelungsabweichung) in Steuerungsanwendungen.
*   **Offset-Kompensation:** Abzug von Nullpunktfehlern oder Offsets bei Sensordaten, die über Adapterstrukturen in das System eingespeist werden.
*   **Modulare Systemarchitekturen:** Einsatz in komplexen, verteilten Steuerungssystemen, bei denen ein strukturierter und übersichtlicher Datenfluss durch den Einsatz von Adaptern gefordert ist.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Subtraktionsbaustein `SUB` aus der IEC 61131-3 Bibliothek benötigt `ALI_SUB_2` keine explizite Verdrahtung von Datentypen (wie `INT`, `REAL`) und Steuerereignissen (wie `REQ` / `CNF`). Während der Standard-`SUB`-Baustein diskrete Ein- und Ausgänge besitzt, bündelt `ALI_SUB_2` diese in `ALI`-Adaptern, was die Wiederverwendbarkeit und die Übersichtlichkeit im Systemdesign erheblich verbessert.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ALI_SUB_2` ist ein vielseitiger und wartungsfreundlicher Funktionsbaustein für arithmetische Subtraktionen in 4diac. Durch die konsequente Nutzung von Adaptern fügt er sich ideal in serviceorientierte und modulare Steuerungsarchitekturen ein und minimiert den Verdrahtungsaufwand im Entwicklungswerkzeug.