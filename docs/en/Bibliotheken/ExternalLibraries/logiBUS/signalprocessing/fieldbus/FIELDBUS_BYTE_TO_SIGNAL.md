# FIELDBUS_BYTE_TO_SIGNAL
![FIELDBUS_BYTE_TO_SIGNAL](./FIELDBUS_BYTE_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction
The function block **FIELDBUS_BYTE_TO_SIGNAL** is used for the simple validation of a BYTE signal from a fieldbus. It only passes the input value unchanged to the output if it lies within a defined valid range. The result of the validation is signaled via a separate Boolean output.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Normal execution trigger; processes the current value at the IN input. |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Confirmation of execution; the outputs OUT and VALID have been updated. |

### **Data Inputs**

| Name | Data Type | Initial Value | Comment |
|------|----------|-------------|-----------|
| IN | BYTE | NOT_AVAILABLE_B | Input signal as a byte value. |

### **Data Outputs**

| Name | Data Type | Initial Value | Comment |
|------|----------|-------------|-----------|
| OUT | BYTE | 16#00 | Filtered output value; 0 if signal is invalid. |
VALID | BOOL | FALSE | TRUE if the input signal is recognized as valid. |

### **Adapter**
None.

## Functionality
The block checks the current BYTE input value **IN** against a predefined constant **VALID_SIGNAL_B** (from the import `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`) on each REQ event.

The logic in the algorithm is:

```structuredtext
IF (BYTE_TO_USINT(IN) <= BYTE_TO_USINT(VALID_SIGNAL_B)) THEN
OUT := IN;
VALID := TRUE;
ELSE
OUT := BYTE#0;
VALID := FALSE;
END_IF;

- If the value of **IN** (interpreted as an unsigned integer) is **less than or equal to** the threshold **VALID_SIGNAL_B**, the input is passed directly to **OUT** and **VALID** is set to `TRUE`.
- If **IN** exceeds the threshold, **OUT** is reset to `0` and **VALID** is set to `FALSE`.

After the calculation, the **CNF** event is output. The initial value of **IN**, `NOT_AVAILABLE_B`, is already outside the valid range, so the block is set to "invalid" by default after the first iteration.

- If **IN** exceeds the threshold, **OUT** is reset to `0` and **VALID** is set to `FALSE`.

After the calculation, the **CNF** event is output. The initial value of **IN** is already outside the valid range, so the block is set to "invalid" by default after the first iteration.


## Technical Features

- The filter is based on **two external constants** from the `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` library:
- `NOT_AVAILABLE_B` – defines the value for "Signal not available" (initial value of IN).
- `VALID_SIGNAL_B` – defines the upper limit for valid signals.
- The conversion `BYTE_TO_USINT` ensures that the values can be compared as numbers 0…255.
- The block is implemented as a **SimpleFB** with only one state (**REQ**) – not a state machine with multiple steps.
- License: Eclipse Public License 2.0.

## State Overview
The function block has exactly one execution state:

| State | Action | Output Event |
|---------|--------|-----------------|
| REQ | Executes the **REQ** algorithm (filter logic) | CNF |

There are no further wait or initialization states.

## Application Scenarios
- **Fieldbus Signal Validation**: A sensor delivers a BYTE value that is only physically meaningful within a specific range (e.g., 0…100). This block prevents erroneous or implausible values from entering the control logic.
- **Safety-Related Systems**: Can be used as a simple range checker for analog or digital fieldbus signals in automation technology (e.g., agriculture, machine control).
- **Signal Switch**: Separation of valid and invalid data streams – e.g., for controlling an AND filter or for error detection.

## Comparison with Similar Blocks
- Unlike simple **threshold switches** (e.g., `HYSTERESIS` or `LIMIT_ALARM`), this block operates purely at the BYTE level and outputs the original value directly as long as it is within the valid range – no hysteresis or alarm function.
- Compared to a **multiplexer** (`MUX`), it does not require a second control signal but makes the decision automatically based on the input value.
- Similar blocks in IEC 61499 often exist as `RANGE_CHECK` or `VALIDATE`, but are usually designed for generic data types. This block is specifically tailored to the BYTE format commonly used in fieldbuses.
-
## Conclusion

**FIELDBUS_BYTE_TO_SIGNAL** is a compact, specialized filter block for validating BYTE signals. It requires no boundary configuration, as these are defined via the imported constants in the library. Due to the clear separation of the data output and the validity signal, it is ideally suited for processing fieldbus data in safety-critical or fault-tolerant automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
