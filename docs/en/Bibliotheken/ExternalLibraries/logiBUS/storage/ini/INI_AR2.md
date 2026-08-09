# INI_AR2

![INI_AR2](./INI_AR2.svg)

* * * * * * * * * *
## Introduction

The INI_AR2 function block is used to read and write real values to and from a settings.ini file using a section and key name. It encapsulates an INI function block and provides a bidirectional AR2 adapter interface. Upon initialization, the value for the specified section and key name is read and output via the adapter. Simultaneously, new values can be received via the adapter and written back to the file.
## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Service initialization. Triggers the loading of the value from settings.ini and initializes the function block.

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation. Sent after successful processing of the INIT event.

### **Data Inputs**

- **QI** (BOOL): Input qualifier. Controls execution (e.g., activation/deactivation).
- **SECTION** (STRING): Section name in the settings.ini file (e.g., "[MySection]").
- **KEY** (STRING): Key name in the section (e.g., "MyKey").
- **DEFAULT_VALUE** (REAL): Default value returned if the key is not present in the file.

### **Data Outputs**

- **QO** (BOOL): Output qualifier. Indicates the processing status.
- **STATUS** (STRING): Service status message (e.g., error message or "OK").

### **Adapters**

- **VAL** (AR2): Bidirectional adapter of type `adapter::types::bidirectional::AR2`. This adapter provides the read values (output) and receives new values (input) for writing back to the INI file. The adapter has the events EO1 (output) and EI1 (input) as well as data DO1 (output) and DI1 (input).

## Functionality

The FB INI_AR2 is a composite function block that internally uses an INI function block (`eclipse4diac::storage::INI`). The process is as follows:

1. **Initialization**: Upon arrival of the INIT event, the parameters QI, SECTION, KEY, and DEFAULT_VALUE are passed to the internal INI block.
2. **Reading**: After INIT, the INI block automatically performs a GET operation (controlled by the event connection from INI.INITO to INI.GET). It reads the value from the settings.ini file for the specified section and key. If no entry exists, the DEFAULT_VALUE is used.
3. **Output via Adapter**: The read value is passed to the adapter output via the data connection INI.VALUEO -> VAL.DI1 and the event INI.GETO -> VAL.EI1.
4. **Write via Adapter**: When a new value arrives at VAL.DO1 via the adapter (triggered by VAL.EO1), the event VAL.EO1 -> INI.SET is sent. The INI block then writes the new value back to the file. After writing, INI.SETO -> VAL.EI1 is sent, which returns the acknowledgment to the adapter.
5. **Completion**: After the initial read operation, the INITO event is output, along with the status information QO and STATUS. After write operations via the adapter, no INITO is sent, only an acknowledgment via VAL.EI1.

## Technical Features

- The function block uses the Eclipse 4diac infrastructure and imports types from `eclipse4diac::storage` and `adapter::types::bidirectional::AR2`.
- The AR2 adapter enables a clear separation between read and write accesses via a single adapter socket.
- By default, the file `settings.ini` is expected in the application's working directory. The exact path can be adjusted via the INI block configuration (not directly visible in INI_AR2).
- The function block is designed for REAL data; corresponding variants would need to be created for other data types.
- Error handling is handled via the STATUS output and QO.
- The INITO event is only triggered after the initial read operation, not after write operations via the adapter. Write operations are only acknowledged via the adapter.
-
## State Overview

Since this is a composite function block, there is no explicit internal state machine. The process is determined by the event network:

- Receive INIT → Execute INI.INIT.
- After INI.INITO: Execute INI.GET automatically.
- After INI.GETO: Trigger VAL.EI1 (value output) and send INITO.
- Upon receiving VAL.EO1 (new value from an external source): Execute INI.SET, then INI.SETO → VAL.EI1 (acknowledgment to the adapter, no INITO).

## Application Scenarios

- **Parameter Management**: Saving and loading settings (e.g., PID controller parameters, setpoints) from a configuration file.
- **Initial Configuration**: When an application starts, predefined values are loaded from the settings.ini file.
- **Online Parameterization**: New values can be written at runtime via the AR2 adapter using an HMI or a control system. The block immediately saves and confirms these values in the file.
- **Redundancy**: If no file exists, the DEFAULT_VALUE is used, allowing the application to start even without configuration.

## Comparison with Similar Blocks

- **INI (eclipse4diac::storage::INI)**: The INI_AR2 extends the basic INI block with an adapter interface, making it easier to integrate into a higher-level structure. The standard INI block requires separate event connections for reading and writing; INI_AR2 simplifies this with its bidirectional adapter.
- Other storage blocks (e.g., for databases or OPC UA): INI_AR2 is limited to simple INI files but is very lightweight and has no additional runtime dependencies.

## Conclusion

The INI_AR2 function block offers a compact and easy-to-integrate solution for persistently storing and loading REAL configuration values. Using an AR2 adapter standardizes the connection to other components. This block is particularly suitable for embedded controllers with low data storage requirements, where a single INI file is sufficient.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
