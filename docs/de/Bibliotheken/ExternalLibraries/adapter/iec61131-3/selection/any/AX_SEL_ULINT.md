# AX_SEL_ULINT


![AX_SEL_ULINT](./AX_SEL_ULINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AX_SEL_ULINT` ist ein binärer Selektionsbaustein (Multiplexer) für den Datentyp `ULINT` (Unsigned Long Integer / 64-Bit Ganzzahl) nach dem IEC 61131-3-Standard. Er ermöglicht das Umschalten zwischen zwei Eingangswerten (`IN0` und `IN1`) basierend auf dem Zustand eines Selektors, der über einen Adapter (`G`) angebunden ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Trigger-Ereignis zur Übernahme und Aktualisierung des Eingangswerts `IN0`.
* **EI1**: Trigger-Ereignis zur Übernahme und Aktualisierung des Eingangswerts `IN1`.

### **Ereignis-Ausgänge**

* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert die Aktualisierung des ausgewählten Ausgangswerts `OUT`.

### **Daten-Eingänge**

* **IN0** (ULINT): Erster auswählbarer Eingangswert. Wird an den Ausgang durchgeschaltet, wenn das Selektorsignal am Adapter `G` den Zustand für `IN0` (logisch `0` bzw. `FALSE`) vorgibt.
* **IN1** (ULINT): Zweiter auswählbarer Eingangswert. Wird an den Ausgang durchgeschaltet, wenn das Selektorsignal am Adapter `G` den Zustand für `IN1` (logisch `1` bzw. `TRUE`) vorgibt.

### **Daten-Ausgänge**

* **OUT** (ULINT): Der aktuell ausgewählte Ausgangswert.

### **Adapter**

* **G** (Typ: `adapter::types::unidirectional::AX`): Ein Socket-Adapter vom Typ `AX`. Er dient als Selektor für die Umschaltung zwischen den beiden Eingängen `IN0` und `IN1`.

## Funktionsweise

Der Baustein arbeitet intern mit einem Standard-Selektionsglied (`F_SEL`). Die Datenübernahme erfolgt ereignisgesteuert:

1. Sobald ein Ereignis an `EI0` oder `EI1` eintrifft, werden die entsprechenden Datenwerte (`IN0` oder `IN1`) im Baustein aktualisiert.
2. Der Zustand des Selektors wird über den Adapter `G` (Ereignis `E1` und Datenwert `D1`) eingelesen.
3. Basierend auf dem Zustand des Selektors wird entweder `IN0` oder `IN1` an den Ausgang `OUT` weitergeleitet.
4. Ein Ausgangsereignis an `CNF` wird ausgegeben, um nachfolgende Bausteine über den neuen Wert zu informieren.

## Technische Besonderheiten

* **Ereignis-Filterung bei Wertänderung:** Der Baustein verwendet intern einen Flankendetektor (`E_D_FF_ANY`), um sicherzustellen, dass das Bestätigungsereignis `CNF` nur dann ausgelöst wird, wenn sich der ausgewählte Ausgangswert `OUT` tatsächlich ändert.
* **Spezielle Selektor-Logik:** Gemäß den Spezifikationsdetails ist das Verhalten so optimiert, dass eine Ausgabe vorrangig dann erzeugt wird, wenn sich das Auswahlsignal `G` ändert.
* **Effizienz:** Durch die Verwendung von Adaptern wird die Verdrahtungskomplexität im 4diac-Netzwerk erheblich reduziert, da Steuerereignis und Selektionsdaten gebündelt übertragen werden.

## Zustandsübersicht

| Zustand Adapter `G` (Wert) | Ausgewählter Eingang | Ausgang (`OUT`) |
| :--- | :--- | :--- |
| `0` (FALSE) | `IN0` | Wert von `IN0` |
| `1` (TRUE) | `IN1` | Wert von `IN1` |

## Anwendungsszenarien

* **Modusabhängige Zählerwert-Auswahl:** Umschalten zwischen zwei großen Zählerständen (z. B. Gesamtstückzahl vs. Chargenstückzahl auf `ULINT`-Basis) in Abhängigkeit von einem Anlagenstatus, der über einen Adapter geliefert wird.
* **Signal-Routing:** Dynamisches Weiterleiten von 64-Bit-Ganzzahldaten in modularen Automatisierungsarchitekturen.
* **Redundante Sensorik:** Auswahl zwischen einem primären und einem sekundären Messwertgeber (z. B. hochpräzise Zeitstempel oder Impulszähler).

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einem klassischen `SEL`-Baustein nach IEC 61131-3, der diskrete Steuerleitungen für Daten und Ereignisse benötigt, nutzt `AX_SEL_ULINT` ein integriertes Adapterkonzept (`G`). Dies macht ihn besonders geeignet für moderne, serviceorientierte IEC 61499 Architekturen, bei denen Koppelsignale strukturiert übergeben werden sollen. Zudem ist er fest auf den ressourcenschonenden, hochpräzisen Datentyp `ULINT` ausgelegt.

## Fazit

`AX_SEL_ULINT` ist ein spezialisierter und robuster Funktionsbaustein zur daten- und ereignisgesteuerten Signalumschaltung im 64-Bit-Bereich. Dank integrierter Änderungsüberwachung (Change-Detection) und der Nutzung von Adaptern arbeitet er hochgradig ereigniseffizient und trägt zu übersichtlichen Steuerungsdiagrammen bei.