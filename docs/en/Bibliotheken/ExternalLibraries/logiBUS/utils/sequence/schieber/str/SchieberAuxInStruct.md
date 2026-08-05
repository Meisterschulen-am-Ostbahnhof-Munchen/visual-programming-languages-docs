# SliderAuxInStruct
* * * * * * * * * *
## Introduction
The structured data type `SchieberAuxInStruct` is used to bundle information for the visual representation of an auxiliary element (AUX) in a slider control. It combines the specification of an image with a background color to define the graphical representation of an auxiliary input or element.
## Interface Structure
This function block is a structured data type (struct) and therefore has no event or adapter interfaces. Its structure consists of the following two data elements:
### **Data Inputs**
Since it is a data type, there are no direct inputs. The structure is used as a whole at the data inputs of other function blocks.

### **Data Outputs**
Since it is a data type, there are no direct outputs. The structure is used as a whole at the data outputs of other function blocks.

### **Structured Elements**
* **`Picture`** (`logiBUS::utils::sequence::schieber::SchieberStruct`):
* **Comment:** `u16ObjId for Picture`
* **Description:** Contains the identifier (Object ID) for the image to be displayed in the helper element. The underlying type `SchieberStruct` likely provides the necessary information for referencing and handling the image object.
* **`u8Colour`** (`logiBUS::utils::sequence::schieber::SchieberColorStruct`):
* **Comment:** `Background Color of the AUX`
* **Description:** Defines the background color of the helper element. The type ``SchieberColorStruct`` specifies the color used, likely in a format suitable for the target system (e.g., an HMI).

## Functionality

The data type ``SchieberAuxInStruct`` is a passive data structure. Its sole function is to logically combine the two properties ``Picture`` (image) and ``u8Colour`` (background color) into a single, reusable data record. It is used to transport these visual attributes consistently between different functional blocks within an application.

## Technical Details
* **Namespaces:** The data type and its components are defined in the package ``logiBUS::utils::sequence::schieber``, indicating a specific application in agricultural machinery control technology.
* **Typing:** Using specific, user-defined types (`SchieberStruct`, `SchieberColorStruct`) for members promotes type safety and reusability throughout the project.

## State Overview
As a pure data type, `SchieberAuxInStruct` has no internal state or state machine.

## Application Scenarios
This data type is typically used in PLC (Programmable Logic Controller) controllers for mobile machinery, particularly in:

* **HMI Configuration:** To define the appearance of operating or display elements (e.g., sliders, buttons, status lights) on an operator panel.
* **Sequence Controls:** Within sequential control systems where the display of an element (color, image) should change depending on the process state.
* **Data Encapsulation:** Simplifies the parameterization of function blocks that control the appearance of an "AUX" element by allowing all visual parameters to be passed in a single variable.

## ⚖️ Comparison with Similar Building Blocks
Unlike function blocks (FBs), this building block has no algorithm or behavioral logic. It is comparable to a `STRUCT` in IEC 61131-3 or a `class`/`struct` in higher-level programming languages. Other similar elements would be simple data types (e.g., `ARRAY` of single values), but these do not offer the semantic grouping and type safety of this structured type.

``` ## Conclusion

The ``SchieberAuxInStruct`` is a fundamental, reusable data type for modeling the visual properties of a helper element in a specific control environment. By encapsulating image and color information, it contributes to better structuring, readability, and maintainability of the application code. Its use is particularly advantageous in projects with complex user interfaces or state-dependent visualizations.