# FIELDBUS_LWORD_TO_SIGNAL
![FIELDBUS_LWORD_TO_SIGNAL](./FIELDBUS_LWORD_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction
The function block **FIELDBUS_LWORD_TO_SIGNAL** converts an LWORD value from a fieldbus system into a valid signal. It accepts an input value and passes it on unchanged only if its value lies within a defined valid range. Otherwise, a zero value is output, and the validity is signaled as `FALSE`.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| REQ | Event | Normal execution request (with data input `IN`) |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Execution Confirmation (with data outputs `OUT` and `VALID`) |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|------|-----|--------------|-----------|

| IN | LWORD | `NOT_AVAILABLE_LWM` | Input value from the fieldbus |

*Note:* `NOT_AVAILABLE_LWM` is a constant defined in the project (e.g., `LWORD#16#FFFFFFFFFFFFFFFF`) that represents an invalid or unavailable value.

### **Data Outputs**

| Name | Type | Initial Value | Comment |

|-------|--------|----------------------------------|-----------|

| OUT | LWORD | `LWORD#16#0000000000000000` | Filtered output value (0 for invalid signal) |

| VALID | BOOL | `FALSE` | Validation flag (`TRUE` if signal is valid) |

### **Adapters**
No adapters available.

## Functionality
The function block is activated by an event at the input `REQ`. The current value of `IN` is read and processed according to the following logic:

1. The incoming LWORD value is converted into an unsigned integer (ULINT).

2. This value is compared to a constant `VALID_SIGNAL_LW`, also interpreted as a ULINT.

- If the input value is **less than or equal to** this threshold, the signal is considered valid:
- `OUT` receives the value of `IN`.
- `VALID` is set to `TRUE`.
- Otherwise (value greater than threshold), the signal is considered invalid:
- `OUT` is set to zero (`LWORD#16#0000000000000000`).
- `VALID` is set to `FALSE`.

3. After processing is complete, the event `CNF` is output to confirm completion.

The constant `VALID_SIGNAL_LW` defines the upper limit of the valid value range. Common values are, for example, `LWORD#16#0000FFFFFFFFFFFF` or similar ranges specified by the fieldbus protocol.

## Technical Features
- **Type Conversion:** The comparison is performed after converting both LWORD values to ULINT using `LWORD_TO_ULINT`. This interprets the values as unsigned 64-bit integers, enabling a consistent comparison independent of bit pattern-specific interpretations.
- **Use of project-wide constants:** The values `NOT_AVAILABLE_LWM` (initial value for `IN`) and `VALID_SIGNAL_LW` (limit value) are obtained via imports from a common signal processing package. They are not defined within the function block itself and can therefore be adjusted globally.
- **No additional state machine:** The function block has only a single state (`REQ`), which is exited immediately after the algorithm is executed. There are no internal delays or wait loops.

## State Overview

| State | Description | Action |

|---------|--------------|--------|

| REQ | Waits for an event at input `REQ`. | Executes the algorithm `REQ` (checking and, if necessary, filtering) and then sends the event `CNF`. |

After each execution, the function block returns to the state `REQ`, so it is immediately ready for a new task after each processing cycle.

## Application Scenarios
- **Fieldbus Signal Validation:** Used in automation systems where analog or digital signals are received via a fieldbus (e.g., PROFIBUS, CANopen). The function block filters out values that are outside the permissible range (e.g., error or initialization values) and outputs a defined zero value instead.
- **Safety-Related Applications:** If the fieldbus protocol specifies certain bit patterns for "signal not available" or "error," these can be detected by the limit check and marked as invalid.
- **Data preprocessing before logical operations:** The output `VALID` can be used directly as an enable signal for subsequent function blocks, so that they are only activated with valid input signals.

## Comparison with similar function blocks
- **Simple filters (e.g., `FIELDBUS_LWORD_FILTER`):** These usually perform a simple limit check without a validity flag. The function block described here additionally offers the Boolean output `VALID`, which simplifies decision-making in the controller.
- **Signal converters (e.g., `LWORD_TO_REAL`):** These convert the data type but do not check the validity of the original value. The function block `FIELDBUS_LWORD_TO_SIGNAL` combines validation and optional conversion (here as a 1:1 pass-through on validity).
- **Monitor blocks (e.g., `WATCHDOG`):** These only monitor the signal's validity, not its value range. This block adds range checking.

## Conclusion
The function block `FIELDBUS_LWORD_TO_SIGNAL` is a simple yet effective tool for processing fieldbus LWORD signals. The combination of range checking and outputting a validity flag ensures a clear separation of valid and invalid values. The use of project-wide constants provides flexibility, while the clear state logic guarantees reliable and fast processing. It is particularly suitable for applications where error signals or initialization values must be reliably detected and forwarded.
