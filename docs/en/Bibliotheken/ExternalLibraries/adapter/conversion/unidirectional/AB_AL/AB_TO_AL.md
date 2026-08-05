# AB_TO_AL

![AB_TO_AL](./AB_TO_AL.svg)

* * * * * * * * * *

## Introduction

The function block `AB_TO_AL` is a composite block for converting a unidirectional BYTE adapter (type `AB`) into a unidirectional LWORD adapter (type `AL`). It is used to convert data from an 8-bit data format to a 64-bit data format, thereby transferring the event control of the source adapter to the target adapter.

## Interface Structure

### **Event Inputs**

The block does not have direct event inputs. Incoming events are received indirectly via the socket adapter `AB_IN`. The adapter `AB` provides an internal event input (`E1`) that is connected to the event output of the target adapter.

### **Event Outputs**

This function block does not have direct event outputs. The outgoing event flow is indirect via the plug adapter `AL_OUT`. The adapter `AL` provides an internal event output (`E1`) that is activated by the internal connection.

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| `AB_IN.D1` | BYTE | 8-bit input value (via the socket adapter) |

### **Data Outputs**

| Name | Data Type | Description |

|------|----------|--------------|

| `AL_OUT.D1` | LWORD | 64-bit output value (via the plug adapter) |

### **Adapters**

| Name | Direction | Adapter Type | Description |

|------|----------|--------------|--------------|

| `AB_IN` | Socket | `adapter::types::unidirectional::AB` | Input adapter, returns BYTE data and an event |

| `AL_OUT` | Plug | `adapter::types::unidirectional::AL` | Output adapter, expects LWORD data and passes on an event |

## Functionality

The component is implemented as a pure wiring (composite) circuit. Internally, the following connections are established:

- Event: `AB_IN.E1` → `AL_OUT.E1`

- Data: `AB_IN.D1` → `AL_OUT.D1`

As soon as an event arrives at the socket adapter `AB_IN`, the corresponding BYTE value (`D1`) is passed to the data output `AL_OUT.D1`, and simultaneously the event is forwarded to `AL_OUT.E1`. An implicit type conversion from BYTE (8 bits) to LWORD (64 bits) takes place – the upper 56 bits are padded with zeros. The component has no internal state logic or delay.


## Technical Features

- **Pure Composite Block**: No algorithm, no state machine – functionality is derived solely from the internal wiring.

- **Unidirectional Adapters**: Data flow is only possible from `AB_IN` to `AL_OUT`; there is no reverse direction.

- **Automatic Type Conversion**: The 4diac IDE implicitly performs the conversion from BYTE to LWORD (big-endian extension with zeros).

- **No Parameters or Configuration**: The block requires no additional settings.

## State Overview

As a composite block without its own state machine, there is no defined state. Its behavior is entirely determined by the incoming events and data of the socket adapter.


## Application Scenarios

- **Interface Adaptation**: A sensor delivers BYTE data via an AB adapter, but the downstream system expects LWORD data via an AL adapter.

- **Data Preparation**: Simplified integration of 8-bit devices into 64-bit control architectures.

- **Protocol Conversion**: When events and data are encapsulated via adapters, `AB_TO_AL` can serve as a universal conversion stage.

## Comparison with Similar Components

Other adapter conversion components exist, such as `WORD_TO_DWORD`, `ARRAY_TO_STRUCT`, or specific type converters. However, `AB_TO_AL` is distinguished by its complete encapsulation within adapters – both events and data are converted together. This simplifies the exchange of complete interfaces without the need to model separate data and event connections.

## Conclusion

`AB_TO_AL` is a simple yet useful composite building block for converting a BYTE adapter to an LWORD adapter. It reduces the modeling effort for type conversions in adapter-based networks and ensures that events are passed on synchronously with the data. Due to its clearly defined interface, it is particularly well-suited for modular and reusable automation solutions.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]