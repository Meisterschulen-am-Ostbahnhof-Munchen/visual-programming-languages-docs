# AX_BOOL_AX_SEL_AX


![AX_BOOL_AX_SEL_AX](./AX_BOOL_AX_SEL_AX.svg)

*Kein Bild vorhanden*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_BOOL_AX_SEL_AX` dient der binären Auswahl (Selektion) zwischen zwei booleschen Signalquellen. Das Besondere an diesem Baustein ist die nahtlose Kombination aus klassischen IEC 61499-Ereignissen/Daten und spezialisierten unidirektionalen Adaptern vom Typ `AX`. Er ermöglicht es, ein Signal entweder aus einem Adapter-Eingang (`IN0`) oder einem lokalen Daten-Eingang (`IN1`) auszuwählen und an einen Adapter-Ausgang (`OUT`) weiterzuleiten. Die Steuerung, welches Signal durchgeschaltet wird, erfolgt über einen Selektor-Adapter (`G`).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Löst die Übernahme und Verarbeitung des Werts am Daten-Eingang `IN1` aus.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge vorhanden.* (Die Ereignisausgabe erfolgt gekoppelt über den Adapter-Ausgang `OUT`).

### **Daten-Eingänge**

*   **IN1** (BOOL): Auswählbare Eingangsvariable, die mit dem Ereignis `EI1` verknüpft ist.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge vorhanden.* (Die Datenausgabe erfolgt gekoppelt über den Adapter-Ausgang `OUT`).

### **Adapter**

*   **Sockets (Eingangs-Adapter)**:
    *   **IN0** (Typ: `adapter::types::unidirectional::AX`): Adapterbasierter Signaleingang, der den ersten auswählbaren Wert liefert.
    *   **G** (Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter. Der Zustand dieses Adapters bestimmt, welcher Eingang auf den Ausgang geschaltet wird.
*   **Plugs (Ausgangs-Adapter)**:
    *   **OUT** (Typ: `adapter::types::unidirectional::AX`): Der ausgewählte Ausgang, an den das selektierte Signal weitergeleitet wird.

---

## Funktionsweise

Der Baustein basiert intern auf einem Netzwerk, das den IEC 61131-3 Standard-Auswahlbaustein `F_SEL` sowie verschiedene Flip-Flops (`E_D_FF`, `E_D_FF_ANY`) zur Ereignis- und Zustandssynchronisation nutzt.

Die Logik verhält sich wie folgt:
1.  **Zustandserfassung**: Sobald an den Adaptern `G` oder `IN0` ein neues Ereignis (`E1`) anliegt, wird der zugehörige Datenwert (`D1`) über ein internes Flip-Flop zwischengespeichert.
2.  **Manuelle Triggerung**: Trifft am Ereigniseingang `EI1` ein Signal ein, wird der aktuelle Wert des Dateneingangs `IN1` erfasst.
3.  **Auswahl-Logik (F_SEL)**:
    *   Ist der Zustand des Selektors `G` gleich **`FALSE`**, wird das Signal des Adapters **`IN0`** an den Ausgang durchgereicht.
    *   Ist der Zustand des Selektors `G` gleich **`TRUE`**, wird das Signal des Eingangs **`IN1`** an den Ausgang durchgereicht.
4.  **Ausgabe**: Jede Änderung an den Eingängen führt zu einer Aktualisierung am Ausgangs-Adapter `OUT`. Dabei wird das Ereignis `OUT.E1` getriggert und der ausgewählte Zustand an `OUT.D1` übergeben.

---

## Technische Besonderheiten

*   **Hybrid-Ansatz**: Der Baustein schließt die Lücke zwischen klassischer ereignis- und datenbasierter IEC 61499-Programmierung (über `EI1`/`IN1`) und moderner, adapterbasierter Signalverdrahtung.
*   **Signalstabilität**: Durch den Einsatz interner Event-D-Flip-Flops (`E_D_FF` / `E_D_FF_ANY`) wird sichergestellt, dass Signaländerungen nur bei entsprechenden Ereignissen übernommen werden. Dies verhindert unkontrollierte Signalzustände ("Glitsches") bei asynchronen Datenänderungen.

---

## Zustandsübersicht

Die folgende Wahrheitstabelle beschreibt das Verhalten der Auswahl-Logik:

| Zustand Selektor (G) | Signalquelle IN0 | Signalquelle IN1 | Ausgang (OUT) |
| :--- | :--- | :--- | :--- |
| **FALSE** | Wert A | Wert B | **Wert A** (von IN0) |
| **TRUE** | Wert A | Wert B | **Wert B** (von IN1) |

---

## Anwendungsszenarien

*   **Automatik-/Handbetrieb-Umschaltung**: Ein Steuerungssignal wird standardmäßig automatisiert über den Adapter `IN0` bezogen. Bei Bedarf (z. B. Wartung oder manueller Eingriff) schaltet der Selektor `G` um, sodass ein manueller Wert über `IN1` (getriggert durch eine HMI an `EI1`) vorgegeben werden kann.
*   **Dynamische Signalquellen-Auswahl**: In komplexen modularisierten Anlagen können Sensorsignale oder Freigabebedingungen je nach Betriebsmodus flexibel zwischen einem Bus-System (Adapter) und einer fest verdrahteten Notfall-Ebene (Direkteingang) umgeschaltet werden.

---

## Vergleich mit ähnlichen Bausteinen

*   **`F_SEL` (Standard-Auswahlbaustein)**: Arbeitet rein datenflussorientiert nach IEC 61131-3. Er bietet keine direkte Ereignissteuerung und unterstützt keine Adapterverbindungen.
*   **Klassischer Multiplexer**: Erfordert meist eine Vielzahl einzelner Event- und Datenleitungen. `AX_BOOL_AX_SEL_AX` reduziert diesen Verdrahtungsaufwand im 4diac-System durch die Nutzung von Adaptern erheblich.

---

## Fazit

Der `AX_BOOL_AX_SEL_AX`-Funktionsbaustein ist ein effizientes Werkzeug zur ereignisgesteuerten Signalumschaltung. Durch die native Einbindung von unidirektionalen `AX`-Adaptern vereinfacht er das Systemdesign im 4diac-IDE-Netzwerk deutlich, während die internen Synchronisationsmechanismen eine hohe Zuverlässigkeit und Datenkonsistenz garantieren.