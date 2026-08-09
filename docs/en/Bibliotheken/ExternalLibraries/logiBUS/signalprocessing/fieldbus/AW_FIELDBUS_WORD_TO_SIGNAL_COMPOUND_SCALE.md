# AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE

![AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE](./AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE.svg)

* * * * * * * * * *
## Introduction

The function block **AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** converts a 16-bit word received via a fieldbus into a scaled signal value. The word is multiplied byte by byte by different scaling factors, an offset is added, and the result is output as a normalized signal. Additionally, a validity signal is provided to indicate whether the incoming value is valid.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-------|----------------------------|
| INIT | EInit | Initialization Request |

### **Event Outputs**

| Event | Type | Description |
|----------|-------|-----------------------------|
| INITO | EInit | Initial Confirmation |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------------|------|-------------|-------------------------------------------|
| SCALE_HIGH | REAL | 0.256 | Scaling factor for the upper byte |
| SCALE_LOW | REAL | 0.001 | Scaling factor for the lower byte |
| OFFSET | DINT | 0 | Additive offset after scaling |

### **Data Outputs**

The FB does not have its own data outputs. The output data is provided via the adapters listed below.

### **Adapters**

| Adapter | Type (Direction) | Description |
|---------|-------------------------------------|---------------------------------------|
| IN | `adapter::types::unidirectional::AW` | Incoming 16-bit word |
| OUT | `adapter::types::unidirectional::AR` | Output signal (scaled) |
| VALID | `adapter::types::unidirectional::AX` | Validation signal (TRUE = valid) |

## Functionality

After successful initialization (INIT event → INITO), the FB begins responding to incoming data via the **IN** adapter. As soon as the event **IN.E1** is received, the 16-bit word currently present at **IN.D1** is processed:

1. **Byte-wise scaling**

The upper byte (bits 15…8) is multiplied by `SCALE_HIGH`, the lower byte (bits 7…0) by `SCALE_LOW`.

2. **Offset addition**

The sum of both scaled byte values is incremented by the configured `OFFSET`.

3. **Output**

The result is passed to the **OUT** adapter (event **OUT.E1** with data **OUT.D1**).

4. **Validity Handling**

An internal flip-flop (`E_D_FF`) is clocked in parallel. The validity status (signal **VALID**) is taken from the internal **VALID** output of the scaling module and is retained until the next valid signal.

The internal flip-flop ensures that the validity signal is only updated upon the next input event. This guarantees a stable signal state at the output.

## Technical Features

- **Compound Scaling**

Separate scaling of the upper and lower bytes allows the processing of fieldbus signals encoded in two differently scaled byte halves (e.g., temperature or pressure values with range and resolution).

- **Integrated Flip-Flop**

The validity output is implemented using an edge-triggered D flip-flop. This ensures that the validity signal is only updated upon a new input event, guaranteeing a stable output.

- **Configurable Parameters**

Scaling and offset are freely adjustable via the data inputs and can be changed at runtime.

- **Initialization**

Before first use, the function block (FB) must be initialized with the INIT event. This resets the internal states.

## State Overview

The FB has an internal state represented by the flip-flop `E_D_FF`:

| State | Description |
|---------|-------------------------------------------------------------------|
| UNVALID | No valid signal. The **VALID** output returns FALSE. |
| VALID | Valid signal detected. The **VALID** output displays TRUE. |

The state changes with each new input event (i.e., with each word transmission) according to the validity information of the internal scaling module.

## Application Scenarios

- **Analog Value Acquisition via Fieldbus**

A fieldbus device sends a 16-bit raw value, where the upper byte represents a coarse value (e.g., 0…255) and the lower byte a fine value (e.g., 0…1000). The physical measured value is calculated using `SCALE_HIGH` and `SCALE_LOW`.

- **Process Data Preparation**

A controller requires several scaled signals whose validity must be monitored. The function block combines scaling and validation in a single block.

- **Gateway Function**

This function block can be used as a converter between a fieldbus protocol (word-based) and an internal signal protocol (with a validity flag).

## Comparison with Similar Function Blocks

- **FIELDBUS_WORD_TO_SIGNAL** (simple)

This function block scales the entire 16-bit word by a single factor. The compound function block, on the other hand, allows byte-by-byte scaling.

- **SCALE** (general)

A universal scaling function block without a fieldbus interface. This function block integrates the fieldbus adapters and validity management.

- **BADAPTER_STATUS**

Returns only a status regarding validity, without scaling. The compound function block combines both functions.

## Conclusion

The **AW_FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** is a specialized function block for processing fieldbus word signals with different scaling for the upper and lower bytes. Its integrated validity management via a flip-flop makes it particularly suitable for safety-critical or application-specific signal processing in automation technology. Thanks to its configurable parameters and clearly structured interface, it can be easily integrated into higher-level control logic.
