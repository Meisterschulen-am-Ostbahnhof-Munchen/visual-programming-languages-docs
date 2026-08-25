# TON (On-Delay) - IEC 61131-3

The **TON** (Timer On-Delay) function block implements an on-delay. The output is only activated when the input signal is present for a defined period.
## Interface

| Type | Name | Data Type | Description |
| :--- | :--- | :--- | :--- |
| **Input** | IN | BOOL | Start Signal |
| **Input** | PT | TIME | Preset Time (Delay Time) |
| **Output** | Q | BOOL | Output Signal |
| **Output** | ET | TIME | Elapsed Time |

**Output**
## Function

The behavior corresponds to **Table 46** (Standard Function Blocks Timers) and **Figure 15 b)** (Turn-on Delay (TON) Time Behavior) of the standard DIN EN 61131-3.

- **Start:** When `IN` equals `TRUE`, the time measurement begins at `ET`.
- **Sequence:** When `ET` reaches the value of `PT` and `IN` is still `TRUE`, the output `Q` is set to `TRUE`.
- **Hold:** `Q` remains `TRUE` as long as `IN` is `TRUE`.
- **Abort:** When `IN` changes to `FALSE` (before or after `PT` expires), `ET` is reset to 0 and `Q` becomes `FALSE`.

## Time Diagram (Principle)

+---------------------+
IN    |                     |
--+                     +-------
:   PT   :
+------------+
Q              |            |
-----------+            +-------
:        :
ET    /--------X------------\
-/                       \------
