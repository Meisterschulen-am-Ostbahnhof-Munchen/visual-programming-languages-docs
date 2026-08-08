# AR_REAL_AX_SEL_AR


![AR_REAL_AX_SEL_AR](./AR_REAL_AX_SEL_AR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AR_REAL_AX_SEL_AR` ist ein binärer Selektor (Multiplexer), der zur Auswahl zwischen zwei analogen Signalquellen (`REAL`) dient. Das Besondere an diesem Baustein ist die hybride Schnittstellenstruktur: Er ermöglicht die Auswahl zwischen einem über einen Adapter eingelesenen Wert und einer klassischen, direkt anliegenden IEC 61499-Variable. Die Steuerung der Auswahl erfolgt ebenfalls über eine adapterbasierte Schnittstelle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Aktualisiert den Wert der direkt anliegenden Daten-Eingangsvariable `IN1` und triggert den internen Auswahlprozess.

### **Ereignis-Ausgänge**

*   *(Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`)*.

### **Daten-Eingänge**

*   **IN1** (REAL): Selektierbare Eingangsvariable (Kanal 1). Wird zusammen mit dem Ereignis `EI1` eingelesen.

### **Daten-Ausgänge**

*   *(Keine direkten Daten-Ausgänge vorhanden. Die Datenbereitstellung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`)*.

### **Adapter**

*   **Sockets (Eingangs-Adapter):**
    *   **IN0** (Typ: `adapter::types::unidirectional::AR`): Selektierbare Eingangsvariable (Kanal 0) in Form eines unidirektionalen Adapters für Analogwerte.
    *   **G** (Typ: `adapter::types::unidirectional::AX`): Selektionssignal (Steuereingang) in Form eines unidirektionalen Adapters. Bestimmt, welcher Eingang auf den Ausgang geschaltet wird.
*   **Plugs (Ausgangs-Adapter):**
    *   **OUT** (Typ: `adapter::types::unidirectional::AR`): Der ausgewählte Ausgangswert (REAL), bereitgestellt über einen unidirektionalen Adapter.

## Funktionsweise

Der Baustein arbeitet intern als ereignisgesteuertes Netzwerk (Composite FB) und nutzt standardisierte IEC 61131-3 und IEC 61499 Bausteine zur Datenpufferung und -selektion:

1.  **Datenpufferung (Latching):**
    *   Ereignisse an den Eingängen (`IN0.E1`, `G.E1` oder `EI1`) triggern jeweils ein internes Flip-Flop (`E_D_FF` bzw. `E_D_FF_ANY`).
    *   Dies stellt sicher, dass die Datenwerte (`IN0.D1`, `G.D1` und `IN1`) konsistent zwischengespeichert und synchron an die Logik übergeben werden.
2.  **Wertübertragung (Move):**
    *   Die gepufferten Datenwerte der Kanäle werden über Konvertierungsbausteine (`F_MOVE`) an den zentralen Selektor übergeben.
3.  **Auswahl (Selection):**
    *   Der Kernbaustein `F_SEL` (Standard-Selektor) wertet das Steuersignal `G` aus:
        *   Ist das Signal am Adapter **G** `FALSE` (0), wird der Wert von **IN0** (Adapter) an den Ausgang durchgeschaltet.
        *   Ist das Signal am Adapter **G** `TRUE` (1), wird der Wert von **IN1** (Direkteingang) an den Ausgang durchgeschaltet.
4.  **Ausgabe:**
    *   Der ausgewählte Wert wird an den Ausgangs-Plug `OUT` (`OUT.D1`) übergeben, und zeitgleich wird das Ausgangsereignis `OUT.E1` ausgelöst, um nachfolgende Bausteine über die Datenaktualisierung zu informieren.

```
                  +-------------------------+
                  |    AR_REAL_AX_SEL_AR    |
   [AR] IN0 ------> (0)                     |
                  |     \                   |
   [AX] G   ------> [Sel]---> [OUT] --------> [AR] OUT
                  |     /                   |
        IN1 ------> (1)                     |
   (EI1)    ------>                         |
                  +-------------------------+
```

## Technische Besonderheiten

*   **Hybrides Interface:** Ermöglicht die nahtlose Kopplung zwischen der adapterbasierten Signalverarbeitung und klassischen, ereignis-/datenbasierten Funktionsbausteinen.
*   **Erhöhte Datenkonsistenz:** Durch die Verwendung von internen Event-D-Flip-Flops (`E_D_FF`) werden Daten- und Ereignissynchronität garantiert. Ein "Durchrutschen" von unvollständigen Signalzuständen bei asynchronen Eingängen wird verhindert.
*   **Ressourceneffizienz:** Durch die Verwendung von unidirektionalen Adaptern (`AR` und `AX`) bleibt der Kommunikations-Overhead minimal.

## Zustandsübersicht

Da es sich um einen Composite-Funktionsbaustein handelt, wird das Verhalten nicht über eine Zustandsmaschine (ECC), sondern rein über den internen Daten- und Ereignisfluss gesteuert. Jedes Eingangsereignis führt zu einer unmittelbaren Neuberechnung und Aktualisierung des Ausgangs.

| Selektionssignal (G.D1) | Gewählter Eingang | Ausgangswert (OUT.D1) | Ausgangsereignis |
| :--- | :--- | :--- | :--- |
| `FALSE` | IN0 (Adapter) | Wert von `IN0.D1` | `OUT.E1` wird ausgelöst |
| `TRUE` | IN1 (Direkteingabe) | Wert von `IN1` | `OUT.E1` wird ausgelöst |

## Anwendungsszenarien

*   **Hand-/Automatik-Umschaltung:** Einbindung eines automatischen Sollwerts über ein Bussystem (Adapter `IN0`) und eines manuellen Sollwerts über eine lokale Benutzerschnittstelle (Variable `IN1`).
*   **Signal-Override / Sicherheitsabschaltung:** Temporäres Aufschalten eines fest definierten Ersatzwerts (`IN1`) bei Eintreten eines bestimmten Ereignisses (gesteuert über Adapter `G`).
*   **Schnittstellenkonvertierung:** Zusammenführen verschiedener Datenquellen in einer modularen 4diac-Anwendung.

## Vergleich mit ähnlichen Bausteinen

*   **Standard `F_SEL`:** Der klassische Selektionsbaustein verarbeitet ausschließlich Standarddatentypen und besitzt keine integrierte Ereignissteuerung oder Adapterschnittstellen. `AR_REAL_AX_SEL_AR` kapselt diese Funktionalität und macht sie direkt netzwerkfähig.
*   **Rein adapterbasierte Selektoren:** Im Gegensatz zu Selektoren, die ausschließlich Adapter an den Eingängen erwarten, bietet dieser Baustein durch den direkten `REAL`-Eingang Flexibilität beim Anschluss von physikalischen Hardware-Eingängen oder internen Variablen.

## Fazit

Der `AR_REAL_AX_SEL_AR` ist ein vielseitiger Hilfsbaustein für Steuerungsprojekte in 4diac-IDE. Er löst elegant das Problem der Signalzusammenführung aus unterschiedlichen Schnittstellentypen und stellt durch seine interne Pufferung ein stabiles und deterministisches Verhalten im verteilten Steuerungssystem sicher.