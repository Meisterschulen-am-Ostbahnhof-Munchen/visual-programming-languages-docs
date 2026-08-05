# AULI_MUX_3
![AULI_MUX_3](./AULI_MUX_3.svg)

* * * * * * * * * *
## Introduction
The function block `AULI_MUX_3` is a generic multiplexer that allows the selection of one of three data streams connected via adapters. It operates within the AULI adapter specification (unidirectional) and is suitable for flexible switching between different data sources in an IEC 61499-based control environment. Selection is made via an index `K`, which is evaluated upon a query (`REQ`).
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Set Index K. Triggers the multiplexer action. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of index selection (after successful switching). |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index for selecting the input (0, 1, or 2). |

### **Data Outputs**

The FB has no direct data outputs; the output data is provided via the adapter `OUT`.

### **Adapter**
- **Sockets (Inputs):**
- `IN1` (Type: `adapter::types::unidirectional::AULI`) – Input data for K = 0.
- `IN2` (Type: `adapter::types::unidirectional::AULI`) – Input data for K = 1.
- `IN3` (Type: `adapter::types::unidirectional::AULI`) – Input data for K = 2.
- **Plugs (Outputs):**
- `OUT` (Type: `adapter::types::unidirectional::AULI`) – Output that switches the selected input.

## Functionality

The `AULI_MUX_3` operates in an event-driven manner. Upon an event at the **REQ** input, the current value of the data input `K` (unsigned integer) is read. Depending on this value, the corresponding socket input (IN1, IN2, or IN3) is switched to the plug output `OUT`. Data flow occurs via the adapter interfaces of type `AULI` (unidirectional), meaning that after switching, data exchange between the selected source and the output is established. A confirmation event is sent at the **CNF** output after successful switching.

If `K` assumes an invalid value outside the range 0 to 2, the behavior is unspecified – this should be avoided by the application logic.

If `K` assumes an invalid value outside the range 0 to 2, the behavior is unspecified – this should be avoided by the application logic.

## Technical Features

- **Generic Type**: The function block (FB) is marked as generic (`GEN_AULI_MUX`), so it can be used for various AULI data types or structures, provided the adapter definition allows it.
- **Unidirectional Adapter**: All adapters are unidirectional (`adapter::types::unidirectional::AULI`), meaning that data flows in only one direction (from the socket to the plug).
- **Event-Driven**: No cyclic polling; switching occurs only on demand.
- **Simple Interface**: Only one event input and one event output minimizes connection complexity.

## State Overview

The FB does not have a sophisticated state machine (e.g., ECC) because it operates purely event-driven and without internal memory. The process is as follows:

1. Wait for event `REQ`

2. Read `K`

3. Switch the corresponding input to `OUT`

4. Send `CNF`

5. Return to step 1

## Application Scenarios
- **Sensor Selection**: In a machine control system, data from three different sensors (e.g., temperature, pressure, speed) should be forwarded to a subsequent processing unit, depending on the operating mode.
- **Redundancy**: Three identical data sources are available; if one source fails, the index can be switched via external logic to switch to another source.
- **Test Environments**: For switching between real and simulated data streams during commissioning.

## Comparison with Similar Function Blocks
- **Standard MUX** (e.g., `MUX` from IEC 61499 libraries): These typically work with data inputs directly on the function block and a single output data value. In contrast, `AULI_MUX_3` uses adapters, which enables loose coupling and the exchange of entire data structures.
- **AULI Splitter**: The counterpart that distributes one input to multiple outputs (e.g., `AULI_DISTRIBUTE`). While the MUX combines many sources into one output, the splitter distributes one source to many outputs.
- **Selector without Adapters**: A simple index-based function block with data inputs (e.g., `SEL`) typically only offers single values, not complex adapter interfaces.

## Conclusion

The `AULI_MUX_3` is a flexible, event-driven multiplexer that switches between up to three data sources via adapter interfaces. Its generic nature and the use of standard adapters make it ideal for modular and reusable control applications. The simple interface with only one index and one acknowledgment event allows for seamless integration into higher-level logic systems.
