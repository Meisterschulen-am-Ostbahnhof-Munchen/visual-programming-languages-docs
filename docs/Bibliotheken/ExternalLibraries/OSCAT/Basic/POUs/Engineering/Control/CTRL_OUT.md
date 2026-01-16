# CTRL_OUT

Control Output with Limit and Manual Override

CTRL_OUT adds to the CI input the value of OFFSET and returns the result
to Y if MANUAL = FALSE. If MANUAL is TRUE at output Y the input value of
MAN_IN + OFFSET is issued. Y is always limited to the boundaries defined
by LIM_L and LIM_H. If Y reaches one of the limits, then the output LIM is
TRUE. CTRL_OUT can be used to build own rule modules.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| REQ | Normal Execution Request | CI, OFFSET, MAN_IN, LIM_L, LIM_H, MANUAL |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| CNF | Execution Confirmation | Y, LIM |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| CI | REAL | Control Input |
| OFFSET | REAL | Offset |
| MAN_IN | REAL | Manual Input Value |
| LIM_L | REAL | Low Limit |
| LIM_H | REAL | High Limit |
| MANUAL | BOOL | Manual Mode Active |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Y | REAL | Control Output |
| LIM | BOOL | Limit Reached Flag |
