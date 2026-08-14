# F_IS_VALID

![F_IS_VALID](F_IS_VALID.svg)

* * * * * * * * * *
## Einleitung

Der `F_IS_VALID` prüft, ob ein Gleitkommawert (`REAL`/`LREAL`) ein gültiger, endlicher Wert ist — also weder `NaN` (Not a Number) noch `+/-Infinity`. Er dient der Absicherung numerischer Berechnungen gegen ungültige Zwischenergebnisse.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Prüfung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (ANY_REAL): Der zu prüfende Gleitkommawert.

### **Daten-Ausgänge**

- **OUT** (BOOL): `TRUE`, wenn `IN` ein gültiger, endlicher Wert ist; `FALSE` bei `NaN` oder `Infinity`.

## Funktionsweise

Bei Eintreffen von `REQ` prüft die Algorithmus-ST-Anweisung `OUT := IS_VALID(IN)`, ob `IN` weder `NaN` noch `+/-Infinity` ist, und gibt das Ergebnis über `OUT` aus. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_REAL`-Eingang**: Akzeptiert sowohl `REAL` als auch `LREAL`.
- **Erkennt typische Fehlerresultate**: `NaN` entsteht z. B. bei `0.0/0.0`, `Infinity` bei Division durch `0.0` mit von-Null-verschiedenem Zähler — beides klassische Fehlerquellen in Gleitkommaberechnungen.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Prüfung und zu `CNF`.

## Anwendungsszenarien

- **Absicherung von Berechnungsketten**: Vor der Weiterverarbeitung eines Gleitkommaergebnisses prüfen, ob es gültig ist, um Folgefehler (z. B. `NaN`-Propagation) zu vermeiden.
- **Plausibilitätsprüfung von Sensordaten**: Erkennung fehlerhafter oder aus dem gültigen Bereich gefallener Messwerte.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_IS_VALID_BCD](F_IS_VALID_BCD.md)**: dieselbe Grundidee der Gültigkeitsprüfung, jedoch für BCD-kodierte Bitfolgen statt Gleitkommazahlen.

## Fazit

`F_IS_VALID` liefert eine einfache, zentrale Gültigkeitsprüfung für Gleitkommawerte und hilft, `NaN`/`Infinity`-bedingte Folgefehler in Berechnungsketten frühzeitig zu erkennen.
