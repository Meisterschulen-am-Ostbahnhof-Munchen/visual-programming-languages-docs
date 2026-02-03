# ST08X

```{index} single: ST08X
```

* * * * * * * * * *
## Einleitung
Der Datentyp **ST08X** ist eine strukturierte Datenkomponente, die für die Verwaltung und Gruppierung von acht individuellen booleschen Werten konzipiert wurde. Sein Hauptzweck ist es, eine kompakte Darstellung für eine Sammlung von acht unabhängigen Bits bereitzustellen, die oft als Status-Flags, Steuersignale oder ähnliche binäre Zustände verwendet werden.

## Schnittstellenstruktur
Da **ST08X** ein Datentyp und kein Funktionsblock ist, besitzt er keine Ereignis-, Daten-Ein- oder Ausgänge im Sinne eines 4diac-Funktionsblocks. Stattdessen definiert er eine interne Struktur von Mitgliedsvariablen.

### **Ereignis-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Ereignis-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Eingänge**
Nicht zutreffend für einen Datentyp. Der Datentyp besteht aus folgenden internen Variablen:
*   `X_00`: Typ `BOOL`, Kommentar: "BIT 00"
*   `X_01`: Typ `BOOL`, Kommentar: "BIT 01"
*   `X_02`: Typ `BOOL`, Kommentar: "BIT 02"
*   `X_03`: Typ `BOOL`, Kommentar: "BIT 03"
*   `X_04`: Typ `BOOL`, Kommentar: "BIT 04"
*   `X_05`: Typ `BOOL`, Kommentar: "BIT 05"
*   `X_06`: Typ `BOOL`, Kommentar: "BIT 06"
*   `X_07`: Typ `BOOL`, Kommentar: "BIT 07"

### **Daten-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Adapter**
Nicht zutreffend für einen Datentyp.

## Funktionsweise
Der Datentyp **ST08X** hat keine eigenständige "Funktionsweise" im Sinne eines Algorithmus oder einer Verarbeitung. Er dient lediglich als Container, um acht boolesche Werte unter einem gemeinsamen Namen zu organisieren. Die einzelnen Bits können über ihre Namen (z.B. `ST08X_Variable.X_00`) in anderen Funktionsblöcken oder Programmlogiken gelesen und geschrieben werden.

## Technische Besonderheiten
*   **Kompakte Struktur**: Fasst acht `BOOL`-Variablen zu einer einzigen logischen Einheit zusammen.
*   **Explizite Benennung**: Jedes Bit ist explizit von `X_00` bis `X_07` benannt, was die Lesbarkeit und Adressierung verbessert.
*   **Keine implizite Konvertierung**: Als strukturierter Datentyp bietet er eine typsichere Kapselung der Bits.

## Zustandsübersicht
Als reiner Datentyp besitzt **ST08X** keine Zustände im Sinne einer Zustandsmaschine oder eines Lebenszyklus. Sein "Zustand" wird durch die aktuellen Werte seiner acht booleschen Mitglieder bestimmt.

## Anwendungsszenarien
*   **Statusregister**: Abbildung von Statusbits eines externen Geräts oder einer internen Komponente.
*   **Konfigurationsparameter**: Gruppierung von 8 binären Konfigurationsoptionen.
*   **Fehlermeldungen**: Sammlung von bis zu 8 verschiedenen Fehlermeldungs-Flags.
*   **Binäre Ein-/Ausgänge**: Repräsentation von 8 digitalen Ein- oder Ausgängen.
*   **Datenbus-Repräsentation**: In Fällen, wo eine Gruppe von 8 Bits als Einheit behandelt werden soll, ohne sie als kompletten Byte-Wert zu interpretieren, ermöglicht ST08X den direkten Zugriff auf einzelne Bits.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Der Datentyp **ST08X** bietet eine Alternative zu:
*   **Einzelne BOOL-Variablen**: Reduziert die Anzahl der Deklarationen und vereinfacht die Parameterübergabe, wenn viele boolesche Werte zusammengehören.
*   **BYTE-Datentyp**: Während ein `BYTE` ebenfalls 8 Bits speichert, werden diese als numerischer Wert behandelt. **ST08X** behält die separate, namentliche Adressierbarkeit jedes einzelnen Bits, was die Semantik und den direkten Zugriff auf logische Flags verbessert, ohne Bitmaskierungen oder Bitverschiebeoperationen verwenden zu müssen. Die explizite Benennung `X_00` bis `X_07` macht den Code selbsterklärender.

## Fazit
Der Datentyp **ST08X** ist ein nützliches Konstrukt, um acht unabhängige boolesche Werte in einer strukturierten und gut benannten Weise zu gruppieren. Er fördert die Code-Lesbarkeit und -Wartbarkeit, indem er eine klare semantische Kapselung für Sammlungen von binären Flags bietet, die über einfache Bit-Operationen auf einem Byte hinausgehen soll.