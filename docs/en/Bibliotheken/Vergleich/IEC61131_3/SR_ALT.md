# SR (Bistable, Set Priority) - IEC 61131-3
The function block **SR** is a bistable element (flip-flop) where setting takes precedence over resetting.
## Interface
| Type | Name | Data Type | Description |
| :--- | :--- | :--- | :--- |
**Input** | S1 | BOOL | Set Input |
**Input** | R | BOOL | Reset Input |
**Output** | Q1 | BOOL | Output State |

## Function

The behavior corresponds to **Table 43** (Standard Bistable Function Blocks) of the DIN EN 61131-3 standard.

The logic is described by the following truth table:

| S1 | R | Q1 (current) | Description |
| :---: | :---: | :---: | :--- |
| 0 | 0 | Q1 (old) | Hold state |
| 0 | 1 | 0 | Reset |
| 1 | 0 | 1 | Set |
| 1 | 1 | 1 | **Priority Set** |

*Note: The initial state of the output variable `Q1` is `0` (FALSE) by default.*

## Logical Equation

In graphical representations (FBS), this is often depicted as an OR gate at the set input and a memory element, but logically, the state corresponds to:

Q1 := S1 OR (Q1 AND NOT R);
*(Taking into account the dominance of S1 during simultaneous activation)*
More precisely according to the normative framework (Table 43, 1a):

(Table 43, 1a):

*(Table 43, 1a):```text
Q1 := S1 OR (NOT R AND Q1);
If `S1` is TRUE, then `Q1` is TRUE, regardless of whether `R` is true.

## See also
* [E_SR (IEC 61499)](../../StandardLibraries/events/E_SR.md): The event-driven equivalent in IEC 61499. Note that there is no guaranteed "dominance" for concurrent events.

]
