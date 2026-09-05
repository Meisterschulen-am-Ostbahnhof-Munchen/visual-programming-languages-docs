# Uebung_010e_PC_B_OPC_Adapter

![Uebung_010e_PC_B_OPC_Adapter_network](./Uebung_010e_PC_B_OPC_Adapter_network.svg)

* * * * * * * * * *

## Introduction

`Uebung_010e_PC_B_OPC_Adapter` is the adapter-bundled variant of [`Uebung_010e_PC_B_OPC`](./Uebung_010e_PC_B_OPC.md) (device B, station 12): the 3 `SERVER_0` instances + `AX_CLIENT_1_0` are bundled behind a SINGLE `ASRT_AX_SERVER_0_CLIENT_1_0` block behind one bidirectional adapter connection; `ASRT_AX_AX_SPLIT` feeds both `DigitalOutput_Q1` and the SR/toggle flip-flop logic (`ASRT_AX_T_FF_SR_2`). Counterpart: [`Uebung_010e_PC_A_OPC_Adapter`](./Uebung_010e_PC_A_OPC_Adapter.md).

## Function blocks used

- **TRIGGER** (`adapter::net::ASRT_AX_SERVER_0_CLIENT_1_0`): bundles server reception (`ID_SET_METHOD`/`ID_RESET_METHOD`/`ID_TOGGLE_METHOD`) and state feedback (`ID_STATE_WRITE`).
- **SPLIT** (`adapter::events::bidirectional::ASRT_AX_AX_SPLIT`): splits to the physical output + the flip-flop logic.
- **FLIPFLOP** (`adapter::events::bidirectional::ASRT_AX_T_FF_SR_2`): combined SR/toggle flip-flop logic as an adapter block.
- **DigitalOutput_Q1** (`logiBUS::io::DQ::logiBUS_QXA`): physical output.

## Summary

Adapter-bundled variant of `Uebung_010e_PC_B_OPC`: network protocol and SR/toggle flip-flop logic as reusable adapter blocks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
