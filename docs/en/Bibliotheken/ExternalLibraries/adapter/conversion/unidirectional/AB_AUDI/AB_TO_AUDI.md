# AB_TO_AUDI

![AB_TO_AUDI](./AB_TO_AUDI.svg)

* * * * * * * * * *

## Introduction
The function block **AB_TO_AUDI** is a composite function block (FB) that converts an AB adapter (data type BYTE) into an AUDI adapter (data type UDINT). It serves as an interface between different data formats in an IEC 61499-based automation environment.

## Interface Structure
The function block has no direct event or data input/output at the top level. Communication occurs exclusively via two adapters:

### **Event Inputs**
- None (events are provided via the socket adapter `AB_IN`)

### **Event Outputs**
- None (events are output via the plug adapter `AUDI_OUT`)

### **Data Inputs**
- None (data is provided via the socket adapter `AB_IN`)

### **Data Outputs**
- None (data is output via the plug adapter `AUDI_OUT`)

### **Adapter**
- **`AB_IN`** (Socket) – Type: `adapter::types::unidirectional::AB`

Accepts a BYTE signal. The adapter provides an event `E1` and a data value `D1` (BYTE).

- **`AUDI_OUT`** (Plug) – Type: `adapter::types::unidirectional::AUDI`

Outputs the converted UDINT signal. The adapter expects an event `E1` and a data value `D1` (UDINT).

## Functionality
The module internally uses a predefined conversion module `F_BYTE_TO_UDINT` from the IEC 61131 library. The process:

1. An event `E1` is received via socket `AB_IN`, triggering the start of the conversion.

2. Simultaneously, the corresponding BYTE data value from `AB_IN.D1` is forwarded to the converter `F_BYTE_TO_UDINT.IN`.

3. The converter calculates the UDINT value and outputs it at its output `OUT`.

4. The converter's acknowledgment event `CNF` is sent to the plug `AUDI_OUT.E1`.

5. The converted UDINT value is passed to the connected component via `AUDI_OUT.D1`.


This enables unidirectional BYTE-to-UDINT conversion with event-driven control.

## Technical Features

- **Unidirectional Adapters**: Both the input and output adapters are unidirectional – data flows in only one direction (BYTE → UDINT).

- **Synchronous Operation**: The conversion is strictly event-driven: Each incoming event `E1` triggers exactly one conversion and one outgoing event.

- **Standard Conversion**: The internal function block `F_BYTE_TO_UDINT` is an established IEC 61131 function block, ensuring that the conversion is standards-compliant and portable.


## State Overview
Since this is a purely composite component without its own state machine, the state logic results from the interaction of the internal connections:

- **Ready**: After initialization, wait for event `AB_IN.E1`.

- **Conversion Active**: After receiving `AB_IN.E1`, while the internal converter is working.

- **Output Ready**: After confirmation by `Convert.CNF`, until event `AUDI_OUT.E1` and the associated data value are transmitted.

## Application Scenarios

- **Protocol Adaptation**: When a sensor or actuator with a BYTE interface is to be connected to a control unit that expects UDINT (e.g., for counts, frequencies, or time values).

- **Data Preparation in Automation Networks**: Used in PLC or distributed systems to harmonize different data widths.

- **Adapter Bridge**: As an intermediary between predefined adapter types in an IEC 61499 application.

## Comparison with Similar Function Blocks

- **AB_TO_DINT**: Converts BYTE to DINT (signed) – here, the conversion is to UDINT (unsigned).

- **Direct Converters** such as `F_BYTE_TO_UDINT`: These are simple function blocks without an adapter interface. `AB_TO_AUDI` encapsulates this function block in an adapter structure and integrates event control.


## Conclusion

The function block `AB_TO_AUDI` provides a compact and reusable solution for converting BYTE data via an AB adapter to UDINT data via an AUDI adapter. The use of standardized conversion and adapters ensures high compatibility and clear interfaces in IEC 61499 systems.