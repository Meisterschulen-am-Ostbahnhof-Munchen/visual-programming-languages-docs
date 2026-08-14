# ARRAY2ARRAY_8_BYTE

![ARRAY2ARRAY_8_BYTE](ARRAY2ARRAY_8_BYTE.svg)

* * * * * * * * * *
## Einleitung

Der `ARRAY2ARRAY_8_BYTE` ist ein Service-Interface-Funktionsblock, der ein `BYTE`-Array der Größe 8 unverändert von `IN` nach `OUT` kopiert. Er gehört zur generischen `GEN_ARRAY2ARRAY`-Familie (vgl. [ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)) und dient als reine Typ-/Schnittstellenbrücke zwischen zwei `BYTE`-Arrays gleicher Größe.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst den Kopiervorgang aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (`BYTE`, Array-Größe 8): Das Quell-Array (8-Bit-Bitmuster).

### **Daten-Ausgänge**

- **OUT** (`BYTE`, Array-Größe 8): Das Ziel-Array, identische Werte wie `IN`.

## Funktionsweise

Bei Eintreffen von `REQ` werden die 8 Elemente von `IN` unverändert nach `OUT` kopiert, anschließend wird `CNF` ausgelöst. Es findet keine Typumwandlung oder Wertänderung statt — der Baustein dient ausschließlich der Entkopplung zweier Array-Variablen mit identischem Typ und identischer Größe.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, dieselbe C++-Basis wie alle anderen `ARRAY2ARRAY_*`-Varianten (z. B. [ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)), lediglich Array-Größe und Datentyp unterscheiden sich pro Instanziierung.
- **Feste Größe 8**: Für andere Array-Größen desselben Typs siehe `ARRAY2ARRAY_2_BYTE`.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur vollständigen Kopie und zu `CNF`.

## Anwendungsszenarien

- **Schnittstellenentkopplung**: Ein Baustein liefert ein `BYTE`-Array der Größe 8 als Ausgabe, ein anderer erwartet ein separates Eingangs-Array — `ARRAY2ARRAY_8_BYTE` dient als Brücke ohne Seiteneffekte.
- **Datenrouting** von `BYTE`-Arrays fester Größe zwischen Teilen einer 4diac-Applikation.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)**: dieselbe generische Implementierung für den Datentyp `LREAL`.
- **`ARRAY2ARRAY_2_BYTE`**: dieselbe Implementierung mit Array-Größe 2 statt 8.
- **`ARRAY2VALUES_8_BYTE`**: zerlegt das Array stattdessen in 8 einzelne Skalarvariablen.

## Fazit

`ARRAY2ARRAY_8_BYTE` liefert eine einfache, generisch implementierte Eins-zu-eins-Kopie eines `BYTE`-Arrays der Größe 8 und dient als unkomplizierte Schnittstellenbrücke zwischen gleichartigen Array-Variablen.
