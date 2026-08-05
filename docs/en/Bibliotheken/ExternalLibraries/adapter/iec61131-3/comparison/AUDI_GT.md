# AUDI_GT
![AUDI_GT](./AUDI_GT.svg)

* * * * * * * * * *
## Introduction
The AUDI_GT function block performs a "greater than" comparison of two values. It is designed as an IEC 61131-3 compliant comparison block and uses an adapter-based interface to transmit values and events. The block is part of the iec61131::comparison library.
## Interface Structure

### **Event Inputs**
- **IN1.E1** – Event input for the first value (via adapter IN1)
- **IN2.E1** – Event input for the second value (via adapter IN2)
Both events are connected to the internal REQ input of the F_GT block.

### **Event Outputs**
- **OUT.E1** – Event output that is activated after the comparison is complete (via adapter OUT). The result is then available at the data output.

### **Data Inputs**
- **IN1.D1** – First input value (via adapter IN1, type depends on adapter AUDI)
- **IN2.D1** – Second input value (via adapter IN2, type depends on adapter AUDI)

### **Data Outputs**
- **OUT.D1** – Comparison result: TRUE if IN1 > IN2, otherwise FALSE (via adapter OUT, type depends on adapter AX)

### **Adapters**
- **Socket IN1** (Type: `adapter::types::unidirectional::AUDI`) – Connection for the first value to be compared.
- **Socket IN2** (Type: `adapter::types::unidirectional::AUDI`) – Connection for the second value to be compared.
- **Plug OUT** (Type: `adapter::types::unidirectional::AX`) – Output of the comparison result.

The adapters used are unidirectional and each provides one event port and one data port.

## Functionality

The AUDI_GT function block encapsulates the basic comparison function block F_GT from the IEC 61131-3 library. The input adapters IN1 and IN2 each provide a value (D1) and a start signal (E1). Both events are connected to the REQ input of F_GT, so that the comparison is triggered as soon as at least one of the events occurs. Internally, F_GT performs the comparison of the two values. The result (BOOL) is provided via the output adapter OUT, simultaneously generating an event (E1).

## Technical Features
- The function block uses adapters instead of direct input/output ports, which allows for flexible encapsulation and reuse of the interfaces.
- The events from both inputs are combined on the same REQ input of the internal F_GT. This means that the function block re-performs the comparison with each event received at IN1 or IN2.
- The function block outputs the result as a BOOL value (TRUE/FALSE). The exact data types of the adapters (AUDI, AX) are application-specific and may vary depending on the context.
- The function block is identified as part of the `iec61131::comparison` library and complies with the IEC 61131-3 standard.

## State Overview

The AUDI_GT function block does not have its own state machine. All logic is implemented by the internal F_GT, which performs a simple combinational comparison. There are no internal states or memory behaviors; the result is recalculated with each activation.

## Application Scenarios
- **Process Monitoring**: Comparison of measured values (e.g., temperature, pressure) with a threshold value. If Value1 > Value2, an alarm is triggered.
- **Logical Decisions**: In automation processes, e.g., sorting logic or priority controls.
- **Safety Functions**: Checking whether a current value exceeds a limit.
- **Adapter-Based Systems**: Wherever modular, reusable interfaces via adapters are desired.

## Comparison with Similar Function Blocks
- **GT (Greater Than)**: Simple comparators like `F_GT` (IEC 61131-3) have direct inputs. `AUDI_GT` extends this to an adapter-based interface, which facilitates integration into heterogeneous systems.
- **GE (Greater or Equal)**, **LT (Less Than)**, **EQ (Equal)**: Analogous function blocks for other comparison operations. This function block only supports "Greater Than".
- **Comparison Cascades**: Multiple AUDI_GTs can be linked to create more complex expressions by connecting their outputs to the inputs of other function blocks.

## Conclusion

The AUDI_GT is a dedicated comparison function block for the "greater than" function with adapter-based inputs and outputs. It offers a standardized, modular interface according to IEC 61131-3 and is particularly suitable for use in distributed automation systems that require loose coupling of components. Thanks to its adapter technology, the function block can be flexibly embedded in various contexts.
