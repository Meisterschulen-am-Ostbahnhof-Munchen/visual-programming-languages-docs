# Q_ActiveMask
![Q_ActiveMask](https://user-images.githubusercontent.com/69573151/212328886-4d5587f1-b2cd-4e8a-9cbe-0aa55ca1abcf.png)
* * * * * * * * * *
## Introduction
The **Q_ActiveMask** is a standards-compliant function block for controlling active masks in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.34) specification for agricultural tax systems.
![Q_ActiveMask](Q_ActiveMask.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request
- `REQ`: Screen Change Request (with parameters)

### **Event Outputs**
- `INITO`: Initialization Confirmation
- `CNF`: Screen Change Confirmation (with result data)

### **Data Inputs**
- `u16NewMaskId` (UINT): Object ID of the new screen

!!! Note: "WorkingSet Object ID fixed to 0"

The **WorkingSet Object ID** (`u16WorkSetId`) is **fixed to 0** by the authors of [logiBUS®](https://www.logibus.tech/)]. The user must ensure that the WorkingSet object in the object pool always has Object ID 0. This is the default setting in most tools:

- [ISO-Designer](https://www.bucherautomation.com/iso-designer/sw10133) from Bucher Automation AG
- [Isobus Studio](https://isobus-studio.com/) from [to-the-future / Tobias Tenberg](https://www.to-the-future.de/)]

Since the working set is a single object and only exists once, this limitation is not a problem.

### **Data Outputs**
- `STATUS` (STRING): Operating status message
- `u16OldMaskId` (UINT): Object ID of the previous screen
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` event starts the function block
- `INITO` confirms successful setup

2. **Mask Change**:

- Trigger `REQ` with new mask parameters
- Return `CNF` result and previous mask ID

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.34)

✔ **Deterministic** behavior
✔ **Multi-client capable** architecture
✔ **Real-time capable** execution

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-----------|-----------|

| 0 | VT_E_NO_ERR | Success |

| -6 | VT_E_OVERFLOW | Buffer Overflow |

-8 | VT_E_NOACT | Invalid State |

-21 | VT_E_NO_INSTANCE | No VT Instance |

## Application Scenarios
- **Tractor Controls**: Operating Mode Switching
- **Harvest Monitoring**: Data Acquisition Masks
- **Diagnostic Systems**: Fault Display Masks
- **Multi-Terminal Operation**: Synchronized Displays

## ⚖️ Comparison with Similar Function Blocks

| Feature | Q_ActiveMask | VtMaskManager | VtDynamicDisplay |

---------------|---------------|---------------|------------------|

| ISO Standard | ✔ | ✖ | ✖ |

Error Codes | Standard | Manufacturer | Partial |

Condition Management | Full | Basic | Advanced |

``` ## 🛠️ Related Exercises

* [Exercise_019](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019.md)]
* [Exercise_019a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019a.md)]
* [Exercise_019b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019b.md)]
* [Exercise_019c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)]

## Conclusion

The Q_ActiveMask block provides the reference implementation for ISOBUS mask switching:

- **Standard-compliant**: Full ISO 11783-6 compatibility
- **Robust**: Proven technology in series production
- **Flexible**: Supports complex display scenarios

Essential for:

- Manufacturers of ISOBUS terminals
- Developers of agricultural control units
- System integrators in agricultural technology