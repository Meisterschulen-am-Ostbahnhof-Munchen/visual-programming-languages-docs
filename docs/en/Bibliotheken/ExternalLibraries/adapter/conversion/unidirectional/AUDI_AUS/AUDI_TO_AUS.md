# AUDI_TO_AUS

![AUDI_TO_AUS](./AUDI_TO_AUS.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_TO_AUS** serves as a composite block for converting a UDINT value (via the AUDI adapter) into a USINT value (via the AUS adapter). It encapsulates the conversion and allows for easy integration of components that expect different data types.
## Interface Structure

### **Event Inputs**

- **AUDI_IN.E1** (event from the AUDI adapter) – initiates the conversion of the incoming data value.

### **Event Outputs**

- **AUS_OUT.E1** (event to the AUS adapter) – signals the completion of the conversion and the availability of the result.

### **Data Inputs**

- **AUDI_IN.D1** (UDINT from the AUDI adapter) – the 32-bit value to be converted.

### **Data Outputs**

- **AUS_OUT.D1** (USINT to the AUS adapter) – the converted 8-bit value.

### **Adapters**

- **AUDI_IN** (Socket) – adapter of type `adapter::types::unidirectional::AUDI` (UDINT source).
- **AUS_OUT** (Plug) – adapter of type `adapter::types::unidirectional::AUS` (USINT sink).

## Functionality

The module is implemented as a simple pass-through. In the FBNetwork, the incoming event pulse (`AUDI_IN.E1`) is forwarded directly to the internal conversion block `F_UDINT_TO_USINT`. Simultaneously, the data value `AUDI_IN.D1` is transferred to the input `IN` of the converter. After successful conversion, the converter sends the confirmation event (`CNF`) to the output adapter (`AUS_OUT.E1`) and the result (`OUT`) to the data output (`AUS_OUT.D1`). No intermediate storage or further logic takes place.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- Uses the standard conversion block `iec61131::conversion::F_UDINT_TO_USINT` from the IEC 61131 library.
- Pure event and data forwarding – no separate state machine required.
- The conversion is lossy: A UDINT (32-bit) is mapped to a USINT (8-bit), meaning higher-order bits are lost (values > 255 are truncated or handled according to the manufacturer's definition).

## State Overview

The composite chip has no states of its own; it is entirely event-driven. The internal converter `F_UDINT_TO_USINT` operates according to the standard protocol (REQ/CNF). There are no additional locks or delays.

## Application Scenarios

- Connecting a UDINT-based sensor to an actuator that only accepts a USINT value.
- Converting addresses or count values when only the lower-order part is needed.
- Interface adaptation in a mixed IEC 61499 environment where various data types are used.

## Comparison with similar function blocks

- **AUDI_TO_AUDI** or **AUS_TO_AUS**: Would not perform any conversion, but only a simple forwarding.
- **F_UDINT_TO_USINT** (direct): This function block performs the same conversion, but does not offer an adapter interface. `AUDI_TO_AUS` encapsulates the adapter types and simplifies the network structure.
- If range checking or error handling is required, a separate function block would have to be created; this function block does not perform any plausibility checks.

## Conclusion

AUDI_TO_AUS` is a simple yet useful strip-down function block for unidirectional UDINT-to-USINT conversion via adapters. It reduces complexity in the FB network by combining adapter coupling and conversion logic into a single block. Due to the lack of error handling, it is only suitable for applications where values > 255 do not occur or where their loss can be tolerated.
