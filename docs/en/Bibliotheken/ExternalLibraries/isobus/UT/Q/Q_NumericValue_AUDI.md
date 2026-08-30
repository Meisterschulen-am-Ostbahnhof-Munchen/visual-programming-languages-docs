# Q_NumericValue_AUDI (ISOBUS Numeric Value Adapter)

## Introduction

The `Q_NumericValue_AUDI` is a special ISOBUS function block that allows numeric values (`UDINT`) to be sent from a controller to a Universal Terminal (UT) for display or modification. It uses the `AUDI` adapter for transferring new and old values, ensuring a modern and type-safe connection.
![Q_NumericValue_AUDI](Q_NumericValue_AUDI.svg)
## Interface Structure

### **Event Inputs**

- **INIT**: `EInit` - Initializes the service with `u16ObjId`.

### **Event Outputs**

- **INITO**: `EInit` - Confirms initialization.
- **CNF**: `Event` - Confirms service execution.
- Linked to variables `STATUS` and `s16result`.

### **Input Variables**

- **u16ObjId**: `UINT` - The object ID of the numeric input field on the ISOBUS terminal (default: `ID_NULL`).

### **Output Variables**

- **STATUS**: `STRING` - Service status message (e.g., "OK", "Error").
- **s16result**: `INT` - Service return value (error codes according to ISO 11783-6).

### **Adapter**

- **u32OldValue** (Plug): `AUDI` - The old/current value of the object.
- **u32NewValue** (Socket): `AUDI` - The new value to be sent to the ISOBUS terminal.

## Valid Object IDs

`u16ObjId` is valid for the same object types as the wrapped base block `Q_NumericValue` (Annex F.22, objects with numeric value attribute): Input Boolean Field (7000–7999), Input Number Field (9000–9999), Input List Field (10000–10999), Output Number Field (12000–12999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Number Variable (21000–21999), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999).

ID_NULL (65535) is not a command target but deactivates the FB when used with `INIT`.

## Functionality

The function block is initialized via the `INIT` event with the object ID `u16ObjId`. As soon as an event arrives at the `u32NewValue` socket (`u32NewValue.E1`), the contained UDINT value (`u32NewValue.D1`) is sent to the ISOBUS terminal to update the displayed numeric value. After successful execution, a `CNF` event is triggered, and the object's previous value is provided via the `u32OldValue` plug.

## Technical Features

✔ **ISO 11783-6 Standard**: Compliant implementation for ISOBUS Universal Terminals.

✔ **Adapter-based**: Uses the `AUDI` adapter for numerical values.

✔ **Asynchronous operation**: Event-driven communication.

## Application scenarios

- **Display of counter readings**: Visualization of counter readings (e.g., operating hours, quantities) on the terminal.
- **Setpoint specification**: Transfer of target values (e.g., temperature, pressure) from the ISOBUS terminal to the controller (in combination with a NumericValue_IDA input block).
- **Feedback systems**: Display of process values in real time.

## 🛠️ Related exercises

- [Exercise_009_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_009_AX.md)
- [Exercise_083_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_083_AX.md)
