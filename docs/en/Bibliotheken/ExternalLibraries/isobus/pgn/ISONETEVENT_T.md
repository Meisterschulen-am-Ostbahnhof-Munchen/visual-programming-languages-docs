# ISONETEVENT_T
* * * * * * * * * *
## Introduction
The data type `ISONETEVENT_T` is a structured type used to describe a network event within an ISOBUS network. It encapsulates all relevant information needed to identify and process an event related to the management of network participants (control functions). This type is typically used in callback functions to report changes in the network's state.
## Interface Structure
The structure `ISONETEVENT_T` consists of the following six elements:
### **Data Elements**
* **`eNetEvent`** (Type: `USINT`, Initial value: `ISO_NETEVENT_e::Isonet_Last`)
* **Description:** Indicates which specific event occurred in the network member management (e.g., connection establishment, termination, address change).
* **`eMemberRefer`** (Type: `SINT`, Initial value: `ISOUSERHOME_e::notdef`)
* **Description:** Identifies which network member is affected by the event. Specifies whether it is the callback owner, another internal, or an external Control Function (CF).
* **`s16OwnCfHnd`** (Type: `INT`)

**Description:** The CF handle of the entry for which the callback was triggered. This identifies the local representation of the affected network participant.

* **`s16Handle`** (Type: `INT`)

**Description:** The network member handle of the involved control function or user. This is the handle of the CF that caused the event (Event Source CF Handle).

* **`u8SAMember`** (Type: `USINT`)

**Description:** The current source address (SA) of the network member at the time of the event.

* * **`cfName`** (Type: `isobus::pgn::CF_NAME_T`)

**Description:** The ISOBUS name of the involved control function. This name is a unique identifier according to the ISOBUS standard.

## Functionality
The structure `ISONETEVENT_T` functions as a container or message object. When a relevant network event occurs (defined by `eNetEvent`), an instance of this structure is populated with the current data and passed to a registered callback function. The contained data enables the receiving software component to accurately classify the event and identify the affected network entities (`eMemberRefer`, `s16OwnCfHnd`, `s16Handle`), their current address (`u8SAMember`), and their ISOBUS name (`cfName`).

## Technical Details
* **Type:** This is a `StructuredType` within the 4diac IDE.

## Technical Details
* **Type:** This is a `StructuredType` within the 4diac IDE.
* **Initial Values:** Two elements (`eNetEvent`, `eMemberRefer`) have defined initial values that reference enumerated types (`ISO_NETEVENT_e`, `ISOUSERHOME_e`). This ensures a defined initial state.
* **ISOBUS Integration:** The structure is specifically designed for the ISOBUS context, as evidenced by the use of the type-specific `CF_NAME_T` and the parameter designations (SA, CF).
* **Compiler Package:** The data type is assigned to the package `isobus::pgn`, indicating its association with ISOBUS Parameter Group Number (PGN) processing.
*
## Application Scenarios

This data type is primarily used in scenarios where an application needs to be informed about dynamic changes in the ISOBUS network. Examples include:

* Monitoring the appearance or disappearance of electronic control units (ECUs) on the network.
* Responding to address changes of network participants.
* Implementing user-defined logic when establishing or terminating a connection to a specific CF.
* Logging network activity for diagnostic purposes.

## ⚖️ Comparison with Similar Building Blocks
Within the 4diac type library, various structured data types exist for communication protocols. Unlike generic communication structures (such as those for TCP/IP), `ISONETEVENT_T` is highly specialized for the event messages of the ISOBUS protocol stack, particularly the network management (NM) component. Other ISOBUS-related types might focus more on the exchange of process data (PGN data).

## Conclusion

The data type `ISONETEVENT_T` is an essential tool for developing ISOBUS-enabled applications in 4diac that need to react to network events. It provides a standardized, information-rich interface for receiving and processing callback-based event notifications from the ISOBUS network stack. Its use promotes a decoupled and event-driven architecture in the control software.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
