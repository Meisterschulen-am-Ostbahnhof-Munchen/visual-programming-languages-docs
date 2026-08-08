# AX_SEL_WSTRING

![AX_SEL_WSTRING](./AX_SEL_WSTRING.svg)

* * * * * * * * * *
## Introduction
The function block `AX_SEL_WSTRING` is used for binary selection between two inputs of type `WSTRING` (Wide String). Which of the two inputs is passed through to the output is controlled by a coupled adapter. This block combines the classic selection logic of IEC 61131-3 with the event-driven architecture of IEC 61499.

## Interface Structure
### **Event Inputs**
* **EI0**: Updates and adopts the value of the data input `IN0`.

* **EI1**: Updates and adopts the value of the data input `IN1`.


### **Event Outputs**

* **CNF**: Confirmation event. Signals that a newly selected value is present at output `OUT`.

### **Data Inputs**

* **IN0** (`WSTRING`): First selectable string input (selected when the adapter's selection signal is inactive or in its default state).

* **IN1** (`WSTRING`): Second selectable string input (selected when the adapter's selection signal is active).

### **Data Outputs**

* **OUT** (`WSTRING`): The currently selected string value.


### **Adapter**

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. A change in the state of this adapter triggers a recalculation of the output.


## Functionality
Inside the function block is a network of standard selection blocks (`F_SEL`), assignment blocks (`F_MOVE`), and event-driven D flip-flops (`E_D_FF` and `E_D_FF_ANY`):

1. **Data Storage:** The input data at `IN0` and `IN1` is temporarily stored in internal memory upon the arrival of the respective events `EI0` and `EI1`, respectively.

2. **Selection:** The adapter `G` provides the selection signal. As soon as the signal at the adapter changes, the event is processed, and the internal component `F_SEL` switches the corresponding string (`IN0` or `IN1`) to the output.

3. **Event Filtering:** The output event `CNF` is routed through a value-change D flip-flop (`E_D_FF_ANY_OUT`). This ensures that a `CNF` event is primarily output when the selection signal `G` changes or the value at the output actually updates.


## Technical Features
* **Unicode Support:** By using the data type `WSTRING`, international character sets and special characters can be processed without problems, unlike the standard `STRING`.

* **Resource Efficiency:** Internal event filtering minimizes unnecessary cascading of calculations in the subsequent system. An output event is generated selectively.

## State Overview
* **Selector G = 0 (i.e., inactive):** `OUT` corresponds to the value of `IN0`.

* **Selector G = 1 (i.e., active):** `OUT` corresponds to the value of `IN1`.

* **Value Change on Inactive Channel:** For example, if `IN1` is updated while `G` points to `IN0`, the output `OUT` does not change. No `CNF` event is triggered until the selector switches.

## Application Scenarios

* **Language Switching on HMIs:** Dynamic switching of operating and display texts (e.g., between German and English) via a central control signal.

* **Status and Error Message Systems:** Selection of a specific text message based on the status of a system or sensor.

* **Recipe Control:** Switching parameter sets or process names in text format during batch changes.


## Comparison with Similar Function Blocks

* **Standard `SEL` (IEC 61131-3):** The classic `SEL` function block operates purely in a data flow-oriented manner without event interfaces. `AX_SEL_WSTRING` extends this functionality for event-based control in IEC 61499 and uses adapters for clean structuring.

* **`MUX` (Multiplexer):** While a multiplexer enables selection from a multitude of channels, `AX_SEL_WSTRING` specializes in a lean, binary selection (either/or).

## Conclusion
The `AX_SEL_WSTRING` is a specialized and optimized function block for event-driven text selection. By encapsulating the internal memory and selection logic, it significantly simplifies application diagrams in 4diac-ide and ensures a clean interface design using adapters.