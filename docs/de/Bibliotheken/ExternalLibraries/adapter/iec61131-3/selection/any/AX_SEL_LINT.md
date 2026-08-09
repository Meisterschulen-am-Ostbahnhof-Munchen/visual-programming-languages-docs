# AX_SEL_LINT




![AX_SEL_LINT](./AX_SEL_LINT.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_LINT` ist ein Standard-Auswahlbaustein (Selection Function Block) nach IEC 61131-3 für die binäre Auswahl zwischen zwei Eingangswerten des Datentyps `LINT` (Long Integer). Die Steuerung und Auswahl des aktiven Kanals erfolgt über ein standardisiertes Adapter-Interface. Der Baustein ist ereignisgesteuert und optimiert für den Einsatz in IEC 61499-Anwendungen innerhalb von 4diac IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Löst die Übernahme des Datenwerts von `IN0` aus.
* **EI1**: Löst die Übernahme des Datenwerts von `IN1` aus.

### **Ereignis-Ausgänge**

* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert, dass sich der ausgewählte Ausgangswert (`OUT`) geändert hat.

### **Daten-Eingänge**

* **IN0** (LINT): Erster auswählbarer Daten-Eingangswert.
* **IN1** (LINT): Zweiter auswählbarer Daten-Eingangswert.

### **Daten-Ausgänge**

* **OUT** (LINT): Der aktuell selektierte Ausgangswert.

### **Adapter**

* **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Er liefert das Schaltereignis (`E1`) und das Selektions-Datensignal (`D1`), welches bestimmt, welcher der Eingänge durchgeschaltet wird.

---

## Funktionsweise

Der Baustein `AX_SEL_LINT` kombiniert interne Speicher- und Selektionsfunktionen, um einen der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang `OUT` zu schalten:

1. **Datenerfassung:** Bei Eintreffen der Ereignisse `EI0` bzw. `EI1` werden die Werte an den Eingängen `IN0` und `IN1` über interne Event-D-Flip-Flops (`E_D_FF_ANY`) gepuffert.
2. **Selektion:** Der Adapter `G` fungiert als Steuerkanal. Trifft ein Ereignis auf `G.E1` ein, wird der boolesche Zustand von `G.D1` ausgewertet:
   * Ist der Zustand `FALSE` (0), wird der Wert von `IN0` ausgewählt.
   * Ist der Zustand `TRUE` (1), wird der Wert von `IN1` ausgewählt.
3. **Ausgabe-Filterung:** Der ausgewählte Wert wird an den Ausgang `OUT` übergeben. Ein Ausgangsereignis (`CNF`) wird über ein nachgeschaltetes Flip-Flop (`E_D_FF_ANY_OUT`) **nur dann** ausgelöst, wenn sich der Wert am Ausgang `OUT` tatsächlich verändert hat. Dadurch werden redundante Event-Kaskaden im Netzwerk vermieden.

---

## Technische Besonderheiten

* **Ereignis-Reduktion:** Ein Ausgangsereignis (`CNF`) wird nicht bei jedem Eingangsereignis generiert, sondern ausschließlich bei einer tatsächlichen Änderung des selektierten Ausgangswerts.
* **Adapter-Anbindung:** Durch die Kapselung der Selektionslogik in einem `AX`-Adapter wird die Signalverdrahtung im Applikationsdiagramm signifikant vereinfacht und übersichtlicher gestaltet.
* **Datentyp-Spezifisch:** Dieser Baustein verarbeitet dediziert 64-Bit Ganzzahlen (`LINT`).

---

## Zustandsübersicht

| Selektor-Zustand (`G.D1`) | Letztes aktives Ereignis | Ausgangswert (`OUT`) | Verhalten von `CNF` |
| :--- | :--- | :--- | :--- |
| `FALSE` | Beliebig | Entspricht `IN0` | Wird ausgelöst, wenn sich `IN0` ändert |
| `TRUE` | Beliebig | Entspricht `IN1` | Wird ausgelöst, wenn sich `IN1` ändert |
| Wechsel von `FALSE` auf `TRUE` | `G.E1` | Wechselt von `IN0` auf `IN1` | Wird ausgelöst, falls `IN0 != IN1` |
| Wechsel von `TRUE` auf `FALSE` | `G.E1` | Wechselt von `IN1` auf `IN0` | Wird ausgelöst, falls `IN0 != IN1` |

---

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Umschalten zwischen zwei verschiedenen Identifikationsnummern, Zählerständen oder großen Zeitstempeln (als `LINT` deklariert) in einer automatisierten Anlage.
* **Rezepturwechsel:** Auswahl zwischen vordefinierten Konfigurationsparametern im laufenden Betrieb über ein HMI (mittels des Selektor-Adapters).
* **Signal-Routing:** Dynamisches Routing von Datenströmen in ereignisgesteuerten Systemen.

---

## Vergleich mit ähnlichen Bausteinen

* **`F_SEL` (Standard-Auswahlbaustein):** Der klassische `F_SEL` besitzt keine integrierten Event-Eingänge zur Wertspeicherung und keinen Adapter-Anschluss. Er reagiert rein datenflussorientiert.
* **`AX_SEL_INT` / `AX_SEL_REAL`:** Identische Funktionsweise und Struktur, jedoch für die jeweiligen Datentypen `INT` (16-Bit) bzw. `REAL` (Gleitkommazahl) ausgelegt.

---

## Fazit

Der `AX_SEL_LINT` ist ein leistungsfähiger Hilfsbaustein für die strukturierte Programmierung in 4diac. Durch die Kombination aus ereignisbasierter Filterung und der übersichtlichen Adapter-Schnittstelle trägt er maßgeblich zur Erstellung sauberer, performanter und wartungsfreundlicher IEC 61499 Steuerungsanwendungen bei.