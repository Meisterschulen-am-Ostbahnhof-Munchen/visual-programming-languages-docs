# PROVIDE_ARR_0021_BYTE

![PROVIDE_ARR_0021_BYTE](PROVIDE_ARR_0021_BYTE.svg)

* * * * * * * * * *

## Einleitung

Der `PROVIDE_ARR_0021_BYTE` stellt einen `BYTE`-Array-Container fester Größe 21 als `InOut`-Variable `D1` bereit. Er gehört zur generischen `GEN_INIT_ARR`-Familie: eine Reihe baugleicher Bausteine, die sich nur in Array-Größe und Datentyp unterscheiden, und dient dazu, ein zur Entwurfszeit mit Startwerten vorbelegbares Array in einer 4diac-Anwendung verfügbar zu machen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierungsanforderung, trägt `D1`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt die Initialisierung, trägt `D1`.

### **Ein-/Ausgangsvariablen (InOut)**

- **D1** (`BYTE`, Array-Größe 21, Index 0…20): Der Array-Container (8-Bit-Bitmuster je Element). Kann im FB-Instanzeditor mit Startwerten vorbelegt werden (z. B. `[16#01, 16#00, ...]` für `BYTE`).

## Funktionsweise

Bei Eintreffen von `INIT` liest der Baustein das `InOut`-Array `D1` (das bereits zur Entwurfszeit mit Startwerten vorbelegt sein kann) und bestätigt dies unmittelbar über `INITO`, wobei `D1` unverändert weitergereicht wird. Der Baustein führt keine eigene Berechnung durch — er dient als deklarativer Container, dessen Inhalt über die FB-Instanzparametrierung vorgegeben wird.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_INIT_ARR'`, dieselbe C++-Basis wie alle anderen `PROVIDE_ARR_*`-Varianten; Array-Größe und Datentyp werden pro Instanziierung über die Typdefinition festgelegt.
- **InOut statt getrennter Input/Output**: `D1` ist eine einzige `InOut`-Variable — Vorbelegung und Bereitstellung erfolgen über dieselbe Variable, es gibt keine separate Kopie.
- **Feste Größe 21**: Weitere Größen derselben oder anderer Datentypen: `PROVIDE_ARR_0002_BYTE`, `PROVIDE_ARR_0007_BYTE`, `PROVIDE_ARR_0008_BYTE`, `PROVIDE_ARR_0014_BYTE`.

## Zustandsübersicht

Zustandslos: `INIT` liest `D1` und bestätigt sofort über `INITO`, ohne den Inhalt zu verändern.

## Anwendungsszenarien

- **Konfigurationsarrays**: Bereitstellung fest vorbelegter Tabellen (z. B. Kalibrierwerte, Lookup-Tabellen, Protokoll-Header-Bytes) als wiederverwendbarer, zur Entwurfszeit parametrierbarer Baustein.
- **Testdatengenerierung**: Bereitstellung eines vordefinierten `BYTE`-Arrays für Testaufbauten, ohne das Array manuell in jeder Applikation neu zu verdrahten.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- `PROVIDE_ARR_0002_BYTE`, `PROVIDE_ARR_0007_BYTE`, `PROVIDE_ARR_0008_BYTE`, `PROVIDE_ARR_0014_BYTE`: dieselbe generische Implementierung mit anderer Array-Größe bzw. anderem Datentyp.
- **`ARRAY2ARRAY_2_BYTE`**: kopiert ein bereits vorhandenes Array, ohne es bereitzustellen/vorzubelegen.

## Fazit

`PROVIDE_ARR_0021_BYTE` liefert einen einfachen, zur Entwurfszeit vorbelegbaren `BYTE`-Array-Container fester Größe 21 und eignet sich für Konfigurations- und Testdatenarrays, die wiederverwendbar in 4diac-Applikationen eingebunden werden sollen.
