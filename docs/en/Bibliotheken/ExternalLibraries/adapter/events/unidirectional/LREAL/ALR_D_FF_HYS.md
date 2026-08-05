# ALR_D_FF_HYS

![ALR_D_FF_HYS](./ALR_D_FF_HYS.svg)

* * * * * * * * * *

## Introduction

The **ALR_D_FF_HYS** function block implements a data latch (D flip-flop) with adjustable hysteresis. It receives a data value via an adapter socket and outputs the latched value via an adapter plug. The hysteresis is set during the initialization event and serves to suppress noise or small fluctuations in the input signal.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|-------|-----|---------------|

| INIT | EInit | Sets the hysteresis (with the data value `HYSTERESIS`) and starts the initialization. |

### **Event Outputs**

| Event | Type | Description |

|--------|-----|--------------|

| INITO | EInit | Confirms successful initialization. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-----|--------------|

| HYSTERESIS | LREAL | Size of the hysteresis band (passed on the `INIT` event). |

### **Data Outputs**

The FB has no direct data outputs. The latched value is output exclusively via the adapter plug `Q`.

### **Adapter**

| Name | Type | Direction | Description |

|-------------|-----|-----------|--------------|

| I (Socket) | `adapter::types::unidirectional::ALR` | Input | Receives the value to be latched via the event `I.E1` and the associated data value `I.D1`. |

| Q (Plug) | `adapter::types::unidirectional::ALR` | Output | Outputs the latched value via the event `Q.E1` and the data value `Q.D1`. |

The adapter used, **ALR**, is a unidirectional data adapter with one event (`E1`) and one data value (`D1`).

## Functionality

The function block (FB) works internally with the block `E_D_FF_ANY_HYS`, which implements the actual latch and hysteresis logic. The sequence of events is as follows:

1. **Initialization**: Upon arrival of `INIT`, the value of `HYSTERESIS` is forwarded to the internal block, and the output event `INITO` is immediately acknowledged.

2. **Latch Operation**: On each rising edge of the event `I.E1` (from the socket), the current data value `I.D1` is adopted. However, the latched value is only output when it leaves the band defined by the hysteresis. This suppresses small changes around the current latch value.

3. **Output**: As soon as the latched value leaves the hysteresis band, the internal function block generates an event on `EO`, which is output externally as `Q.E1`, and the new value is available on `Q.D1`.

## Technical Features

- The hysteresis is set exclusively on the `INIT` event and remains constant during operation.

- The function block (FB) does not use its own state machine, but delegates all logic to the internal block `E_D_FF_ANY_HYS`.

- The initial state of the latch is undefined; initialization with `INIT` is mandatory before valid latch operations can occur.

## State Overview

Since the FB implements the behavior via an internal block, there is no separate state diagram. The internal block `E_D_FF_ANY_HYS` typically operates with the following states:

- **Initial** – Waiting for the hysteresis setting.

- **Normal** – Latch operation with hysteresis band check (delayed output update).

- **Output** – Sending the newly latched value via the output adapter.


## Application Scenarios

- **Signal Conditioning**: Latching of measured values with noise suppression in automation technology.

- **Debouncing**: Processing of switching signals where short pulses or bouncing need to be suppressed.

- **Threshold Monitoring**: Detection of analog values that only assume a new valid state above or below a hysteresis band.

## Comparison with Similar Components

| Component | Property |

|----------|-------------|

| Simple D flip-flop (e.g., `E_D_FF`) | Latch without hysteresis – any change at the input is immediately registered. |

| D flip-flop with deadband (`E_D_FF_TOTBAND`) | It has a deadband that blocks changes as long as the value remains within the band. |

**ALR_D_FF_HYS** | Hysteresis is only effective in one direction (threshold behavior), typically used to prevent flutter. |

## Conclusion

The ALR_D_FF_HYS is a specialized function block for applications where a data value needs to be latched and hysteresis applied simultaneously for noise suppression. Encapsulating the logic in an internal block keeps the interface simple and allows for flexible use via the adapter interface.