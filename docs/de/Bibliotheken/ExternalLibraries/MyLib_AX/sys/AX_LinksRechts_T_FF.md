# AX_LinksRechts_T_FF

![AX_LinksRechts_T_FF_network](./AX_LinksRechts_T_FF_network.svg)

* * * * * * * * * *

## Einleitung

`AX_LinksRechts_T_FF` wandelt einen einzelnen Taster (`IN`) über ein Toggle-Flipflop in zwei komplementäre Adapter-Ausgänge `Links`/`Rechts` um — jeder Tastendruck schaltet zwischen "Links aktiv" und "Rechts aktiv" um.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: AX_LinksRechts_T_FF

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **AX_R_TRIG**: `adapter::events::unidirectional::AX_R_TRIG` — erkennt die steigende Flanke des Tasters.
    - **AX_T_FF_INIT**: `adapter::events::unidirectional::AX_T_FF_INIT` — Toggle-Flipflop mit definiertem Startzustand (`QI=TRUE`, `Q_INIT=FALSE`).
    - **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2` — verzweigt den Flipflop-Zustand.
    - **AX_NOT**: `adapter::booleanOperators::AX_NOT` — negiert einen der beiden Zweige für das komplementäre Signal.
- **Funktionsweise**: Jede steigende Flanke an `IN` togglet `AX_T_FF_INIT.Q`. Der direkte Zustand geht an `Rechts`, der negierte Zustand an `Links` — dadurch sind `Links` und `Rechts` immer exakt komplementär (siehe Kommentar im Quellcode: "der AX_T_FF_INIT schaltet den Ausgang Aktiv auf FALSE, somit ist LINKS dann TRUE").

## Programmablauf und Verbindungen

1. `IN` → `AX_R_TRIG.QI`; `AX_R_TRIG.EO` → `AX_T_FF_INIT.CLK` (togglet bei jeder steigenden Flanke).
2. `AX_T_FF_INIT.Q` → `AX_SPLIT_2.IN`.
3. `AX_SPLIT_2.OUT1` → `AX_NOT.IN` → `AX_NOT.OUT` → `Links`.
4. `AX_SPLIT_2.OUT2` → `Rechts`.

## Anwendungsszenarien

- Ein-Taster-Umschaltung zwischen zwei sich gegenseitig ausschließenden Zuständen (z. B. Fahrtrichtung, Anzeige-Umschaltung), ohne zwei separate Taster zu benötigen.

## Zusammenfassung

`AX_LinksRechts_T_FF` realisiert eine klassische Ein-Taster-Umschaltung zwischen zwei komplementären Zuständen über ein Toggle-Flipflop mit definiertem Startzustand und eine Negation für das Gegensignal.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
