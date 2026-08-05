# FIELDBUS_DWORD_TO_SIGNAL
![FIELDBUS_DWORD_TO_SIGNAL](./FIELDBUS_DWORD_TO_SIGNAL.svg)
* * * * * * * * * *
## Introduction
The function block `FIELDBUS_DWORD_TO_SIGNAL` mirrors and validates a DWORD input signal. If the input value is valid, it is passed unchanged to the output, and the `VALID` signal is set. Otherwise, the block returns a zero value, indicating invalidity.
## Interface Structure

### **Event Inputs**

| Event | Comment |

|----------|-----------|

| REQ | Normal execution trigger; processes the current value of `IN`. |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| CNF | Execution confirmation; sent after calculation. |

### **Data Inputs**

| Variable | Type | Initial Value | Comment |

|----------|--------|---------------------|------------------|

| IN | DWORD | `NOT_AVAILABLE_DWM` | Input signal |

### **Data Outputs**

| Variable | Type | Initial Value | Comment |

|----------|--------|---------------|------------------------------------|

| OUT | DWORD | `16#00000000` | Filtered output value |

| VALID | BOOL | `FALSE` | `TRUE`, if the signal is valid |

### **Adapter**
None.

## Functionality

The function block is activated by an event at `REQ`. The associated algorithm compares the input value `IN` (as an unsigned integer) with a predefined threshold `VALID_SIGNAL_DW`:

- If `DWORD_TO_UDINT(IN) <= DWORD_TO_UDINT(VALID_SIGNAL_DW)`, the signal is considered **valid**:
- `OUT` receives the value of `IN`.
- `VALID` is set to `TRUE`.

`` - Otherwise (signal invalid):

- `OUT` is set to `DWORD#0`.
- `VALID` is set to `FALSE`.

After the calculation is complete, the output event `CNF` is sent.

## Technical Features
- The limit value `VALID_SIGNAL_DW` comes from the imported package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. It defines the maximum permissible value for a valid signal.
- The initial value of the input `IN` is `NOT_AVAILABLE_DWM` (also imported), so the function block already assumes an invalid state at startup.
- Converting DWORD to UDINT enables simple numerical comparison (≤) without sign issues.
- The function block is implemented as a **SimpleFB** with a single ECA state, `REQ`.

## State Overview

| State | Action | Output Event |

|---------|----------------------|------------------|

| REQ | Execute `REQ` Algorithm | CNF |

There is only one state; after its processing, the function block returns to the IDLE state (implicitly).

## Application Scenarios
- **Fieldbus Signal Processing**: A DWORD value from a fieldbus (e.g., CANopen, Profibus) is validated before being used in the controller.
- **Data Validation**: This function block can be used as a filter to detect invalid or erroneous telegrams and replace them with a defined zero value.
- **Safety-Critical Systems**: The clear separation of valid and invalid signals allows for monitoring and further processing of signal quality.

## Comparison with Similar Function Blocks
- A simple **MOVE** function block would pass the value through without validation; `FIELDBUS_DWORD_TO_SIGNAL` adds the validation logic.
- Function blocks like `FIELDBUS_SIGNAL_TO_DWORD` (if available) perform the opposite conversion – here, a DWORD signal is converted into a validated signal with a validity flag.
- This function block is specialized for DWORD values; corresponding variants for other data types (e.g., WORD, SINT) would be conceivable.

## Conclusion

FIELDBUS_DWORD_TO_SIGNAL` is a compact yet essential function block for robust fieldbus connectivity. It combines signal transmission with simple validity checking and provides the validity as a separate Boolean signal. This allows downstream functions to quickly react to valid data or initiate error handling. The use of imported constants ensures a consistent definition of the validity threshold across multiple functions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
