# ARRAY2VALUES_8_INT

![ARRAY2VALUES_8_INT](ARRAY2VALUES_8_INT.svg)

* * * * * * * * * *
## Einleitung

Der `ARRAY2VALUES_8_INT` zerlegt ein `INT`-Array der Größe 8 in 8 einzelne Skalarvariablen `OUT_1`…`OUT_8`. Er gehört zur generischen `GEN_ARRAY2ARRAY`-Familie (vgl. [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)) und dient der Umwandlung von Array-Daten in diskrete Einzelwerte.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zerlegung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4`, `OUT_5`, `OUT_6`, `OUT_7`, `OUT_8`.

### **Daten-Eingänge**

- **IN** (`INT`, Array-Größe 8): Das zu zerlegende Array (16-Bit-Ganzzahl (vorzeichenbehaftet)).

### **Daten-Ausgänge**

- `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4`, `OUT_5`, `OUT_6`, `OUT_7`, `OUT_8` (`INT`): `OUT_i` entspricht `IN[i-1]`, also dem i-ten Element des Arrays.

## Funktionsweise

Bei Eintreffen von `REQ` wird jedes Element von `IN` auf den entsprechenden Skalarausgang `OUT_i` kopiert (`IN[0]` → `OUT_1`, …, `IN[7]` → `OUT_8`), anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, dieselbe C++-Basis wie [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md) und die übrigen `ARRAY2VALUES_*`-Varianten.
- **Feste Größe 8**: Für andere Array-Größen desselben Typs siehe .

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur vollständigen Zerlegung und zu `CNF`.

## Anwendungsszenarien

- **Datenaufbereitung**: Ein vorgeschalteter Baustein liefert ein `INT`-Array, ein nachgeschalteter Baustein benötigt jedoch diskrete Einzelvariablen.
- **Schnittstellenanpassung** zwischen array-basierten und variablenbasierten Bausteinschnittstellen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)**: dieselbe generische Implementierung für den Datentyp `LREAL`.
- **`VALUES2ARRAY_8_INT`**: die Umkehrrichtung — fasst 8 Einzelwerte zu einem Array zusammen.
- **`ARRAY2ARRAY_8_INT`**: kopiert das Array unverändert, statt es zu zerlegen.

## Fazit

`ARRAY2VALUES_8_INT` liefert eine einfache, generisch implementierte Zerlegung eines `INT`-Arrays der Größe 8 in 8 diskrete Einzelvariablen und eignet sich zur Anpassung array-basierter an variablenbasierte Schnittstellen.
