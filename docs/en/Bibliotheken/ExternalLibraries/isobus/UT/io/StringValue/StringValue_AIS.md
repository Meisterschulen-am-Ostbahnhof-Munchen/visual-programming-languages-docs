# StringValue_AIS
![StringValue_AIS](./StringValue_AIS.svg)

* * * * * * * * * *
## Introduction
The **StringValue_AIS** function block is a service interface function block for providing string input data. It serves as an interface between an external resource (e.g., ISOBUS Universal Terminal) and the control logic. The block initializes communication, processes requests, and passes status information to the application.
## Interface Structure
### **Event Inputs**

| Event | Type | With Variables | Description |
|----------|-----|----------------|--------------|
| INIT | EInit | QI, PARAMS, u16ObjId | Initializes the service and passes qualifiers, parameters, and object IDs. |
| REQ | Event | QI | Requests a data query or processing. |

### **Event Outputs**

| Event | Type | With Variables | Description |
|----------|-----|----------------|--------------|
| INITO | EInit | QO, STATUS | Confirms initialization and provides status information. |

### **Data Inputs**

| Variable | Type | Initial Value | Description |
|----------|-----|--------------|--------------|
| QI | BOOL | – | Qualifier for events (TRUE = active). |
| PARAMS | STRING | – | Service parameters (e.g., configuration data). |
| u16ObjId | UINT | ID_NULL | Object ID referenced in the log. |

### **Data Outputs**

| Variable | Type | Description |
|----------|-----|--------------|
| QO | BOOL | Output qualifier (service acknowledgment). |
| STATUS | STRING | Service status message (e.g., error message or success message). |

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|-----------|--------------|
| IN | adapter::types::unidirectional::AIS | Input | Unidirectional adapter for data exchange with an external resource (e.g., a hardware interface).

## Functionality
The **StringValue_AIS** block encapsulates an internal service block **StringValue_IS** and controls its event and data flows. Upon an INIT event, the input parameters (QI, PARAMS, u16ObjId) are forwarded to the internal block, which initializes the communication. The INITO event output signals success (QO, STATUS).

A REQ event triggers a further query—the internal block sends the request (e.g., reading a string value) to the external resource via the **IN** adapter. The response is received asynchronously via the adapter (IND or CNF event) and returned as a STATUS/QO output.

The connections are hard-coded in the FB network:

- **INIT** and **REQ** are routed to the internal function block **StringValue_IS**.
- The response events **IND** and **CNF** of the internal function block are routed to the adapter output **IN.E1**.
- The data lines **QI**, **PARAMS**, and **u16ObjId** feed the internal function block, while **IN.D1** (from the adapter) and **STATUS**/**QO** are passed to the outputs of the function block.

## Technical Features
- The function block is designed as a **Service Interface Function Block (SIFB)** and is suitable for integration into an ISOBUS-compliant control environment.
- The interface uses a **unidirectional adapter (AIS)**, which transmits data exclusively from the resource to the controller.
- The initial value of `u16ObjId` is set to `ID_NULL` – a placeholder that must be replaced with a valid object ID during the initialization step.
- The implementation is licensed under the **Eclipse Public License 2.0**.
- The component uses an internal type hash mechanism for integrity checking.

## State Overview
An explicit state machine is not represented in the XML. The component operates in an event-driven manner:

- **IDLE**: Waiting for INIT.
- **INIT completed**: Initialization complete, waiting for REQ.
- **IN processing**: After REQ, the request is sent to the adapter; the response is asynchronous.

The response via INITO signals the completion of initialization, while the STATUS output reflects the current state of the service.

## Application Scenarios
- **ISOBUS UT Connection**: Reading a text field (e.g., machine name, field label) from a Universal Terminal.
- **Configuration Interface**: Accepting string parameters from a higher-level control system.
- **Data Logging**: Capturing external strings (e.g., barcode scanner, serial numbers) for further processing.

## Comparison with Similar Modules
- **IntegerValue_AIS**: Similar structure, but for integer data. It differs only in the data type of the output value.
- **CommandValue_AIS**: Offers bidirectional communication (send/receive) and expects a command format.
- **StringValue_AIS** is specifically optimized for receiving strings and requires no response other than status.

## Conclusion

The **StringValue_AIS** is a specialized service interface module for receiving string data via a unidirectional adapter. It simplifies the integration of external text sources into automation systems and provides a clean separation between communication services and application logic. Thanks to its standardized interface (event/data connections), it can be flexibly integrated into 4diac IDE projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
