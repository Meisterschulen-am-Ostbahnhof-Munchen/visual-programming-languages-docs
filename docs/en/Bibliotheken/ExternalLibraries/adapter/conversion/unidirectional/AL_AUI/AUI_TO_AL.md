# AUI_TO_AL

![AUI_TO_AL](./AUI_TO_AL.svg)

* * * * * * * * * *
## Introduction

The function block **AUI_TO_AL** is a composite function block that enables the conversion of an AUI adapter (based on the UINT data type) to an AL adapter (based on the LWORD data type). It encapsulates the standardized conversion function `F_UINT_TO_LWORD` and provides a simple, event-driven interface for unidirectional data transfer.
## Interface Structure

### **Event Inputs**

The block does not have explicit individual event inputs, as event control is handled by the connected adapters. The **E1** event of the **AUI_IN** socket is internally routed to the `REQ` input of the conversion block.

### **Event Outputs**

The function block outputs the event **E1** via the **AL_OUT** plug after the conversion is complete (signal from `CNF` of the internal function block).

### **Data Inputs**

The data input is provided exclusively via the socket:

* **AUI_IN.D1** (Type: UINT) – The value to be converted.

### **Data Outputs**

The data output is provided via the plug:

* **AL_OUT.D1** (Type: LWORD) – The converted value (LWORD).

### **Adapter**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `AUI` | **AUI_IN** | Input (Socket) | Input adapter for the UINT value and the trigger event. |
| `AL` | **AL_OUT** | Output (Plug) | Output adapter for the converted LWORD value and the acknowledgment event. |

## Functionality

The function block operates in an event-driven manner:

1. An incoming event at socket **AUI_IN.E1** (triggered by the connected transmitter) activates the internal block `F_UINT_TO_LWORD` via its event input `REQ`.
2. The value of **AUI_IN.D1** (UINT) is passed to the data input `IN` of the conversion block.

3. The conversion is performed according to the IEC 61131 standard: A UINT value is converted into an LWORD value (the upper 48 bits are padded with zeros).

4. After the conversion is complete, the result is passed to **AL_OUT.D1** (LWORD).
5. Simultaneously, the acknowledgment event from `CNF` is sent to **AL_OUT.E1** to signal the availability of the new value to the receiver.

## Technical Features

- **Composite Function Block (FB)**: The implementation hides the internal logic and facilitates reuse in larger adapter chains.
- **Standard Conversion**: Uses the IEC 61131-compliant function `F_UINT_TO_LWORD`, making it portable and platform-independent.
- **Unidirectional Transmission**: The adapters are designed for one-way data flow only (no return channel).
- **No State Logic**: The function block does not have its own state machine; sequence control is achieved purely through event chaining.

## State Overview

The **AUI_TO_AL** function block does not implement explicit states, as it is a purely event-driven mapping. The following deterministic sequence applies:

- **Wait**: The function block waits for an event at the input socket.
- **Convert**: After an event is received, the conversion is performed.
- **Output**: Upon completion, the result is output, and the function block returns to the wait state.

## Application Scenarios

- **Protocol Adaptation**: When a data provider supplies UINT values via an AUI adapter, but the consumer expects an AL adapter (LWORD).
- **System Integration**: In distributed automation systems with different data types at the communication layer.
- **Adapter Chaining**: As an intermediate link in an adapter cascade for stepwise type conversion.

## Comparison with Similar Function Blocks

In the 4diac environment, other conversion adapters exist, such as `AUI_TO_AB` (UINT to BYTE) or `AUI_TO_AW` (UINT to WORD). **AUI_TO_AL** differs in its target size of LWORD (64 bits), which is used for time-critical applications or for combining multiple data words into a single, contiguous value. It does not replace a universal type conversion but offers a dedicated, event-driven adaptation for the aforementioned adapter types.

## Conclusion

The **AUI_TO_AL** function block provides a clean, standardized solution for converting a UINT-based adapter (AUI) to an LWORD-based adapter (AL). It is easy to use, event-driven, and utilizes a proven IEC 61131 conversion function. Thanks to its composite nature, it integrates seamlessly into existing 4diac networks and facilitates the integration of different data widths in automation technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
