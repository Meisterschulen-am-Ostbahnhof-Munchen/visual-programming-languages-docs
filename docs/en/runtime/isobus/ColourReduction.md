# Colour reduction for Virtual Terminals with fewer colours

## Purpose

Object pools are designed with the full 256-colour palette. Not every connected Virtual Terminal (VT), however, supports 256 colours - some only display **16 colours**, and simple devices only **2 colours (monochrome/black and white)**.

The VT client automatically detects how many colours the connected VT can actually display, and reduces the object pool's colours accordingly **before** it is transferred to the VT. The object pool itself does not need to be adapted for this - the same pool works unchanged on a 256-, 16-, and 2-colour VT.

This happens fully automatically on every connection, based on what the connected VT itself reports about its capabilities - no configuration is required.

## Stage 1: 256 colours → 16 colours

The full colour palette (0-231, see [CCI colour fallback](ScalingTest.md#cci-colour-fallback-colour-indices-232-255) for indices 232-255) is reduced to the following 16 base colours. Each of the 232 possible colours is mapped to whichever of these 16 colours is closest to it:

| Colour index | Colour |
|---|---|
| `0` | Black |
| `1` | White |
| `2` | Green |
| `3` | Teal |
| `4` | Maroon |
| `5` | Purple |
| `6` | Olive |
| `7` | Silver |
| `8` | Grey |
| `9` | Blue |
| `10` | Lime |
| `11` | Cyan |
| `12` | Red |
| `13` | Magenta |
| `14` | Yellow |
| `15` | Navy |

### Mapping the extended colour palette (16-231)

Indices 0-15 stay unchanged (they are already one of these 16 colours). The extended palette (16-231) is reduced to the nearest of the 16 base colours as follows:

| Colour index range | → Base colour |
|---|---|
| 16, 22, 52 | Black |
| 17–19, 23–25, 53–55, 60 | Navy |
| 20–21, 26–27, 32–33, 38–39, 56–57, 61–63, 67–69, 74–75 | Blue |
| 28–29, 34–35, 64–65, 70–71, 106–107 | Green |
| 30–31, 36–37, 66, 72–73, 108–109 | Teal |
| 40–42, 46–49, 76–78, 82–85, 112–114, 118–121, 148–150, 154–157 | Lime |
| 43–45, 50–51, 79–81, 86–87, 110–111, 115–117, 122–123, 151–153, 158–159, 194–195 | Cyan |
| 58, 100–101, 136–137, 142–144, 184–185 | Olive |
| 59, 102–103, 138, 145–146 | Grey |
| 88–89, 94–95, 124–125, 130–131 | Maroon |
| 90–93, 96–99, 104–105, 126–129, 132–135, 139–141, 147 | Purple |
| 160–161, 166–168, 172–174, 178–181, 196–198, 202–204, 208–210 | Red |
| 162–165, 169–171, 175–177, 183, 199–201, 205–207, 211–213, 217–219, 224–225 | Magenta |
| 182, 186–189 | Silver |
| 190–193, 214–216, 220–223, 226–229 | Yellow |
| 230–231 | White |

## Stage 2: 16 colours → 2 colours (monochrome)

For very simple VTs that can only display black and white, each of the 16 base colours is further reduced to black or white:

| Base colour | → Monochrome |
|---|---|
| Black | Black |
| White | White |
| Green | Black |
| Teal | Black |
| Maroon | Black |
| Purple | Black |
| Olive | Black |
| Silver | White |
| Grey | Black |
| Blue | White |
| Lime | White |
| Cyan | White |
| Red | White |
| Magenta | White |
| Yellow | White |
| Navy | Black |

A VT that only supports 256 → 2 colours goes through both stages in sequence (first down to 16, then down to 2 colours).

## See also

- [CCI colour fallback](ScalingTest.md#cci-colour-fallback-colour-indices-232-255) — covers the additional, manufacturer-specific colour indices 232-255, independent of this colour depth reduction
- [Scaling](Scaling.md) — background on the scaling logic per ISO 11783-6
