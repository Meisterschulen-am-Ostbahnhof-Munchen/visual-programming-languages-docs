# RT_Bridge_1

* * * * * * * * * *
## Introduction

The RT_Bridge_1 function block serves as a decoupling bridge for a data connection between real-time event chains. It enables secure data exchange between different execution contexts.
## Interface Structure

### **Event Inputs**

- **RD**: Read data from the bridge.
- **WR**: Write data to the bridge.

### **Event Outputs**

- **RDO**: Notification of read data.

### **Data Inputs**

- **SD_1** (ANY): Data to be written to the bridge.

### **Data Outputs**

- **RD_1** (ANY): Data read from the bridge.

## Functionality

The module temporarily stores the data received via `WR` and makes it available at the output at `RD`. This decouples the write and read processes in terms of timing.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2023 Johannes Kepler University Linz |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac Package | eclipse4diac::rtevents |

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
