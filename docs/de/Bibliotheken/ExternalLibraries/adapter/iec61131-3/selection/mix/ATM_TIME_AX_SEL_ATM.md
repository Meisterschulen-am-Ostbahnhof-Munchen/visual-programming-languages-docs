# ATM_TIME_AX_SEL_ATM


![ATM_TIME_AX_SEL_ATM](./ATM_TIME_AX_SEL_ATM.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ATM_TIME_AX_SEL_ATM` dient der binären Auswahl (Selektion) zwischen zwei Zeitwerten (Typ `TIME`). Er fungiert als Bindeglied zwischen verschiedenen Schnittstellenkonzepten der IEC 61499, indem er sowohl klassische Event-/Dateneingänge als auch adapterbasierte Verbindungen nutzt. Der Baustein wählt basierend auf einem Steuersignal eines Selektor-Adapters (`G`) einen der beiden Eingänge (`IN0` oder `IN1`) aus und gibt diesen am Adapter-Ausgang (`OUT`) aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **EI1** | Signalisiert, dass ein neuer Wert am Dateneingang `IN1` anliegt und dieser aktualisiert werden soll. | `IN1` |

### **Ereignis-Ausgänge**

*Der Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge auf der Hauptebene. Die Ereignisausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Datenpunkt | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN1** | TIME | Direkt selektierbare Eingangsvariable (Zeitwert). |

### **Daten-Ausgänge**

*Der Funktionsbaustein besitzt keine direkten Daten-Ausgänge auf der Hauptebene. Die Datenausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Adaptername | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::ATM` | Plug (Stecker) | Der ausgewählte Ausgangs-Zeitwert (enthält Daten `D1` und Ereignis `E1`). |
| **IN0** | `adapter::types::unidirectional::ATM` | Socket (Buchse) | Selektierbarer Adapter-Eingang für einen Zeitwert (enthält Daten `D1` und Ereignis `E1`). |
| **G** | `adapter::types::unidirectional::AX` | Socket (Buchse) | Selektor-Adapter zur Steuerung, welcher Eingang ausgewählt wird (enthält Daten `D1` als Boolean und Ereignis `E1`). |

---

## Funktionsweise

Das interne Netzwerk des Funktionsbausteins realisiert eine ereignisgesteuerte Selektionslogik:

1. **Datenspeicherung und Synchronisation:**
   * Geht ein Ereignis am Selektor-Adapter `G.E1` ein, wird der Selektionszustand (Boolean aus `G.D1`) über ein D-Flip-Flop (`E_D_FF_G`) zwischengespeichert.
   * Geht ein Ereignis am Adapter-Eingang `IN0.E1` ein, wird der Zeitwert aus `IN0.D1` über ein universelles D-Flip-Flop (`E_D_FF_ANY_IN0`) und einen Kopierbaustein (`F_MOVE_IN0`) übernommen.
   * Ein Ereignis am klassischen Eingang `EI1` übernimmt den Wert von `IN1` analog über `E_D_FF_ANY_IN1` und `F_MOVE_IN1`.

2. **Auswahllogik (Selection):**
   * Der Standard-Auswahlbaustein `F_SEL` wertet das Steuersignal aus:
     * Ist das gelatchte Signal von `G` **FALSE**, wird der Wert von `IN0` durchgeschaltet.
     * Ist das gelatchte Signal von `G` **TRUE**, wird der Wert von `IN1` durchgeschaltet.
   * Jede Änderung an den Eingängen oder dem Selektor triggert die Neuberechnung des Bausteins `F_SEL`.

3. **Ausgabe:**
   * Der ausgewählte Wert wird über `F_MOVE_OUT` an ein Ausgangs-Flip-Flop (`E_D_FF_ANY_OUT`) übergeben.
   * Dieses gibt den selektierten Zeitwert an das Datenelement `OUT.D1` des Ausgangs-Adapters weiter und triggert zeitgleich das Adapter-Ereignis `OUT.E1`.

---

## Technische Besonderheiten

* **Hybrid-Architektur:** Der Baustein kombiniert klassische IEC 61499 Daten-/Event-Schnittstellen (für `IN1` / `EI1`) mit modernen, unidirektionalen Adaptern (`IN0`, `G`, `OUT`). Dies macht ihn äußerst flexibel einsetzbar in heterogenen Steuerungsapplikationen.
* **Ereignisentkopplung:** Durch den Einsatz interner D-Flip-Flops (`E_D_FF_ANY` bzw. `E_D_FF`) wird sichergestellt, dass Daten nur bei Vorliegen der entsprechenden Ereignisse übernommen und verarbeitet werden.

---

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) handelt, wird das Verhalten durch den internen Daten- und Ereignisfluss bestimmt:

| Zustand des Selektors (`G.D1`) | Trigger-Ereignis | Verhalten am Ausgang (`OUT`) |
| :--- | :--- | :--- |
| **FALSE** | Beliebiges Eingangsereignis | Der Wert von `IN0.D1` wird an `OUT.D1` ausgegeben; `OUT.E1` wird ausgelöst. |
| **TRUE** | Beliebiges Eingangsereignis | Der Wert von `IN1` wird an `OUT.D1` ausgegeben; `OUT.E1` wird ausgelöst. |

---

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Dynamisches Umschalten von Prozesszeiten (z. B. Spülzeiten, Belüftungsdauern oder Verzögerungszeiten) zwischen einem automatischen Standardwert (über Adapter `IN0`) und einem manuell vorgegebenen Parameter (über Dateneingang `IN1`).
* **Schnittstellenanpassung:** Verwendung als Brückenbaustein in Systemen, bei denen ältere Programmteile (die mit Standard-Datenports arbeiten) mit neuen, adapterbasierten Softwarekomponenten interagieren müssen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Selektorbaustein (wie `F_SEL` aus der IEC 61131-3 Bibliothek) bietet der `ATM_TIME_AX_SEL_ATM` eine vollständige Kapselung der Event-Verarbeitung. Während beim einfachen `F_SEL` Events manuell verdrahtet werden müssen, übernimmt dieser Baustein das Event-Latching und die Signalweiterleitung über Adapter komplett selbstständig.

---

## Fazit

Der `ATM_TIME_AX_SEL_ATM` ist ein spezialisierter, robuster Auswahlbaustein für Zeitwerte. Durch die intelligente Kombination aus klassischen Eingängen und modernen Adaptern vereinfacht er das Signalrouting in komplexen, ereignisgesteuerten Steuerungsanwendungen erheblich und reduziert den manuellen Verdrahtungsaufwand im 4diac-Applikationseditor.