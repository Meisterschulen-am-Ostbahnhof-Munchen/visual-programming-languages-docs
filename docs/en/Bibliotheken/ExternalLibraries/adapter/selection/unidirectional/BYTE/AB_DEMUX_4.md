# AB_DEMUX_4
![AB_DEMUX_4](./AB_DEMUX_4.svg)

* * * * * * * * * *
## Introduction
The function block AB_DEMUX_4 is a generic demultiplexer for the adapter type `adapter::types::unidirectional::AB`. It distributes incoming adapter data (IN) to one of four output adapters (OUT1–OUT4), controlled by an index K. The block is designed as a generic FB (GenericClassName `'GEN_AB_DEMUX'`) and can be parameterized for various specific adapter versions.
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-----------|
| **REQ** | Sets the index K and triggers the distribution. |

### **Event Outputs**

| Event | Comment |
|----------|-----------|
| **CNF** | Confirmation of successful indexing and distribution. |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| **K** | UINT | Index (value range 1–4), selects the destination output. |

### **Data Outputs**

No separate data outputs are available; the output data is provided via the adapter plugs.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Socket (Input) | **IN** | adapter::types::unidirectional::AB | Input adapter that supplies the data to be distributed. |
| Plug (Output) | **OUT1** | adapter::types::unidirectional::AB | First output adapter (Index 1). |
| Plug (Output) | **OUT2** | adapter::types::unidirectional::AB | Second output adapter (Index 2). |
| Plug (Output) | **OUT3** | adapter::types::unidirectional::AB | Third output adapter (Index 3). |
| Plug (Output) | **OUT4** | adapter::types::unidirectional::AB | Fourth output adapter (Index 4). |

## Functionality

This function block operates in an event-driven manner. As soon as an event arrives at the **REQ** event input, the index at the **K** data input is evaluated (values 1 to 4). The adapter **IN** is connected to the output adapter corresponding to the index, meaning that data received via the socket is forwarded to the selected plug (OUT1..OUT4). After the forwarding is complete, the event **CNF** is triggered. For invalid index values, no forwarding occurs, but CNF is still triggered (implicit behavior – the exact response is application-dependent).

## Technical Features
- The function block (FB) is declared as a **generic function block** (`GenericClassName = 'GEN_AB_DEMUX'`). This allows it to be used for various specific adapter types (derived from `adapter::types::unidirectional::AB`).
- No data I/O outside the adapters is used; all data transmission occurs via the adapter interfaces.
- The function block has no internal state memory – each REQ event is processed independently.

## State Overview

The AB_DEMUX_4 function block does **not have an explicit state machine**. It behaves like a purely combinational signal switch: Each REQ is immediately followed by the corresponding forwarding and the output of CNF. Since no state is retained, the behavior is deterministic and free of memory effects.

## Application Scenarios
- **Data Path Switching**: In a production plant, sensor data (e.g., via an AB adapter) is to be forwarded to different control units depending on the operating mode.
- **Process Value Routing**: A central data stream (e.g., fill level, temperature) is distributed across multiple parallel processing branches.
- **Test and Simulation Environments**: A simulated data stream is selectively routed to various test cases or visual components.

## Comparison with Similar Components
- **AB_MUX (Multiplexer)**: Reverses the function – multiple inputs are multiplexed to a single output. AB_DEMUX_4 implements the opposite case.
- **AB_DEMUX_2 / AB_DEMUX_8**: Variants with two or eight outputs, respectively. The present module offers exactly four outputs and an index in the range 1 to 4.
- **Direct connection via adapter**: Without a demultiplexer, a separate adapter socket would have to be created for each destination; the demultiplexer saves resources and simplifies configuration.

## Conclusion

The AB_DEMUX_4 is a compact, generic demultiplexer for unidirectional AB adapters. It enables flexible and resource-efficient distribution of adapter data to up to four outputs and is particularly suitable for applications where a data stream needs to be selectively routed to different devices. Its generic design increases reusability in various 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
