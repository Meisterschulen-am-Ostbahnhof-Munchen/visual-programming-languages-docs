# AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED
![AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED](./AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Introduction
The AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED function block is used for the scalable transmission of an incoming UINT value (fieldbus signal) to an analog REAL output. It only operates if the incoming signal is marked as valid (VALID signal). An additional initialization interface allows the internal logic to be reset. The block is implemented as a composite and combines a scalable sub-block with a D flip-flop for validity storage.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| INIT | EInit | Initialization Request |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|------|-----|-------------|-----------|

| SCALE | REAL | REAL#1.0 | Scaling Factor |

| OFFSET | DINT | DINT#0 | Offset after Scaling |

### **Data Outputs**

*(No direct data outputs – outputs are via adapters)*

### **Adapters**

| Type | Name | Direction | Comment |

|-----|------|----------|-----------|

| adapter::types::unidirectional::AUI | IN | Socket | UINT input (fieldbus signal) |

| adapter::types::unidirectional::AR | OUT | Plug | Scaled REAL output |

| adapter::types::unidirectional::AX | VALID | Plug | Validation signal (TRUE = valid) |

## Functionality
The function block consists internally of two sub-function blocks: the scalable core function block `logiBUS::signalprocessing::fieldbus::FIELDBUS_UINT_TO_SIGNAL_SCALED` and a D flip-flop `E_D_FF`.

Initialization is performed via the INIT event input, which is forwarded directly to the internal core function block. The acknowledgment INITO is returned after successful initialization.

The actual signal processing is triggered by an incoming event (E1) from the IN adapter. This event triggers the core module, which processes the UINT value received via IN.D1 as follows:

- **Scaling**: `Wert_skaliert = (REAL)IN_D1 * SCALE`
- **Offset**: `Wert_skaliert = Wert_skaliert + OFFSET`

The result (REAL) is output as OUT.D1, and an event OUT.E1 is simultaneously generated. In parallel, the VALID signal (TRUE = valid, FALSE = invalid) calculated by the core module is applied to the D input of the D flip-flop. The same CNF event from the core module serves as the clock signal for the flip-flop. This ensures that the validity state is maintained at the Q output until the next clock cycle. The final validity value is output via the VALID adapter (D1) and its event E1.

This means the VALID signal is only updated after scaling is complete and remains stable until a new value arrives at the input.

## Technical Features
- **Composite Architecture**: The function block (FB) is built entirely from sub-FBs, enabling easy adaptation and reuse.
- **Validity Storage**: A D flip-flop stores the validity signal between processing cycles. This allows the output to display a defined state even when no new data is present.
- **Scaling and Offset**: Scaling is performed using a REAL factor and a DINT offset. This allows for flexible adaptation to physical units (e.g., conversion of digital values to pressure or temperature).
- **Adapter-Based Input/Output**: All signals are exchanged via standardized 61499 adapters (AUI, AR, AX), which facilitates integration into modular fieldbus systems.

## State Overview

The function block itself does not have its own state machine. The internal state is represented by the D flip-flop:

- **State Q = FALSE**: The last processed value was invalid or no value has yet been received.
- **State Q = TRUE**: The last processed value was valid and is scaled and available at the OUT output.

The state change occurs with each new event on the IN adapter (E1) when the core module provides a new VALID signal.

## Application Scenarios
- **Agricultural Sensors**: Transmission of scaled measured values (e.g., fill level, pressure) from fieldbus sensors with a validity flag.
- **Data Preprocessing**: Conversion of raw values from digital converters (e.g., 0–10 V → REAL values) with automatic validity checks.
- **Quality Assurance**: Only values marked as valid are passed on to subsequent control logic.

## Comparison with Similar Function Blocks
- **AUI_FIELDBUS_UINT_TO_SIGNAL** (without validity flag): Always outputs a scaled value, regardless of signal quality.
- **AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED** (Core): Already provides a scaled output with a validity flag, but without storage. This composite adds this storage capability and allows for more stable output between events.
- **Adapter-Based Filters**: Other function blocks use similar principles, but with specific validity conditions (e.g., time filters).

## Conclusion
The AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED offers a reliable and flexible solution for the scaled transmission of UINT fieldbus signals with explicit validity marking. The combination of scaling, offset, and stored validity signal makes it particularly suitable for safety-critical or quality-controlled applications in automation technology.
