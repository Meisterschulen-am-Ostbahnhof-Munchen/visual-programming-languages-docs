# AX_SEL_DINT


![AX_SEL_DINT](./AX_SEL_DINT.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_DINT` dient zur binären Auswahl (Selektion) zwischen zwei Eingangswerten vom Typ `DINT` (Double Integer). Die Steuerung, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird, erfolgt über einen angeschlossenen Selektor-Adapter (`G`). Der Baustein ist für den Einsatz in ereignisgesteuerten Systemen gemäß dem IEC 61499-Standard optimiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Löst das Einlesen und Verarbeiten des Daten-Eingangs `IN0` aus.
*   **EI1**: Löst das Einlesen und Verarbeiten des Daten-Eingangs `IN1` aus.

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungsereignis (Confirmation). Es wird ausgegeben, um zu signalisieren, dass sich der ausgewählte Ausgangswert `OUT` aktualisiert hat.

### **Daten-Eingänge**

*   **IN0** (DINT): Erster auswählbarer Daten-Eingangswert. Wird an den Ausgang durchgereicht, wenn das Auswahlsignal des Adapters `G` den Zustand für den ersten Eingang vorgibt.
*   **IN1** (DINT): Zweiter auswählbarer Daten-Eingangswert. Wird an den Ausgang durchgereicht, wenn das Auswahlsignal des Adapters `G` den Zustand für den zweiten Eingang vorgibt.

### **Daten-Ausgänge**

*   **OUT** (DINT): Der aktuell ausgewählte Ausgangswert (entspricht entweder `IN0` oder `IN1`).

### **Adapter**

*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Über diesen Adapter wird das Steuersignal empfangen, welches bestimmt, welcher Eingang aktiv geschaltet wird.

---

## Funktionsweise

Der Baustein `AX_SEL_DINT` kapselt ein internes Netzwerk aus Hilfs-Funktionsbausteinen, um eine saubere ereignisgesteuerte Selektion zu realisieren:

1.  **Datenspeicherung und -weiterleitung**:
    *   Trifft ein Ereignis an `EI0` oder `EI1` ein, werden die entsprechenden Daten (`IN0` bzw. `IN1`) über interne D-Flipflops (`E_D_FF_ANY_IN0` / `E_D_FF_ANY_IN1`) zwischengespeichert und an die interne Selektionseinheit (`F_SEL`) weitergeleitet.
2.  **Auswahl-Logik via Adapter**:
    *   Über den Adapter-Eingang `G` wird sowohl das Datensignal für die Auswahl als auch das dazugehörige Trigger-Ereignis empfangen.
    *   Das Ereignis des Adapters (`G.E1`) triggert die Übernahme des Auswahlsignals (`G.D1`) im internen Flipflop `E_D_FF_G`.
    *   Der eigentliche Auswahlprozess wird durch den Standard-Baustein `F_SEL` durchgeführt. Ist das Auswahlsignal `False` (0), wird `IN0` gewählt. Ist es `True` (1), wird `IN1` gewählt.
3.  **Ereignisgenerierung am Ausgang**:
    *   Der ausgewählte Wert wird an das Ausgangs-Flipflop `E_D_FF_ANY_OUT` übergeben.
    *   Ein Ausgangsereignis an `CNF` wird nur dann generiert, wenn sich der ausgewählte Wert am Ausgang `OUT` tatsächlich ändert. Dies verhindert unnötige Folge-Ereignisse im System, wenn sich Werte ohne Relevanz aktualisieren.

---

## Technische Besonderheiten

*   **Ereignisfilterung**: Durch den Einsatz von `E_D_FF_ANY_OUT` am Ausgang wird sichergestellt, dass nachfolgende Programmteile nur bei einer echten Wertänderung am Ausgang getriggert werden.
*   **Adapter-Anbindung**: Die Verwendung des standardisierten, unidirektionalen Adapters `AX` vereinfacht die Verdrahtung in komplexen Systemen, da Steuerleitungen und zugehörige Ereignisse in einer einzigen Verbindung gebündelt werden.

---

## Zustandsübersicht

| Zustand des Selektors (G.D1) | Aktives Ereignis | Ausgangswert (OUT) |
| :--- | :--- | :--- |
| `0` (bzw. False) | `G.E1` / `EI0` / `EI1` | `IN0` |
| `1` (bzw. True) | `G.E1` / `EI0` / `EI1` | `IN1` |

*Hinweis: Ein Ausgangsereignis (`CNF`) wird bei einer Änderung des Ausgangswertes `OUT` generiert.*

---

## Anwendungsszenarien

*   **Sollwertumschaltung**: Umschalten zwischen einem Automatik-Sollwert (z. B. von einer übergeordneten Steuerung) und einem Hand-Sollwert (z. B. von einem HMI) in industriellen Anlagen oder landwirtschaftlichen Maschinen.
*   **Sensor-Redundanz**: Umschalten zwischen einem Haupt- und einem Ersatzsensor bei Ausfall oder zur Kalibrierung.
*   **Rezeptursteuerung**: Dynamische Auswahl unterschiedlicher Konfigurationsparameter im laufenden Betrieb.

---

## Vergleich mit ähnlichen Bausteinen

*   **Klassischer `SEL` (IEC 61131-3)**: Der Standard-Selektionsbaustein arbeitet rein datenflussorientiert und besitzt keine Ereignissteuerung. Er benötigt zudem ein direktes `BOOL`-Signal zur Auswahl.
*   **`AX_SEL_DINT`**: Bietet eine vollwertige ereignisgesteuerte Implementierung für die IEC 61499. Durch die Adapter-Schnittstelle `G` werden Steuer- und Datensignale sauber gekapselt, und der Baustein minimiert durch seine interne Logik die Ereignislast auf dem Steuerungsnetzwerk.

---

## Fazit

Der `AX_SEL_DINT`-Funktionsbaustein ist ein robuster und effizienter Baustein zur ereignisgesteuerten Signalumschaltung. Durch die Kapselung der Auswahl- und Speicherlogik sowie der Verwendung von Adaptern eignet er sich hervorragend für modulare und übersichtliche Systemarchitekturen in modernen Steuerungsumgebungen.