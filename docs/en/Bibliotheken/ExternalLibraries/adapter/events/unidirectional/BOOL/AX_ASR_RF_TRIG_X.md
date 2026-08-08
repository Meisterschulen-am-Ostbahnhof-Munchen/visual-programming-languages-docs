# AX_ASR_RF_TRIG_X
![AX_ASR_RF_TRIG_X](./AX_ASR_RF_TRIG_X.svg)

* * * * * * * * * *
The function block **AX_ASR_RF_TRIG_X** detects the rising and falling edges of a Boolean signal. It maps the detected edges to a set/reset output signal using crossed mapping: The rising edge triggers a reset operation, and the falling edge triggers a set operation. The block is implemented as a pure adapter block and internally uses the standard function block `E_RF_TRIG`.
The function block has no direct event or data inputs/outputs at the interface level. All communication takes place via two specified adapters.

None (Event control is handled via the **QI** adapter)

None (Event output is handled via the **Q** adapter)

None (Data input is handled via the **QI** adapter)

None (Data output is handled via the **Q** adapter)

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapter**

| Adapter | Type | Direction | Description |
|---------|-----|-----------|--------------|
| **QI** | `adapter::types::unidirectional::AX` | Socket | Receives the Boolean signal to be checked for edges. Contains the event `E1` (trigger) and the data word `D1` (value). |
| **Q** | `adapter::types::unidirectional::ASR` | Plug | Outputs the set/reset signals. The corresponding actions are signaled via the events `SET` (falling edge) and `RESET` (rising edge). |

## Functionality
An instance of the standard function block `E_RF_TRIG` is used in the block's FB network. The connections are configured as follows:

- The event input `QI.E1` triggers edge detection and is connected to `E_RF_TRIG.EI`.
- The data value `QI.D1` is forwarded to `E_RF_TRIG.QI`.
- The output event `E_RF_TRIG.EF` (falling edge) is assigned to the adapter output `Q.SET`.
- The output event `E_RF_TRIG.ER` (rising edge) is assigned to the adapter output `Q.RESET`.

This configuration results in the desired "crossed mapping":

- **Rising edge** at the input value → **RESET** pulse at the output.
- **Falling edge** at the input value → **SET** pulse at the output.

- The function block is implemented entirely as an adapter function block, i.e., It does not have its own event/data interfaces, but communicates exclusively via the defined adapters **QI** and **Q**.
- The inverse assignment of edges (Rising → Reset, Falling → Set) is a special feature compared to the standard use of `E_RF_TRIG`.
- The implementation follows the IEC 61499-1 specification and uses the `adapter::events::unidirectional` library.

The function block does not have its own state machine. Internal edge detection is performed by the integrated function block `E_RF_TRIG`, whose state logic (waiting for edge) is responsible for the functionality.

- **Reverse Set/Reset Logic**: In controllers where an active HIGH state is to be reset by a rising edge and set by a falling edge.

- **Simplification of Adapter Chains**: By encapsulating the inverse logic in a separate function block, the network structure becomes clearer.

- **`E_RF_TRIG`** (IEC 61499 Standard): Provides a rising edge on `ER` and a falling edge on `EF`. `AX_ASR_RF_TRIG_X` inverts this assignment.
- **`E_RS_TRIG`**: Detects only rising edges. This function block detects both edges and assigns them to different outputs.
- **`AX_ASR_TRIG_X`**: Possible alternative variants with different mapping logic differ in their edge-output assignment.

The function block `AX_ASR_RF_TRIG_X` offers specialized edge detection with inverted output assignment. By using adapters, it integrates seamlessly into ad-hoc 61499 communication and enables clear, reusable encapsulation of this logic. It is particularly suitable for scenarios where the standard mapping of `E_RF_TRIG` does not meet the desired behavior.

## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion