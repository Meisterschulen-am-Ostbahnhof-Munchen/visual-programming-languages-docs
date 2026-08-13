# ATM_MUX_3

![ATM_MUX_3](./ATM_MUX_3.svg)

* * * * * * * * * *
## Introduction

The function block **ATM_MUX_3** is a generic multiplexer for ATM adapters (Automation Transfer Modules). It enables the selective routing of one of three incoming ATM adapters (IN1, IN2, IN3) to an outgoing ATM adapter (OUT). The active input is selected via the index parameter K, which is set by the REQ event.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Sets the index K and triggers the switching. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of successful index setting and switching. |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index for selecting the active input (0 for IN1, 1 for IN2, 2 for IN3). |

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Plug (OUT) | OUT | adapter::types::unidirectional::ATM | Output adapter that is connected to one of the three sockets depending on the K value. |
| Socket (IN1) | IN1 | adapter::types::unidirectional::ATM | First input adapter (for K=0). |
| Socket (IN2) | IN2 | adapter::types::unidirectional::ATM | Second input adapter (for K=1). |
| Socket (IN3) | IN3 | adapter::types::unidirectional::ATM | Third input adapter (for K=2). |

## Functionality

The module operates on the principle of a **1-out-of-3 multiplexer** for ATM adapters. An incoming **REQ** event takes the current value of the data input **K** and then switches the corresponding socket (IN1, IN2, or IN3) to the **OUT** plug. After a successful switch, the **CNF** event is output. The switch is event-driven, meaning that as long as no new REQ arrives, the current connection remains active.

# Functionality ## Technical Features

- **Generic Implementation**: The function block (FB) is implemented as a generic block (`GEN_ATM_MUX`) and can be adapted to other adapter types by adjusting the type parameters.
- **Unidirectional Adapters**: All involved ATM adapters are defined as unidirectional interfaces. The flow direction is from the input sockets to the output plug.
- **No Data Outputs**: The function block only forwards the adapter communication – no additional data values are output.
- **Safety Aspect**: The index K is not validated. Values outside the range 0 to 2 result in undefined behavior (no valid input selected). The user must ensure that K is always within the permissible range.

## State Overview

The FB does not have an explicit state machine. It is always in one of three logical states, determined by the last set index K:

- **State 0**: OUT is connected to IN1.
- **State 1**: OUT is connected to IN2.
- **State 2**: OUT is connected to IN3.

A change occurs only upon the arrival of the REQ event. The state remains until the next REQ.

## Application Scenarios

- **Switching Alternative ATM Sources**: In a control application where different sensor data (e.g., temperature, pressure, fill level) are to be transmitted via a single output channel depending on the operating mode.
- **Redundancy and Failover**: Three identical ATM adapter sources (e.g., from different sensors) can be monitored and switched to a common output line as needed.
- **Test and Simulation Environments**: Switching between real and test data sources without changing the wiring.

## Comparison with Similar Function Blocks

- **Event-Based Multiplexers for Standard Data Types**: Unlike multiplexers that switch simple data types (BOOL, INT), ATM_MUX_3 operates at the ATM adapter level – i.e., entire interfaces with multiple signals and protocols.
- **Multi-Level Multiplexers**: If more than three inputs are required, cascading multiple ATM_MUX_3 blocks or a standalone function block with a larger number of K inputs is necessary.
- **Adapter Selector (e.g., SELECT Adapter)**: Some libraries offer adapter selectors directly, but these often lack explicit index control via a data input and only switch based on events.

## Change Detection

The selected output plug (`OUT`) is only written and its adapter event only sent if the incoming value differs from the value currently held on `OUT`. If the value is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The **ATM_MUX_3** is a compact and flexible function block for dynamically switching three ATM adapters to a common output. Its simple handling via events and indexes makes it ideal for control applications where multiple similar sources need to be connected as required. Its generic design allows for broad reuse in various projects.
