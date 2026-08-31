# Button_IXA_TO_logiBUS_QXA_BG

![Button_IXA_TO_logiBUS_QXA_BG_network](./Button_IXA_TO_logiBUS_QXA_BG_network.svg)

* * * * * * * * * *

## Einleitung

`Button_IXA_TO_logiBUS_QXA_BG` erweitert [`Button_IXA_TO_logiBUS_QXA`](./Button_IXA_TO_logiBUS_QXA.md) um eine VT-Statusfarbe: Der Taster-Zustand schaltet nicht nur den physischen Ausgang, sondern zusätzlich die Hintergrundfarbe des Tasters selbst (Grün/Weiß). Die OPC-UA-fähige Weiterentwicklung ist [`Button_IXA_TO_logiBUS_QXA_BG_OPC`](Button_IXA_TO_logiBUS_QXA_BG_OPC.md).

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Button_IXA_TO_logiBUS_QXA_BG

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **Button_IXA**: `isobus::UT::io::Button::Button_IXA` — VT-Taster-Adapter.
    - **logiBUS_QXA**: `logiBUS::io::DQ::logiBUS_QXA` — physischer digitaler Ausgang.
    - **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2` — verzweigt das Taster-Signal.
    - **GreenWhiteBackground1_AX** (SubApp, `MyLib::sys`): setzt die VT-Hintergrundfarbe passend zum Zustand (siehe [Background-Farbbausteine](./Background-Farbbausteine.md)).
- **Funktionsweise**: `Button_IXA.IN` wird über `AX_SPLIT_2` sowohl an `logiBUS_QXA.OUT` (physischer Ausgang) als auch an `GreenWhiteBackground1_AX.DI1` (Statusfarbe) verteilt.

## Programmablauf und Verbindungen

1. `u16ObjId` → `Button_IXA.u16ObjId` und `GreenWhiteBackground1_AX.u16ObjId`; `Output` → `logiBUS_QXA.Output`.
2. `Button_IXA.IN` → `AX_SPLIT_2.IN` → `AX_SPLIT_2.OUT1` → `logiBUS_QXA.OUT`, `AX_SPLIT_2.OUT2` → `GreenWhiteBackground1_AX.DI1`.

## Anwendungsszenarien

- VT-Taster mit direkter optischer Rückmeldung (Statusfarbe), aber ohne Fernbedienung über OPC-UA.

## Zusammenfassung

Fügt der einfachen Taster-zu-Ausgang-Verdrahtung eine VT-Statusfarbe hinzu — die Vorstufe zur OPC-UA-fähigen Variante.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
