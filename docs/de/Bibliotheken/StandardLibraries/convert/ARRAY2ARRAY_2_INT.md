# ARRAY2ARRAY_2_INT

![ARRAY2ARRAY_2_INT](ARRAY2ARRAY_2_INT.svg)

* * * * * * * * * *
## Einleitung

Der `ARRAY2ARRAY_2_INT` ist ein Service-Interface-Funktionsblock, der ein `INT`-Array der Größe 2 unverändert von `IN` nach `OUT` kopiert. Er gehört zur generischen `GEN_ARRAY2ARRAY`-Familie (vgl. [ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)) und dient als reine Typ-/Schnittstellenbrücke zwischen zwei `INT`-Arrays gleicher Größe.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst den Kopiervorgang aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (`INT`, Array-Größe 2): Das Quell-Array (16-Bit-Ganzzahl (vorzeichenbehaftet)).

### **Daten-Ausgänge**

- **OUT** (`INT`, Array-Größe 2): Das Ziel-Array, identische Werte wie `IN`.

## Funktionsweise

Bei Eintreffen von `REQ` werden die 2 Elemente von `IN` unverändert nach `OUT` kopiert, anschließend wird `CNF` ausgelöst. Es findet keine Typumwandlung oder Wertänderung statt — der Baustein dient ausschließlich der Entkopplung zweier Array-Variablen mit identischem Typ und identischer Größe.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, dieselbe C++-Basis wie alle anderen `ARRAY2ARRAY_*`-Varianten (z. B. [ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)), lediglich Array-Größe und Datentyp unterscheiden sich pro Instanziierung.
- **Feste Größe 2**: Für andere Array-Größen desselben Typs siehe `ARRAY2ARRAY_8_INT`.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur vollständigen Kopie und zu `CNF`.

## Anwendungsszenarien

- **Schnittstellenentkopplung**: Ein Baustein liefert ein `INT`-Array der Größe 2 als Ausgabe, ein anderer erwartet ein separates Eingangs-Array — `ARRAY2ARRAY_2_INT` dient als Brücke ohne Seiteneffekte.
- **Datenrouting** von `INT`-Arrays fester Größe zwischen Teilen einer 4diac-Applikation.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)**: dieselbe generische Implementierung für den Datentyp `LREAL`.
- **`ARRAY2ARRAY_8_INT`**: dieselbe Implementierung mit Array-Größe 8 statt 2.
- **`ARRAY2VALUES_2_INT`**: zerlegt das Array stattdessen in 2 einzelne Skalarvariablen.

## Fazit

`ARRAY2ARRAY_2_INT` liefert eine einfache, generisch implementierte Eins-zu-eins-Kopie eines `INT`-Arrays der Größe 2 und dient als unkomplizierte Schnittstellenbrücke zwischen gleichartigen Array-Variablen.
