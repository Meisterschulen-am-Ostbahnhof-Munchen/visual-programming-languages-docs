# AR_TO_AI
![AR_TO_AI](./AR_TO_AI.svg)
* * * * * * * * * *
## Introduction
The **AR_TO_AI** function block is a composite module that converts a unidirectional AR adapter (input with data type REAL) into a unidirectional AI adapter (output with data type INT). It is used for numerical type conversion within 4diac networks and encapsulates an IEC 61131 conversion module.
## Interface Structure
### **Event Inputs**
The event input is provided via the **AR_IN** socket. The **AR_IN.E1** event triggers the conversion.

### **Event Outputs**
The event output is provided via the **AI_OUT** plug. After successful conversion, the event **AI_OUT.E1** is sent.

### **Data Inputs**
The data input is provided via the socket **AR_IN**. The input value **AR_IN.D1** is of type REAL.

### **Data Outputs**
The data output is provided via the plug **AI_OUT**. The output value **AI_OUT.D1** is of type INT.

### **Adapters**

| Label | Direction | Type | Remark |

|-------------|----------|-----|-----------|

| AR_IN | Input | `adapter::types::unidirectional::AR` | REAL Adapter (Input) |

| AI_OUT | Output | `adapter::types::unidirectional::AI` | INT Adapter (Output) |

## Functionality
The function block (FB) is implemented as a composite and contains a single **F_REAL_TO_INT** block from the IEC 61131 library (`iec61131::conversion::F_REAL_TO_INT`).

As soon as an event arrives at socket **AR_IN.E1**, the value of **AR_IN.D1** (REAL) is passed to the input `IN` of the converter, and its processing is started (`REQ`). After the conversion is complete, the converter signals via `CNF` that the result is available at output `OUT` (INT). This result is immediately forwarded to the plug output **AI_OUT.D1** (INT), and the event **AI_OUT.E1** is triggered.

## Technical Features
- The function block (FB) is fully event-driven; it does not have its own state machine.
- Conversion is performed according to the IEC 61131 standard: REAL is mapped to INT (decimal places are truncated, corresponding to a type conversion).
- The function block is located in the package `adapter::conversion::unidirectional`, which allows for clear separation from other conversion function blocks.
- The use of adapters improves encapsulation and reusability in 4diac projects.

## State Overview
The **AR_TO_AI** function block does not have an internal state machine. Its operation is purely combinatorial and depends on the incoming event:

- **Waiting:** No event is pending at AR_IN.E1.
- **Converting:** Upon an event, the REAL value is converted immediately, and the result is output as an INT.

## Application Scenarios
- **Sensor Connection:** Real-value sensors (e.g., analog voltage measurement) deliver REAL data via an AR adapter; downstream logic requires INT values (e.g., for counters or index calculations).
- **Protocol Conversion:** When a subsystem sends data in REAL format, but the target system only accepts INT data (e.g., with fieldbus gateways).
- **Test and Simulation Environments:** For easy conversion between REAL and INT adapters in test setups.

## Comparison with Similar Function Blocks
- **AI_TO_AR:** Performs the reverse conversion (INT → REAL).
- **F_REAL_TO_INT (Direct):** The encapsulated basic function block is designed for point-to-point connections without an adapter. The AR_TO_AI offers an adapter-based interface that can be better integrated into adapter-oriented networks.
- **Custom Composite Blocks:** Other projects could create similar adapter conversions for other data types (e.g., LREAL, DINT).

## Conclusion
The **AR_TO_AI** is a compact, adapter-based conversion block that enables the conversion of REAL to INT data in event-driven 4diac networks. By encapsulating the standard block `F_REAL_TO_INT` in an adapter interface, integration into existing adapter socket architectures is simplified, and the overall system readability is improved.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]