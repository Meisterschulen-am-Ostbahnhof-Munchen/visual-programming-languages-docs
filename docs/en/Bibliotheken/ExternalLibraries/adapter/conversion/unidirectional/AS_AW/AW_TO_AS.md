# AW_TO_AS
![AW_TO_AS](./AW_TO_AS.svg)
* * * * * * * * * *
## Introduction
The function block `AW_TO_AS` is a composite block that converts a WORD-based adapter (AW) into a SINT-based adapter (AS). It encapsulates the necessary type conversion, thus enabling the easy integration of different adapter interfaces in automation technology.
## Interface Structure
### **Event Inputs**
- `AW_IN.E1` – Starts the conversion of the incoming data value.

### **Event Outputs**
- `AS_OUT.E1` – Signals that the converted value is available at the data output.

### **Data Inputs**
- `AW_IN.D1` (WORD) – The 16-bit value to be converted to a SINT value.

### **Data Outputs**
- `AS_OUT.D1` (SINT) – The converted 8-bit value (signed, range -128 … 127).

### **Adapter**
- **Socket (Input)**: `AW_IN` of type `adapter::types::unidirectional::AW`
- **Plug (Output)**: `AS_OUT` of type `adapter::types::unidirectional::AS`

## Functionality

The module is implemented as a composite and internally uses the IEC 61131 function block `F_WORD_TO_SINT`. An incoming event at `AW_IN.E1` triggers the conversion: The data value from `AW_IN.D1` is passed to the input `IN` of the internal converter. After successful conversion, this generates an acknowledgment event at `CNF`, which is forwarded to the output adapter `AS_OUT.E1`. Simultaneously, the converted SINT value is output to `AS_OUT.D1`.

## Technical Features
- The conversion follows the IEC 61131 function `WORD_TO_SINT`. An overflow occurs if the incoming WORD value is outside the valid SINT range (-128 … 127) – this must be taken into account in the application.
- The function block operates purely event-driven: Conversion only occurs when an event is present at the input.
- The adapters are unidirectional; conversion back from SINT to WORD is not supported.

## State Overview
Since this is a simple composite function block (FB) without its own state machine, there is no explicit state machine. The FB waits for an event, performs the conversion, and outputs the result synchronously. A state table is not required.

## Application Scenarios
- Adapting sensor data supplied as WORD (e.g., via an analog input) to a system that processes SINT values.
- Converting fieldbus data formats when coupling different automation components.
- Use in heterogeneous control environments where adapters use different data types.

## Comparison with Similar Function Blocks

Analogously structured converters such as `AW_TO_BY` (WORD → BYTE) or `AINT_TO_AUDINT` (INT → UDINT) follow the same principle. The `AW_TO_AS` function block stands out due to its specific adapter combination, which enables direct integration into adapter-based architectures. Unlike simple data-level type conversions, this block utilizes an event-driven adapter interface, thus increasing reusability and interchangeability.

## Conclusion
The composite function block `AW_TO_AS` offers a compact and clear solution for converting a WORD adapter to a SINT adapter. Encapsulating the conversion in a separate function block improves the readability and maintainability of the application. This function block is particularly suitable for environments where different data types are handled at the adapter level.
