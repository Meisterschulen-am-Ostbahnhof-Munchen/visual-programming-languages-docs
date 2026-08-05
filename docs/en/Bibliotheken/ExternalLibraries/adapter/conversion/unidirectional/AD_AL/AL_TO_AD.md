# AL_TO_AD
![AL_TO_AD](./AL_TO_AD.svg)
* * * * * * * * * *
## Introduction
The **AL_TO_AD** function block is a composite function block that converts a unidirectional LWORD adapter (AL) into a unidirectional DWORD adapter (AD). It enables data conversion between two different adapter types within the 4diac IDE, based on the IEC 61499 standard.
## Interface Structure
### **Event Inputs**
- None (the FB has no dedicated event inputs; event control is handled via the AL_IN socket)

### **Event Outputs**
- None (the FB has no dedicated event outputs; event forwarding is handled via the AD_OUT plug)

### **Data Inputs**
- None (data is provided exclusively via the AL_IN socket)

### **Data Outputs**
- None (data is output exclusively via the AD_OUT plug)

### **Adapter**

| Type | Name | Direction | Description |

|------|------|----------|--------------|

| Socket | AL_IN | Input | Unidirectional LWORD adapter with one event input (`E1`) and one data input (`D1` of type `LWORD`) |

| Plug | AD_OUT | Output | Unidirectional DWORD adapter with one event output (`E1`) and one data output (`D1` of type `DWORD`) |

## Functionality
The function block receives an LWORD data word (`D1`) along with an event (`E1`) via the **AL_IN** socket. The event iterates through the internal function block **F_LWORD_TO_DWORD**, which performs the conversion according to the IEC 61131 standard. After successful conversion, the result is output as a DWORD (`AD_OUT.D1`) via the plug, accompanied by an event (`AD_OUT.E1`).

The event then passes through the internal function block **F_LWORD_TO_DWORD**, which performs the conversion according to the IEC 61131 standard. The internal network structure consists of:

- A **F_LWORD_TO_DWORD** block (from the library `iec61131::conversion`)
- Event connection: `AL_IN.E1` → `Convert.REQ` / `Convert.CNF` → `AD_OUT.E1`
- Data connection: `AL_IN.D1` → `Convert.IN` / `Convert.OUT` → `AD_OUT.D1`

## Technical Features
- **Standard Compliance**: The conversion is performed using the IEC 61131-compliant FB `F_LWORD_TO_DWORD`, which enables lossless conversion from 64-bit to 32-bit (low-order 32-bit) support.
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional, reducing complexity and ensuring a clearly defined data flow direction.
- **Event-driven Communication**: Conversion is triggered by an event at the input adapter; the result is also passed on in an event-driven manner.
- **Embedded in Composite Function Blocks**: By encapsulating the function block as a composite block, the function block can be easily integrated into larger networks.

## State Overview
The **AL_TO_AD** function block does not have its own state machine, as it is implemented as a composite function block. The state logic is fully implemented by the internal **F_LWORD_TO_DWORD** function block:

1. **Wait** – No event is present at the input.

2. **Convert** – After receiving an event, the conversion of the LWORD data is performed (one clock cycle).

3. **Output** – The DWORD result and an acknowledgment event are provided at the output adapter.

## Application Scenarios
- **System Integration** – When a component (e.g., a PLC) provides LWORD data, but a downstream module expects DWORD data.
- **Adapter Bridge** – In heterogeneous networks where devices use different data types for the same physical value.
- **Data Preparation** – Preprocessing of 64-bit values that are to be further processed on a 32-bit basis (e.g., for measured values or counters).

## Comparison with Similar Function Blocks
- **WORD_TO_DWORD** – Converts 16-bit words to 32-bit double words, but on simple data types, not on adapters.
- **Direct Adapter Coupling** – Without conversion, both systems would have to use the same adapter type (either AL or AD), which is often not the case.
- **F_LWORD_TO_DWORD (Isolated)** – This function block operates only at the data layer; the adapter connection must be established separately. **AL_TO_AD** simplifies handling by encapsulating the adapter logic and conversion.

## Conclusion
The **AL_TO_AD** function block provides a lean and standards-compliant solution for converting LWORD to DWORD adapter data. Combining adapter and conversion logic in a single composite function block increases reusability and simplifies network creation. It is particularly well-suited for integrating various IEC 61499 components and contributes to the modularity of industrial automation solutions.

**AL_TO_AD** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
