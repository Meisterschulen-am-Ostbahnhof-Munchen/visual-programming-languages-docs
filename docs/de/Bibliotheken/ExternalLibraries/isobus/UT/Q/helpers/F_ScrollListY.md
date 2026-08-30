# F_ScrollListY

![F_ScrollListY](F_ScrollListY.svg)

* * * * * * * * * *

## Einleitung

Die Funktion `F_ScrollListY` berechnet aus der aktuellen Scroll-Position (in Zeilen) und der
Zeilenhöhe (in Pixeln) die Y-Verschiebung, die `Container_Scrolling_Content.Top` bekommen muss,
damit die richtige Zeile im Sichtfenster erscheint. Sie ist eine reine Rechenhilfsfunktion für
den Scroll-Baustein `ScrollFS` (Paket `isobus::UT::Q`) und wird dort intern verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `REQ`: Berechnungsanforderung, liest `i32Pos` und `i32RowHeight` ein.

### **Ereignis-Ausgänge**

- `CNF`: Bestätigt die Berechnung und liefert den Rückgabewert (namenlose `OutputVar`,
  angesprochen über `<Instanzname>.` mit abschließendem Punkt, IEC-61131-3-Konvention für den
  Rückgabewert einer Funktion).

### **Daten-Eingänge**

- `i32Pos` (DINT): Aktuelle Scroll-Position in Zeilen (0…`i32PosMax`).
- `i32RowHeight` (DINT): Zeilenhöhe in Pixeln.

### **Daten-Ausgänge**

- *(namenlos)* (INT): `Container_Scrolling_Content.Top`-Wert (`s16Yposition` für
  `Q_ChildPosition`).

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Die Berechnung ist eine einzige Formel:

```
OUT := DINT_TO_INT(-(i32Pos * i32RowHeight))
```

Je größer `i32Pos`, desto weiter negativ wird `Top` — der Inhalts-Container schiebt sich nach
oben, spätere Zeilen rutschen ins Sichtfenster. Bei `i32Pos = 0` ist `Top = 0` (Listenanfang,
keine Verschiebung).

## Technische Besonderheiten

- **`DINT_TO_INT`-Cast**: Die interne Rechnung läuft in `DINT` (32 Bit), das Ergebnis wird erst
  am Ende nach `INT` (16 Bit) konvertiert, weil `Q_ChildPosition.s16Yposition` ein `INT` erwartet
  (ISO 11783-6 F.16, „Change Child Location“).
- **Konkret typisiert, kein `ANY`**: Im Gegensatz zu generischen Bausteinen wie `F_MOVE` oder
  `F_SEL` sind alle Ein-/Ausgänge fest typisiert (`DINT`/`INT`) — dadurch ist beim Verdrahten in
  `ScrollFS` kein `MOVE`-Anker nötig, obwohl der Wert direkt aus anderen generischen/Struct-Feldern
  stammt.

## Zustandsübersicht

Zustandslos — jeder `REQ` berechnet das Ergebnis unmittelbar aus den aktuellen Eingangswerten neu.

## Anwendungsszenarien

- Ausschließlich intern in `ScrollFS` verwendet, um bei jeder Positionsänderung
  `Container_Scrolling_Content.Top` neu zu berechnen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Gegenüber `F_ScrollBarY`**: Beide berechnen eine Y-Verschiebung aus der Scroll-Position,
  `F_ScrollBarY` zusätzlich mit Skalierung auf die (kleinere) Scrollbalken-Spanne und einem
  Offset — siehe [F_ScrollBarY](F_ScrollBarY.md).

## Fazit

Eine kleine, robuste Rechenfunktion — verantwortlich für exakt eine Umrechnung
(Zeilenposition → Pixel-Offset der Liste), konkret typisiert und ohne Nebenwirkungen.
