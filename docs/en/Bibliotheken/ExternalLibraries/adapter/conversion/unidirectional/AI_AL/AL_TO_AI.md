# AL_TO_AI
![AL_TO_AI](./AL_TO_AI.svg)
* * * * * * * * * *
## Introduction
The AL_TO_AI function block is a composite block that converts a unidirectional AL adapter (LWORD) into a unidirectional AI adapter (INT). It serves as an interface converter for adapter-based communication and enables easy integration between components that use different data types. The conversion is performed internally using the standardized IEC 61131-3 function block F_LWORD_TO_INT.
## Interface Structure
### **Event Inputs**
The function block does not have explicit event inputs. Event control is handled indirectly via the socket adapter **AL_IN**, which provides the event **E1**.

### **Event Outputs**
The function block does not have explicit event outputs. Event control is handled indirectly via the plug adapter **AI_OUT**, which provides the event **E1**.

### **Data Inputs**
The function block (FB) has no explicit data inputs. The data to be received is provided as an LWORD via the socket adapter **AL_IN**.

### **Data Outputs**
The FB has no explicit data outputs. The converted data is output as an INT via the plug adapter **AI_OUT**.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|-------------|

| **AL_IN** | Socket (Input) | `adapter::types::unidirectional::AL` | Provides an LWORD (via data port D1) and an event (E1). |

| **AI_OUT** | Plug (Output) | `adapter::types::unidirectional::AI` | Provides an INT (via data port D1) and an event (E1). |

## Functionality
The FB acts as a transparent converter between the two adapters. As soon as the event **E1** arrives at socket **AL_IN**, the internal function block **F_LWORD_TO_INT** is triggered with the passed LWORD value (from **AL_IN.D1**). The conversion block converts the value to an INT and signals completion via the event **CNF**. This event is forwarded directly to plug **AI_OUT** (E1), and the converted INT (from **F_LWORD_TO_INT.OUT**) is output on **AI_OUT.D1**. The entire conversion occurs synchronously within a single event cycle.

```
## Technical Features

- **Composite Architecture**: The function block (FB) internally uses a standardized IEC 61131-3 function block (`F_LWORD_TO_INT`), which can be implemented platform-independently.
- **Unidirectional Adapters**: Both the input and output adapters are of type `unidirectional`, meaning they only support one data and event direction (from socket to plug).
- **No Internal Logic**: The FB contains no state logic or sequences; it functions solely as a coupler and converter.
- **Type Conversion**: Converting from LWORD (64-bit) to INT (16-bit) can lead to data loss (truncation of higher-order bits), depending on the value range. This must be considered in the application context.

## State Overview
The composite function block does not have its own states. The behavior is entirely determined by the internal **F_LWORD_TO_INT** function, which is a pure function without state. The sequence control is event-driven: an input event is immediately followed by an output event.

## Application Scenarios
- **Adapter Bridge**: Connecting a component that provides LWORD via an AL adapter to a component that expects INT via an AI adapter.
- **System Integration**: Use in heterogeneous automation systems where different adapter types interact.
- **Protocol Adaptation**: Data conversion in a service-oriented architecture (e.g., 4diac) to adapt interfaces from various IEC 61499 or IEC 61131 libraries.

## Comparison with Similar Function Blocks
- **AL_TO_AI** is specific to the combination of unidirectional AL and AI adapters. Other converters, such as `LWORD_TO_INT`, operate at a pure data level without adapter encapsulation.
- The 4diac ecosystem includes other adapter converters (e.g., `AI_TO_AL`) that cover the reverse direction. `AL_TO_AI` fills the gap for unidirectional LWORD→INT conversion.
- Compared to directly using `F_LWORD_TO_INT`, the Composite FB offers the advantage of a standardized adapter interface, enabling simple plug-and-play integration.

## Conclusion
The **AL_TO_AI** function block is a useful, lightweight converter for switching between unidirectional LWORD and INT adapters. It encapsulates the proven IEC 61131-3 conversion in an adapter-friendly format, thus facilitating the reuse and replacement of components in IEC 61499-based systems. Thanks to its event-driven handling, it integrates seamlessly into event-driven workflows and requires no additional configuration.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
