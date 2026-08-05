# AL_TO_AB

![AL_TO_AB](./AL_TO_AB.svg)

* * * * * * * * * *
## Introduction
The function block **AL_TO_AB** is a composite function block that enables unidirectional conversion from an LWORD adapter (AL) to a BYTE adapter (AB). It is used to convert data from an LWORD-based adapter to the format of a BYTE adapter, with the conversion being performed internally by the IEC 61131-3 block `F_LWORD_TO_BYTE`.

## Interface Structure
### **Adapter (Input)**

| Name | Type | Description |

|------|-----|--------------|

| AL_IN | `adapter::types::unidirectional::AL` | LWORD adapter socket. This adapter receives the LWORD data to be converted. By default, the adapter provides an event output `E1` and a data output `D1` (data type LWORD). |

### **Adapter (Output)**

| Name | Type | Description |

|------|-----|-------------|

| AB_OUT | `adapter::types::unidirectional::AB` | BYTE adapter plug. This adapter outputs the converted BYTE data. The adapter has an event input `E1` and a data input `D1` (data type BYTE). |


**Note:** The function block (FB) has no separate event or data inputs/outputs; all communication takes place via the two adapter interfaces.

## Functionality
1. An event (at the adapter's event output `E1`) is received via socket `AL_IN`, which simultaneously provides an LWORD value via data output `D1`.

2. This event internally triggers the function block `F_LWORD_TO_BYTE` (type: `iec61131::conversion::F_LWORD_TO_BYTE`), which converts the LWORD value into a BYTE value.

3. After successful conversion, `F_LWORD_TO_BYTE` signals completion via its event output `CNF`, which forwards the event to plug `AB_OUT`.

4. Simultaneously, the converted BYTE value is transferred via the converter's data output `OUT` to the data input `D1` of `AB_OUT`.

5. The connected receiver on plug `AB_OUT` thus receives the event and the converted data value.


4. ## Technical Features

- **Integration of IEC 61131-3**: The conversion uses the standardized function block `F_LWORD_TO_BYTE` from the IEC 61131-3 library. This ensures that the conversion logic is standards-compliant and portable.

- **Composite Structure**: The function block consists exclusively of an internal network, has no independent state (ECC), and therefore operates in an event-driven manner without delay.

- **Unidirectional Adapters**: The unidirectional adapters `AL` and `AB` are used, which define a clear direction for data and event flows.

- **Package Structure**: The function block is organized in the package `adapter::conversion::unidirectional`, which facilitates reuse in modular projects.

## State Overview
The function block does not have its own state machine. The entire process control is managed via the event chain of the internal network. Therefore, status monitoring is not required.

## Application Scenarios

- **Protocol Adaptation**: When an adapter in a distributed system that delivers LWORD data needs to be replaced by an adapter that only processes BYTE data.

- **System Integration**: Coupling components that use different adapter formats (e.g., AL and AB adapters) without modifying the original components.

- **Data Reduction**: Targeted conversion of 64-bit LWORD to 8-bit BYTE when the higher bytes are not needed or a narrower interface is required.

## Comparison with Similar Components

| Component | Function | Difference |

|----------|----------|-------------|

| `LWORD_TO_BYTE` | Pure data type conversion without adapters | No adapter interface; direct data and event ports |

`AB_TO_AL` | Reverse conversion (BYTE → LWORD) | Opposite direction; also composite with adapters |

`WORD_TO_BYTE` | Conversion from WORD (16-bit) to BYTE | Different data type; similar structure, but different adapter types |

The **AL_TO_AB** is specifically designed for use with the unidirectional adapters `AL` and `AB` and offers clean, reusable encapsulation.


## Conclusion

The `AL_TO_AB` function block provides a simple yet effective solution for converting an LWORD adapter signal into a BYTE adapter signal. By using a standardized IEC 61131-3 converter and a consistent adapter interface, it is easily integrated into existing systems and promotes a modular, maintainable design.