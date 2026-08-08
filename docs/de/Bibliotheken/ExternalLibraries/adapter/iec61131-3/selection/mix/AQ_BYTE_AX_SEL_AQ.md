# AQ_BYTE_AX_SEL_AQ


![AQ_BYTE_AX_SEL_AQ](./AQ_BYTE_AX_SEL_AQ.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AQ_BYTE_AX_SEL_AQ` ist ein binärer Selektor (Multiplexer) für Byte-Signale, der speziell für die Verwendung in IEC 61499-Systemen (wie Eclipse 4diac) entwickelt wurde. Er ermöglicht die ereignisgesteuerte Auswahl zwischen zwei Byte-Eingangsquellen basierend auf einem Selektionssignal. Der Baustein nutzt standardisierte, unidirektionale Adapter-Schnittstellen (`AQ` und `AX`), um Daten und Steuerereignisse effizient und sauber gekapselt zu übertragen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Löst die Aktualisierung und Übernahme des Datenwerts am lokalen Dateneingang `IN1` aus (gekoppelt mit `IN1`).

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge*. Die Ereignisausgabe erfolgt gekapselt über den Adapter-Plug **OUT** (`OUT.E1`).

### **Daten-Eingänge**

*   **IN1** (BYTE): Lokaler, auswählbarer Byte-Eingangswert.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge*. Die Datenausgabe erfolgt gekapselt über den Adapter-Plug **OUT** (`OUT.D1`).

### **Adapter**

*   **Plugs (Stecker):**
    *   **OUT** (Typ: `adapter::types::unidirectional::AQ`): Der ausgewählte Ausgangsadapter. Er gibt das selektierte Byte-Signal (`D1`) zusammen mit dem dazugehörigen Aktualisierungsereignis (`E1`) weiter.
*   **Sockets (Buchsen):**
    *   **IN0** (Typ: `adapter::types::unidirectional::AQ`): Der erste auswählbare Byte-Eingang über eine Adapterschnittstelle (entspricht dem Standard-Eingang bei Selektor = `FALSE`).
    *   **G** (Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter (Gate). Das hier anliegende boolesche Signal bestimmt, welcher Eingang auf den Ausgang durchgeschaltet wird.

---

## Funktionsweise

Das interne Netzwerk des `AQ_BYTE_AX_SEL_AQ` kombiniert klassische IEC 61131-3 Selektionslogik (`F_SEL`) mit der ereignisgesteuerten Ausführung der IEC 61499:

1.  **Datenerfassung und Synchronisation:**
    *   Die Eingangsdaten von `IN0` (Adapter), `IN1` (Direkteingang) und das Auswahlsignal `G` (Adapter) werden bei ankommenden Ereignissen (`IN0.E1`, `EI1`, `G.E1`) über Event-D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) gepuffert. Dies stellt sicher, dass die Datenwerte konsistent bleiben, bis die Selektion verarbeitet wird.
    *   Die gepufferten Daten werden mittels `F_MOVE`-Bausteinen an das zentrale Selektionsglied übergeben.
2.  **Selektionslogik (`F_SEL`):**
    *   Ist das Selektionssignal des Adapters `G` auf `FALSE`, wird der Wert von `IN0` ausgewählt.
    *   Ist das Selektionssignal des Adapters `G` auf `TRUE`, wird der Wert von `IN1` ausgewählt.
3.  **Ausgabe:**
    *   Der ausgewählte Wert wird an das D-Flip-Flop des Ausgangs (`E_D_FF_ANY_OUT`) übergeben.
    *   Nach erfolgreicher Selektion wird das Ereignis `OUT.E1` ausgelöst und der ausgewählte Byte-Wert an `OUT.D1` bereitgestellt.

```
          +-----------------------------------+
          |         AQ_BYTE_AX_SEL_AQ         |
          |                                   |
 (AQ) IN0 |==> [E_D_FF] --> [F_MOVE] ---\     |
          |                              +--> |
  (AX)  G |==> [E_D_FF] -------------> [F_SEL]==> OUT (AQ)
          |                              +--> |
      EI1 |--> [E_D_FF] --> [F_MOVE] ---/     |
      IN1 |--> [  ANY ]                       |
          +-----------------------------------+
```

---

## Technische Besonderheiten

*   **Ereignisentkopplung:** Durch den Einsatz von D-Flip-Flops für alle Eingänge führt jede Änderung an den Eingängen oder am Selektor zu einer konsistenten Aktualisierung des Ausgangs. Ein "Durchrutschen" von undefinierten Zuständen wird verhindert.
*   **Adapter-Anbindung:** Die Verwendung von unidirektionalen Adaptern (`AQ` für Analog-/Byte-Werte, `AX` für Binärwerte) reduziert den Verdrahtungsaufwand im übergeordneten Funktionsplan drastisch, da Daten und Ereignisse in einer einzigen Verbindung geführt werden.

---

## Zustandsübersicht

Die folgende Tabelle zeigt das Verhalten des Ausgangs `OUT` in Abhängigkeit des Selektors `G`:

| Zustand Selektor (`G.D1`) | Relevanter Eingang | Ausgangswert (`OUT.D1`) | Auslösendes Ereignis am Ausgang (`OUT.E1`) |
| :--- | :--- | :--- | :--- |
| **FALSE** | `IN0` (via Adapter) | Wert von `IN0.D1` | Trigger durch `IN0.E1` oder `G.E1` |
| **TRUE** | `IN1` (Direkteingang) | Wert von `IN1` | Trigger durch `EI1` oder `G.E1` |

---

## Anwendungsszenarien

*   **Hand-/Automatik-Umschaltung:** Umschaltung eines Byte-Sollwerts zwischen einem automatischen Prozesswert (geliefert über den Adapter `IN0`) und einem manuell vorgegebenen Byte-Wert (über den lokalen Eingang `IN1`, z. B. von einer Visualisierung).
*   **Signal-Routing in verteilten Systemen:** Dynamische Wegleitung von Byte-Datenströmen in Steuerungsnetzwerken, bei denen die Signale über standardisierte Adapterstrukturen übertragen werden.
*   **Sensor-Redundanz:** Umschalten zwischen einem primären Sensor-Byte und einem Ersatzwert bei Erkennung eines Fehlers über das Gate-Signal `G`.

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard `F_SEL` (IEC 61131-3):** Der Standard-Auswahlbaustein arbeitet rein datenflussorientiert und besitzt keine Ereignissteuerung oder Adapterunterstützung. `AQ_BYTE_AX_SEL_AQ` erweitert diese Funktionalität um die vollständige Event-Steuerung von IEC 61499 und kapselt die Signale in Adaptern.
*   **Standard `E_SEL`:** Dieser Baustein selektiert Ereignisse, führt jedoch keine byteweise Datenverarbeitung oder Adapterverwaltung durch.

---

## Fazit

Der `AQ_BYTE_AX_SEL_AQ` ist ein hochgradig modularer und robuster Baustein für die Signalsteuerung in modernen 4diac-Applikationen. Durch die konsequente Nutzung von Adaptern fügt er sich nahtlos in saubere Softwarearchitekturen ein und minimiert Fehlerquellen bei der ereignisgesteuerten Datenverarbeitung von Byte-Signalen.