# FB_RS_T_FF
![FB_RS_T_FF](./FB_RS_T_FF.svg)

* * * * * * * * * *
## Introduction
The function block `FB_RS_T_FF` implements a bistable, reset-dominant latch with an additional toggle function. It combines the properties of an RS flip-flop (set and reset) with the ability to toggle the output on each rising edge of the clock signal. The reset input has priority, followed by the set input, and then the toggle function.
## Interface Structure
### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `REQ` | Normal execution request – triggers the processing of the input signals. |

#### **Event Outputs**

| Event | Comment |
|----------|-----------|

| `CNF` | Confirms execution after the output `Q1` has been calculated. |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-------|-----------|

| `S` | BOOL | Set – sets the output `Q1` to `TRUE`, provided `R1` is not active at the same time. |

| `R1` | BOOL | Reset (dominant) – sets the output `Q1` to `FALSE` and takes precedence over `S` and Toggle. |

| `CLK` | BOOL | Clock – clock generator for the Toggle function; on a rising edge, `Q1` is inverted if neither Reset nor Set is active. |

### **Data Outputs**

| Variable | Type | Comment |

|----------|-------|-----------|

| `Q1` | BOOL | Latch output – displays the current stored state. |

### **Adapters**
This function block has no adapter interfaces.

#
## ## Functionality
The following algorithm is executed for each event `REQ`:

- **Reset dominant**: If `R1 = TRUE` occurs, `Q1` is immediately set to `FALSE` – regardless of any other inputs.
- **Set**: If `R1 = FALSE` and `S = TRUE` occur, `Q1` is set to `TRUE`.
- **Toggle**: If neither Reset nor Set is active (`R1 = FALSE`, `S = FALSE`), the toggle mechanism is triggered: If `CLK` assumes the value `TRUE` and a rising edge is detected (i.e., `CLK` was `FALSE` in the previous call, stored in the internal variable `EDGE`), then `Q1` is inverted (`Q1 := NOT Q1`).

If `CLK` assumes the value `TRUE` and a rising edge is detected (i.e., `CLK` was `FALSE` in the previous call, stored in the internal variable `EDGE`), then `Q1` is inverted (`Q1 := NOT Q1`). - The internal variable ``EDGE`` is then set to the current value of ``CLK`` to detect edges for the next call.

The algorithm is implemented in ST code as follows:

``structured text
IF R1 THEN
Q1 := BOOL#FALSE;
ELSIF S THEN
Q1 := BOOL#TRUE;
ELSIF CLK AND NOT EDGE THEN
Q1 := NOT Q1;
END_IF;
EDGE := CLK;
## Technical Features
- **Reset Dominance**: The R1 input has the highest priority; when set, it overrides both Set and Toggle commands.
- **Edge Detection**: The toggle occurs only on a rising edge of `CLK` (transition from `FALSE` to `TRUE`), which is implemented by the internal variable `EDGE`.
- **Initial State**: The internal variable `EDGE` is initialized with `TRUE`, preventing an unintended toggle from being triggered on the first call, as the condition `CLK AND NOT EDGE` would otherwise be met at a static `TRUE` level.
- **Data Type**: All inputs and outputs are of type `BOOL`.

## State Overview
The function block does not have an explicit state machine; the state is implicitly represented by the internal variables `Q1` and `EDGE`. A state table summarizes the behavior:

| Current `Q1` | `R1` | `S` | `CLK` (rising edge) | New `Q1` |

----------------|------|-----|---------------------------|-------------|

x | TRUE | x | x | FALSE |

x | FALSE| TRUE| x | TRUE |

x | FALSE| FALSE| TRUE (and previously FALSE) | NOT Q1 |

x | FALSE| FALSE| FALSE or no edge | unchanged |

## Application Scenarios
- **Reset-dominant control** with additional switching option, e.g., for manual override in safety circuits.
- **Toggle function** on clock edges, e.g., as a frequency divider or switch in digital logic circuits.
- **Combined set/reset/toggle control** in automation systems, where an output can be set by sensor signals and toggled by a push button.

## Comparison with similar components
- **RS flip-flop**: Pure RS without toggle; `FB_RS_T_FF` extends it with a toggle function.
- **Toggle flip-flop (T-FF)**: Pure toggle without set/reset; this component combines both functions, with the toggle only being executed when set/reset is inactive.
- **JK flip-flop**: Offers similar flexibility (set, reset, toggle) but requires two event inputs (e.g., for J and K). `FB_RS_T_FF` simplifies the interface to one event input and three Boolean values.

## Conclusion

FB_RS_T_FF` is a versatile function block that combines a reset-dominant latch with an edge-triggered toggle function. It is suitable for applications requiring both fixed set and reset signals as well as switchable state transitions. Its clear prioritization (Reset > Set > Toggle) and built-in edge detection make it robust and easy to integrate into control logic.
