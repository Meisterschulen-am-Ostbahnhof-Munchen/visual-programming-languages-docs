# Scaling Test (SCALING-TEST)

## Purpose

The **SCALING-TEST** is a test feature in the VT client (`App_VTClient.c`) that lets you exercise [scaling](Scaling.md) of the object pools and [softkey reduction](SoftKeyReduction.md) in a targeted way, **without changing the source code or recompiling**.

Normally, the following values are read live from the connected Virtual Terminal (VT) when the connection is established:

- the **Data Mask scaling factor** (`PoolDataMaskScalFaktor`)
- the **Softkey Mask scaling factor** (`PoolSoftKeyMaskScalFaktor`)
- the **number of physical softkeys** (`VT_PHYSICALSOFTKEYS`)

To test the behavior for different VT screen sizes, scaling factors, or softkey counts, you previously had to connect a real VT with the matching properties. With the SCALING-TEST, these three values can instead be overridden through a setting in `settings.ini`.

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

### Keys

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

## Verification / expected debug output

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

## See also

- [Scaling](Scaling.md) — background on the scaling logic per ISO 11783-6
- [SoftKey Reduction](SoftKeyReduction.md) — background on softkey reduction
