# FT_PIDWL

```{index} single: FT_PIDWL
```

PI Controller with Anti-Windup

version 1.3	13. nov. 2009
programmer 	hugo
tested by		tobias

FT_PIDWL is a PID controller with dynamic wind_up reset.
The PID controller works according to the fomula Y = KP *(IN + KI * INTEG(e) + DERIV(e) ).
a rst will reset the integrator to 0
lim_h and Lim_l set the possible output range of the internal integrator.
the output flags lim will signal that the output limits are active.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Init Request | |
| REQ | Normal Execution Request | IN, KP, TN, TV, LIM_L, LIM_H |
| RST | Reset Integrator | IN |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | Y, LIM |
| CNF | Execution Confirmation | Y, LIM |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| IN | REAL | | Process Variable Input |
| KP | REAL | 1.0 | Proportional Gain |
| TN | REAL | 1.0 | Integral Time |
| TV | REAL | 1.0 | Derivative Time |
| LIM_L | REAL | -1.0E38 | Output Limit Low |
| LIM_H | REAL | 1.0E38 | Output Limit High |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Y | REAL | PID Output |
| LIM | BOOL | Limit reached flag |