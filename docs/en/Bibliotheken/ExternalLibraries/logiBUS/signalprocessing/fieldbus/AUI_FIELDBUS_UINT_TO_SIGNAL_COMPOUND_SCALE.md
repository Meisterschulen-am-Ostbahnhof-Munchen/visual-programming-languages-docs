# AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE
![AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE](./AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE.svg)
* * * * * * * * * *
## Introduction
The function block `AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` is used to convert and scale a 16-bit value received via an AUI fieldbus adapter into a scalable signal. The block mirrors the input value to the output, provided the validity signal is active, and performs compound scaling on the upper and lower bytes of the input value. An offset can be added after scaling. The output is provided via a unidirectional AR adapter, while the validity is signaled via an AX adapter. The block is specifically designed for industrial fieldbus protocols where user data consists of two separately scalable byte ranges.
## Interface Structure
### **Event Inputs**

| Event | Type | Description |

|----------|-----|-------------|

| INIT | EInit | Initialization request; sets the function block to a defined start state. |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|-------------|

| INITO | EInit | Initialization confirmation; sent after successful initialization. |

### **Data Inputs**

| Variable | Type | Initial Value | Description |

|----------|-----|--------------|-------------|

| SCALE_HIGH | REAL | 0.256 | Scaling factor for the upper byte of the incoming value. |

SCALE_LOW | REAL | 0.001 | Scaling factor for the lower byte of the incoming value. |

OFFSET | DINT | 0 | Integer offset added after scaling. |

### **Data Outputs**
This function block has no separate data outputs other than `VarDeclaration`. The output data is provided via the adapters `OUT` and `VALID`.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|-------------|

IN | Socket | adapter::types::unidirectional::AUI | Input for the fieldbus data value to be processed. |

OUT | Plug | adapter::types::unidirectional::AR | Output of the scaled value (e.g., REAL or DINT, depending on the internal function block). |

VALID | Plug | adapter::types::unidirectional::AX | Output signal: TRUE if the current output value is valid. |

## Functionality
The function block operates as a composite function block that uses an internal function block `FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` in combination with an edge-triggered D flip-flop (`E_D_FF`). The processing proceeds as follows:

1. **Input Event**: An event at the event input `IN.E1` of the AUI adapter triggers the processing of the current data value `IN.D1`.

2. **Scaling**: The incoming 16-bit value is split into an upper and a lower byte. Each byte is multiplied by its corresponding scaling factor (`SCALE_HIGH`, `SCALE_LOW`). The result of both scaling operations is summed and added to `OFFSET`. The calculated value is then passed to `OUT.D1` via the data output of the internal module.

3. **Validity Signal**: In parallel, the internal component generates a logic signal `VALID`, indicating whether the calculated value is valid. This signal is clocked by the D flip-flop with the completion event `CNF` and forwarded to the `VALID.D1` adapter. This ensures that the validity signal is only activated if the value has actually been recalculated.

`` 4. **Output Event**: The internal block's `CNF` event is used to control both the output adapter `OUT` (event `E1`) and the `VALID` adapter (event `E1`).

5. **Initialization**: The `INIT` event is forwarded directly to the internal block; the initialization confirmation `INITO` is returned accordingly.

## Technical Features
- **Compound Scaling**: Unlike simple scaling blocks, this function block allows separate weighting of the two byte halves of a 16-bit value. This is useful when a sensor value is composed of two different physical quantities (e.g., an integer and a decimal place).
- **Integrated Validation Logic**: The D flip-flop makes the `VALID` signal edge-triggered and only activates it when new calculations are actually performed. This prevents unwanted output when no update is available.
- **Initialization Pass-Through**: The INIT/INITO events are passed transparently through the composite block, ensuring that the internal scaling block is correctly initialized.

## State Overview
The block itself does not have an explicit state machine at the composite level. Operational readiness is established by the `INIT` event. After successful initialization, the function block waits for incoming events at the `IN` adapter and processes them cyclically. As long as no INIT event has been sent, the function block is in an undefined state (no output, `VALID` inactive).

## Application Scenarios
- **Fieldbus Interfaces**: Conversion of analog sensor values transmitted as a 16-bit word with separate scaling factors for the integer and decimal parts (e.g., temperature/pressure values with decimal places).
- **Measurement Processing**: Scaling of digital input signals from fieldbus controllers that deliver raw data in two-byte ranges.
- **Signal Validation**: Used in safety-related applications where only valid and correctly calculated values may be passed on to the subsequent controller.

## Comparison with Similar Function Blocks
Unlike simple scaling blocks (e.g., `SCALE` or `UINT_TO_REAL`), this function block offers differentiated processing of the two byte halves. It is specifically designed for data formats where the upper and lower bytes represent different physical units or scaling ranges. Alternative function blocks would have to implement this logic manually by splitting, scaling separately, and then adding the values, which increases the implementation effort.

## Conclusion
The `AUI_FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` is a specialized yet flexible function block for processing fieldbus signals. Its ability to process an incoming 16-bit word with two different scaling factors and to control the validity of the output signal makes it a valuable component in IEC-61499-based automation systems, especially when it comes to integrating devices with compounded data formats.
