# Uebung_010d_PC_B_OPC

![Uebung_010d_PC_B_OPC_network](./Uebung_010d_PC_B_OPC_network.svg)

* * * * * * * * * *

## Introduction

`Uebung_010d_PC_B_OPC` is the device-B side (station 12, 192.168.1.12) of the PC-to-PC OPC-UA variant of exercise 010d: receives the trigger method call from device A via `SERVER_0` (a pure RPC trigger, no value-change trick, no bridge needed), clocks the actual toggle flip-flop logic (`AX_T_FF`), drives `DigitalOutput_Q1`, and actively writes the new state back to device A via `AX_CLIENT_1_0`. Counterpart: [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC.md).

## Function blocks used

- **TRIGGER_SERVER** (`iec61499::net::SERVER_0`): receives the method call under `ID_TRIGGER_METHOD`.
- **AX_T_FF** (`adapter::events::unidirectional::AX_T_FF`): toggle flip-flop, clocked by `TRIGGER_SERVER.IND`.
- **AX_SPLIT_2** (`adapter::events::unidirectional::AX_SPLIT_2`): splits the flip-flop state to the physical output + the echo.
- **DigitalOutput_Q1** (`logiBUS::io::DQ::logiBUS_QXA`): physical output (`Output` selects `Output_Q1..Q8`).
- **STATE_CLIENT** (`adapter::net::AX_CLIENT_1_0`): actively writes the new state to device A under `ID_STATE_WRITE`.

## Summary

Device-B side: receives the trigger via RPC, holds the actual toggle logic, and actively reports the state back to device A.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
