# ALR_TO_AL
![ALR_TO_AL](./ALR_TO_AL.svg)

* * * * * * * * * *
## Introduction
The **ALR_TO_AL** function block is a composite function block according to IEC 61499-2. It is used to convert an **ALR adapter** (LREAL data type) into an **AL adapter** (LWORD data type). The conversion is implemented via the internal function block `F_LREAL_TO_LWORD` from the IEC 61131-3 library.
## Interface Structure
### **Event Inputs**

The function block has **no independent event inputs**. Events are provided via the **socket adapter** `ALR_IN`:

| Adapter | Event / Signal | Description |

| Adapter | Event / Signal | Description | |---------|-------------------|--------------|

| ALR_IN | E1 | Trigger event to initiate the conversion |

### **Event Outputs**
This function block has **no independent event outputs**. Events are output via the **plug adapter** `AL_OUT`:

| Adapter | Event / Signal | Description |

|---------|-------------------|--------------|

| AL_OUT | E1 | Confirmation event after conversion is complete |

### **Data Inputs**
There are also **no direct data inputs**. Data is supplied via the socket adapter `ALR_IN`:

| Adapter | Data / Signal | Data Type | Description |

| Adapter | Data / Signal | Data Type | Description | |---------|----------------|----------|--------------|

| ALR_IN | D1 | LREAL | Input value in LREAL format |

### **Data Outputs**
No direct data outputs. Output data is provided via the plug adapter `AL_OUT`:

| Adapter | Data / Signal | Data Type | Description |

|---------|----------------|----------|--------------|

| AL_OUT | D1 | LWORD | Converted output value in LWORD format |

### **Adapters**

The module is connected to the environment via two adapters:

- **Socket** `ALR_IN`: Of type `adapter::types::unidirectional::ALR` – provided by a preceding component.
- **Plug** `AL_OUT`: Of type `adapter::types::unidirectional::AL` – offered to a subsequent component.

The adapters transmit both events and data via their respective ports (E1, D1).

## Functionality
When an event **E1** arrives at socket `ALR_IN`, the internal module `F_LREAL_TO_LWORD` (type `iec61131::conversion::F_LREAL_TO_LWORD`) is activated via its event input `REQ`. Simultaneously, the data value `D1` of the adapter socket is transferred to the data input `IN` of the conversion module. After successful conversion, the internal module outputs a confirmation event at its output `CNF`. This event is forwarded to the event input `E1` of the plug adapter `AL_OUT`. The converted value (LWORD) is transferred to the adapter plug via the data connection `Convert.OUT` → `AL_OUT.D1`.

... The conversion itself corresponds to the IEC 61131-3 function `LREAL_TO_LWORD`, which maps the bitwise structure of an LREAL value to an LWORD value (e.g., for transferring floating-point numbers as raw data).

## Technical Features
- **Composite Block**: The functionality is implemented by an internal network circuit that uses the block `F_LREAL_TO_LWORD`.
- **Packaging**: The block is stored in the package `adapter::conversion::unidirectional`, indicating its use in unidirectional adapter chains.
- **Import**: `iec61131::conversion::F_LREAL_TO_LWORD` must be available in the project.
- **Copyright**: This block was developed for HR Agrartechnik GmbH and is licensed under the Eclipse Public License 2.0 (EPL-2.0).

## State Overview
Since this is a **composite function block** without its own state machine, its behavior is determined by that of the internal function block `F_LREAL_TO_LWORD`. This block performs a pure, stateless conversion: An event triggers the calculation, and the result is provided immediately. The function block has no internal state that persists across multiple calls.

## Application Scenarios
- **Data Format Adaptation**: When a system component delivers data in ALR format (LREAL via adapter), but a subsequent component only understands AL interfaces (LWORD via adapter).
- **Communication Between Different Control Levels**: For example, transferring physical measured values from a PLC (LREAL) to a higher-level control system that expects LWORD as the raw data format.
- **Test and Simulation Setups**: Generating defined LWORD values from LREAL sources without changing the actual adapter logic.

## Comparison with Similar Function Blocks
- **AL_TO_ALR**: Performs the reverse conversion (LWORD → LREAL).
- **Direct Conversion Functions**: IEC 61131-3 provides `LREAL_TO_LWORD` and `LWORD_TO_LREAL` as elementary function blocks – `ALR_TO_AL` encapsulates these in an adapter-compliant composite function block, allowing it to be directly integrated into adapter chains.

## Conclusion
The **ALR_TO_AL** function block is a specialized conversion block for converting an LREAL adapter to an LWORD adapter. Its composite structure enables seamless integration into existing adapter-based architectures without requiring the user to manually configure the underlying conversion function. The unambiguous event control and the use of standardized data types make it a robust solution for adapting data formats in IEC 61499 control systems.
