# SoftKeySRT_ASRT_AX

![SoftKeySRT_ASRT_AX_network](./SoftKeySRT_ASRT_AX_network.svg)

* * * * * * * * * *

## Introduction

`SoftKeySRT_ASRT_AX` bundles 3 softkeys (set/reset/toggle) and a `GreenWhiteBackground1_AX` (on the toggle softkey) behind a single `ASRT_AX` plug (bidirectional: set/reset/toggle go out, state comes in). A pure HMI block with no OPC-UA involvement - the SR+toggle counterpart of [`SoftKeySR_ASR_AX`](./SoftKeySR_ASR_AX.md).

## Function blocks used

- **SoftKey_SET / SoftKey_RESET / SoftKey_TOGGLE** (`isobus::UT::io::Softkey::Softkey_IE`, `InputEvent=SK_RELEASED`): the 3 physical softkeys.
- **ASRT_3EVENTS_TO_SRT** (`adapter::conversion::unidirectional::ASRT_3EVENTS_TO_SRT`): converts the 3 softkey events into an ASRT adapter event triple.
- **SPLIT** (`adapter::events::bidirectional::ASRT_TO_ASRT_AX_SPLIT`): splits the bidirectional `ASRT_AX` traffic to `OUT` and to the background element.
- **GreenWhiteBackground_AX** (SubApp, type `MyLib::sys::GreenWhiteBackground1_AX`): status color on the toggle softkey.

## Summary

Reusable set/reset/toggle-with-status block, bundled behind an `ASRT_AX` adapter - the HMI counterpart of [`Uebung_010e_PC_A_OPC_Adapter`](./Uebung_010e_PC_A_OPC_Adapter.md)/[`Uebung_010e_PC_B_OPC_Adapter`](./Uebung_010e_PC_B_OPC_Adapter.md).

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
