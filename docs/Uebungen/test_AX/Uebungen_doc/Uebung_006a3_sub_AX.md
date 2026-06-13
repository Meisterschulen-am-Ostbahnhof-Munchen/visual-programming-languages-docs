Hier ist die Dokumentation für die Übung `Uebung_006a3_sub_AX` basierend auf den bereitgestellten Daten.

# Uebung_006a3_sub_AX: Subapplication Type


* * * * * * * * * *

## Einleitung
Bei diesem Baustein handelt es sich um eine Subapplikation (SubAppType), die eine Logik zur wechselseitigen Ansteuerung zweier Ausgänge implementiert. Der Baustein nutzt die Adapter-Technologie (`AX`), um Signale zu verarbeiten. Ziel ist es, basierend auf einem Eingangssignal den Zustand zweier Ausgänge (`Links` und `Rechts`) zu toggeln, wobei diese Ausgänge stets entgegengesetzte Zustände haben (komplementär).

## Verwendete Funktionsbausteine (FBs)

In dieser Subapplikation werden spezifische Adapter-Bausteine verwendet, um die Umschaltlogik und Signalverteilung zu realisieren.

### Sub-Bausteine: Uebung_006a3_sub_AX
- **Typ**: SubAppType
- **Verwendete interne FBs**:

    - **AX_SWITCH**: `adapter::events::unidirectional::AX_SWITCH`
        - **Beschreibung**: Dient als Eingangsschalter, der Adapter-Signale in Events umwandelt oder durchschaltet.
        - **Adapter-Eingang**: `G` (Verbunden mit dem externen Adapter `IN`).
        - **Ereignisausgang**: `EO1` (Verbunden mit `AX_T_FF.CLK`).

    - **AX_T_FF**: `adapter::events::unidirectional::AX_T_FF`
        - **Beschreibung**: Ein Toggle-Flip-Flop (T-Flip-Flop) für Adapter-Strukturen. Es wechselt seinen Ausgangszustand bei jedem Eingangsimpuls.
        - **Ereigniseingang**: `CLK` (Kommt von `AX_SWITCH.EO1`).
        - **Adapter-Ausgang**: `Q` (Geht an `AX_SPLIT_2.IN`).

    - **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2`
        - **Beschreibung**: Ein Splitter-Baustein, der ein eingehendes Adapter-Signal auf zwei Ausgänge aufteilt.
        - **Adapter-Eingang**: `IN` (Kommt von `AX_T_FF.Q`).
        - **Adapter-Ausgang 1**: `OUT1` (Geht direkt an den externen Adapter `Rechts`).
        - **Adapter-Ausgang 2**: `OUT2` (Geht an `AX_NOT.IN`).

    - **AX_NOT**: `adapter::booleanOperators::AX_NOT`
        - **Beschreibung**: Ein logischer NICHT-Baustein (Inverter) für Adapter-Signale.
        - **Adapter-Eingang**: `IN` (Kommt von `AX_SPLIT_2.OUT2`).
        - **Adapter-Ausgang**: `OUT` (Geht an den externen Adapter `Links`).

- **Funktionsweise**:
    Der Baustein empfängt ein Signal über den Adapter-Socket `IN`. Dieses Signal triggert über den `AX_SWITCH` das Toggle-Flip-Flop `AX_T_FF`. Das Flip-Flop ändert daraufhin seinen Zustand. Das Zustandssignal wird durch den `AX_SPLIT_2` aufgeteilt: Ein Pfad führt direkt zum Ausgang `Rechts`, während der andere Pfad durch den `AX_NOT` invertiert wird und zum Ausgang `Links` führt. Somit verhalten sich `Links` und `Rechts` immer gegensätzlich zueinander.

## Programmablauf und Verbindungen

Der Ablauf innerhalb der Subapplikation ist rein ereignis- und signalgesteuert über die Adapter-Verbindungen:

1.  **Eingangssignal**: Das externe Signal kommt am Socket `IN` an.
2.  **Triggerung**: Der `AX_SWITCH` detektiert das Signal am Eingang `G` und feuert ein Event am Ausgang `EO1`.
3.  **Zustandswechsel**: Dieses Event dient als Clock-Signal (`CLK`) für das `AX_T_FF`, welches daraufhin seinen internen Zustand `Q` umschaltet (Toggelt).
4.  **Signalverteilung**: Das Signal von `Q` wird an den Splitter `AX_SPLIT_2` weitergegeben.
    *   **Pfad A (Rechts)**: Der Ausgang `OUT1` des Splitters leitet das Signal direkt an den Plug `Rechts` weiter.
    *   **Pfad B (Links)**: Der Ausgang `OUT2` des Splitters leitet das Signal an den Inverter `AX_NOT`. Das invertierte Signal wird dann an den Plug `Links` ausgegeben.

**Schnittstellen:**
*   `IN` (Socket): Eingang für das Steuersignal.
*   `Rechts` (Plug): Ausgang, der dem aktuellen Zustand des Flip-Flops entspricht.
*   `Links` (Plug): Ausgang, der dem invertierten Zustand des Flip-Flops entspricht.

## Zusammenfassung
Die Subapplikation `Uebung_006a3_sub_AX` stellt ein Modul zur Verfügung, das einen Eingangsimpuls in zwei alternierende Ausgangssignale umwandelt. Durch die Verwendung von Adapter-Bausteinen (`AX`) wird die Verdrahtung vereinfacht, da Daten und Events gekapselt übertragen werden können. Die integrierte Invertierung (`AX_NOT`) stellt sicher, dass die Ausgänge `Links` und `Rechts` niemals denselben logischen Zustand haben.