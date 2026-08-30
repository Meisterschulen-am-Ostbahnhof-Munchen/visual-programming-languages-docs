# FIELDBUS_UDINT_TO_SIGNAL

![FIELDBUS_UDINT_TO_SIGNAL](./FIELDBUS_UDINT_TO_SIGNAL.svg)

* * * * * * * * * *

## Introduction

The function block **FIELDBUS_UDINT_TO_SIGNAL** is used to check the validity of an incoming UDINT value and, if the check is successful, forward it unchanged to the output. If the value is invalid, the output is set to a defined error value (0) and the validity indicator is deactivated. This function block is typically used in fieldbus signal processing to ensure that only valid measurement or control values are passed on to subsequent logic.

## Interface Structure

### **Event Inputs**

| Event | Description |
|-------|--------------|
| REQ | Normal execution request; triggers the processing of the IN input. |

### **Event Outputs**

| Event | Description |
|-------|--------------|
| CNF | Confirms processing is complete. Triggered according to the algorithm. |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------|-------|------------------------------------------------|--------------|
| IN | UDINT | `DWORD_TO_UDINT(NOT_AVAILABLE_DWM)` | The input value to be checked. |

### **Data Outputs**

| Name | Type | Initial Value | Description |
| ------- | ------- | -------------- | -------------- |
| OUT | UDINT | `16#00000000` | The filtered output value. With a valid signal, it corresponds to IN; otherwise, it's 0. |
| VALID | BOOL | FALSE | TRUE if the signal is valid, i.e., IN is within the valid range. |

#### **Adapter**

None.

## Functionality

As soon as an event arrives at the **REQ** input, the algorithm is executed:

1. The value of **IN** is compared to the predefined threshold `VALID_SIGNAL_DW`.
2. If **IN** is less than or equal to this threshold, **OUT** is set to **IN** and **VALID** to `TRUE`.
3. Otherwise, **OUT** is set to `0` (UDINT) and **VALID** to `FALSE`.

The limit value `VALID_SIGNAL_DW` and the initial value `NOT_AVAILABLE_DWM` are imported as constants from the package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. They represent a maximum permissible signal value and an "unavailable" marker, respectively.

## Technical Features

- **Data Type** – The function block works exclusively with the type `UDINT` (Unsigned Double Integer, 32-bit).
- **Initial Value** – The input IN is set to the value `NOT_AVAILABLE_DWM` by default. This is converted from a previously defined DWORD using the function `DWORD_TO_UDINT`.
- **Limit Value** – The validity is determined by a simple comparison with the imported constant `VALID_SIGNAL_DW`. All values ≤ this limit are considered valid.
- **Simple State Logic** – The function block consists of exactly one state (REQ) and executes the algorithm on every request.

## State Overview

The function block is implemented as a simple FB (SimpleFB) and has only one state:

| State | Action | Output Event |
|---------|-------------|------------------|
| REQ | Algorithm REQ | CNF |

There is no state machine with multiple steps or branches.

## Application Scenarios

- **Fieldbus Signal Conditioning** – In automation systems where UDINT values are received via a fieldbus, the function block is used to filter invalid values or values outside the valid range (e.g., sensor data that must not exceed a maximum value).
- **Agricultural Technology** – Originally developed for use in agricultural control systems (e.g., HR Agrartechnik) to validate analog measurements such as rotational speeds or pressures.
- **Quality Assurance** – Preprocessing of measurement data before it is incorporated into control loops or logging.

## Comparison with Similar Function Blocks

- **FIELDBUS_DINT_TO_SIGNAL** – Analog function block for signed 32-bit values (DINT).
- **FIELDBUS_BOOL_TO_SIGNAL** – Comparable function block for Boolean signals; threshold validation is omitted.
- **FIELDBUS_REAL_TO_SIGNAL** – For floating-point numbers, possibly with different tolerance logic.

This function block is specifically designed for the UDINT data type and uses a simple absolute limit for validation.

## Conclusion

**FIELDBUS_UDINT_TO_SIGNAL** is a compact and efficient function block for filtering UDINT fieldbus signals. Its clear separation of valid and invalid values, along with its simple interface, makes it well-suited for robust automation solutions. The use of imported constants increases reusability and adaptability to various fieldbus protocols.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
