# CallbackFB
<img width="1298" height="232" alt="image" src="https://github.com/user-attachments/assets/3e1dbee0-183b-4d4f-a9e7-110505249cb4" />
* * * * * * * * * *
## Introduction
The `CallbackFB` is a composite function block that simplifies the use of the callback mechanism in subapplications. It serves as a wrapper block to provide a standardized interface for asynchronous communication via a callback adapter. Its primary purpose is to decouple and provide structured handling of acknowledgment messages (`CNF`) and requests (`REQ`) within a function block network.
![CallbackFB](CallbackFB.svg)
## Interface Structure

### **Event Inputs**
* **`CNF`**: Confirmation Event. This event is received by the connected plug and signals the completion of a request or the arrival of data.

### **Event Outputs**
* **`REQ`**: Request event. This event is triggered by the adapter's internal socket and signals a pending action or data request.

### **Data Inputs**
* **`DI1`**: Data input of type `isobus::pgn::CAN_MSG`. This input carries the CAN message data associated with the incoming `CNF` event.

### **Data Outputs**
* *(No direct data outputs are defined on the function block. The data is forwarded via the adapter.)*

### **Adapters**
* **`PLUG1`**: A plug adapter of type `isobus::pgn::tx::Callback`. This adapter establishes the connection to a corresponding socket adapter in another function block and implements the callback pattern.

## Functionality
The `CallbackFB` acts as a transparent intermediary. Its internal network (FBNetwork) connects the public interfaces of the composite function block directly to the pins of the integrated `Callback` adapter (`PLUG1`).

1. An incoming `CNF` event is forwarded directly to the `CNF` input of the `PLUG1` adapter.

2. The data associated with `CNF` (`DI1` of type `isobus::pgn::CAN_MSG`) is simultaneously transferred to the `DO1` data input of the `PLUG1` adapter.

3. When the internal socket of the `PLUG1` adapter triggers a `REQ` event, it is directly forwarded to the public `REQ` event output of the `CallbackFB`.

The module itself does not perform any additional logic or data processing. Its function consists solely of the structured bundling and forwarding of events and data.

## Technical Features
* **Typing**: The data input `DI1` uses the specific data type `isobus::pgn::CAN_MSG`, indicating an application in the context of ISOBUS and CAN-based agricultural systems.
* **Adapter Pattern**: All functionality is based on the 61499 adapter concept. The function block (FB) encapsulates a `Plug` and requires a corresponding `Socket` of type `isobus::pgn::tx::Callback` in another function block for operation.
* **Transparency**: As a composite FB without additional algorithms, its behavior is completely defined by the internal connection network and is therefore predictable.

## State Overview
Since it is a purely pass-through composite function block without an internal state machine (Basic FB) or cyclic behavior (Service Interface FB), the `CallbackFB` does not have its own state machine. Its "state" is determined by the state of the connected adapter pair (`PLUG1` and its corresponding socket).

## Application Scenarios
* **Structuring Subapplications**: In complex subapplications, the `CallbackFB` can be used to provide a clean and reusable interface for callback communication.
* **Decoupling Components**: It enables loose coupling between a service provider (providing the socket) and a service user (using this function block), which improves maintainability and testability.
* **ISOBUS Communication**: A specific application in control systems for agricultural machinery to asynchronously acknowledge or request the transmission of CAN messages (PGNs).
* ## ⚖️ Comparison with Similar Building Blocks
* **Direct Adapter Connection**: Instead of directly integrating a `Callback` adapter into a network, the `CallbackFB` offers a bundled, named interface (`CNF`/`REQ`/`DI1`) that may be more readable in some designs.
* **Simple E_CLASS vs. CallbackFB**: A simple E_CLASS building block (Event Splitter/Merger) could perform similar event routing, but would not provide the type-safe data connection for `isobus::pgn::CAN_MSG` along with the standardized adapter interface.
* **Simple E_CLASS vs. CallbackFB**: * **Generic Wrapper Function Blocks**: Unlike generic wrapper function blocks, `CallbackFB` is specialized for a specific data type and adapter, ensuring type safety and clear semantics.

## 🛠️ Related Exercises
* [Exercise_126b2_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b2_sub.md)]
* [Exercise_126b_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b_sub.md)]
* [Exercise_12x_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_12x_sub.md)]

## Conclusion
`CallbackFB` is a useful auxiliary construct for the structured application of the adapter pattern in IEC 61499, especially in the ISOBUS environment. It reduces complexity in the main network by offloading the connection logic for callback communication into a single, reusable composite component. Its strength lies in its simplicity and clarity, as it does not implement any active logic itself. It is the ideal choice when a standardized and type-safe callback interface is required in a subapplication.