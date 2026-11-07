# Servos

This page describes how model servos are connected to a logiBUS output and which values for `FREQ`, `PULSE_MIN` and `PULSE_MAX` of the block [logiBUS_QW_SERVO](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/en/latest/Bibliotheken/ExternalLibraries/logiBUS/io/DO-Servo/logiBUS_QW_SERVO/) fit.

!!! note "Origin of the data"
    The manufacturer data comes from the product description. Franz tested the values for the 9 g servo on the setup (the servo travels 90° in each direction). Franz measured the pulse widths of the driver with an oscilloscope (2026-11-06). I did not verify any of this myself.

## 9 g servo, 180°

Servo "5 pieces 9G servo motor, micro servo motors with cable, 180 degree high-performance servos" (Amazon B0H3BC3PSS).

| Item | Value |
|---|---|
| Cycle | 20 ms (50 Hz) |
| Pulse width | 0.5 to 2.5 ms for 0 to 180° |
| Operating voltage | 3 to 7.2 V |

Suitable values for the block:

| Parameter | Value |
|---|---|
| `FREQ` | `50` |
| `PULSE_MIN` | `T#500us` |
| `PULSE_MAX` | `T#2500us` |

The center is at 1.5 ms. With these values the servo travels exactly 90° in each direction. With the initial values of the block (`T#1000us` to `T#2000us`) it is only about ±35°.

## Recommendation for exercises on the trainer

!!! warning "Unverified values"
    This list is a recommendation from general knowledge (Claude), not a measurement and not a datasheet. Torque, pulse range and current were not looked up. Only the 9 g servo above (B0H3BC3PSS) is tested on hardware with 500/2500 µs at 50 Hz.

| Use | Recommendation | Why |
|---|---|---|
| Standard for the exercises | MG90S (9 g, metal gear) | Same size and connector as the 9 g servos, but with a metal gear. Withstands driving against the stop and turning by hand better than the plastic gears of the SG90 clones. |
| If it should be cheap | SG90 (Tower Pro original) | Fine for pure pointing. The clones vary a lot in angle and center, and the gear breaks easily. |
| If something visible should be moved | Hitec HS-311 or HS-422 (standard size, analog) | Robust, reliable characteristic, well documented. According to general knowledge they run on 4.8 to 6 V. |
| With more force | MG996R (standard size, metal) | A lot of force. But it draws a lot at start-up and stalls above 1 A, so it needs a strong 5 V supply. The clones are inaccurate. |
| If precision matters | Digital servo, for example Feetech or Savöx in standard size | Holds the position more rigidly, no jitter. Some also tolerate frequencies above 50 Hz, which the block can do through `FREQ`. |

General notes:

- **Supply:** never feed servos from the 3.3 V regulator of the ESP, but from a 5 V source of their own with enough current. Plan about 0.5 to 1 A peak per 9 g servo, more for standard size (rule of thumb, not measured). Common ground with the board.
- **Signal:** 3.3 V from the ESP is enough for most servos. Take the signal before the power stage.
- **Pulse width:** the values differ from model to model. Set `PULSE_MIN` and `PULSE_MAX` per servo, preferably with the oscilloscope and carefully up to just before the mechanical stop, symmetrically around 1.5 ms.

## Connection

- **Supply:** from a 5 V source of its own, not from the 3.3 V regulator of the ESP.
- **Ground:** common ground of the servo supply and the logiBUS board.
- **Signal:** the servo needs a logic level signal. On boards with a power stage, take the signal **before** the power stage, not at the power output (see [Power stages of the outputs](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/en/latest/hw/logiBUS/Leistungsstufen/)).

## Note on the mechanical stop

If a servo drives against the mechanical stop with too large a range, it hums and gets warm. Then reduce `PULSE_MIN` and `PULSE_MAX` symmetrically around 1.5 ms.

## Other servos

Other servo types with their values (for example car servos at 250 Hz) are in the table on the page of the block [logiBUS_QW_SERVO](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/en/latest/Bibliotheken/ExternalLibraries/logiBUS/io/DO-Servo/logiBUS_QW_SERVO/).
