# 📏 Standards and Norms

In industrial automation, standards form the foundation for interoperability, safety, and efficiency. They ensure that systems from different manufacturers can work together and that software remains portable.

## IEC 61499: The Standard for Distributed Systems

IEC 61499 is the central standard for this project. It extends the IEC 61131-3 model with a system-wide architecture for distributed control systems.

### Structure of the Standard
The standard is divided into several parts, each covering different aspects:

* **Part 1: Architecture:** Defines the basic model for distributed systems, including function blocks, resources, and devices.

* **Part 2: Requirements for Software Tools:** Specifies the properties that software tools (such as the 4diac IDE) must possess to create compliant applications.

* **Part 4: Rules for Compliance Profiles:** Defines how specific profiles must be created to guarantee interoperability between different systems (e.g., for a specific industry).

### Sources of Supply
Standards are traditionally obtained in Germany through **Beuth Verlag** (DIN). A helpful tip from practical experience is to obtain them through **EVS (Estonian Centre for Standardisation and Accreditation)**. The identical European standards are often available there at significantly lower costs (especially the "3 User Licence").



### Sources of Supply
Standards are typically obtained through **EVS** (Estonian Centre for Standardisation and Accreditation)**. **Links:**

* [Wikipedia (DE): EN 61499](https://de.wikipedia.org/wiki/EN_61499)

* [Wikipedia (EN): IEC 61499](https://en.wikipedia.org/wiki/IEC_61499)

* [Beuth Verlag: DIN EN 61499](https://www.beuth.de/de/norm/din-en-61499-1/209152944)

* [EVS Estonia: EVS-EN 61499](https://www.evs.ee/en/evs-en-61499-1-2013)

---

## IEC 61131-3: Classic PLC Programming

Before IEC 61499 was introduced, IEC 61131-3 was (and still is) the worldwide standard for programming languages of programmable logic controllers (PLCs). It defines languages such as:

* Instruction List (IL)
* Structured Text (ST)
* Ladder Diagram (LD)
* Function Block Diagram (FBD)
* Sequential Function Chart (SFC)

In modern systems, IEC 61131-3 often serves as the basis for the logic within an IEC 61499 function block.

---

## ISO 11783 (ISOBUS): Communication in Agricultural Engineering

The ISOBUS standard is based on the CAN bus and is crucial for communication between tractors and implements. It ensures that a terminal in the tractor can control implements from different manufacturers.

The standard is extremely comprehensive and comprises 14 parts, from the physical layer (cables/connectors) and network management to the task controller and diagnostics.

---

## Graphical Symbols and Safety

Standardized symbols are essential for designing human-machine interfaces (HMIs) and identifying hardware.

* **ISO 7000 / IEC 60417:** A comprehensive collection of graphical symbols for use on devices (e.g., "On/Off", warnings).

* **ISO 7010:** Specific safety signs and colors for accident prevention.

**Resource:**
All registered symbols can be viewed in the ISO Online Browsing Platform (OBP) [](https://www.iso.org/obp)].

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)]

