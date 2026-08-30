# NetEv2NetEv

<img width="1476" height="216" alt="image" src="https://github.com/user-attachments/assets/9bc9ef5f-0a9d-4bd3-8f83-d60a1665ff9c" />
![NetEv2NetEv](./NetEv2NetEv.svg)

* * * * * * * * * *

## Introduction

The function block `NetEv2NetEv` is used to manipulate network events (NetEv) within an ISOBUS-based system. Its primary purpose is to take an incoming network event record and overwrite a specific value—the network member handle. The block thus functions as a simple converter or adapter for ISONETEVENT_T data structures.

## Interface Structure

### **Event Inputs**

- **REQ**: This event triggers the processing of the function block. It is linked to the data inputs `IN` and `s16Handle`.

### **Event Outputs**

- **CNF**: This event signals the completion of processing. It is triggered after the processing of the `REQ` event and is linked to the (empty) data output that returns the manipulated `ISONETEVENT_T` structure.

### **Data Inputs**

- **IN** (`isobus::pgn::ISONETEVENT_T`): The input for the original network event data structure to be manipulated.
- **s16Handle** (`INT`): The new network member handle to be written to the passed `ISONETEVENT_T` structure. This value identifies the controller/function (CF) or user that serves as the source of the event.

### **Data Outputs**

- **`<leer>`** (`isobus::pgn::ISONETEVENT_T`): The output returns the manipulated `ISONETEVENT_T` data structure. The output name is empty, and the data type is identical to that of the input `IN`.

### **Adapters**

This function block does not use any adapters.

## Operation

The operation of the `NetEv2NetEv` block is deterministic and simple:

1. The function is executed when a `REQ` event occurs.
2. The entire contents of the input data structure `IN` are copied to the output data structure.



3. The entire contents of the input data structure `IN` are copied to the output data structure. 3. The field `.s16Handle` within this copied output structure is then overwritten with the value of the input `s16Handle`.
4. The `CNF` event is triggered to signal the output of the modified data set.

This block only modifies the specified handle field. All other fields of the `ISONETEVENT_T` structure remain unchanged.

## Technical Features

- **Data Type**: This block specifically works with the data type `isobus::pgn::ISONETEVENT_T`. The exact structure of this type is defined in the underlying `isobus::pgn` library.
- **Direct Assignment**: The implementation uses a direct assignment in Structured Text (ST). No additional logic, validation, or error handling is performed.
- **Naming Convention**: The data output has no explicit name, which is permitted in 4diac. It is referenced via the `CNF` event.

## State Overview

The function block has no internal state or memory. Its behavior is purely combinatorial: On every `REQ` event, the described operation is immediately performed, and a `CNF` event is generated.

## Application Scenarios

- **Handle Override in Event Streams**: In networks where events are forwarded between different controllers (CFs), the source handle (`s16Handle`) may need to be adjusted to correctly identify the current sender.
- **Event Proxy/Adapter**: This block can be used as a simple proxy to assign a new source identifier to incoming network events before forwarding them to downstream processing logic.
- **Testing and Simulation**: For simulating network events from various virtual sources (CFs) within a test setup.

## ⚖️ Comparison with Similar Blocks

- **E_SR (SR Flip-Flop) or E_D_FF (D Flip-Flop)**: These blocks have internal state (memory). `NetEv2NetEv` is stateless and only manipulates incoming data.
- **E_SELECT / E_MUX**: These blocks select between different data sources or pass them through. `NetEv2NetEv` actively modifies a portion of the incoming data.
- **E_R_TRIG / E_F_TRIG**: These are pure event triggers without data manipulation. `NetEv2NetEv` is a data processing block.
- **Generic ASSIGN Blocks**: A simple `ASSIGN` block copies an input value 1:1 to the output. `NetEv2NetEv` is a specialized `ASSIGN` block for the type `ISONETEVENT_T`, which performs a targeted modification (handle override).

## 🛠️ Related Exercises

- [Exercise_128](../../../../Uebungen/test_B/Uebungen_doc/Uebung_128.md)
- [Exercise_128b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_128b.md)
- [Exercise_134](../../../../Uebungen/test_B/Uebungen_doc/Uebung_134.md)

## Conclusion

The `NetEv2NetEv` function block is a specialized, lightweight tool for ISOBUS applications. It fulfills a clear and necessary niche task: overriding the source handle in network event records. Its simple, stateless implementation makes it robust and predictable. For developers working with ISOBUS PGNs and network events, it provides a useful tool for correctly identifying and customizing data flows.

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
