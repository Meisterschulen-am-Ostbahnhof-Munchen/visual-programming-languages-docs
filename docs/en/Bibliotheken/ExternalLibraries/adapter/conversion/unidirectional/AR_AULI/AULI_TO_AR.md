# AULI_TO_AR
![AULI_TO_AR](./AULI_TO_AR.svg)
* * * * * * * * * *
## Introduction
The function block **AULI_TO_AR** serves as a converting composite block that transforms an **AULI** adapter (ULINT) into an **AR** adapter (REAL).
It enables the easy integration of components that work with different data types and provides type conversion via standardized adapter interfaces.
## Interface Structure

The function block has no direct event or data inputs/outputs, but communicates exclusively via two adapter interfaces.

### **Event Inputs**
- **AULI_IN.E1** (event from socket AULI_IN) – triggers the conversion of the incoming ULINT value.

### **Event Outputs**
- **AR_OUT.E1** (Event for plug AR_OUT) – signals that the converted REAL value is ready.

### **Data Inputs**
- **AULI_IN.D1** (Data from socket AULI_IN) – the ULINT value to be converted.

### **Data Outputs**
- **AR_OUT.D1** (Data for plug AR_OUT) – the converted REAL value.

### **Adapter**

| Name | Direction | Type | Description |

|--------|----------|--------------------------------------------------|-------------------------------|

| AULI_IN | Socket | `adapter::types::unidirectional::AULI` (ULINT) | Input Value |

| AR_OUT | Plug | `adapter::types::unidirectional::AR` (REAL) | Output Value (Converted) |

## Functionality
The function block (FB) is implemented as a composite block and contains an instance of the conversion FB `F_ULINT_TO_REAL` from the IEC 61131 library.

Process:

1. An event on **AULI_IN.E1** triggers the execution of the internal conversion block `Convert`.

2. The current ULINT value from **AULI_IN.D1** is passed to input `Convert.IN`.

3. The internal FB performs the conversion from `ULINT` to `REAL` and stores the result at `Convert.OUT`. 4. After the conversion is complete, the event **AR_OUT.E1** is triggered, and the converted REAL value is available at **AR_OUT.D1**.

## Technical Features
- **Composite structure** – enables reuse and encapsulation of the conversion logic.
- **Adapter-based** – no direct inputs/outputs; communication occurs via unidirectional adapters (socket/plug).
- **Use of the IEC 61131 standard function** `F_ULINT_TO_REAL` – guarantees platform-independent and correct type conversion.
- **Event-driven execution** – the conversion is only triggered by an input event when needed.
- **License** – Eclipse Public License 2.0 (see source code).

## State Overview
The function block **does not have its own state machine**. The conversion is purely functional and event-driven via the internal function block. After each input event, the conversion is performed once, and the result is output.

## Application Scenarios
- **Adapter bridge** between components that supply ULINT and those that expect REAL.
- **Data preparation** in control systems when physical quantities (e.g., counter readings as ULINT) need to be converted into floating-point values for calculations.
- **Modular networking** in IEC 61499 applications, where adapters serve as standardized interfaces between function blocks.

## Comparison with similar function blocks
- **AULI_TO_LREAL** – analog conversion to `LREAL` (double precision).
- **Direct conversion function blocks** (e.g., `F_ULINT_TO_REAL`): These operate at the data level but require manual wiring of events and data. The **AULI_TO_AR** encapsulates this wiring and provides a compact adapter interface.
- **Other Adapter Converters** – there are corresponding function blocks for other type combinations (e.g., `LINT_TO_AR`) that are similarly structured.

## Conclusion
The **AULI_TO_AR** is a useful composite function block for simple and standardized type conversion from ULINT to REAL via adapter interfaces. Thanks to its event-driven execution and the use of an IEC 61131 standard function, it is reliable, reusable, and integrates seamlessly into IEC 61499 projects.