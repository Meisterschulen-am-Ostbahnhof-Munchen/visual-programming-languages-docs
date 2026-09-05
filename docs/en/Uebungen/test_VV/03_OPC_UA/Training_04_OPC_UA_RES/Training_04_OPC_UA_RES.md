# Training_04_OPC_UA_RES: SR+Toggle Flip-Flop over 3 OPC-UA Methods ("SUB style", Option A)

![Training_04_OPC_UA_RES_network](./Training_04_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Introduction

`Training_04_OPC_UA_RES` carries `Uebung_010e_AX` (SR+toggle flip-flop over
3 SoftKeys, see
[`Uebung_010e_AX.md`](../../../test_AX/Uebungen_doc/Uebung_010e_AX.md)) over
to two devices using the same "SUB style" pattern as
`Training_03_OPC_UA_RES`. Set, Reset, and Toggle are three **independent**
OPC-UA methods (**Option A**) — Device A calls one of three `CLIENT_0`
instances depending on which SoftKey was pressed, rather than passing a
single method a string parameter.

## Composites Used

| Composite | Device | Purpose |
|---|---|---|
| [`Uebung_010e_PC_A_OPC`](./Uebung_010e_PC_A_OPC_network.svg) | A (`192.168.1.11`) | 3 SoftKeys (Set/Reset/Toggle) each call their own `CLIENT_0` method on Device B; `GreenWhiteBackground` at the Toggle SoftKey shows the monitored state |
| [`Uebung_010e_PC_B_OPC`](./Uebung_010e_PC_B_OPC_network.svg) | B (`192.168.1.12`) | 3 `SERVER_0` instances receive Set/Reset/Toggle, drive `AX_T_FF_SR`, switch `Output_Q1`, and write the state back via `AX_CLIENT_1_0` |

## OPC-UA Address Space

Three independent method address pairs plus one state address pair, all in
`VV::const::OPC_UA::myOpcUaAddresses`:

| Constant (local/remote) | Value (excerpt) | Purpose |
|---|---|---|
| `SR1_SET_LOCAL_METHOD` / `SR1_SET_REMOTE_CALL` | `.../SRFlipflop/SR1_Set` | Set method |
| `SR1_RESET_LOCAL_METHOD` / `SR1_RESET_REMOTE_CALL` | `.../SRFlipflop/SR1_Reset` | Reset method |
| `SR1_TOGGLE_LOCAL_METHOD` / `SR1_TOGGLE_REMOTE_CALL` | `.../SRFlipflop/SR1_Toggle` | Toggle method |
| `SR1_STATE_LOCAL_READ` / `SR1_STATE_REMOTE_WRITE` | `.../SRFlipflop/SR1_State` | State return channel (`READ`/`WRITE`, as in Training_03) |

Each of the three methods has its own, independent `CLIENT_0`/`SERVER_0`
address path (`SR1_Set`, `SR1_Reset`, `SR1_Toggle`) — no method shared via a
parameter.

## Program Flow and Connections

1. **`Uebung_010e_PC_A_OPC`** (Device A): `SoftKey_SET.IND` →
   `TRIGGER_SET_CLIENT.REQ`, `SoftKey_RESET.IND` →
   `TRIGGER_RESET_CLIENT.REQ`, `SoftKey_TOGGLE.IND` →
   `TRIGGER_TOGGLE_CLIENT.REQ` — three independent `CLIENT_0` calls, one
   per SoftKey. As in Training_03, `STATE_SUBSCRIBE` feeds
   `GreenWhiteBackground_AX.DI1` at the Toggle SoftKey.
2. **`Uebung_010e_PC_B_OPC`** (Device B): three `SERVER_0` instances
   (`TRIGGER_SET_SERVER`, `TRIGGER_RESET_SERVER`,
   `TRIGGER_TOGGLE_SERVER`) each clock the matching input of `AX_T_FF_SR`
   (`S`/`R`/`CLK`); the new state goes through `AX_SPLIT_2` to
   `Output_Q1` and `STATE_CLIENT` (writing back to Device A), just as in
   Training_03.

## Technical Notes

- **Option A: one method per action** — instead of a shared method with a
  parameter (which would signal "which action"), each action gets its own
  `CLIENT_0`/`SERVER_0` address path. Simpler to wire (no parameter
  evaluation needed), but consumes three server instances instead of one.
- **Set/Reset/Toggle on one flip-flop**: `AX_T_FF_SR` is the SR+toggle-
  capable sibling of `AX_T_FF` (see `Uebung_010e_AX.md` for the local ECC
  logic).

## Learning Objectives

- Multiple independent OPC-UA methods on the same device, each with its
  own address path rather than a shared parameter.
- SR+toggle flip-flop logic (`AX_T_FF_SR`) remote-controlled over three
  separate RPC channels.

**Difficulty**: Intermediate to advanced
**Prerequisites**: `Uebung_010e_AX.SUB`, `Training_03_OPC_UA_RES` (RPC
pattern, "SUB style").

## Summary

`Training_04_OPC_UA_RES` extends the RPC pattern from Training_03 to three
independent actions (Set/Reset/Toggle), each with its own OPC-UA method
address path ("Option A") rather than a single parameterized call.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
