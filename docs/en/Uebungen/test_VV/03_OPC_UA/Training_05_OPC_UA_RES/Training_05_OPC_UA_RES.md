# Training_05_OPC_UA_RES: Pure SR Flip-Flop over 2 OPC-UA Methods ("SUB style")

![Training_05_OPC_UA_RES_network](./Training_05_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Introduction

`Training_05_OPC_UA_RES` is the Set/Reset-**without**-Toggle variant of
`Training_04_OPC_UA_RES`: 2 SoftKeys (Set, Reset) instead of 3, a pure
`AX_SR` flip-flop instead of `AX_T_FF_SR`. Same "SUB style" pattern, same
Option-A method split (one method per action), but without the Toggle
action and its third SoftKey/server.

## Composites Used

| Composite | Device | Purpose |
|---|---|---|
| [`SoftKeySR_PC_A_OPC`](./SoftKeySR_PC_A_OPC_network.svg) | A (`192.168.1.11`) | 2 SoftKeys (Set/Reset) each call their own `CLIENT_0` method on Device B; `GreenWhiteBackground` at the Set SoftKey shows the monitored state |
| [`SoftKeySR_PC_B_OPC`](./SoftKeySR_PC_B_OPC_network.svg) | B (`192.168.1.12`) | 2 `SERVER_0` instances receive Set/Reset, drive `AX_SR`, switch `Output_Q1`, and write the state back via `AX_CLIENT_1_0` |

## OPC-UA Address Space

| Constant (local/remote) | Value (excerpt) | Purpose |
|---|---|---|
| `SR2_SET_LOCAL_METHOD` / `SR2_SET_REMOTE_CALL` | `.../SRFlipflop/SR2_Set` | Set method |
| `SR2_RESET_LOCAL_METHOD` / `SR2_RESET_REMOTE_CALL` | `.../SRFlipflop/SR2_Reset` | Reset method |
| `SR2_STATE_LOCAL_READ` / `SR2_STATE_REMOTE_WRITE` | `.../SRFlipflop/SR2_State` | State return channel |

Its own address namespace (`SR2_*`), separate from `SR1_*` in Training_04 —
both exercises can run unchanged, at the same time, on the same two
devices, without any OPC-UA address collision.

## Program Flow and Connections

1. **`SoftKeySR_PC_A_OPC`** (Device A): `SoftKey_SET.IND` →
   `TRIGGER_SET_CLIENT.REQ`, `SoftKey_RESET.IND` →
   `TRIGGER_RESET_CLIENT.REQ` — two independent `CLIENT_0` calls.
   `STATE_SUBSCRIBE` feeds `GreenWhiteBackground_AX.DI1` at the Set
   SoftKey.
2. **`SoftKeySR_PC_B_OPC`** (Device B): `TRIGGER_SET_SERVER.IND` →
   `AX_SR.S`, `TRIGGER_RESET_SERVER.IND` → `AX_SR.R`; the new state goes
   through `AX_SPLIT_2` to `Output_Q1` and `STATE_CLIENT` (writing back
   to Device A), just as in Training_04.

## Technical Notes

- **Reduced action set**: `AX_SR` only has `S`/`R`/`Q` — no `CLK` for
  toggling. Anyone who only needs Set/Reset saves composite complexity
  and a third method/server instance compared to Training_04.
- **Same base pattern as Training_04**: apart from the missing Toggle
  action, wiring, the write-back mechanism, and address structure are all
  identical — a good template for scaling Option A to any number of
  independent actions.

## Learning Objectives

- Pure SR flip-flop (`AX_SR`) remote-controlled over two separate OPC-UA
  methods, as a reduced variant of Training_04.
- A dedicated OPC-UA address namespace per exercise, to avoid collisions
  when running several training systems at once.

**Difficulty**: Intermediate
**Prerequisites**: `Training_04_OPC_UA_RES` (same pattern, with Toggle).

## Summary

`Training_05_OPC_UA_RES` reduces Training_04 to pure Set/Reset without
Toggle — same "SUB style"/Option-A pattern, two OPC-UA methods instead of
three, its own address namespace.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
