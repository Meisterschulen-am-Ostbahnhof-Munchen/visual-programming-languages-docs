# Uebung_010e_PC_A_OPC_Adapter

![Uebung_010e_PC_A_OPC_Adapter_network](./Uebung_010e_PC_A_OPC_Adapter_network.svg)

* * * * * * * * * *

## Introduction

`Uebung_010e_PC_A_OPC_Adapter` is the adapter-bundled variant of [`Uebung_010e_PC_A_OPC`](./Uebung_010e_PC_A_OPC.md) (device A, station 11): HMI (3 softkeys + `GreenWhiteBackground`) and OPC-UA trigger are separated. [`SoftKeySRT_ASRT_AX`](./SoftKeySRT_ASRT_AX.md) bundles the HMI behind an `ASRT_AX` plug; `ASRT_AX_CLIENT_0_SUBSCRIBE_1` bundles the 3 `CLIENT_0` instances + `AX_SUBSCRIBE_1` behind an `ASRT_AX` socket. Counterpart: [`Uebung_010e_PC_B_OPC_Adapter`](./Uebung_010e_PC_B_OPC_Adapter.md).

## Function blocks used

- **SoftKeySRT_ASRT_AX** (SubApp, type `MyLib::sys::SoftKeySRT_ASRT_AX`): 3 softkeys + status display, bundled behind an `ASRT_AX` plug.
- **TRIGGER** (`adapter::net::ASRT_AX_CLIENT_0_SUBSCRIBE_1`): bundles 3 method calls (`ID_SET_CALL`/`ID_RESET_CALL`/`ID_TOGGLE_CALL`) and the state subscription (`ID_STATE_READ`) behind a single `ASRT_AX` socket.

## Summary

Adapter-bundled variant of `Uebung_010e_PC_A_OPC`: HMI and network protocol cleanly separated, reusable via [`SoftKeySRT_ASRT_AX`](./SoftKeySRT_ASRT_AX.md).

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
