# PROVIDE_ARR_0008_INT

![PROVIDE_ARR_0008_INT](PROVIDE_ARR_0008_INT.svg)

* * * * * * * * * *
## Einleitung

Der `PROVIDE_ARR_0008_INT` stellt einen `INT`-Array-Container fester Größe 8 als `InOut`-Variable `D1` bereit. Er gehört zur generischen `GEN_INIT_ARR`-Familie: eine Reihe baugleicher Bausteine, die sich nur in Array-Größe und Datentyp unterscheiden, und dient dazu, ein zur Entwurfszeit mit Startwerten vorbelegbares Array in einer 4diac-Anwendung verfügbar zu machen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierungsanforderung, trägt `D1`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt die Initialisierung, trägt `D1`.

### **Ein-/Ausgangsvariablen (InOut)**

- **D1** (`INT`, Array-Größe 8, Index 0…7): Der Array-Container (16-Bit-Ganzzahl (vorzeichenbehaftet) je Element). Kann im FB-Instanzeditor mit Startwerten vorbelegt werden (z. B. `[16#01, 16#00, ...]` für `BYTE`).

## Funktionsweise

Bei Eintreffen von `INIT` liest der Baustein das `InOut`-Array `D1` (das bereits zur Entwurfszeit mit Startwerten vorbelegt sein kann) und bestätigt dies unmittelbar über `INITO`, wobei `D1` unverändert weitergereicht wird. Der Baustein führt keine eigene Berechnung durch — er dient als deklarativer Container, dessen Inhalt über die FB-Instanzparametrierung vorgegeben wird.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_INIT_ARR'`, dieselbe C++-Basis wie alle anderen `PROVIDE_ARR_*`-Varianten; Array-Größe und Datentyp werden pro Instanziierung über die Typdefinition festgelegt.
- **InOut statt getrennter Input/Output**: `D1` ist eine einzige `InOut`-Variable — Vorbelegung und Bereitstellung erfolgen über dieselbe Variable, es gibt keine separate Kopie.
- **Feste Größe 8**: Weitere Größen derselben oder anderer Datentypen: keine weiteren.

## Zustandsübersicht

Zustandslos: `INIT` liest `D1` und bestätigt sofort über `INITO`, ohne den Inhalt zu verändern.

## Anwendungsszenarien

- **Konfigurationsarrays**: Bereitstellung fest vorbelegter Tabellen (z. B. Kalibrierwerte, Lookup-Tabellen, Protokoll-Header-Bytes) als wiederverwendbarer, zur Entwurfszeit parametrierbarer Baustein.
- **Testdatengenerierung**: Bereitstellung eines vordefinierten `INT`-Arrays für Testaufbauten, ohne das Array manuell in jeder Applikation neu zu verdrahten.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- keine weiteren: dieselbe generische Implementierung mit anderer Array-Größe bzw. anderem Datentyp.
- **`ARRAY2ARRAY_8_INT`**: kopiert ein bereits vorhandenes Array, ohne es bereitzustellen/vorzubelegen.

## Fazit

`PROVIDE_ARR_0008_INT` liefert einen einfachen, zur Entwurfszeit vorbelegbaren `INT`-Array-Container fester Größe 8 und eignet sich für Konfigurations- und Testdatenarrays, die wiederverwendbar in 4diac-Applikationen eingebunden werden sollen.
