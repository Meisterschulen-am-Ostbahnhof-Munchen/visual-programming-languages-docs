# AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED

![AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED](./AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Introduction

The function block `AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED` is used to receive an incoming byte-shaped signal via an adapter, process it with a configurable scaling factor and offset, and provide the result via an output adapter. Simultaneously, the validity of the signal is indicated via a separate adapter. This function block is specifically designed for use in fieldbus environments where raw data needs to be converted into physical or standardized values.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-----|---------------|
| `INIT` | EInit | Initialization request (e.g., for setting parameters) |

### **Event Outputs**

| Event | Type | Description |
|----------|-----|--------------|
| `INITO` | EInit | Confirmation of successful initialization |

### **Data Inputs**

| Name | Type | Initial Value | Description |
| ------ | ----- | -------------- | -------------- |
| `SCALE` | REAL | 1.0 | Scaling factor applied to the raw value |
| `OFFSET` | DINT | 0 | Integer offset added after scaling |

### **Data Outputs**

The module has no independent data inputs or outputs – input/output is handled exclusively via adapters.

### **Adapters**

| Adapter | Type | Direction | Description |
| --------- | ----- | ----------- | -------------- |
| `IN` | AB (Adapter Type A→B) | Socket | Receives the raw BYTE signal |
| `OUT` | AR (Adapter Type A→R) | Plug | Outputs the scaled signal |
| `VALID` | AX (Adapter Type A→X) | Plug | Signals whether the current output value is valid (TRUE = valid) |

## Functionality

1. After successful initialization (`INIT` → `INITO`), the function block becomes operational.
2. As soon as a new BYTE arrives via the `IN` adapter (event `E1`), the event is forwarded to the internal function block `FIELDBUS_BYTE_TO_SIGNAL_SCALED`.
3. This internal block calculates the output value: `OUT = IN * SCALE + OFFSET`. Simultaneously, a validity signal (`VALID`) is generated.
4. After the calculation is complete, the result is output via the `OUT` adapter (`OUT.E1`). Simultaneously, the validity signal is temporarily stored in a D flip-flop (module `E_D_FF`) and output via the `VALID` adapter.
5. The valid status is maintained until a new signal is processed. An invalid state (e.g., due to a missing input) can be set externally using appropriate logic.

The process is purely event-driven: Each incoming event triggers exactly one processing step.

## Technical Features

- **Scaling and Offset**: The configuration of SCALE (REAL) and OFFSET (DINT) allows for flexible adaptation to different measurement ranges.
- **Adapter Interface**: The use of IEC 61499 adapters allows for loose coupling and easy reusability in different fieldbus contexts.
- **Valid Storage**: The D flip-flop (E_D_FF) ensures that the validity status remains stable until the next signal arrives.
- **Initialization**: The function block has its own INIT path to reliably set internal parameters (SCALE, OFFSET).

## State Overview

The function block does not define an explicit state machine (ECC). Processing is exclusively event-driven:

- **In idle state**, it waits for an event.
- **On INIT**, the internal function block is initialized.
- **On IN.E1**, the translation is triggered, and the results are output asynchronously.

Thus, the function block behaves like a combinational, but clocked, function.

## Application Scenarios

- **Fieldbus Signal Conditioning**: Receiving raw data (e.g., pressure sensor values as BYTE) and converting it into physical units (e.g., bar) using scaling and offset.
- **Normalization of Measured Values**: Adapting to a standardized value range, e.g., 0…100% or -50…+50°C.
- **Validity Check**: If the sensor only sends a signal when the measurement is valid, the Validation Adapter can be used to control downstream blocks.

## Comparison with Similar Function Blocks

- **AB_FIELDBUS_BYTE_TO_SIGNAL** (without "SCALED"): Does not offer scaling/offset but transmits the raw value directly.
- **AB_FIELDBUS_SIGNAL_SCALED** (based on REAL): May work directly with REAL values but requires a different adapter configuration.

This module combines BYTE-to-REAL conversion with compact, configurable scaling and an output validity signal.

## Conclusion

AB_FIELDBUS_BYTE_TO_SIGNAL_SCALED` is a specialized function block for the flexible conversion of raw BYTE data into scaled values with integrated validity signaling. Its adapter-based interface allows for easy integration into IEC 61499 systems and makes it particularly suitable for fieldbus applications where raw values need to be transformed into physical quantities.
