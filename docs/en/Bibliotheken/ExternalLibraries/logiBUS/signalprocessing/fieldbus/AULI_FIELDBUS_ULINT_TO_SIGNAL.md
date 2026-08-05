# AULI_FIELDBUS_ULINT_TO_SIGNAL
![AULI_FIELDBUS_ULINT_TO_SIGNAL](./AULI_FIELDBUS_ULINT_TO_SIGNAL.svg)
* * * * * * * * * *
## Introduction
The function block **AULI_FIELDBUS_ULINT_TO_SIGNAL** serves as a composite module for processing a ULINT value from a fieldbus. It mirrors the incoming value to the output if the signal is recognized as valid and also outputs a synchronized validity signal. The module combines an internal fieldbus converter with a D flip-flop to ensure clocked, reliable signal transmission.
## Interface Structure
The module does not have traditional top-level event or data ports, but communicates exclusively via adapters. These are implemented as sockets (inputs) and plugs (outputs).

### **Event Inputs**

| Port | Name | Description |

|------|-------------|--------------|

| `IN.E1` | Event Input (via Socket IN) | Triggers the processing of a new ULINT value. |

### **Event Outputs**

| Port | Label | Description |

|------|-------------|--------------|

| `OUT.E1` | Event Output (via Plug OUT) | Signals completion of the output of the mirrored value. |

| `VALID.E1` | Event Output (via Plug VALID) | Indicates that the validity signal has been updated. |

### **Data Inputs**

| Port | Label | Data Type | Description |

|------|-------------|----------|-------------|

| `IN.D1` | Data Input (via Socket IN) | ULINT | The fieldbus value to be processed. |

### **Data Outputs**

| Port | Label | Data Type | Description |

|------|-------------|-----------|-------------|

| `OUT.D1` | Data Output (via Plug OUT) | ULINT | The mirrored input value (if valid). |

| `VALID.D1` | Data Output (via Plug VALID) | BOOL | Validation signal (TRUE = value is valid). |

### **Adapter**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `IN` | Socket (Input) | `adapter::types::unidirectional::AULI` | Receives the ULINT value and the associated event. |

| `OUT` | Plug (Output) | `adapter::types::unidirectional::AULI` | Outputs the processed ULINT value and an event. |

| `VALID` | Plug (Output) | `adapter::types::unidirectional::AX` | Provides the validity signal (BOOL) and an event. |

## Functionality
The function block operates internally with two sub-functions:

1. **FIELDBUS_ULINT_TO_SIGNAL** – A fieldbus converter that converts a ULINT value into a signal and simultaneously generates a validity signal (BOOL).

2. **E_D_FF** – An edge-triggered D flip-flop that receives the validity signal synchronously with the converter's event.

**Process:**

1. An event at input `IN.E1` starts the processing.

2. The input value `IN.D1` is passed to the internal converter.

3. The converter calculates the output value `OUT` and the `VALID` signal.

4. The result `OUT` is immediately mirrored to the output adapter `OUT.E1` / `OUT.D1`.

5. Simultaneously, the `VALID` signal is passed to the flip-flop and clocked by the event `CNF`.

6. The flip-flop output `Q` is output to the adapter `VALID.D1`, generating an event `VALID.E1`.

`` `` ``VALID`` ``Q` ``VALID.D1` ``VALID.E1` ... This ensures that the output value and the validity signal are always updated consistently and synchronously.

## Technical Features
- **Adapter-Based Interface**: The function block uses standardized unidirectional adapters (`AULI`, `AX`), enabling loose coupling and reusability.
- **Synchronization via Flip-Flop**: The validity signal is edge-triggered to avoid clock and glitch issues.
- **Composite Structure**: The internal logic is implemented as a network of two standard function blocks, increasing maintainability and transparency.
- **No Direct Event/Data Ports**: All communication occurs via adapters, facilitating integration into adapter-based architectures.

## State Overview
The function block itself is stateless (purely combinatorial with clocked takeover). The internal flip-flop `E_D_FF` has two states:

- **Q = FALSE**: No valid signal (initial or after an invalid value).
- **Q = TRUE**: Valid signal is present.

A state diagram for the entire function block is not required, as the behavior is fully described by the event and data flows.

## Application Scenarios
- **Fieldbus Signal Conditioning**: A ULINT value (e.g., counter reading, position value) is received from a fieldbus, checked for validity, and passed on to a controller or visualization system.
- **Quality Indication**: A Boolean signal indicating validity (e.g., "Data valid" / "Data faulty") is provided along with the data value.
- **Safety-Oriented Transmission**: By synchronously receiving the validity signal, errors in the data line can be detected and signaled.

## Comparison with Similar Function Blocks
- **Simple Pass-Through Function Block**: A simple `MOVE` or `REPEAT` function block forwards the value without validation. `AULI_FIELDBUS_ULINT_TO_SIGNAL` adds explicit validity checking and signaling.
- **FIELDBUS_ULINT_TO_SIGNAL (Single)**: This core function block already provides the validity signal, but without edge-triggered synchronization. This composite function block enhances signal quality with a flip-flop.
- **Adapter-Based Function Blocks**: Specifically designed for use in 4diac environments that rely on adapter communication; other function blocks with direct ports are less flexible.

## Conclusion
`AULI_FIELDBUS_ULINT_TO_SIGNAL` is a robust, adapter-based function block for the reliable transmission of a ULINT fieldbus signal with validity indication. The combination of converter and flip-flop ensures synchronized and reliable signal output. Its clear interface structure makes it particularly suitable for modular automation solutions that rely on loosely coupled adapters.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]