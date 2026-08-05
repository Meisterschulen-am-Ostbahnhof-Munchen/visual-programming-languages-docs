# AD_TO_AUS

![AD_TO_AUS](./AD_TO_AUS.svg)

* * * * * * * * * *
## Introduction
The **AD_TO_AUS** is a composite function block (FB) that converts a DWORD adapter (AD) into a USINT adapter (AUS). It serves as a unidirectional interface for converting a 32-bit data value into an 8-bit value. The block encapsulates the IEC 61131 conversion function `F_DWORD_TO_USINT` and provides the adapter interfaces, allowing it to be seamlessly integrated into an adapter-based communication structure.

## Interface Structure

### **Event Inputs**
The **E1** event is received via the adapter input **AD_IN**. It triggers the conversion of the incoming DWORD value.

### **Event Outputs**
The **E1** event is sent via the adapter output **AUS_OUT** as soon as the conversion is complete and the converted USINT value is available.

### **Data Inputs**
The adapter input **AD_IN** provides a DWORD value (32-bit) via the **D1** data line.

### **Data Outputs**
The adapter output **AUS_OUT** provides the converted USINT value (8-bit) via the **D1** data line.

### **Adapters**

| Adapter | Type | Direction | Description |

|---------|-----|----------|--------------|

| **AD_IN** | `adapter::types::unidirectional::AD` | Input (Socket) | Receives DWORD data and control events. |

| **AUS_OUT** | `adapter::types::unidirectional::AUS` | Output (Plug) | Outputs USINT data and acknowledgment events. |

## Functionality
1. The function block waits for an event at the adapter input **AD_IN** (signal **E1**).

2. Upon arrival of the event, the DWORD value present at **AD_IN.D1** is forwarded to the internal function block `F_DWORD_TO_USINT`, and its `REQ` input is activated.

3. The integrated conversion block performs the type conversion from DWORD to USINT (type conversion according to IEC 61131-3).

4. After the conversion is complete, the internal function block (FB) signals the event `CNF`, which is passed to the adapter output **AUS_OUT** (signal **E1**). Simultaneously, the converted USINT value is made available via **AUS_OUT.D1**.

## Technical Features

- **Adapter Coupling:** The FB has no direct event or data inputs/outputs, but communicates exclusively via adapter interfaces. This enables loose coupling in a modular control architecture.

- **Library Used:** The conversion is performed using the standardized function block `iec61131::conversion::F_DWORD_TO_USINT`. This ensures IEC 61131 compliance.

- **Package name:** `adapter::conversion::unidirectional` (see CompilerInfo) places the function block (FB) in a specific adapter conversion library.

## State Overview
The **AD_TO_OFF** is a pure function block without its own state machine. It operates strictly causally: Each input event leads to exactly one output event. The latency results from the execution time of the internal conversion block.

## Application Scenarios

- **Interface Adaptation:** If a sensor or actuator delivers data in DWORD format (32 bits), but the controller can only process USINT values (8 bits), the FB is used as an intermediary.

- **Adapter-based systems:** In a 4diac environment that relies on unidirectional adapters, the function block can be seamlessly integrated into data flow paths without changing the event/data structure of the surrounding components.

- **Data reduction:** Targeted truncation of higher-order bytes when only the lower-order part of a DWORD is relevant (e.g., for counters or simple analog values).

## Comparison with similar function blocks

- **AD_TO_AUS** is specific for the unidirectional conversion of a DWORD adapter to a USINT adapter. Alternatively, the IEC 61131 function `F_DWORD_TO_USINT` could be used directly, but then the adapter coupling would have to be performed manually.

Other adapter conversion blocks (e.g., `AD_TO_BYTE` or `AUS_TO_DWORD`) follow the same pattern but work with different data types. This function block fills the gap for the specific combination DWORD → USINT.

## Conclusion
The **AD_TO_AUS** is a simple yet useful composite function block for type conversion between two unidirectional adapter interfaces. It reduces implementation effort by encapsulating the standard conversion and enabling clean, event-driven adapter communication. Thanks to its clear structure, it is suitable for both rapid design and production use in IEC 61499-based controllers.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]