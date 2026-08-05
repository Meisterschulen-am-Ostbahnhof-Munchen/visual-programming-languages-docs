# FB_CTU_DINT
<img width="1396" height="277" alt="" src="https://github.com/user-attachments/assets/36c696fb-4dfc-457a-bd17-1842876fa432" />
* * * * * * * * * *
## Introduction
The FB_CTU_DINT is an up counter for the DINT data type (32-bit count). It increments with each count pulse and can be reset to a predefined value. This function block is particularly suitable for applications requiring large count ranges.
* ![FB_CTU_DINT](FB_CTU_DINT.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request (triggers the counting process)

### **Event Outputs**
- **CNF**: Execution confirmation (triggered after completion of the counting process)

### **Data Inputs**
- **CU** (BOOL): Count input (increments the counter when TRUE)
- **R** (BOOL): Reset input (sets the counter value to 0 when TRUE)
- **PV** (DINT): Preset value (defines the comparison value for the Q output)

### **Data Outputs**
- **Q** (BOOL): Status output (becomes TRUE if CV ≥ PV)
- **CV** (DINT): Current counter value (Count Value)

### **Adapters**
No adapters available.

## Functionality
The FB_CTU_DINT operates according to the following rules:

1. When reset is active (R=TRUE), the counter value (CV) is reset to 0.

2. When the counter input is active (CU=TRUE) and reset is inactive, the counter value is incremented by 1 (up to the maximum value of 2147483647).

3. The output Q is set to TRUE as soon as the counter value (CV) reaches or exceeds the preset value (PV).

## Technical Features
- Uses 32-bit integers (DINT) for counter values
- Maximum counter value: 2147483647
- Implemented as a simple function block (SimpleFB)
- Supports the IEC 61131-3 standard

## State Overview
The function block does not have an internal state machine. The logic is executed on each REQ event.

## Application Scenarios
- Production counting in manufacturing plants
- Event counting in process control systems
- Cycle time monitoring
- General counting tasks in automation technology

## ⚖️ Comparison with similar function blocks
- Compared to FB_CTU_INT, FB_CTU_DINT offers a larger counting range (32-bit vs. 16-bit)
- Compared to FB_CTU_LINT, FB_CTU_DINT has a smaller value range but lower memory requirements
- Similar to IEC 61131-3 CTU function blocks, but implemented in the 4diac IDE

## Conclusion
The FB_CTU_DINT is a robust and easy-to-use increment counter for applications with medium to large counting ranges. Its clear interface and simple functionality make it particularly suitable for standard counting tasks in automation technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
