# AX_SEL_STRING


![AX_SEL_STRING](./AX_SEL_STRING.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_STRING` dient zur binären Auswahl (Selektion) zwischen zwei Zeichenketten (`STRING`). Er basiert auf dem Standard IEC 61131-3 für Selektionsfunktionen und ist für die ereignisorientierte Ausführung in 4diac (IEC 61499) angepasst. Die Auswahl, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird, erfolgt über einen unidirektionalen Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Löst das Einlesen und Verarbeiten des Daten-Eingangs `IN0` aus.
* **EI1**: Löst das Einlesen und Verarbeiten des Daten-Eingangs `IN1` aus.

### **Ereignis-Ausgänge**

* **CNF**: Bestätigungsereignis (Confirmation). Wird gesendet, wenn ein neuer ausgewählter Wert am Ausgang `OUT` bereitgestellt wurde.

### **Daten-Eingänge**

* **IN0** (STRING): Der erste auswählbare Eingangswert. Dieser wird an den Ausgang weitergegeben, wenn das Selektionssignal den Zustand `FALSE` aufweist.
* **IN1** (STRING): Der zweite auswählbare Eingangswert. Dieser wird an den Ausgang weitergegeben, wenn das Selektionssignal den Zustand `TRUE` aufweist.

### **Daten-Ausgänge**

* **OUT** (STRING): Der aktuell ausgewählte Ausgangswert (`IN0` oder `IN1`).

### **Adapter**

* **G** (Typ: `adapter::types::unidirectional::AX`): Ein unidirektionaler Adapter, der das Selektionssignal liefert. Über diesen Adapter wird gesteuert, welcher der beiden Dateneingänge aktiv geschaltet wird.

## Funktionsweise

Im internen Netzwerk von `AX_SEL_STRING` werden die Eingangsdaten über Speicherglieder (`E_D_FF_ANY`) gepuffert. 

1. **Eingangsereignisse**: Sobald ein Ereignis an `EI0` oder `EI1` ankommt, wird der jeweilige String (`IN0` bzw. `IN1`) intern aktualisiert.
2. **Adaptersteuerung**: Der Adapter `G` liefert das Steuersignal. Bei einer Änderung des Adapterzustands (Ereignis `E1` am Adapter `G`) wird der Selektionswert aktualisiert.
3. **Auswahl**: Der interne Standardbaustein `F_SEL` entscheidet anhand des Zustands von `G.D1` (Datenleitung des Adapters), welcher Wert an den Ausgang weitergegeben wird:
   - Ist der Zustand des Selektors `G` `FALSE`, wird der Wert von `IN0` durchgeschaltet.
   - Ist der Zustand des Selektors `G` `TRUE`, wird der Wert von `IN1` durchgeschaltet.
4. **Ereignisfilterung**: Am Ausgang des Bausteins wacht ein `E_D_FF_ANY`-Glied darüber, ob sich der Wert an `OUT` tatsächlich geändert hat. Nur bei einer reellen Änderung des Ausgangswertes wird ein `CNF`-Ausgangsereignis ausgelöst.

## Technische Besonderheiten

* **Ereignis-Optimierung**: Ein Ausgangsereignis (`CNF`) wird nur dann generiert, wenn sich der ausgewählte Zustand am Ausgang tatsächlich ändert (z. B. durch ein Umschalten des Selektors `G` oder durch eine Änderung des aktiven Eingangswerts). Statische Aktualisierungen ohne Wertänderung triggern kein unnötiges Ausgangsereignis.
* **Adapter-Kopplung**: Die Verwendung des `AX`-Adapters ermöglicht eine elegante, lose Kopplung der Selektionslogik im Gesamtsystem, ohne direkte Bool'sche Datenleitungen quer durch das Anwendungsdiagramm ziehen zu müssen.

## Zustandsübersicht

Die nachfolgende Tabelle zeigt die logische Zuordnung des Ausgangs in Abhängigkeit des Adapter-Zustands:

| Zustand des Selektors (G.D1) | Ausgangswert (OUT) |
| :--- | :--- |
| `FALSE` / `0` | Entspricht dem Wert von `IN0` |
| `TRUE` / `1` | Entspricht dem Wert von `IN1` |

## Anwendungsszenarien

* **HMI-Textumschaltung**: Dynamische Auswahl zwischen zwei Statusmeldungen oder Anzeigetexten basierend auf einem Systemzustand (z. B. "BETRIEB" vs. "STÖRUNG").
* **Rezepturverwaltung**: Umschalten von Rezeptur- oder Produktnamen im String-Format beim Wechsel von Betriebsmodi.
* **Mehrsprachigkeit**: Einfache Umschaltung von Oberflächentexten zwischen zwei Sprachen über ein zentrales Steuersignal.

## Vergleich mit ähnlichen Bausteinen

* **F_SEL (IEC 61131-3)**: Der Standard-Auswahlbaustein benötigt ein direktes `BOOL`-Signal zur Auswahl und besitzt keine inhärente Ereignissteuerung. `AX_SEL_STRING` kapselt diese Funktionalität ereignisbasiert und nutzt einen Adapter zur Steuerung.
* **AX_SEL_INT / AX_SEL_REAL**: Diese Bausteine arbeiten nach demselben Prinzip, sind jedoch auf numerische Datentypen ausgelegt, während `AX_SEL_STRING` speziell für die Verarbeitung von Zeichenketten (`STRING`) optimiert ist.

## Fazit

`AX_SEL_STRING` ist ein spezialisierter und effizienter Hilfsbaustein für IEC 61499-Anwendungen, der eine saubere Trennung von Steuerungslogik und Datenfluss bei der Arbeit mit Zeichenketten ermöglicht. Durch die integrierte Ereignisfilterung schont er Systemressourcen, indem er redundante Folge-Berechnungen im Steuerungsnetzwerk minimiert.