# AW_FIELDBUS_WORD_TO_SIGNAL_SCALED


![AW_FIELDBUS_WORD_TO_SIGNAL_SCALED](./AW_FIELDBUS_WORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AW_FIELDBUS_WORD_TO_SIGNAL_SCALED` dient dazu, ein eingehendes Feldbus-Wort (16‑Bit) unter Berücksichtigung eines Skalierungsfaktors und Offsets auf einen physikalischen Ausgabewert zu übertragen. Zusätzlich wird die Gültigkeit des Signals über einen eigenen Ausgang überwacht und gespeichert. Der Baustein kapselt die typische Verarbeitungskette von der digitalen Übertragung bis zur normierten Analog- oder Signalgröße.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar |
|----------|-------|-----------|
| INIT     | EInit | Initialisierungsanforderung (z. B. Reset der internen Logik) |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar |
|----------|-------|-----------|
| INITO    | EInit | Bestätigung der erfolgreichen Initialisierung |

### **Daten-Eingänge**

| Name   | Typ  | Default         | Kommentar                     |
|--------|------|-----------------|-------------------------------|
| SCALE  | REAL | REAL#1.0        | Skalierungsfaktor             |
| OFFSET | DINT | DINT#0          | Ganzzahliger Offset (nach Skalierung) |

### **Daten-Ausgänge**
Der Baustein besitzt keine separaten Datenausgänge. Die Ausgangswerte werden über die Adapter bereitgestellt.

### **Adapter**

| Adapter | Richtung | Typ (unidirektional) | Kommentar |
|---------|----------|----------------------|-----------|
| IN      | Socket   | AW                   | Eingangssignal (Feldbus-Wort) |
| OUT     | Plug     | AR                   | Verarbeitetes und skaliertes Ausgangssignal |
| VALID   | Plug     | AX                   | Boolescher Wert: TRUE, wenn das Signal gültig ist |

## Funktionsweise
Der Baustein arbeitet mit einem internen Sub‑FB `FIELDBUS_WORD_TO_SIGNAL_SCALED` und einem flankengesteuerten D‑Flip‑Flop (`E_D_FF`).

1. **Initialisierung:** Ein INIT-Ereignis wird an den Sub‑FB weitergeleitet. Nach dessen Abschluss wird INITO ausgegeben.
2. **Datenverarbeitung:** Ein eingehendes Ereignis auf `IN.E1` triggert den Sub‑FB (`REQ`). Dieser liest das aktuelle Wort von `IN.D1`, skaliert es mit dem Faktor `SCALE`, addiert den `OFFSET` und stellt das Ergebnis auf dem internen Ausgang `OUT` bereit. Gleichzeitig wird ein Gültigkeitsflag (`VALID`) erzeugt.
3. **Weitergabe und Speicherung:** Nach erfolgreicher Verarbeitung (`CNF`) wird das Ausgangsereignis auf `OUT.E1` gesendet und das Gültigkeitsflag in das D‑Flip‑Flop übernommen (Taktflanke). Der gespeicherte Wert steht am Validierungsausgang (`VALID.D1`) stabil zur Verfügung.
4. **Signalvalidität:** Wenn das eingehende Wort als ungültig erkannt wird (z. B. durch Fehlerbits oder Plausibilitätsprüfung im Sub‑FB), setzt der Sub‑FB das `VALID`-Signal auf FALSE. Das Flip‑Flop friert diesen Zustand ein, bis der nächste gültige Zyklus eintritt.

## Technische Besonderheiten
- **Skalierung mit Offset:** Die Verarbeitung erfolgt in der Reihenfolge `(Wort * SCALE) + OFFSET`. Dadurch können lineare Umrechnungen realisiert werden, z. B. Rohwerte in physikalische Einheiten.
- **Gültigkeitsspeicherung:** Das D‑Flip‑Flop entkoppelt die dynamische Validität vom Ausgangssignal. Ein einmal als ungültig markiertes Signal bleibt so lange ungültig, bis wieder ein gültiger Zyklus durchläuft – das verhindert kurzzeitige Fehlinterpretationen.
- **Adapterbasierte Schnittstelle:** Der Baustein verwendet uni-direktionale Adapter eines Typsystems, das auf Feldbus-Kommunikation ausgelegt ist (`AW`, `AR`, `AX`). Die genauen Datentypen der Adapter (z. B. Wort, Real, Bool) werden durch die Adapterdefinitionen bereitgestellt.

## Zustandsübersicht
Der Baustein selbst hat keine explizite Zustandsmaschine in der XML. Sein Verhalten ergibt sich aus der Abfolge der internen Elemente:

- **Warten auf INIT:** Kein Betrieb bevor INIT ausgeführt.
- **Betrieb:** Nach INIT lauscht der Baustein auf Ereignisse am `IN`‑Socket. Jedes eingehende Ereignis startet einen Verarbeitungsschritt.
- **Ausgabe:** Das Ausgangsereignis `OUT.E1` wird unmittelbar nach Abschluss der internen Skalierung gesendet. Das Validitätssignal `VALID` wird zeitgleich aktualisiert.

## Anwendungsszenarien
- **Feldbus‑Analogwertaufbereitung:** Ein von einem Feldbus übertragenes 16‑Bit‑Signal (z. B. 0…65535) wird mittels Skalierung in einen physikalischen Bereich wie 0 … 10 V oder 4 … 20 mA umgerechnet.
- **Sensorwert mit Gültigkeitsflag:** Sensoren, die über ein Feldbusprotokoll Daten liefern, können auch einen Gültigkeitsstatus (z. B. „Data valid“ Bit) senden. Dieser wird über den `VALID`‑Ausgang geführt.
- **Sicherheitsgerichtete Übertragung:** Wenn das Feldbuswort ein Fehlerbit enthält, kann der Sub‑FB `VALID` auf FALSE setzen, sodass nachgeschaltete Logiken das Signal als ungültig erkennen.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Wort-zu-Signal‑Konvertern (z. B. `FIELDBUS_WORD_TO_SIGNAL`) besitzt `AW_FIELDBUS_WORD_TO_SIGNAL_SCALED` eine integrierte Gültigkeitsspeicherung und getrennte Adapter für Ausgang und Validität. Dies reduziert die Verdrahtung in der Applikation und vereinfacht die Handhabung von temporären Fehlern. Bausteine ohne Offset-/Skalierungslogik müssten extern mit Rechenblöcken ergänzt werden.

## Fazit
`AW_FIELDBUS_WORD_TO_SIGNAL_SCALED` ist ein kompakter, funktionaler Baustein zur Aufbereitung von Feldbussignalen. Er verbindet Skalierung, Offset und Gültigkeitsüberwachung in einem wiederverwendbaren Modul. Die adapterbasierte Schnittstelle und die gespeicherte Validität machen ihn besonders geeignet für industrielle Steuerungen, bei denen Signalqualität und einfache Parametrierung im Vordergrund stehen.