# AUDI_MUX_4
![AUDI_MUX_4](./AUDI_MUX_4.svg)
* * * * * * * * * *
## Introduction
The AUDI_MUX_4 is a generic multiplexer function block according to IEC 61499-2. It selects one of four inputs (IN1 to IN4) based on an index K and forwards this value to the output OUT. The block is designed for use in adapter-based systems.
## Interface Structure
### **Event Inputs**
- **REQ**: Event to trigger the multiplexer action. The index K is evaluated upon receipt of REQ.

### **Event Outputs**
- **CNF**: Confirmation event that signals that the index setting (selection) is complete.

### **Data Inputs**
- **K** (UINT): Index value (0, 1, 2, 3) for selecting the active input.

### **Data Outputs**
No direct data outputs are available. Output is provided via the adapter.

### **Adapters**
- **OUT** (Plugs, Type: adapter::types::unidirectional::AUDI): Output adapter that provides the selected input value.
- **IN1** (Sockets, Type: adapter::types::unidirectional::AUDI): First input value (index K=0).
- **IN2** (Sockets, Type: adapter::types::unidirectional::AUDI): Second input value (index K=1).
- **IN3** (Sockets, Type: adapter::types::unidirectional::AUDI): Third input value (index K=2).
- **IN4** (Sockets, Type: adapter::types::unidirectional::AUDI): Fourth input value (index K=3).

## Functionality
When a REQ event arrives, the current value of index K is read. Depending on K (0–3), the corresponding socket (IN1..IN4) is switched to the plug OUT. After successful switching, the CNF event is output. The function block is generic and can also be referred to as "GEN_AUDI_MUX".

## Technical Features
- Uses adapters of type "AUDI" (unidirectional), which define a standardized interface for data transmission.
- The function block is fully event-driven; the index changes only upon REQ.
- Index K is expected as a UINT; valid values are 0–3. Values outside this range result in undefined behavior.
- As a generic function block, it is identified with the attribute `GenericClassName = 'GEN_AUDI_MUX'` and can be further specified using type hashing mechanisms.

```
## State Overview
The function block (FB) does not have an explicit state machine. It operates in an implicit state: Waiting for REQ; upon REQ, the appropriate input is selected according to the index, and CNF is sent.

## Application Scenarios
- Selection of one of four analog or digital measured values for further processing.
- Switching between different signal sources in automation systems.
- Configurable signal routing in modular control applications.

## Comparison with Similar Function Blocks
The IEC 61499 standard often offers multiplexer FBs with direct data inputs. The AUDI_MUX_4, however, uses adapters, enabling flexible coupling with other function blocks that support the AUDI adapter interface. This increases reusability and allows for consistent data transmission across adapters.

## Conclusion
The AUDI_MUX_4 is a useful generic multiplexer for adapter-based systems. It allows the selection of one of four inputs via an index and is particularly suitable for modular automation solutions where a clear separation of event and data flows is desired.
