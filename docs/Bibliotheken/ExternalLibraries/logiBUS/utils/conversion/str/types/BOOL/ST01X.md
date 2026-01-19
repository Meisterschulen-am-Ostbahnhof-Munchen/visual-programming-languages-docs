# ST01X

```{index} single: ST01X
```

* * * * * * * * * *
## Einleitung
Der Datentyp `ST01X` ist ein einfacher strukturierter Datentyp, der einen einzelnen Booleschen Wert (BOOL) kapselt. Er dient dazu, eine klar definierte Struktur für einen einzelnen Binärzustand bereitzustellen, was die Standardisierung und Lesbarkeit in komplexeren Anwendungen verbessern kann.

## Schnittstellenstruktur
Die "Schnittstellenstruktur" eines Datentyps bezieht sich auf seine internen Mitglieder, die die Definition des Datentyps bilden. Der Datentyp `ST01X` besitzt die folgende interne Struktur:

*   **`X_00`**: Eine Variable vom Typ `BOOL`. Dieser Member dient als "BIT 00" innerhalb der Struktur, wie im Kommentar angegeben.

### **Ereignis-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Ereignis-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Eingänge**
Nicht zutreffend für einen Datentyp im Sinne von Funktionblock-Eingängen. Der Datentyp definiert lediglich die Struktur für Daten.

### **Daten-Ausgänge**
Nicht zutreffend für einen Datentyp im Sinne von Funktionblock-Ausgängen. Der Datentyp definiert lediglich die Struktur für Daten.

### **Adapter**
Nicht zutreffend für einen Datentyp.

## Funktionsweise
Der Datentyp `ST01X` hat keine aktive Funktionsweise im Sinne eines Algorithmus oder einer Ausführung. Seine Funktion besteht ausschließlich darin, als definierter Container für einen einzelnen Booleschen Wert zu dienen. Er ermöglicht es Entwicklern, einen spezifischen Booleschen Zustand innerhalb einer strukturierten Umgebung klar und typensicher zu referenzieren, wodurch die Modularität und die Verständlichkeit von Datenstrukturen erhöht werden können.

## Technische Besonderheiten
*   **Minimale Struktur:** `ST01X` ist einer der einfachsten strukturierten Datentypen, der nur ein einziges `BOOL`-Element enthält.
*   **Kapselung:** Er kapselt einen einzelnen Booleschen Wert, der typischerweise einen Status, eine Flagge oder einen Zustand repräsentiert.
*   **Standardisierung:** Dieser Datentyp kann zur Standardisierung der Verwendung von einzelnen Booleschen Werten in größeren Datenstrukturen oder bei der Definition von Kommunikationsprotokollen eingesetzt werden, um Konsistenz zu gewährleisten.

## Zustandsübersicht
Ein Datentyp besitzt keine eigene "Zustandsübersicht" im Sinne eines Zustandsautomaten eines Funktionsblocks. Der "Zustand" eines Objekts vom Typ `ST01X` wird ausschließlich durch den Wert seines einzigen Members `X_00` bestimmt. Dieser kann entweder `TRUE` (wahr) oder `FALSE` (falsch) sein.

## Anwendungsszenarien
*   **Statusflaggen:** Repräsentation eines einfachen Ein/Aus-Status, z.B. zur Anzeige, ob ein Gerät aktiv ist, ein Prozess läuft oder eine Bedingung erfüllt ist.
*   **Kommunikationsprotokolle:** Als standardisierter Block innerhalb von Datenpaketen oder Telegrammen, um einen einzelnen Bit-Zustand zwischen Systemen zu übermitteln.
*   **Strukturierte Datenhaltung:** Wenn ein Boolescher Wert in einer übergeordneten Struktur mit einem spezifischen Namen und Kommentar benötigt wird, um die Lesbarkeit und Wartbarkeit zu verbessern, besonders wenn viele einzelne Booleans in einer logischen Gruppe zusammengefasst werden sollen.
*   **Typensicherheit:** Erzwingt die Verwendung eines explizit definierten Typs für bestimmte Boolesche Informationen, um Fehler durch versehentliche Typinkonsistenzen zu vermeiden.

## Vergleich mit ähnlichen Bausteinen
*   **Vergleich mit dem primitiven Typ `BOOL`:** Im Gegensatz zum einfachen `BOOL`-Typ, der nur den reinen Wert darstellt, bietet `ST01X` eine benannte Kapselung (`X_00`). Dies verbessert die Selbstbeschreibung und die Semantik des Wertes innerhalb einer größeren Struktur. Während `BOOL` ein elementarer Datentyp ist, ist `ST01X` ein zusammengesetzter (strukturierter) Datentyp.
*   **Vergleich mit größeren Strukturen (z.B. `ST08X`, `ST16X`):** `ST01X` ist die elementarste Form dieser Art von Struktur, spezialisiert auf nur ein Bit. Größere Strukturen wie `ST08X` oder `ST16X` würden entsprechend 8 oder 16 Boolesche Werte enthalten und dienen der Bündelung mehrerer Flags.

## Fazit
Der Datentyp `ST01X` ist ein grundlegender, aber nützlicher Baustein in der 4diac-IDE für die Strukturierung von Daten. Er ermöglicht die explizite Definition und Kapselung eines einzelnen Booleschen Wertes, was zur Verbesserung der Code-Lesbarkeit, Wartbarkeit und Standardisierung in komplexen Automatisierungsprojekten beiträgt. Er dient als Basis für einheitliche Datenstrukturen, insbesondere wenn ein Bit-Flag eine spezifische Bedeutung innerhalb einer breiteren Datenlandschaft hat.