# AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED
![AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED](./AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block **AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED** is used for the scalable mirroring of an unsigned integer value (ULINT) into a scaled signal value (LREAL), taking validity information into account. It is implemented as a composite block and combines the actual scaling logic with a synchronized valid output. The block is designed for use in fieldbus environments where raw data (e.g., sensor values) must be converted using a linear factor and offset, and the signal's validity must be reliably transmitted.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|----------------------| | INIT | EInit | Init Request |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|-----------------------|

| INITO | EInit | Init Confirmation |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|--------|-------|--------------|-----------------------------------|

| SCALE | LREAL | 1.0 | Scaling Factor |

| OFFSET | DINT | 0 | Offset added after scaling |

### **Data Outputs**
*No explicit data outputs are available on the FB interface – output is provided via the adapters.*

### **Adapter**
#### **Socket (Input)**

| Name | Type | Comment |

|------|--------------------------------------------------|-----------|

| IN | adapter::types::unidirectional::AULI | Input |

#### **Plug (Output)**

| Name | Type | Comment |

|-------|--------------------------------------------------|---------------------|

| OUT | adapter::types::unidirectional::ALR | Filtered Output |

| VALID | adapter::types::unidirectional::AX | TRUE if Signal is VALID |

## Functionality
The function block operates in an event-driven manner. After an INIT event (at input `INIT`), the internal scaling block is initialized and acknowledged with `INITO`. The actual processing occurs with each event that arrives via the adapter `IN.E1`:

1. **Data Transfer:** The ULINT value provided by `IN.D1` is forwarded to the internal function block `FIELDBUS_ULINT_TO_SIGNAL_SCALED`.

2. **Scaling:** The internal block applies the scaling factor `SCALE` (LREAL) and the offset `OFFSET` (DINT) to the raw value, generating a scaled LREAL value and a validity signal (`VALID`).

3. **Synchronization:** The validity signal is synchronized via an edge-triggered D flip-flop (`E_D_FF`). The clock edge is provided by the internal block's ``CNF`` event.

4. **Output:** The scaled value is sent to adapter ``OUT`` via ``OUT.D1`` and the associated event ``OUT.E1``. The synchronized validity signal is output to adapter ``VALID`` via ``VALID.D1`` and the event ``VALID.E1``.

The internal scaling block is of the same type as the outer one, meaning that the scaling logic could be recursive. However, in this design, the inner instance contains the actual computational logic. The outer shell adds the synchronization of the validity information and provides the adapter interfaces.

The internal scaling block is of the same type as the outer one, meaning that the scaling logic could be recursive. ## Technical Features

- **Adapted Inputs/Outputs:** The module uses adapters exclusively for data transmission. This enables loose coupling in fieldbus and component networks.
- **Validity Synchronization:** The validation information is clocked via a D flip-flop so that it coincides with the output signal value.
- **Scaling Parameters:** `SCALE` and `OFFSET` are directly accessible as input variables and can be changed at runtime. Initial values allow immediate operation without configuration.

## State Overview

The module does not have an explicit state machine. Its behavior is determined by event control:

- **Initialized:** After successful `INIT`, the internal scaling block is ready.
- **Ready:** Data processing is triggered upon an event on `IN.E1`. Upon completion, `OUT.E1` and `VALID.E1` are triggered.
- **Error Case:** An erroneous scaling operation (e.g., overflow) is handled by the internal block; the validation signal would then be `FALSE`.

## Application Scenarios
- **Fieldbus Sensor Evaluation:** A sensor delivers a raw ULINT value via a bus (e.g., CANopen, PROFIBUS). The block scales the value into a physical unit (e.g., temperature, pressure) and passes it to the controller as LREAL, along with a validation flag.
- **Signal conditioning in agricultural machinery** (as indicated in the copyright notice): Conversion of speed, fill level, or velocity data into standardized signals for a higher-level control system.
- **Quality-assured data transmission:** When the validity of a signal (e.g., sensor error, communication failure) must be explicitly tracked, the synchronized valid output ensures consistent signals.

## Comparison with similar function blocks
- **FIELDBUS_ULINT_TO_SIGNAL** (without scaled): A direct pass without scaling – scaling is integrated here.
- **Standard scaling function blocks** (e.g., from IEC 61131-3): These often operate with simple inputs/outputs and without adapters or validity synchronization.
- **Function blocks with integrated validation:** Many fieldbus function blocks output only a single data value. This function block stands out due to its separate, clocked validity output.

## Conclusion
The **AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED** is a specialized composite function block for the scaled conversion of ULINT fieldbus data into LREAL signals with synchronized validity information. Thanks to the use of adapters and the clear separation of scaling and synchronization, it is particularly suitable for modular, safety-critical applications in automation and agricultural technology. Parameterization via `SCALE` and `OFFSET` makes it highly versatile.