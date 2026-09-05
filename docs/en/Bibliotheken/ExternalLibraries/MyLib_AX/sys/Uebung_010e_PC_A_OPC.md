# Uebung_010e_PC_A_OPC

![Uebung_010e_PC_A_OPC_network](./Uebung_010e_PC_A_OPC_network.svg)

* * * * * * * * * *

## Introduction

`Uebung_010e_PC_A_OPC` is the device-A side (station 11, 192.168.1.11) of the PC-to-PC OPC-UA variant of exercise 010e (SR+toggle flip-flop via 3 softkeys): 3 softkeys (set/reset/toggle) each call their own argument- and return-value-less OPC-UA method on device B (`CLIENT_0`, 3 distinct methods instead of 1 string parameter - option A). `GreenWhiteBackground1_AX` on the toggle softkey shows the flip-flop state locally monitored from device B. Counterpart: [`Uebung_010e_PC_B_OPC`](./Uebung_010e_PC_B_OPC.md).

## Function blocks used

- **SoftKey_SET / SoftKey_RESET / SoftKey_TOGGLE** (`isobus::UT::io::Softkey::Softkey_IE`): the 3 physical softkeys.
- **TRIGGER_SET_CLIENT / TRIGGER_RESET_CLIENT / TRIGGER_TOGGLE_CLIENT** (`iec61499::net::CLIENT_0`): each its own remote method (`ID_SET_CALL`/`ID_RESET_CALL`/`ID_TOGGLE_CALL`).
- **STATE_SUBSCRIBE** (`adapter::net::AX_SUBSCRIBE_1`): subscribes to the flip-flop state under `ID_STATE_READ`.
- **GreenWhiteBackground_AX** (SubApp, type `MyLib::sys::GreenWhiteBackground1_AX`): displays the state at the toggle softkey.

## Summary

Device-A side of a set/reset/toggle RPC pattern with 3 distinct method calls and state feedback.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
