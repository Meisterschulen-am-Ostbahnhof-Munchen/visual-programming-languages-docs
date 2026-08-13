# F_ScrollBarY

![F_ScrollBarY](F_ScrollBarY.svg)

* * * * * * * * * *
## Einleitung

Die Funktion `F_ScrollBarY` berechnet aus der aktuellen Scroll-Position (in Zeilen) die
Y-Verschiebung für den Scrollbalken-Inhalts-Container (`Container_Scrollbar_Content.Top`), so
dass der Balken-„Thumb“ die Listenposition proportional widerspiegelt. Sie ist das
Scrollbalken-Gegenstück zu [F_ScrollListY](F_ScrollListY.md) und wird intern vom Scroll-Baustein
`ScrollFS` (Paket `isobus::UT::Q`) verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `REQ`: Berechnungsanforderung, liest `i32Pos`, `i32BarTravel`, `i32PosMax` und
  `i32BarBaseOffset` ein.

### **Ereignis-Ausgänge**

- `CNF`: Bestätigt die Berechnung und liefert den Rückgabewert (namenlose `OutputVar`,
  angesprochen über `<Instanzname>.` mit abschließendem Punkt).

### **Daten-Eingänge**

- `i32Pos` (DINT): Aktuelle Scroll-Position in Zeilen (0…`i32PosMax`).
- `i32BarTravel` (DINT): Verfügbarer Verschiebeweg des Thumbs (Sichtfensterhöhe − Thumbhöhe).
- `i32PosMax` (DINT): Maximale Scroll-Position (letzte gültige Zeile).
- `i32BarBaseOffset` (DINT): `Top`-Wert von `Container_Scrollbar_Content` bei Position 0 — muss
  betragsmäßig genau der festen internen `Top`-Position des Thumbs entsprechen, mit
  umgekehrtem Vorzeichen, damit der Thumb bei `i32Pos = 0` netto auf Y = 0 steht.

### **Daten-Ausgänge**

- *(namenlos)* (INT): `Container_Scrollbar_Content.Top`-Wert (`s16Yposition` für
  `Q_ChildPosition`).

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Die Berechnung ist eine einzige Formel:

```
OUT := DINT_TO_INT(i32BarBaseOffset + (i32Pos * i32BarTravel) / i32PosMax)
```

Bei `i32Pos = 0` ergibt sich `OUT = i32BarBaseOffset` (Thumb am Listenanfang), bei
`i32Pos = i32PosMax` ergibt sich `OUT = i32BarBaseOffset + i32BarTravel` (Thumb am Listenende).
Dazwischen wird linear interpoliert.

## Technische Besonderheiten

- **`DINT_TO_INT`-Cast**: wie bei `F_ScrollListY` — die Rechnung läuft in `DINT`, das Ergebnis
  wird erst am Ende nach `INT` konvertiert (`Q_ChildPosition.s16Yposition`).
- **Ganzzahlige Division**: `(i32Pos * i32BarTravel) / i32PosMax` rundet ab (Integer-Division) —
  bei kleinen `i32BarTravel`-Werten relativ zu `i32PosMax` kann der Thumb dadurch mehrere
  Positionsschritte lang stehen bleiben, bevor er sich sichtbar bewegt. In der Praxis
  unauffällig, da `i32BarTravel` üblicherweise deutlich größer als `i32PosMax` ist.
- **Konkret typisiert, kein `ANY`**: wie `F_ScrollListY` — feste `DINT`/`INT`-Typisierung, kein
  `MOVE`-Anker beim Verdrahten nötig.

## Zustandsübersicht

Zustandslos — jeder `REQ` berechnet das Ergebnis unmittelbar aus den aktuellen Eingangswerten neu.

## Anwendungsszenarien

- Ausschließlich intern in `ScrollFS` verwendet, um bei jeder Positionsänderung
  `Container_Scrollbar_Content.Top` neu zu berechnen — parallel zu `F_ScrollListY` für die
  eigentliche Liste, mit demselben `i32Pos`-Wert als gemeinsame Quelle.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Gegenüber `F_ScrollListY`**: gleiche Grundidee (Zeilenposition → Pixel-Offset), aber mit
  Skalierung auf die (kleinere) Scrollbalken-Spanne statt direkter Multiplikation mit der
  Zeilenhöhe, plus einem Basis-Offset. Siehe [F_ScrollListY](F_ScrollListY.md).

## Fazit

Das Scrollbalken-Pendant zu `F_ScrollListY` — dieselbe Zeilen-Position treibt über zwei getrennte,
konkret typisierte Formeln sowohl die Liste als auch den Scrollbalken an, jeweils mit ihrer
eigenen Skalierung.
