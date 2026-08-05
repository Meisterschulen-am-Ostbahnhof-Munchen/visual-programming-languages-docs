# Q_ChangePolygonScale
![Q_ChangePolygonScale](https://user-images.githubusercontent.com/116869307/214147096-01ad8095-df5d-4cab-82ee-7f97a5758ea0.png)

* * * * * * * * * *
## Introduction
The **Q_ChangePolygonScale** is a standards-compliant function block for scaling polygon objects in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.54) specification for agricultural tax systems.
![Q_ChangePolygonScale](Q_ChangePolygonScale.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with polygon object ID)
- `REQ`: Scaling request (with new dimensions)

### **Event Outputs**
- `INITO`: Initialization confirmation
- `CNF`: Scaling confirmation (with result data)

### **Data Inputs**
- `u16ObjId` (UINT): Polygon object ID
- `u16NewWidth` (UINT): New width in pixels
- `u16NewHeight` (UINT): New height in pixels

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u16OldWidth` (UINT): Previous width
- `u16OldHeight` (UINT): Previous height
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with polygon object ID
- `INITO` confirms operational readiness

2. **Scaling**:

- `REQ` triggers with new dimensions
- Proportional scaling of all polygon points
- `CNF` returns result and previous values

3. **Error Handling**:

- ISO-standardized Error Codes
- Detailed Status Messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.54)
✔ **Proportional scaling** (width/height)
✔ **16-bit resolution** (0-65535 pixels)
✔ **Real-time processing**

## Scaling Behavior

| Parameter | Effect |
|------------|-----------------------------|
| Width | Horizontal scaling |
| Height | Vertical scaling |
| 0xFFFF | Maintain original size |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Success | | -6 | VT_E_OVERFLOW | Invalid Dimensions |
| -128 | VT_E_HANDLE_INVALID | Invalid Polygon ID |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid Instance |

## Application Scenarios
- **Machine Display**: Dynamic Resizing
- **Zoom Functions**: Detail Magnification
- **Responsive Designs**: Adapting to Display Sizes
- **Animated Transitions**: Smooth Size Changes

## ⚖️ Comparison with Similar Building Blocks

| Feature | Q_ChangePolygonScale | VtGeometryScaler | VtDynamicResize |
|---------------|----------------------|------------------|-----------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Scaling | Proportional | Free | Width Only |
| Resolution | 16-bit | 8-bit | 16-bit |

## Conclusion

The Q_ChangePolygonScale block provides the reference implementation for polygon scaling:

- **Precise**: Pixel-accurate size control
- **Proportional**: Maintains the original shape
- **Standards-compliant**: Full ISO 11783-6 compatibility

Ideal for:

- Adaptive visualizations
- Dynamic map views
- Resizable controls
