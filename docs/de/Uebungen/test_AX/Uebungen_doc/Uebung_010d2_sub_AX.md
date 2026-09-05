# Uebung_010d2_sub_AX: Toggle-Flipflop mit SoftKey_F1 und GreenWhiteBackground mit Typed Subapp

![Uebung_010d2_sub_AX_network](./Uebung_010d2_sub_AX_network.svg)

* * * * * * * * * *

## Einleitung

Diese Übung demonstriert die Erstellung und Nutzung einer "Typed SubApp" für eine Toggle-Flipflop-Schaltung. Die Logik verbindet eine SoftKey-Eingabe (F1) mit einem Toggle-Flipflop, das einen physikalischen digitalen Ausgang (Q1) sowie eine visuelle Rückmeldung (Hintergrundfarbe) umschaltet. Durch die Kapselung in einer SubApp wird der Code modular und wiederverwendbar gestaltet.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Uebung_010d2_sub_AX (Diese Komponente selbst)

-   **Typ**: SubAppType
-   **Schnittstelle**:
    -   **Eingänge**:
        -   `u16ObjId` (UINT): Die Objekt-ID für das ISOBUS-Element.
        -   `Output` (logiBUS_DO_S): Identifiziert den physikalischen Ausgang (z.B. Q1..Q8).
-   **Verwendete interne FBs**:

    -   **SoftKey_UP_F1**: `isobus::UT::io::Softkey::Softkey_IE`
        -   **Parameter**:
            -   `QI` = `TRUE`
            -   `InputEvent` = `SK_RELEASED`
        -   **Ereignisausgang**: `IND`, ausgelöst beim Loslassen der Taste.
        -   **Dateneingang**: `u16ObjId` (kommt von der SubApp-Schnittstelle).
        -   **Beschreibung**: Dieser Baustein repräsentiert die SoftKey-Taste F1 auf dem Universal Terminal (UT), reagiert aber erst beim Loslassen.

    -   **AX_T_FF**: `adapter::events::unidirectional::AX_T_FF`
        -   **Funktionsweise**: Toggle-Flipflop. Jedes Ereignis an `CLK` kehrt den Adapterausgang `Q` um.
        -   **Ereigniseingang**: `CLK`, verbunden mit `SoftKey_UP_F1.IND`.

    -   **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2`
        -   **Funktionsweise**: Ein Splitter-Baustein für Adapter-Verbindungen. Er nimmt das Zustandssignal von `AX_T_FF.Q` entgegen und teilt es auf zwei Ausgänge (`OUT1`, `OUT2`) auf, um mehrere Ziele gleichzeitig anzusteuern.

    -   **DigitalOutput_Q1**: `logiBUS::io::DQ::logiBUS_QXA`
        -   **Parameter**:
            -   `QI` = `TRUE`
        -   **Ereigniseingang**: Adapter-Verbindung über Port `OUT`.
        -   **Dateneingang**: `Output` (kommt von der SubApp-Schnittstelle).
        -   **Beschreibung**: Steuert einen hardwareseitigen digitalen Ausgang über den logiBUS an.

    -   **GreenWhiteBackground_AX**: `MyLib::sys::GreenWhiteBackground1_AX`
        -   **Typ**: Verschachtelte SubApp
        -   **Verbindungen**:
            -   Dateneingang `u16ObjId` verbunden mit der Schnittstelle.
            -   Adaptereingang `DI1` verbunden mit `AX_SPLIT_2.OUT2`.
        -   **Beschreibung**: Eine weitere gekapselte Logik, die für die Umschaltung der Hintergrundfarbe (Grün/Weiß) zuständig ist.

## Programmablauf und Verbindungen

Der Ablauf innerhalb dieser SubApp gestaltet sich wie folgt:

1.  **Initialisierung**: Über die Eingänge der SubApp (`u16ObjId` und `Output`) werden die IDs für das ISOBUS-Objekt und der zu schaltende Hardware-Ausgang an die internen Bausteine weitergereicht.
2.  **Eingabe (SoftKey)**: Der Baustein `SoftKey_UP_F1` überwacht die Taste F1 des Terminals. Wird diese losgelassen, wird ein Signal über das Ereignis `IND` gesendet.
3.  **Toggle**: Das Ereignis erreicht `AX_T_FF.CLK`, wodurch der interne Zustand `Q` umgekehrt wird.
4.  **Signalverteilung**: Das Adaptersignal `AX_T_FF.Q` gelangt zum Baustein `AX_SPLIT_2`. Dieser teilt das Signal auf zwei Pfade auf:
    -   **Pfad 1 (Hardware)**: Geht an `DigitalOutput_Q1`. Hierdurch wird der physikalische Ausgang (entsprechend dem Eingangsparameter `Output`) geschaltet.
    -   **Pfad 2 (Visualisierung)**: Geht an die SubApp `GreenWhiteBackground_AX`. Diese sorgt dafür, dass sich die Hintergrundfarbe des zugehörigen Softkeys ändert, um dem Benutzer eine visuelle Rückmeldung zu geben.

**Lernziele:**

-   Verständnis von Toggle-Flipflops (`AX_T_FF`) im Vergleich zu direkter Durchschaltung.
-   Umgang mit Adapter-Verbindungen (Adapter Connections) und deren Splitting.
-   Umgang mit verschachtelten SubApps (SubApp in SubApp).
-   Verknüpfung von ISOBUS-UI-Elementen mit Hardware-I/Os.

**Voraussetzungen:**

-   Grundkenntnisse in IEC 61499.
-   Verständnis des Adapter-Konzepts in 4diac.
-   Kenntnis der Übung `Uebung_010c3_sub_AX` (direkte Durchschaltung ohne Toggle).

## Zusammenfassung

Die Übung `Uebung_010d2_sub_AX` ist ein wiederverwendbares Modul, das eine SoftKey-Bedienung über ein Toggle-Flipflop gleichzeitig auf einen Hardware-Ausgang und eine Display-Visualisierung abbildet. Durch den Einsatz des `AX_SPLIT_2` Bausteins wird demonstriert, wie ein einzelnes Adapter-Event parallel verarbeitet werden kann, um Hardware-Aktionen und UI-Updates synchron zu halten.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
