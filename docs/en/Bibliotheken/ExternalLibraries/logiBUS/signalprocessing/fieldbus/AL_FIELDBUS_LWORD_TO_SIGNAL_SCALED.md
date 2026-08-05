# AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED

![AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED](./AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Introduction
The function block `AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED` converts a fieldbus signal (LWORD) into a scaled value with an offset. A valid output signal is only generated if the input signal is marked as valid. Validity is maintained via an internal D flip-flop and output as a Boolean signal.

## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|-----------|

| INIT | EInit | Initialization Request |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|-----------|

| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|--------|-------|--------------|-----------------------------|

| SCALE | LREAL | 1.0 | Scaling Factor |

| OFFSET | DINT | 0 | Offset Added After Scaling |

### **Adapters**

| Type | Direction | Name | Comment |

|------|----------|-------|--------------------------|

| AL | Socket | IN | Input Signal (LWORD) |

| ALR | Plug | OUT | Output signal (scaled) |

AX | Plug | VALID | Signal valid (TRUE/FALSE) |

## Functionality
The function block contains two internal components:

- **FIELDBUS_LWORD_TO_SIGNAL_SCALED**: Performs the actual conversion of the LWORD input using the SCALE and OFFSET parameters. Upon an event at `IN.E1` (connected to `REQ`), the processed value is set to `OUT` and the validity signal to `VALID`.

- **E_D_FF**: An edge-triggered D flip-flop that takes the validity signal from the previous function block. The clock signal (`CLK`) is triggered by the acknowledgment event (`CNF`) of the first block. The output `Q` is written to the adapter `VALID.D1`.

This results in the following sequence:

1. An incoming event at `IN.E1` starts the processing.

2. The internal block calculates the scaled value and outputs the validation signal.

3. The flip-flop stabilizes this signal and passes it to the `VALID` adapter.

4. Simultaneously, the scaled value is output via the `OUT` adapter.

The INIT interface is used for initialization and is passed through directly.


## Technical Features

- The INIT and INITO connections are marked as invisible in the network, but they exist for a clean initialization cascade.

- Scaling and offset are passed internally to the subordinate function block (FB) and are directly configurable.

- The D flip-flop prevents unwanted edges or momentary invalidity changes at the output.

## State Overview
The FB does not have an explicit state machine (ECC). Its behavior is controlled by event processing:

- **After INIT**: The FB is ready to receive events at `IN.E1`.

- **After each REQ/CNF cycle**: A new scaled value and an updated validity signal are available at the adapters.


## Application Scenarios
Typical application areas include:

- Conversion of raw fieldbus data (e.g., LWORD from PROFIBUS, CAN, etc.) into physical quantities (temperature, pressure, speed) with user-defined scaling.

- Forwarding of sensor data where only values marked as valid should be passed to the subsequent logic.

- Integration into plant control systems that require a clean initialization sequence (via INIT).

## Comparison with Similar Function Blocks
Simpler LWORD conversion function blocks often lack integrated validity checking and output the signal directly. `AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED` adds this functionality with:

- A separate validity signal, edge-triggered via a D flip-flop.

- An explicit initialization interface.

The combination of scaling, offset, and validity latch distinguishes it from simple conversion function blocks.


## Conclusion

This functional block represents a robust solution for conditioning fieldbus signals. It combines scaling, offset shifting, and reliable validity indication in a compact, initializable component. The use of a D flip-flop stabilizes the signal quality, which is particularly advantageous in safety-critical or noisy environments.