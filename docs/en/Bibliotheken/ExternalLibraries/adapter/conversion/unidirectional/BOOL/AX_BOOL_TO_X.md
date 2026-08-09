# AX_BOOL_TO_X

<img width="1151" height="231" alt="image" src="https://github.com/user-attachments/assets/d7e1acea-074c-48d3-afa2-37176d3d2d1f" />
* * * * * * * * * *
## Introduction

The AX_BOOL_TO_X function block is a composite function block used to convert a BOOL value into the AX adapter format. It enables the easy conversion of Boolean values into a standardized output format for further processing in automation systems.
![AX_BOOL_TO_X](AX_BOOL_TO_X.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: BOOL input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapters**

- **AX_OUT**: Unidirectional AX adapter output for the converted data

## Functionality

The function block receives a Boolean value at the OUT data input and converts it to the AX adapter format upon arrival of the REQ event. The conversion is automatic, and the converted value is output via the AX_OUT adapter. The block acts as a bridge between simple Boolean signals and the standardized AX communication format.

## Technical Features

- Composite function block with internal networking
- Uses a unidirectional AX adapter for output
- Automatic forwarding of events and data to the adapter
- Simple and direct signal conversion without additional logic

## State Overview

The function block has a simple state machine:

1. **Wait state**: Waits for a REQ event
2. **Process state**: Upon a REQ event, the BOOL value is converted and output via the adapter
3. Returns to wait state after conversion is complete

## Application Scenarios

- Integration of simple switching states into more complex AX-based systems
- Interface adaptation between different automation components
- Protocol conversion in distributed control systems
- Integration of basic sensors into AX-compliant architectures

## ⚖️ Comparison with Similar Blocks

Compared to other conversion blocks, AX_BOOL_TO_X stands out due to its specific focus on the AX adapter format. While general conversion blocks often support multiple output formats, this block offers an optimized solution for the specific AX interface.

## 🛠️ Related Exercises

* [Exercise_001_AX_b](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_001_AX_b.md)]
* [Exercise_002a2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a2_AX.md)]
* [Exercise_004b_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX.md)]
* [Exercise_004b_AX_ASR](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR.md)]
* [Exercise_004b_AX_ASR_X](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR_X.md)]

## Conclusion

AX_BOOL_TO_X is a specialized conversion block that provides a simple and efficient interface between Boolean signals and the AX adapter format. Its clear structure and direct functionality make it a reliable solution for integration tasks in automation systems.