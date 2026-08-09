# AUS_USINT_AX_SEL_AUS


![AUS_USINT_AX_SEL_AUS](./AUS_USINT_AX_SEL_AUS.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUS_USINT_AX_SEL_AUS` dient zur binären Auswahl (Selektion) zwischen zwei Eingangssignalen des Datentyps `USINT` (Unsigned Short Integer). Die Auswahl erfolgt ereignisgesteuert über ein Selektionssignal. Der Baustein nutzt unidirektionale Adapter, um Daten und Ereignisse modular und strukturiert zu verarbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Löst die Übernahme und Verarbeitung des direkt anliegenden Daten-Eingangs `IN1` aus.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge.* (Die Ereignisausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`).

### **Daten-Eingänge**

*   **IN1** (USINT): Direkt anliegende auswählbare Eingangsvariable.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge.* (Die Datenausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`).

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AUS`): Der ausgewählte Ausgangswert (`USINT`) und das dazugehörige Bestätigungsereignis.
*   **IN0** (Socket, Typ: `adapter::types::unidirectional::AUS`): Der erste auswählbare Eingangswert (`USINT`), der über einen Adapter eingespeist wird.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Das Selektionssignal (Gate), welches bestimmt, welcher Eingang auf den Ausgang geschaltet wird.

---

## Funktionsweise

Der Funktionsbaustein arbeitet intern mit einer Kombination aus D-Flip-Flops (`E_D_FF_ANY` bzw. `E_D_FF`) und Standard-Auswahlbausteinen (`F_SEL`). Die interne Verarbeitung läuft wie folgt ab:

1.  **Wertpufferung**: 
    *   Trifft ein Ereignis am Adapter `IN0` (`IN0.E1`) ein, wird der Wert `IN0.D1` im Flip-Flop `E_D_FF_ANY_IN0` gepuffert und an den Selektor weitergeleitet.
    *   Trifft das Ereignis `EI1` ein, wird der direkt anstehende Wert `IN1` im Flip-Flop `E_D_FF_ANY_IN1` gepuffert.
    *   Trifft ein Ereignis am Selektor-Adapter `G` (`G.E1`) ein, wird das Auswahlsignal `G.D1` im Flip-Flop `E_D_FF` gepuffert.
2.  **Auswahllogik (`F_SEL`)**:
    *   Ist das Selektionssignal am Adapter `G` **FALSE** (0), wird der Wert von `IN0` ausgewählt.
    *   Ist das Selektionssignal am Adapter `G` **TRUE** (1), wird der Wert von `IN1` ausgewählt.
3.  **Ausgabe**:
    *   Der ausgewählte Wert wird an den Ausgangs-Adapter `OUT` übergeben.
    *   Gleichzeitig wird ein Ausgangsereignis am Adapter `OUT` (`OUT.E1`) generiert, um nachfolgende Bausteine über die Datenänderung zu informieren.

---

## Technische Besonderheiten

*   **Mischbetrieb von Schnittstellen**: Der Baustein kombiniert klassische IEC 61499 Event-/Daten-Schnittstellen (`EI1` / `IN1`) mit modernen, unidirektionalen Adaptern (`IN0`, `G`, `OUT`).
*   **Datensicherheit durch Event-Kopplung**: Durch den Einsatz interner D-Flip-Flops wird sichergestellt, dass Datenwerte nur bei einem entsprechenden Event-Trigger übernommen und verarbeitet werden. Dies verhindert Dateninkonsistenzen (Race Conditions).

---

## Zustandsübersicht

| Zustand des Selektors (`G.D1`) | Ausgewählter Ausgang (`OUT.D1`) | Triggerndes Ereignis |
| :--- | :--- | :--- |
| **FALSE** | Wert von `IN0.D1` | `IN0.E1` oder `G.E1` |
| **TRUE** | Wert von `IN1` | `EI1` oder `G.E1` |

---

## Anwendungsszenarien

*   **Umschaltung zwischen Automatik- und Handwert**: Auswahl eines Sollwerts (z. B. eine Drehzahl oder ein Schrittindex als `USINT`) zwischen einem automatischen Prozesswert (`IN0` über Adapter) und einem manuell vorgegebenen Wert (`IN1`).
*   **Signal-Multiplexing**: Flexible Weiterleitung von Status- oder Steuerungscodes in dezentralen Steuerungssystemen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Funktionsbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet dieser Baustein eine vollständige Kapselung für die IEC 61499. Während der Standard-`F_SEL` rein datenflussorientiert arbeitet, integriert `AUS_USINT_AX_SEL_AUS` eine ereignisgesteuerte Zustandsspeicherung und nutzt Adapter, was die Verkabelung im 4diac-IDE Application Editor erheblich vereinfacht und übersichtlicher gestaltet.

---

## Fazit

Der `AUS_USINT_AX_SEL_AUS` ist ein robuster Hilfsbaustein für die strukturierte Signal- und Datenflusssteuerung. Durch die Nutzung von unidirektionalen Adaptern eignet er sich hervorragend für modulare und saubere Softwarearchitekturen in der industriellen Automatisierungstechnik.