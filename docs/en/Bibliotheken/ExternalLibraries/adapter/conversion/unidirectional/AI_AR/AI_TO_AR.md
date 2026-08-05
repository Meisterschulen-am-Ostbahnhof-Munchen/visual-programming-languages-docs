# AI_TO_AR

![AI_TO_AR](./AI_TO_AR.svg)

* * * * * * * * * *
## Introduction
The **AI_TO_AR** function block is a composite module that enables interface conversion from an **AI** adapter (integer type) to an **AR** adapter (real type). It serves purely as a pass-through and adaptation unit between different adapter protocols in an industrial control system.

## Interface Structure
Since **AI_TO_AR** does not have its own event or data interfaces, all communication takes place exclusively via the connected adapters.

### **Event Inputs**
– not present – 
Event control is handled via the incoming adapter **AI_IN**.

### **Event Outputs**
– not present – 
Event forwarding is handled via the outgoing adapter **AR_OUT**.


### **Data Inputs**
– not available – 
The data is provided as an integer value via the **AI_IN** adapter.

### **Data Outputs**
– not available – 
The data is output as a real value via the **AR_OUT** adapter.

### **Adapters**

| Name | Type | Direction | Description |

|--------|----------------------------------------------|----------|------------------------|

| AI_IN | `adapter::types::unidirectional::AI` | Socket | Integer Adapter (Input) |

| AR_OUT | `adapter::types::unidirectional::AR` | Plug | Real Adapter (Output) |


## Functionality
In the FB network of the composite block, the event and data lines of the two adapters are directly connected:

- The event **E1** of the AI_IN adapter is routed to the event **E1** of the AR_OUT adapter.

- The data value **D1** (type INT) of the AI_IN adapter is transferred to the data value **D1** (type REAL) of the AR_OUT adapter.

The block itself does not perform any explicit type conversion; the conversion from integer to real is either implicitly handled by the runtime environment or must be ensured by the connected context. Thus, the block functions purely as a pass-through for events and data between the two adapter interfaces.

## Technical Features

- The block does not contain its own event or data interface; all its communication takes place via the adapters.

- There is no internal state machine (ECC) – the block operates purely event-driven through the connections.

- The use of adapters achieves loose coupling between the inputs and outputs, increasing the reusability and interchangeability of the interfaces.

## State Overview
The component does not have a state machine. Processing occurs directly without delay or state dependency.

## Application Scenarios

- **Adapter Conversion**: Use in systems where an integer-based sensor signal (AI) must be transferred to a component that expects a real signal (AR).

- **Interface Adaptation**: Use in modular control solutions to mediate between different adapter types without affecting the actual data processing.

- **Prototypes and Testing**: Quick assembly of different adapter components during the development phase.

## Comparison with Similar Components

| Component | Function | Special Feature |

|-----------|-------------------------------------------------|---------------------------------------|
| AI_TO_AR | Pass-through from INT to REAL via adapter | No dedicated logic, pure adapter switching |

REAL_TO_INT | Conversion from REAL to INT (usually with rounding) | Often includes its own algorithm |

ADAPTER_COUPLER | General adapter coupling without type conversion | Requires identical data types |

Unlike dedicated converters, **AI_TO_AR** does not perform active value conversion but relies on the compatibility of the connected adapters.

## Conclusion

**AI_TO_AR** is a simple yet effective composite block for connecting two different adapter interfaces (INT to REAL). It is particularly suitable for cross-system signal transmission in IEC 61499-based controllers where the type conversion logic is located outside the block. Its clear structure makes it a useful tool for modular and flexible automation solutions.