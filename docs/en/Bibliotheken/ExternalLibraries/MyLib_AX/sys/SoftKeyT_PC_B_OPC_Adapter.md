# SoftKeyT_PC_B_OPC_Adapter

![SoftKeyT_PC_B_OPC_Adapter_network](./SoftKeyT_PC_B_OPC_Adapter_network.svg)

* * * * * * * * * *

## Introduction

`SoftKeyT_PC_B_OPC_Adapter` is the adapter-bundled variant of [`Uebung_010d_PC_B_OPC`](./Uebung_010d_PC_B_OPC.md) (device B, station 12): the `CLIENT_0`/`SERVER_0` trigger and `AX_CLIENT_1_0` are bundled behind a SINGLE `AE_AX_SERVER_0_CLIENT_1_0` block behind one bidirectional adapter connection; `AE_AX_AX_SPLIT` feeds both `DigitalOutput_Q1` and the toggle flip-flop logic (`AE_AX_T_FF`). Counterpart: [`SoftKeyT_PC_A_OPC_Adapter`](./SoftKeyT_PC_A_OPC_Adapter.md).

## Function blocks used

- **TRIGGER** (`adapter::net::AE_AX_SERVER_0_CLIENT_1_0`): bundles server reception (`ID_TRIGGER_METHOD`) and state feedback (`ID_STATE_WRITE`).
- **SPLIT** (`adapter::events::bidirectional::AE_AX_AX_SPLIT`): splits the trigger to the physical output + the flip-flop logic.
- **FLIPFLOP** (`adapter::events::bidirectional::AE_AX_T_FF`): toggle flip-flop logic as an adapter block.
- **DigitalOutput_Q1** (`logiBUS::io::DQ::logiBUS_QXA`): physical output.

## Summary

Adapter-bundled variant of `Uebung_010d_PC_B_OPC`: network protocol and flip-flop logic as reusable adapter blocks instead of individually wired FBs.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
