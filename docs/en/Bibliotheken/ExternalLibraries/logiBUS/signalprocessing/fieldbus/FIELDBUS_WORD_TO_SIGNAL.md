# FIELDBUS_WORD_TO_SIGNAL
![FIELDBUS_WORD_TO_SIGNAL](./FIELDBUS_WORD_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction
The FIELDBUS_WORD_TO_SIGNAL function block is used for simple signal filtering in fieldbus applications. It reflects an incoming WORD value at the output, provided the signal is classified as valid. A Boolean output indicates the validity status. Implementation is based on a comparison with an externally defined limit constant.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Normal execution command; triggered by the IN input. |

#### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of execution; output after processing is complete. |

### **Data Inputs**

| Name | Type | Initial Value | Comment |
|------|-----|-------------|-----------|
| IN | WORD | NOT_AVAILABLE_WM | Input value that is checked for validity. |

### **Data Outputs**

| Name | Type | Initial Value | Comment |
|------|-----|-------------|-----------|
| OUT | WORD | 16#0000 | Filtered output value (only if the signal is valid). |
| VALID | BOOL | FALSE | TRUE if the input signal is recognized as valid. |

### **Adapter**
No adapters available.

## Functionality
The module operates using a simple algorithm:

1. Upon arrival of the **REQ** event, the incoming value **IN** is read.

2. The value is converted to an unsigned integer using `WORD_TO_UINT`.

3. This is compared to the external constant `VALID_SIGNAL_W`.

– If the converted value is **less than or equal to** `VALID_SIGNAL_W`, **IN** is directly passed to **OUT** and **VALID** is set to `TRUE`.

`` Otherwise, **OUT** is reset to `16#0000` and **VALID** to `FALSE`.

4. The **CNF** event is then triggered.

The initial value of input `IN` is `NOT_AVAILABLE_WM`, so the function block signals an invalid signal in its default state.

## Technical Features
- **External Constants:** The comparison limit `VALID_SIGNAL_W` and the default unavailable value `NOT_AVAILABLE_WM` are imported from the package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. Their values are defined outside the function block.
- **Data Type Conversion:** The comparison is performed after converting `WORD` to `UINT` (`WORD_TO_UINT`) to enable an unsigned numerical comparison.
- **Initial Values:** The output `OUT` starts with `16#0000`, and `VALID` with `FALSE`. The input `IN` starts with the invalid value `NOT_AVAILABLE_WM`.
- **Simple State Machine:** There is only one execution state (REQ) – the function block is event-driven and does not remain in any other states.

**Initial State Machine:**
## State Overview
The function block has exactly one state:

| State | Description |
|---------|--------------|
| **REQ** | Executes the algorithm, sets the outputs accordingly, and sends the confirmation event **CNF**. |

There are no loops or branches in the state machine; each call to REQ is executed only once.

## Application Scenarios
- **Fieldbus Signal Filtering:** Checks whether a WORD value originating from a fieldbus is within a valid range (e.g., sensor values, control commands).
- **Plausibility Check:** Suppresses values marked as "unavailable" or "erroneous" (represented by `NOT_AVAILABLE_WM`).
- **Data Consistency:** Used as a simple gate in industrial controllers, passing only valid data to subsequent logic.

## Comparison with Similar Function Blocks
Similar function blocks such as **FIELDBUS_SIGNAL_FILTER** or **VALUE_CHECK** also perform comparisons using threshold values. The advantage of `FIELDBUS_WORD_TO_SIGNAL` lies in the direct integration of the validity identifier (`VALID`) and the use of predefined constants from the fieldbus library, which enables standardized handling of "unavailable" states. Unlike generic multiplex blocks, the logic here is optimized for specific use in the fieldbus context.

## Conclusion
The function block `FIELDBUS_WORD_TO_SIGNAL` offers a compact and reliable way to check fieldbus signals for validity and forward only values recognized as valid. Using imported constants ensures a consistent definition of validity limits and unavailable values across the entire project. This component is particularly suitable for safety-critical applications where invalid data must be detected and suppressed.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
