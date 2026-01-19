# FB_CTUD_ULINT

```{index} single: FB_CTUD_ULINT
```

<img width="1423" height="340" alt="FB_CTUD_ULINT" src="https://github.com/user-attachments/assets/dbd0e935-fff7-4ac2-b484-178aa62809f7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_CTUD_ULINT` ist ein Zähler mit Aufwärts- und Abwärtszählfunktion für den Datentyp `ULINT` (unsigned 64-bit integer). Er bietet zusätzliche Funktionen wie Reset, Laden eines Vorgabewerts und Statusausgaben für die Zählrichtung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die normale Ausführung des Zählvorgangs. Wird mit den Daten-Eingängen `CU`, `CD`, `R`, `LD` und `PV` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung und liefert die aktuellen Zählerwerte über die Daten-Ausgänge `QU`, `QD` und `CV`.

### **Daten-Eingänge**
- `CU` (BOOL): Signal zum Hochzählen (Count Up)
- `CD` (BOOL): Signal zum Herunterzählen (Count Down)
- `R` (BOOL): Reset-Signal (setzt den Zähler auf 0)
- `LD` (BOOL): Load-Signal (lädt den Vorgabewert `PV` in den Zähler)
- `PV` (ULINT): Preset Value (Vorgabewert für den Zähler)

### **Daten-Ausgänge**
- `QU` (BOOL): Signalisiert, ob der Zählerwert größer oder gleich dem Vorgabewert ist
- `QD` (BOOL): Signalisiert, ob der Zählerwert kleiner oder gleich 0 ist
- `CV` (ULINT): Aktueller Zählerwert (Count Value)

## Funktionsweise
Der Zähler führt folgende Operationen beim `REQ`-Ereignis aus:
1. Bei aktivem `R` (Reset) wird der Zähler auf 0 gesetzt
2. Bei aktivem `LD` (Load) wird der Vorgabewert `PV` in den Zähler geladen
3. Wenn weder Reset noch Load aktiv sind:
   - Bei aktivem `CU` (und nicht gleichzeitig `CD`) wird hochgezählt (bis zum Maximalwert 18446744073709551615)
   - Bei aktivem `CD` (und nicht gleichzeitig `CU`) wird heruntergezählt (bis zum Minimalwert 0)
4. Die Ausgänge `QU` und `QD` werden entsprechend dem aktuellen Zählerstand aktualisiert

## Technische Besonderheiten
- Verwendet den 64-bit unsigned integer Datentyp (ULINT)
- Maximaler Zählerwert: 18446744073709551615
- Besondere Behandlung der gleichzeitigen Aktivierung von `CU` und `CD` (keine Zähloperation)
- Statusausgänge für Über-/Unterschreitung

## Anwendungsszenarien
- Industrielle Zählaufgaben mit großen Zahlenbereichen
- Positionserfassung in großen Systemen
- Materialflussüberwachung mit hohen Stückzahlen
- Generelle Steuerungsaufgaben mit Aufwärts-/Abwärtszählfunktion

## Vergleich mit ähnlichen Bausteinen
- Gegenüber einfachen Zählern bietet dieser FB beide Zählrichtungen
- Im Vergleich zu kleineren Datentypen (z.B. INT) ermöglicht ULINT extrem große Zählbereiche
- Integrierte Statusausgänge (`QU`, `QD`) vereinfachen die Überwachung

## Fazit
Der `FB_CTUD_ULINT` ist ein leistungsfähiger Zählbaustein für Anwendungen, die große Zahlenbereiche und flexible Zählfunktionen benötigen. Durch die kombinierte Aufwärts-/Abwärtszählfunktion und die zusätzlichen Steuer- und Statusmöglichkeiten eignet er sich für komplexe Zählaufgaben in industriellen Steuerungen.