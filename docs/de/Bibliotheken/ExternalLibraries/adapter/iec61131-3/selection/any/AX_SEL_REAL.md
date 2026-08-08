# AX_SEL_REAL


![AX_SEL_REAL](./AX_SEL_REAL.svg)

![AX_SEL_REAL](./AX_SEL_REAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_SEL_REAL` ist ein binärer Selektor für Daten des Typs `REAL`. Er dient dazu, basierend auf dem Zustand eines über einen Adapter (`G`) übergebenen Auswahlsignals, zwischen zwei analogen Eingangswerten (`IN0` und `IN1`) zu wählen und den ausgewählten Wert am Ausgang (`OUT`) bereitzustellen. Der Baustein entspricht der Standard-Selektionsfunktion nach IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **EI0**: Aktualisiert den Wert des Eingangs `IN0`.
*   **EI1**: Aktualisiert den Wert des Eingangs `IN1`.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigungsereignis (Confirmation). Wird ausgelöst, um zu signalisieren, dass sich der Ausgangswert `OUT` aktualisiert hat.

### **Daten-Eingänge**
*   **IN0** (REAL): Der erste auswählbare Eingangswert (wird gewählt, wenn der Selektor `FALSE` ist).
*   **IN1** (REAL): Der zweite auswählbare Eingangswert (wird gewählt, wenn der Selektor `TRUE` ist).

### **Daten-Ausgänge**
*   **OUT** (REAL): Der aktuell ausgewählte Ausgangswert.

### **Adapter**
*   **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Eine Änderung an diesem Adapter triggert die Neuberechnung der Auswahl.

## Funktionsweise
Der Funktionsblock arbeitet intern mit standardisierten IEC 61131- und IEC 61499-Elementen:
1. Trifft ein Ereignis an `EI0` oder `EI1` ein, werden die entsprechenden Daten (`IN0` bzw. `IN1`) über interne Flip-Flops (`E_D_FF_ANY`) zwischengespeichert und an den Selektionskern übergeben.
2. Der Zustand des Adapters `G` (Ereignis `E1` und Datenwert `D1`) steuert ein weiteres Flip-Flop (`E_D_FF_G`).
3. Der eigentliche Selektionsbaustein (`F_SEL`) wertet den Zustand aus:
    * Ist das Auswahlsignal an `G` **FALSE**, wird der Wert von `IN0` an den Ausgang `OUT` weitergeleitet.
    * Ist das Auswahlsignal an `G` **TRUE**, wird der Wert von `IN1` an den Ausgang `OUT` weitergeleitet.
4. Das Ergebnis wird über `F_MOVE_OUT` an den Ausgang `OUT` übertragen, und ein `CNF`-Ereignis wird generiert.

## Technische Besonderheiten
*   **Ereignis-Generierung**: Ein Ausgangsereignis (`CNF`) wird primär dann erzeugt, wenn sich der Zustand des Selektors `G` ändert oder sich der ausgewählte Wert ändert.
*   **Adapter-Anbindung**: Durch die Verwendung des standardisierten Adapters `AX` lässt sich die Auswahlsteuerung elegant und übersichtlich kapseln, ohne dass separate Boolean-Steuerleitungen quer durch das FB-Netzwerk gezogen werden müssen.

## Zustandsübersicht

| Zustand Selektor (G) | Ausgang (OUT) |
|:---|:---|
| **FALSE** (bzw. 0) | Wert von `IN0` |
| **TRUE** (bzw. 1) | Wert von `IN1` |

## Anwendungsszenarien
*   **Sollwert-Umschaltung**: Wechseln zwischen einem manuell vorgegebenen Sollwert (`IN0`) und einem automatischen Sollwert (`IN1`) einer Regelung (z. B. Temperatur oder Druck in `REAL`).
*   **Sensor-Redundanz**: Umschalten auf einen Ersatzsensor (`IN1`), falls der Hauptsensor (`IN0`) als fehlerhaft markiert wird.
*   **Rezeptursteuerung**: Auswahl verschiedener physikalischer Parameter basierend auf dem aktuellen Prozessschritt.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zum standardmäßigen Baustein `F_SEL` (aus der IEC 61131-3 Bibliothek) bietet `AX_SEL_REAL` eine ereignisgesteuerte Verarbeitung nach IEC 61499. Zudem nutzt dieser Baustein einen Adapter für das Selektionssignal, was die Kopplung an übergeordnete Steuerungslogiken (z.B. Zustandsmaschinen) vereinfacht. Andere Varianten dieses Bausteins (z.B. `AX_SEL_INT`) arbeiten nach demselben Prinzip, verarbeiten jedoch andere Datentypen.

## Fazit
Der `AX_SEL_REAL` ist ein robuster und flexibler Baustein für die strukturierte Auswahl von analogen Fließkommawerten in 4diac-Anwendungen. Durch die Integration des Steuersignals über einen Adapter trägt er erheblich zur Reduzierung von Verbindungslinien im FB-Netzwerk bei.