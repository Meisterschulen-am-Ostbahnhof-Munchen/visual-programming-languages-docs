# FT_DERIV_10

```{index} single: FT_DERIV_10
```

Derivative with variable window size (0..9 periods)

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Init Request | |
| REQ | Normal Execution Request | in, K, Faktor, run |
| RST | Reset Buffer | |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | |
| CNF | Execution Confirmation | out, valid, DT_0, DI_0, DT_1, DI_1, DT_2, DI_2, DT_3, DI_3, DT_4, DI_4, DT_5, DI_5, DT_6, DI_6, DT_7, DI_7, DT_8, DI_8, DT_9, DI_9 |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| in | REAL | | Input Signal |
| K | UINT | 0 | Window Select: 0=1 Period, 9=10 Periods |
| Faktor | REAL | 1.0 | Multiplication Factor (formerly K) |
| run | BOOL | 1 | Enable calculation |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| out | REAL | Resulting Derivative based on K |
| valid | BOOL | True if buffer has enough data for K |
| DT_0 | UDINT | Delta T over 1 period |
| DI_0 | REAL | Delta In over 1 period |
| DT_1 | UDINT | Delta T over 2 period |
| DI_1 | REAL | Delta In over 2 period |
| DT_2 | UDINT | Delta T over 3 period |
| DI_2 | REAL | Delta In over 3 period |
| DT_3 | UDINT | Delta T over 4 period |
| DI_3 | REAL | Delta In over 4 period |
| DT_4 | UDINT | Delta T over 5 period |
| DI_4 | REAL | Delta In over 5 period |
| DT_5 | UDINT | Delta T over 6 period |
| DI_5 | REAL | Delta In over 6 period |
| DT_6 | UDINT | Delta T over 7 period |
| DI_6 | REAL | Delta In over 7 period |
| DT_7 | UDINT | Delta T over 8 period |
| DI_7 | REAL | Delta In over 8 period |
| DT_8 | UDINT | Delta T over 9 period |
| DI_8 | REAL | Delta In over 9 period |
| DT_9 | UDINT | Delta T over 10 period |
| DI_9 | REAL | Delta In over 10 period |