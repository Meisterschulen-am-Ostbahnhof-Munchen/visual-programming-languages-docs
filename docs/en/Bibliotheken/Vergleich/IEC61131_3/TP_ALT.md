# TP (Pulse) - IEC 61131-3
The **TP** (Timer Pulse) function block implements a pulse generator (monoflop). It generates an output pulse of defined duration.
## Interface
| Type | Name | Data Type | Description |
| :--- | :--- | :--- | :--- |
**Input** | IN | BOOL | Start signal (rising edge triggers pulse) |

**Input** | PT | TIME | Preset Time (pulse duration) |

**Output** | Q | BOOL | Output signal |

**Output** | ET | TIME | Elapsed Time (time elapsed since pulse start) |

## Function

The behavior corresponds to **Table 46** (Standard Function Blocks Timers) and **Figure 15 a)** (Pulse (TP) Timing Behavior) of the standard DIN EN 61131-3.

- **Start:** When `IN` changes from `FALSE` to `TRUE` (rising edge), the output `Q` is set to `TRUE` and the timing measurement `ET` starts.
- **Duration:** The output `Q` remains at `TRUE` for the duration `PT`, regardless of whether `IN` changes back to `FALSE` during that time.
- **Reset:** After the time `PT` has elapsed (i.e., `ET` >= `PT`), `Q` reverts to `FALSE`.
- **Re-Trigger:** The pulse is **not** retriggerable. Edges at the input `IN` during pulse output (as long as `ET` < `PT` and `Q` = `TRUE`) are ignored.
- **Initialization:** `ET` is reset when `IN` `FALSE` and the timer has expired or has not yet started.

## Timing Diagram (Principle)

```text
+--------+
IN    |        |
--+        +--------------------------
:   PT   :
+--------+
Q     |        |
--+        +--------------------------
:        :
ET    /--------\
-/          \-------------------------
