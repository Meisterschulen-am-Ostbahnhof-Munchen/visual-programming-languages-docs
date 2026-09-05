# Training_07_OPC_UA_RES: Pure SR Flip-Flop over OPC-UA — Adapter Variant of Training_05

![Training_07_OPC_UA_RES_network](./Training_07_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Introduction

`Training_07_OPC_UA_RES` relates to `Training_05_OPC_UA_RES` exactly the
way `Training_06_OPC_UA_RES` relates to `Training_04_OPC_UA_RES`: the same
Set/Reset function, but with the combined `ASR_AX` adapter blocks instead
of individually wired `CLIENT_0`/`SERVER_0`/`AX_CLIENT_1_0` instances. Same
OPC-UA addresses as Training_05 (`SR2_*`).

## Composites Used

| Composite | Device | Purpose |
|---|---|---|
| [`SoftKeySR_PC_A_OPC_Adapter`](./SoftKeySR_PC_A_OPC_Adapter_network.svg) | A (`192.168.1.11`) | HMI (2 SoftKeys + `GreenWhiteBackground`) behind `SoftKeySR_ASR_AX`, OPC-UA trigger behind `ASR_AX_CLIENT_0_SUBSCRIBE_1` — coupled via a bidirectional adapter connection |
| [`SoftKeySR_PC_B_OPC_Adapter`](./SoftKeySR_PC_B_OPC_Adapter_network.svg) | B (`192.168.1.12`) | `ASR_AX_SERVER_0_CLIENT_1_0` bundles the 2 `SERVER_0` + `AX_CLIENT_1_0` behind one adapter; `ASR_AX_AX_SPLIT` fans out to `DigitalOutput_Q1` and `ASR_AX_SR_2` |

## OPC-UA Address Space

Identical to Training_05 (`SR2_SET_*`, `SR2_RESET_*`, `SR2_STATE_*`) — see
[Training_05_OPC_UA_RES](../Training_05_OPC_UA_RES/Training_05_OPC_UA_RES.md#opc-ua-address-space).

## Program Flow and Connections

1. **`SoftKeySR_PC_A_OPC_Adapter`** (Device A): `SoftKeySR_ASR_AX` bundles
   the 2 SoftKeys + `GreenWhiteBackground` behind an `ASR_AX` Plug; an
   adapter connection hands Set/Reset/state off to
   `ASR_AX_CLIENT_0_SUBSCRIBE_1` (`TRIGGER`), which carries the
   `ID_SET_CALL`/`ID_RESET_CALL`/`ID_STATE_READ` addresses.
2. **`SoftKeySR_PC_B_OPC_Adapter`** (Device B): `TRIGGER`
   (`ASR_AX_SERVER_0_CLIENT_1_0`) carries the 3 `ID_*` addresses and
   delivers the Set/Reset/state bundle via `TRIGGER.S_R` to `SPLIT`
   (`ASR_AX_AX_SPLIT`), which passes it on to `FLIPFLOP` (`ASR_AX_SR_2`);
   `SPLIT.AX_OUT` drives `DigitalOutput_Q1` in parallel.

## Technical Notes

- **`ASR_AX_*` instead of `ASRT_AX_*`**: the same bundling logic as
  Training_06, but the two-valued (Set/Reset) rather than three-valued
  (Set/Reset/Toggle) adapter variant — one pin fewer (`S_R` instead of
  `S_R_T`), otherwise structurally identical.
- **Direct comparison with Training_05**: same address space, same
  function, but far fewer individual connections in the composite.

## Learning Objectives

- Adapter-3.0.0 combo blocks for the reduced Set/Reset-without-Toggle
  variant (`ASR_AX_CLIENT_0_SUBSCRIBE_1`, `ASR_AX_SERVER_0_CLIENT_1_0`).
- Direct comparison of Training_05 (manual) vs. Training_07 (adapter) for
  identical function.

**Difficulty**: Advanced
**Prerequisites**: `Training_05_OPC_UA_RES`, `Training_06_OPC_UA_RES` (same
adapter pattern, with Toggle).

## Summary

`Training_07_OPC_UA_RES` carries the adapter-bundling pattern from
Training_06 over to the reduced Set/Reset variant from Training_05.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
