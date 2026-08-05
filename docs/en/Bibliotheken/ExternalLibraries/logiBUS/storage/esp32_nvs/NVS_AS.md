# NVS_AS
![NVS_AS](./NVS_AS.svg)
* * * * * * * * * *
## Introduction
The function block **NVS_AS** serves as an interface for reading and writing SINT (signed integer) data in non-volatile storage (NVS). Storage is performed using a user-defined key (KEY). The block extends access to the NVS with an adapter interface (unidirectional AS type), allowing values to be received and sent via standardized adapter connections. This enables modular and reusable connectivity to storage functions in IEC 61499 applications.
## Interface Structure

### **Event Inputs**

| Event | Description | Associated Variables |

|----------|---------------|-----------------------|

| INIT | Initializes the NVS and triggers the first loading of a stored value. | QI, KEY, DEFAULT_VALUE |

### **Event Outputs**

| Event | Description | Associated Variables |

|----------|---------------|-----------------------|

| INITO | Confirmation of initialization and the first loading process. | QO, STATUS |

### **Data Inputs**

| Variable | Type | Description |

|----------|--------|--------------|

| QI | BOOL | Enables initialization (TRUE = enable). |

| KEY | STRING | Key under which the value is stored in the NVS. |

| DEFAULT_VALUE | SINT | Default value, read if no value exists under the key. |

### **Data Outputs**

| Variable | Type | Description |

|----------|--------|--------------|

| QO | BOOL | Confirms successful initialization and operational readiness. |

| STATUS | STRING | Status message (e.g., "Success" or error message). |

### **Adapters**

| Adapter | Type | Direction | Description |

|-----------|----------|-----------|-------------|

| AS_IN | AS | SOCKET | Receives a SINT value to be stored via a unidirectional adapter protocol (Event + Data). |

| AS_OUT | AS | PLUG | Sends the read SINT value to connected blocks via a unidirectional adapter protocol. |

## Functionality
The **NVS_AS** block encapsulates an instance of the **NVS** block (from the `logiBUS::storage::esp32_nvs` library). The function operates in two modes:

1. **Initialization and First Read Operation**

After an INIT event, the internal NVS block is initialized. Immediately afterward (automatic chaining of `INITO` to `GET`), the value stored under the specified KEY is read. If no value exists, `DEFAULT_VALUE` is returned. The read or specified value is sent to downstream function blocks via the **AS_OUT** adapter (event `E1` and data `D1`).

2. **Writing and Reading via Adapters**

- An event (`E1`) with an associated data value (`D1`) received via the **AS_IN** adapter triggers a **SET** operation in the NVS. The value is stored under the KEY specified during INIT.
- After a successful SET, the stored value is automatically output via **AS_OUT** (through the connection between `NVS.SETO` and `AS_OUT.E1`).
- Similarly, a reread can be triggered by an INIT event or by the internal process after a successful SET. A separate external read event is not provided; the value is always updated after a change or during initialization.

The function block therefore operates as a **read and write memory access with automatic feedback of the current value**.

## Technical Features
- **Adapter-Based Input/Output**

The use of unidirectional AS adapters allows for loose coupling: **AS_IN** receives write requests, **AS_OUT** outputs the stored value. This corresponds to a publisher/subscriber or client/server pattern at the adapter level.

- **Automatic Initialization**

After the INIT event, a GET request is executed immediately, so the function block provides the current or default value immediately after initialization.

- **Type Restriction to SINT**

The function block stores and loads only SINT values. Separate versions are required for other data types (e.g., INT, REAL, STRING).

- **Error Handling**

Errors during NVS operations (e.g., invalid key, memory error) are output as an error message via the STATUS output, and QO is set to FALSE.

## State Overview
The internal NVS module has its own state machine. The following processes are relevant for the user:

| Phase | State |

|-------|---------|

| 1 | Waiting for INIT event. |

| 2 | INIT executed → NVS initialized → GET started. |

| 3 | GET completed → Value sent via AS_OUT → Ready for write operations via AS_IN. |

| 4 | Event via AS_IN → SET executed → Value saved → Value sent via AS_OUT → Return to Phase 3. |

A new INIT event can force a re-initialization at any time.

## Application Scenarios
- **Persistent Device Parameters**

Storing configuration values (e.g., brightness, delay time) in the non-volatile memory of an ESP32, automatically loading them on restart.

- **State Markers for Automation**

Remembering the last state (e.g., counter reading, production parameters) even after a power failure.

- **Adapter-Based Data Nodes**

Integration into a chain of adapters where one module sets values and another reads them.

## Comparison with Similar Modules
- **NVS (Direct)**

The `NVS` module offers the same functionality, but without an adapter interface. It requires separate event and data lines. `NVS_AS` simplifies integration into adapter-oriented architectures.

- **NVS_AS_REAL, NVS_AS_STRING**

Analogous modules for other data types. The interface and behavior are identical; only the data type varies.

- **Retain Values**

In some systems, retain variables are also persistent. `NVS_AS` relies on low-level NVS (e.g., on ESP32) and is therefore platform-specific, but offers higher performance and optimized capacity.

## Conclusion
The **NVS_AS** function block provides a practical, adapter-based encapsulation of non-volatile memory for SINT values. By combining initialization logic, automatic value feedback, and an adapter interface, it is ideally suited for modular IEC 61499 projects that require persistent storage with minimal wiring. The limitation to the SINT type and the automatic GET post-initialization should be noted, but simultaneously simplify handling in many standard applications.

# Conclusion ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)
