# UINT_AUI_AX_SEL_AUI


![UINT_AUI_AX_SEL_AUI](./UINT_AUI_AX_SEL_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `UINT_AUI_AX_SEL_AUI` ist ein binärer Selektor (Auswahlbaustein), der ereignisgesteuert zwischen zwei Eingangssignalen wählt und das Ergebnis an einen Ausgang weiterleitet. Das Besondere an diesem Baustein ist die Kombination aus klassischen IEC 61499-Schnittstellen (Standarddaten und -ereignisse) und adapterbasierten Verbindungen. Dies ermöglicht eine nahtlose Integration und saubere Strukturierung von Signalflüssen in komplexen Steuerungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Löst die Übernahme und Aktualisierung des direkt anliegenden Daten-Eingangs `IN0` aus. (Verknüpft mit `IN0`).

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge vorhanden.* (Die Ereignisweiterleitung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`).

### **Daten-Eingänge**

*   **IN0** (UINT): Auswählbarer Eingangskanal 0 (Standard-Datenvariable).

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge vorhanden.* (Die Datenweitergabe erfolgt über den Ausgangs-Adapter `OUT`).

### **Adapter**

*   **IN1** (Socket, Typ `adapter::types::unidirectional::AUI`): Auswählbarer Eingangskanal 1 via Adapter-Verbindung.
*   **G** (Socket, Typ `adapter::types::unidirectional::AX`): Der Selektor-Eingang via Adapter. Bestimmt, welcher der beiden Kanäle auf den Ausgang durchgeschaltet wird.
*   **OUT** (Plug, Typ `adapter::types::unidirectional::AUI`): Der selektierte Ausgangs-Adapter, welcher das ausgewählte Signal und das dazugehörige Ereignis weiterleitet.

---

## Funktionsweise

Der Baustein basiert intern auf einem Netzwerk aus Standard-Auswahl- und Speicherbausteinen:

1.  **Latching (Signalspeicherung):** 
    Die Eingangssignale (`IN0`, `IN1` und der Selektor `G`) werden bei Eintreffen ihrer jeweiligen Ereignisse (`EI0`, `IN1.E1` oder `G.E1`) über interne D-Flipflops (`E_D_FF` / `E_D_FF_ANY`) zwischengespeichert. Dies stellt sicher, dass die Werte bis zur nächsten expliziten Aktualisierung stabil bleiben.
2.  **Wertübertragung:**
    Über interne `F_MOVE`-Bausteine werden die gepufferten Werte an den zentralen Auswahlbaustein `F_SEL` übergeben.
3.  **Auswahllogik (Selection):**
    Der Baustein `F_SEL` schaltet das Signal basierend auf dem Zustand des Selektors `G` durch:
    *   Ist `G` **FALSE** (0), wird der Wert von Kanal `IN0` gewählt.
    *   Ist `G` **TRUE** (1), wird der Wert von Kanal `IN1` gewählt.
4.  **Ausgabe:**
    Der ausgewählte Wert wird an das Ausgangs-D-Flipflop `E_D_FF_ANY_OUT` übergeben, welches schließlich den Adapter-Plug `OUT` (Datenwert `D1` und Ereignis `E1`) triggert.

```
       +--------------------------------------------+
       |             UINT_AUI_AX_SEL_AUI            |
       |                                            |
EI0 ---> [E_D_FF]                                   |
IN0 ---> [ IN0  ] -------\                          |
                         +---> [ F_SEL ] ---> OUT   |
IN1 ---> [  IN1 ] -------/       ^                  |
(AUI)  |                         |                  |
       |                         |                  |
  G ---> [   G  ] ---------------/                  |
 (AX)  |                                            |
       +--------------------------------------------+
```

---

## Technische Besonderheiten

*   **Mischbetrieb von Schnittstellen:** Der Baustein fungiert als Brücke zwischen der klassischen IEC 61499-Ereignis-/Datenwelt (`IN0`/`EI0`) und modernen, adapterbasierten Verbindungskonzepten.
*   **Ereignisentkopplung:** Durch die interne Pufferung führt nicht jede minimale Schwankung an den Eingängen zu unkontrollierten Zustandsänderungen. Erst das entsprechende Ereignis validiert den neuen Wert.
*   **Konsistenz:** Da alle Pfade über D-Flipflops synchronisiert sind, ist sichergestellt, dass Daten und Ereignisse am Ausgang `OUT` stets konsistent anliegen.

---

## Zustandsübersicht

| Selektor-Zustand (`G`) | Gewählter Eingang | Signal am Ausgang `OUT` | Triggerung von `OUT.E1` bei... |
| :--- | :--- | :--- | :--- |
| **FALSE** (0) | `IN0` (Standard-Eingang) | Wert von `IN0` | Ereignis auf `EI0` oder Änderung von `G` |
| **TRUE** (1) | `IN1` (Adapter-Eingang) | Wert von `IN1` | Ereignis `IN1.E1` oder Änderung von `G` |

---

## Anwendungsszenarien

*   **Hand-/Automatik-Umschaltung:** Ein Prozesswert kann entweder manuell über ein lokales HMI (vorgegeben an `IN0`) oder automatisiert über ein Bussystem / eine überlagerte Steuerung (geliefert über den Adapter `IN1`) vorgegeben werden. Der Selektor `G` schaltet zwischen den Modi um.
*   **Parametrierbare Standardwerte:** Vorgabe eines Default-Werts direkt an `IN0` für den Initialisierungs- oder Fehlerfall, während im Normalbetrieb dynamische Daten über den Adapter `IN1` eingespielt werden.
*   **Redundante Signalpfade:** Umschalten auf einen Ersatzkanal beim Ausfall eines Primärsensors.

---

## Vergleich mit ähnlichen Bausteinen

*   **`F_SEL` (Standard-Selektor):** Arbeitet rein wertbasiert und besitzt keine integrierte Ereignissteuerung oder Adapter-Unterstützung.
*   **Standard-Multiplexer (`MUX`):** Erlauben meist das Umschalten vieler Kanäle, bieten jedoch keine native Integration von unidirektionalen Adaptern wie `AUI` und `AX`.

---

## Fazit

Der `UINT_AUI_AX_SEL_AUI` ist ein extrem nützlicher Hilfsbaustein für modulare 4diac-Architekturen. Er vereinfacht das Signalrouting bei der Verwendung von Adaptern und garantiert durch seine interne ereignisgesteuerte Speicherarchitektur eine robuste und deterministische Signalverarbeitung.