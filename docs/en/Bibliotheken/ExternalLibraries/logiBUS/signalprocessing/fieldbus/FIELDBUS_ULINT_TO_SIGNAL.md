# FIELDBUS_ULINT_TO_SIGNAL

![FIELDBUS_ULINT_TO_SIGNAL](./FIELDBUS_ULINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction

The function block **FIELDBUS_ULINT_TO_SIGNAL** serves as a filter block for fieldbus signals of type `ULINT`. It checks whether an incoming value lies within the valid signal range and, depending on the result, either outputs it unchanged or sets the output to a defined invalid value. The VALID output signal indicates the signal validity status.
This block is particularly suitable for use in safety-critical or quality-monitoring applications where invalid or faulty fieldbus values must be reliably detected and handled.

## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| REQ | Normal execution request – triggers the processing of the input value IN. The event output CNF is sent after the action is completed. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| CNF | Execution confirmation – sent after the calculation of OUT and VALID. |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------|-------|------------------------------------------------|--------------|
| IN | ULINT | `LWORD_TO_ULINT(NOT_AVAILABLE_LWM)` | Input signal (raw value from the fieldbus) |

*Note:* `NOT_AVAILABLE_LWM` is a constant imported from the library `FIELDBUS_SIGNAL`, representing an invalid or unavailable signal value.

### **Data Outputs**

| Name | Type | Initial Value | Description |
|-------|-------|----------------------------|--------------|
| OUT | ULINT | `16#0000000000000000` | Filtered output value – corresponds to IN if valid, otherwise 0. |
| VALID | BOOL | `FALSE` | Signal validity – `TRUE` if valid input, otherwise `FALSE`. |

### **Adapter**

This component has no adapter interfaces.

## Functionality

After an event at the **REQ** input, the following algorithm is executed:

1. Check: **IN** ≤ `LWORD_TO_ULINT(VALID_SIGNAL_LW)`

VALID_SIGNAL_LW` is an imported constant from the `FIELDBUS_SIGNAL` library and defines the upper limit of the valid value range.

2. **Case – Valid Input** (Condition met):
- `OUT` := `IN`
- `VALID` := `TRUE`
3. **Case – Invalid Input** (Condition not met):
- `OUT` := `0`
- `VALID` := `FALSE`

The **CNF** event output is then triggered.

## Technical Features

- The function block operates deterministically and requires only a single processing stage.
- The threshold values `NOT_AVAILABLE_LWM` and `VALID_SIGNAL_LW` are defined as external constants and stored centrally in the library `FIELDBUS_SIGNAL`. They can be adjusted without modifying the function block.
- The output value for an invalid signal is set to 0, which represents a defined "invalidity value" in many fieldbus systems.
- The initial value of `IN` is declared as "not available," so the function block provides a defined state even without a prior event.

## State Overview

The function block is implemented as a **SimpleFB** and has only one state:

| State | Description |
|---------|--------------|
| REQ | Input state: Waiting for event REQ. Upon entry, the algorithm `REQ` is executed, and then the output `CNF` is sent. Afterward, the function block remains in the same state.

There are no further states or branches – the functionality is purely process-oriented.

## Application Scenarios

- **Fieldbus Signal Conditioning:** A sensor delivers a ULINT value that is only physically meaningful within a specific range (e.g., rotational speed, pressure). The function block filters out invalid measurements.
- **Safety Chain:** In a safety-related controller, faulty or deviating fieldbus values are detected and replaced by a defined substitute value (0). Simultaneously, a validity signal is provided for the downstream logic.
- **Quality Monitoring:** The VALID output can be used to monitor data integrity, e.g., to trigger alarms or switch to alternative signal sources.

## Comparison with Similar Function Blocks

The 4diac framework includes other filter blocks for different data types, such as `FIELDBUS_DINT_TO_SIGNAL` or `FIELDBUS_REAL_TO_SIGNAL`. All of these share the principle of validity checking using a predefined upper limit. This particular block is specifically designed for the `ULINT` data type, enabling efficient and type-safe use in applications with 64-bit unsigned values.

## Conclusion

The **FIELDBUS_ULINT_TO_SIGNAL** is a simple yet reliable function block for signal validation in fieldbus environments. Its clear distinction between valid and invalid values, along with the provision of a BOOL output for validity, makes it ideally suited for use in modular automation systems where data quality and error detection are essential. The use of external constants allows for flexible adaptation to different signal ranges without modifying the component itself.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
