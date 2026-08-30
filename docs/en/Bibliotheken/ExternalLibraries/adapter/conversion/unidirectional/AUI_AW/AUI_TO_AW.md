# AUI_TO_AW

![AUI_TO_AW](./AUI_TO_AW.svg)

* * * * * * * * * *
## Introduction

The function block `AUI_TO_AW` is a composite module that converts an AUI adapter (data type UINT) into an AW adapter (data type WORD). It encapsulates the type conversion and provides it as a standardized adapter interface, enabling seamless integration of system components with different data types.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| `AUI_IN.E1` | Event (via adapter) | Trigger to convert the incoming UINT value |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `AW_OUT.E1` | Event (via adapter) | Confirmation that the converted WORD value has been provided |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `AUI_IN.D1` | UINT (via adapter) | The input value to be converted |

### **Data Outputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `AW_OUT.D1` | WORD (via adapter) | Converted Output Value |

### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Socket (Input) | `AUI_IN` | `adapter::types::unidirectional::AUI` | UINT adapter as source |
| Plug (Output) | `AW_OUT` | `adapter::types::unidirectional::AW` | WORD adapter as sink |

## Functionality

This function block responds to an event on socket `AUI_IN.E1`. The current value of `AUI_IN.D1` (data type UINT) is then forwarded to the internal conversion block `F_UINT_TO_WORD`. This block converts the value to the WORD data type according to IEC 61131. Once the conversion is complete, the result is passed to the plug `AW_OUT.D1`, and an acknowledgment event is triggered on `AW_OUT.E1`.

The interaction of event and data flow ensures secure and deterministic data transmission.

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Composite Structure:** The block encapsulates the complete conversion logic in a single function block, eliminating the need for any further conversion steps in the application.
- **Type Conversion:** Conversion is performed using the standardized IEC 61131 function block `F_UINT_TO_WORD`. UINT and WORD are bit-compatible, so no data loss occurs.
- **Adapter Interface:** The use of adapters enables loose coupling of the components. The function block can be directly integrated into adapter-based networks.
- **No States:** The function block has no state behavior (ECC). It operates purely event-driven and performs an immediate conversion upon each trigger.

## State Overview

The function block does not contain its own state machine (ECC). Sequence control is handled solely through the event connections in the composite network. After startup, the function block is immediately ready to process incoming events and perform the conversion.

## Application Scenarios

- **Adapter Bridge:** If one system component communicates only via an AUI adapter (UINT), but another component expects an AW adapter (WORD), `AUI_TO_AW` can be used as an intermediary.
- **Data Type Adaptation:** In Industry 4.0 or IIoT environments where devices use different data types, this component harmonizes the interfaces.
- **Modular Chaining:** The component can be easily inserted into a chain of adapters to ensure compatibility between components.

## Comparison with Similar Components

- **Direct Use of `F_UINT_TO_WORD`:** Instead of the composite component, `F_UINT_TO_WORD` could be used directly, and the adapters connected separately. The composite block simplifies cabling and increases reusability.
- **Analog converters (e.g., `AWORD_TO_AUINT`):** Corresponding modules exist for the reverse direction. `AUI_TO_AW` focuses specifically on the conversion from UINT to WORD and offers a clearly named, targeted solution.

## Conclusion

The `AUI_TO_AW` function block provides a compact and robust solution for converting a UINT adapter signal to a WORD adapter signal. By encapsulating the standard conversion and using the adapter interface, integration into existing systems is facilitated, and network readability is improved. The module is ideally suited to reconcile data type differences between components without compromising application clarity.
