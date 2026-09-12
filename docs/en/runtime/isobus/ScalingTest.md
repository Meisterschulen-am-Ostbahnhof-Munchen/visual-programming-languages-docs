# Scaling Test (SCALING-TEST)

## Purpose

The **SCALING-TEST** is a test feature in the VT client that lets you exercise [scaling](Scaling.md) of the object pools, [softkey reduction](SoftKeyReduction.md), and the [CCI colour fallback](#cci-colour-fallback-colour-indices-232-255) in a targeted way, **without changing the source code or recompiling**.

Normally, the following values are read live from the connected Virtual Terminal (VT) when the connection is established:

- the **Data Mask scaling factor** (`PoolDataMaskScalFaktor`)
- the **Softkey Mask scaling factor** (`PoolSoftKeyMaskScalFaktor`)
- the **number of physical softkeys** (`VT_PHYSICALSOFTKEYS`)
- the VT's **manufacturer code** (NAME field from the ISO 11783-5 address claim), which decides whether colour indices 232-255 are passed through unchanged or remapped

To test the behavior for different VT screen sizes, scaling factors, softkey counts, or VT manufacturers, you previously had to connect a real VT with the matching properties. With the SCALING-TEST, these values can instead be overridden through a setting in `settings.ini`.

!!! warning "Test purposes only"
    The SCALING-TEST is a developer/test tool. It is **disabled** by default and must not be left permanently enabled on production devices, since it deliberately bypasses the normal scaling safety clamp (see below).

## Configuration via `settings.ini`

The `settings.ini` file lives at, depending on the platform:

- `/data/settings.ini` (ESP32 target)
- `./settings.ini` (Linux/host build)

To enable the test, add the following section:

```ini
[ScalingTest]
enable = 1
skmScal = 15000
dmScal = 12000
softkeys = 8
```

### Keys (scaling and softkeys)

| Key        | Meaning                                                   | Valid values                             | Default (if not set)                   |
|------------|--------------------------------------------------------------|--------------------------------------------|-------------------------------------------|
| `enable`   | Master switch for the SCALING-TEST                           | `0` = off, `1` = on                        | `0` (off, normal behavior)                |
| `skmScal`  | Overrides the Softkey Mask scaling factor                     | integer factor, unit 1/10000 (`10000` = 100 %, `15000` = 150 %) | the value read live from the VT           |
| `dmScal`   | Overrides the Data Mask scaling factor                         | same as `skmScal`                          | the value read live from the VT           |
| `softkeys` | Overrides the number of physical softkeys (`sknu`)             | `6` to `11`                                  | the value read live from the VT           |

`skmScal`, `dmScal`, and `softkeys` are **only evaluated when `enable = 1` is set**. If the `[ScalingTest]` section is missing entirely, or `enable = 0`, the VT client behaves exactly as it would without this feature.

## Notes

- **The 111% clamp is skipped**: In normal operation, a Softkey Mask scaling factor between 90% and 111.11% is reset to 100% (so that, e.g., 80×80 and 72×72 softkeys aren't unnecessarily scaled — see [Scaling](Scaling.md)). When the SCALING-TEST is active, this safeguard is deliberately **not** applied, so the configured test value is visible exactly as set.
- **An invalid softkey count is rejected**: Softkey reduction (see [SoftKey Reduction](SoftKeyReduction.md)) only supports the values 6 through 11. If `softkeys` is set outside this range (e.g. `20` or `3`), the override is ignored, a debug message is logged, and the value read live from the VT is used instead.
- **No device restart required, but a VT reconnect is**: The values are evaluated every time the object pool is loaded (VT connection/reconnection). After changing `settings.ini`, you therefore need to reconnect to the VT (or restart the device) for the new values to take effect.

## Verification / expected debug output (scaling)

When the SCALING-TEST is active, the following extra line appears in the debug logs while the pool is loading:

```text
SCALING-TEST active: SKM_Scal=15000 DM_Scal=12000 (111% clamp skipped)
```

followed by the existing lines showing the (now overridden) values:

```text
PoolDataMaskScalFaktor    =  12000
PoolSoftKeyMaskScalFaktor =  15000
```

If an invalid softkey override is set (e.g. `softkeys = 20`), you instead see:

```text
SCALING-TEST: ignoring out-of-range softkeys override=20 (valid 6..11), using live value=12
```

### Example workflow

1. Edit `settings.ini` as described above.
2. Re-establish the VT connection (restart the device or disconnect/reconnect the VT).
3. Check the debug log (see above).
4. Visually verify on the connected VT: Data Mask objects are scaled by the `dmScal` factor, Softkey Mask objects are scaled/centered by the `skmScal` factor; with `softkeys = 8`, a pool authored for 12 softkeys now shows only 8 softkeys.
5. When done, set `enable = 0` (or remove the section) to restore normal, VT-derived behavior.

## CCI colour fallback (colour indices 232-255)

### Background (CCI colour fallback)

Per ISO 11783-6 Annex A ("VT standard colour palette", Table A.4), only colour indices **0-231** are guaranteed as a uniform standard palette - every ISOBUS VT must render them identically. Indices **232-255** are explicitly marked **"Proprietary"** by the standard: how a given VT displays them is manufacturer-specific and not defined.

The object pool uses colour indices from this range in a few places (e.g. a subtle grey row background in tables). On a **CCI VT** (Competence Center ISOBUS e.V., manufacturer code `339`) the appearance has already been checked and is as intended - there, these colour values are **passed through unchanged**. On **every other VT** (e.g. FENDT/AGCO - confirmed to render differently in a hardware test), colour indices 232-255 are instead **remapped to the nearest standard colour index (0-231)** via a lookup table before the pool is sent.

Detecting whether a CCI VT is connected happens automatically via the manufacturer code in the VT's NAME field (ISO 11783-5 address claim) - **no manual intervention needed in normal operation**. The SCALING-TEST lets you force or simulate this behavior on demand.

### Remapping table (colour indices 232-255 → 0-231)

Indices 232-255 form a 24-step greyscale ramp in the object pool (verified in Bucher ISO Designer and on real CCI and Bucher VT hardware). On a non-CCI VT (`forceCCI = 2`, or auto-detected), each of these values is mapped to a fixed nearest standard colour index (0-231, by Euclidean RGB distance per ISO 11783-6 Annex A, Table A.4):

| Colour index (pool) | → Standard index | Standard colour                  |
|-----------------------|---------------------|--------------------------------------|
| 232, 233               | `0`                  | Black (`#000000`)                    |
| 234–238                 | `59`                 | Dark grey (`#333333`)                |
| 239–243                 | `102`                | Grey (`#666666`)                     |
| 244–247                 | `8`                  | Grey (`#999999`)                     |
| 248–252                 | `7`                  | Silver (`#CCCCCC`)                   |
| 253–255                 | `1`                  | White (`#FFFFFF`)                    |

This mapping covers the colour indices currently used in the object pool (e.g. the grey table row background). If a future pool object ever uses a **non-grey** colour from 232-255, the mapping needs to be extended for that index - otherwise a shade of grey would appear instead on non-CCI VTs.

### Keys (CCI colour fallback)

| Key               | Meaning                                                                   | Valid values                                                                                                        | Default (if not set)              |
|--------------------|------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------|--------------------------------------|
| `forceCCI`         | Overrides the result of the CCI detection                                    | `0` = auto (real detection via manufacturer code), `1` = force CCI (colours unchanged), `2` = force non-CCI (lookup table), `3` = FENDT/AGCO simulation (every colour index 232-255 is replaced by `forceCCIColor`) | `0` (auto)                          |
| `manufCode`        | Overrides the manufacturer code read from the VT                             | any manufacturer code, e.g. `339` (CCI) or `102` (AGCO)                                                            | the value read live from the VT     |
| `forceCCIColor`    | Test colour for `forceCCI = 3` mode                                          | colour index `0`-`231`                                                                                              | `0` (black)                         |

`forceCCI`, `manufCode`, and `forceCCIColor` are **only evaluated when `enable = 1` is set** (same section, same master switch as the scaling options above).

### Example: simulating a non-CCI VT

```ini
[ScalingTest]
enable = 1
forceCCI = 2
```

### Example: FENDT/AGCO simulation with a signal colour

Shows every object that would normally use a colour index 232-255 in one fixed test colour, so all affected objects are visible at a glance on screen:

```ini
[ScalingTest]
enable = 1
forceCCI = 3
forceCCIColor = 12
```

(Colour index `12` = red; see the standard colour table per ISO 11783-6 Annex A.)

### Verification / expected debug output (colour fallback)

```text
CCI-Colour: manufCode=339 forceCCI=2 passthrough=0 solidTest=0/0
```

`passthrough=1` means colours are passed through unchanged (CCI detected, or `forceCCI = 1`). When `passthrough=0`, check `solidTest`: `solidTest=0` means the lookup table is applied (normal non-CCI case, or `forceCCI = 2`); `solidTest=1` means every colour index 232-255 is instead replaced by the fixed test colour (`forceCCIColor`) (`forceCCI = 3`).

## Colour depth simulation (16-colour / monochrome VTs)

### Background (colour depth simulation)

Independent of the CCI colour fallback, the VT client automatically detects when a connected VT itself supports **fewer colours** than the object pool (e.g. only 16 colours, or only black/white), and reduces the pool's colours accordingly - see [Colour reduction for Virtual Terminals with fewer colours](ColourReduction.md) for background and the full mapping tables. This happens fully automatically in normal operation, based on what the VT reports about its own capabilities.

`forceColourDepth` lets you simulate this behavior on demand via the SCALING-TEST, even while a real full 256-colour VT is connected - useful for checking how a pool will look on a simpler VT without needing that hardware. Pictures/icons in the pool are converted directly to the reduced colour depth; every other object (background, border, and text colours) follows the same mapping described in [Colour reduction for Virtual Terminals with fewer colours](ColourReduction.md).

### Colour depth values

`forceColourDepth` uses the same values a VT itself uses to report its own colour capability:

| Value | Meaning |
|---|---|
| `0` | Monochrome (black/white only) |
| `1` | 16 colours |
| `2` | 256 colours (= off, no simulation - normal behavior) |

### Keys (colour depth simulation)

| Key                  | Meaning                                                    | Valid values                                                                 | Default (if not set)       |
|-----------------------|-----------------------------------------------------------------|-----------------------------------------------------------------------------------|--------------------------------|
| `forceColourDepth`    | Simulates a VT with fewer colours                                | `0` = monochrome, `1` = 16 colours, `2` = 256 colours (off) - see table above | `2` (off)                       |

`forceColourDepth` is **only evaluated when `enable = 1` is set**, and applies on top of the CCI colour fallback (i.e. also to colour indices 232-255 that were already remapped).

### Example: simulating a 16-colour VT

```ini
[ScalingTest]
enable = 1
forceColourDepth = 1
```

### Verification / expected debug output (colour depth)

```text
CCI-Colour: manufCode=339 forceCCI=0 passthrough=1 solidTest=0/0 forceColourDepth=1
```

If an invalid value is set (e.g. `forceColourDepth = 5`), you instead see:

```text
CCI-Colour: ignoring out-of-range forceColourDepth=5 (valid 0=monochrome/1=colour_16/2=colour_256), using 2
```

## See also

- [Scaling](Scaling.md) — background on the scaling logic per ISO 11783-6
- [SoftKey Reduction](SoftKeyReduction.md) — background on softkey reduction
- [Colour reduction for Virtual Terminals with fewer colours](ColourReduction.md) — full 256→16 and 16→2 mapping tables
