# TOF (Timer Off-Delay) - IEC 61131-3

The function block **TOF** (Timer Off-Delay) implements a timer off. The output remains active for a defined period after the input signal ceases.
## Interface

| Type | Name | Data Type | Description |
| :--- | :--- | :--- | :--- |
**Input** | IN | BOOL | Start Signal |
**Input** | PT | TIME | Preset Time (Delay Time) |
**Output** | Q | BOOL | Output Signal |
**Output** | ET | TIME | Elapsed Time (Time Elapsed Since Falling Edge) |

## Function

The behavior corresponds to **Table 46** (Standard Function Blocks Timers) and **Figure 15 c)** (Turn-off Delay (TOF) Time Behavior) of the standard DIN EN 61131-3.

- **Activation:** When `IN` is `TRUE`, the output `Q` is immediately set to `TRUE`, and `ET` is held at 0.
- **Start Delay:** When `IN` transitions from `TRUE` to `FALSE` (falling edge), the time measurement `ET` starts. `Q` remains `TRUE`.
- **Process:** When `ET` reaches the value of `PT`, the output `Q` is set to `FALSE`.
- **Reset:** If `IN` becomes `TRUE` again before the time expires, `ET` is reset to 0, and `Q` remains `TRUE`.

## Time Diagram (Principle)

+--------+
IN    |        |
--+        +------------------------
:        :   PT   :
+-----------------+
Q     |                 |
--+                 +---------------
:        :        :
ET             /--------\
-----------/         \--------------
