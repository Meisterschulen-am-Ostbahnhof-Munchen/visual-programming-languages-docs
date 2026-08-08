# ADI_DINT_AX_SEL_ADI


![ADI_DINT_AX_SEL_ADI](./ADI_DINT_AX_SEL_ADI.svg)

*Kein Bild verfügbar*

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `ADI_DINT_AX_SEL_ADI` dient der binären Auswahl (Selektion) zwischen zwei Datenströmen vom Typ `DINT` (Double Integer). Der Baustein kombiniert die klassische Auswahllogik nach IEC 61131-3 (`F_SEL`) mit der ereignisgesteuerten Architektur von IEC 61499. Durch die Verwendung von Adaptern ermöglicht er eine saubere, modulare und flexible Signalverdrahtung in komplexen Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **EI1**: Löst die Aktualisierung und Übernahme des Daten-Eingangswerts `IN1` aus.

### **Ereignis-Ausgänge**
*   *Keine direkten Ereignis-Ausgänge an der Hauptschnittstelle.* Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.

### **Daten-Eingänge**
*   **IN1** (DINT): Wählbarer Dateneingang (wird bei Aktivierung des Selektors auf den Ausgang durchgeschaltet).

### **Daten-Ausgänge**
*   *Keine direkten Daten-Ausgänge an der Hauptschnittstelle.* Die Datenübergabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.

### **Adapter**
*   **OUT** (Plug, Typ: `adapter::types::unidirectional::ADI`): Der ausgewählte Ausgangskanal (Selected Output). Gibt den selektierten `DINT`-Wert sowie das dazugehörige Gültigkeitsereignis aus.
*   **IN0** (Socket, Typ: `adapter::types::unidirectional::ADI`): Wählbarer Eingangskanal 0. Liefert den ersten `DINT`-Alternativwert über eine Adapterverbindung.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Kanal (Selector). Empfängt das boolesche Steuersignal, das bestimmt, welcher Eingang gewählt wird.

---

## Funktionsweise
Der Baustein arbeitet als binärer Multiplexer (Umschalter) für `DINT`-Signale. Die Auswahlsteuerung erfolgt über das Signal am Adapter `G`:

*   Ist der Selektor `G` auf **FALSE**, wird der Wert von Adapter **IN0** auf den Ausgangs-Adapter **OUT** geschaltet.
*   Ist der Selektor `G` auf **TRUE**, wird der Wert vom Daten-Eingang **IN1** auf den Ausgangs-Adapter **OUT** geschaltet.

### Interner Signalfluss:
1.  **Zwischenspeicherung:** Die über die Schnittstellen (`IN0`, `IN1`, `G`) eingehenden Datenwerte werden bei Eintreffen des jeweiligen Triggersignals in internen Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert.
2.  **Selektion:** Der interne Funktionsbaustein `F_SEL` wertet den Zustand des Selektors aus und schaltet den entsprechenden Datenpfad durch.
3.  **Ausgabe:** Das Ergebnis wird über einen internen Verschiebe-Baustein (`F_MOVE`) an den Ausgangs-Adapter `OUT` übergeben und zeitgleich mit einem Ereignis (`OUT.E1`) signalisiert.

---

## Technische Besonderheiten
*   **Adapter-Kopplung:** Durch den Einsatz von unidirektionalen Adaptern (`ADI` für Daten, `AX` für Steuerereignisse) wird die Anzahl der notwendigen Verbindungslinien im übergeordneten Funktionsplan drastisch reduziert.
*   **Ereignis-Konsistenz:** Die internen Daten-Flip-Flops stellen sicher, dass Datenänderungen nur dann verarbeitet und weitergeleitet werden, wenn auch das dazugehörige Ereignis eintrifft. Dies verhindert transiente Fehlschaltungen (Glitches).
*   **Hybrid-Schnittstelle:** Der Baustein erlaubt die Mischung aus einer adapterbasierten Quelle (`IN0`) und einer klassischen Pin-basierten Signalquelle (`IN1`).

---

## Zustandsübersicht
Das Verhalten des Bausteins wird durch die Eintreffenden Ereignisse bestimmt (ereignisgesteuerte Ausführung):

| Auslösendes Ereignis | Bedingung / Zustand Selektor (G) | Aktion / Auswirkung |
| :--- | :--- | :--- |
| **G.E1** (Änderung Selektor) | `G.D1` wechselt auf `FALSE` | Wert von `IN0` wird an `OUT` übergeben; Ereignis `OUT.E1` wird ausgelöst. |
| **G.E1** (Änderung Selektor) | `G.D1` wechselt auf `TRUE` | Wert von `IN1` wird an `OUT` übergeben; Ereignis `OUT.E1` wird ausgelöst. |
| **IN0.E1** (Neuer Wert an IN0) | `G` ist `FALSE` | Neuer Wert von `IN0` wird direkt an `OUT` durchgereicht und signalisiert. |
| **IN0.E1** (Neuer Wert an IN0) | `G` ist `TRUE` | Wert wird intern aktualisiert, hat aber keine direkte Auswirkung auf `OUT`. |
| **EI1** (Neuer Wert an IN1) | `G` ist `TRUE` | Neuer Wert von `IN1` wird direkt an `OUT` durchgereicht und signalisiert. |
| **EI1** (Neuer Wert an IN1) | `G` ist `FALSE` | Wert wird intern aktualisiert, hat aber keine direkte Auswirkung auf `OUT`. |

---

## Anwendungsszenarien
*   **Sollwert-Umschaltung (Hand/Automatik):** Umschalten zwischen einem automatischen Sollwert (z. B. geliefert über Adapter `IN0` von einem Profilgenerator) und einem manuell eingegebenen Festwert (`IN1`).
*   **Sensor-Redundanz:** Auswahl zwischen zwei redundanten Messwerten (skaliert als `DINT`), basierend auf einem vorgelagerten Diagnose-Flag, das an den Selektor `G` übergeben wird.
*   **Parametrierung:** Dynamisches Laden von verschiedenen Konfigurations- oder Rezeptur-DINT-Werten in Abhängigkeit von Maschinenzuständen.

---

## Vergleich mit ähnlichen Bausteinen
*   **Standard `F_SEL`:** Der klassische IEC 61131-3 Selektions-Baustein arbeitet rein datenflussorientiert. Er besitzt keine Event-Steuerung und keine Adapter-Schnittstellen. `ADI_DINT_AX_SEL_ADI` kapselt diese Logik und macht sie fit für die verteilte, ereignisgesteuerte Ausführung in IEC 61499-Umgebungen.
*   **Standard-Multiplexer:** Im Gegensatz zu generischen Multiplexern mit variabler Eingangsanzahl ist dieser Baustein exakt auf zwei Kanäle und die spezifischen Datentypen `DINT` (über `ADI`-Adapter) und `BOOL` (über `AX`-Adapter) optimiert, was die Fehleranfälligkeit bei der Projektierung minimiert.

---

## Fazit
Der `ADI_DINT_AX_SEL_ADI` ist ein äußerst nützlicher Hilfsbaustein für modulare Steuerungsanwendungen in 4diac. Er löst die Aufgabe der ereignisgesteuerten Signalumschaltung elegant auf Systemebene und trägt durch seine Adapterstruktur maßgeblich zu übersichtlichen und wartungsfreundlichen Applikationsnetzwerken bei.