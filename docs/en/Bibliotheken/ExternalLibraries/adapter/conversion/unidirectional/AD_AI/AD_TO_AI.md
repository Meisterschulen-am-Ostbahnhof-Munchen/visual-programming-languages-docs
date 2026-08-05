# AD_TO_AI
![AD_TO_AI](./AD_TO_AI.svg)
* * * * * * * * * *
## Introduction
The function block **AD_TO_AI** acts as a converter between two different adapter interfaces: It converts an **AD adapter (DWORD)** into an **AI adapter (INT)**. The block is implemented as a composite function block and internally uses the IEC 61131-3 function `F_DWORD_TO_INT` to perform the actual type conversion. The goal is to facilitate the integration of components based on different data types while ensuring event-driven data transfer within the 4diac IDE.
## Interface Structure

### **Event Inputs**
The function block does not have direct event inputs at the top level. Event control is handled via the connected adapters:

- **AD_IN.E1** (Socket adapter event) – triggers the conversion.

### **Event Outputs**
These are also provided exclusively via the adapters:

- **AI_OUT.E1** (Plug adapter event) – signals the completion of the converted data.

### **Data Inputs**
- **AD_IN.D1** (DWORD) – The original data value supplied by the AD adapter.

### **Data Outputs**
- **AI_OUT.D1** (INT) – The converted value output via the AI adapter.

### **Adapters**

| Adapter Type | Direction | Type | Description |

|-----------|----------|-----|--------------|

| Socket | Input | `adapter::types::unidirectional::AD` | Receives a DWORD value (via event E1 and data D1). |

| Plug | Output | `adapter::types::unidirectional::AI` | Provides the converted INT value (event E1, data D1). |

## Functionality

The function block operates in an event-driven manner:

1. An event at socket **AD_IN.E1** triggers the internal instance `Convert` (type `F_DWORD_TO_INT`) via its event input **REQ**.

``` 2. Simultaneously, the data value **AD_IN.D1** (DWORD) is passed to the data input **IN** of `Convert`.

3. The function `F_DWORD_TO_INT` performs the type conversion from DWORD to INT.

4. After the calculation is complete, `Convert` sends an event at its output **CNF**, which is connected to the plug event **AI_OUT.E1**.

5. In parallel, the converted INT value is forwarded from the output **OUT** of `Convert` to the data output **AI_OUT.D1**.

Thus, after each incoming event at the socket, a converted data value is automatically made available on the plug.

4. After the calculation is complete, `Convert` sends an event at its output **CNF**, which is connected to the plug event **AI_OUT.E1**.

5.
## Technical Features

- **Composition:** The FB is a pure composite function block – it contains no internal logic but delegates the conversion to the standard function block `F_DWORD_TO_INT` from the IEC 61131 library.
- **Data Types:** DWORD is a 32-bit value, while INT is a 16-bit signed integer. Data loss can occur during conversion if the DWORD value is outside the INT range (−32768 … 32767) or does not fit within this range. The user must take this into account when using the function block.
- **Adapter Coupling:** The connection between the socket and the plug is established exclusively via the internal event and data flows. The adapters themselves are of type `unidirectional`, i.e., They only transfer data in one direction.
- **Package Structure:** The function block is provided in package `adapter::conversion::unidirectional` and imports the conversion function from `iec61131::conversion`.

## State Overview

Since this is a composite function block without its own state machine, there are no explicit states. The function block behaves like a transparent converter:

- **Idle:** Waits for an event at the socket.
- **Processing:** After receiving an event, the conversion is started; no other events are active during this phase.
- **Done:** After the conversion, the output event is displayed; the function block returns to the idle state.

The internal function block `F_DWORD_TO_INT` has its own system-defined state logic, which is not visible due to its encapsulation within the composite function block.

## Application Scenarios
- **Integration of Different Adapter Types:** A sensor delivers data as DWORD via an AD adapter, but downstream logic expects INT values via an AI adapter. The function block handles the type conversion seamlessly.
- **Heterogeneous System Architectures:** In systems where different components use different data types, `AD_TO_AI` enables simple and standardized connectivity.
- **Prototyping and Migration:** When switching from DWORD-based data processing to INT-based components, the function block can be used as a temporary or permanent converter.

## Comparison with Similar Function Blocks

Other converter function blocks exist, such as `AD_TO_AI`, `AI_TO_AD`, `INT_TO_DWORD`, etc. This function block focuses specifically on the adapter level and operates entirely event-driven. Unlike simple data conversion function blocks (e.g., `F_DWORD_TO_INT`), it offers a pre-built adapter interface that enables direct coupling to adapter-oriented architectures without requiring the manual drawing of additional connections.

Other similar composite function blocks differ primarily in the direction (e.g., `AI_TO_AD` for reverse conversion) or in the data types used.

## Conclusion

The composite function block **AD_TO_AI** is a useful tool for type conversion between DWORD and INT adapters. It encapsulates the conversion logic in a clean, event-driven interface, thus facilitating reusability and integration into existing 4diac projects. Its simple structure and the use of a proven standard function block make it reliable and easy to understand. However, users should always keep the limitations of the INT data type in mind to avoid unintentional data loss.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
