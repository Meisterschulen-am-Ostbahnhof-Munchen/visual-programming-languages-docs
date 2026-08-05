# SliderColorStruct
* * * * * * * * * *
## Introduction
The data type `SchieberColorStruct` is a structured data structure used to manage color values for different states of a slider (e.g., a valve, flap, or closure). It defines a consistent color coding for the visual representation of the states `Unbekannt`, `Geschlossen`, `Öffnend`, `Geöffnet`, and `Schließend` in a user interface or display.
## Interface Structure
The data type is a structure (`STRUCT`) and does not contain any events or adapters. Its interface consists exclusively of data elements.
### **Data Inputs**

This structure does not have event inputs in the conventional sense, as it is a data type. The following elements are the structure's member variables, which can be written to or assigned values during instantiation.

### **Data Outputs**

This structure does not have event outputs. The member variables represent the stored data.

### **Data Elements (Structure Members)**

| Name | Data Type | Comment | Initial Value |

| :------- | :------- | :--------------------------------- | :---------------- |

| `Unknown`| `USINT` | u8Colour for Unknown State | `COLOR_WHITE` |

| `Closed` | `USINT` | u8Colour for Closed State | `COLOR_WHITE` |

| `Opening`| `USINT` | u8Colour for Opening State | `COLOR_WHITE` |

| `Opened` | `USINT` | u8Colour for Opened State | `COLOR_WHITE` |

| `Closing`| `USINT` | u8Colour for Closing State | `COLOR_WHITE` |

### **Adapters**
This data structure does not use adapters.

## Functionality
The ``SchieberColorStruct`` is a pure data type. It serves as a container to group five different color values (each as an 8-bit unsigned integer, ``USINT``) for the five defined slider states. By using this structure, a function block or application can pass or store a single, consistent variable containing all the colors required for display. The initial values of all members are set to the constant ``COLOR_WHITE``, which comes from the imported package ``isobus::UT::Q::const::colours``.

## Technical Details
* **Imported Constant:** The structure depends on the externally defined constant ``COLOR_WHITE``, which is provided via the compiler import ``isobus::UT::Q::const::colours::COLOR_WHITE``. This ensures that a consistent, project-wide shade of white is used.
* **Type Safety:** Using a structured type instead of five individual variables improves code readability and maintainability and reduces the likelihood of errors.
* **Hash Attribute:** The structure contains the attribute ``eclipse4diac::core::TypeHash`` with an empty value. This is used by the 4diac system for type identification and management.

## State Overview
Because it is a static data type, ``SchieberColorStruct`` itself does not have a state machine. Instead, it encodes the display attributes for the states of another, parent element (e.g., a ``Schieber`` function block).

## Application Scenarios
* **Visualization in HMIs:** Passing the color configuration to visualization components to correctly display the state of a slider using color (e.g., red for "Closed," green for "Open").
* **Function Block Configuration:** A function block that controls a physical slider can have an instance of this type as a configurable input to enable user-defined colors for state feedback.
* **Data Encapsulation:** Bundling all state-related color information into a single parameter that can be exchanged between different software modules (e.g., controller and visualization).
*
## ⚖️ Comparison with Similar Building Blocks
Unlike function blocks (FBs) such as `E_SR` or `E_D_FF`, which implement logic, `SchieberColorStruct` is a pure **data type** (STRUCT). Similar structured types could be, for example, `MotorConfigStruct` (for configuration data) or `AxisPositionStruct` (for multidimensional positions). Its specific function is to define a color scheme for a predefined set of states.

## Conclusion
The `SchieberColorStruct` is a simple yet useful structured data type that standardizes the management and exchange of color values for representing the state of a slider. It promotes clean interfaces, facilitates reuse, and contributes to consistency within a project through the use of initial default values and imported constants.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
