# ALR_DEMUX_2
![ALR_DEMUX_2](./ALR_DEMUX_2.svg)

* * * * * * * * * *
## Introduction
The ALR_DEMUX_2 is a generic demultiplexer function block for ALR data. It forwards an incoming ALR value, provided via socket IN, to one of the two output adapters OUT1 or OUT2 based on an index K. Switching is triggered by the REQ event.
## Interface Structure
### **Event Inputs**
- **REQ**: Triggers the forwarding. The index K is evaluated.

### **Event Outputs**
- **CNF**: Confirms successful processing of the REQ event.

### **Data Inputs**
- **K** (UINT): Index indicating which output the value should be routed to (e.g., 0 for OUT1, 1 for OUT2).

### **Data Outputs**

No direct data outputs. Output is provided via adapters OUT1 and OUT2.

### **Adapters**
- **IN** (Socket, Type: `adapter::types::unidirectional::ALR`): Input adapter for the ALR value to be demultiplexed.
- **OUT1** (Plug, Type: `adapter::types::unidirectional::ALR`): First output adapter.
- **OUT2** (Plug, Type: `adapter::types::unidirectional::ALR`): Second output adapter.

## Operation
The function block operates in an event-driven manner. Upon a REQ event, the current value of input K is read. Depending on K, the IN adapter is connected to OUT1 (e.g., when K=0) or to OUT2 (when K=1). The CNF event is then output. The function block is stateless; each request results in an immediate reconnection.

## Technical Features
- The function block is declared as a generic function block (GenericClassName "GEN_ALR_DEMUX"), which allows for flexible reuse in different contexts.
- It uses the user-defined adapter type `adapter::types::unidirectional::ALR`.
- The function block is provided under the Eclipse Public License 2.0 (SPDX license identifier: EPL-2.0).
- No internal states or algorithms are defined in the XML; the logic is implemented by the 4diac IDE or the runtime system.

## State Overview
The function block does not have an explicit state machine. The functionality can be described as a simple switch with no memory. After a REQ has been processed, the connection remains open until the next request.

## Application Scenarios
- Splitting an ALR data stream into two different processing paths in an automation application.
- Switching between two sensors or actuators that communicate via the ALR protocol.
- Testing and diagnostic purposes to temporarily reroute a data path.

## Comparison with Similar Components
- **ALR_DEMUX_2** is specific to ALR data. A general-purpose demultiplexer (e.g., with an ANY data type) would be more flexible but not optimized for ALR.
- A multiplexer (ALR_MUX) would perform the opposite function: combining multiple inputs into one output.
- The component is similar to a 1-to-2 demultiplexer in digital technology, but at the adapter level.

## Conclusion

The ALR_DEMUX_2 is a useful, simple demultiplexer for ALR data. Its clear interface and event-driven operation make it well-suited for applications that require targeted routing of ALR connections. Thanks to its generic declaration, it can be easily integrated into existing 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
