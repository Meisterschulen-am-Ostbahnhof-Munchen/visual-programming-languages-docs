# FIELDBUS_UINT_TO_SIGNAL
![FIELDBUS_UINT_TO_SIGNAL](./FIELDBUS_UINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Introduction
The FIELDBUS_UINT_TO_SIGNAL function block is used to process fieldbus signals. It mirrors an incoming UINT value to the output, provided it is classified as valid. Validity is determined by comparing it to a configured threshold (VALID_SIGNAL_W). If the input value exceeds this threshold, the output is reset and the signal is marked as invalid.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Normal Execution Trigger (connected to IN) |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Execution confirmation (connected to OUT and VALID) |

### **Data Inputs**

| Name | Data Type | Initial Value | Comment |
|------|----------|-------------|-----------|
| IN | UINT | WORD_TO_UINT(NOT_AVAILABLE_WM) | Input value (raw fieldbus signal) |

### **Data Outputs**

| Name | Data Type | Initial Value | Comment |
|------|----------|-------------|-----------|
| OUT | UINT | 16#0000 | Filtered Output Value |
| VALID | BOOL | FALSE | TRUE if the signal is recognized as valid |

### **Adapter**
None.

## Functionality
On each REQ event, the REQ algorithm is executed:

1. The incoming value IN is compared to the constant `VALID_SIGNAL_W`.

2. If `IN <= WORD_TO_UINT(VALID_SIGNAL_W)` is valid, the signal is considered valid:

- `OUT` receives the value of `IN`.
- `VALID` is set to TRUE.

3. Otherwise (signal invalid):

- `OUT` is reset to 0.
- `VALID` is set to FALSE.

4. The CNF event is then triggered.

The constants `NOT_AVAILABLE_WM` (for the initial value of IN) and `VALID_SIGNAL_W` (as the threshold) are obtained from external imports and define the valid range of the fieldbus signal.

## Technical Features
- Use of type conversions (`WORD_TO_UINT`) for comparison with the imported constants.
- The function block imports two constants from the package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`: `NOT_AVAILABLE_WM` and `VALID_SIGNAL_W`. These must be defined or provided accordingly in the application.
- The function block is implemented as a simple FB, i.e., It has exactly one execution state.

## State Overview
The function block consists of a single state, **REQ**.

- **START** → **REQ**: The algorithm is executed as soon as the REQ event occurs. After processing, CNF is output, and the state remains in REQ (cyclic processing).

## Application Scenarios
- Processing of analog sensor values from a fieldbus where a specific value range is defined as valid (e.g., 0–1000 for a pressure sensor).
- Filtering of communication errors or invalid telegrams by setting values outside the valid range to zero and marking them as invalid.
- Preprocessing of fieldbus signals before forwarding them to subsequent logic blocks.

## Comparison with Similar Function Blocks

Unlike simple pass-through blocks (e.g., `MOVE`), `FIELDBUS_UINT_TO_SIGNAL` performs a deliberate validity check and distinguishes between valid and invalid values. Other blocks, such as `LIMIT` or `SCALE`, offer range limits but no separate Boolean output for validity. This block is particularly suitable for applications requiring explicit signal status indication.

## Conclusion
The FIELDBUS_UINT_TO_SIGNAL function block provides a simple and efficient way to check the validity of fieldbus signals and either pass them through or discard them. Its clear interface and the use of configurable constants make it versatile for use in IEC 61499 automation applications.

# Conclusion ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
