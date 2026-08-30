# INI_AB2

![INI_AB2](./INI_AB2.svg)

* * * * * * * * * *

## Introduction

The function block `INI_AB2` is used to read and write REAL values to or from a `settings.ini` file. Access is via a combination of section name and key name. Communication with external systems is via a bidirectional **AB2 adapter**, which allows values from the INI file to be passed to other function blocks or values from other function blocks to be received and stored in the file. The function block was developed according to the IEC 61499-2 standard.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-----|---------------|
| INIT | EInit | Initialization event; starts the read or write operation depending on the connected adapter logic. The data passed specifies the section, key, and a default value. |

### **Event Outputs**

| Event | Type | Description |
|----------|-----|--------------|
| INITO | EInit | Initialization confirmation. Triggered after the read/write access is complete. |

### **Data Inputs**

| Variable | Type | Description |
| ---------- | ----- | -------------- |
| QI | BOOL | Qualifier for the event input; controls its execution. |
| SECTION | STRING | Name of the section in `settings.ini`. |
| KEY | STRING | Name of the key within the section. |
| DEFAULT_VALUE | REAL | The value returned if the key does not exist in `settings.ini`. |

### **Data Outputs**

| Variable | Type | Description |
|----------|-----|--------------|
| QO | BOOL | Output qualifier; indicates successful execution. |
| STATUS | STRING | Service status message (e.g., error messages or "OK"). |

### **Adapters**

| Adapter | Type | Description |
|---------|-----|--------------|
| VAL | adapter::types::bidirectional::AB2 | Bidirectional adapter for exchanging real values. The incoming value (`DO1`) is written to the INI file; the outgoing value (`DI1`) is read from the INI file and passed on. |

## Functionality

The `INI_AB2` block internally contains an instance of the function block `eclipse4diac::storage::INI`. Communication with `settings.ini` occurs exclusively via this internal instance.

1. **Initialization (Read Operation):** An INIT event at the input sets the internal parameters (Section, Key, Default Value) and activates the internal INI instance (`INI.INIT`). After successful reading, the read value is sent to the connected module via the adapter output (`VAL.DI1`). Simultaneously, outputs `INITO`, `QO`, and `STATUS` are updated.
2. **Write Operation:** The connected module can provide a new value via the adapter input (`VAL.DO1`). As soon as the event `VAL.EO1` arrives, the value is saved in the INI instance (`INI.SET`). The confirmation (`INI.SETO`) is returned to the adapter via `VAL.EI1`.
3. **Write Operation:** The connected module can provide a new value via the adapter input (`VAL.DO1`). 3. **Cyclic Reading:** After each INIT operation, the internal GET command is automatically triggered, allowing the current value to be read from the file and output via the adapter.

The circuitry ensures that both read and write accesses can be handled bidirectionally via the adapter. The module thus implements persistent data storage with external control.

## Technical Features

- **Bidirectional Adapter Connection:** The AB2 adapter allows both reading and writing to the INI file via a single connection.
- **Default Value:** If a specified key is not present in `settings.ini`, the value passed via `DEFAULT_VALUE` is used and output as the read value.
- **Use of `eclipse4diac::storage::INI`:** The function block encapsulates the actual INI access logic and provides robust error handling (status output).
- **IEC 61499-2 compliant:** The function block adheres to the standard for function blocks, which increases interoperability and reusability.

## State Overview

The `INI_AB2` function block itself does not have explicit states (no ECC states), as the logic is fully implemented through the internal INI instance and the event/data flows. However, the interaction can be described as a simple sequential process:

1. **Idle State** – Waiting for INIT or data from the adapter.
2. **Initialize** – INIT is processed, the internal INI is started.
3. **Read** – The INI reads the value and outputs it via the adapter.
4. **Write** – Value from the adapter is saved to the INI file.
5. **Return** – Confirmation via INITO or adapter event.

## Application Scenarios

- **Configuration Management:** Saving and retrieving machine parameters (e.g., setpoint temperatures, limit values) in a central `settings.ini` file.
- **Plant Parameterization:** Multiple control components access the same INI file via the AB2 adapter and can thus exchange parameters.
- **Data Exchange Between Heterogeneous Systems:** The standardized adapter enables integration into any 4diac architecture.

## Comparison with Similar Function Blocks

- **INI_AB (Unidirectional):** Uses a unidirectional adapter that allows either read-only or write-only access. `INI_AB2` is more flexible due to its bidirectional interface.
- **INI_CFB (Composite FB):** A similar function block without an adapter, addressed directly via events and data. `INI_AB2` abstracts the connection and enables modular coupling.
- **eclipse4diac::storage::INI (direct):** The basic function block does not offer an adapter interface; `INI_AB2` encapsulates this and adds bidirectional communication.

## Conclusion

The `INI_AB2` function block is a practical extension for IEC 61499-based automation solutions. It simplifies access to INI configuration files through a standardized adapter interface and enables both read and write operations. Its ease of use and clear separation of logic and interface make it a useful tool for modular and reusable control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
