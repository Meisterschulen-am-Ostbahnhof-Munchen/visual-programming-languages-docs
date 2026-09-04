# ASRT_AX

![ASRT_AX](ASRT_AX.svg)

bidirectional Adapter Interface for 3 Events (forward, Set/Reset/Toggle) and 1 Bool (backward, AX-style)

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
| TOGGLE | Toggle / Switch output | |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| DI1 | BOOL | Indication (or Request) Data to Plug |
