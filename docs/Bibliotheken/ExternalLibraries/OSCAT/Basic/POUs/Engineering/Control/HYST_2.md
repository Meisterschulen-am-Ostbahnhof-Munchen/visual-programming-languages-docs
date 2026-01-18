# HYST_2

```{index} single: HYST_2
```

Hystereses function

this hysteresis function switches the output high if the input signal reaches obove val + hys/2
and will switch to low when the input falls back below val - hys/2 value.
a separate output mid is set if the input stays between low and high value.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| REQ | | IN, VAL, HYS |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| CNF | | Q, WIN |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| IN | REAL | |
| VAL | REAL | |
| HYS | REAL | |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Q | BOOL | |
| WIN | BOOL | |