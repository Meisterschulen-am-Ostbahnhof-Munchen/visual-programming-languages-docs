# AL_TO_AUS

![AL_TO_AUS](./AL_TO_AUS.svg)

* * * * * * * * * *
## Introduction

The function block AL_TO_AUS converts an AL adapter (LWORD) into an AUS adapter (USINT). It is implemented as a composite function block and encapsulates the conversion logic using the function block F_LWORD_TO_USINT. Input and output are handled via unidirectional adapter interfaces.
## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs. Instead, events are received via the adapter socket `AL_IN`. This socket provides the event input `E1`.

- **`AL_IN.E1`** (event): Trigger for data conversion.

### **Event Outputs**

The FB has no direct event outputs. Events are sent via the adapter plug `AUS_OUT`. This plug provides the event output `E1`.

- **`AUS_OUT.E1`** (Event): Signals the completion of the conversion and the availability of the output value.

### **Data Inputs**

The data is provided via the adapter socket `AL_IN`.

- **`AL_IN.D1`** (LWORD): The LWORD value to be read and converted into a USINT value.

### **Data Outputs**

The converted data is output via the adapter plug `AUS_OUT`.

- **`AUS_OUT.D1`** (USINT): The converted USINT value.

### **Adapters**

- **Socket `AL_IN`** (Type: `adapter::types::unidirectional::AL`): Unidirectional LWORD input adapter.
- **Plug `AUS_OUT`** (Type: `adapter::types::unidirectional::AUS`): Unidirectional USINT output adapter.

## Functionality

The function block waits for an event at the input adapter `AL_IN.E1`. As soon as this event occurs, the LWORD value at `AL_IN.D1` is read and passed to the internal conversion function block `F_LWORD_TO_USINT`. This performs the conversion to a USINT value. After successful conversion, the result is forwarded to the output adapter `AUS_OUT.D1`, and an event is simultaneously sent to `AUS_OUT.E1`.

The internal connections are:

- From the event input of the socket to the `REQ` input of the converter.
- From the `CNF` output of the converter to the event output of the plug.
- From the data input of the socket to the `IN` input of the converter.
- From the `OUT` output of the converter to the data output of the plug.

## Technical Features

- **Bit-reinterpretation**, value-preserving only if the source value fits the narrower destination width (otherwise the upper bits are silently dropped).

- The function block is implemented as a composite function block (FB) that utilizes the IEC 61131 conversion function `F_LWORD_TO_USINT`.
- The adapters are unidirectional, meaning data and event flows only in one direction.
- The conversion function block is from the library `iec61131::conversion`.
- Encapsulating the conversion logic in a composite function block increases its reusability and interchangeability.

## State Overview

The function block does not have its own defined state machine. The internal logic consists of a single conversion function block and fixed connections. The process is purely event-driven:

1. Wait for an event at the input (`AL_IN.E1`).
2. Perform the conversion.
3. Output the result and set an event at the output (`AUS_OUT.E1`).

## Application Scenarios

- Connecting sensors or actuators that provide an LWORD value to a system that expects USINT.
- Protocol implementation in automation systems where different data types need to be converted between adapters.
- Integration into larger composite function blocks that combine multiple conversion steps.

## Comparison with Similar Function Blocks

- **F_LWORD_TO_UINT**: Converts LWORD to UINT (16 bits).
- **F_LWORD_TO_DWORD**: Converts LWORD to DWORD (32 bits).
- **F_LWORD_TO_BYTE**: Converts LWORD to BYTE (8 bits), but returns a signed/unsigned value. USINT is unsigned 8 bits.
- This function block fills the gap for direct conversion to the USINT data type within the adapter context.

## Conclusion

The composite function block AL_TO_AUS offers a simple and clean solution for converting an LWORD adapter input to a USINT adapter output. By using standardized conversion blocks and encapsulating the conversion in a dedicated function block type, the maintainability and readability of the overall system are improved. It is particularly suitable for scenarios where unidirectional adapter interfaces with different data types need to be connected.
