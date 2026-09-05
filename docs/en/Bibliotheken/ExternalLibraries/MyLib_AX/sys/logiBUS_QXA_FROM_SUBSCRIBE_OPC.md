# logiBUS_QXA_FROM_SUBSCRIBE_OPC

![logiBUS_QXA_FROM_SUBSCRIBE_OPC_network](./logiBUS_QXA_FROM_SUBSCRIBE_OPC_network.svg)

* * * * * * * * * *

## Introduction

`logiBUS_QXA_FROM_SUBSCRIBE_OPC` drives a digital output (`logiBUS_QXA`) from a locally-subscribed OPC-UA node that is remotely written by ANOTHER device via `AX_CLIENT_1_0` - "Krauternter style" (per the source comment): the protocol (`AX_SUBSCRIBE_1`) lives INSIDE the block itself, not in the device's resource.

## Function blocks used

- **AX_SUBSCRIBE_1** (`adapter::net::AX_SUBSCRIBE_1`): subscribes to the locally-monitored address `ID` (BOOL, written remotely).
- **logiBUS_QXA** (`logiBUS::io::DQ::logiBUS_QXA`): physical digital output, identified via `Output_Q1..Q8`.

## Summary

Single-block bridge from a locally-subscribed OPC-UA value to a physical digital output - counterpart to [`logiBUS_IXA_TO_CLIENT_OPC`](./logiBUS_IXA_TO_CLIENT_OPC.md) on the sending side.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
