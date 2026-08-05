# Version
## 🎧 Podcast
![version](./version.svg)
* "Store Version" – Your key to managing object data pools in non-volatile VT memory (ISO 11783-6) ](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/Store-Version--Dein-Schlssel-zur-Verwaltung-von-Objektdatenpools-im-nichtflchtigen-VT-Speicher-ISO-11783-6-e36vfh0)
* Understanding VT Versions: Your path to becoming a master of agricultural and construction machinery mechatronics ](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/VT-Versionen-verstehen-Dein-Weg-zum-Meister-der-Land--und-Baumaschinenmechatronik-e36a8e8)
## Introduction
The function block `version` facilitates the simple transmission of version information. It receives a string as input and outputs it unchanged. This block is useful for transporting version numbers or other identifiers within an application chain or for diagnostic purposes.

## Interface Structure

### **Event Inputs**
* **REQ**: This event triggers the processing of the function block. Upon its arrival, the value of the corresponding data input `VERSION` is copied to the data output `VERSIONO`.

### **Event Outputs**
* **CNF**: This event signals the successful completion of the operation. It is generated simultaneously with the data output `VERSIONO`.

### **Data Inputs**
* **VERSION** (STRING): This input expects the string to be passed on (e.g., a version number such as "1.2.3").

### **Data Outputs**
* **VERSIONO** (STRING): This output outputs the received value from `VERSION` unchanged.

### **Adapters**
This function block does not have any adapter interfaces.

## Functionality
The `version` block operates in an extremely simple and deterministic manner. Upon each occurrence of the `REQ` event, the current value of the input variable `VERSION` is copied to the output variable `VERSIONO`. Immediately following this assignment, the acknowledgment event `CNF` is generated along with the new output value. No formatting checks, manipulation, or storage of the value takes place.

## Technical Features
* **Simple Pass-Through**: The block performs no transformations or logic on the data.
* **Direct Coupling**: The `REQ` and `CNF` events are directly coupled; the execution time is negligible.
* **No Internal State**: The block has no internal memory. Every execution depends solely on the current inputs.

## State Overview
The function block `version` is stateless. It remains in a single, passive state until a `REQ` event occurs. The response to this event (copying the data and triggering `CNF`) is instantaneous and does not result in a different state.

## Application Scenarios

1. **Version Propagation**: In an application chain, a higher-level function block (e.g., a master or management function block) can pass its own version to this block to be sent to downstream diagnostic or logging functions.

## 2. **Diagnostics and Tracing**: This block can be used to collect specific software versions or configuration versions in a central log or display system.

3. **Data Consolidation**: In conjunction with other function blocks, it can be used to provide version information from various sources in a central location (e.g., an HMI or a network service).

## ⚖️ Comparison with Similar Blocks
* **`E_SR` or `E_RS` (Flip-Flops)**: These blocks have an internal state (set/reset) that is changed by events. The `version` block does not have such a state.
* **`E_MERGE`**: This block merges events from multiple inputs. The `version` block has only a single event input and does not process any event streams.
* **Simple data blocks (e.g., `E_R_TRIG`)**: These react to signal edges or perform timing operations. The `version` block performs only data copying.
* **Generic blocks like `COPY`**: A `COPY` block would perform a similar function (copying data from A to B) but is typically a pure data block without event control. The `version` block follows the standard IEC 61499 event/data flow paradigm.
*
## Conclusion

The `version` function block is a minimalist and specialized tool for passing string information within an event-driven control system. Its strength lies in the simplicity and clarity of its purpose. For simple data copying without event logic, alternative implementations might be suitable; however, it is well-suited for integration into a standards-compliant IEC 61499 application with a clearly defined event flow.
