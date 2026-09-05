# Uebung_010e2_sub_AX: SR+Toggle-Flipflop mit 3x SoftKey und GreenWhiteBackground mit Typed Subapp

![Uebung_010e2_sub_AX_network](./Uebung_010e2_sub_AX_network.svg)

* * * * * * * * * *

## Einleitung

Diese Übung demonstriert die Erstellung und Nutzung einer "Typed SubApp" für ein SR+Toggle-Flipflop mit drei SoftKeys. Die Logik verbindet drei SoftKey-Eingaben (Set, Reset, Toggle) mit einem kombinierten Speicherbaustein, der einen physikalischen digitalen Ausgang (Q1) sowie eine visuelle Rückmeldung (Hintergrundfarbe am Toggle-SoftKey) steuert. Durch die Kapselung in einer SubApp wird der Code modular und wiederverwendbar gestaltet.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Uebung_010e2_sub_AX (Diese Komponente selbst)

-   **Typ**: SubAppType
-   **Schnittstelle**:
    -   **Eingänge**:
        -   `u16ObjId_SET` (UINT): Objekt-ID des Set-SoftKeys.
        -   `u16ObjId_RESET` (UINT): Objekt-ID des Reset-SoftKeys.
        -   `u16ObjId_TOGGLE` (UINT): Objekt-ID des Toggle-SoftKeys (wird auch für die Hintergrundfarbe verwendet).
        -   `Output` (logiBUS_DO_S): Identifiziert den physikalischen Ausgang (z.B. Q1..Q8).
-   **Verwendete interne FBs**:

    -   **SoftKey_SET**, **SoftKey_RESET**, **SoftKey_TOGGLE**: je `isobus::UT::io::Softkey::Softkey_IE`
        -   **Parameter**: `QI` = `TRUE`, `InputEvent` = `SK_RELEASED`
        -   **Ereignisausgang**: `IND`, ausgelöst beim Loslassen der jeweiligen Taste.
        -   **Dateneingang**: `u16ObjId` jeweils von der zugehörigen SubApp-Eingangsvariable.

    -   **AX_T_FF_SR**: `adapter::events::unidirectional::AX_T_FF_SR`
        -   **Funktionsweise**: Kombiniertes SR+Toggle-Flipflop. `S` setzt den Ausgang `Q` fest, `R` setzt ihn fest zurück, `CLK` kehrt ihn um.
        -   **Ereigniseingänge**: `S` ← `SoftKey_SET.IND`, `R` ← `SoftKey_RESET.IND`, `CLK` ← `SoftKey_TOGGLE.IND`.

    -   **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2`
        -   **Funktionsweise**: Ein Splitter-Baustein für Adapter-Verbindungen. Er nimmt das Zustandssignal von `AX_T_FF_SR.Q` entgegen und teilt es auf zwei Ausgänge (`OUT1`, `OUT2`) auf.

    -   **DigitalOutput_Q1**: `logiBUS::io::DQ::logiBUS_QXA`
        -   **Parameter**: `QI` = `TRUE`
        -   **Dateneingang**: `Output` (kommt von der SubApp-Schnittstelle).
        -   **Beschreibung**: Steuert einen hardwareseitigen digitalen Ausgang über den logiBUS an.

    -   **GreenWhiteBackground_AX**: `MyLib::sys::GreenWhiteBackground1_AX`
        -   **Typ**: Verschachtelte SubApp
        -   **Verbindungen**:
            -   Dateneingang `u16ObjId` verbunden mit `u16ObjId_TOGGLE` (nur der Toggle-SoftKey zeigt die Rückmeldung).
            -   Adaptereingang `DI1` verbunden mit `AX_SPLIT_2.OUT2`.

## Programmablauf und Verbindungen

1.  **Initialisierung**: Über die Eingänge der SubApp werden die Objekt-IDs der drei SoftKeys und der zu schaltende Hardware-Ausgang an die internen Bausteine weitergereicht.
2.  **Set**: Wird `SoftKey_SET` losgelassen, setzt `AX_T_FF_SR.S` den Zustand `Q` fest auf AN.
3.  **Reset**: Wird `SoftKey_RESET` losgelassen, setzt `AX_T_FF_SR.R` den Zustand `Q` fest auf AUS.
4.  **Toggle**: Wird `SoftKey_TOGGLE` losgelassen, kehrt `AX_T_FF_SR.CLK` den aktuellen Zustand `Q` um.
5.  **Signalverteilung**: `AX_SPLIT_2` verteilt den neuen Zustand an `DigitalOutput_Q1` (physischer Ausgang) und `GreenWhiteBackground_AX` (Hintergrundfarbe des Toggle-SoftKeys).

**Lernziele:**

-   Verständnis kombinierter SR+Toggle-Flipflops (`AX_T_FF_SR`) mit mehreren unabhängigen Ereigniseingängen.
-   Umgang mit Adapter-Verbindungen (Adapter Connections) und deren Splitting.
-   Umgang mit verschachtelten SubApps (SubApp in SubApp).
-   Verknüpfung mehrerer ISOBUS-UI-Elemente mit einem gemeinsamen Speicherzustand.

**Voraussetzungen:**

-   Grundkenntnisse in IEC 61499.
-   Verständnis des Adapter-Konzepts in 4diac.
-   Kenntnis der Übungen `Uebung_010c3_sub_AX` und `Uebung_010d2_sub_AX`.

## Zusammenfassung

Die Übung `Uebung_010e2_sub_AX` ist ein wiederverwendbares Modul, das drei unabhängige SoftKey-Eingaben (Set, Reset, Toggle) auf einen gemeinsamen Speicherzustand abbildet und diesen sowohl auf einen Hardware-Ausgang als auch auf eine Display-Visualisierung überträgt.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
