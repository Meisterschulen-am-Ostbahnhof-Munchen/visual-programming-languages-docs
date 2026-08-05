# AX_CYCLE

* * * * * * * * * *
## Introduction
The AX_CYCLE is a function block that outputs a cyclic event via an AX adapter.

## Interface Structure

### **Data Inputs**
- **DT** (TIME): Cycle time.

### **Adapters**
**Sockets (Inputs):**

- **START** (adapter::types::unidirectional::AX): Start signal.

- **STOP** (adapter::types::unidirectional::AX): Stop signal.

**Plugs (Outputs):**

- **EO** (adapter::types::unidirectional::AX): Cyclic output event.

## Functionality

While START is active, EO is output with a period of DT. STOP terminates the cycle.

## Technical Features
- Uses unidirectional adapters.


## State Overview
State-based.

## Application Scenarios
Clock Generation.

## ⚖️ Comparison with Similar Function Blocks

- **E_CYCLE**: Standard Cycle Function Block.

## Conclusion
Adapter-based Cycle Function Block.