# RS (Bistable, Priority Reset) - IEC 61131-3
The function block **RS** is a bistable element (flip-flop) where resetting takes precedence over setting.
## Interface
| Type | Name | Data Type | Description |
| :--- | :--- | :--- | :--- |
**Input** | S | BOOL | Set Input (Set) |

**Input** | R1 | BOOL | Reset Input (Reset) |

**Output** | Q1 | BOOL | Output State |

## Function

The behavior corresponds to **Table 43** (Standard Bistable Function Blocks) of the DIN EN 61131-3 standard.

The logic is described by the following truth table:

| S | R1 | Q1 (current) | Description |

| :---: | :---: | :---: | :--- |

| 0 | 0 | Q1 (old) | Hold state |

| 0 | 1 | 0 | Reset |

| 1 | 0 | 1 | Set |

| 1 | 1 | 0 | **Priority Reset** |

*Note: The initial state of the output variable `Q1` is `0` (FALSE) by default.*

## Logical Equation

According to the function block body in the standard (Table 43, 2a):

Q1 := NOT R1 AND (S OR Q1);
If ``R1`` is TRUE, the expression ``NOT R1`` becomes FALSE, and thus ``Q1`` inevitably becomes ``FALSE`` (0), regardless of the state of ``S``. This implements reset dominance.

## See also
* [E_RS (IEC 61499)](../../StandardLibraries/events/E_RS.md): The event-driven equivalent in IEC 61499. Note that there is no guaranteed "dominance" for concurrent events.
