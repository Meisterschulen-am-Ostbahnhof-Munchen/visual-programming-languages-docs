# AX_SEL_INT


![AX_SEL_INT](./AX_SEL_INT.svg)

*Keine Bilddatei vorhanden. Die Schnittstellen und die interne Struktur sind im Folgenden detailliert beschrieben.*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AX_SEL_INT` ist ein Standard-Auswahlbaustein (Selection Function Block) nach IEC 61499. Er dient zur binären Auswahl zwischen zwei ganzzahligen Eingangswerten (`INT`) über ein Selektorsignal, das über einen unidirektionalen Adapter bereitgestellt wird. Der Baustein ist so konzipiert, dass er Ereignisse hocheffizient verarbeitet und ein Ausgangsereignis optimiert ausgibt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **EI0** | Signalisiert die Aktualisierung des Eingangswerts `IN0`. | `IN0` |
| **EI1** | Signalisiert die Aktualisierung des Eingangswerts `IN1`. | `IN1` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **CNF** | Bestätigungsereignis (Confirmation), das eine Änderung oder Aktualisierung des ausgewählten Ausgangswerts signalisiert. | `OUT` |

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | INT | Erster auswählbarer ganzzahliger Eingangswert (Standardmäßig gewählt, wenn der Selektor `FALSE` ist). |
| **IN1** | INT | Zweiter auswählbarer ganzzahliger Eingangswert (Ausgewählt, wenn der Selektor `TRUE` ist). |

### **Daten-Ausgänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **OUT** | INT | Der aktuell selektierte ganzzahlige Ausgangswert. |

### **Adapter**

| Adapter-Name | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **G** | `adapter::types::unidirectional::AX` | Socket (Buchse) | Unidirektionaler Adapter zur Übergabe des Selektorsignals (beinhaltet das Datenfeld `D1` für die Auswahl und das Ereignis `E1` zur Triggerung). |

## Funktionsweise

Der Baustein `AX_SEL_INT` arbeitet als ereignisgesteuerter Multiplexer für zwei `INT`-Werte. 

1. **Wertepufferung:** Bei Eintreffen der Ereignisse `EI0` oder `EI1` werden die Datenwerte `IN0` bzw. `IN1` über interne D-Flipflops (`E_D_FF_ANY_IN0` / `E_D_FF_ANY_IN1`) zwischengespeichert.
2. **Selektion:** Der Adapter `G` liefert über seinen Datenkanal (`G.D1`) das Auswahlsignal. 
   - Ist das Signal `FALSE`, wird der Wert von `IN0` an den Ausgang `OUT` durchgereicht.
   - Ist das Signal `TRUE`, wird der Wert von `IN1` an den Ausgang `OUT` durchgereicht.
3. **Ereignisfilterung (Wichtige Besonderheit):** Ein Ausgangsereignis (`CNF`) wird primär dann generiert, wenn sich das Selektionssignal des Adapters `G` ändert oder sich der resultierende Ausgangswert tatsächlich ändert. Dies verhindert eine unnötige Ereignisflut im nachfolgenden Steuerungsnetzwerk bei redundanten Datenupdates.

## Technische Besonderheiten

* **Composite-FB-Netzwerk:** Der Baustein ist intern aus mehreren Standard-Hilfsbausteinen aufgebaut, darunter `F_SEL` (Auswahlfunktion nach IEC 61131-3), `F_MOVE` (Wertübertragung) und `E_D_FF_ANY` (Ereignisgesteuerte D-Flipflops zur Flankenerkennung und Wertänderungsprüfung).
* **Adapterkopplung:** Durch die Nutzung des Adapters `G` (`AX`-Typ) wird die Verdrahtung im Steuerungsentwurf vereinfacht, da Kontroll- und Datensignale der Auswahl logisch gebündelt übertragen werden.
* **Effiziente Ereignisfortleitung:** Durch die interne Filterung wird das Ausgangsereignis `CNF` nur dann ausgelöst, wenn eine echte Änderung vorliegt (insbesondere bei einer Änderung des Selektors `G`).

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) ohne eigenen Zustandsautomaten (ECC) handelt, wird das Verhalten direkt durch den Signalfluss im internen Netzwerk bestimmt:

* **Zustand "IN0 aktiv":** `G.D1` ist `FALSE`. Änderungen an `IN0` (über `EI0`) führen bei einer Wertänderung zur Aktualisierung von `OUT` und triggern `CNF`. Änderungen an `IN1` werden ignoriert.
* **Zustand "IN1 aktiv":** `G.D1` ist `TRUE`. Änderungen an `IN1` (über `EI1`) führen bei einer Wertänderung zur Aktualisierung von `OUT` und triggern `CNF`. Änderungen an `IN0` werden ignoriert.
* **Umschaltvorgang:** Sobald ein Ereignis `G.E1` eintrifft, bewertet der Baustein die Selektion neu und aktualisiert `OUT` entsprechend dem neu gewählten Eingang.

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Wechsel zwischen einem manuell vorgegebenen Sollwert (`IN0`) und einem Automatik-Sollwert (`IN1`) in einer industriellen Anlage.
* **Sensor-Redundanz:** Umschalten zwischen zwei redundanten Temperatursensoren oder Positionssensoren (übertragen als Integer-Werte) im Falle eines Fehlers.
* **Rezeptursteuerung:** Auswahl verschiedener vordefinierter Parameter-IDs basierend auf dem Zustand einer übergeordneten Ablaufsteuerung.

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL`:** Der klassische IEC 61131-3 Baustein `F_SEL` besitzt keine ereignisbasierte Steuerung und reagiert nicht dynamisch auf Signaländerungen im Sinne von IEC 61499. `AX_SEL_INT` kapselt diese Funktionalität ereignisgesteuert.
* **`AX_SEL_REAL`:** Identische Funktionsweise, jedoch speziell für den Fließkommadatentyp `REAL` ausgelegt, während `AX_SEL_INT` optimiert für ganzzahlige `INT`-Werte ist.

## Fazit

Der `AX_SEL_INT` ist ein robuster und wiederverwendbarer Baustein für die ereignisdiskrete Steuerungstechnik. Durch seine integrierte Filterung von redundanten Ereignissen trägt er maßgeblich zur Performance-Optimierung und Stabilität innerhalb von 4diac-basierten Laufzeitumgebungen bei.