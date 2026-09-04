# ASR_AX

![ASR_AX](ASR_AX.svg)

bidirectional Adapter Interface for 2 Events (forward, Set/Reset) and 1 Bool (backward, AX-style)

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| EI1 | Indication (or Request) | DI1 |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| SET | Set / Switch on | |
| RESET | Reset / Switch off | |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| DI1 | BOOL | Indication (or Request) Data to Plug |
