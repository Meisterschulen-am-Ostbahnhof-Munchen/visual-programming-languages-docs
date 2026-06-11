# ASSEMBLE_AW_FROM_AQ


![ASSEMBLE_AW_FROM_AQ](./ASSEMBLE_AW_FROM_AQ.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ASSEMBLE_AW_FROM_AQ` dient dazu, acht einzelne **AQ (Quarter)**-Adapter zu einem zusammenhängenden **AW (Word)**-Adapter zu kombinieren. Ein Quarter repräsentiert jeweils ein 4-Bit-Datenpaket (halbes Byte). Der Baustein setzt diese acht Quarter-Daten – insgesamt 32 Bit – zu einem vollständigen Wort (WORD, 32 Bit) zusammen und stellt es über einen einzigen AW-Ausgangsadapter bereit. Typische Anwendungen sind die Rekonstruktion breiter Datenbusse aus seriell oder partiell ankommenden Bruchstücken.

## Schnittstellenstruktur

Der FB besitzt ausschließlich **Adapter-Schnittstellen**: Es gibt keine direkten Ereignis- oder Dateneingänge/-ausgänge auf der obersten Ebene. Die gesamte Kommunikation erfolgt über die angeschlossenen Adapter.

### **Ereignis-Eingänge**

- Keine direkten Ereigniseingänge.
- Ereignisse werden über die Sockets der **AQ-Adapter** empfangen (jeder AQ-Adapter stellt einen Ereignisausgang `E1` bereit).

### **Ereignis-Ausgänge**

- Keine direkten Ereignisausgänge.
- Das Ausgangsereignis wird über den **AW-Adapter** (Plug `OUT`) als Ereignis `E1` zur Verfügung gestellt.

### **Daten-Eingänge**

- Keine direkten Dateneingänge.
- Die zu verarbeitenden Daten werden über die **AQ-Adapter** als Dateneingang `D1` (jeweils 4 Byte) eingelesen.

### **Daten-Ausgänge**

- Keine direkten Datenausgänge.
- Das zusammengesetzte Wort (4 Byte) wird über den **AW-Adapter** als Datenausgang `D1` ausgegeben.

### **Adapter**

| Name              | Typ                   | Richtung | Kommentar                   |
|-------------------|-----------------------|----------|-----------------------------|
| `OUT`             | adapter::AW           | Plug     | Wort-Ausgang (4 Byte)       |
| `QUARTER_BYTE_00` | adapter::AQ           | Socket   | Quarter 0 (niederwertigstes)|
| `QUARTER_BYTE_01` | adapter::AQ           | Socket   | Quarter 1                   |
| `QUARTER_BYTE_02` | adapter::AQ           | Socket   | Quarter 2                   |
| `QUARTER_BYTE_03` | adapter::AQ           | Socket   | Quarter 3                   |
| `QUARTER_BYTE_04` | adapter::AQ           | Socket   | Quarter 4                   |
| `QUARTER_BYTE_05` | adapter::AQ           | Socket   | Quarter 5                   |
| `QUARTER_BYTE_06` | adapter::AQ           | Socket   | Quarter 6                   |
| `QUARTER_BYTE_07` | adapter::AQ           | Socket   | Quarter 7 (höchstwertigstes)|

## Funktionsweise

Der FB enthält intern zwei Funktionsblöcke:

1. **`ASSEMBLE_WORD_FROM_QUARTERS`**: Ein spezialisierter Assembler, der die Daten aller acht Quarter-Eingänge (jeweils 4 Byte) in der Reihenfolge 00 (LSB) bis 07 (MSB) zu einem 32-Bit-Wort zusammenfügt.
2. **`E_D_FF_ANY`**: Ein flankengesteuertes D-Flipflop, das das zusammengesetzte Wort zwischenspeichert und am Ausgang `Q` bereitstellt.

Der Ablauf:

- Sobald ein angeschlossener AQ-Adapter ein Ereignis auf seinem Ausgang `E1` sendet, wird dieses Ereignis an den `REQ`-Eingang des Assemblers weitergeleitet. Alle acht AQ-Adapter sind mit dem gleichen `REQ` verbunden, sodass jedes eingehende Ereignis (unabhängig vom Absender) eine neue Verarbeitung anstößt.
- Der Assembler verarbeitet die aktuellen Daten aller acht Quarter und legt das Ergebnis am Datenausgang an.
- Nach Abschluss der Berechnung sendet der Assembler ein Bestätigungsereignis (`CNF`), das den Takteingang (`CLK`) des D-Flipflops triggert.
- Das Flipflop übernimmt den berechneten Wert und gibt ihn stabil an `Q` weiter. Über den OUT-Adapter wird dann sowohl das Ereignis `E1` als auch der Datenwert `D1` auf der Ausgangsseite verfügbar.

Durch diese Struktur wird sichergestellt, dass das Ausgangswort erst dann aktualisiert wird, wenn eine vollständige Berechnung durchgeführt wurde – unabhängig davon, welcher Quarter als letztes aktualisiert wurde.

## Technische Besonderheiten

- **Zwischenspeicherung mit Flipflop**: Der Einsatz eines D-Flipflops vermeidet Glitches oder unvollständige Datenweitergabe, falls mehrere Quarter in schneller Folge aktualisiert werden. Der Ausgang ändert sich nur dann, wenn der Assembler einen neuen, gültigen Wert berechnet hat.
- **Adapter-basierte Schnittstelle**: Alle Ein- und Ausgaben erfolgen über Adapter, was den FB besonders geeignet für modulare, typisierte Datenflussarchitekturen in 4diac macht.
- **Synchroner Ablauf**: Die Verarbeitung wird durch jedes eingehende Ereignis eines Quarters angestoßen, erzeugt jedoch nur dann ein Ausgangsereignis, wenn die Berechnung abgeschlossen ist.

## Zustandsübersicht

Der FB besitzt kein eigenes ECC (Execution Control Chart) – die interne Logik wird vollständig durch die enthaltenen Bausteine `ASSEMBLE_WORD_FROM_QUARTERS` und `E_D_FF_ANY` realisiert. Der Baustein verhält sich daher wie eine kombinatorische Schaltung mit einer flankengesteuerten Speicherstufe.

## Anwendungsszenarien

- **Rekonstruktion breiter Datenpfade**: In der Automatisierungstechnik werden Daten oft in kleinen Paketen („Nibbles“) übertragen, z.B. über mehrere parallele E/A-Module. Der FB setzt diese wieder zu einer vollständigen 32-Bit-Größe zusammen.
- **Seriell-parallele Umsetzung**: Wenn ein Sensor oder Aktor seine Daten in 4-Bit-Quarten liefert (z.B. über asynchrone Schnittstellen), kann der FB die ankommenden Bruchstücke zwischenspeichern und zu einem konsistenten Gesamtwert vereinen.
- **Datenkonsolidierung**: In hierarchischen Steuerungssystemen, in denen mehrere Unterbausteine jeweils einen Quartierwert liefern, kann dieser FB die Werte zentral zusammenführen.

## Vergleich mit ähnlichen Bausteinen

- **`ASSEMBLE_BYTE_FROM_NIBBLES`**: Kombiniert zwei Halbbytes zu einem Byte (8 Bit). Der vorliegende FB arbeitet auf der nächsthöheren Ebene mit 8 Quartieren (32 Bit).
- **Einfache Datenkonverter**: Konverter wie `WORD_TO_BYTE` oder `BYTE_TO_NIBBLE` arbeiten meist ohne Zwischenspeicher und Ereignissteuerung. `ASSEMBLE_AW_FROM_AQ` bietet eine ereignisgesteuerte, stabile Weiterleitung mit optionale Speicherung.

## Fazit

Der Funktionsblock `ASSEMBLE_AW_FROM_AQ` stellt eine robuste und flexible Lösung dar, um aus acht unabhängigen Quarter-Daten (je 4 Bit) ein konsistentes 32-Bit-Wort zu erzeugen. Dank der adapterbasierten Schnittstellen und des integrierten D-Flipflops eignet er sich besonders für Echtzeitanwendungen, in denen Datenpakete asynchron eintreffen und zuverlässig zu einem Gesamtwert vereint werden müssen.