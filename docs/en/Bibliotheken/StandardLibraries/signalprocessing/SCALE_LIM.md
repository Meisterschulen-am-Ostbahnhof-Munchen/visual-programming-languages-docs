# SCALE_LIM

<img width="951" height="257" alt="SCALE_LIM" src="https://github.com/user-attachments/assets/9cc71e27-9ab8-454a-a6fc-01b86dfde68e" />
* * * * * * * * * *
## Introduction

The SCALE_LIM function block is a scaling module with additional limiting functions. It enables the linear scaling of an input value within a defined range and also offers the option of fixing output values when certain input limits are exceeded.
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the scaling operation. It is linked to all data inputs.

### **Event Outputs**

- **CNF**: Signals the completion of the scaling operation.

### **Data Inputs**

- **IN** (REAL): Input value to be scaled
- **MAX_IN** (REAL): Maximum input value for scaling
- **MIN_IN** (REAL): Minimum input value for scaling
- **MAX_IN_LIM** (REAL): Upper input limit, above which MAX_OUT_FIX is output
- **MIN_IN_LIM** (REAL): Lower input limit, below which MIN_OUT_FIX is output
- **MAX_OUT** (REAL): Maximum output value for scaling
- **MIN_OUT** (REAL): Minimum output value for scaling
- **MAX_OUT_FIX** (REAL): Fixed output value if MAX_IN_LIM is exceeded
- **MIN_OUT_FIX** (REAL): Fixed output value if MIN_IN_LIM is not reached

### **Data Outputs**

- (REAL): Scaled output value

### **Adapters**

No adapters available.

## Functionality

The function block performs the following operations:

1. Checks whether the input value IN exceeds the defined limits MIN_IN_LIM or MAX_IN_LIM
2. If IN exceeds MAX_IN_LIM: Outputs MAX_OUT_FIX
4. In normal operating range: Linear scaling of the input value according to the formula:

(IN - MIN_IN) * (MAX_OUT - MIN_OUT) / (MAX_IN - MIN_IN) + MIN_OUT
## Technical Features

- Implemented in Structured Text (ST)
- Supports both scaling and limiting
- Part of the `eclipse4diac::signalprocessing` package

## State Overview

The function block (FB) has a simple state machine:

1. Waits for a REQ event
2. Performs scaling/limiting
3. Sends a CNF event

## Application Scenarios

- Signal processing in control systems
- Scaling of sensor values with limit monitoring
- Process control with defined operating ranges

## ⚖️ Comparison with Similar Function Blocks

Compared to simple scaling function blocks, SCALE_LIM additionally offers:

- Limit monitoring
- Option to output fixed values when a limit is exceeded
- More flexible definition of scaling ranges

## 🛠️ Related Exercises

* [Exercise_043](../../../Uebungen/test_B/Uebungen_doc/Uebung_043.md)

## Conclusion

SCALE_LIM is a versatile function block for applications that require both scaling and limiting values. Its additional limit functions make it particularly suitable for safety-critical applications where defined responses to limit violations are necessary.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
