# ALI_TO_AR
![ALI_TO_AR](./ALI_TO_AR.svg)

* * * * * * * * * *
## Introduction
The function block **ALI_TO_AR** is a composite function block (FB) that converts a LINT adapter (ALI) into a REAL adapter (AR). It serves as a universal conversion interface to provide 64-bit integer values from the IEC 61131 standard into floating-point values for further processing in control applications. The function block is licensed under the Eclipse Public License 2.0 and is provided by HR Agrartechnik GmbH.
## Interface Structure
The function block does not have direct event or data ports. All communication takes place via two predefined unidirectional adapters:

### **Event Inputs**
– None (the event interface is provided via the **ALI_IN** adapter)

### **Event Outputs**
– None (the event interface is provided via the **AR_OUT** adapter)

### **Data Inputs**
– None (the data interface is provided via the **ALI_IN** adapter)

### **Data Outputs**
– None (the data interface is provided via the **AR_OUT** adapter)

### **Adapter**

| Direction | Name | Type | Description |

|----------|--------|------------------------------------------|----------------------------------|

| Socket | ALI_IN | `adapter::types::unidirectional::ALI` | LINT Input Adapter (64-bit Integer) |

| Plug | AR_OUT | `adapter::types::unidirectional::AR` | REAL Output Adapter (Floating Point) |

Each adapter contains an event channel (E1) and a data channel (D1), which are connected via the module's internal network.

## Functionality
The module performs a simple data-driven conversion:

1. An event arrives at the event input **E1** via the **ALI_IN** socket – simultaneously, the corresponding LINT value is provided at the data input **D1**.

2. This event is forwarded to the internal module `iec61131::conversion::F_LINT_TO_REAL` (event **REQ**).

3. The internal module converts the LINT value into a REAL value and signals completion via the event output **CNF**.

4. The converted REAL value is transferred via the data connection to the data input of the plug adapter **AR_OUT** (D1).

5. Simultaneously, the **E1** event of the **AR_OUT** adapter is triggered, allowing the connected logic to process the new REAL value.

The entire conversion process is performed without state storage – each request is processed immediately.

## Technical Features
- **Composite Block**: The ALI_TO_AR is a composite function block consisting exclusively of the internal standard block `F_LINT_TO_REAL`.
- **Library Integration**: The conversion utilizes the IEC 61131 library `iec61131::conversion::F_LINT_TO_REAL`, which is declared as an import.
- **Package Structure**: The block is organized within the package `adapter::conversion::unidirectional`.
- **License**: The source code is licensed under the Eclipse Public License 2.0 (EPL-2.0).

## State Overview
The function block has no states of its own. It operates purely event-driven and data-flow-oriented. There are no initialization or error-related states – every incoming request is processed directly.

## Application Scenarios
- **Counter Evaluation**: A LINT counter (e.g., pulse counter) delivers a large integer that must be converted into a REAL value for control purposes.
- **Data Preprocessing**: In a PLC application, measured values are available as LINT (e.g., from an encoder) that need to be converted into REAL for further calculations or visualization.
- **Adapter Bridge**: The function block serves as a standardized converter between two different adapter types in a cross-device communication infrastructure.

## Comparison with Similar Function Blocks
- **ALI_TO_ARI**: Converts LINT to an ARRAY-from-REAL – for multiple values or buffers.
- **LREAL_TO_AR**: Converts LREAL (80-bit floating-point) to REAL – for losses due to lower precision.
- **Direct Type Conversion** to IEC 61131 functions (e.g., `LINT_TO_REAL`) – without adapter encapsulation, requires manual event wiring.

The ALI_TO_AR offers the advantage of a standardized adapter interface over simple function calls, enabling plug-and-play use in modular systems.

## Conclusion

The **ALI_TO_AR** is a compact, reusable function block for converting LINT values to REAL values via an adapter interface. Its simple internal structure and clear event-data coupling make it an indispensable component for any application that needs to convert integer sensor data into floating-point values for control or visualization purposes. Licensing under EPL-2.0 allows unrestricted use in open and commercial projects.
