# OUT_ANY_CONSOLE

![OUT_ANY_CONSOLE](https://user-images.githubusercontent.com/116869307/214155060-5060da47-97f7-475f-9a49-036c24119346.png)

* * * * * * * * * *

## Introduction
The **OUT_ANY_CONSOLE** function block is a universal debugging tool for outputting variable values to the system console, developed under the EPL 2.0 license (version 3.0).

The block supports outputting any data type for development and diagnostic purposes.


![OUT_ANY_CONSOLE](OUT_ANY_CONSOLE.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Trigger for console output (with qualifier `QI`, value `IN`, and optional `LABEL`)

### **Event Outputs**

- `CNF`: Acknowledgement of the output operation

### **Data Inputs**

| Parameter | Type | Description |

|-----------|-----|--------------|

| `QI` | BOOL | Enables output when TRUE |

| `LABEL` | STRING | Optional description text |

| `IN` | ANY | Any value to be output |

### **Data Outputs**

| Parameter | Type | Description |

|-----------|-----|--------------|

| `QO` | BOOL | Confirms successful output |


## Functionality

1. **Triggering**:

- The `REQ` event with `QI`=TRUE starts output

- The combination of `LABEL` and `IN` is formatted

2. **Execution**:

- The value is written to standard output

- Automatic type conversion for `ANY`

3. **Confirmation**:

- `CNF` with `QO`=TRUE on success

- `CNF` with `QO`=FALSE on errors

## Technical Features

✔ **Universal Type Support** (ANY data type)
✔ **Flexible labeling** with LABEL parameters
✔ **Eclipse 4diac integration** (Package: eclipse4diac::utils)
✔ **Platform-independent** for various target systems

## Application Scenarios

- **Debugging**: Runtime variable inspection
- **Logging**: Event tracking
- **System diagnostics**: Condition monitoring
- **Development**: Rapid algorithm testing

## Example outputs

| LABEL | IN (value) | Console output |

|-------|----------|-----------------|

| "Temperature" | 23.5 | "Temperature: 23.5" |

| "Status" | TRUE | "Status: TRUE" |

| "" | 42 | "42" |

## ⚖️ Comparison with similar building blocks

| Feature | OUT_ANY_CONSOLE | Standard debugging | Extended logging |

|---------|-----------------|----------------|---------------------|

| Data types | Any | Limited | Limited |

| Labeling | Optional | No | Yes |

| Integration | 4diac-specific | System-dependent | Framework-dependent |

| Real-time capable | Yes | Partially | No |


## Conclusion

The OUT_ANY_CONSOLE block is an indispensable tool for development:

- **Flexible**: Supports all data types
- **Easy**: Quick integration into existing systems
- **Powerful**: Suitable for real-time debugging

Ideal for:

- Prototype development
- System testing
- Error analysis
- Live diagnostics

*The Swiss Army knife for developers in Eclipse 4diac environments*

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]