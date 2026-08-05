# ADI_TO_AR
![ADI_TO_AR](./ADI_TO_AR.svg)
* * * * * * * * * *
## Introduction
The **ADI_TO_AR** function block is a composite module that converts a DINT adapter (ADI) into a REAL adapter (AR). It acts as an intermediary between components that communicate via unidirectional adapters, performing a data type conversion from integer (DINT) to floating-point number (REAL).
## Interface Structure
### **Event Inputs**
- No directly visible event inputs. Event control is handled indirectly via the **ADI_IN** adapter (event E1).

### **Event Outputs**
- No directly visible event outputs. Event signaling is handled indirectly via the **AR_OUT** adapter (event E1).

### **Data Inputs**
- No directly visible data inputs. The input data value is provided via the **ADI_IN** adapter (data point D1 of type DINT).

### **Data Outputs**
- No directly visible data outputs. The output data value is provided via the **AR_OUT** adapter (data point D1 of type REAL).

### **Adapters**

| Adapter | Role | Type | Description |

|---------|-------|-----|--------------|

| ADI_IN | Socket | adapter::types::unidirectional::ADI | Unidirectional DINT adapter as input interface. |

| AR_OUT | Plug | adapter::types::unidirectional::AR | Unidirectional REAL adapter as output interface. |

## Functionality
The function block internally contains a single function block, `F_DINT_TO_REAL`, from the IEC 61131-3 standard library. The sequence control is purely event-driven:

1. An event at the input adapter **ADI_IN.E1** triggers the input **REQ** of the internal conversion block.

2. The data value **ADI_IN.D1** (DINT) is passed to the input **IN** of the converter.

3. Upon completion of the conversion, the output **CNF** of the converter signals an event.

4. This event is forwarded to the output adapter **AR_OUT.E1**.

5. Simultaneously, the converted REAL value (output **OUT**) is passed to the data point **AR_OUT.D1**.

The entire process is synchronous and without intermediate storage – each successful conversion immediately triggers an output event.

## Technical Features
- **Type Conversion according to IEC 61131-3**: The internal function block `F_DINT_TO_REAL` guarantees standards-compliant conversion of 32-bit integers to floating-point numbers (single precision).
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional. Reverse communication is not supported, which simplifies implementation and clearly defines the data flow.
- **Composite Structure**: The function block consists of a network that is completely encapsulated within the function block itself. It is therefore particularly well-suited for modular, reusable interfaces.
- **No States**: There is no state machine – the functionality is purely combinatorial with an event-driven trigger.

## State Overview

The function block does not have its own state machine. The process can be described as a simple step:

| Step | Action |

|---------|--------|

| 1 | Wait for event at **ADI_IN.E1** |

| 2 | Convert the data value from DINT to REAL |

| 3 | Output the converted value to **AR_OUT.D1** and event to **AR_OUT.E1** |

| 4 | Return to step 1 |

## Application Scenarios
- **Sensor Integration**: A sensor provides integer measurements (e.g., speed, counter reading) via an ADI adapter. This function block is used as a converter for downstream control or visualization systems that expect REAL values.
- **Interface Adaptation**: In heterogeneous control systems where different components use different data types, this function block enables seamless integration without modifying existing adapter definitions.
- **Type-safe data processing**: Explicit conversion avoids runtime errors that can occur with implicit type conversions in IEC 61499.

## Comparison with similar function blocks
- **F_DINT_TO_REAL**: A direct call to this standard function block would serve the same purpose, but requires manual configuration of event and data connections. The adapter-based approach simplifies reuse and improves network readability.
- **ADI_TO_AR** in contrast to other conversion function blocks (e.g., REAL_TO_DINT): This function block is specifically designed for unidirectional adapter communication and does not offer any other conversion directions.
- **Composite function blocks without adapters**: Other implementations use direct data and event ports, which limits flexibility when replacing components. The adapter interface allows for simple plug-and-play in predefined architectures.

**F_DINT_TO_REAL**: ** ...
## Conclusion

The **ADI_TO_AR** function block represents an elegant and standards-compliant solution for converting DINT values to REAL values, fully embedded in the adapter-based communication structure of IEC 61499. By encapsulating the conversion process in a reusable composite component, it supports the development of modular, type-safe, and well-documented automation systems.
