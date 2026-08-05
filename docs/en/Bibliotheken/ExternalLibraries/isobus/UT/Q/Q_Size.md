# Q_Size

![Q_Size](https://user-images.githubusercontent.com/116869307/214153095-72c9e230-b193-4843-be85-33038f6bd44d.png)

* * * * * * * * * *

## Introduction
The **Q_Size** is a standards-compliant function block for resizing objects in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.18) specification for VT objects.


![Q_Size](Q_Size.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with object ID)
- `REQ`: Resize request

### **Event Outputs**
- `INITO`: Initialization acknowledgment
- `CNF`: Resize acknowledgment

### **Data Inputs**
- `u16ObjId` (UINT): Object ID (16-bit)
- `u16Width` (UINT): New width in pixels
- `u16Height` (UINT): New height in pixels

### **Data Outputs**
- `STATUS` (STRING): Operational status message

- `u16OldWidth` (UINT): Previous width
- `u16OldHeight` (UINT): Previous height
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with target object ID

- `INITO` confirms operational readiness

2. **Resize**:

- `REQ` with new dimensions

- Dynamically adjusts the object geometry

- `CNF` provides operational status and previous dimensions

3. **Unit of measurement**:

- All values in screen pixels

## Technical Features

✔ **ISO 11783-6 compliant** (F.18)
✔ **Dynamic resizing** (real-time update)
✔ **Comprehensive object support**
✔ **Traceability** (previous dimensions)

## Size reference

| Parameter | Value range | Description |

|-----------|---------------|--------------------|

| Width | 1-65535 pixels | Horizontal extent |

| Height | 1-65535 pixels | Vertical extent |

## Return codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful change |

| -6 | VT_E_OVERFLOW | Buffer Overflow |

-8 | VT_E_NOACT | VT Not Ready |

-21 | VT_E_NO_INSTANCE | No VT Client Available |

-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT Instance |

-130 | VT_E_NOT_ALIVE | VT Not Active |

## Application Scenarios

- **Responsive Designs**: Adapting to Display Sizes

- **Zoom Functions**: Dynamic Scaling

- **Layout Manager**: Automatic Size Optimization

- **Animation Control**: Size Change Effects

## ⚖️ Comparison with Similar Building Blocks

| Feature | Q_Size | VtResizeObject | VtGeometryManager |

|---------------|--------|----------------|-------------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Real-time Update | ✔ | ✔ | ✖ |

| 2D Control | ✔ | ✔ | ✔ |

| Feedback | ✔ | ✖ | ✔ |

## Conclusion

The Q_Size block offers precise size control:

- **Flexible**: Pixel-accurate adjustment
- **High-Performance**: Instant display updates
- **Reliable**: ISO-compliant implementation

Essential for:

- Adaptive User Interfaces
- Dynamic Visualizations
- Professional VT Applications