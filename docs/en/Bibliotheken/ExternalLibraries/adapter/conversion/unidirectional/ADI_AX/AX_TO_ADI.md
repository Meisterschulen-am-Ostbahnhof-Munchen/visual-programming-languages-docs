# AX_TO_ADI
![AX_TO_ADI](./AX_TO_ADI.svg)
* * * * * * * * * *
## Introduction
The **AX_TO_ADI** function block is a composite function block (FB) that converts an AX adapter with a Boolean interface (BOOL) into an ADI adapter with an integer interface (DINT). It serves as a converter between unidirectional adapters and enables the seamless integration of binary signals into systems that use integer-based adapters.
## Interface Structure
Since it is a composite FB, all inputs and outputs are implemented via the included adapters. The following list shows the logical interfaces.

## **Event Inputs**
The function block does not have direct event inputs. Event control is handled via the **AX_IN** adapter:

- **E1** (BOOT): Event input of the AX adapter that triggers the data conversion.

### **Event Outputs**

This function block does not have direct event outputs. Event forwarding is handled via the **ADI_OUT** adapter:

- **E1** (CNF): Event output of the ADI adapter, signals completion of the conversion.

### **Data Inputs**
This function block does not have direct data inputs. Data is acquired via the **AX_IN** adapter:

- **D1** (BOOL): Boolean input value that is converted to a DINT value.

### **Data Outputs**
This function block does not have direct data outputs. Data output is handled via the **ADI_OUT** adapter:

- **D1** (DINT): Converted integer output value (0 for FALSE, 1 for TRUE).

### **Adapter**
- **AX_IN** (Socket): Receives an AX adapter (type: `adapter::types::unidirectional::AX`) with a Boolean data and event key.
- **ADI_OUT** (Plug): Provides an ADI adapter (type: `adapter::types::unidirectional::ADI`) with a DINT data and event key.

## Functionality
The function block internally uses the IEC 61131-3 converter `F_BOOL_TO_DINT`. As soon as an event arrives at **AX_IN.E1**, the current value of **AX_IN.D1** is read and passed to the converter. The converter sets the value 0 for FALSE and the value 1 for TRUE. After the conversion is complete, the result is passed to **ADI_OUT.D1** and an event is simultaneously sent to **ADI_OUT.E1**.

The event chain is thus fully looped:

`AX_IN.E1` → Conversion → `ADI_OUT.E1`.

## Technical Features
- **Pure Data Conversion:** The function block does not perform any state logic or time delay – every event activation at the input immediately generates an output.
- **Use of IEC 61131 Libraries:** The conversion is based on the standardized function block `F_BOOL_TO_DINT` from the IEC 61131 conversion library.
- **Unidirectional Adapters:** Both AX and ADI are unidirectional adapters, meaning they only support one direction (input or output). This simplifies data flow control.
- **Composite Function Block without its own state:** As a composite function block, it has no internal state machine; all logic is implemented by the embedded function block.

## State Overview
As a composite function block, **AX_TO_ADI** does not have its own state machine. Its behavior is determined solely by the embedded `F_BOOL_TO_DINT`, which has no state-dependent logic. The output is always a direct function of the input at the time of event activation.

## Application Scenarios
- **Binary Signal Conversion:** When a sensor or switch provides a Boolean signal via an AX adapter that needs to be further processed in a system with ADI adapters (DINT).
- **Gateway Function:** Connection between subsystems using different adapter types without changing the underlying logic.
- **Testing and Simulation:** Generation of a defined DINT value from a Boolean input for testing purposes.

## Comparison with Similar Function Blocks
- **AX_TO_ADI (this function block):** Converts BOOL to DINT via adapters.
- **ADI_TO_AX (hypothetical):** Would convert DINT to BOOL, e.g., by comparison with zero or a threshold.
- **Direct Command F_BOOL_TO_DINT:** This function block is an encapsulated version specifically designed for use with unidirectional adapters. Unlike the basic function block, the adapter interfaces are already integrated.

## Conclusion

**AX_TO_ADI** is a simple yet useful converter function block that converts Boolean adapter signals into integer-based adapter signals. It enhances interoperability between different components of a system and enables a clean separation of data and event flows. Due to its low complexity, it can be deployed quickly and easily integrated into larger composite function block chains.