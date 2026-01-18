# HYST_1

```{index} single: HYST_1
```

Hystereses function

this hysteresis function switches the output high if the input signal reaches obove high and will
switch to low when the input falls back below low value.
a separate output mid is set if the input stays between low and high value.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| REQ | | In, high, low |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| CNF | | Q, win |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| In | REAL | |
| high | REAL | |
| low | REAL | |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Q | BOOL | |
| win | BOOL | |