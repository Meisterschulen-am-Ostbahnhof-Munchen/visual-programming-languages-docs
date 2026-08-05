# STRUCT_MUX
<img width="1174" height="182" alt="STRUCT_MUX" src="https://github.com/user-attachments/assets/f133152d-9c9e-4f60-83b9-425cf3f873dd" />
* * * * * * * * * *
## Introduction
The function block (FB) `STRUCT_MUX` is a generic multiplexer for structured data types. It functions as the counterpart to `STRUCT_DEMUX` and is responsible for combining individual data values from multiple inputs into a single data structure at the output.
![STRUCT_MUX](STRUCT_MUX.svg)
## Interface Structure
The interface of the `STRUCT_MUX` function block is defined generically. The actual data inputs are only determined during the instantiation of the block.

### **Event Inputs**
- **REQ**: Triggers the execution of the function block. This causes the values at the inputs to be read and the output structure to be assembled.
- **With Data Variables**: All dynamically generated data inputs.

### **Event Outputs**
- **CNF**: Confirms the completion of the operation after the output structure has been successfully created.
- **With Data Variable**: `OUT`

### **Data Inputs**
The data inputs of this function block are not predefined. Instead, they are created **dynamically** based on the data type specified for the `OUT` output. For each member of the output structure, a corresponding data input with the same name and data type is created in the function block.

**Example:**

If the output `OUT` is set to the data type `MyStruct` with the members `a` (type `INT`) and `b` (type `BOOL`), the `STRUCT_MUX` block automatically creates two data inputs:

- `a` (type `INT`)
- `b` (type `BOOL`)

The image above illustrates this exact case.

- `a` (type `INT`)
- `b` (type `BOOL`)

The image above illustrates this exact case.

...
### **Data Outputs**

- **OUT** (Type: `ANY_STRUCT`): The output data structure, which is assembled from the values of the inputs.

## Functionality
As soon as a `REQ` event is received at the input of the `STRUCT_MUX` function block, the block reads the values from all its dynamically generated data inputs. These values are then combined into a single data structure. The resulting structure is made available at the `OUT` output. Immediately afterward, the `CNF` event is triggered to signal the completion of the process.

## Technical Features
- **Generic Block**: Thanks to the attribute `GEN_STRUCT_MUX`, the block can adapt to any structured data type (`ANY_STRUCT`).
- **Dynamic Interface**: The ability to generate its inputs based on the output data type makes it extremely flexible and reusable.
- **Service Interface Function Block Type**: The block is designed as a standardized interface for this service.

## State Overview
The `STRUCT_MUX` is a stateless block that operates according to a simple request-acknowledgment cycle:

1. **Ready**: Waits for a `REQ` event.

2. **Executing**: Reads the input values and assembles the output structure.

3. **Completed**: Provides the structure at the `OUT` output, triggers the `CNF` event, and returns to standby mode.

## Application Scenarios
- **Data Consolidation**: Bundles individual signals (e.g., configuration parameters, control values) into a single structure for further processing or communication.
- **Improved Clarity**: Combines many individual data lines into a single structured line to reduce the complexity of graphical representations.
- **Interface Adaptation**: Adapts individual data values to a function block that expects a single data structure as an input.

## ⚖️ Comparison with Similar Function Blocks
- **`STRUCT_DEMUX`**: The complementary function block that splits a single data structure into its individual members.
- **`SET_STRUCT_VALUE`**: While `SET_STRUCT_VALUE` dynamically modifies a single value within an existing structure, `STRUCT_MUX` creates a completely new structure from individual values.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2020 Johannes Kepler University Linz |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac Package | eclipse4diac::convert |

## 🛠️ Related Exercises
* [Exercise_051](../../../Uebungen/test_B/Uebungen_doc/Uebung_051.md)]
* [Exercise_052](../../../Uebungen/test_B/Uebungen_doc/Uebung_052.md)]
* [Exercise_121](../../../Uebungen/test_B/Uebungen_doc/Uebung_121.md)]
* [Exercise_126b2_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_126b2_sub.md)]
* [Exercise_126b_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_126b_sub.md)]

## Conclusion

STRUCT_MUX` is a fundamental and very practical building block for working with data structures in 4diac. Its ability to generate any structure from individual values simplifies application logic and promotes clean, structured data management. It is the standard tool for bundling data and generating structured information.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
