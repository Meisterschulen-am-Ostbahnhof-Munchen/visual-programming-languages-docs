# ALR_TO_AUI
![ALR_TO_AUI](./ALR_TO_AUI.svg)

* * * * * * * * * *
## Introduction
The function block **ALR_TO_AUI** is a composite function block (FB) that converts an LREAL value, received via an **ALR** adapter (unidirectional), into a UINT value and makes it available via an **AUI** adapter (unidirectional). The conversion is performed using the internal IEC 61131 function block `F_LREAL_TO_UINT`. This block encapsulates the adapter conversion and provides a clean interface for data exchange between the two adapter types.
## Interface Structure

### **Event Inputs**
The FB does not have its own event inputs. Events are received indirectly via the **ALR_IN** adapter:

- **ALR_IN.E1** – Event to trigger the conversion.

### **Event Outputs**
The FB does not have its own event outputs. Events are sent via the **AUI_OUT** adapter:

- **AUI_OUT.E1** – Confirmation event after successful conversion.

### **Data Inputs**
The data is also provided via the **ALR_IN** adapter:

- **ALR_IN.D1** – Input value of type **LREAL** (according to the ALR adapter).

### **Data Outputs**
The converted data is output via the **AUI_OUT** adapter:

- **AUI_OUT.D1** – Output value of type **UINT** (according to the AUI adapter).

### **Adapters**

| Name | Type | Direction | Description |
|-------------|-----|----------|--------------|
| **ALR_IN** | `adapter::types::unidirectional::ALR` | Socket (Input) | Returns the LREAL value and the trigger event. |
| **AUI_OUT** | `adapter::types::unidirectional::AUI` | Plug (Output) | Outputs the converted UINT value and the confirmation event. |

## Functionality

The function block operates as a pure translation layer between two adapters:

1. An incoming event at socket **ALR_IN.E1** triggers the internal conversion block `F_LREAL_TO_UINT` via its **REQ** input.

2. Simultaneously, the data value **ALR_IN.D1** is forwarded to the **IN** input of the conversion block.

3. The internal block performs the type conversion from **LREAL** to **UINT** and places the result at its **OUT** output.

4. Once the conversion is complete, the internal block sends an acknowledgment event (**CNF**), which is passed to the plug **AUI_OUT.E1**.

5. Simultaneously, the converted value (**OUT**) is transferred to the data output **AUI_OUT.D1**.

The entire process is event-driven and occurs once per triggering event.

## Technical Features
- **Adapter Encapsulation:** The block combines two different adapter types (ALR and AUI), thus enabling type-safe communication between components that use these adapters.
- **Unidirectional Adapters:** Both the input and output adapters are unidirectional, meaning there is only one direction of data and events (input → output).
- **Internal Conversion:** The actual conversion is performed by the standardized IEC 61131 function block `F_LREAL_TO_UINT`. This ensures well-defined and platform-independent conversion behavior.
- **No Control:** The composite function block itself does not have its own state machine. Its behavior is entirely determined by the embedded function block.

## State Overview

Since this is a composite function block without its own Execution Control Chart (ECC), there is no internal state machine. The process is controlled by the event links:

- **IDLE:** Waiting for an event at socket **ALR_IN.E1**.
- **CONVERT:** After receiving the event, the conversion is triggered; The internal function block iterates through its own state machine (e.g., REQ → CNF).
- **OUTPUT:** After the conversion is complete, the output event **AUI_OUT.E1** and the converted value are output.

## Application Scenarios
- **Connecting Sensors/Actuators:** A sensor provides an LREAL value (e.g., temperature, pressure) which is read into a PLC via an ALR adapter. For display or transmission to a system that only processes integers (UINT), the function block is used.
- **Adapter Migration:** In existing systems, adapters need to be converted from ALR to AUI without changing the connected components. The function block acts as an intermediary.
- **Test and Simulation Environments:** Generating UINT values from LREAL sources for testing purposes.

## Comparison with Similar Function Blocks

| Function Block | Input Type | Output Type | Description |
|----------|-------------|-------------|-------------|
| **ALR_TO_AUI** | ALR (LREAL) | AUI (UINT) | Adapter-based conversion LREAL→UINT. |
| `F_LREAL_TO_UINT` | LREAL | UINT | Pure data conversion without an adapter. |
| `LREAL_TO_INT` | LREAL | INT | Conversion to a signed integer. |

Unlike pure data converters, **ALR_TO_AUI** operates at the adapter level, so both the data and the associated events are exchanged via the adapter interfaces. This simplifies integration into adapter-based architectures.

## Conclusion

The **ALR_TO_AUI** function block is a useful tool for converting LREAL values from an ALR adapter to UINT values from an AUI adapter. Encapsulating the conversion in a composite function block increases reusability and clearly defines the system interface. This block is particularly suitable for applications where adapter types need to be harmonized or adapted without altering the internal logic of the connected components.
