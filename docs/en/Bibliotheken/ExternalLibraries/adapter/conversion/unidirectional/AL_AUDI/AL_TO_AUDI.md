# AL_TO_AUDI

![AL_TO_AUDI](./AL_TO_AUDI.svg)

* * * * * * * * * *

## Introduction

The function block **AL_TO_AUDI** is a composite block that converts an LWORD adapter input (type `AL`) into a UDINT adapter output (type `AUDI`). It encapsulates the IEC 61131-3 conversion function `F_LWORD_TO_UDINT` and provides a clean, adapter-based interface for unidirectional data flows.

## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs. Event control is handled entirely via the integrated socket adapter `AL_IN`.

### **Event Outputs**

The function block (FB) does not have direct event outputs. Events are passed to subsequent logic via the integrated plug adapter `AUDI_OUT`.

### **Data Inputs**

The FB does not have direct data inputs. The LWORD data to be converted is received via the socket adapter `AL_IN`.

### **Data Outputs**

The FB does not have direct data outputs. The converted UDINT data is output via the plug adapter `AUDI_OUT`.

### **Adapters**

| Adapter Type | Name | Description |
| ------------ | ----------- | ------------------------------------------------------- |
| Socket | `AL_IN` | LWORD adapter input (Type: `adapter::types::unidirectional::AL`) |
| Plug | `AUDI_OUT` | UDINT adapter output (Type: `adapter::types::unidirectional::AUDI`) |

## Functionality

1. An incoming event at socket `AL_IN` (via its event output `E1`) triggers the conversion instance `Convert` (Type `F_LWORD_TO_UDINT`).
2. Simultaneously, the LWORD data value from `AL_IN.D1` is transferred to the input `IN` of `Convert`.

3. The conversion function converts the LWORD value into a UDINT value.

4. After successful conversion, `Convert` signals this via its event output `CNF`, causing the plug `AUDI_OUT` to receive an event at its event input `E1`.
5. The converted UDINT value is passed from the output `OUT` of `Convert` to the data input `D1` of `AUDI_OUT` and is thus available at the output adapter.

## Technical Features

- **Composite Architecture**: The function block consists solely of the internal use of the function block `F_LWORD_TO_UDINT` and the adapters. It has no independent state logic or additional control.
- **Unidirectional Adapters**: Both `AL_IN` and `AUDI_OUT` are unidirectional adapters (input to output).
- **IEC 61131-3 Compliance**: The conversion uses a standardized IEC 61131-3 function, which increases reusability and interchangeability.

## State Overview

The function block has no states of its own. Its behavior is purely combinatorial and is entirely determined by the internal conversion function – the conversion occurs per event without internal storage.

**Unidirectional Adapters**: ** ...

## Application Scenarios

- **System Integration**: Connecting components that use different data types for addresses, counters, or configuration values (e.g., LWORD for wide addresses, UDINT for embedded systems).
- **Adapter Architectures**: Use in modular automation solutions where standardized interfaces are provided via adapters.
- **Data Preparation**: Converting LWORD signals from sensors or bus systems to UDINT for further processing in controllers.

## Comparison with Similar Components

- **Simple Type Converters** (e.g., `F_LWORD_TO_UDINT`): These work directly with input/output variables, while `AL_TO_AUDI` encapsulates the conversion in an adapter interface, thus offering a higher level of abstraction.
- **Other adapter converters** (e.g., `UDINT_TO_DINT`): Similar concepts, but for different data types and directions. `AL_TO_AUDI` is specifically for the unidirectional conversion of LWORD to UDINT.

## Conclusion

The function block `AL_TO_AUDI` is a compact and reusable building block for converting LWORD to UDINT data via standardized adapters. It simplifies the integration of components with different data types and promotes a modular, adapter-based architecture in automation technology.
