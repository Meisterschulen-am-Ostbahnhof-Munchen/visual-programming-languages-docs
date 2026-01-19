# ST02X

```{index} single: ST02X
```

*(Kein Bild verfügbar für diesen Datentyp.)*

* * * * * * * * * *
## Einleitung
Der Datentyp **ST02X** ist ein strukturierter Datentyp, der darauf ausgelegt ist, zwei boolesche Werte zu kapseln. Er dient als einfache Datenstruktur, um zwei individuelle Bits oder boolesche Zustände in einer einzigen Einheit zu organisieren und zu transportieren. Der Name "ST02X" deutet auf eine "Struktur mit 2 [Booleschen Werten]" hin.

## Schnittstellenstruktur
Da es sich bei ST02X um einen Datentyp und nicht um einen Funktionsblock handelt, besitzt er keine externen Ereignis- oder Dateneingänge/-ausgänge im üblichen Sinne eines Funktionsblocks. Seine "Struktur" bezieht sich auf die Definition seiner internen Komponenten, die die eigentlichen Daten darstellen.

### **Ereignis-Eingänge**
Nicht zutreffend, da ST02X ein Datentyp und kein Funktionsblock ist und somit keine Ereignisse verarbeitet.

### **Ereignis-Ausgänge**
Nicht zutreffend, da ST02X ein Datentyp und kein Funktionsblock ist und somit keine Ereignisse erzeugt.

### **Daten-Eingänge**
Die internen Komponenten dieses Datentyps können als seine "Daten" betrachtet werden, die gesetzt oder gelesen werden können, wenn eine Variable dieses Typs verwendet wird.
*   **X_00** (Typ: BOOL, Kommentar: BIT 00)
    *   Der erste boolesche Wert innerhalb der Struktur.
*   **X_01** (Typ: BOOL, Kommentar: BIT 01)
    *   Der zweite boolesche Wert innerhalb der Struktur.

### **Daten-Ausgänge**
Die internen Komponenten können auch als "Daten-Ausgänge" angesehen werden, da ihre Werte von externen Bausteinen oder Programmteilen ausgelesen werden können, wenn eine Variable vom Typ ST02X verwendet wird.

### **Adapter**
Nicht zutreffend, da ST02X ein Datentyp und kein Funktionsblock ist und somit keine Adapter-Schnittstellen besitzt.

## Funktionsweise
Der Datentyp ST02X ist ein passiver Container für Daten. Er selbst führt keine Operationen oder Logik aus. Seine Funktionsweise beschränkt sich darauf, die beiden booleschen Werte `X_00` und `X_01` logisch zusammenzufassen. Wenn eine Variable des Typs ST02X deklariert wird, kann auf ihre Komponenten über den Punkt-Operator (z.B. `meineVariable.X_00`) zugegriffen werden, um deren Werte zu lesen oder zu schreiben.

## Technische Besonderheiten
*   **Kompakte Struktur:** Der Datentyp ist sehr einfach gehalten und besteht nur aus zwei booleschen Variablen.
*   **Typische Anwendung:** Er eignet sich besonders zur Gruppierung von zwei verwandten Status-Bits, Flags oder Schalterzuständen, die gemeinsam behandelt werden sollen.
*   **Paketierung:** Die interne Struktur kann dazu beitragen, Daten kompakt zu halten und die Lesbarkeit des Codes zu verbessern, indem logisch zusammengehörende Informationen gebündelt werden.

## Zustandsübersicht
Da ST02X selbst keine aktive Logik besitzt, hat es keinen "Zustand" im Sinne eines Zustandsautomaten. Der "Zustand" einer Variablen vom Typ ST02X wird durch die Kombination der Werte ihrer beiden booleschen Komponenten (`X_00` und `X_01`) bestimmt. Es gibt vier mögliche Zustände für eine Instanz von ST02X:
*   `X_00 = FALSE, X_01 = FALSE`
*   `X_00 = TRUE, X_01 = FALSE`
*   `X_00 = FALSE, X_01 = TRUE`
*   `X_00 = TRUE, X_01 = TRUE`

## Anwendungsszenarien
*   **Statusanzeige:** Gruppierung von zwei Status-Flags (z.B. "Alarm Aktiv" und "Warnung Anstehend").
*   **Konfigurationsparameter:** Bündelung von zwei binären Konfigurationseinstellungen.
*   **Sensordaten:** Zusammenfassung der Zustände zweier einfacher Sensoren (z.B. zwei Endlagenschalter).
*   **Schnittstellen:** Als Parameter für Funktionsblöcke, die zwei boolesche Informationen auf einmal verarbeiten oder zurückgeben müssen, was die Schnittstellendefinition vereinfacht.

## Vergleich mit ähnlichen Bausteinen
*   **Einzelne BOOL-Variablen:** Anstatt ST02X zu verwenden, könnten zwei separate BOOL-Variablen deklariert werden. Der Vorteil von ST02X liegt in der logischen Bündelung und der potenziell übersichtlicheren Übergabe als einzelner Parameter an Funktionsblöcke.
*   **ARRAY OF BOOL:** Ein Array wie `ARRAY[0..1] OF BOOL` könnte ebenfalls zwei boolesche Werte halten. ST02X bietet jedoch den Vorteil der benannten Zugriffe (`.X_00`, `.X_01`), was die Lesbarkeit gegenüber Indexzugriffen (`[0]`, `[1]`) verbessern kann.
*   **Andere strukturierte Typen:** Abhängig von der Anwendung könnten komplexere strukturierte Datentypen mit mehr booleschen Werten (z.B. ST04X, ST08X) oder gemischten Datentypen besser geeignet sein, wenn mehr oder unterschiedliche Informationen gebündelt werden müssen. ST02X ist speziell für den Fall von genau zwei BOOLS optimiert.

## Fazit
ST02X ist ein einfacher, aber nützlicher strukturierter Datentyp, der die logische Gruppierung von zwei booleschen Werten ermöglicht. Er verbessert die Code-Organisation und Lesbarkeit, insbesondere beim Umgang mit zwei verwandten binären Informationen. Seine Stärke liegt in seiner Einfachheit und klaren Definition, was ihn zu einer guten Wahl für spezifische Anwendungsfälle macht, bei denen genau zwei boolesche Zustände gebündelt werden müssen.