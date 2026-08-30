# ARRAY2VALUES_4_BYTE

![ARRAY2VALUES_4_BYTE](ARRAY2VALUES_4_BYTE.svg)

* * * * * * * * * *

## Einleitung

Der `ARRAY2VALUES_4_BYTE` zerlegt ein `BYTE`-Array der Größe 4 in 4 einzelne Skalarvariablen `OUT_1`…`OUT_4`. Er gehört zur generischen `GEN_ARRAY2ARRAY`-Familie (vgl. [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)) und dient der Umwandlung von Array-Daten in diskrete Einzelwerte.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Zerlegung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4`.

### **Daten-Eingänge**

- **IN** (`BYTE`, Array-Größe 4): Das zu zerlegende Array (8-Bit-Bitmuster).

### **Daten-Ausgänge**

- `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4` (`BYTE`): `OUT_i` entspricht `IN[i-1]`, also dem i-ten Element des Arrays.

## Funktionsweise

Bei Eintreffen von `REQ` wird jedes Element von `IN` auf den entsprechenden Skalarausgang `OUT_i` kopiert (`IN[0]` → `OUT_1`, …, `IN[3]` → `OUT_4`), anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, dieselbe C++-Basis wie [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md) und die übrigen `ARRAY2VALUES_*`-Varianten.
- **Feste Größe 4**: Für andere Array-Größen desselben Typs siehe `ARRAY2VALUES_2_BYTE`, `ARRAY2VALUES_8_BYTE`, `ARRAY2VALUES_16_BYTE`, `ARRAY2VALUES_32_BYTE`.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur vollständigen Zerlegung und zu `CNF`.

## Anwendungsszenarien

- **Datenaufbereitung**: Ein vorgeschalteter Baustein liefert ein `BYTE`-Array, ein nachgeschalteter Baustein benötigt jedoch diskrete Einzelvariablen.
- **Schnittstellenanpassung** zwischen array-basierten und variablenbasierten Bausteinschnittstellen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)**: dieselbe generische Implementierung für den Datentyp `LREAL`.
- **`VALUES2ARRAY_4_BYTE`**: die Umkehrrichtung — fasst 4 Einzelwerte zu einem Array zusammen.
- **`ARRAY2ARRAY_2_BYTE`**: kopiert das Array unverändert, statt es zu zerlegen.

## Fazit

`ARRAY2VALUES_4_BYTE` liefert eine einfache, generisch implementierte Zerlegung eines `BYTE`-Arrays der Größe 4 in 4 diskrete Einzelvariablen und eignet sich zur Anpassung array-basierter an variablenbasierte Schnittstellen.
