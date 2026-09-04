# AE_AX

![AE_AX](AE_AX.svg)

bidirectional Adapter Interface for 1 Event (forward) and 1 Bool (backward, AX-style)

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| EI1 | Indication (or Request) | DI1 |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| E1 | Request (or Indication) | |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| DI1 | BOOL | Indication (or Request) Data to Plug |
