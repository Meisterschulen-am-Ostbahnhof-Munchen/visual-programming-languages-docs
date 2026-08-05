# ALR_TO_ALI

![ALR_TO_ALI](./ALR_TO_ALI.svg)

* * * * * * * * * *
## Introduction
The function block **ALR_TO_ALI** is a composite block that performs an adapter conversion from **ALR (LREAL)** to **ALI (LINT)**. It enables the simple and structured integration of an LREAL-based adapter interface into a LINT-based environment without requiring the implementation of the conversion logic itself. The block is designed for use in IEC 61499-based industrial controllers and utilizes the internal function block `F_LREAL_TO_LINT` according to IEC 61131-3.

## Interface Structure
### **Event Inputs**
The function block does not have explicit event inputs. The triggering event is provided via the incoming adapter **ALR_IN** (type `adapter::types::unidirectional::ALR`):

- **ALR_IN.E1** – Input event that starts the conversion.

### **Event Outputs**
The function block (FB) does not have any explicit event outputs. The confirmation event is provided via the outgoing adapter **ALI_OUT** (type `adapter::types::unidirectional::ALI`):

- **ALI_OUT.E1** – Output event that signals the completion of the conversion.

### **Data Inputs**
The FB does not have an explicit data input. The input value is provided via the adapter **ALR_IN**:

- **ALR_IN.D1** – Value of type LREAL to be converted to LINT.

### **Data Outputs**
The FB does not have an explicit data output. The result is output via the **ALI_OUT** adapter:

- **ALI_OUT.D1** – converted value of type LINT.

### **Adapter**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket (Input) | ALR_IN | `adapter::types::unidirectional::ALR` | Unidirectional adapter for LREAL data and events. Includes event port E1 and data port D1 (LREAL). |

| Plug (Output) | ALI_OUT | `adapter::types::unidirectional::ALI` | Unidirectional adapter for LINT data and events. Includes event port E1 and data port D1 (LINT). |


## Functionality
The function block (FB) acts as a wrapper for type conversion from LREAL to LINT. The flowchart is as follows:

1. An event (E1) on the input adapter **ALR_IN** triggers the internal block **Convert** (type `iec61131::conversion::F_LREAL_TO_LINT`).

2. The data value from **ALR_IN.D1** (LREAL) is passed to the input **Convert.IN**.

3. The internal block performs the conversion and outputs the result to **Convert.OUT**.

4. The event at the output **Convert.CNF** is forwarded to **ALI_OUT.E1**, so the outgoing adapter signals that the conversion is complete.

5. The converted LINT value is available at **ALI_OUT.D1**.


Call control is achieved via event chaining (E1 → REQ → CNF → E1), ensuring that conversion occurs blocking within a single execution cycle.

## Technical Features

- **Composite Structure**: The function block is implemented as a composite (network) and internally uses the standard function block `F_LREAL_TO_LINT` from the IEC 61131-3 library.

- **Adapter Encapsulation**: The adapter technology allows the specific LREAL and LINT signals to be connected via standardized interfaces (ALR, ALI), enabling high reusability and interchangeability.

- **License**: The source code is licensed under the Eclipse Public License 2.0 (EPL-2.0).

- **Version**: 1.0, released on February 17, 2026, by HR Agrartechnik GmbH, author: Franz Höpfinger.

- **Package Structure**: `adapter::conversion::unidirectional`.

## State Overview
The function block does not have an explicit state machine, as it is implemented as a network by a single internal function block. Its behavior is purely event-driven:

- **Idle**: Waiting for an event at the input adapter (ALR_IN.E1).

- **Processing**: Upon arrival of the event, the internal conversion block is activated.

- **Done**: After completion (CNF), the output event (ALI_OUT.E1) is set, and the function block returns to the idle state.

There is no explicit error state, as the conversion block `F_LREAL_TO_LINT` does not provide error handling.

## Application Scenarios

- **Migration**: Replacing an ALI-based (LINT) system with an ALR-based (LREAL) system or vice versa, without changing the higher-level logic.

- **Adapter Bridge**: If a component only provides LREAL values, but the subsequent adapter expects LINT, this function block (FB) can be used as an intermediary.

- **Standardized Conversion**: In libraries or frameworks that require a uniform implementation of type conversions via adapters.

## Comparison with Similar Function Blocks
In the IEC 61499 and IEC 61131 worlds, numerous conversion function blocks exist:

- **F_LREAL_TO_LINT** (direct): A single function block that converts a simple value but does not provide an adapter interface.

- **ALR_TO_ALI** (this FB): Encapsulates the direct function block in an adapter structure, enabling connection via standardized adapter ports.

- **Other Type Conversions**: Similarly structured function blocks for, e.g., REAL → DINT or LREAL → DWORD, can be created using the same pattern.


The key advantage of **ALR_TO_ALI** is its reusability within the adapter context and the clean separation of events and data.

## Conclusion
The **ALR_TO_ALI** function block is a useful composite block that enables clean and standardized adapter conversion from LREAL to LINT. It inherits the robustness of the IEC 61131-3 conversion block and seamlessly integrates it into the adapter-based communication architecture. Its open license and clear interface make it well-suited for use in modular automation solutions.