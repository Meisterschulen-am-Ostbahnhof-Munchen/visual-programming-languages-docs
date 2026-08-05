# AE_MUX_2
![AE_MUX_2](./AE_MUX_2.svg)

* * * * * * * * * *
## Introduction
The **AE_MUX_2** is a generic multiplexer function block for analog value adapters (AEs). It selects one of two analog signal inputs based on an index input and routes it to the output. The block is built according to the IEC 61499-2 standard and is suitable for flexible signal switching in distributed automation systems.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|---------------|
| REQ | Event | Controls the updating of the index `K` and the switching of the output |

### **Event Outputs**

| Name | Type | Description |
|------|-----|--------------|
| CNF | Event | Acknowledgement after successful output switching |

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| K | UINT | Index for selecting the input (0 → IN1, 1 → IN2) |

### **Data Outputs**

None

### **Adapters**

| Function | Name | Type | Description |
|----------|------|-----|--------------|
| Socket | IN1 | adapter::types::unidirectional::AE | First analog input (for K = 0) |
| Socket | IN2 | adapter::types::unidirectional::AE | Second analog input (for K = 1) |
| Plug | OUT | adapter::types::unidirectional::AE | Analog output (corresponds to IN1 or IN2) |

## Functionality

The module operates as a 2-to-1 multiplexer at the adapter level. As soon as a **REQ** event arrives, the current value of index `K` is evaluated:

- If `K = 0`, adapter **IN1** is switched to output **OUT**.
- If `K = 1`, adapter **IN2** is switched to output **OUT**.

After successful switching, the **CNF** event is output. The function block is event-driven and only performs a switchover on a rising edge at **REQ**.

## Technical Features
- **Generic Class**: The function block is marked as a generic function block by the attribute `GenericClassName = 'GEN_AE_MUX'`, enabling reuse with different adapter types.
- **Standard Compliance**: Full implementation according to IEC 61499-2, including metadata for identification and versioning.
- **Restricted Index Range**: The index `K` is declared as `UINT`, but the logic only implements the values 0 and 1; other values lead to undefined behavior (depending on the specific implementation).
- **Unidirectional Adapters**: The adapters used are defined as unidirectional (`unidirectional`), meaning... The data flows in only one direction.

## State Overview

The function block does not have an explicit state machine. Operation is purely combinatorial: Each **REQ** event triggers an immediate evaluation of `K` and the corresponding switching.

## Application Scenarios
- **Switching between two analog sensors** – e.g., selecting a temperature sensor from two measuring points.
- **Redundant signal paths** – if one input fails, the system can switch to the second.
- **Testing & Commissioning** – manual switching between a real and a simulated analog value.
- **Flexible Parameterization** – the index `K` can be dynamically set by a higher-level controller.

## Comparison with Similar Function Blocks

| Feature | AE_MUX_2 | Standard IEC 61131 MUX | SE_MUX (for Boolean signals) |
|---------|----------|------------------------|--------------------------------|
| **Data Type** | Analog Value (Adapter) | Simple Data Types | Boolean Values |
| **Number of Inputs** | 2 | Multiple (configurable) | 2 |
| **Interface** | Adapter | Data Inputs/Outputs | Event/Data Inputs/Outputs |
| **Event Control** | Yes (REQ/CNF) | No (Cyclic) | Yes |

The AE_MUX_2 is specifically optimized for use with analog value adapters and integrates seamlessly into the event-driven 4diac IDE environment.

## Conclusion

The **AE_MUX_2** offers a compact and standards-compliant solution for selecting one of two analog adapter signals. Thanks to its generic nature, it can be used in various automation projects where flexible and elegant signal switching at the adapter level is required.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
