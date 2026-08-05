# FIELDBUS_USINT_TO_SIGNAL
![FIELDBUS_USINT_TO_SIGNAL](./FIELDBUS_USINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction
The FIELDBUS_USINT_TO_SIGNAL function block processes a USINT signal from a fieldbus. It checks whether the incoming value represents a valid signal range and, if so, mirrors it to the output. Otherwise, the output is set to a defined zero value, and the validity signal is reset.
## Interface Structure

### **Event Inputs**

| Event | Description | With |

|----------|--------------|-----|

| REQ | Normal Execution Order | IN |

### **Event Outputs**

| Event | Description | With |

|----------|--------------|-----|

| CNF | Execution Confirmation | OUT, VALID |

### **Data Inputs**

| Name | Type | Comment | Initial Value |

|------|-------|-----------|------------|

| IN | USINT | Input Value from Fieldbus | BYTE_TO_USINT(NOT_AVAILABLE_B) |

### **Data Outputs**

| Name | Type | Comment | Initial Value |

|-------|-------|-----------|-------------|

| OUT | USINT | Filtered Output Value | 16#00 |

| VALID | BOOL | TRUE if signal is valid | FALSE |

### **Adapter**

None.

## Functionality

When a REQ event arrives, the algorithm is executed. The incoming value IN is compared to the constant threshold `VALID_SIGNAL_B` (interpreted as USINT). If `IN <= BYTE_TO_USINT(VALID_SIGNAL_B)` is true, the input value is directly transferred to the output OUT, and the validity signal VALID is set to TRUE. Otherwise, OUT is set to 0 and VALID to FALSE. The result is acknowledged with the CNF event.

The two constants `NOT_AVAILABLE_B` and `VALID_SIGNAL_B` are part of the package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` and define a reference value for "not available" and the upper limit for valid signals, respectively.

## Technical Features
- The initial value of the IN input is set to `BYTE_TO_USINT(NOT_AVAILABLE_B)`, so that on the first call without a valid value, an invalid state is immediately signaled.
- The comparison uses the function `BYTE_TO_USINT` to convert the constant's byte value to the USINT data type.
- The function block is licensed under the Eclipse Public License 2.0.

## State Overview

The function block has a single state, `REQ`. As soon as a REQ event arrives, the algorithm is executed and the CNF event is immediately sent. There are no internal state changes or delays.

## Application Scenarios
- **Fieldbus Signal Conditioning**: A sensor provides values in the range 0–127 as valid signals. The VALID_SIGNAL_B threshold is set to 127. Values above this threshold (e.g., 255 as an error code) are recognized as invalid.
- **Initialization**: At system startup, the input is preset to the "not available" value, so that until the first valid signal is received, the output remains at 0 and VALID is set to FALSE.
- **Error Detection**: Any permissible value range can be defined by adjusting the threshold.

## Comparison with Similar Function Blocks

Similar function blocks such as `FIELDBUS_BYTE_TO_SIGNAL` or `FIELDBUS_SINT_TO_SIGNAL` operate on the same principle, but with different data types. This function block specializes in USINT. A simple "mirror" function block without validation would pass the value through unfiltered.

## Conclusion

The `FIELDBUS_USINT_TO_SIGNAL` function block offers a simple and reliable way to check the validity of USINT fieldbus signals and only pass valid values on to subsequent processing. Its use of configurable limits (via package constants) makes it highly versatile.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
