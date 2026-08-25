# NVS_AR

![NVS_AR](./NVS_AR.svg)

* * * * * * * * * *
## Introduction

The function block `NVS_AR` is used to load and store REAL data in non-volatile storage (NVS) using a key. It provides unidirectional communication with other IEC 61499 function blocks via two AR adapter interfaces. The block encapsulates the internal `NVS` function block and extends its functionality with a standardized adapter connection.
## Interface Structure

### **Event Inputs**

- **INIT** (EInit) – Initializes the function block. Upon this event, the data inputs `QI`, `KEY`, and `DEFAULT_VALUE` are accepted.

### **Event Outputs**

- **INITO** (EInit) – Confirms successful completion of the initialization. After this event, the outputs `QO` and `STATUS` are valid.

### **Data Inputs**

- **QI** (BOOL) – Input qualifier; controls the execution of the initialization.
- **KEY** (STRING) – Key name under which the value is stored/retrieved in the NVS.
- **DEFAULT_VALUE** (REAL) – Default value that is returned if no entry with the specified key exists in the NVS.

### **Data Outputs**

- **QO** (BOOL) – Output qualifier; indicates successful initialization.
- **STATUS** (STRING) – Status message for error diagnosis or confirmation.

### **Adapters**

- **AR_IN** (Adapter type `adapter::types::unidirectional::AR`) – Receives a value to be stored (SET event and data).
- **AR_OUT** (Adapter type `adapter::types::unidirectional::AR`) – Makes the read value available to other function blocks (GETO event and data).

## Functionality

The function block operates as follows:

1. **Initialization**: An event at `INIT` starts the initialization of the internal `NVS` function block. The inputs `QI`, `KEY`, and `DEFAULT_VALUE` are forwarded to `NVS`.
2. **After Initialization**: Once `NVS` completes initialization (event `INITO`), a **read command** (`GET`) is automatically sent to `NVS`. The read value (or the default value) is then output via the adapter output `AR_OUT`.
... 3. **Save**: An event received via the adapter input `AR_IN` (`AR_IN.E1`) triggers a **save command** (`SET`) in the internal `NVS`. The value to be saved is taken from the adapter data channel (`AR_IN.D1`).

4. **Feedback**: After both a read and a save operation, the result (success/error) is reported via the adapter event `AR_OUT.E1` and via the data outputs `QO`/`STATUS`.

## Technical Features

- The module uses the unidirectional AR adapter, which enables loose coupling between function blocks.
- It is specifically designed for REAL data; other data types cannot be processed.
- The implementation is based on the generic `NVS` block from the `logiBUS::storage::esp32_nvs` library.
- The event control ensures that the current value is automatically read from the NVS and made available after initialization.

## State Overview

The `NVS_AR` block does not have an explicit state engine in its XML definition. Its functional behavior is determined by the event chaining:

- **Idle State**: The block waits for an event on `INIT` or `AR_IN.E1`.
- **Initialization Phase**: After `INIT`, the internal `NVS` block is started. The outputs are not yet active during this phase.
- **Operation Phase**: After `INITO`, the block is ready to read values (automatically) and have them saved via `AR_IN`.

## Application Scenarios

- **Configuration Memory**: Storing and retrieving real-world configuration parameters (e.g., limits, factors) in an ESP32-NVS.
- **Calibration Data**: Storing calibration values for sensors or actuators.
- **Persistent Operational Data**: Storing count values or totals that should be retained during power outages.

## Comparison with Similar Blocks

| Feature | `NVS_AR` | Direct `NVS` block |
---------|-----------|-------------------------|
| Interface | AR adapter (unidirectional) | Standard event/data inputs |
| Intended use | Easy integration into adapter-based networks | Flexible, but more complex wiring |
| Data type | REAL | Multiple types (via generic parameter) |

The `NVS_AR` simplifies integration by standardizing the adapter connection, while the pure `NVS` block offers broader type support.

## Conclusion

The `NVS_AR` function block offers a compact, adapter-based solution for loading and storing real data in non-volatile memory. Thanks to the AR adapter, it can be easily integrated into existing IEC 61499 networks without requiring detailed connections. Automatic initial readout after initialization simplifies its use in typical real-time control scenarios.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de ](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)
