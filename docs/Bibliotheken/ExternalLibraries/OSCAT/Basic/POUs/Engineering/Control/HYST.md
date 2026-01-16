# HYST

Hystereses function

This Hystereses function has two modes:
1. if on > off then Q will be switched high when in > on and switched low when in < off.
2. if on < off then Q will be switched high when in < on and switched low when in > off.
the output win will be high when in is between low and high.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| REQ | | IN, ONN, OFF |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| CNF | | Q, WIN |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| IN | REAL | |
| ONN | REAL | |
| OFF | REAL | |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Q | BOOL | |
| WIN | BOOL | |
