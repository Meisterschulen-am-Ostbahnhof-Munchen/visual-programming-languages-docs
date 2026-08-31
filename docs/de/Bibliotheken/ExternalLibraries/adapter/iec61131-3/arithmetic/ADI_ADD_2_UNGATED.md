# ADI_ADD_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`ADI_ADD_2`](ADI_ADD_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![ADI_ADD_2_UNGATED](./ADI_ADD_2_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ADI_ADD_2_UNGATED` ist ein generischer Funktionsbaustein zur Durchführung von arithmetischen Additionsoperationen. Im Gegensatz zu herkömmlichen mathematischen Funktionsbausteinen nutzt dieser Baustein ein adapterbasiertes Schnittstellenkonzept (unidirektionale `ADI`-Adapter), um Daten und zugehörige Steuerungssignale gebündelt zu übertragen. Er ermöglicht die Addition von zwei Eingangswerten zu einem Ausgangswert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Ausgänge. Die Ereignisweiterleitung wird vollständig über den Ausgangs-Adapter abgewickelt.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine standardmäßigen, direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine standardmäßigen, direkten Daten-Ausgänge.*

### **Adapter**

#### **Sockets (Buchsen - Eingänge)**

-   **IN1**: Typ `adapter::types::unidirectional::ADI`
    -   *Beschreibung:* Erster Eingangswert für die mathematische Addition.
-   **IN2**: Typ `adapter::types::unidirectional::ADI`
    -   *Beschreibung:* Zweiter Eingangswert für die mathematische Addition.

#### **Plugs (Stecker - Ausgänge)**

-   **OUT**: Typ `adapter::types::unidirectional::ADI`
    -   *Beschreibung:* Ausgang, der das Ergebnis der Addition (`IN1 + IN2`) bereitstellt.

---

## Funktionsweise

Der Baustein `ADI_ADD_2_UNGATED` realisiert die arithmetische Operation:
$$\text{OUT} = \text{IN1} + \text{IN2}$$

Sobald sich an den Eingangs-Adaptern `IN1` oder `IN2` Daten ändern oder ein entsprechendes Übertragungsereignis über die Adapterstruktur signalisiert wird, verarbeitet der Baustein die Werte. Die Summe wird berechnet und über das entsprechende Ereignis-/Datenbündel des Ausgangs-Adapters `OUT` an nachfolgende Bausteine weitergeleitet.

Da es sich um einen generischen Baustein (`GEN_ADI_ADD`) handelt, richtet sich der konkret verwendete Datentyp nach den Spezifikationen und der Instanziierung der genutzten `ADI`-Adapter.

---

## Technische Besonderheiten

-   **Generischer Typ:** Der Baustein ist als `GEN_ADI_ADD` deklariert. Dies erlaubt eine flexible Handhabung unterschiedlicher numerischer Datentypen, sofern diese durch die verwendeten Adapter unterstützt werden.
-   **Adapterbasiertes Design:** Durch die Verwendung von unidirektionalen Adaptern vom Typ `ADI` wird die Anzahl der expliziten Verbindungslinien (Verdrahtungsaufwand im Application Editor der 4diac-IDE) drastisch reduziert, da Daten und Synchronisationsereignisse in einer Verbindung gekapselt sind.

---

## Zustandsübersicht

Der Baustein verhält sich wie ein zustandsloser (bzw. rein ereignisgesteuerter kombinatorischer) Baustein:

1.  **Warten auf Datenaktualisierung:** Der Baustein verharrt im Ruhezustand, bis über `IN1` oder `IN2` neue Werte signalisiert werden.
2.  **Berechnung:** Bei Eintreffen eines Ereignisses an den Eingängen wird die mathematische Summe gebildet.
3.  **Ausgabe:** Das Ergebnis wird direkt an den Ausgangs-Adapter `OUT` übergeben und das zugehörige Trigger-Ereignis ausgelöst.

---

## Anwendungsszenarien

-   **Modulare Signalverarbeitung:** Addition von Messwerten (z. B. Sensor 1 + Sensor 2 zur Ermittlung eines Gesamtwerts) in Systemen, die konsequent auf einer Adapter-Architektur aufbauen.
-   **Kaskadierte Berechnungen:** Einfache Integration in komplexe arithmetische Berechnungsnetzwerke durch saubere, strukturierte Adapter-Verbindungen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen `ADD`-Baustein nach IEC 61499 (welcher typischerweise dedizierte `REQ`- und `CNF`-Ereignisports sowie direkte Dateneingänge wie `IN1` und `IN2` als `ANY_NUM` besitzt) kapselt der `ADI_ADD_2_UNGATED` diese Schnittstellen in Adaptern.

-   **Standard ADD:** Erfordert manuelle Verdrahtung von min. 2 Ereignissen und 3 Datenleitungen (insgesamt 5 Verbindungen).
-   **ADI_ADD_2_UNGATED:** Benötigt lediglich die Verbindung der 3 Adapterleitungen (`IN1`, `IN2`, `OUT`), was die Lesbarkeit von komplexen Steuerungsdiagrammen signifikant erhöht.

---

- **[`ADI_ADD_2`](ADI_ADD_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `ADI_ADD_2_UNGATED` ist ein hocheffizienter, übersichtlicher und moderner Baustein für arithmetische Additionen in der 4diac-IDE. Er eignet sich hervorragend für anspruchsvolle Architekturen, bei denen Übersichtlichkeit durch den Einsatz von standardisierten Adaptern im Vordergrund steht.
