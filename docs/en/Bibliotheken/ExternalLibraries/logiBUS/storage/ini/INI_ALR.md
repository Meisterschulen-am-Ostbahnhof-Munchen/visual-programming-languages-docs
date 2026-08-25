# INI_ALR

![INI_ALR](./INI_ALR.svg)

* * * * * * * * * *
## Introduction

The function block **INI_ALR** is used to read and write floating-point values of type LREAL to and from a `settings.ini` file. It accesses a configuration file that is parameterized via a section name and a key. The block encapsulates the use of the internal `INI` function block and additionally provides a standardized **ALR** adapter interface (unidirectional) through which values can be both set and read.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment | With Variables |
|----------|-------|----------------------------------------------|--------------------------------------|
| INIT | EInit | Initializes the function block and triggers a read operation | QI, SECTION, KEY, DEFAULT_VALUE |

### **Event Outputs**

| Event | Type | Comment | With variables |
|----------|-------|---------------------------------|---------------|
| INITO | EInit | Confirms initialization | QO, STATUS |

### **Data Inputs**

| Name | Type | Comment |
|----------------|--------|-----------------------------------------------------------|
| QI | BOOL | Event Input Qualifier (Allow) |
| SECTION | STRING | Section name in the INI file |
| KEY | STRING | Key name within the section |
| DEFAULT_VALUE | LREAL | Fallback value if the key is missing in the INI file |

### **Data Outputs**

| Name | Type | Comment |
|--------|--------|----------------------------------|
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Status message (e.g., error text) |

### **Adapters**

| Adapter | Type | Comment |
|----------|-----------------------------------|--------------------------------------------------------|
| ALR_IN | adapter::types::unidirectional::ALR| Socket – Value to store (SET) |
| ALR_OUT | adapter::types::unidirectional::ALR| Plug – Read value (GET)/Confirmation |

## Functionality

1. **Initialization and First Read**

An event at the input `INIT` triggers the initialization of the internal `INI` block. The parameters `QI`, `SECTION`, `KEY`, and `DEFAULT_VALUE` are forwarded to the `INI` block. After its acknowledgment (`INITO`), the GET operation of the `INI` block is automatically triggered. The read value appears at the data output of the adapter `ALR_OUT.D1` and is simultaneously signaled via the event `ALR_OUT.E1`. The outputs `QO` and `STATUS` of the `INI` block are directly passed through to the corresponding outputs of the `INI_ALR` block.

... 2. **Write via ALR-IN**

A set event at the adapter socket `ALR_IN.E1` is forwarded to the SET input of the internal `INI` module. The value to be saved is located at `ALR_IN.D1` and is set via `INI.VALUE`. After successful writing, the `INI` module acknowledges with `SETO`, which in turn triggers `ALR_OUT.E1`.

3. **Reading via ALR-IN** (implicit)

The currently read value is always available at output `ALR_OUT` via the initial GET sequence and the forwarding of `GETO`. A new read can be triggered by another `INIT` pulse.

## Technical Features

- **Reuse** of the standardized `INI` block (`eclipse4diac::storage::INI`) for file access.
- **ALR adapter interface** – allows unidirectional coupling with other blocks that use the same adapter type. This simplifies integration into modular control applications.
- **Asynchronous processing**: Read and write operations are event-driven and performed asynchronously. Acknowledgement is provided via the corresponding event outputs.
- **Compliant with IEC 61499-2 standard** – all inputs and outputs are defined with standard types.
- **Error handling** is provided via the STATUS output (e.g., for missing files or corrupted data).

## State Overview

The `INI_ALR` itself does not have its own state machines. State management is fully implemented by the internal `INI` block. Typical phases are:

- **Idle** – Waiting for an INIT event.
- **Initialize** – Processing of INIT, forwarding data to `INI`.
- **Ready** – A read result is available after successful INIT acknowledgment.
- **Write Operation** – triggered by `ALR_IN.E1`.
- **Error State** – in case of faulty INI accesses, STATUS is set accordingly.

## Application Scenarios

- **Machine Configuration** – Loading parameters (e.g., maximum speed, limits) from a central INI configuration file.
- **Calibration Values** – Storing and reading calibration data in automation technology.
- **Interface to ALR-based Components** – If a function block provides or expects an LREAL value via an ALR adapter, `INI_ALR` can be used as a link for persistent storage.

## Comparison with Similar Function Blocks

| Function Block | Description | Advantage of INI_ALR |
|------------|-------------------------------------------------------------------|-------------------------------------------------|
| `INI` | Direct access to INI files (without ALR) | No adapter interface, manual coupling required |
| `INI_ALR` | Encapsulates `INI` and provides an ALR adapter interface | Easy integration into ALR-based architectures |

The `INI_ALR` combines the proven INI file functionality with a standardized adapter interface, thereby reducing the effort required for integration into a service-oriented control system.

## Conclusion

The `INI_ALR` is a practical function block that extends access to `settings.ini` for LREAL data with a flexible adapter interface. It is particularly suitable for applications that require consistent ALR-based communication while also needing simple, file-based persistence. By encapsulating the complex `INI`The use of modular components and the automatic chaining of event and data flows reduces development effort and increases reusability.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
