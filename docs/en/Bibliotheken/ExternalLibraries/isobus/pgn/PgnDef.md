# PgnDef

![PgnDef](./PgnDef.svg)

* * * * * * * * * *
## Introduction

PgnDef` is a collection of global constants for the 4diac IDE that defines Parameter Group Numbers (PGNs) for ISOBUS and NMEA 2000 communication protocols. These constants represent numeric identifiers for specific message types used in agricultural and maritime vehicle networking. The collection serves as a central reference library for accessing standardized PGNs in IEC 61499 applications, thus improving code readability and maintainability.
## Interface Structure

PgnDef` is a `GlobalConstants` element and therefore does not have event- or data-flow-based interfaces in the conventional sense of a function block. Instead, it provides a collection of constants that can be declared and used in other function blocks or programs.

### **Event Inputs**

Not present. This is a constant definition.

### **Event Outputs**


### **Data Inputs**


### **Data Outputs**


### **Adapters**


## How it Works

PgnDef` itself has no executable logic. It simply defines an extensive list of constants of the data type `UDINT` (Unsigned Double Integer). Each constant is a PGN value initialized in hexadecimal notation (`UDINT#16#XXXX`) and contains a human-readable comment with the PGN name and often a reference to the corresponding standard (e.g., ISO 11783-7). Other function blocks can import these constants via their fully qualified names (e.g., `isobus::pgn::PGN_HEARTBEAT`) and use them in their logic to identify or generate messages.

## Technical Features

* **Extensive Coverage:** The collection contains PGNs from a variety of standards, including ISO 11783 (ISOBUS, Parts 3-7, 12, 13), SAE J1939 (71, 73, 75), and NMEA 2000.
* **Organized Structure:** The constants are commented in logical groups (PDU1/Group Functions, PDU2, J1939-71, ISO 11783-7, Diagnostics (J1939-73), Generator Sets (J1939-75), NMEA).
* **Data Type:** All PGNs are defined as `UDINT` (32-bit, unsigned), which corresponds to the addressable range of the protocols.
* **Package Assignment:** The constants are assigned to the package `isobus::pgn`, which ensures clear namespace separation.

## State Overview

Not applicable, as this is a static constant declaration.

## Application Scenarios

* **ISOBUS ECU Development:** For developing electronic control units (ECUs) for tractors or implements that communicate via an ISOBUS network.
* **NMEA 2000 Integration:** In maritime applications for integrating ship electronics such as GPS receivers, depth sounders, or engine controls.
* **Protocol Implementation:** As a basis for implementing protocol stacks (e.g., for transport protocols such as TP/CM or ETP/CM).
* **Message Filtering:** In gateway or bridge function blocks to filter and forward incoming messages based on their PGN.
* **Diagnostic Tools:** In applications for diagnosing and monitoring vehicle networks, to correctly name and display received messages.

## ⚖️ Comparison with Similar Blocks

* **Simple `VAR_GLOBAL CONSTANT` Declarations:** `PgnDef` offers the advantages of centralization, reusability, and avoidance of redundancy and typos compared to constants declared manually in the function block.
* **Enumerations (ENUM):** While ENUMs in IEC 61499 can be used for ordered lists, `PgnDef` is better suited as a collection of discrete, not necessarily consecutive, values. Constants also offer more flexibility in value assignment (hexadecimal).
* **Specific Protocol Function Blocks:** Unlike function blocks that implement a specific protocol function (e.g., a `ADDRESS_CLAIM` function block), `PgnDef` is purely a reference tool and contains no active logic.

## Conclusion

The `PgnDef` constant collection is an essential tool for developing IEC 61499-based applications in the domains of mobile machinery (ISOBUS) and marine electronics (NMEA 2000). It promotes standardization, improves code quality through enhanced readability, and reduces errors through the use of centrally defined and tested values. For any developer working with these protocols in 4diac, `PgnDef` is a valuable and likely indispensable resource.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
