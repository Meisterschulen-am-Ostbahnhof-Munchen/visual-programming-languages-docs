# FIELDBUS_UINT_TO_SIGNAL_SCALED

![FIELDBUS_UINT_TO_SIGNAL_SCALED](./FIELDBUS_UINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Introduction

The function block **FIELDBUS_UINT_TO_SIGNAL_SCALED** processes a UINT value received via a fieldbus. It checks the validity of the input signal and, if valid, scales it to a REAL output using a multiplication constant (SCALE) and an additive offset (OFFSET). If the signal is invalid, the output is set to zero and a validity flag is set to FALSE. A typical application is the conversion of raw fieldbus data into physical quantities while simultaneously detecting exceptional conditions such as wire breaks or sensor errors.
## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization request. This event sets the parameters `SCALE` and `OFFSET`.
- **REQ** (Event): Normal execution request. This event processes the current value `IN`.

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation. Sent after processing the INIT event.
- **CNF** (Event): Execution confirmation. Sent after processing the REQ event and carries the output data `OUT` and `VALID`.

### **Data Inputs**

| Name | Type | Initial Value | Description |
|--------|-------|----------------------------------|-----------------------------------------------------------|
| IN | UINT | WORD_TO_UINT(NOT_AVAILABLE_WM) | Raw value from the fieldbus to be scaled. |
| SCALE | REAL | REAL#1.0 | Scaling factor (multiplication). |
| OFFSET | DINT | DINT#0 | Additive offset to be added after scaling. |

### **Data Outputs**

| Name | Type | Initial Value | Description |
|--------|-------|--------------|-----------------------------------------------------------|
| OUT | REAL | REAL#0.0 | Scaled output value. 0.0 if the signal is invalid. |
| VALID | BOOL | FALSE | Validation flag: TRUE if the input signal is valid. |

### **Adapter**

None.

## Functionality

The FB has two operating states, which are controlled by the corresponding events.

- **INIT state**: Upon receiving `INIT`, the parameters `SCALE` and `OFFSET` are adopted (the algorithm is empty; the transfer occurs implicitly via the `With` link). The event `INITO` is then sent.

- **REQ State**: Upon receiving `REQ`, the following algorithm is executed:

1. Check whether the input value `IN` is less than or equal to a predefined validity threshold. This threshold is given by the imported constant `VALID_SIGNAL_W` (from the namespace `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`).
2. **Valid (`IN <= VALID_SIGNAL_W`)**:
- `OUT := UINT_TO_REAL(IN) * SCALE + DINT_TO_REAL(OFFSET)`
- `VALID := TRUE`
3. **Invalid (`IN > VALID_SIGNAL_W`)**:
- `OUT := 0.0`
- `VALID := FALSE`
4. Subsequently, the event `CNF` is sent with the current values of `OUT` and `VALID`.

The validity threshold is provided as part of the imported library and must be defined according to the fieldbus standard used. The initial value of `IN` is `WORD_TO_UINT(NOT_AVAILABLE_WM)`, which, by default, results in an invalid signal being detected if no data is passed.

## Technical Features

- **Use of Imported Constants**: Validation is performed using constants from the `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` namespace. These must be correctly defined in the target system (e.g., `VALID_SIGNAL_W` as the maximum valid UINT value, `NOT_AVAILABLE_WM` as an indicator for "not available").
- **Empty INIT Algorithm**: The INIT event is used solely for parameter passing. No explicit initialization logic exists – the values of `SCALE` and `OFFSET` are taken directly from the data inputs. Therefore, these parameters can also be set before the first INIT (see Initial Values).
- **Type Preservation**: The input is UINT, the output is REAL. Scaling is performed using REAL arithmetic after an explicit type conversion.
- **No State Machine Logic**: The FB is implemented as a SimpleFB, which only has the two states INIT and REQ. There are no time-based or repetitive processes; each execution is strictly event-driven.

## State Overview

The FB has exactly two EC states:

| State | Input | Algorithm | Output Event |
|---------|---------|-------------|------------------|
| INIT | INIT | – (empty) | INITO |
| REQ | REQ | REQ | CNF |

There is no state loop or dwell time. After initialization, the function block (FB) starts in the INIT state and can then be executed any number of times via REQ. A subsequent INIT resets the parameters.

## Application Scenarios

- **Scaling of Analog Values**: A fieldbus delivers a raw 16-bit measurement value (e.g., 0–4095). Using `SCALE = 0.001` and `OFFSET = -5.0`This results in, for example, a pressure in bar.
- **Error Value Detection**: Many fieldbus protocols define specific bit patterns for "sensor errors" or "wire breaks." The function block (FB) detects such values by classifying them as being above the validity threshold (e.g., 0xFFFE or 0x8000) and setting the output to zero.
- **Initialization Sequence**: After system startup, an INIT call can load the scaling parameters from a configuration file. Subsequently, REQ calls are sent in rapid succession for cyclical measurement processing.

## Comparison with Similar Function Blocks

- **FIELDBUS_UINT_TO_SIGNAL (without scaling)**: A simpler FB that directly outputs the UINT value as a REAL and only performs the validity check. Scaling must be done externally.
- **FIELDBUS_UINT_TO_SIGNAL_FILTERED**: In addition to scaling, a low-pass or median filter is applied – suitable for noisy signals.
- **FIELDBUS_INT_TO_SIGNAL_SCALED**: Analog function block for signed inputs (INT), with corresponding adjustment of the validation logic.

This function block is characterized by its simplicity, clear separation of scaling and validation detection, and the use of imported constants, which allows for flexible adaptation to various fieldbus standards.

## Conclusion

**FIELDBUS_UINT_TO_SIGNAL_SCALED** is a compact, event-driven function block for converting a UINT fieldbus signal into a scaled REAL value. The integrated validation check enables easy error detection. This block is particularly suitable for applications where raw bus data needs to be converted into physical quantities with minimal effort, while simultaneously monitoring signal quality. The clear interface and the use of imported constants facilitate reuse in different project contexts.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
