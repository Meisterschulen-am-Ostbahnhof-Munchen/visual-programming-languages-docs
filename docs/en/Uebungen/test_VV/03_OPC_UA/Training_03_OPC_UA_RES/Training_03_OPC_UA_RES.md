# Training_03_OPC_UA_RES: Toggle Flip-Flop over OPC-UA ("SUB style")

![Training_03_OPC_UA_RES_network](./Training_03_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Introduction

`Training_03_OPC_UA_RES` carries `Uebung_010d_AX` (SoftKey-triggered toggle
flip-flop with `GreenWhiteBackground`, see
[`Uebung_010d_AX.md`](../../../test_AX/Uebungen_doc/Uebung_010d_AX.md)) over
to two physically separate FORTE devices, linked via OPC-UA.

Unlike `Training_02_OPC_UA_RES` ("RES style": the communication blocks live
in each device's `<Resource>`), this exercise uses the **"SUB style"**: the
entire protocol — SoftKey input, OPC-UA client/server blocks, and
`GreenWhiteBackground` — lives inside two reusable `MyLib::sys` composites
(`Uebung_010d_PC_A_OPC`, `Uebung_010d_PC_B_OPC`). As a result, the `.sys`
file itself contains **no** FBs at all, only two `SubApp` instances and the
device `Mapping`.

## Composites Used

| Composite | Device | Purpose |
|---|---|---|
| [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC_network.svg) | A (Station 11, `192.168.1.11`) | `SoftKey_F1` triggers an argument- and return-value-less OPC-UA method call to Device B via `CLIENT_0`; `GreenWhiteBackground` shows the state Device B monitors locally |
| [`Uebung_010d_PC_B_OPC`](./Uebung_010d_PC_B_OPC_network.svg) | B (Station 12, `192.168.1.12`) | Receives the method call via `SERVER_0`, clocks `AX_T_FF` (toggle flip-flop), drives `Output_Q1`, and actively writes the new state back to Device A via `AX_CLIENT_1_0` |

Device A needs **no** `AX_T_FF` of its own — the SoftKey press is a pure
RPC trigger, no value-change trick required. On Device A, an
`AX_SUBSCRIBE_1` (`STATE_SUBSCRIBE`) locally reads the state written by
Device B and feeds `GreenWhiteBackground_AX`.

## OPC-UA Address Space

Both constant pairs live in `VV::const::OPC_UA::myOpcUaAddresses`:

| Constant | Value | Used by |
|---|---|---|
| `FF1_TRIGGER_LOCAL_METHOD` | `opc_ua[CREATE_METHOD;/Objects/ToggleFF/FF1_Trigger]` | `TRIGGER_SERVER` on Device B (locally created method) |
| `FF1_TRIGGER_REMOTE_CALL` | `opc_ua[CALL_METHOD;opc.tcp://192.168.1.12:4840#;/Objects/ToggleFF/FF1_Trigger]` | `TRIGGER_CLIENT` on Device A (calls the same method remotely) |
| `FF1_STATE_LOCAL_READ` | `opc_ua[READ;/Objects/ToggleFF/FF1_State,1:s=FF1_State]` | `STATE_SUBSCRIBE` on Device A (locally monitored state node) |
| `FF1_STATE_REMOTE_WRITE` | `opc_ua[WRITE;opc.tcp://192.168.1.11:4840#;/Objects/ToggleFF/FF1_State,1:s=FF1_State]` | `STATE_CLIENT` on Device B (writes the same node remotely) |

Unlike `Q1_LOCAL_READ`/`Q1_REMOTE_WRITE` in Training_02 (pure value
transport), `FF1_TRIGGER_*` is a real OPC-UA **method** (RPC), not a
written/read node — a good match for the event-driven SoftKey press, which
carries no value.

## Program Flow and Connections

1. **`Uebung_010d_PC_A_OPC`** (Device A): `SoftKey_UP_F1.IND` (SoftKey
   released) triggers `TRIGGER_CLIENT.REQ` — `CLIENT_0` calls the remote
   method `FF1_TRIGGER_REMOTE_CALL`. In parallel, `STATE_SUBSCRIBE`
   (`AX_SUBSCRIBE_1`) delivers the state written by Device B to
   `GreenWhiteBackground_AX.DI1` via an adapter connection.
2. **`Uebung_010d_PC_B_OPC`** (Device B): `TRIGGER_SERVER.IND` (method
   called) clocks `AX_T_FF.CLK` — the toggle flip-flop inverts its state.
   `AX_SPLIT_2` fans the new state out to two destinations:
   `DigitalOutput_Q1.OUT` (local, drives `Output_Q1`) and
   `STATE_CLIENT.IN` (`AX_CLIENT_1_0`, actively writes the state back to
   `FF1_STATE_REMOTE_WRITE` on Device A).
3. **Mapping/Devices**: `App_OPC_UA_RES2.SubApp_PC_A` → `FORTE_PC_A`,
   `SubApp_PC_B` → `FORTE_PC_B`; one `E_TRIG('EInit')` per device
   initializes its composite at startup.

## Technical Notes

- **RPC instead of value transport**: `FF1_TRIGGER_*` uses `CALL_METHOD`/
  `CREATE_METHOD` rather than `READ`/`WRITE` — the right ACTION type for an
  argument-less, stateless trigger (a key press carries no value that would
  need transferring).
- **"SUB style" vs. "RES style"**: the protocol lives entirely inside the
  reusable `MyLib::sys` composite here, not in the device's Resource. The
  benefit: the same composite can be instantiated unchanged on any device
  playing the same role (A or B) — the `.sys` file stays reduced to mapping
  and device setup.
- **No value-change trick needed**: since the trigger is a genuine RPC
  method (not an observed value), Device A needs no `AX_T_FF` of its own —
  unlike pure read/write-based signaling, which would have to simulate an
  edge change.

## Learning Objectives

- OPC-UA method calls (`CALL_METHOD`/`CREATE_METHOD`) as an RPC alternative
  to `READ`/`WRITE` for event-triggered, valueless triggers.
- The "SUB style" distribution pattern: protocol in the reusable composite
  rather than in the resource.
- The return path (state from B to A) via a second, independent read/write
  address channel, separate from the trigger channel.

**Difficulty**: Intermediate
**Prerequisites**: `Uebung_010d_AX.SUB` (local toggle flip-flop pattern),
`Training_02_OPC_UA_RES` (RES-style distribution, `AX_CLIENT_1_0`/
`AX_SUBSCRIBE_1`).

## Summary

`Training_03_OPC_UA_RES` distributes `Uebung_010d_AX` across two devices
and introduces two concepts beyond Training_02: OPC-UA method calls as an
RPC alternative to pure value transport, and the "SUB style" pattern, where
the protocol lives in the reusable composite rather than the resource.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
