# AX_SEL_UDINT


![AX_SEL_UDINT](./AX_SEL_UDINT.svg)

![AX_SEL_UDINT Funktionsblock](https://via.placeholder.com/150 "AX_SEL_UDINT Blockdiagramm") *(Bild des Funktionsblocks Platzhalter)*

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AX_SEL_UDINT` dient der binären Auswahl (Selektion) zwischen zwei Eingangssignalen des Datentyps `UDINT` (Unsigned Double Integer). Die Steuerung, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird, erfolgt über einen dedizierten Adapter-Eingang. Dieser Baustein basiert auf dem IEC 61131-3 Standard für Selektionsfunktionen und ist speziell für den Einsatz in IEC 61499-Umgebungen (wie 4diac IDE) konzipiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Aktualisiert und übernimmt den Wert des Daten-Eingangs `IN0`.
*   **EI1**: Aktualisiert und übernimmt den Wert des Daten-Eingangs `IN1`.

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungsereignis (Confirmation). Es wird ausgegeben, sobald der ausgewählte Wert am Ausgang `OUT` erfolgreich aktualisiert wurde. *(Hinweis: Ein Ausgangsereignis wird primär dann erzeugt, wenn sich der Zustand des Selektors G ändert).*

### **Daten-Eingänge**

*   **IN0** (UDINT): Erster auswählbarer Datenkanal.
*   **IN1** (UDINT): Zweiter auswählbarer Datenkanal.

### **Daten-Ausgänge**

*   **OUT** (UDINT): Der aktuell selektierte Datenwert.

### **Adapter**

*   **G** (Typ: `adapter::types::unidirectional::AX`): Empfänger-Adapter (Socket), welcher das Auswahlsignal bereitstellt. Die darin enthaltenen Daten und Ereignisse steuern das Umschalten zwischen `IN0` und `IN1`.

---

## Funktionsweise

Der Funktionsblock `AX_SEL_UDINT` arbeitet intern als Netzwerk aus mehreren elementaren Funktionsblöcken. Die Auswahlsteuerung läuft wie folgt ab:

1.  **Wertübernahme**: Die Eingänge `IN0` und `IN1` werden bei Eintreffen ihrer jeweiligen Ereignisse (`EI0` bzw. `EI1`) über Event-D-Flip-Flops (`E_D_FF_ANY`) zwischengespeichert und an die internen Zuweisungsblöcke (`F_MOVE`) weitergeleitet.
2.  **Selektion**: Der Adapter `G` liefert das Steuersignal. Das Ereignis `G.E1` triggert die Übernahme des Auswahlsignals `G.D1` über ein Flip-Flop (`E_D_FF_G`).
    *   Ist das Auswahlsignal am Adapter **FALSCH** (0), wird der Wert von `IN0` auf `OUT` geschaltet.
    *   Ist das Auswahlsignal am Adapter **WAHR** (1), wird der Wert von `IN1` auf `OUT` geschaltet.
3.  **Ausgabe**: Das Ergebnis wird über das interne Selektionsglied `F_SEL` an den Ausgang `OUT` übergeben, gefolgt von der Auslösung des `CNF`-Events.

---

## Technische Besonderheiten

*   **Composite FB-Netzwerk**: Der Baustein ist intern als Netzwerk realisiert und verwendet Standard-IEC-61131-Funktionen wie `F_SEL` und `F_MOVE`.
*   **Adapter-Kopplung**: Die Umschaltung erfolgt nicht über ein klassisches boolesches Datenfeld, sondern elegant und modular über ein Adapter-Interface (`AX`). Dies vereinfacht die Verdrahtung in komplexen Applikationen.
*   **Ereignisgesteuertes Verhalten**: Ein Ausgangsereignis (`CNF`) wird bei einer Änderung des Selektionszustands (`G`) zuverlässig getriggert, um nachfolgende Programmteile über die Umschaltung zu informieren.

---

## Zustandsübersicht

Die Selektion verhält sich gemäß der folgenden Wahrheitstabelle:

| Zustand Adapter `G` (Daten `D1`) | Aktiver Eingang | Wert an `OUT` |
| :--- | :--- | :--- |
| **FALSE** | `IN0` | Wert von `IN0` |
| **TRUE** | `IN1` | Wert von `IN1` |

---

## Anwendungsszenarien

*   **Sollwert-Umschaltung**: Wechseln zwischen einem Automatik-Sollwert (z.B. von einem Profilgenerator) und einem Hand-Sollwert (z.B. von einer HMI), die beide als `UDINT` vorliegen.
*   **Rezeptursteuerung**: Auswahl zwischen verschiedenen Parametersätzen oder Grenzwerten basierend auf Maschinenzuständen, die über den Adapter `G` signalisiert werden.
*   **Fehlersicherer Standardwert**: Umschalten auf einen sicheren Ersatzwert (`IN0`), falls ein Sensorwert (`IN1`) ungültig wird.

---

## Vergleich mit ähnlichen Bausteinen

*   **F_SEL (Standard)**: Der klassische `F_SEL`-Baustein besitzt direkt einen booleschen Eingang `G` zur Auswahl. `AX_SEL_UDINT` kapselt diese Logik und nutzt stattdessen ein standardisiertes Adapter-Interface, was die Wiederverwendbarkeit und Übersichtlichkeit im Systemdesign erhöht.
*   **AX_SEL (andere Datentypen)**: Es existieren analoge Bausteine für andere Datentypen (z.B. `AX_SEL_REAL`, `AX_SEL_INT`). `AX_SEL_UDINT` ist strikt auf den Datentyp `UDINT` typisiert, um Typsicherheit in der IEC 61499 zu gewährleisten.

---

## Fazit

Der `AX_SEL_UDINT` Funktionsblock bietet eine saubere, adapterbasierte Lösung zur binären Signalwahl für `UDINT`-Datenströme. Durch die Integration des Adapters eignet er sich hervorragend für modulare Steuerungsarchitekturen, bei denen Auswahlsignale gebündelt und ereignisgesteuert übergeben werden sollen.