# Softkey_IXA_TO_logiBUS_QXA_BG

![Softkey_IXA_TO_logiBUS_QXA_BG_network](./Softkey_IXA_TO_logiBUS_QXA_BG_network.svg)

* * * * * * * * * *
## Einleitung

`Softkey_IXA_TO_logiBUS_QXA_BG` erweitert [`Softkey_IXA_TO_logiBUS_QXA`](./Softkey_IXA_TO_logiBUS_QXA.md) um eine VT-Statusfarbe — das Softkey-Pendant zu [`Button_IXA_TO_logiBUS_QXA_BG`](./Button_IXA_TO_logiBUS_QXA_BG.md).

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: Softkey_IXA_TO_logiBUS_QXA_BG

- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **Softkey_IXA**: `isobus::UT::io::Softkey::Softkey_IXA` — VT-Softkey-Adapter.
    - **logiBUS_QXA**: `logiBUS::io::DQ::logiBUS_QXA` — physischer digitaler Ausgang.
    - **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2` — verzweigt das Softkey-Signal.
    - **GreenWhiteBackground1_AX** (SubApp, `MyLib::sys`): setzt die VT-Statusfarbe (siehe [Background-Farbbausteine](./Background-Farbbausteine.md)).
- **Funktionsweise**: `Softkey_IXA.IN` wird über `AX_SPLIT_2` sowohl an `logiBUS_QXA.OUT` als auch an `GreenWhiteBackground1_AX.DI1` verteilt.

## Programmablauf und Verbindungen

1. `u16ObjId` → `Softkey_IXA.u16ObjId` und `GreenWhiteBackground1_AX.u16ObjId`; `Output` → `logiBUS_QXA.Output`.
2. `Softkey_IXA.IN` → `AX_SPLIT_2.IN` → `AX_SPLIT_2.OUT1` → `logiBUS_QXA.OUT`, `AX_SPLIT_2.OUT2` → `GreenWhiteBackground1_AX.DI1`.

## Anwendungsszenarien

- VT-Softkey mit direkter optischer Rückmeldung, ohne OPC-UA.

## Zusammenfassung

Softkey-Pendant zu `Button_IXA_TO_logiBUS_QXA_BG` — identisches Muster, anderer Tastertyp.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
