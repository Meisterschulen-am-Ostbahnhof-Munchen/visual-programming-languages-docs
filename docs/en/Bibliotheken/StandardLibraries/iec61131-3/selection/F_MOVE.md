# F_MOVE

![F_MOVE](https://github.com/user-attachments/assets/16aaf0c8-4559-4366-be56-14f0db433d33)

* * * * * * * * * *

![F_MOVE](F_MOVE.svg)

## Introduction
The **F_MOVE** is a universal function block for type-safe data transfer, developed under the EPL-2.0 license. Version 1.0 enables the transfer of any data type (ANY) between variables in control applications.


## Interface Structure

### **Event Inputs**
- `REQ`: Transfer request (with input value)

### **Event Outputs**
- `CNF`: Transfer acknowledgment (with output value)

### **Data Inputs**
- `IN` (ANY): Source data (any type)

#### **Data Outputs**
- `OUT` (ANY): Destination data (identical type to input)

## Functionality

1. **Activation**:

- Triggered by the `REQ` event

- Processes any data type (ANY)

2. **Data Transfer**:

- 1:1 copy of the input value

- Type-preserving transfer

- Supports all IEC 61131-3 Data Types

3. **Confirmation**:

- `CNF` event after successful transfer

- OUT receives an exact copy of IN

## Technical Specifications

✔ **Generic Type Support** (ANY)
✔ **Bit-perfect data copy**
✔ **One-cycle latency**
✔ **IEC 61131-3 compliant**

## Application Examples

- **Data Conversion**: Type conversions
- **Signal Forwarding**: Process data distribution
- **Buffer Operations**: Intermediate storage
- **Interfaces**: Data encapsulation

## Special Notes

- **Type Compatibility**:

- Input and output types must be identical

- No automatic type conversion

- **Performance**:

- Consistently fast execution

- Independent of data type

## ⚖️ Comparison with similar function blocks

| Feature | F_MOVE | F_BLOCK_MOVE | F_CAST |

----------------|---------|--------------|--------|

| Functionality | Single Value | Memory Block | Type Conversion |

| Type Support | ANY | BYTE Array | ANY |

| Latency | 1 Cycle | Variable | 1 Cycle |


## 🛠️ Related Exercises

* [Exercise_002b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b2.md)]
* [Exercise_103c](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c.md)]
* [Exercise_110](../../../../Uebungen/test_B/Uebungen_doc/Uebung_110.md)]
* [Exercise_111](../../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)]
* [Exercise_171](../../../../Uebungen/test_B/Uebungen_doc/Uebung_171.md)]

## Conclusion

The F_MOVE block offers essential data transfer functions:

- Universal type support
- Reliable 1:1 data copying
- Minimal resource consumption

Indispensable for control applications with complex data structures or type-sensitive operations. The generic implementation as GEN_FORTE_F_MOVE enables maximum flexibility in heterogeneous automation environments.