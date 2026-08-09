# AUDI_UDINT_AX_SEL_AUDI


![AUDI_UDINT_AX_SEL_AUDI](./AUDI_UDINT_AX_SEL_AUDI.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUDI_UDINT_AX_SEL_AUDI` dient zur binären Auswahl (Multiplexing) zwischen zwei Eingangssignalen des Datentyps `UDINT` (Unsigned Double Integer). Die Steuerung, welcher der beiden Eingänge an den Ausgang durchgeschaltet wird, erfolgt über ein Selektionssignal (Selector). Der Baustein nutzt ein ereignisgesteuertes Netzwerk aus IEC 61499 Standard-Komponenten und verwendet Adapter zur strukturierten Signalübertragung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **EI1** | Event | Aktualisiert und übernimmt den Wert des Dateneingangs `IN1`. |

### **Ereignis-Ausgänge**

Auf direkter Block-Ebene sind keine Ereignis-Ausgänge definiert. Die Ereignisausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN1** | UDINT | Auswählbare Eingangsvariable (Wert 1). Wird über das Ereignis `EI1` eingelesen. |

### **Daten-Ausgänge**

Auf direkter Block-Ebene sind keine Daten-Ausgänge definiert. Die Datenübertragung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug (Stecker) | `adapter::types::unidirectional::AUDI` | Der ausgewählte und durchgeschaltete Ausgangswert. |
| **IN0** | Socket (Buchse) | `adapter::types::unidirectional::AUDI` | Auswählbarer Dateneingang (Wert 0), bereitgestellt über einen Adapter. |
| **G** | Socket (Buchse) | `adapter::types::unidirectional::AX` | Selektorsignal zur Steuerung der Auswahl. |

* * * * * * * * * *

## Funktionsweise

Der Funktionsbaustein basiert intern auf einem logischen Netzwerk (`FBNetwork`), welches die Eingangswerte synchronisiert, die Auswahl trifft und das Ergebnis am Ausgang bereitstellt.

### Signalfluss und Logik:

1. **Eingangssynchronisation (`IN0` und `IN1`):**
   * Ein Ereignis am Adapter-Eingang `IN0.E1` liest den Datenwert `IN0.D1` über ein D-Flip-Flop (`E_D_FF_ANY_IN0`) ein. Mittels `F_MOVE_IN0` wird dieser an den Selektor-Baustein übergeben.
   * Ein Ereignis am physischen Eingang `EI1` liest den Datenwert `IN1` über das D-Flip-Flop (`E_D_FF_ANY_IN1`) ein. Mittels `F_MOVE_IN1` wird dieser an den Selektor-Baustein übergeben.
   
2. **Selektionssteuerung (`G`):**
   * Ein Ereignis am Selektor-Adapter `G.E1` liest den Zustand `G.D1` ein. Das D-Flip-Flop `E_D_FF_G` speichert diesen Zustand und steuert den Auswahleingang `G` des internen Auswahlbausteins `F_SEL` an.

3. **Auswahl und Ausgabe (`F_SEL`):**
   * Der Baustein `F_SEL` (Standard IEC 61131-3 Auswahlfunktion) wertet das Auswahlsignal `G` aus:
     * Ist `G` **FALSE** (0), wird der Wert von `IN0` zum Ausgang durchgeschaltet.
     * Ist `G` **TRUE** (1), wird der Wert von `IN1` zum Ausgang durchgeschaltet.
   * Das Ergebnis wird über `F_MOVE_OUT` an das Ausgangs-D-Flip-Flop (`E_D_FF_ANY_OUT`) übergeben.
   * Nach erfolgreicher Aktualisierung wird das Ereignis `OUT.E1` getriggert und der aktualisierte Wert liegt an `OUT.D1` an.

* * * * * * * * * *

## Technische Besonderheiten

* **Adapter-Kopplung:** Durch die Verwendung von `AUDI`- und `AX`-Adaptern wird die Anzahl der externen Verdrahtungen minimiert und eine standardisierte Schnittstelle für unidirektionale Signalpfade bereitgestellt.
* **Ereignis-Daten-Entkopplung:** Die internen D-Flip-Flops (`E_D_FF_ANY`) stellen sicher, dass Datenwerte nur bei den entsprechenden Trigger-Ereignissen übernommen und konsistent weitergeleitet werden (Vermeidung von Race Conditions).
* **Datentypstabilität:** Die internen Datenpfade und `F_MOVE`-Funktionen sind explizit für den Typ `UDINT` parametriert.

* * * * * * * * * *

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (`Composite FB`) handelt, wird das Verhalten durch den internen ereignisgesteuerten Datenfluss bestimmt:

| Auslösendes Ereignis | Zustand Selektor `G` | Zustand Daten-Eingänge | Resultierendes Verhalten am Ausgang |
| :--- | :--- | :--- | :--- |
| `G.E1` (Änderung) | **FALSE** | Beliebig | `OUT.D1` übernimmt aktuellen Wert von `IN0.D1`; Trigger auf `OUT.E1` |
| `G.E1` (Änderung) | **TRUE** | Beliebig | `OUT.D1` übernimmt aktuellen Wert von `IN1`; Trigger auf `OUT.E1` |
| `IN0.E1` (Wertänderung) | **FALSE** | `IN0.D1` hat neuen Wert | `OUT.D1` wird mit neuem Wert von `IN0.D1` aktualisiert; Trigger auf `OUT.E1` |
| `IN0.E1` (Wertänderung) | **TRUE** | `IN0.D1` hat neuen Wert | Keine Änderung am Ausgang `OUT`. |
| `EI1` (Wertänderung) | **FALSE** | `IN1` hat neuen Wert | Keine Änderung am Ausgang `OUT`. |
| `EI1` (Wertänderung) | **TRUE** | `IN1` hat neuen Wert | `OUT.D1` wird mit neuem Wert von `IN1` aktualisiert; Trigger auf `OUT.E1` |

* * * * * * * * * *

## Anwendungsszenarien

* **Rezeptur- oder Parameter-Umschaltung:** Dynamisches Umschalten zwischen zwei Konfigurations-IDs oder Grenzwerten im `UDINT`-Format während des laufenden Betriebs.
* **Sensor-Redundanz:** Umschaltung zwischen einem primären Messwert (`IN0` über Adapter) und einem Ersatz- oder Kalibrierwert (`IN1` über Direkteingabe) basierend auf einer Fehlerdiagnose (gesteuert via `G`).
* **Betriebsartenwahl:** Routing von unterschiedlichen Zählerständen oder Timern je nach aktiver Betriebsart der Anlage.

* * * * * * * * * *

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL`:** Die reine IEC 61131-3 Funktion `F_SEL` besitzt keine integrierte Ereignissteuerung und keine Adapter-Unterstützung. `AUDI_UDINT_AX_SEL_AUDI` kapselt diese Funktion und macht sie direkt nutzbar für ereignisorientierte IEC 61499 Architekturen.
* **Generische Auswahlbausteine:** Im Vergleich zu rein datenbasierten Selektoren erzwingt dieser Baustein durch seine internen D-Flip-Flops eine strikte Synchronisation zwischen Daten und Ereignissen, was die deterministische Ausführung im Steuerungssystem erhöht.

* * * * * * * * * *

## Fazit

Der `AUDI_UDINT_AX_SEL_AUDI` ist ein spezialisierter und robuster Multiplexer für `UDINT`-Datenströme. Durch die geschickte Kombination von standardisierter IEC 61131-Logik und der ereignisbasierten IEC 61499 Adapter-Technologie eignet er sich hervorragend für modulare und übersichtlich strukturierte Steuerungsanwendungen, bei denen Werte sicher und konsistent umgeschaltet werden müssen.