# CbVtStatus
![CbVtStatus](https://user-images.githubusercontent.com/116869307/214146846-2d9f0694-b5f4-4e70-aae0-dc64540eb356.png)

* * * * * * * * * *
## Introduction
The **CbVtStatus** is a standardized callback module for virtual terminal page changes, developed under the EPL 2.0 license. Version 1.0 supports ISO 11783-6 (ISOBUS) in agricultural tax systems.
![CbVtStatus](CbVtStatus.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request

### **Event Outputs**
- `INITO`: Initialization Confirmation (with STATUS)
- `IND`: Page Change Indication (with Page Info)

### **Data Outputs**
- `STATUS` (STRING): Operational Status
- `u8Instance` (USINT): Client Instance Identifier
- `qWsActive` (BOOL): Workload Status
- `wPage` (UINT): Current Page ID

## Functionality

1. **Initialization**:

- Event `INIT` starts setup
- Event `INITO` confirms with STATUS

2. **Page Change**:

- Event `IND` is triggered on screen change
- Returns: Page ID, Active Status, Instance Number

3. **Operation**:

- Real-time monitoring of the VT status
- Multi-ECU capable architecture

## Technical Features

✔ **ISO 11783-6 compliant**
✔ **Deterministic** behavior
✔ **Multi-ECU support**
✔ **Plug-in capable** architecture

## Supported Operating Modes

| Mode | Description |
|---------------|----------------------------------|
| Single device | Standard operation with u8Instance=0 |
| Multi-ECU | Parallel Instances (1-255) |
Diagnostics | STATUS Messages for Service |

## Application Scenarios
- **Tractor Control Units**: Operator Screen Monitoring
- **Harvesting Machines**: Work Data Display
- **Diagnostic Tools**: VT Status Monitoring
- **Multi-Display Systems**: Synchronization

## ⚖️ Comparison with Similar Modules

| Feature | CbVtStatus | VtPageManager | VtEventLogger |
|----------------|-------------|---------------|---------------|
| Page Switch | ✔ | ✔ | ✖ |
| Multi-ECU | ✔ | ✖ | ✖ |
STATUS feedback | ✔ | ✖ | ✔ |

## Error Handling
- Invalid Page ID:
- STATUS = "ERR_INVALID_PAGE"
- wPage = 0xFFFF
- Initialization Error:
- STATUS = "ERR_INIT_FAILED"
- System in Safe State

## 🛠️ Related Exercises
* [Exercise_012](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012.md)]
* [Exercise_012a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012a.md)]
* [Exercise_012b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012b.md)]
* [Exercise_012c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012c.md)]

## Conclusion

The CbVtStatus module is essential for ISOBUS-compliant agricultural systems:

- Robust page change management
- Full ISO 11783-6 compatibility
- Proven architecture In series production

Especially valuable for manufacturers of:

- Tractor control units
- Harvesting machine control systems
- ISOBUS diagnostic devices

The standardized implementation enables reliable operation in heterogeneous system environments.
