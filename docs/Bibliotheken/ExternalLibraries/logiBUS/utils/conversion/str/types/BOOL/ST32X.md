# ST32X

*(Kein Bild vorhanden, da dies ein Datentyp und kein Funktionsblock ist.)*

* * * * * * * * * *
## Einleitung
Der Datentyp `ST32X` ist ein benutzerdefinierter Strukturdatentyp, der aus 32 einzelnen BOOL-Variablen besteht. Er dient dazu, eine Sammlung von booleschen Zuständen oder Flags in einer einzigen, zusammenhängenden Datenstruktur zu bündeln, was die Handhabung und Übergabe von Statusinformationen vereinfachen kann. Der Name `ST32X` leitet sich von "Structure (ST) with 32 X/B (Boolean) bits" ab.

## Schnittstellenstruktur
Da `ST32X` ein Datentyp und kein Funktionsblock ist, besitzt er keine ereignis- oder datenbezogenen Ein- und Ausgänge im Sinne eines FB. Seine "Struktur" definiert lediglich seine internen Elemente.

### **Ereignis-Eingänge**
Nicht zutreffend, da `ST32X` ein benutzerdefinierter Datentyp und kein Funktionsblock ist.

### **Ereignis-Ausgänge**
Nicht zutreffend, da `ST32X` ein benutzerdefinierter Datentyp und kein Funktionsblock ist.

### **Daten-Eingänge**
Die Struktur besteht aus den folgenden 32 BOOL-Elementen, die intern in der Struktur als "Eingänge" betrachtet werden können, da sie die Werte aufnehmen, aus denen die Struktur gebildet wird:
*   `X_00` (Type: BOOL, Comment: BIT 00)
*   `X_01` (Type: BOOL, Comment: BIT 01)
*   `X_02` (Type: BOOL, Comment: BIT 02)
*   `X_03` (Type: BOOL, Comment: BIT 03)
*   `X_04` (Type: BOOL, Comment: BIT 04)
*   `X_05` (Type: BOOL, Comment: BIT 05)
*   `X_06` (Type: BOOL, Comment: BIT 06)
*   `X_07` (Type: BOOL, Comment: BIT 07)
*   `X_08` (Type: BOOL, Comment: BIT 08)
*   `X_09` (Type: BOOL, Comment: BIT 09)
*   `B_10` (Type: BOOL, Comment: BIT 10)
*   `B_11` (Type: BOOL, Comment: BIT 11)
*   `B_12` (Type: BOOL, Comment: BIT 12)
*   `B_13` (Type: BOOL, Comment: BIT 13)
*   `B_14` (Type: BOOL, Comment: BIT 14)
*   `B_15` (Type: BOOL, Comment: BIT 15)
*   `B_16` (Type: BOOL, Comment: BIT 16)
*   `B_17` (Type: BOOL, Comment: BIT 17)
*   `B_18` (Type: BOOL, Comment: BIT 18)
*   `B_19` (Type: BOOL, Comment: BIT 19)
*   `B_20` (Type: BOOL, Comment: BIT 20)
*   `B_21` (Type: BOOL, Comment: BIT 21)
*   `B_22` (Type: BOOL, Comment: BIT 22)
*   `B_23` (Type: BOOL, Comment: BIT 23)
*   `B_24` (Type: BOOL, Comment: BIT 24)
*   `B_25` (Type: BOOL, Comment: BIT 25)
*   `B_26` (Type: BOOL, Comment: BIT 26)
*   `B_27` (Type: BOOL, Comment: BIT 27)
*   `B_28` (Type: BOOL, Comment: BIT 28)
*   `B_29` (Type: BOOL, Comment: BIT 29)
*   `B_30` (Type: BOOL, Comment: BIT 30)
*   `B_31` (Type: BOOL, Comment: BIT 31)

### **Daten-Ausgänge**
Nicht zutreffend. Die Struktur `ST32X` selbst ist der "Ausgang", da sie die gebündelten booleschen Werte repräsentiert. Einzelne Elemente können über den Punktoperator (`.`) angesprochen werden (z.B. `myST32X.X_00`).

### **Adapter**
Nicht zutreffend, da `ST32X` ein benutzerdefinierter Datentyp und kein Funktionsblock ist.

## Funktionsweise
`ST32X` hat keine aktive "Funktionsweise" im Sinne von Logik oder Algorithmen. Es dient lediglich als passiver Datencontainer. Seine Funktion besteht darin, eine Gruppe von 32 einzelnen BOOL-Werten in einer einzigen Variable zu organisieren, was die Strukturierung von Programmen und die Übergabe von Daten zwischen Funktionsblöcken oder Programmteilen vereinfacht. Man kann die einzelnen Bits der Struktur ansprechen und ihren Wert setzen oder lesen.

## Technische Besonderheiten
*   **Anzahl der Bits:** Die Struktur fasst 32 unabhängige BOOL-Variablen zusammen.
*   **Benennung:** Die Elemente sind von `X_00` bis `X_09` und dann von `B_10` bis `B_31` benannt. Die Kommentare geben jeweils die Bit-Nummer an. Dies könnte auf eine ursprüngliche Absicht hindeuten, die Bits in einem Wort (z.B. DINT) zu repräsentieren, obwohl sie hier als separate BOOLs deklariert sind.
*   **Speichereffizienz:** Die genaue Speicherbelegung hängt von der Compiler-Implementierung ab. Typischerweise würde eine solche Struktur mindestens 32 Bytes (ein Byte pro BOOL) oder möglicherweise mehr belegen, je nach Padding und Ausrichtung.

## Zustandsübersicht
Als passiver Datentyp hat `ST32X` keine eigene Zustandsmaschine. Sein "Zustand" wird ausschließlich durch die Werte der 32 enthaltenen BOOL-Variablen definiert. Jedes Bit kann entweder `TRUE` oder `FALSE` sein.

## Anwendungsszenarien
*   **Bündelung von Statusflags:** Wenn ein System viele binäre Statusinformationen (z.B. Fehlercodes, Betriebszustände von Komponenten, Sensorflags) verwalten muss, kann `ST32X` verwendet werden, um diese in einer einzigen Variable zu übergeben oder zu speichern.
*   **Schnittstellenoptimierung:** Anstatt 32 separate BOOL-Signale an einen Funktionsblock zu übergeben, kann eine Instanz von `ST32X` über eine einzige Datenverbindung übermittelt werden.
*   **Bit-Mapping:** Obwohl die Elemente als `BOOL` definiert sind, könnte diese Struktur in Verbindung mit Konvertierungs-FBs (z.B. zur Umwandlung in einen `DINT`) verwendet werden, um auf die Bits eines 32-Bit-Wortes zuzugreifen oder diese zu manipulieren.
*   **SPS-ähnliche E/A-Abbildungen:** In Umgebungen, die an SPS-Programmierungen angelehnt sind, kann eine solche Struktur zur Abbildung von digitalen Ein- oder Ausgängen dienen.

## Vergleich mit ähnlichen Bausteinen
*   **Standard-Datentypen (z.B. `DINT`):** Ein `DINT` (Double Integer) ist ebenfalls 32 Bit breit, speichert jedoch die Bits als einen einzigen numerischen Wert. `ST32X` hingegen behandelt jedes Bit als eine separate boolesche Variable, was den direkten Zugriff per Namen ermöglicht, ohne Bitmaskierung oder Bit-Operationen.
*   **Andere strukturierte Datentypen:** Es könnten andere benutzerdefinierte Strukturen existieren, die eine kleinere oder größere Anzahl von BOOLs bündeln oder unterschiedliche Datentypen mischen. `ST32X` ist spezifisch auf 32 BOOLs ausgelegt.
*   **Array von BOOLs:** Ein `ARRAY[0..31] OF BOOL` würde ebenfalls 32 boolesche Werte speichern. Der Unterschied zu `ST32X` liegt im Zugriff: Bei `ST32X` erfolgt der Zugriff über benannte Elemente (z.B. `myST32X.X_00`), bei einem Array über den Index (z.B. `myArray[0]`). Benannte Elemente sind oft lesbarer und robuster gegenüber Änderungen in der Reihenfolge.

## Fazit
Der Datentyp `ST32X` bietet eine praktische Methode, um 32 einzelne boolesche Variablen zu einem kohärenten Ganzen zu verbinden. Er fördert die Code-Organisation und vereinfacht die Datenübergabe von umfangreichen Statusinformationen oder Flags. Obwohl er selbst keine aktive Logik implementiert, ist er ein nützliches Werkzeug in der Architektur komplexer Steuerungsprogramme, die auf der 4diac-IDE basieren.