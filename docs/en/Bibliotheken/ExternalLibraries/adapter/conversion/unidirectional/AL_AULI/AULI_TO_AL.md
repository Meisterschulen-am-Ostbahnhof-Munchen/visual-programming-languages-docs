# AULI_TO_AL
![AULI_TO_AL](./AULI_TO_AL.svg)
* * * * * * * * * *
## Introduction
The function block `AULI_TO_AL` is a composite function block for converting an AULI adapter (data type ULINT) into an AL adapter (data type LWORD). Internally, it uses the IEC 61131 conversion function `F_ULINT_TO_LWORD` and is intended for use in unidirectional adapter structures.
## Interface Structure

### **Event Inputs**

| Name | Description |

|---------------|------------------------------------------------------|

| AULI_IN.E1 | Event input via the AULI_IN socket. Starts the conversion. |

### **Event Outputs**

| Name | Description |

|---------------|------------------------------------------------------|

| AL_OUT.E1 | Event output via the AL_OUT plug. Signals the completion of the conversion. |

### **Data Inputs**

| Name | Data Type | Description |

|---------------|----------|------------------------------------------------------|

| AULI_IN.D1 | ULINT | Input value to be converted to LWORD. |

### **Data Outputs**

| Name | Data Type | Description |

|---------------|----------|-----------------------------------------------------|

| AL_OUT.D1 | LWORD | Converted output value. |

### **Adapter**

| Name | Type | Direction | Description |

|-------------|-----------|----------|------------------------------------------|

| AULI_IN | AULI (ULINT) | Socket | Unidirectional input adapter. |

| AL_OUT | AL (LWORD) | Plug | Unidirectional output adapter. |

## Functionality

This function block operates as a simple forwarder: An incoming event at `AULI_IN.E1` triggers the internal function block `F_ULINT_TO_LWORD`, which reads the current value of `AULI_IN.D1` and converts it into an LWORD value. After the conversion is complete, the result value is output to `AL_OUT.D1`, and a completion event is simultaneously sent to `AL_OUT.E1`. The internal logic is limited to the data and event connections between the socket and the internal converter.

## Technical Features
- **Composite Implementation**: The function block does not contain its own execution control logic (ECC) but consists exclusively of a linked function block from the IEC 61131 library.
- **Adapter Architecture**: Both the input and output are designed as unidirectional adapters (socket/plug), enabling loose coupling and easy reuse in various applications.
- **Type Conversion**: The conversion from ULINT (unsigned 64-bit integer) to LWORD (64-bit bit field) is performed according to the IEC 61131 standard.

## State Overview

This function block does not have its own state machine. All functionality is implemented by the internal function block `F_ULINT_TO_LWORD`, which operates as a stateless function. Event control is handled exclusively via the connections defined in the netlist.

## Application Scenarios
- Integration of sensor systems that deliver ULINT data via an AULI adapter into controllers that expect LWORD data via an AL adapter.
- Data type migration or protocol adaptation in existing automation solutions.
- Uniform adapter interfaces for libraries that represent different physical quantities or address spaces.

## Comparison with Similar Function Blocks

Unlike generic converter function blocks (e.g., `ULINT_TO_LWORD`), `AULI_TO_AL` is specifically designed for adapter-based data exchange. Similar adapter converters exist for other data types (e.g., `BOOL_TO_BYTE`, `INT_TO_DINT`), but they differ in the adapter types used and the internal conversion function. This function block adds a clean, typed interface for ULINT↔LWORD to the library.

## Conclusion

`AULI_TO_AL` is a simple yet reliable composite function block for converting between AULI and AL adapters. Direct use of the standardized IEC 61131 function ensures high compatibility and accuracy of the conversion. The adapter interfaces enable modular integration into complex automation systems.