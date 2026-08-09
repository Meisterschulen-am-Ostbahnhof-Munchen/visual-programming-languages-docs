# AL_FIELDBUS_LWORD_TO_SIGNAL

![AL_FIELDBUS_LWORD_TO_SIGNAL](./AL_FIELDBUS_LWORD_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction

The function block `AL_FIELDBUS_LWORD_TO_SIGNAL` filters and passes a fieldbus signal of type `LWORD`. It only passes the input value to the output if the corresponding valid signal is set. The valid status is provided via a separate output and stabilized by an internal flip-flop. The block is implemented as a composite function block and encapsulates the signal processing logic and the valid signal state.
## Interface Structure

### **Event Inputs**

- **`IN.E1`** (via socket `IN`): Event to request signal processing. An incoming event triggers the mirroring of the input value to the output and updates the validity status.

### **Event Outputs**

- **`OUT.E1`** (via plug `OUT`): Event output after successful processing. Signals that the current output value (`OUT.D1`) is valid.
- **`VALID.E1`** (via plug `VALID`): Event output simultaneously with `OUT.E1`. Confirms the update of the validity signal (`VALID.D1`).

### **Data Inputs**

- **`IN.D1`** (via socket `IN`, type: `LWORD`): The fieldbus signal to be processed. The value is passed unchanged to the output, provided the internal validity signal is active.

### **Data Outputs**

- **`OUT.D1`** (via plug `OUT`, type: `LWORD`): The filtered output signal. Contains the value of `IN.D1` if the signal is valid; otherwise, the last valid value is retained (due to the internal behavior of the function block used, `FIELDBUS_LWORD_TO_SIGNAL`).
- **`VALID.D1`** (via plug `VALID`, type: `BOOL`): Indicates whether the currently output signal is valid. The value is buffered by an internal flip-flop (E_D_FF) and updated with each processing cycle.

### **Adapter**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| `IN` | Socket | `adapter::types::unidirectional::AL` | Receives the event and data signal from an upstream component. |
| `OUT` | Plug | `adapter::types::unidirectional::AL` | Sends the filtered signal and associated event to subsequent function blocks. |
| `VALID` | Plug | `adapter::types::unidirectional::AX` | Sends the validity status as a Boolean value and an acknowledgment event. |

## Functionality

This function block operates as a composite function block with the following internal logic:

1. An incoming event at `IN.E1` triggers the internal function block `FIELDBUS_LWORD_TO_SIGNAL` via its `REQ` input.
2. This internal function block (FB) reflects the value of `IN.D1` to its output `OUT` and simultaneously generates a Boolean signal `VALID` indicating whether the value is valid.
3. The internal FB's `CNF` event is distributed to three destinations:
- It triggers the output plug `OUT.E1`, so the filtered value (`OUT.D1`) is passed to the next processing stage.
- It triggers the `CLK` input of the flip-flop `E_D_FF`.
4. The `VALID` signal of the internal function block is applied to the `D` input of the flip-flop. On each rising edge of the clock (triggered by `CNF`), the flip-flop takes this value and outputs it to `Q`.
5. The output `Q` of the flip-flop is set to `VALID.D1`, and the simultaneous event `VALID.E1` is triggered by the flip-flop event `EO`.

This ensures that the validity status is only passed to the Valid output once the signal processing is complete. The output value `OUT.D1` corresponds to the input value `IN.D1`, provided it was recognized as valid; otherwise, the last valid value is retained (depending on the implementation of the internal function block `FIELDBUS_LWORD_TO_SIGNAL`).

## Technical Features

- **Composite Architecture:** The functionality is implemented through an internal network consisting of a specialized function block (`FIELDBUS_LWORD_TO_SIGNAL`) and an edge-triggered flip-flop (E_D_FF). This enables a modular and testable implementation.
- **State Maintenance:** The validity status is stored via a flip-flop. This ensures that the valid output remains stable between processing cycles and is only updated upon new events.
- **Unidirectional Adapters:** All interfaces are implemented as unidirectional adapters (AL or AX), which allows for a clear separation of event and data flow.
- **Licensing:** This function block is available under the Eclipse Public License 2.0 (Copyright HR Agrartechnik GmbH).

## State Overview

This function block does not have an explicit ECC, as it is a composite function block. The internal state logic is limited to the flip-flop `E_D_FF`, which has two states:

| State | Q (VALID.D1) | Meaning |
|---------|---------------|------------|
| RESET (Initial) | FALSE | Signal is invalid (initial). |
| SET | TRUE | Signal is valid after a valid value has been detected. |

The state change occurs with each incoming event at `CLK` (from `CNF`) depending on the `D` input (from the internal `VALID` signal). The state is maintained until the next event arrives.

## Application Scenarios

- **Fieldbus Signal Processing:** Acquisition of LWORD signals (e.g., from a CANopen or Profibus network) and their transmission only if the status is valid.
- **Filtering of Invalid Values:** If a sensor temporarily delivers invalid measured values, the function block transmits the last valid value and signals the invalidity via `VALID.D1`.
- **Synchronization of Multiple Paths:** Due to the separate outputs for signal and valid, downstream function blocks can process both pieces of information simultaneously.

## Comparison with Similar Function Blocks

Simpler function blocks like `MOVE` or `REPEAT` pass incoming values unfiltered, without validation. `AL_FIELDBUS_LWORD_TO_SIGNAL` extends this functionality with validation logic and a separate validation output. Other function blocks from the `logiBUS` library might offer similar tasks for other data types (e.g., `WORD` or `BOOL`), but they are not specifically designed for `LWORD`.

## Conclusion

The `AL_FIELDBUS_LWORD_TO_SIGNAL` Function Blockis a specialized composite component for the reliable transmission of fieldbus signals while adhering to a validity criterion. Its combination of signal processing and state management makes it ideal for safety-critical or quality-conscious applications in automation technology. The clearly defined adapter interfaces facilitate integration into existing 4diac IDE projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
