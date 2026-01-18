# FT_PIWL

```{index} single: FT_PIWL
```

PI Controller with Anti-Windup

version 1.3	11. mar. 2009
programmer 	hugo
tested by		oscat

FT_PIWL is a PI controller.
The PID controller works according to the fomula Y = IN *(KP+ KI * INTEG(e) ).
a rst will reset the integrator to 0
lim_h and Lim_l set the possible output range of the controller.
the output flag lim will signal that the output limits are active.
the integrator ist equipped with anti wind-up circuitry which limits trhe total output ranke to lim_l and lim_h

default values for KP = 1, KI = 1, ILIM_L = -1E37, iLIM_H = +1E38.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Init Request | |
| REQ | Normal Execution Request | IN, KP, KI, LIM_L, LIM_H |
| RST | Reset Integrator | IN |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | Y, LIM |
| CNF | Execution Confirmation | Y, LIM |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| IN | REAL | | Process Variable / Error Input |
| KP | REAL | 1.0 | Proportional Gain |
| KI | REAL | 1.0 | Integral Gain |
| LIM_L | REAL | -1.0E38 | Lower Limit |
| LIM_H | REAL | 1.0E38 | Upper Limit |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Y | REAL | Controller Output |
| LIM | BOOL | Limit Reached Flag |
