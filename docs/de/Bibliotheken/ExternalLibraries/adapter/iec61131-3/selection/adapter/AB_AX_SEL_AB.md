# AB_AX_SEL_AB


![AB_AX_SEL_AB](./AB_AX_SEL_AB.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AB_AX_SEL_AB` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für die IEC 61499, der eine binäre Auswahl (Selektion) auf Adapter-Ebene realisiert. Er dient dazu, basierend auf einem Steuersignal eines Selektor-Adapters (`G`), zwischen den Signalen zweier Eingangs-Adapter (`IN0` und `IN1`) auszuwählen und das ausgewählte Signal an einen Ausgangs-Adapter (`OUT`) weiterzuleiten. 

Dieser Baustein eignet sich besonders für ereignisgesteuerte Architekturen, bei denen Datenströme flexibel geroutet werden müssen, ohne die Kapselung der Adapter-Schnittstellen aufzubrechen.

## Schnittstellenstruktur

Da es sich um einen adapterbasierten Funktionsbaustein handelt, sind die klassischen Ereignis- und Dateneingänge vollständig in den Adapterschnittstellen gekapselt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Steuerung erfolgt über die Ereignisse innerhalb der Adapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Signalisierung erfolgt über die Ereignisse innerhalb des Ausgangs-Adapters.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug (Consumer) | `adapter::types::unidirectional::AB` | Der ausgewählte Ausgang (Selected Output). Gibt das weitergeleitete Signal aus. |
| **IN0** | Socket (Provider) | `adapter::types::unidirectional::AB` | Erster auswählbarer Eingang (wird selektiert, wenn der Selektor `G` den Zustand `FALSE` hat). |
| **IN1** | Socket (Provider) | `adapter::types::unidirectional::AB` | Zweiter auswählbarer Eingang (wird selektiert, wenn der Selektor `G` den Zustand `TRUE` hat). |
| **G** | Socket (Provider) | `adapter::types::unidirectional::AX` | Selektor-Adapter (Steuersignal für die Auswahl). |

*Hinweis zu den Adaptertypen:*
* `AB` steht für einen unidirektionalen Adapter, der ein Byte-Datensignal (`D1`/`D`) und ein Ereignis (`E1`) führt.
* `AX` steht für einen unidirektionalen Adapter, der ein boolesches Datensignal (`D1`/`D`) und ein Ereignis (`E1`) führt.

## Funktionsweise

Im Inneren des Funktionsblocks befindet sich ein Netzwerk aus Standard-Funktionsbausteinen (IEC 61131-3 und IEC 61499), das die Logik abbildet:

1. **Ereignis- und Datenerfassung:**
   * Trifft an einem der Eingangs-Adapter (`IN0`, `IN1`, `G`) ein Ereignis (`E1`) ein, wird der jeweilige Wert (`D1`) über ein flankengetriggertes Speicherglied (D-Flip-Flop `E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert.
2. **Datenkonvertierung / Pufferung:**
   * Die Bausteine `F_MOVE_IN0` und `F_MOVE_IN1` kopieren die Byte-Werte der Eingänge an das Auswahl-Element.
3. **Auswahl-Logik (`F_SEL`):**
   * Der Standard-Auswahlbaustein `F_SEL` (aus der IEC 61131-3 Library) übernimmt die eigentliche Selektion:
     * Ist das Signal aus dem Selektor-Adapter `G` gleich `FALSE`, wird das Signal von `IN0` an den Ausgang durchgeschaltet.
     * Ist das Signal aus dem Selektor-Adapter `G` gleich `TRUE`, wird das Signal von `IN1` an den Ausgang durchgeschaltet.
4. **Ausgabe:**
   * Der ausgewählte Wert wird über einen weiteren Konvertierungsbaustein (`F_MOVE_OUT` mit Datentyp `BYTE`) an ein Ausgangs-Flipflop (`E_D_FF_ANY_OUT`) übergeben.
   * Dieses generiert am Plug `OUT` das entsprechende Ausgangsereignis (`OUT.E1`) und stellt den selektierten Datenwert (`OUT.D1`) bereit.

## Technische Besonderheiten

* **Ereignisgesteuertes Daten-Routing:** Jede Änderung an den Eingängen `IN0` oder `IN1` sowie am Selektor `G` triggert eine Aktualisierung und Berechnung des Ausgangs. Es erfolgt keine zyklische Abfrage (Polling).
* **Entkopplung durch Speicherglieder:** Durch den Einsatz von `E_D_FF` und `E_D_FF_ANY` wird sichergestellt, dass die Daten konsistent übernommen werden und keine unkontrollierten Signaländerungen (Race Conditions) am Ausgang entstehen.
* **Typisierung:** Die interne Verarbeitung der Daten ist fest auf den Datentyp `BYTE` ausgelegt (definiert über das Attribut `DataType="BYTE"` an den `F_MOVE`-Bausteinen).

## Zustandsübersicht

| Zustand Selektor `G` | Ereignis an Eingang | Verhalten am Ausgang `OUT` |
| :--- | :--- | :--- |
| `FALSE` | Ereignis an `IN0` | Wert von `IN0` wird an `OUT` übergeben; Ereignis `OUT.E1` wird ausgelöst. |
| `FALSE` | Ereignis an `IN1` | Wert von `IN1` wird intern aktualisiert, jedoch **nicht** an `OUT` weitergeleitet. |
| `TRUE` | Ereignis an `IN0` | Wert von `IN0` wird intern aktualisiert, jedoch **nicht** an `OUT` weitergeleitet. |
| `TRUE` | Ereignis an `IN1` | Wert von `IN1` wird an `OUT` übergeben; Ereignis `OUT.E1` wird ausgelöst. |
| Wechsel `FALSE` $\rightarrow$ `TRUE` | Ereignis an `G` | Der aktuell gespeicherte Wert von `IN1` wird an `OUT` durchgeschaltet; `OUT.E1` wird ausgelöst. |
| Wechsel `TRUE` $\rightarrow$ `FALSE` | Ereignis an `G` | Der aktuell gespeicherte Wert von `IN0` wird an `OUT` durchgeschaltet; `OUT.E1` wird ausgelöst. |

## Anwendungsszenarien

* **Signal-Umschaltung in der Feldebene:** Umschalten zwischen dem Signal eines aktiven Sensors (`IN1`) und einem vordefinierten Ersatzwert/Fehlerwert (`IN0`) im Falle einer Störung.
* **Hand-/Automatik-Umschaltung:** Weiterleitung von Steuerbytes, wobei im Automatikbetrieb (`G = TRUE`) Werte aus der automatischen Regelung verwendet werden, während im Handbetrieb (`G = FALSE`) manuell vorgegebene Werte an die Aktoren gesendet werden.
* **Rezeptur- oder Modusauswahl:** Dynamische Pfadauswahl für Konfigurations- oder Zustandsdaten in komplexen Prozesssteuerungen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Funktionsbaustein `F_SEL` arbeitet `AB_AX_SEL_AB` direkt auf Adapter-Ebene. 
* Während bei `F_SEL` diskrete Datenleitungen und separate Trigger-Ereignisse manuell verdrahtet werden müssen, kapselt `AB_AX_SEL_AB` diese Logik. 
* Das spart Engineering-Zeit, reduziert die Anzahl sichtbarer Verbindungen im 4diac-IDE Application Editor und minimiert Fehlerquellen bei der Verknüpfung von Daten- und Ereignisströmen.

## Fazit

Der `AB_AX_SEL_AB` ist ein robuster und wiederverwendbarer Hilfsbaustein zur Signalroutung auf Basis von Byte-Adaptern. Durch die konsequente Kapselung der Auswahl- und Synchronisationslogik trägt er maßgeblich zur Übersichtlichkeit und Modularisierung von Steuerungsprogrammen in 4diac-IDE bei.