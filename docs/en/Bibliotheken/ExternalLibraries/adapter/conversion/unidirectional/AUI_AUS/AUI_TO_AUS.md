# AUI_TO_AUS

![AUI_TO_AUS](./AUI_TO_AUS.svg)

* * * * * * * * * *
The function block **AUI_TO_AUS** serves as a composite module for converting an AUI adapter (data type UINT) into an AUS adapter (data type USINT). It is typically used to mediate between different adapter types in the 4diac IDE when a reduction in the value range or a type conversion is required. The module encapsulates the conversion logic and enables seamless integration into existing runtime environments.

No separate event inputs. Event control is handled via the connected adapters.

No separate event outputs. Event propagation is handled via the connected adapters.

No separate data inputs. Data input is via the connected adapters.

No separate data outputs. Data output is via the connected adapters.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Direction | Name | Type | Description |
|----------|-------------------------------------|----------------------------------|-------------------------------------------|
| Socket | **AUI_IN** | adapter::types::unidirectional::AUI | UINT input adapter (source) |
| Plug | **AUS_OUT** | adapter::types::unidirectional::AUS | USINT output adapter (destination) |

The socket `AUI_IN` accepts the UINT value (16-bit unsigned) and the corresponding event signal. The plug `AUS_OUT` outputs the converted USINT value (8 unsigned bits) along with the corresponding event.

## Functionality

The function block operates as a simple pass-through element with type conversion:

1. **Event Reception**: An incoming event at socket `AUI_IN.E1` triggers processing.
2. **Data Acquisition**: The corresponding data value `AUI_IN.D1` (type UINT) is read.
3. **Conversion**: Internally, the function `F_UINT_TO_USINT` from the IEC 61131 library is called. This function converts the UINT value into a USINT value. If the USINT value range (0…255) is exceeded, the value is truncated or handled according to the underlying implementation (usually capped at 255).
4. **Output**: The converted value is made available on `AUS_OUT.D1` (type USINT), and the output event `AUS_OUT.E1` is sent.

All coupling occurs via the event and data connections in the FB network of the composite block.

- **Range Limitation**: Converting UINT (0…65535) to USINT (0…255) inevitably results in information loss if the input value is greater than 255. Users must ensure that the input value range meets expectations.
- **No State Storage**: The FB is stateless – all processing occurs independently of previous conversions.
- **Reusability**: The function block is designed as an encapsulated component and can be used in different projects without having to reimplement the conversion logic.
- **Compatibility**: The availability of the library `iec61131::conversion::F_UINT_TO_USINT` is required.

The function block does not have an explicit state machine. However, the internal process can be described as two-step:

- **Ready (Idle)**: The function block waits for an incoming event at the socket.
- **Processing (Convert)**: After the event is received, the conversion is performed and the output event is triggered. The function block then immediately returns to the ready state.

A detailed state graph is not required, as the function block does not have any delays or multi-stage steps.

- **Sensor Connection**: A sensor delivers values in UINT format that must be passed to subsequent logic with a USINT request.
- **Device Coupling**: Seamless communication is established between two devices or components that use different adapter types.
- **Data Reduction**: In cases where the higher resolution of a UINT is not required, conversion to USINT can offer storage and bandwidth advantages.
- **System Migration**: When switching from older to newer adapter protocols, this function block can serve as a temporary or permanent bridge.

Other conversion function blocks exist in the 4diac library, e.g., `F_UINT_TO_USINT`, which directly maps a UINT input to a USINT output. The **AUI_TO_AUS** described here differs in that it uses adapters (AUI and AUS) instead of basic data inputs. This allows it to encapsulate the entire interface, including event control, simplifying its use in complex, adapter-based architectures. A pure function block like `F_UINT_TO_USINT`, on the other hand, requires separate event and data connections.

The **AUI_TO_AUS** is a compact and focused function block for adapter-based conversion from UINT to USINT. Its composite structure facilitates integration into existing 4diac projects, reduces wiring effort, and improves clarity. Its simple functionality and clear interface make it a useful tool for all applications requiring type conversion at the adapter level.

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
