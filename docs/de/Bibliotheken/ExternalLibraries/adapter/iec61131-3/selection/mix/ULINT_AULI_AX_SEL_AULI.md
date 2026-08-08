# ULINT_AULI_AX_SEL_AULI


![ULINT_AULI_AX_SEL_AULI](./ULINT_AULI_AX_SEL_AULI.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ULINT_AULI_AX_SEL_AULI` ist ein binärer Selektionsbaustein (Auswahlschalter) für vorzeichenlose 64-Bit-Ganzzahlen (`ULINT`). Er ermöglicht das Umschalten zwischen zwei Eingangswerten basierend auf dem Zustand eines Selektions-Adapters (`G`). Das Ergebnis wird über einen Ausgangs-Adapter (`OUT`) bereitgestellt. Der Baustein kombiniert klassische IEC 61131-3 Selektionslogik mit der ereignisgesteuerten Architektur von IEC 61499 unter Verwendung von Adaptern zur Reduzierung der Verdrahtungskomplexität.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- | :--- |
| **EI0** | Event | Signalisiert, dass ein neuer Wert für den statischen Dateneingang `IN0` vorliegt. | `IN0` |

### **Ereignis-Ausgänge**

*Dieser Baustein besitzt keine direkten, eigenständigen Ereignis-Ausgänge auf der Hauptebene. Die Ereignisweiterleitung erfolgt gekapselt über die Adapter.*

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | ULINT | Direkt anzubindende, auswählbare Eingangs-Variable (statisch). |

### **Daten-Ausgänge**

*Dieser Baustein besitzt keine direkten, eigenständigen Daten-Ausgänge auf der Hauptebene. Der selektierte Wert wird über den Adapter `OUT` ausgegeben.*

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::AULI` | Plug (Stecker) | Der ausgewählte Ausgangswert (Typ: `ULINT` inklusive Ereignissteuerung). |
| **IN1** | `adapter::types::unidirectional::AULI` | Socket (Buchse) | Der auswählbare Eingangswert über ein Adapter-Interface. |
| **G** | `adapter::types::unidirectional::AX` | Socket (Buchse) | Der Selektor (Steuersignal zur Auswahl zwischen `IN0` und `IN1`). |

---

## Funktionsweise

Der Baustein realisiert intern eine Multiplexer-Funktion (entspricht der Standard-Funktion `SEL`). 

1. **Ereignis- und Datenverarbeitung:**
   * Sobald ein Ereignis an einem der Eingänge (`EI0`, `IN1.E1` oder `G.E1`) eintrifft, werden die entsprechenden Datenwerte über interne D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert und synchronisiert.
   * Der interne Selektionsbaustein `F_SEL` wertet den Zustand des Selektors `G` aus.

2. **Auswahllogik:**
   * Ist der Selektor `G.D1` **FALSE (0)**, wird der Wert von **`IN0`** an den Ausgang weitergeleitet.
   * Ist der Selektor `G.D1` **TRUE (1)**, wird der Wert von **`IN1`** (über den Adapter geliefert) an den Ausgang weitergeleitet.

3. **Ausgabe:**
   * Nach erfolgter Auswahl wird der Wert über einen `F_MOVE`-Baustein an das Ausgangsregister übergeben.
   * Ein Trigger-Ereignis wird über den Ausgangs-Adapter `OUT.E1` gesendet, um nachfolgende Programmteile über die Datenänderung zu informieren.

---

## Technische Besonderheiten

* **Hybrid-Schnittstelle:** Der Baustein verbindet klassische Hardware-Pins (`IN0`, `EI0`) mit modernen, ereignisgesteuerten Kommunikationsadaptern (`IN1`, `G`, `OUT`). Dies erleichtert die strukturierte modulare Programmierung.
* **Flankengesteuerte Aktualisierung:** Jede Änderung an den Eingängen oder am Selektor führt durch die interne Event-Verschaltung unmittelbar zu einer Neuberechnung und Aktualisierung des Ausgangs.
* **Datentyp-Spezifisch:** Der Baustein ist fest für den Datentyp `ULINT` (64-Bit vorzeichenlos) ausgelegt, was eine hohe Präzision und einen großen Wertebereich garantiert.

---

## Zustandsübersicht

| Zustand Selector (`G.D1`) | Aktiviertes Ereignis | Resultierender Wert an `OUT.D1` | Generiertes Ausgangsereignis |
| :--- | :--- | :--- | :--- |
| **FALSE** | Beliebig (`EI0` / `G.E1` / `IN1.E1`) | **`IN0`** | `OUT.E1` |
| **TRUE** | Beliebig (`EI0` / `G.E1` / `IN1.E1`) | **`IN1.D1`** | `OUT.E1` |

---

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Wechsel zwischen einem manuell eingegebenen Standardwert (`IN0`) und einem automatisiert berechneten Wert, der über ein Bussystem oder ein anderes Modul (`IN1`) geliefert wird.
* **Redundante Sensorik:** Umschalten zwischen zwei Sensorkanälen bei Ausfall oder zur Kalibrierung.
* **Betriebsartenwahl:** Auswahl unterschiedlicher Konfigurationsparameter (als `ULINT` codiert) basierend auf dem aktuellen Anlagenzustand (Automatik/Handbetrieb).

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `SEL` aus der IEC 61131-3 benötigt dieser Baustein dank der integrierten Adapter-Strukturen deutlich weniger manuelle Verbindungen im 4diac-Funktionsplan. Während ein klassischer `SEL` alle Event-Leitungen separat benötigt, kapselt `ULINT_AULI_AX_SEL_AULI` die Ereignisse für die Eingänge und den Ausgang direkt in den Adaptern `IN1`, `G` und `OUT`.

---

## Fazit

Der `ULINT_AULI_AX_SEL_AULI` ist ein spezialisierter und hocheffizienter Baustein zur Signal- und Datenflusssteuerung in komplexen IEC 61499-Anwendungen. Durch die konsequente Nutzung von Unidirectional-Adaptern sorgt er für saubere, übersichtliche und wartungsfreundliche Applikationsnetzwerke in der 4diac IDE.