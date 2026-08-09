# Funk_IXA

<img width="1725" height="316" alt="image" src="https://github.com/user-attachments/assets/18811a6e-8efc-454f-b9ec-ea728163a624" />
* * * * * * * * * *
## Introduction

The **Funk_IXA** function block is a composite function block for processing Boolean input data. It serves as an interface for digital inputs and enables the initialization and querying of input signals via a standardized interface.
![Funk_IXA](Funk_IXA.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization (with QI, PARAMS, Input)
- **REQ**: Service Request (with QI)

### **Event Outputs**

- **INITO**: Initialization Acknowledgement (with QO, STATUS)

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL)
- **PARAMS**: Service Parameters (STRING)
- **Input**: Digital Input Identification (Funk_DI_S, Initial Value: Invalid)

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL)
- **STATUS**: Service Status (STRING)

### **Adapters**

- **IN**: Unidirectional Adapter Type AX

## Functionality

The The Funk_IXA block acts as a wrapper for the underlying Funk_IX block. During INIT initialization, the parameters QI, PARAMS, and Input are passed to the internal IX block. The REQ request triggers a query of the current input state. The IN adapter enables communication with external systems.

Funk_IXA acts as a wrapper for the underlying Funk_IX block.
## Technical Features

- Uses the specific data type Funk_DI_S to identify digital inputs
- Implements invalid initialization for the input parameter
- Supports string-based parameter passing for flexible configuration
- Provides status feedback via the STATUS output

## State Overview

The block goes through the following states:

1. **Not Initialized**: Before INIT call
2. **Initialized**: After successful INIT processing
3. **Ready**: Can process REQ requests
4. **Active**: During REQ processing

## Application Scenarios

- Connecting digital inputs in automation systems
- Integration into distributed control systems
- Use in agricultural machinery controls
- Interface for sensor data acquisition

## ⚖️ Comparison with Similar Blocks

Compared to simple digital input blocks, Funk_IXA offers:

- Extended parameterization options
- Status feedback
- Adapter interface for extended communication
- Typed Input Identification

## 🛠️ Related Exercises

* [Exercise_003b2_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003b2_sub_AX.md)
* [Exercise_003b3_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003b3_sub_AX.md)

## Conclusion

The Funk_IXA function block represents a robust and flexible solution for processing digital input signals. Its composite structure and the use of standardized interfaces make it particularly suitable for complex automation applications that require reliable data acquisition and status monitoring.
