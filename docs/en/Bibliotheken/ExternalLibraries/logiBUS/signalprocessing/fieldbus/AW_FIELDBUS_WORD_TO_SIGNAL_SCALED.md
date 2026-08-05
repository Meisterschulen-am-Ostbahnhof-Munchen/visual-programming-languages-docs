# AW_FIELDBUS_WORD_TO_SIGNAL_SCALED
![AW_FIELDBUS_WORD_TO_SIGNAL_SCALED](./AW_FIELDBUS_WORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Introduction
The function block `AW_FIELDBUS_WORD_TO_SIGNAL_SCALED` is used to convert an incoming fieldbus word (16-bit) to a physical output value, taking into account a scaling factor and offsets. Additionally, the validity of the signal is monitored and stored via a dedicated output. The block encapsulates the typical processing chain from digital transmission to the standardized analog or signal value.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |
|----------|-------|-----------|
| INIT | EInit | Initialization request (e.g., reset of internal logic) |

### **Event Outputs**

| Event | Type | Comment |
|----------|-------|-----------|
| INITO | EInit | Confirmation of successful initialization |

### **Data Inputs**

| Name | Type | Default | Comment |
|--------|------|-----------------|-------------------------------|
| SCALE | REAL | REAL#1.0 | Scaling Factor |
| OFFSET | DINT | DINT#0 | Integer Offset (after scaling) |

### **Data Outputs**

This function block does not have separate data outputs. The output values are provided via the adapters.

### **Adapters**

| Adapter | Direction | Type (unidirectional) | Comment |
|---------|----------|----------------------|-----------|
| IN | Socket | AW | Input signal (fieldbus word) |
| OUT | Plug | AR | Processed and scaled output signal |
| VALID | Plug | AX | Boolean value: TRUE if the signal is valid |

## Functionality
The function block operates with an internal sub-FB `FIELDBUS_WORD_TO_SIGNAL_SCALED` and an edge-triggered D flip-flop (`E_D_FF`).

1. **Initialization:** An INIT event is forwarded to the sub-FB. Upon its completion, INITO is output.

2. **Data Processing:** An incoming event on `IN.E1` triggers the sub-FB (`REQ`). This reads the current word from `IN.D1`, scales it by the factor `SCALE`, adds `OFFSET`, and outputs the result to the internal output `OUT`. Simultaneously, a validity flag (`VALID`) is generated.

3. **Passing and Storage:** After successful processing (`CNF`), the output event is sent to `OUT.E1`, and the validity flag is transferred to the D flip-flop (clock edge). The stored value is stably available at the validation output (`VALID.D1`).

4. **Signal Validity:** If the incoming word is recognized as invalid (e.g., due to error bits or plausibility checks in the sub-FB), the sub-FB sets the `VALID` signal to FALSE. The flip-flop freezes this state until the next valid cycle occurs.

## Technical Features
- **Scaling with Offset:** Processing occurs in the sequence `(Wort * SCALE) + OFFSET`. This allows for linear conversions, e.g., raw values to physical units.
- **Validity Storage:** The D flip-flop decouples the dynamic validity from the output signal. A signal marked as invalid remains invalid until a valid cycle is completed – this prevents momentary misinterpretations.
- **Adapter-based interface:** The function block uses unidirectional adapters of a type system designed for fieldbus communication (`AW`, `AR`, `AX`). The exact data types of the adapters (e.g., Word, Real, Boolean) are provided by the adapter definitions.

## State overview
The function block itself does not have an explicit state machine in the XML. Its behavior results from the sequence of its internal elements:

- **Waiting for INIT:** No operation occurs before INIT is executed.
- **Operation:** After INIT, the function block listens for events at the `IN` socket. Each incoming event triggers a processing step.
- **Output:** The output event `OUT.E1` is sent immediately after the internal scaling is complete. The validity signal `VALID` is updated simultaneously.

## Application Scenarios
- **Fieldbus Analog Value Processing:** A 16-bit signal transmitted from a fieldbus (e.g., 0…65535) is converted into a physical range such as 0…10V or 4…20mA using scaling.
- **Sensor Value with Validity Flag:** Sensors that deliver data via a fieldbus protocol can also send a validity status (e.g., "Data valid" bit). This is transmitted via the `VALID` output.
- **Safety-Oriented Transmission:** If the fieldbus word contains an error bit, the sub-FB `VALID` can set it to FALSE, causing downstream logic to recognize the signal as invalid.

## Comparison with Similar Function Blocks
Unlike simple word-to-signal converters (e.g., `FIELDBUS_WORD_TO_SIGNAL`), `AW_FIELDBUS_WORD_TO_SIGNAL_SCALED` features integrated validity storage and separate adapters for output and validity. This reduces wiring in the application and simplifies the handling of temporary errors. Function blocks without offset/scaling logic would require external computation blocks.

## Conclusion
AW_FIELDBUS_WORD_TO_SIGNAL_SCALED` is a compact, functional function block for conditioning fieldbus signals. It combines scaling, offset, and validity monitoring in a reusable module. The adapter-based interface and stored validity make it particularly suitable for industrial controls where signal quality and simple parameterization are paramount.
