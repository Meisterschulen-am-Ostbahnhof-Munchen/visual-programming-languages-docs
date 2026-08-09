# Q_NumericValue

![Q_NumericValue](https://user-images.githubusercontent.com/113907471/204326982-47eea33a-9b9c-4107-8f96-97c85a945fbc.png)

* * * * * * * * * *
## Introduction

The **Q_NumericValue** is a standards-compliant function block for changing numeric values in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.22) specification for numeric VT objects.
![Q_NumericValue](Q_NumericValue.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Value Change Request

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**

- `u16ObjId` (UINT): Object ID (16-bit)
- `u32NewValue` (UDINT): New Numeric Value (32-bit unsigned)

### **Data Outputs**

- `STATUS` (STRING): Operational Status Message
- `u32OldValue` (UDINT): Previous numeric value
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

**`u16ObjId` — valid object types (Annex F.22, objects with numeric value attribute):**
Input Boolean Field (7000–7999), Input Number Field (9000–9999), Input List Field (10000–10999), Output Number Field (12000–12999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Number Variable (21000–21999), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999).

ID_NULL (65535) is not a command target but deactivates the FB when used with `INIT`. Any ID outside these ranges is invalid for commanding.

## Functionality

1. **Initialization**:
- `INIT` with target object ID
- `INITO` confirms operational readiness
2. **Value Update**:
- `REQ` with new 32-bit value
- Updates the numeric VT object
- `CNF` returns operational status and previous value
3. **Value Range**:
- 0 to 4,294,967,295 (32-bit unsigned)

## Technical Features

✔ **ISO 11783-6 compliant** (F.22)

✔ **32-bit value range** (UDINT)

✔ **Instant update**

✔ **Traceability** (Previous value)

✔ **Internal buffering**: The function block buffers the value internally. A message is only sent to the bus if `u32NewValue` differs from `u32OldValue`. This significantly reduces the bus load and tolerates frequent REQ events.

## Value range

| Parameter | Type | Value range |
|-------------|-----------|-----------------------|
| u32NewValue | UDINT | 0 to 4,294,967,295 |

## Return codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful change |
| -6 | VT_E_OVERFLOW | Buffer overflow |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -128 | VT_E_HANDLE_INVALID | Invalid object ID |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Process Visualization**: Real-time Measurement Data
- **Control Elements**: Setpoint Specifications
- **Diagnostic Systems**: Error Code Display
- **Production Data**: Counters and Statistics

## ⚖️ Comparison with Similar Function Blocks

| Feature | Q_NumericValue | VtNumberUpdate | VtDataManager |
---------------|----------------|----------------|---------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Value Range | 32-bit | 16-bit | 32-bit |
| Feedback | ✔ | ✖ | ✔ |
| Object Type | Numeric | All | All |

## 🛠️ Related exercises

* [Uebung_009](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_009.md)
* [Uebung_009a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_009a.md)
* [Uebung_011a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011a.md)
* [Uebung_011a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011a2.md)
* [Uebung_012](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012.md)
* [Uebung_012a_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012a_sub.md)
* [Uebung_012b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012b.md)
* [Uebung_015](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_015.md)
* [Uebung_015a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_015a.md)
* [Uebung_020c2_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2_sub.md)
* [Uebung_035](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035.md)
* [Uebung_035b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035b.md)
* [Uebung_035c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035c.md)
* [Uebung_036](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_036.md)
* [Uebung_037](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_037.md)
* [Uebung_038](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_038.md)
* [Uebung_038_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_038_AX.md)
* [Uebung_039_sub_NumbAnsicht](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_039_sub_NumbAnzeig.md)
* [Uebung_040](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_040.md)
* [Uebung_040_2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_040_2.md)
* [Uebung_040_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_040_AX.md)
* [Uebung_041](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_041.md)
* [Uebung_070](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_070.md)
* [Uebung_071](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_071.md)
* [Uebung_071a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_071a.md)
* [Uebung_071b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_071b.md)
* [Uebung_072](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072.md)
* [Exercise_072b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072b.md)
* [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)
* [Exercise_073](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_073.md)
* [Exercise_074](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_074.md)
* [Exercise_083](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_083.md)

## Conclusion

The Q_NumericValue block offers precise numerical control:

- **High-resolution**: 32-bit precision
- **Reliable**: Integrated error checking
- **Flexible**: For all numerical objects

Essential for:

- Precise process visualization
- Real-time data monitoring
- Industrial control systems

## Example applications

[Q_NumericValue_examples](Q_NumericValue_beispiele.md)]
