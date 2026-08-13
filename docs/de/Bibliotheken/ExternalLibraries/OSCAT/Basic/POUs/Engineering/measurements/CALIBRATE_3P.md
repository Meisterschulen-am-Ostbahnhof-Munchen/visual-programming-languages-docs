# CALIBRATE_3P

![CALIBRATE_3P](CALIBRATE_3P.svg)

* * * * * * * * * *
## Einleitung

`CALIBRATE_3P` ist eine Drei-Punkt-Kalibrierung für Roheingänge mit Mittelstellung, wie sie typischerweise bei Joysticks auftritt. Statt einer linearen Skalierung wie [CALIBRATE](CALIBRATE.md) interpoliert er stückweise linear zwischen drei gespeicherten Referenzpunkten (Min, Mid, Max) und kompensiert damit auch eine Mittelstellung, die nicht exakt in der Mitte des Rohbereichs liegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Normale Ausführungsanforderung, liefert `X`, `C_MIN`, `C_MID`, `C_MAX`, `MIN_REF`, `MID_REF`, `MAX_REF`, `X_MIN`, `X_MID`, `X_MAX`. Berechnet bei jedem Aufruf `Y` neu und führt dabei ggf. eine Kalibrierung durch.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die Ausführung, liefert `Y`, `X_MIN`, `X_MID`, `X_MAX`.

### **Daten-Eingänge**

- **X** (REAL): Roheingangswert.
- **C_MIN** (BOOL): Löst bei `TRUE` die Kalibrierung des Minimalpunkts aus.
- **C_MID** (BOOL): Löst bei `TRUE` die Kalibrierung des Mittelpunkts aus.
- **C_MAX** (BOOL): Löst bei `TRUE` die Kalibrierung des Maximalpunkts aus.
- **MIN_REF** (REAL, Startwert `0.0`): Zielausgabewert für den Minimalpunkt.
- **MID_REF** (REAL, Startwert `50.0`): Zielausgabewert für den Mittelpunkt.
- **MAX_REF** (REAL, Startwert `100.0`): Zielausgabewert für den Maximalpunkt.

### **Daten-Ausgänge**

- **Y** (REAL): Kalibrierter, interpolierter und auf `MIN_REF..MAX_REF` begrenzter Ausgangswert.

### **Ein-/Ausgabevariablen (InOut)**

- **X_MIN** (REAL, Startwert `0.0`): Gespeicherter Rohwert am Minimalpunkt.
- **X_MID** (REAL, Startwert `50.0`): Gespeicherter Rohwert am Mittelpunkt.
- **X_MAX** (REAL, Startwert `100.0`): Gespeicherter Rohwert am Maximalpunkt.

## Funktionsweise

Bei jedem `REQ` prüft `CALIBRATE_3P` zunächst `C_MIN`, `C_MID` und `C_MAX` (als `ELSIF`-Kette, höchstens ein Kalibrierpunkt pro Aufruf) und speichert bei gesetztem Flag den aktuellen Rohwert `X` im jeweiligen `X_MIN`/`X_MID`/`X_MAX`.

Anschließend wird `Y` stückweise linear interpoliert:

- Für `X < X_MID`: Interpolation zwischen `(X_MIN, MIN_REF)` und `(X_MID, MID_REF)`.
- Für `X >= X_MID`: Interpolation zwischen `(X_MID, MID_REF)` und `(X_MAX, MAX_REF)`.
- Das Ergebnis wird auf den Bereich `MIN_REF..MAX_REF` begrenzt (Clipping).

Die drei Kalibrierpunkte können in **beliebiger Reihenfolge** und beliebig oft einzeln wiederholt werden -- pro `REQ`-Aufruf wird jedoch höchstens einer davon aktualisiert.

**Beispiel** (Joystick mit Mittelpunkt-Drift, Rohbereich `0..1000`, gewünschter Ausgabebereich `-100..0..100`):

| Schritt | Aktion | Ergebnis |
|---|---|---|
| 1 | Joystick auf **Minimum**, `C_MIN=TRUE` | `X_MIN = 50` (Drift gegenüber ideal `0`) |
| 2 | Joystick auf **Mitte**, `C_MID=TRUE` | `X_MID = 520` (Drift gegenüber ideal `500`) |
| 3 | Joystick auf **Maximum**, `C_MAX=TRUE` | `X_MAX = 980` (Drift gegenüber ideal `1000`) |

Ergebnis: `Y` wird zwischen `MIN_REF=-100`, `MID_REF=0` und `MAX_REF=100` interpoliert und begrenzt -- die tatsächliche (verschobene) Mittelstellung des Joysticks liefert exakt `Y=0`.

## Technische Besonderheiten

- **Kompensation der Mittelstellung**: Anders als bei einer reinen Zwei-Punkt-Kalibrierung (siehe [CALIBRATE](CALIBRATE.md)) wird die Mittelstellung explizit erfasst -- wichtig bei Joysticks, deren mechanische Ruhelage nicht exakt in der Mitte des elektrischen Rohbereichs liegt.
- **Ausgabe stets begrenzt**: `Y` wird nach der Interpolation auf `MIN_REF..MAX_REF` geklippt, auch wenn `X` außerhalb der kalibrierten Rohwerte liegt.
- **Degenerierte Kalibrierpunkte**: Liegt `X_MID` nicht oberhalb von `X_MIN` (bzw. `X_MAX` nicht oberhalb von `X_MID`), liefert die betroffene Interpolation konstant `MIN_REF` bzw. `MID_REF`, statt durch Null zu teilen.
- **Reihenfolge nicht erzwungen**: Wie bei `CALIBRATE` liegt es als `SimpleFB` in der Verantwortung des Aufrufers, sinnvolle Kalibrierwerte zu liefern. Für eine ereignisgesteuerte Variante siehe [E_CALIBRATE_3P](E_CALIBRATE_3P.md).

## Zustandsübersicht

`CALIBRATE_3P` ist ein `SimpleFB` mit einem einzigen `ECState` (`REQ`): Jeder Aufruf führt unmittelbar den `REQ`-Algorithmus aus und feuert `CNF`. Es gibt keine Zustandsübergänge -- welcher Kalibrierpunkt (falls überhaupt) aktualisiert wird, ergibt sich rein aus `C_MIN`/`C_MID`/`C_MAX` zum Zeitpunkt des Aufrufs.

## Anwendungsszenarien

- Kalibrierung von Joysticks und ähnlichen Bedienelementen mit mechanischer Mittelstellung
- Roheingänge mit nichtlinearem oder nicht symmetrischem Verhalten um den Nullpunkt
- Anwendungen, bei denen einzelne Kalibrierpunkte unabhängig voneinander nachjustiert werden müssen, ohne die anderen zu beeinflussen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [CALIBRATE](CALIBRATE.md), das dieselbe boolean-gesteuerte Auslösung nutzt, jedoch nur eine lineare Zwei-Punkt-Kalibrierung ohne Mittelstellung bietet, sowie mit [E_CALIBRATE_3P](E_CALIBRATE_3P.md), das dieselbe Drei-Punkt-Logik ereignisgesteuert (`EI_MIN`/`EI_MID`/`EI_MAX`) mit eigenen Bestätigungsereignissen pro Punkt bereitstellt.

## Fazit

`CALIBRATE_3P` eignet sich überall dort, wo eine einfache Zwei-Punkt-Kalibrierung nicht ausreicht, weil der Rohwertbereich um einen (ggf. verschobenen) Mittelpunkt nicht symmetrisch ist -- allen voran bei Joysticks und ähnlichen Bedienelementen.
