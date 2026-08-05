# AULI_TO_ALR
No image available.
![AULI_TO_ALR](./AULI_TO_ALR.svg)

* * * * * * * * * *
## Introduction
The **AULI_TO_ALR** is a composite function block (FB) that converts an incoming AULI adapter (ULINT data) into an outgoing ALR adapter (LREAL data). It serves as a standardized interface between components that communicate different data types via adapters.

## Interface Structure

### **Event Inputs**

The block has no direct event inputs. The incoming event is provided via the socket adapter **AULI_IN**:

- **AULI_IN.E1** (Event) – Receives the trigger signal for the conversion.

### **Event Outputs**

The block has no direct event outputs. The outgoing event is provided via the **ALR_OUT** plug adapter:

- **ALR_OUT.E1** (Event) – Signals that the converted data is available at the data output.

### **Data Inputs**

Direct data inputs are not available. The input data is provided via the **AULI_IN** socket adapter:

- **AULI_IN.D1** (ULINT) – The value to be converted in unsigned long integer format.

### **Data Outputs**

Direct data outputs are not available. The output data is provided via the **ALR_OUT** plug adapter:

- **ALR_OUT.D1** (LREAL) – The converted value in long real format (64-bit floating-point number).

### **Adapters**

The function block uses exactly two adapters:

- **Socket AULI_IN** (Type: AULI from `adapter::types::unidirectional`) – Receives the ULINT values and the associated trigger event.
- **Plug ALR_OUT** (Type: ALR from `adapter::types::unidirectional`) – Provides the converted LREAL values and an acknowledgment event.

## Functionality

The function block operates according to the request-acknowledgment principle:

1. As soon as an event arrives at **E1** on the input adapter **AULI_IN**, the internal function block **F_ULINT_TO_LREAL** (from the library `iec61131::conversion`) is called.

2. The value **AULI_IN.D1** is fed to the input **IN** of the converter. 3. The converter performs the conversion from ULINT to LREAL (integer to floating-point number).

4. After the conversion is complete, the result is forwarded to **ALR_OUT.D1**.

5. Simultaneously, the event **ALR_OUT.E1** is triggered at the output adapter to signal the downstream function block that the data is being processed.

All logic runs within a function block network and is transparent to the user.

## Technical Features
- **Adapter-based communication:** The function block encapsulates the type conversion in an adapter interface, allowing it to be seamlessly integrated into systems with standardized adapter types (e.g., AULI and ALR). This increases compatibility between components.
- **Reuse of existing function blocks:** As a composite function block, it uses the standardized conversion block `F_ULINT_TO_LREAL`, ensuring the maintainability and correctness of the conversion logic.
- **Compatibility with IEC 61499-2:** The function block complies with the standard and can be used in any 4diac IDE project.
- **No State Machine:** The conversion is purely combinatorial, controlled by events – there are no internal states.

## State Overview

The function block has no independent states. The sequence control is triggered by the event at **AULI_IN.E1** and ends with the event at **ALR_OUT.E1**. During the conversion, the function block is in the state "waiting for confirmation from the internal function block." This is not visible to the user.

## Application Scenarios
- **Integration of sensors or actuators** that deliver their internal counter values as ULINT into a controller that requires LREAL for calculations (e.g., control algorithms).
- **Adapter bridge** between two subsystems with different adapter definitions, enabling type conversion without changing the interface definitions.
- **Data preparation** in communication protocols where received integers need to be converted into floating-point values for further processing.

## Comparison with similar function blocks

Instead of a dedicated adapter converter, one could also use the function block `F_ULINT_TO_LREAL` directly and connect the events/data manually. The advantage of **AULI_TO_ALR** lies in the encapsulation of the adapter interfaces: It saves the developer from manually wiring the adapter events and data and ensures a clean, reusable component. Compared to a custom solution, it offers a standardized, documented interface.

## Conclusion

The **AULI_TO_ALR** is a useful, specialized function block for converting ULINT to LREAL values in the context of adapters. It simplifies the integration of components with different data types into uniform adapter structures and increases the maintainability of IEC 61499 systems. Thanks to its standardized conversion function and clear, event-driven operation, it is reliable and easy to understand.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
