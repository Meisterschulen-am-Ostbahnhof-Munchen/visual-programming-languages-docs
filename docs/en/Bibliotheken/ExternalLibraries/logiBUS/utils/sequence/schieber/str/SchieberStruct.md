# SlideStruct

* * * * * * * * * *
## Introduction
The `SchieberStruct` is a structured data type used to represent all possible states of a slide (e.g., a valve, flap, or closure) within a control system. It serves as a central container for the object identifiers (IDs) assigned to the various states of the slide. This data type is typically used in conjunction with function blocks that implement state machines or sequences for slide control.

## Interface Structure
The `SchieberStruct` is a data type and therefore does not have event or adapter interfaces in the conventional sense. Its structure consists exclusively of data fields.

## **Data Inputs**
Not applicable. The structure defines a data type, not function block interfaces.

## **Data Outputs**
Not applicable. The structure defines a data type, not function block interfaces.

### **Adapter**
Not applicable.

## Functionality
The ``SchieberStruct`` is a data structure containing five fields of type ``UINT`` (16-bit unsigned integer). Each field represents a specific state of a slider and stores the corresponding object ID (``u16ObjId``). These IDs are used to access the graphical or logical representations of the states in a higher-level system (e.g., a visualization or logic module).

The initial values of all fields are set to the constant ``ID_NULL``, indicating an undefined or unassigned state. These must be populated with valid object IDs before using the structure.


``` ## Technical Features
* **Initialization:** All member variables are initialized with the default value `ID_NULL`. This ensures that the structure starts in a defined, neutral state before specific IDs are assigned.

* **Type Safety:** Using a structured data type instead of individual, loosely coupled variables improves code maintainability and readability.

* **Compilation Note:** The data type is defined in the package `logiBUS::utils::sequence::schieber` and imports the constant `ID_NULL` from the `isobus::UT::Q::const::IDs` namespace.

## State Overview
The structure explicitly maps the following five states of a slider:

1. **`Unknown`:** The slider's state is unknown or could not be determined.

2. **`Closed`:** The slide is in the closed end position.

3. **`Opening`:** The slide is in the process of opening (movement state).

4. **`Opened`:** The slide is in the open end position.

5. **`Closing`:** The slide is in the process of closing (movement state).

## Application Scenarios

* **State Management:** A higher-level control block can maintain an instance of this structure to centrally manage the currently valid object IDs for all slide states.

* **Parameterization:** The structure can be passed as a configurable parameter to a function block, which then selects the corresponding ID from the structure based on its internal state and forwards it, for example, to a visualization system. * **Visualization:** An HMI or SCADA system can use the IDs stored in the structure to update the slider's graphical symbol according to its current state (e.g., color, symbol).

## ⚖️ Comparison with similar blocks
Unlike function blocks such as `E_SR` (memory element) or `E_CTUD` (counter), which implement active logic, `SchieberStruct` is a passive data type. Similar structured data types could be defined for other devices with state machines (e.g., `PumpeStruct`, `MotorStruct`). The unique feature lies in the specific mapping of the states characteristic of a linear slider: `Opening`, `Closing`, `Opened`, and `Closed`, including a `Unknown` state.

## Conclusion
The `SchieberStruct` data type is a useful construct for the structured and type-safe handling of state information for slider actuators. By encapsulating the relevant object IDs in a single structure, the configuration and maintenance of applications that control and visualize such actuators is simplified. Its use promotes a clear and consistent programming style.


## Conclusion ---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter module on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)


```