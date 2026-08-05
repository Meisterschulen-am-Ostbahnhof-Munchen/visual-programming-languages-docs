# AS_TO_AB
![AS_TO_AB](./AS_TO_AB.svg)
* * * * * * * * * *
## Introduction
The function block **AS_TO_AB** is a composite function block that converts an AS adapter (SINT) into an AB adapter (BYTE).
It serves as a bridge between different adapter types and enables data type conversion within an adapter-based communication chain.
The block internally uses the IEC 61131 function **F_SINT_TO_BYTE** and is implemented as a pure data converter without state logic.

## Interface Structure
Since the function block does not have direct event or data ports, inputs and outputs are provided via the following adapters:

### **Event Inputs**

| Port | Description |

|------|--------------|

| `AS_IN.E1` | Starts the conversion of a SINT value. |

### **Event Outputs**

| Port | Description |

|------|--------------|

| `AB_OUT.E1` | Signals the completion of the conversion. |

### **Data Inputs**

| Port | Data Type | Description |

|------|----------|--------------|

| `AS_IN.D1` | SINT | The value to be converted (Signed Short Integer). |

### **Data Outputs**

| Port | Data Type | Description |

|------|----------|--------------|

| `AB_OUT.D1` | BYTE | The converted value (byte). |

### **Adapter**

| Label | Type | Direction | Comment |

|-------------|-----|-----------|-----------|

| `AS_IN` | `adapter::types::unidirectional::AS` | Socket (Input) | SINT Adapter Input |

| `AB_OUT` | `adapter::types::unidirectional::AB` | Plug (Output) | BYTE Adapter Output |

## Functionality
1. An incoming event on `AS_IN.E1` triggers processing.

2. The current value of `AS_IN.D1` (SINT) is read.

3. The internal instance `F_SINT_TO_BYTE` performs the conversion to a BYTE value.

4. After successful conversion, an event is output on `AB_OUT.E1`, and the calculated BYTE value is made available on `AB_OUT.D1`.

The conversion strictly adheres to IEC 61131 semantics: The SINT value is mapped bitwise to the BYTE data type, without any sign or range considerations (since SINT comprises 8 bits, identical to BYTE).

## Technical Features
- **Composite FB**: The function block encapsulates the conversion logic and provides it as an adapter converter.
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional – data flows in only one direction.
- **No Internal State**: The FB behaves like a pure function; each activation produces the correct result regardless of the previous state.
- **Dependency**: The function block imports the IEC 61131 function `F_SINT_TO_BYTE`, which must be available in the target environment.

## State Overview

The FB has **no state diagram** – it is event-driven and performs a one-time conversion immediately upon each activation.

The internal element `F_SINT_TO_BYTE` is also stateless.

## Application Scenarios
- **Adapter Coupling**: If a sensor or actuator provides an AS adapter (SINT), but the downstream system expects an AB adapter (BYTE), this function block (FB) is used as an intermediary.
- **Protocol Conversion**: In PLC or automation systems, different data types often need to be converted between adapters – specifically SINT ↔ BYTE.
- **Modularization**: The FB allows conversion logic to be encapsulated in reusable adapter blocks, instead of having to implement it anew in each application FB.

## Comparison with Similar Function Blocks
- **AS_TO_WORD / AS_TO_INT**: Convert SINT to WORD or INT; AS_TO_AB specializes in BYTE.

``` - **Direct use of `F_SINT_TO_BYTE`**: The composite function block offers the advantage that the conversion is performed via adapter ports, eliminating the need for manual wiring of event and data flows.

- **Other adapter converters**: If similar adapter converters exist in the library (e.g., `AB_TO_AS`), this function block complements the unidirectional conversion in the opposite direction.

## Conclusion
The **AS_TO_AB** function block is a simple yet useful converter for adapter-based architectures.

It allows the seamless integration of SINT and BYTE-communicating components without requiring the user to program the underlying conversion themselves.

Thanks to its composite structure, the logic remains clear and maintainable – ideal for use in industrial control systems according to IEC 61499.
