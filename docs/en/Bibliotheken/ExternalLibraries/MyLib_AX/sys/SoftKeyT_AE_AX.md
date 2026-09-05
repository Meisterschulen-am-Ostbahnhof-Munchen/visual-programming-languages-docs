# SoftKeyT_AE_AX

![SoftKeyT_AE_AX_network](./SoftKeyT_AE_AX_network.svg)

* * * * * * * * * *

## Introduction

`SoftKeyT_AE_AX` bundles 1 SoftKey (trigger) and a `GreenWhiteBackground1_AX` behind a single `AE_AX` plug (bidirectional: trigger goes out, state comes in). A pure HMI block with no OPC-UA involvement - reusable in any network that needs a single trigger softkey with a state display.

## Function blocks used

- **SoftKey_UP_F1** (`isobus::UT::io::Softkey::Softkey_IE`, `InputEvent=SK_RELEASED`): physical softkey.
- **AE_EVENT_TO_E** (`adapter::conversion::unidirectional::AE_EVENT_TO_E`): converts the softkey event into an AE adapter event.
- **GreenWhiteBackground_AX** (SubApp, type `MyLib::sys::GreenWhiteBackground1_AX`): status color on the same object.
- **SPLIT** (`adapter::events::bidirectional::AE_TO_AE_AX_SPLIT`): splits the bidirectional `AE_AX` traffic to the external plug `OUT` and internally to the background element.

## Program flow and connections

`SoftKey_UP_F1.IND` -> `AE_EVENT_TO_E.REQ` -> `SPLIT.IN` -> `OUT` (outward) and `SPLIT.AX_OUT` -> `GreenWhiteBackground_AX.DI1` (state display).

## Summary

Reusable single-key trigger-with-status block, bundled behind an `AE_AX` adapter - the HMI counterpart of the PC_A/PC_B OPC network blocks like [`SoftKeyT_PC_A_OPC_Adapter`](./SoftKeyT_PC_A_OPC_Adapter.md).

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
