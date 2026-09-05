# Training_06_OPC_UA_RES: SR+Toggle over OPC-UA — Adapter Variant of Training_04

![Training_06_OPC_UA_RES_network](./Training_06_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Introduction

`Training_06_OPC_UA_RES` is the **adapter variant** of
`Training_04_OPC_UA_RES` — the same function (3 SoftKeys, SR+toggle
flip-flop, OPC-UA write-back), but instead of individual `CLIENT_0`/
`SERVER_0`/`AX_CLIENT_1_0` instances with manual data wiring, it uses the
combined adapter blocks from the `adapter-3.0.0` library (see the
adapter-3.0.0 FB family, documented under
[`Bibliotheken/ExternalLibraries/adapter`](../../../../Bibliotheken/ExternalLibraries/adapter/index.md)).
Same OPC-UA addresses as Training_04 (`SR1_*`).

## Composites Used

| Composite | Device | Purpose |
|---|---|---|
| [`Uebung_010e_PC_A_OPC_Adapter`](./Uebung_010e_PC_A_OPC_Adapter_network.svg) | A (`192.168.1.11`) | HMI (3 SoftKeys + `GreenWhiteBackground`) behind `SoftKeySRT_ASRT_AX`, OPC-UA trigger behind `ASRT_AX_CLIENT_0_SUBSCRIBE_1` — coupled via a single bidirectional adapter connection |
| [`Uebung_010e_PC_B_OPC_Adapter`](./Uebung_010e_PC_B_OPC_Adapter_network.svg) | B (`192.168.1.12`) | `ASRT_AX_SERVER_0_CLIENT_1_0` bundles the 3 `SERVER_0` + `AX_CLIENT_1_0` behind one adapter; `ASRT_AX_AX_SPLIT` fans out to `DigitalOutput_Q1` and `ASRT_AX_T_FF_SR_2` |

## OPC-UA Address Space

Identical to Training_04 (`SR1_SET_*`, `SR1_RESET_*`, `SR1_TOGGLE_*`,
`SR1_STATE_*`) — see
[Training_04_OPC_UA_RES](../Training_04_OPC_UA_RES/Training_04_OPC_UA_RES.md#opc-ua-address-space).
Only the wiring inside the composite changes, not the address space.

## Program Flow and Connections

1. **`Uebung_010e_PC_A_OPC_Adapter`** (Device A): `SoftKeySRT_ASRT_AX`
   bundles the 3 SoftKeys + `GreenWhiteBackground` behind an `ASRT_AX`
   Plug; a single adapter connection
   (`SoftKeySRT_ASRT_AX.OUT` → `TRIGGER.S_R_T`) hands Set/Reset/Toggle/
   state off to `ASRT_AX_CLIENT_0_SUBSCRIBE_1` (`TRIGGER`), which carries
   the 3 `ID_*_CALL` and `ID_STATE_READ` addresses as data pins.
2. **`Uebung_010e_PC_B_OPC_Adapter`** (Device B): `TRIGGER`
   (`ASRT_AX_SERVER_0_CLIENT_1_0`) carries the 4 `ID_*` addresses as data
   pins and delivers the bundled Set/Reset/Toggle/state signal via
   `TRIGGER.S_R_T` to `SPLIT` (`ASRT_AX_AX_SPLIT`), which passes it on to
   `FLIPFLOP` (`ASRT_AX_T_FF_SR_2`); `SPLIT.AX_OUT` drives
   `DigitalOutput_Q1` in parallel.

## Technical Notes

- **One adapter instead of four separate blocks**: `ASRT_AX_SERVER_0_CLIENT_1_0`
  bundles 3× `SERVER_0` + 1× `AX_CLIENT_1_0` behind a single bidirectional
  adapter connection — the four `ID_*` address pins stay visible as data
  pins directly on the composite interface (see
  [PR #158](https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/visual-programming-languages-docs/pull/158)
  for the full adapter-3.0.0 documentation of these combo types).
- **A continuous adapter chain instead of event/BOOL switching**: unlike
  Training_04 (`AX_T_FF_SR` with separate `S`/`R`/`CLK` event pins and a
  BOOL `Q`), here the entire Set/Reset/Toggle/state bundle runs as **one**
  adapter connection through `TRIGGER` → `SPLIT` → `FLIPFLOP` — the actual
  flip-flop logic (`ASRT_AX_T_FF_SR_2`) is itself adapter-based, no longer
  wired to individual events.
- **Less wiring, same semantics**: functionally identical to Training_04,
  but with far fewer connections in the composite — the price is that the
  individual actions (Set/Reset/Toggle) are no longer visible as separate
  pins in the network diagram, disappearing into the adapter bundle (only
  readable at the `ID_*` data pins).

## Learning Objectives

- Adapter-3.0.0 combo blocks (`ASRT_AX_CLIENT_0_SUBSCRIBE_1`,
  `ASRT_AX_SERVER_0_CLIENT_1_0`) as a replacement for several individually
  wired network FBs.
- Continuous bidirectional adapter chains (`ASRT_AX_AX_SPLIT`,
  `ASRT_AX_T_FF_SR_2`) instead of individual event/BOOL wiring.
- Direct comparison of Training_04 (manual) vs. Training_06 (adapter) for
  identical function and identical OPC-UA address space.

**Difficulty**: Advanced
**Prerequisites**: `Training_04_OPC_UA_RES`, the adapter-3.0.0 FB family
(`Bibliotheken/ExternalLibraries/adapter`).

## Summary

`Training_06_OPC_UA_RES` shows the same SR+toggle-over-OPC-UA function as
Training_04, now using the combined adapter-3.0.0 blocks
(`ASRT_AX_CLIENT_0_SUBSCRIBE_1`, `ASRT_AX_SERVER_0_CLIENT_1_0`) instead of
manually wired individual FBs — fewer connections, same address space,
same behavior.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
