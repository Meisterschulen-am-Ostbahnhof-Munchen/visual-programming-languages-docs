# Power stages of the outputs

This page describes which power drivers are fitted on the logiBUS boards, which frequency limits apply to PWM, and how much energy the switch may dissipate when an inductive load (valve coil) is switched off.

!!! note "Origin of the data"
    The assignment of the boards and the frequency limits come from the concept `PWM_KONZEPT.md` (table "Fitting per board") and from Franz. The datasheet values were read from the Infineon datasheets by the development session; they have not been checked against the datasheets here. The assignment has not been checked against the schematics. According to Franz, all outputs have a freewheeling diode.

## Fitting per board

| Board | Outputs | Power stage | Page |
|---|---|---|---|
| APIXON Node-ISO 20 | Q1–Q12 | BTT6030-2ERA | [APIXON Node-ISO 20](APIXON_Node-ISO_20.md) |
| APIXON 15 PWR | Q1 | BTH50030-1LUA | no page of its own |
| APIXON 15 PWR | Q7–Q12 | BTT6030-2ERA | no page of its own |
| Deca Out | all | BTS7030-2EPA | [DualCAN deca-output](DualCAN/DualCAN_deca_output_ESP32S3.md) |
| Octa Out | all | BTS7030-2EPA | [DualCAN octa-output](DualCAN/DualCAN_octa_output_ESP32S3.md) |
| Hutschienenmoped 2026 (XL26) | Q1–Q4 | BTS7030-2EPA | [Hutschienenmoped XL26](Hutschienenmoped/HutschienenmopedXL26.md) |
| Hutschienenmoped 2026 (XL26) | Q5–Q8 | two BTM9010EP (H-bridge), PWM on the low side Q56 and Q78 | [Hutschienenmoped XL26](Hutschienenmoped/HutschienenmopedXL26.md) |
| Dual Out 12-24-48V | all | BTH6070-2EPV | page assignment open |
| Dual Out 12V | all | BTS7030-2EPA | page assignment open |
| Hutschienenmoped 12V | all | BTS7030-2EPA | page assignment open |
| Trainer20 | Q01–Q08 | no power stage | [Trainer20](Trainer20.md) |

Other boards (for example M5, lilygo) are not yet covered.

## Frequency limits for PWM

The firmware does not check these limits. They are given as a hint in the comment of `FREQ` of the PWM blocks.

| Power stage | Limit |
|---|---|
| BTH50030-1LUA (APIXON 15 PWR Q1) | at most 100 Hz (datasheet: maximum input frequency `fIN` = 100 Hz) |
| BTS7030-2EPA, BTT6030-2ERA, BTH6070-2EPV | for valves 100 to 200 Hz |
| Trainer20 | no power stage, any frequency |

## Turn-off energy of inductive loads

When a coil is switched off, the stored energy has to go somewhere.

- **With a freewheeling diode** (all logiBUS outputs according to Franz): the diode dissipates the coil energy. With valve PWM the energy is therefore not dissipated in the clamp of the switch.
- **Without a diode or with a defective diode** (for example a coil connected directly without a diode): the switch clamps the voltage itself and the energy is dissipated in the switch. The energy limits in the table apply to this case.

The limits are documented anyway, because they matter for a diode failure or for loads without a diode.

| Switch | Family | Clamp voltage | Single pulse `EAS` | Repetitive `EAR` / note | Datasheet |
|---|---|---|---|---|---|
| BTS7030-2EPA | PROFET+2 12 V, 2 × 30 mΩ | `VDS(CLAMP)` at least 35 V | at most 38 mJ at `IL` = 2 · `IL(NOM)` | at most 18 mJ at `IL(NOM)`, `TJ(0)` = 85 °C | 2024-07-29 |
| BTT6030-2ERA | PROFET+2 12/24 V, 2 × 30 mΩ | `VDS(AZ)` 66 to 75 V | at most 85 mJ at `IL(0)` = 4 A, `TJ(0)` = 150 °C, `VS` = 28 V | protection functions not designed for continuous repetitive operation | Rev. 2019-03-09 |
| BTH6070-2EPV | PROFET+ 48 V, 2 × 60 mΩ (on DualOut 48V) | `VDS(CLAMP)` 65 to 75 V | at most 40 mJ at `IL(NOM)` = 2.17 A | also not designed for repetitive operation | Rev. 1.00, 2025-11-15 |
| BTH50030-1LUA | Power PROFET+ 24/48 V, 3 mΩ, 25 A | Smart Clamp with fast turn-off | limit curve `EAS`/`EAR` over `IL` (datasheet, Figure 6) | switching energy at high load about 9 to 12.5 mJ on and 7 to 10 mJ off; `fIN` at most 100 Hz | – |
| BTM9010EP (H-bridge) | bridge with its own freewheeling diodes | – | – | diode forward voltage `Vf` at most 0.9 V at 2 A, 150 °C | – |

For turning off a coil `L` with resistance `RL` through the clamp, the datasheet gives the clamp energy as:

```text
E = VDS(CLAMP) · L/RL · [ (VS − VDS(CLAMP))/RL · ln(1 − RL·IL/(VS − VDS(CLAMP))) + IL ]
```

With PWM and no diode, this energy occurs in every period. The power dissipated in the switch is then `E` times the PWM frequency. Example: 18 mJ at 100 Hz is 1.8 W from the clamp alone.

## Sources

- Infineon BTS7030-2EPA (<https://www.infineon.com/part/BTS7030-2EPA>)
- Infineon BTT6030-2ERA (<https://www.infineon.com/part/BTT6030-2ERA>)
- Infineon BTH6070-2EPV (<https://www.infineon.com/part/BTH6070-2EPV>)
- Infineon BTH50030-1LUA (<https://www.infineon.com/part/BTH50030-1LUA>)
- Infineon BTM9010EP (<https://www.infineon.com/part/BTM9010EP>)
