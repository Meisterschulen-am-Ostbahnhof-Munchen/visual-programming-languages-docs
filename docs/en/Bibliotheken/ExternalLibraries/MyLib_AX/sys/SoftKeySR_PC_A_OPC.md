# SoftKeySR_PC_A_OPC

![SoftKeySR_PC_A_OPC_network](./SoftKeySR_PC_A_OPC_network.svg)

* * * * * * * * * *

## Introduction

`SoftKeySR_PC_A_OPC` is the device-A side (station 11, 192.168.1.11) of a PC-to-PC OPC-UA set/reset pattern: 2 softkeys (set/reset) each call their own argument- and return-value-less OPC-UA method on device B (`CLIENT_0`, 2 distinct methods - like Training_04, but without toggle). `GreenWhiteBackground1_AX` on the set softkey shows the flip-flop state locally monitored from device B. "SUB style": the protocol lives in the `MyLib::sys` composite, not in the device's resource - counterpart: [`SoftKeySR_PC_B_OPC`](./SoftKeySR_PC_B_OPC.md).

## Function blocks used

- **SoftKey_SET / SoftKey_RESET** (`isobus::UT::io::Softkey::Softkey_IE`): the two physical softkeys.
- **TRIGGER_SET_CLIENT / TRIGGER_RESET_CLIENT** (`iec61499::net::CLIENT_0`): each calls its own argument-less remote method on device B (`ID_SET_CALL`/`ID_RESET_CALL`).
- **STATE_SUBSCRIBE** (`adapter::net::AX_SUBSCRIBE_1`): subscribes to the flip-flop state under `ID_STATE_READ`.
- **GreenWhiteBackground_AX** (SubApp, type `MyLib::sys::GreenWhiteBackground1_AX`): displays the state at the set softkey.

## Summary

Device-A side of a set/reset RPC pattern with 2 distinct method calls (instead of one string parameter) and state feedback.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
