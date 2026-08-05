# SliderAuxOutStruct

* * * * * * * * * *
## Introduction
The data block `SchieberAuxOutStruct` defines a structure for configuring the visual representation of an AUX output element. It is used to specify both the image to be displayed and its background color. This block is part of a functionality for controlling screen displays, typically in agricultural or mobile machinery.

## Interface Structure
The block is a structured data type (STRUCT) and has no event or adapter interfaces. It consists exclusively of data elements.

### **Data Inputs**
The structure itself has no inputs in the conventional sense, as it is a data type. Its elements are populated with values when an instance of this type is created.

### **Data Outputs**
The structure itself has no outputs. It defines the following internal data fields:

| Name | Data Type | Initial Value | Comment |

| :--- | :--- | :--- | :--- |

| `Picture` | `UINT` | `ID_NULL` | u16ObjId for the image to be displayed. |

| `u8Colour` | `USINT` | `COLOR_WHITE` | Background color of the AUX element. |

## Functionality
The `SchieberAuxOutStruct` is purely a data storage structure. It encapsulates the two parameters `Picture` (image ID) and `u8Colour` (background color), which are needed together to describe the visual properties of an AUX output field. The initial values ensure a defined default state: an empty image (`ID_NULL`) on a white background (`COLOR_WHITE`).

## Technical Features
* **Initialization:** The structure uses predefined constants (`ID_NULL`, `COLOR_WHITE`) from imported namespaces for the initial values. This ensures consistency and simplifies maintenance.

* **Typing:** Explicit typing (`UINT` for the image ID, `USINT` for the color) enables rigorous checks by the compiler and increases reliability.

* **Usage:** This STRUCT is typically used as a data type for inputs or outputs of function blocks (FBs) that interact with graphical user interfaces or display devices.


* ## State Overview
Since it is a passive data type, `SchieberAuxOutStruct` does not have an internal state machine. Its "state" is entirely defined by the currently stored values in `Picture` and `u8Colour`.

## Application Scenarios
This function block primarily serves to parameterize display elements in ISOBUS-compatible terminals (UTs). Specific applications include:

* Configuration of sliders or status indicators in a user interface.

* Dynamic change of symbols and their backgrounds depending on the machine state (e.g., warning, activity, error).

* Standardization of data exchange between control logic and visualization function blocks.


## ⚖️ Comparison with Similar Building Blocks
Unlike function blocks, which contain active logic, `SchieberAuxOutStruct` is a pure data type. Similar STRUCTs in the same context could be, for example, `SchieberAuxInStruct` for input parameters or more general `DisplayElementStruct` blocks, which may contain additional properties such as position or size. This block is specifically tailored to the combination of image and background color.

## Conclusion
`SchieberAuxOutStruct` is an essential, reusable data component for display applications in the 4diac IDE. By encapsulating the relevant parameters in a structured type, it promotes clear interfaces, improves code readability, and reduces parameter passing errors. Its use with initialized default values and imported constants follows established software engineering practices.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```