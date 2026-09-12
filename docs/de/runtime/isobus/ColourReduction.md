# Farbreduktion für Virtual Terminals mit weniger Farben

## Zweck

Object Pools werden mit voller 256-Farben-Palette entworfen. Nicht jedes angeschlossene Virtual Terminal (VT) unterstützt jedoch 256 Farben - manche zeigen nur **16 Farben**, einfache Geräte nur **2 Farben (monochrom/schwarz-weiß)**.

Der VT-Client erkennt automatisch, wie viele Farben das angeschlossene VT tatsächlich darstellen kann, und reduziert die Farben des Object Pools passend, **bevor** er zum VT übertragen wird. Der Object Pool selbst muss dafür nicht angepasst werden - ein und derselbe Pool funktioniert unverändert auf einem 256-, 16- und 2-Farben-VT.

Das passiert vollautomatisch bei jedem Verbindungsaufbau, abhängig davon, was das angeschlossene VT selbst über seine Fähigkeiten meldet - es ist keine Konfiguration nötig.

## Stufe 1: 256 Farben → 16 Farben

Die volle Farbpalette (0-231, siehe [CCI-Farbfallback](ScalingTest.md#cci-farbfallback-farbindizes-232-255) für die Indizes 232-255) wird auf die folgenden 16 Grundfarben reduziert. Jede der 232 möglichen Farben wird auf die ihr am nächsten liegende dieser 16 Farben abgebildet:

| Farbindex | Farbe |
|---|---|
| `0` | Schwarz |
| `1` | Weiß |
| `2` | Grün |
| `3` | Türkis |
| `4` | Kastanienbraun |
| `5` | Violett |
| `6` | Oliv |
| `7` | Silber |
| `8` | Grau |
| `9` | Blau |
| `10` | Hellgrün |
| `11` | Cyan |
| `12` | Rot |
| `13` | Magenta |
| `14` | Gelb |
| `15` | Marineblau |

### Zuordnung der erweiterten Farbpalette (16-231)

Die Indizes 0-15 bleiben unverändert (sie sind bereits eine dieser 16 Farben). Die erweiterte Palette (16-231) wird nach folgender Zuordnung auf die nächstliegende der 16 Grundfarben reduziert:

| Farbindex-Bereich | → Grundfarbe |
|---|---|
| 16, 22, 52 | Schwarz |
| 17–19, 23–25, 53–55, 60 | Marineblau |
| 20–21, 26–27, 32–33, 38–39, 56–57, 61–63, 67–69, 74–75 | Blau |
| 28–29, 34–35, 64–65, 70–71, 106–107 | Grün |
| 30–31, 36–37, 66, 72–73, 108–109 | Türkis |
| 40–42, 46–49, 76–78, 82–85, 112–114, 118–121, 148–150, 154–157 | Hellgrün |
| 43–45, 50–51, 79–81, 86–87, 110–111, 115–117, 122–123, 151–153, 158–159, 194–195 | Cyan |
| 58, 100–101, 136–137, 142–144, 184–185 | Oliv |
| 59, 102–103, 138, 145–146 | Grau |
| 88–89, 94–95, 124–125, 130–131 | Kastanienbraun |
| 90–93, 96–99, 104–105, 126–129, 132–135, 139–141, 147 | Violett |
| 160–161, 166–168, 172–174, 178–181, 196–198, 202–204, 208–210 | Rot |
| 162–165, 169–171, 175–177, 183, 199–201, 205–207, 211–213, 217–219, 224–225 | Magenta |
| 182, 186–189 | Silber |
| 190–193, 214–216, 220–223, 226–229 | Gelb |
| 230–231 | Weiß |

## Stufe 2: 16 Farben → 2 Farben (monochrom)

Für sehr einfache VTs, die nur Schwarz und Weiß darstellen können, wird jede der 16 Grundfarben zusätzlich auf Schwarz oder Weiß reduziert:

| Grundfarbe | → Monochrom |
|---|---|
| Schwarz | Schwarz |
| Weiß | Weiß |
| Grün | Schwarz |
| Türkis | Schwarz |
| Kastanienbraun | Schwarz |
| Violett | Schwarz |
| Oliv | Schwarz |
| Silber | Weiß |
| Grau | Schwarz |
| Blau | Weiß |
| Hellgrün | Weiß |
| Cyan | Weiß |
| Rot | Weiß |
| Magenta | Weiß |
| Gelb | Weiß |
| Marineblau | Schwarz |

Ein VT, das nur 256 → 2 Farben unterstützt, durchläuft beide Stufen nacheinander (erst auf 16, dann auf 2 Farben).

## Siehe auch

- [CCI-Farbfallback](ScalingTest.md#cci-farbfallback-farbindizes-232-255) — betrifft die zusätzlichen, herstellerspezifischen Farbindizes 232-255, unabhängig von dieser Farbtiefenreduktion
- [Scaling](Scaling.md) — Hintergrund zur Skalierungslogik nach ISO 11783-6
