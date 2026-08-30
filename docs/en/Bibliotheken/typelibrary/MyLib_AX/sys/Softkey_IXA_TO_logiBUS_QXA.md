# Softkey_IXA_TO_logiBUS_QXA

![Softkey_IXA_TO_logiBUS_QXA_network](./Softkey_IXA_TO_logiBUS_QXA_network.svg)

* * * * * * * * * *
## Introduction

`Softkey_IXA_TO_logiBUS_QXA` connects a VT softkey (`Softkey_IXA`) directly to a physical digital output (`logiBUS_QXA`) — functionally identical to [`Button_IXA_TO_logiBUS_QXA`](./Button_IXA_TO_logiBUS_QXA.md), but for softkeys instead of buttons.

## Function Blocks (FBs) Used

### Sub-blocks: Softkey_IXA_TO_logiBUS_QXA

- **Type**: SubAppType
- **Internal FBs used**:
    - **Softkey_IXA**: `isobus::UT::io::Softkey::Softkey_IXA` — VT softkey adapter, `QI=TRUE`.
    - **logiBUS_QXA**: `logiBUS::io::DQ::logiBUS_QXA` — physical digital output.
- **Functionality**: Direct adapter connection `Softkey_IXA.IN` → `logiBUS_QXA.OUT`, no intermediate logic.

## Program Flow and Connections

1. `u16ObjId` → `Softkey_IXA.u16ObjId`; `Output` → `logiBUS_QXA.Output`.
2. `Softkey_IXA.IN` → `logiBUS_QXA.OUT`.

## Application Scenarios

- Minimal softkey-to-output block with no status display or remote control.

## Summary

Softkey counterpart to `Button_IXA_TO_logiBUS_QXA` — identical pattern, different control type.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
