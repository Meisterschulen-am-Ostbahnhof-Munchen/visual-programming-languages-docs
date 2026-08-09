# AX_SEL_LWORD


![AX_SEL_LWORD](./AX_SEL_LWORD.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_LWORD` dient der binären Auswahl (Selektion) zwischen zwei `LWORD`-Eingangswerten (`IN0` und `IN1`). Die Steuerung, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird, erfolgt über einen Adapter-Eingang `G` vom Typ `AX`. Dieser Baustein basiert auf der klassischen Auswahlfunktion (Selection) der Norm IEC 61131-3 und bereitet diese für die ereignisgesteuerte Ausführung in IEC 61499-Umgebungen wie 4diac-ide vor.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **`EI0`**: Signalisiert, dass der Eingangswert `IN0` aktualisiert bzw. neu gesetzt wurde.
* **`EI1`**: Signalisiert, dass der Eingangswert `IN1` aktualisiert bzw. neu gesetzt wurde.

### **Ereignis-Ausgänge**

* **`CNF`**: Bestätigungsereignis (Confirmation). Signalisiert dem nachfolgenden Netzwerk, dass ein neuer ausgewählter Wert am Datenausgang `OUT` anliegt.

### **Daten-Eingänge**

* **`IN0` (`LWORD`)**: Erster auswählbarer Daten-Eingangswert (aktiv, wenn das Selektionssignal `G` logisch `FALSE` ist).
* **`IN1` (`LWORD`)**: Zweiter auswählbarer Daten-Eingangswert (aktiv, wenn das Selektionssignal `G` logisch `TRUE` ist).

### **Daten-Ausgänge**

* **`OUT` (`LWORD`)**: Der aktuell selektierte Daten-Ausgangswert.

### **Adapter**

* **`G` (Typ: `adapter::types::unidirectional::AX`)**: Unidirektionaler Adapter-Socket, der als Selektor fungiert. Über diesen Adapter wird das Umschaltsignal empfangen.

## Funktionsweise

Das interne Netzwerk des `AX_SEL_LWORD` verarbeitet die Ereignisse und Daten flanken- und wertgesteuert:
1. **Ereignisverarbeitung**: Wenn an `EI0` oder `EI1` ein Ereignis eintrifft, wird der zugehörige Datenwert (`IN0` oder `IN1`) über interne Flip-Flops (`E_D_FF_ANY`) gepuffert und an den Kern-Selektionsbaustein (`F_SEL`) übergeben.
2. **Adapter-Auswahl**: Ereignisse am Adapter `G` (Ereignis `E1`) triggern das interne Flip-Flop `E_D_FF_G` mit dem Datenwert `D1`. Dies steuert den Wahleingang des internen Selektors.
3. **Ausgabe und Filterung**: Der ausgewählte Wert wird an den Ausgang `OUT` angelegt. Ein Ausgangsereignis an `CNF` wird über ein nachgeschaltetes `E_D_FF_ANY` nur dann generiert, wenn sich der Zustand des Selektors `G` ändert oder eine tatsächliche Wertänderung am Ausgang stattfindet.

## Technische Besonderheiten

* **Datentyp**: Der Baustein ist speziell auf den 64-Bit-Datentyp `LWORD` ausgelegt.
* **Ereignis-Optimierung**: Ein Ausgangsereignis (`CNF`) wird vorrangig bei einer Änderung des Selektions-Adapters `G` oder bei einer echten Änderung des Ausgangswertes erzeugt, um unnötige Ereigniskaskaden im System zu minimieren.
* **Einfache Verdrahtung**: Durch die Nutzung des standardisierten `AX`-Adapters wird die Anzahl der expliziten Verbindungslinien im Applikations-Editor reduziert.

## Zustandsübersicht

| Zustand des Selektors `G` | Relevanter Ereignis-Eingang | Ausgangswert `OUT` | Ereignis-Ausgang `CNF` |
|:---|:---|:---|:---|
| `FALSE` (0) | `EI0` | `IN0` | Wird bei Wertänderung ausgelöst |
| `TRUE` (1) | `EI1` | `IN1` | Wird bei Wertänderung ausgelöst |
| Signalwechsel auf `G` | `G.E1` | Wechselt auf den neu selektierten Eingang | Wird ausgelöst |

## Anwendungsszenarien

* **Signalumschaltung**: Auswahl zwischen zwei redundanten Signalquellen (z. B. primärer und sekundärer Datenbus) auf Basis eines globalen Systemstatus.
* **Modus-Umschaltung**: Laden von unterschiedlichen 64-Bit-Konfigurationsregistern oder Bitmasken je nach Betriebsmodus (z. B. Automatik- vs. Handbetrieb).
* **Daten-Routing**: Dynamisches Weiterleiten von Datenströmen in verteilten Steuerungssystemen.

## Vergleich mit ähnlichen Bausteinen

* **`F_SEL` (IEC 61131-3)**: Der Standard-Auswahlbaustein `F_SEL` arbeitet rein datenflussorientiert. `AX_SEL_LWORD` erweitert diese Funktionalität um das ereignisbasierte Ausführungsmodell von IEC 61499 und bindet die Steuerung über einen komfortablen Adapter an.
* **`AX_SEL` für andere Datentypen** (z. B. `AX_SEL_DWORD`): Diese besitzen dieselbe funktionale Struktur, sind jedoch für kleinere Bitbreiten (z. B. 32-Bit) dimensioniert.

## Fazit

`AX_SEL_LWORD` ist ein spezialisierter und optimierter Funktionsbaustein zur sicheren, ereignisgesteuerten Auswahl von 64-Bit-Datenwerten. Dank der Adapteranbindung integriert er sich nahtlos und übersichtlich in komplexe 4diac-Applikationen.