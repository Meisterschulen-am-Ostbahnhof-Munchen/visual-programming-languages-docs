# AUS_FIELDBUS_USINT_TO_SIGNAL
![AUS_FIELDBUS_USINT_TO_SIGNAL](./AUS_FIELDBUS_USINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction
The function block `AUS_FIELDBUS_USINT_TO_SIGNAL` is used to pass a USINT signal from a fieldbus adapter, taking a validity check into account. It mirrors the input value to the output if the signal is recognized as valid. An additional adapter outputs the validity status. The internal logic uses a dedicated fieldbus conversion block and an edge-triggered D flip-flop for synchronization.
## Interface Structure
### **Event Inputs**

| Name | Description |

|-------------|--------------|

| `IN.E1` | Event received via adapter `IN` (socket) that triggers processing. |

### **Event Outputs**

| Name | Description |

|-------------|--------------|

| `OUT.E1` | Event output via adapter `OUT` (plug) after successful mirroring of the valid signal. |

| `VALID.E1` | Event output via adapter `VALID` (plug) after updating the validity status. |

### **Data Inputs**

| Name | Type | Description |

|-------------|-----|--------------|

| `IN.D1` | USINT (implicit) | Input data value that is checked for validity and mirrored. |

### **Data Outputs**

| Name | Type | Description |

|-------------|-----|--------------|

| `OUT.D1` | (analogous to IN) | Output data value that mirrors the input value if the signal is valid. |

| `VALID.D1` | BOOL | Validation flag: `TRUE` if the input signal is recognized as valid, otherwise `FALSE`. |

### **Adapter**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| `IN` | `adapter::types::unidirectional::AUS` | Socket | Receives the raw signal (event + data) from the fieldbus. |

| `OUT` | `adapter::types::unidirectional::AUS` | Plug | Passes the validated signal to downstream components. |

| `VALID` | `adapter::types::unidirectional::AX` | Plug | Provides the validity status (event + BOOL). |

## Functionality
The function block (FB) reacts to an incoming event `IN.E1`. This triggers the internal function block `FIELDBUS_USINT_TO_SIGNAL`, which processes the data value `IN.D1` and delivers two results:

- An output value (`OUT`)
- A validation signal (`VALID`)

The output value is passed directly to `OUT.D1` and acknowledged via `OUT.E1`. Simultaneously, the validation signal is fed to the data input `D` of the D flip-flop `E_D_FF`. The flip-flop is clocked by the same event (via `CFN`), so the validity status is held stably at `Q` and output at `VALID.D1`. Only after the clock pulse is `VALID.E1` triggered.

In summary: The output `OUT` mirrors the input `IN`, provided the signal is recognized as valid in the fieldbus module. The validity status is stored using edge triggering.

## Technical Features
- **Adapter-based communication:** All inputs and outputs are implemented via standardized unidirectional adapters (`AUS`, `AX`), which enable a clear separation between event and data paths.
- **Edge-Triggered Validation:** A D flip-flop ensures that the validity state is only updated upon an event (rising edge) – this prevents glitches and asynchronous state transitions.
- **Reused Internal Function Block:** The function block `FIELDBUS_USINT_TO_SIGNAL` handles the actual fieldbus-specific conversion and validity check; the outer function block serves purely as wrapper and synchronization logic.

## State Overview
The internal state is defined by the D flip-flop `E_D_FF`. It has two states:

| State | Description |

|---------|---------------|

| `Q = FALSE` (Initial) | Output `VALID.D1` indicates "invalid". After each event, the current value of `VALID` (`D`) is used. |

| `Q = TRUE` | Output `VALID.D1` indicates "valid". The state remains stable until the next event. |

State transitions occur exclusively on each rising edge of the clock signal (event `CNF` of the fieldbus function block).

## Application Scenarios
- **Fieldbus Signal Conditioning:** A sensor sends USINT values via a fieldbus; the function block filters out invalid values and only forwards valid data and a clear validity status.

`` - **Safety-Oriented Data Transmission:** In control systems that rely on valid signals (e.g., in agricultural technology), this function block (FB) can be used as a simple validation stage.

- **Interface Adaptation:** The function block connects a fieldbus-specific adapter (e.g., CANopen, PROFIBUS) to a standardized logic adapter that only triggers events when the data is valid.

## Comparison with Similar Function Blocks
- **Simple Mirror Function Blocks** (e.g., `MOVE` or `AUS_MIRROR`): These pass the signal without validation. This FB additionally offers validation logic and a separate validity output.
- **Fieldbus Converters Without Memory:** Some function blocks output the validity signal directly and without a clock signal. Using a flip-flop here avoids metastable states and ensures deterministic output.

## Conclusion

The `AUS_FIELDBUS_USINT_TO_SIGNAL` is a useful function block for the clean, validated forwarding of USINT signals from fieldbus systems. The combination of a specialized fieldbus module and an edge-triggered flip-flop ensures reliable separation of valid and invalid data. The adapter-based interface facilitates integration into modular control architectures.
