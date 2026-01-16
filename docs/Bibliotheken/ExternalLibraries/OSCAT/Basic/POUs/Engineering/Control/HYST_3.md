# HYST_3

Hystereses function

this is a double hysteresis function. Out1 follows a hysteresis function defined by val1and hyst,
while out 2 follows val2 and hyst.
if the input signal is between the two hysteresis switches (val1 and val2) then non of the
outputs is active.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| REQ | | in, hyst, val1, val2 |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| CNF | | Q1, Q2 |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| in | REAL | |
| hyst | REAL | |
| val1 | REAL | |
| val2 | REAL | |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Q1 | BOOL | |
| Q2 | BOOL | |
