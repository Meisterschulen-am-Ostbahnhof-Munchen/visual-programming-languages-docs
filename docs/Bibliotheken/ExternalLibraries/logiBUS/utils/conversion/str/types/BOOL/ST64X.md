# ST64X

*(Kein Bild vorhanden, da dies ein Datentyp und kein Funktionsblock ist.)*

* * * * * * * * * *
## Einleitung
Die bereitgestellte XML-Definition beschreibt einen **Datentyp (DataType)** namens `ST64X`, nicht einen Funktionsblock (FB). Dieser strukturierte Datentyp dient als Container für eine Sammlung von 64 einzelnen binären Werten (BOOL-Variablen). Er ermöglicht es, 64 unabhängige Schalter, Flags oder Statusbits unter einem einzigen Namen zu gruppieren und einzeln über benannte Felder anzusprechen. Obwohl der interne XML-Kommentar "A Structure with 16 BOOLS" angibt, enthält die tatsächliche Definition 64 BOOL-Variablen.

## Schnittstellenstruktur
Da `ST64X` ein Datentyp und kein Funktionsblock ist, besitzt er keine direkten Ereignis- oder Datenein- und -ausgänge im Sinne eines FBs. Stattdessen definiert er eine interne Struktur von Komponenten, die als einheitliche Variable in einem Funktionsblock verwendet werden kann (z.B. als Ein- oder Ausgangsparameter).

### **Ereignis-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Ereignis-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Eingänge**
Nicht zutreffend für einen Datentyp. Die hier aufgeführten Elemente sind die **internen Komponenten** der `ST64X`-Struktur, die Daten halten. Wenn `ST64X` als Dateneingang eines FBs verwendet wird, sind dies die verfügbaren Felder:

| Name | Typ | Kommentar |
| :--- | :--- | :-------- |
| `X_00` | `BOOL` | `BIT 00` |
| `X_01` | `BOOL` | `BIT 01` |
| `X_02` | `BOOL` | `BIT 02` |
| `X_03` | `BOOL` | `BIT 03` |
| `X_04` | `BOOL` | `BIT 04` |
| `X_05` | `BOOL` | `BIT 05` |
| `X_06` | `BOOL` | `BIT 06` |
| `X_07` | `BOOL` | `BIT 07` |
| `X_08` | `BOOL` | `BIT 08` |
| `X_09` | `BOOL` | `BIT 09` |
| `B_10` | `BOOL` | `BIT 10` |
| `B_11` | `BOOL` | `BIT 11` |
| `B_12` | `BOOL` | `BIT 12` |
| `B_13` | `BOOL` | `BIT 13` |
| `B_14` | `BOOL` | `BIT 14` |
| `B_15` | `BOOL` | `BIT 15` |
| `B_16` | `BOOL` | `BIT 16` |
| `B_17` | `BOOL` | `BIT 17` |
| `B_18` | `BOOL` | `BIT 18` |
| `B_19` | `BOOL` | `BIT 19` |
| `B_20` | `BOOL` | `BIT 20` |
| `B_21` | `BOOL` | `BIT 21` |
| `B_22` | `BOOL` | `BIT 22` |
| `B_23` | `BOOL` | `BIT 23` |
| `B_24` | `BOOL` | `BIT 24` |
| `B_25` | `BOOL` | `BIT 25` |
| `B_26` | `BOOL` | `BIT 26` |
| `B_27` | `BOOL` | `BIT 27` |
| `B_28` | `BOOL` | `BIT 28` |
| `B_29` | `BOOL` | `BIT 29` |
| `B_30` | `BOOL` | `BIT 30` |
| `B_31` | `BOOL` | `BIT 31` |
| `B_32` | `BOOL` | `BIT 32` |
| `B_33` | `BOOL` | `BIT 33` |
| `B_34` | `BOOL` | `BIT 34` |
| `B_35` | `BOOL` | `BIT 35` |
| `B_36` | `BOOL` | `BIT 36` |
| `B_37` | `BOOL` | `BIT 37` |
| `B_38` | `BOOL` | `BIT 38` |
| `B_39` | `BOOL` | `BIT 39` |
| `B_40` | `BOOL` | `BIT 40` |
| `B_41` | `BOOL` | `BIT 41` |
| `B_42` | `BOOL` | `BIT 42` |
| `B_43` | `BOOL` | `BIT 43` |
| `B_44` | `BOOL` | `BIT 44` |
| `B_45` | `BOOL` | `BIT 45` |
| `B_46` | `BOOL` | `BIT 46` |
| `B_47` | `BOOL` | `BIT 47` |
| `B_48` | `BOOL` | `BIT 48` |
| `B_49` | `BOOL` | `BIT 49` |
| `B_50` | `BOOL` | `BIT 50` |
| `B_51` | `BOOL` | `BIT 51` |
| `B_52` | `BOOL` | `BIT 52` |
| `B_53` | `BOOL` | `BIT 53` |
| `B_54` | `BOOL` | `BIT 54` |
| `B_55` | `BOOL` | `BIT 55` |
| `B_56` | `BOOL` | `BIT 56` |
| `B_57` | `BOOL` | `BIT 57` |
| `B_58` | `BOOL` | `BIT 58` |
| `B_59` | `BOOL` | `BIT 59` |
| `B_60` | `BOOL` | `BIT 60` |
| `B_61` | `BOOL` | `BIT 61` |
| `B_62` | `BOOL` | `BIT 62` |
| `B_63` | `BOOL` | `BIT 63` |

### **Daten-Ausgänge**
Nicht zutreffend für einen Datentyp. Die oben gelisteten Elemente sind die **internen Komponenten** der `ST64X`-Struktur, die Daten halten. Wenn `ST64X` als Datenausgang eines FBs verwendet wird, sind dies die verfügbaren Felder.

### **Adapter**
Nicht zutreffend für einen Datentyp.

## Funktionsweise
`ST64X` hat selbst keine "Funktionsweise" im Sinne eines aktiven Bausteins, der Berechnungen durchführt oder Zustände ändert. Seine "Funktion" besteht darin, eine definierte Struktur bereitzustellen, die als Vorlage für Datenobjekte dient. Einmal instanziiert, hält eine Variable vom Typ `ST64X` 64 individuelle BOOL-Werte, die über ihre Namen direkt gelesen oder geschrieben werden können (z.B. `MyVariable.X_00`, `MyVariable.B_63`). Es ist ein passiver Datencontainer.

## Technische Besonderheiten
*   **Strukturierte Daten:** Definiert eine feste Anordnung von 64 BOOL-Variablen.
*   **Benannte Felder:** Jedes Bit hat einen eindeutigen Namen (`X_00` bis `X_09` und `B_10` bis `B_63`), was die Lesbarkeit des Codes im Vergleich zu rein numerischen Indizes verbessert.
*   **Größe:** Repräsentiert 64 Bits, was in der Regel 8 Bytes Speicherplatz belegt (abhängig von der Compiler-Implementierung und Padding).
*   **Paketinformation:** Der Datentyp ist im Paket `logiBUS::utils::conversion::types` angesiedelt, was auf seine Rolle in Hilfsprogrammen oder Konvertierungen hindeutet.

## Zustandsübersicht
Nicht zutreffend für einen Datentyp, da er keine interne Logik oder Zustandsmaschine besitzt. Der "Zustand" einer `ST64X`-Variable ist einfach der aktuelle Wert der 64 enthaltenen BOOL-Variablen.

## Anwendungsszenarien
*   **Bit-Felder und Flags:** Ideal zur Darstellung einer großen Anzahl von binären Statusflags, Schalterstellungen oder Konfigurationsoptionen, die in einem zusammenhängenden Block organisiert werden sollen.
*   **Hardware-Schnittstellen:** Kann zur Abbildung von Registern oder E/A-Ports verwendet werden, bei denen einzelne Bits spezifische Funktionen oder Zustände repräsentieren.
*   **Kompakte Datenübertragung:** Wenn eine große Menge von BOOL-Werten effizient übermittelt werden muss, kann dieser Typ eine kompakte Darstellung bieten.
*   **Abstrakte Zustände:** Darstellung komplexer Zustände, die sich aus der Kombination von 64 binären Merkmalen ergeben.

## Vergleich mit ähnlichen Bausteinen
Da `ST64X` ein Datentyp ist, vergleicht man ihn nicht direkt mit Funktionsblöcken, sondern mit anderen Möglichkeiten zur Strukturierung von BOOL-Werten:

*   **`ARRAY OF BOOL`:** Ein `ARRAY[0..63] OF BOOL` würde ebenfalls 64 BOOL-Werte speichern. Der Hauptunterschied besteht im Zugriff: `ST64X` verwendet benannte Felder (z.B. `MyVar.X_00`), was oft lesbarer ist, wenn jedes Bit eine spezifische Bedeutung hat. Arrays verwenden Indizes (z.B. `MyArray[0]`), was flexibler für Schleifen und dynamischen Zugriff ist, aber weniger aussagekräftig, wenn die Bedeutung der einzelnen Indizes nicht offensichtlich ist.
*   **Einzelne `BOOL`-Variablen:** Man könnte auch 64 separate `BOOL`-Variablen deklarieren. Dies würde jedoch zu einer unübersichtlichen Liste von Variablen führen und die Zusammengehörigkeit der Bits verdecken. `ST64X` gruppiert sie logisch.
*   **Integer-Datentypen (z.B. `LWORD`):** Ein `LWORD` (64-Bit-Ganzzahl) könnte ebenfalls 64 Bits speichern. Der Zugriff auf einzelne Bits würde jedoch Bit-Operationen (AND, OR, SHIFT) erfordern, was komplexer und fehleranfälliger sein kann als der direkte Feldzugriff einer Struktur. `ST64X` bietet direkten, symbolischen Bit-Zugriff.

## Fazit
Der Datentyp `ST64X` ist ein nützliches Konstrukt in 4diac-ide zur Definition einer strukturierten Variable, die 64 individuelle BOOL-Werte enthält. Er bietet eine klare, benannte Schnittstelle zu jedem einzelnen Bit, was die Lesbarkeit und Wartbarkeit des Codes verbessert, insbesondere in Anwendungen, die eine feingranulare Steuerung oder Statusanzeige mit vielen binären Flags erfordern. Er ist eine gute Alternative zu `ARRAY OF BOOL` oder Bit-Manipulationen auf Integer-Typen, wenn die individuelle Bedeutung jedes Bits im Vordergrund steht.