# OFF_AX_SEL_OFF

![AUS_AX_SEL_AUS](./AUS_AX_SEL_AUS.svg)

*(No image available)*

* * * * * * * * * *

The function block **OFF_AX_SEL_OFF** is a binary selector (multiplexer) for IEC 61499 systems. It is used to select between two input adapters (`IN0` and `IN1`) based on the state of a selection signal (selector `G`) and to forward the selected value to the output adapter (`OUT`).

The block uses unidirectional adapter structures, which enables clean encapsulation of data and event streams and simplifies visual routing within the development environment.

Since this function block is implemented as a composite network and is entirely adapter-based, it has no direct, traditional event or data channels at its main level. All communication is bundled within the adapters.

*No direct event inputs are available (events are received via the adapter interfaces).*

*No direct event outputs are available (events are sent via the adapter interfaces).*

*No direct data inputs are available.*

*No direct data outputs are available.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

#### **Sockets (Input Adapters)**

- **G** (Type: `adapter::types::unidirectional::AX`):
- **Description:** Selector signal.
- **Content:** Contains the selection event `E1` and the associated data signal `D1` (usually interpreted as Boolean), which determines which input is enabled.
- **IN0** (Type: `adapter::types::unidirectional::AUS`):
- **Description:** First selectable input. Passed to the output when the selector `G` is in the state `FALSE` (or `0`).
- **Content:** Event `E1` and data signal `D1` (Data Type: `USINT`).
- **Content:** Event `E1` and data signal `D1` (Data Type: `USINT`). * **IN1** (Type: `adapter::types::unidirectional::AUS`):
- **Description:** Second selectable input. It is routed to the output when selector `G` is in state `TRUE` (or `1`).
- **Content:** Event `E1` and data signal `D1` (Data Type: `USINT`).

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AUS`):
- **Description:** The selected output. Receives the data and events of the currently enabled input.
- **Content:** Event `E1` and data signal `D1` (Data type: `USINT`).

 ## Functionality

The module encapsulates an internal network that extracts and processes the adapter signals and routes them via standardized IEC 61131-3 and IEC 61499 modules:

1. **Data Acquisition:** As soon as an event (`G`, `IN0`, or `IN1`) arrives at one of the input adapters (`G`, `IN0`, or `IN1`), the corresponding data value (`D1`) is temporarily stored using flip-flops (`E_D_FF` or `E_D_FF_ANY`).
2. **Value Transfer:** The values of inputs `IN0` and `IN1` are transferred to the central selection block via copy operations (`F_MOVE` with the data type `USINT`).
3. **Selection:** The internal block `F_SEL` (standard IEC 61131-3 selector) decides based on the state of `G.D1`:
- If `G.D1` = `0` (or `FALSE`), the value of `IN0` is set to the output.
- If `G.D1` = `1` (or `TRUE`), the value of `IN1` is set to the output.
4. **Output:** The result is passed via another flip-flop (`E_D_FF_ANY_OUT`) to the output adapter `OUT`, triggering the event `OUT.E1` simultaneously with the provision of the data on `OUT.D1`.
- **Event-driven:** The output is updated immediately with every change to the inputs or the selector and assigned a new event.
- **Data Type Specific:** Internally, the processing of the data channels is designed for the type `USINT` (defined by the attributes of the internal `F_MOVE` instances).
- **Adapter Encapsulation:** Facilitates the clean design of application diagrams, as complex data and event pairs are represented as a single connection (bus).

Since this is a composite function block without its own Execution Control Chart (ECC), its behavior is determined purely by the signal flow:

| State Selector (`G.D1`) | Trigger Event | Output Activity (`OUT`) |
|:---|:---|:---|
| `0` / `FALSE` | Any (`G.E1`, `IN0.E1`, `IN1.E1`) | Returns the value of `IN0.D1`; triggers `OUT.E1`. |
| `1` / `TRUE` | Any (`G.E1`, `IN0.E1`, `IN1.E1`) | Returns the value of `IN1.D1`; Triggers `OUT.E1`. |

- **Setpoint Switching:** Dynamic switching of a target variable (e.g., a speed or stage of type `USINT`) between automatic operation (`IN1`) and manual operation (`IN0`).
- **Recipe Selection:** Selection between two predefined operating modes or parameter sets in a machine via a higher-level controller.
- **Fault Protection:** Rapid switching to a substitute value (`IN0`) if a main signal path is faulty.
- ## Comparison with Similar Modules

Compared to the standard selection module `F_SEL` from the IEC 61131-3 library, `AUS_AX_SEL_AUS` offers the decisive advantage of being able to work directly with manufacturer-specific or standardized unidirectional adapters (`AUS` and `AX`). While event and data lines in IEC 61499 have to be laboriously wired individually for `F_SEL`, this is done fully automatically within the module.

Compared to the standard selection module `F_SEL` from the IEC 61131-3 library, `AUS_AX_SEL_AUS` offers the crucial advantage of being able to work directly with manufacturer-specific or standardized unidirectional adapters (`AUS` and `AX`). While event and data lines in `F_SEL` have to be laboriously wired individually according to IEC 61499, this is done fully automatically within the module itself. ## Conclusion

The **AUS_AX_SEL_AUS** function block represents an important bridge for modern, adapter-based IEC 61499 architectures. It combines the proven selection logic of IEC 61131-3 with the advantages of event-driven adapter coupling, thus significantly contributing to the clarity and maintainability of control software.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
