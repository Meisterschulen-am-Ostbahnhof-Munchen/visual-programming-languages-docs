# F_DINT_TO_DWORD

<img width="1449" height="212" alt="F_DINT_TO_DWORD" src="https://github.com/user-attachments/assets/bc0e5b81-4008-459d-832e-c81048024cbc" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_TO_DWORD` converts a 32-bit integer value (DINT) into a 32-bit unsigned value (DWORD). This conversion is particularly necessary when signed values need to be converted to unsigned values, for example, for further processing in certain control algorithms or for communication with other systems.
![F_DINT_TO_DWORD](F_DINT_TO_DWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the input value `IN` from DINT to DWORD.

### **Event Outputs**

- **CNF**: Signals successful completion of the conversion and provides the converted value `OUT`.

### **Data Inputs**

- **IN** (DINT): The signed 32-bit input value to be converted.

### **Data Outputs**

- **OUT** (DWORD): The unsigned 32-bit output value after the conversion.

### **Adapters**

- No adapters are available.

## Functionality

This function block performs the DINT to DWORD conversion when the event `REQ` is triggered. The value of input `IN` is converted using the function `DINT_TO_DWORD` and made available at output `OUT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features

- The conversion is performed directly and without any additional delay.
- The function block is optimized for use in real-time control systems.

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Conversion State**: Performs the conversion and sets the output `OUT`.
3. **Acknowledgement State**: Triggers the `CNF` event and returns to the idle state.

## Application Scenarios

- Conversion of signed sensor data to unsigned values for further processing.
- Preparation of data for communication with systems that expect unsigned values.

## ⚖️ Comparison with Similar Blocks

- Unlike generic conversion blocks, `F_DINT_TO_DWORD` specializes in DINT to DWORD conversion and therefore offers optimized and error-free conversion for this specific use case.

## Conclusion

The `F_DINT_TO_DWORD` function block is an efficient and reliable tool for converting signed to unsigned 32-bit values. Its ease of use and direct integration into the 4diac IDE make it an ideal solution for relevant applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]