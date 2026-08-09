# AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED

![AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED](./AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED.svg)
*Image of the function block: not available*

* * * * * * * * * *
## Introduction

The function block **AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED** is used to convert a received UDINT value (unsigned 32-bit integer) from a fieldbus protocol into a scaled signal and only forward it to the output if the input signal is marked as valid. It represents a combined solution for scaling and signal validity checking and is primarily used in automation technology for LogiBUS applications.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|-------|--------|-------------------------------|
| INIT | EInit | Initialization Request |

### **Event Outputs**

| Name | Type | Comment |
|-------|--------|-------------------------------|
| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment | Initial Value |
|--------|-------|------------------------------------|------------------|
| SCALE | LREAL | Scaling Factor | LREAL#1.0 |
| OFFSET | DINT | Offset Added After Scaling | DINT#0 |

### **Data Outputs**

No separate data outputs – the scaled data is provided via the adapter output `OUT`.

### **Adapter**

| Name | Type | Direction | Comment |
|-------|------------------|----------|-------------------------------|
| IN | unidirectional::AUDI | Input | Fieldbus UDINT input signal |
| OUT | unidirectional::ALR | Output | Scaled signal (if valid) |
| VALID | unidirectional::AX | Output | Validation flag (TRUE = valid) |

## Functionality

The function block operates internally as a composite block. It consists of a sub-function block `FIELDBUS_UDINT_TO_SIGNAL_SCALED` (which performs the actual scaling) and an edge-triggered D flip-flop `E_D_FF`.

- A UDINT value (via `IN.D1`) and an event (`IN.E1`) are received via the adapter `IN`.
- The incoming value is forwarded to the internal function block `FIELDBUS_UDINT_TO_SIGNAL_SCALED`, which multiplies the value by `SCALE` and then adds `OFFSET`. The result is available at the output `OUT.D1`.

`` - Simultaneously, the internal function block generates a validity signal (`VALID`) indicating whether the received raw value is considered valid.

- This validity signal is fed to the D flip-flop at its data input (`D`). The rising edge of the processing event (`CNF`) clocks the flip-flop (`CLK`).
- The instantaneous, synchronized validity signal is present at the flip-flop's output (`Q`) and is output via the adapter (`VALID.D1`).
- The event (`OUT.E1`) is triggered simultaneously with the update of the output data, allowing downstream function blocks to retrieve the new values.

## Technical Features

- The function block (FB) is implemented as a **composite FB**, meaning its functionality is represented by an internal network of other function blocks. This allows for a clear separation of scaling and validity logic.
- Initialization occurs via the `INIT` event, which is forwarded to the internal FB. After successful initialization, `INITO` is output.
- The scaling factors `SCALE` and `OFFSET` are set during initialization and cannot be changed at runtime, as they are not updated via separate events.
- The use of a D flip-flop ensures that the validity state remains stable until the next valid data value is processed.

`` - This function block is designed for use in the LogiBUS environment (package `logiBUS::signalprocessing::fieldbus`).

## State Overview

This function block does not have explicit states in the sense of a state machine. Its internal logic is executed purely data-flow controlled via the event chain:

1. **Initialization Phase**: After receiving `INIT`, the internal function block is initialized and `INITO` is sent.
2. **Data Processing Phase**: An incoming `IN.E1` triggers the scaling and validity check. Upon completion, `OUT.E1` and the output data are updated.

## Application Scenarios

- **Scaling of Fieldbus Signals**: When a fieldbus delivers a UDINT value (e.g., a sensor counter reading) that needs to be converted into a physical unit, e.g., scaling and offset.
- **Validity Check**: Only valid measured values should be passed on to the controller. The flag `VALID` can be evaluated by a higher-level safety block, for example.
- **Coupling of LogiBUS and IEC 61499 Systems**: The function block serves as a bridge between the LogiBUS protocol and standardized function blocks.

## Comparison with Similar Function Blocks

- **FIELDBUS_UDINT_TO_SIGNAL_SCALED** (bare scaling block): This block performs only the scaling, without the validity check and without the memory logic. The present composite function block extends it to include the status management of the validity flag.
- **Standard IEC 61499 Scaling Blocks** (e.g., `SCALE`): Usually implemented as simple arithmetic blocks, they often lack integrated validity logic and connectivity to fieldbus adapters.

## Conclusion

The function block `AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED` offers a compact, reusable solution for scalable signal processing with integrated validity checking in LogiBUS environments. It combines scaling, offset, and an edge-triggered validity lock, ensuring that only valid and correctly scaled values are present at the output. Thanks to its composite structure, it is easily extensible and readily integrates into existing IEC 61499 projects.
