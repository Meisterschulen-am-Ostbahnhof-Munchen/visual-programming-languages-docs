# E_TRIG
<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
## Introduction
The `E_TRIG` is a special service function block according to IEC 61499. Its function is to programmatically trigger *unconnected* event inputs of a specific type (name) within a resource. This enables advanced control and initialization scenarios.
![E_TRIG](E_TRIG.svg)

## Interface Structure

### **Event Inputs:**
- **REQ (Request)**: Triggers the trigger mechanism.
- **Connected Data**: `EVENTTYPE`

### **Event Outputs:**
- **CNF (Confirmation)**: Confirms that the trigger command has been issued.

### **Data Inputs:**
- **EVENTTYPE**: The name of the event inputs to be triggered (data type: `STRING`).
- **Default Value**: 'EInit'

## Functionality

1. **Trigger Request**: Upon a `REQ` event, the function block reads the string at the `EVENTTYPE` input.

2. **Internal Triggering**: The function block instructs the 4diac runtime environment (the resource) to find all *unconnected* event inputs of function blocks within the same resource whose name matches the `EVENTTYPE` string.

3. **Event Generation**: The runtime environment triggers these found event inputs.

4. **Acknowledgement**: Immediately after the command is issued, the `E_TRIG` block triggers its `CNF` event.

**Example:**
Suppose several function blocks in a resource have an unconnected input named `INIT`. A `E_TRIG` block with `EVENTTYPE = 'INIT'` would, upon a `REQ` event, trigger all these `INIT` inputs simultaneously to force a re-initialization of these blocks.

## Technical Features
- **Service Block**: This is not a simple logic block, but an interface to a special service of the 4diac runtime environment.

**Example:** - **Effects Unconnected Inputs**: This functionality explicitly targets inputs that are not graphically wired in the network. This is a powerful feature, but it should be used with caution.

- **Default Use Case `EInit`**: The default value 'EInit' indicates the primary use case: manually triggering initialization events that are normally executed only once when a resource starts.

## Application Scenarios
- **Manual Re-Initialization**: Resetting parts of an application to a defined initial state without having to restart the entire resource.
- **Dynamic Configuration**: After loading a new configuration, relevant components can be made to adopt the new parameters via a targeted `E_TRIG` call.
- **Testing and Debugging**: Manually triggering specific events in a running application for testing purposes.

## 🛠️ Related Exercises
* [Exercise_176](../../../Uebungen/test_B/Uebungen_doc/Uebung_176.md)

## Conclusion
The `E_TRIG` building block is a tool for advanced use cases and for developers with in-depth knowledge of the 4diac execution environment. It offers a powerful method to bypass the standard, graphically defined event flow logic and interact directly with the runtime environment. It should be used with caution, as its effect is not immediately apparent from the graphical network.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
