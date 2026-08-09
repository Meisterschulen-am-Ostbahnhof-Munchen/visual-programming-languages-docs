# Q_Attribute_AUDI

![Q_Attribute_AUDI](./Q_Attribute_AUDI.svg)

* * * * * * * * * *
## Introduction

The function block **Q_Attribute_AUDI** implements the "Change Attribute" command of the ISOBUS standard ISO 11783-6 (Part 6 – F.38). It allows you to change an attribute of an object that is identified by a unique attribute ID (AID). The block supports passing the new attribute value via an adapter interface and returns the old value via an adapter as well. String attributes cannot be changed with this command.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-----|---------------|
| INIT | EInit | Initializes the service and starts communication with the ISOBUS VT |

### **Event Outputs**

| Event | Type | Description |
|----------|-----|--------------|
| INITO | EInit | Confirms successful completion of initialization |
| CNF | Event | Confirms execution of the requested attribute change command |

### **Data Inputs**

| Variable | Type | Description |
|---------------|-------|--------------|
| u16ObjId | UINT | Object ID of the attribute to be changed (initial value: ID_NULL) |
| u8IdAttribute | USINT | Attribute ID (AID) – defines which attribute of the object is to be changed |

### **Data Outputs**

| Variable | Type | Description |
|------------|--------|--------------|
| STATUS | STRING | Status message of the executed service |
| s16result | INT | Return value of the command (error codes, see Functionality) |

### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| u32ValueAttribute | Socket | unidirectional::AUDI | New value for the attribute (32-bit, fed into the FB via the adapter) |
| u32OldValueAttribute | Plug | unidirectional::AUDI | Old attribute value (32-bit, output by the function block via the adapter) |

## Functionality

1. **Initialization**: After a rising edge at **INIT**, the service is initialized. The required parameters (object ID and attribute ID) are read from the data inputs.
2. **Command Execution**: As soon as the event output **E1** is triggered at socket **u32ValueAttribute** (e.g., by a connected function block providing a new value), the attribute change command is started. The new attribute value is adopted by the adapter.
3. **Feedback**: After the command is completed, the output **CNF** is activated. The STATU string and the return value **s16result** contain the result. Simultaneously, the previously stored old attribute value is signaled at plug **u32OldValueAttribute** via the event output **E1** and made available via **D1**.

The function block delegates the actual ISOBUS communication to the internal function block **Q_Attribute**, which performs the necessary protocol steps.

## Technical Features

- **Error Codes** (output via s16result):
- `VT_E_NO_ERR (0)` – no error
- `VT_E_OVERFLOW (-6)` – buffer overflow
- `VT_E_NOACT (-8)` – command not possible in the current state
- `VT_E_NO_INSTANCE (-21)` – no VT client instance available
- `VT_E_ISO_INSTANCE_INVALID (-129)` – invalid connection instance
- `VT_E_NOT_ALIVE (-130)` – instance valid, but VT not active
- **Adapter Interfaces**: The use of unidirectional adapters (AUDI) enables loose coupling between the encoder and the function block. The old and new values can thus be managed in separate function blocks (FBs).
- **Limitations**: The command does not support string attributes.

## State Overview

The FB does not have an explicitly displayed state machine. The sequence control is event-driven:

- After **INIT**, it transitions to a ready state.
- Another event is only triggered by the connected adapter socket (E1 of u32ValueAttribute). After processing, **CNF** is sent.
- The function block is **stateless** in the sense of a reusable sequence; each request is processed individually.

## Application Scenarios

- **ISOBUS VT Applications**: Changing parameters of a virtual terminal (e.g., background color, label, visibility) at runtime.
- **Control of Agricultural Equipment**: Dynamically adjusting attributes such as machine settings or diagnostic data.
- **Implementation of ISO 11783-6 Workouts**: Replicating the "Change Attribute" command structure from the standard.

## Comparison with Similar Function Blocks

- **Q_Attribute** (without AUDI): Offers the same core functionality, but without adapter interfaces. The new value must be passed directly as a data input, and no feedback of the old value is provided. **Q_Attribute_AUDI** extends this function block with flexible, adapter-based value passing and the return of the old value, increasing reusability and encapsulation.

## Conclusion

**Q_Attribute_AUDI** is a specialized function block for ISOBUS applications that enables the secure and standards-compliant modification of attributes. The adapter-based interface for attribute values ensures high modularity, and the output of the old value allows for easy change tracking. The function block is ideal for complex VT implementations where values originate from different sources or are managed in separate logic units.
