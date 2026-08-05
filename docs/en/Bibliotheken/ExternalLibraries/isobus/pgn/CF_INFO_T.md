# CF_INFO_T
* * * * * * * * * *
## Introduction
The data type `CF_INFO_T` (Control Function Information Type) is a structured data component used within ISO 11783 (ISOBUS) communication. It serves for the standardized representation and management of information about a participant (control function or user) in the ISOBUS network. This type definition summarizes all essential characteristics and states of a network participant in a single data structure.
## Interface Structure
CF_INFO_T` is a structured data type and does not have any event or adapter interfaces in the conventional sense of a function block. Its structure consists exclusively of data elements (variables).
## **Data Inputs**
Not present, as it is a pure data type.

## **Data Outputs**
Not present, as it is a pure data type.

#
# ### **Data Elements (Structure)**

The internal structure of type `CF_INFO_T` consists of the following elements:

| Name | Type | Comment / Description | Initial Value |
| :--- | :--- | :--- | :--- |
| `s16Handle` | `INT` | Network member handle of the Control Function (CF) / User. Serves as a unique identifier within the application. | `UNVALID` |
| `u8SourceAddress` | `BYTE` | Source Address (SA) of the Control Function (CF) / User in the ISOBUS network. | `NULL_A` |
| `u8CanIdx` | `BYTE` | CAN bus node / index of the control function (CF) / user. Identifies the physical bus node. | – |
| `au8Name` | `isobus::pgn::CF_NAME_T` | The ISOBUS name of the control function. This is a 64-bit unique identifier according to ISO 11783-5. | – |
| `eIsoUserFunct` | `SINT` | Internally used CF function type (e.g., work device, terminal, task controller). | `undefined` |
| `bExternalCf` | `BOOL` | Indicates whether it is an external CF in the CAN network (`TRUE`) or not. | – |
| `bIsAnnounced` | `BOOL` | `TRUE` if the CF is active and fully announced in the network. | – |
| `bIsActive` | `BOOL` | NIU-specific (Network Interface Unit): `TRUE` if the CF is not in an error state or logged off. | – |

## Functionality
The data type `CF_INFO_T` is a passive data storage structure. It is used to store the state and identity of an ISOBUS network participant and to exchange this information between different components of a control application. The information it contains is typically read, written, and interpreted by other function blocks responsible for network management (e.g., address assignment, name management) or application logic.

## Technical Features
* **Typedef for ISOBUS:** Specifically designed for use in ISO 11783 environments (agricultural machinery).
* **State Flags:** Contains several Boolean flags (`bIsAnnounced`, `bIsActive`) that represent the lifecycle and operating state of a function block.
* **Initial Values:** Critical identifiers such as `s16Handle` and `u8SourceAddress` are initialized with defined constants (`UNVALID`, `NULL_A`) to ensure an invalid output state.
* **Integration:** Uses the user-defined type `isobus::pgn::CF_NAME_T` to map the 64-bit ISOBUS name.

## State Overview
Since this is a data type and not an active function block, there is no state machine. The "state" is described by the combination of the included data fields, in particular by the flags:

* **Invalid/Inactive:** `s16Handle == UNVALID`, `bIsAnnounced == FALSE`
* **Valid & Active:** `s16Handle != UNVALID`, `bIsAnnounced == TRUE`, `bIsActive == TRUE`
* **Valid & Faulty/Inactive:** `s16Handle != UNVALID`, `bIsActive == FALSE`

## Application Scenarios
* **Participant Management:** In an ISOBUS manager block that manages a list of all known network participants (`CF_INFO_T[]`).
* **Diagnostics and Display:** Forwarding participant information to a diagnostic or display system to show the network status.
* **Command Forwarding:** As a parameter for communication blocks to specifically address messages to a particular CF (identified by `u8SourceAddress` and `au8Name`).
* **Filtering:** Logic blocks can use the fields `eIsoUserFunct` or `bExternalCf` to decide whether messages from a specific CF should be processed.

## ⚖️ Comparison with Similar Blocks

CF_INFO_T` is not a function block and therefore cannot be directly compared with blocks such as `E_SR` or `E_CYCLE`. Within ISOBUS communication, it is comparable to other structured data types that bundle network or device information (e.g., `PGN_INFO_T` for Parameter Group Numbers). Its unique feature lies in the specific compilation of data required for the identification and state management of a control function.

## Conclusion
The data type `CF_INFO_T` is a fundamental and essential component for implementing ISOBUS-enabled control applications in 4diac. It provides a standardized, type-safe method for grouping and transporting all relevant information about a network participant. Its use increases code reusability and ensures consistency in network communication logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
