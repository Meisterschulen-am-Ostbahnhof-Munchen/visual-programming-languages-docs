# AL_SPLIT_4

![AL_SPLIT_4](./AL_SPLIT_4.svg)

* * * * * * * * * *
## Introduction

The function block **AL_SPLIT_4** is a generic function block that splits a single adapter input (socket) of type `adapter::types::unidirectional::AL` into four separate outputs (plugs) of the same type. It serves to distribute an incoming adapter data stream to multiple parallel consumers without modifying the data itself.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AL` | **IN** | Socket (Input) | Incoming adapter data stream, distributed to all outputs. |
| `adapter::types::unidirectional::AL` | **OUT1** | Plug (Output) | First output – receives an identical copy of the input data stream. |
| `adapter::types::unidirectional::AL` | **OUT2** | Plug (Output) | Second output – receives an identical copy of the input data stream. |
| `adapter::types::unidirectional::AL` | **OUT3** | Plug (Output) | Third output – receives an identical copy of the input data stream. |
| `adapter::types::unidirectional::AL` | **OUT4** | Plug (Output) | Fourth output – receives an identical copy of the input data stream. |

## Functionality

This component is a pure signal distributor. It has internal logic that – as soon as the adapter input **IN** is connected to a data source – forwards the incoming data packets (events and data) directly and unchanged to all four output adapters **OUT1** to **OUT4**. No buffering, delay, or logical processing takes place. Each output receives exactly the same information as the input.

## Technical Features

- **Generic Component:** The class `GEN_AL_SPLIT` is defined in the attribute `eclipse4diac::core::GenericClassName`, which means that the component can be reused as a template for various implementations of the adapter type `AL`.
- **No states or timing:** Since the function block operates exclusively on a line-based basis and has no processing logic, there are no internal states or concurrent execution sequences.
- **Adapter type:** The adapter used, `adapter::types::unidirectional::AL`, is a standardized, unidirectional adapter from the library `adapter::types::unidirectional`. Its exact interface (included events and data) is defined by the adapter definition and is not influenced by the split block itself.

## State overview

The function block does not have a state machine. It operates statically and permanently distributes the input signal to all outputs.

## Application scenarios

- **Distributing a control signal** to multiple parallel actuator units, e.g., in agricultural technology (as indicated in the copyright notice of HR Agrartechnik GmbH).
- **Splitting a measurement data source** across multiple analysis or logging modules.
- **Testing and Debugging:** An original adapter signal can be routed to multiple outputs to be sent to different test instances simultaneously.

## Comparison with Similar Function Blocks

- **AL_SPLIT_2** – splits an AL signal across two outputs (fewer outputs, lower fan-out capacity).
- **AL_MERGE** – combines multiple AL inputs into one output (inverse function).
- **Event-based split function blocks (e.g., SPLIT_EVENT)** – split only events without duplicating the associated data adapters.

Unlike these function blocks, `AL_SPLIT_4` operates exclusively at the adapter level and copies complete adapter communication streams.

## Conclusion

The **AL_SPLIT_4** function block is a simple, efficient signal fan for the `AL` adapter type. It is ideally suited for all applications where a single adapter data stream needs to be distributed to multiple consumers without additional logic or delays. Its generic nature allows its use in various automation contexts, particularly in agricultural machinery control, as intended by the manufacturer.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
