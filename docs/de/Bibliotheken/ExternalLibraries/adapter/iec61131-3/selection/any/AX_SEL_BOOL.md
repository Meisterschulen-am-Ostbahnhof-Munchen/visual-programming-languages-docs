# AX_SEL_BOOL


![AX_SEL_BOOL](./AX_SEL_BOOL.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_BOOL` dient der binären Auswahl (Selection) von booleschen Signalen. Er basiert auf der standardisierten Auswahlfunktion nach IEC 61131-3 und ermöglicht es, ereignisgesteuert zwischen zwei booleschen Eingangswerten (`IN0` und `IN1`) zu wählen. Die Steuerung der Auswahl erfolgt elegant über einen Adapter-Eingang.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Löst die Aktualisierung und Übernahme des Daten-Eingangs `IN0` aus.
* **EI1**: Löst die Aktualisierung und Übernahme des Daten-Eingangs `IN1` aus.

### **Ereignis-Ausgänge**

* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert, dass sich der ausgewählte Ausgangswert `OUT` aktualisiert hat.

### **Daten-Eingänge**

* **IN0** (BOOL): Erster auswählbarer Eingangswert. Dieser Wert wird auf den Ausgang durchgeschaltet, wenn der Selektor den Zustand `FALSE` aufweist.
* **IN1** (BOOL): Zweiter auswählbarer Eingangswert. Dieser Wert wird auf den Ausgang durchgeschaltet, wenn der Selektor den Zustand `TRUE` aufweist.

### **Daten-Ausgänge**

* **OUT** (BOOL): Der aktuell selektierte Ausgangswert (entspricht je nach Zustand des Selektors entweder `IN0` oder `IN1`).

### **Adapter**

* **G** (Typ: `adapter::types::unidirectional::AX`): Ein unidirektionaler Adapter-Socket, der als Selektor fungiert. Über diesen Adapter wird das Umschaltsignal empfangen. Ein Ereignis an diesem Adapter triggert die Neuberechnung der Auswahl.

## Funktionsweise

Intern ist der `AX_SEL_BOOL` als zusammengesetzter Funktionsbaustein (Composite FB) realisiert. Die wesentlichen Schritte der Signalverarbeitung sind:
1. Tritt ein Ereignis an `EI0` oder `EI1` auf, wird der jeweilige Datenwert (`IN0` bzw. `IN1`) über interne Event-D-Flip-Flops (`E_D_FF_ANY`) zwischengespeichert und an den zentralen Auswahlbaustein `F_SEL` weitergegeben.
2. Der Selektor-Adapter `G` liefert das Steuersignal. Bei einem Ereignis am Adapter (`G.E1`) wird das Auswahlsignal (`G.D1`) erfasst.
3. Der Baustein `F_SEL` (IEC 61131-3 Standard-Selektor) wertet den Zustand des Selektors aus:
   * Ist das Auswahlsignal `FALSE`, wird der Wert von `IN0` an den Ausgang weitergegeben.
   * Ist das Auswahlsignal `TRUE`, wird der Wert von `IN1` an den Ausgang weitergegeben.
4. Das Ergebnis wird an das Ausgangs-Flip-Flop übergeben. Eine Ausgabe des Bestätigungsereignisses `CNF` erfolgt ereignisgesteuert.

## Technische Besonderheiten

* **Ereignissteuerung bei Selektor-Änderung**: Ein Ausgangsereignis (`CNF`) wird primär dann erzeugt, wenn eine relevante Änderung oder Aktualisierung über den Selektor-Adapter `G` initiiert wird.
* **Ressourceneffizienz**: Durch den Einsatz von flanken- und ereignisgesteuerten D-Flip-Flops (`E_D_FF` und `E_D_FF_ANY`) im internen Netzwerk wird die CPU-Last minimiert, da Berechnungen und Signalweiterleitungen nur bei tatsächlichen Signaländerungen stattfinden.
* **Adapter-Kopplung**: Die Verwendung des unidirektionalen Adapters `AX` sorgt für eine saubere Kapselung der Steuerungslogik und reduziert die Anzahl der benötigten Einzelverbindungen im übergeordneten System.

## Zustandsübersicht

Als Composite-Funktionsbaustein besitzt `AX_SEL_BOOL` keine klassische Zustandsmaschine (ECC), sondern sein Verhalten wird rein durch den Signal- und Ereignisfluss des internen Netzwerks bestimmt:

| Eingangsevent | Zustand Selektor (G) | Interner Ablauf | Ausgangsevent | Ausgang (OUT) |
| :--- | :--- | :--- | :--- | :--- |
| `EI0` / `EI1` | *Keine Änderung* | Werte an `IN0`/`IN1` werden aktualisiert. | - | Keine direkte Änderung am Ausgang ohne Selektortrigger. |
| Adapterevent (`G.E1`) | `FALSE` | Selektor schaltet auf `IN0`. | `CNF` | Wert von `IN0` |
| Adapterevent (`G.E1`) | `TRUE` | Selektor schaltet auf `IN1`. | `CNF` | Wert von `IN1` |

## Anwendungsszenarien

* **Umschaltung Betriebsmodus**: Ideal geeignet für die Umschaltung von Steuersignalen zwischen Automatikbetrieb (`IN0`) und Handbetrieb (`IN1`), wobei der Adapter `G` direkt mit dem Betriebswahlschalter gekoppelt ist.
* **Redundante Signalpfade**: Auswahl zwischen einem primären und einem sekundären (Backup-) Sensor-Signal im Fehlerfall.
* **Ereignisbasiertes Signalrouting**: Dynamische Pfadauswahl in verteilten Steuerungssystemen, bei denen die Selektionslogik von einem anderen Steuerungsmodul über einen Adapter bereitgestellt wird.

## Vergleich mit ähnlichen Bausteinen

* **Standard-Auswahlglied (`F_SEL` nach IEC 61131-3)**: Im Gegensatz zum reinen `F_SEL` integriert `AX_SEL_BOOL` eine ereignisgesteuerte Speicherlogik und nutzt ein Adapter-Interface anstelle von losen booleschen Eingängen für die Selektion. Dies erleichtert die strukturierte Verdrahtung in IEC 61499-Anwendungen erheblich.
* **Multiplexer (MUX)**: Während ein Multiplexer die Auswahl aus einer Vielzahl von Kanälen über einen Integer-Index erlaubt, ist der `AX_SEL_BOOL` speziell für die schnelle, binäre Umschaltung zwischen genau zwei booleschen Signalen optimiert.

## Fazit

Der `AX_SEL_BOOL` ist ein praxistauglicher Baustein für die moderne Industrieautomatisierung nach IEC 61499. Durch die Kombination von bewährter IEC 61131-3 Auswahl-Logik mit einer modernen, adapterbasierten Ereignissteuerung stellt er eine saubere und wiederverwendbare Lösung für binäre Signalumschaltungen dar.