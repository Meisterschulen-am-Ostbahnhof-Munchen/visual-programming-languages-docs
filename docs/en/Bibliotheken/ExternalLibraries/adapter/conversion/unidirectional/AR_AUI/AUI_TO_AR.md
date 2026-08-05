# AUI_TO_AR
![AUI_TO_AR](./AUI_TO_AR.svg)

* * * * * * * * * *
## Introduction
The **AUI_TO_AR** function block is a composite component that converts an AUI adapter (UINT) into an AR adapter (REAL). It enables the seamless integration of an unsigned integer signal into systems that expect a REAL value by passing the event and data value through one-to-one.
## Interface Structure

### **Event Inputs**

The component does not have a direct event input, as events are provided exclusively via the **AUI_IN** input adapter:

- **E1** (from the AUI_IN adapter): Event that triggers data transmission.

### **Event Outputs**

Event outputs are also implemented via the **AR_OUT** output adapter:

- **E1** (from the AR_OUT adapter): Event output after successful conversion.

### **Data Inputs**

Data inputs are only available indirectly via the **AUI_IN** adapter:

- **D1** (from the AUI_IN adapter): Value to be converted as **UINT**.

### **Data Outputs**

Data outputs are provided via the **AR_OUT** adapter:

- **D1** (from the AR_OUT adapter): Converted value as **REAL**.

### **Adapters**

| Name | Type | Direction | Description |

|-------------|-----|-----------|--------------|

| **AUI_IN** | `adapter::types::unidirectional::AUI` | Input (Socket) | Provides a UINT signal and an associated event. |

| **AR_OUT** | `adapter::types::unidirectional::AR` | Output (Plug) | Outputs the converted REAL signal and an event. |

## Functionality

The **AUI_TO_AR** function block acts as a simple pass-through component. It connects 1:1:

- **AUI_IN.E1** → **AR_OUT.E1**
- **AUI_IN.D1** → **AR_OUT.D1**

This means: As soon as an event arrives at the AUI_IN input, the corresponding **UINT** data is passed to the **AR_OUT** output without any additional processing or type conversion. The actual conversion from **UINT** to **REAL** must be performed either by the sending adapter or by a downstream function block – the **AUI_TO_AR** itself does not perform any arithmetic conversion. It merely ensures that the event and data paths between the two different adapter types are compatible.

## Technical Features
- **Composite Function Block:** The implementation is purely via the network of adapter connections, without any internal logic or state machines.
- **No Type Conversion:** The **AUI_TO_AR** does not perform any explicit data type conversion. It assumes that the **AUI_IN** adapter already provides REAL-compliant data or that the type conversion is performed externally.
- **Unidirectional Adapter Type:** Both adapters are unidirectional, meaning they only transmit data and events in one direction (from AUI_IN to AR_OUT).

## State Overview

Since the function block is implemented as a pure interconnection network without its own state machine, no state machine exists. Its functionality is limited to the immediate forwarding of incoming events and data.

## Application Scenarios
- **System Integration:** Integrating sensors or controllers that provide their measured values as UINT via an AUI adapter into a system that expects REAL values via AR adapters.
- **Protocol Adaptation:** If two subsystems use different adapter types for the same physical quantity, **AUI_TO_AR** can serve as an adapter translator (provided the UINT value already numerically represents the desired REAL value).
- **Library Extension:** As a reusable function block in a library project to streamline adapter conversions.

## Comparison with Similar Function Blocks

| Function Block | Function | Difference |

|----------|----------|-------------|

| **AUI_TO_AR** | Adapter switching UINT → REAL | Pass-through only; no type conversion, expects compatible data. |

| **AR_TO_AUI** | Adapter switching REAL → UINT | Reverse direction, also pass-through only. |

| **CONV_UINT_TO_REAL** | Type conversion from UINT to REAL | Performs actual conversion, but requires direct data inputs/outputs instead of an adapter. |

## Conclusion

The **AUI_TO_AR** is a simple yet useful composite component that connects the **AUI** and **AR** adapter types without modifying the data. It is particularly suitable for systems where type compatibility is already provided at the adapter level or where subsequent conversion takes place. Its streamlined structure makes it a reliable tool for integrating different adapter protocols.
