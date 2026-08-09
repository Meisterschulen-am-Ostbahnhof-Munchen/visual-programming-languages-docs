# F_LOG

![F_LOG](https://user-images.githubusercontent.com/116869307/214145111-55825954-a2a0-4f08-91b0-7e3e30337b48.png)

* * * * * * * * * *
## Introduction

The F_LOG function block calculates the base-10 logarithm (decimal logarithm) of a numeric input value. It belongs to the category of standard functions for a numeric variable according to IEC 61131-3 and is part of the package `iec61131::numerical`.
![F_LOG](F_LOG.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service request - triggers the calculation of the logarithm

### **Event Outputs**

- **CNF**: Confirmation of the requested service - signals the completion of the calculation

### **Data Inputs**

- **IN**: Numeric input value of type ANY_REAL for which the logarithm is to be calculated

### **Data Outputs**

- **OUT**: Calculated logarithm value of type ANY_REAL

### **Adapters**

No adapter interfaces are available.

## Functionality

Upon arrival of a REQ event, the F_LOG block calculates the base-10 logarithm (log₁₀) of the current IN value. The result is output at the OUT output, and simultaneously a CNF event is generated to signal successful computation.

## Technical Features

- Supports the ANY_REAL data type, enabling various numeric data types such as REAL, LREAL, etc.
- Complies with the IEC 61131-3 standard specification
- Simple and deterministic operation without internal states

## State Overview

The function block has no complex internal states. It behaves purely functionally: REQ event → computation → CNF event.

## Application Scenarios

- Scientific calculations and measurement data processing
- Signal processing in automation technology
- Scaling of measured values in logarithmic representations
- Audio and acoustics applications (e.g., dB calculations)

## ⚖️ Comparison with similar blocks

Compared to other logarithmic functions:

- F_LN: Calculates the natural logarithm (base e)
- F_LOG: Specifically calculates the base-10 logarithm
- Both blocks follow the same event/data flow paradigm

## Conclusion

The F_LOG function block offers a standardized, reliable implementation for calculating the base-10 logarithm in 4diac control systems. Its simple interface and deterministic operation make it ideal for use in real-time automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
