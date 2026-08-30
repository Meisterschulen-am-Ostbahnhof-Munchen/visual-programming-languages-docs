# logiBUS_IXA_BG_OPC

![logiBUS_IXA_BG_OPC_network](./logiBUS_IXA_BG_OPC_network.svg)

* * * * * * * * * *
## Introduction

`logiBUS_IXA_BG_OPC` extends [`logiBUS_IXA_BG`](./logiBUS_IXA_BG.md) with OPC-UA feedback: the physical input state is shown as a VT background color (`GreenWhiteBackground1_AX`) and also published externally as a BOOL value via `AX_PUBLISH_1`. The signal path is split for this using `AX_SPLIT_2`.

## Function Blocks Used

### Sub-blocks: logiBUS_IXA_BG_OPC

- **Type**: SubAppType
- **Internal FBs used**:
    - **logiBUS_IXA**: `logiBUS::io::DI::logiBUS_IXA` — physical digital input, `QI=TRUE`.
    - **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2` — splits the BOOL adapter value into two independent outputs (`OUT1`, `OUT2`).
    - **GreenWhiteBackground1_AX** (SubApp): `MyLib::sys::GreenWhiteBackground1_AX` — VT background-color indication, see [Background Color Blocks (shared pattern)](./Background-Color-Blocks.md).
    - **AX_PUBLISH_1**: `adapter::net::AX_PUBLISH_1` — publishes a BOOL value via OPC-UA, `QI=TRUE`, target address via `ID_WRITE`.
- **Operation**: The input value is duplicated via `AX_SPLIT_2`; one path feeds the VT status indication, the other the OPC-UA publication.

## Program Flow and Connections

1. `Input` → `logiBUS_IXA.Input`; `u16ObjId` → `GreenWhiteBackground1_AX.u16ObjId`; `ID_WRITE` → `AX_PUBLISH_1.ID`.
2. `logiBUS_IXA.IN` (adapter) → `AX_SPLIT_2.IN` (adapter).
3. `AX_SPLIT_2.OUT1` → `GreenWhiteBackground1_AX.DI1`.
4. `AX_SPLIT_2.OUT2` → `AX_PUBLISH_1.IN`.

## Application Scenarios

- A physical digital input whose state should be visible locally on the VT as well as readable by an upstream SCADA system via OPC-UA (e.g. limit-switch or fault signals).

## Summary

VT status indication plus OPC-UA publication of a physical digital input, both derived from a shared adapter value via `AX_SPLIT_2`.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
