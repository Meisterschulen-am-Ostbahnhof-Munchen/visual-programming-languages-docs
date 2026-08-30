# NAMEFIELD_T

* * * * * * * * * *
## Introduction

The data type `NAMEFIELD_T` represents a structured data component for mapping the ISO 11783 (ISOBUS) NAME field according to Part 5 of the standard and the Implemented Function Module (IFM) conventions. This structured data type serves for the unique identification and addressing of electronic control units (ECUs) in an ISOBUS network. It combines all parameters required for device identification into a single data structure.
## Interface Structure

NAMEFIELD_T` is a structured data type (STRUCT) consisting of ten individual variables. Each variable corresponds to a defined part of the 64-bit NAME field in the ISOBUS protocol.

### **Data Inputs**

*(As a structured data type, `NAMEFIELD_T` has no events, only data fields. These are listed here as components of the structure.)*

| Name | Data Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| `bSelfConf` | `BOOL` | `TRUE` | Indicates whether it is a self-configurable address ECU. |
| `bIndGroup` | `BYTE` | `16#FF` | Assigns the NAME to an industry group (range 0-7). |
| `bDevClassInst` | `BYTE` | `16#FF` | Identifier if a device class occurs multiple times on the network (0..15). |
| bDevClass` | `BYTE` | `16#FF` | ISO-defined device class (0..127). |
| bReserved` | `BOOL` | `TRUE` | Reserved bit (not used). |
| bFunction` | `BYTE` | `16#FF` | ISO-defined function, corresponds to the Source Address (SA) (0..255). |
| bFunctionInst` | `BYTE` | `16#FF` | Subgroup of a function (0..31). |
| bEcuInstance` | `BYTE` | `16#FF` | Indicates which control unit is assigned to a specific function (0..7). |
| wManufCode` | `WORD` | `16#FFFF` | ISO-defined manufacturer code (0..2047). |
| dwIdentNumb` | `DWORD` | `16#FFFFFFFF` | Unique serial number; used when the NAME is not unique within the same network (0 to 2,097,151).

### **Data Outputs**

*(Not applicable, as this is a data-only type.)*

### **Adapters**

*(Not applicable, as this is a data-only type.)*

## Functionality

The `NAMEFIELD_T` data type is a passive data structure. Its primary function is the structured storage and transmission of the parameters that together form the 64-bit ISOBUS NAME. Each variable within the structure occupies a specific bit range within this overall field. The initial values (`16#FF`, `16#FFFF`, `16#FFFFFFFF`) typically represent an undefined or unassigned state.

## Technical Features

- **Bit-accurate mapping:** The structure directly maps the binary layout of the ISO NAME field, enabling efficient serialization and deserialization for communication via the CAN bus protocol.
- **Initial values:** The selected initial values (maximum values for the respective data types) clearly indicate an uninitialized or placeholder state.
- **ISOBUS compliance:** The naming and division of the fields strictly adhere to the ISO 11783-5 specification and the extended IFM conventions.

## State overview

Since this is a data type and not a function block, there is no state machine. The "state" is defined by the specific values of the ten included variables.

## Application Scenarios

The data type `NAMEFIELD_T` is primarily used in ISOBUS-compliant control applications, for example, in agricultural and forestry technology or construction machinery.

- **Device Identification:** As part of messages (e.g., in the Address Claim process) to identify a participant in the network.
- **Data Storage:** For storing the device's own identity within ECU software.
- **Filtering:** For configuring message filters based on device class, function, or manufacturer.
- **Diagnostics:** For uniquely identifying devices in diagnostic and configuration tools.
*
## ⚖️ Comparison with Similar Function Blocks

Unlike function blocks (FBs) such as `E_SR` or `E_CYCLE`, `NAMEFIELD_T` is a pure **data type** (structured data type). It contains no algorithms, events, or executed code.

- **Similarity to other STRUCTs:** It is comparable to other structured data types in 4diac (e.g., for complex measured values), but is specifically designed for the ISOBUS protocol.
- **Difference to Basic Data Types:** While basic types such as `INT` or `BOOL` hold individual values, `NAMEFIELD_T` groups several logically related values into a single unit.
*
## Conclusion

The data type `NAMEFIELD_T` is an essential tool for developing ISOBUS-compliant control applications with 4diac FORTE. It abstracts the complex bit structure of the ISO NAME field into an easily manageable, strongly typed data structure. This promotes code reusability, improves readability, and reduces errors when handling device identification data. Its use is standards-compliant and recommended for all projects implementing ISOBUS communication.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
