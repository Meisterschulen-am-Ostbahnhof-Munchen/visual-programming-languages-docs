# AX_AE_MERGE
## Introduction
The AX_AE_MERGE function block allows you to merge a pure event signal (**AE**) with a combined event-data signal (**AX**). The result is an AX signal flow where the data bit from the AX branch is preserved but can be triggered by either source.
This is particularly useful when a cyclic event (e.g., from a `AE_CYCLE`) needs to force a status check or action in an AX-based data stream without modifying the data itself.
![AX_AE_MERGE](AX_AE_MERGE.svg)
## Interface Structure

### **Adapter**
- **IN_AX** (Socket): Primary input (event `E1` + data `D1`).
- **IN_AE** (Socket): Additional event input (only event `E1`).
- **OUT** (Plug): Merged output (event from both inputs, data only from `IN_AX`).

## Functionality
When an event arrives at `IN_AX`, it is passed to the output along with the current value of `D1`. When an event arrives at `IN_AE`, an event is also triggered at the output, with the *last known* value of `IN_AX.D1` present at the output.

## ⚖️ Comparison with similar building blocks

In many exercises (e.g., with the blinker in `Uebung_007a3_AX`), a `AX_OR_2` was incorrectly used to feed a `AE` event (from `AE_CYCLE`) into a `AX` data stream.

- **AX_OR_2**: Expects two fully functional AX adapters. Connecting an AE adapter is technically incorrect, as the data value for one of the inputs remains undefined.
- **AX_AE_MERGE**: Is designed precisely for this mixed operation. It ensures that the event is passed through while the data source (`IN_AX`) remains uniquely defined.

**AX_OR_2**: Expects two fully functional AX adapters. Connecting an AE adapter is technically incorrect, as the data value for one of the inputs remains undefined. ## Technical Features

✔ **Event Merge**: Internally uses a `E_MERGE`.

✔ **Data Preservation**: No data is modified, only additional triggering occurs.

✔ **Clean Typing**: Prevents the direct connection of dissimilar adapter types.

## Application Scenarios
- **Blinker Logic**: A `AE_CYCLE` regularly triggers the transmission of the current state of a `AX_SR` flip-flop.
- **Status Refresh**: A timer regularly triggers the transmission of the current AX state.
- **Multiple Triggering**: An AX signal flow should also be triggered by external AE events (e.g., button clicks).

## 🛠️ Related exercises
* [Uebung_007a3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a3_AX.md)
* [Uebung_008_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_008_AX.md)
* [Uebung_009_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_009_AX.md)

