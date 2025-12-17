# ST04X

* * * * * * * * * *
## Einleitung
ST04X ist ein strukturierter Datentyp, der vier boolesche Werte gruppiert. Er dient dazu, eine Sammlung von vier einzelnen Bits in einer einzigen Struktur zu organisieren und zu handhaben.

## Schnittstellenstruktur
Da ST04X ein Datentyp und kein Funktionsblock ist, besitzt er keine Ereignis- oder Dateneingänge/-ausgänge im Sinne eines Funktionsblocks oder Adapter. Stattdessen definiert er eine interne Struktur von Datenfeldern.

### **Ereignis-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Ereignis-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Adapter**
Nicht zutreffend für einen Datentyp.

**Struktur-Elemente:**
Die Struktur ST04X besteht aus den folgenden vier booleschen Feldern:
*   **X_00** (Typ: BOOL, Kommentar: BIT 00)
*   **X_01** (Typ: BOOL, Kommentar: BIT 01)
*   **X_02** (Typ: BOOL, Kommentar: BIT 02)
*   **X_03** (Typ: BOOL, Kommentar: BIT 03)

## Funktionsweise
Als Datentyp hat ST04X keine aktive "Funktionsweise" im Sinne eines Funktionsbausteins. Seine Funktion ist passiv: Er definiert lediglich, wie vier boolesche Variablen logisch zusammengefasst und als eine Einheit referenziert werden können. Dies ermöglicht eine bessere Organisation und Lesbarkeit des Codes, indem zusammengehörige Bits in einer Struktur gebündelt werden.

## Technische Besonderheiten
*   **Kompaktheit**: Bündelt vier individuelle BOOL-Werte, was in manchen Systemen eine effizientere Datenhaltung oder -übertragung ermöglichen kann.
*   **Strukturierung**: Verbessert die Code-Struktur und -Lesbarkeit, indem verwandte Bits unter einem gemeinsamen Namen zusammengefasst werden.
*   **Verwendung in FBs**: Dieser Datentyp kann als Ein- oder Ausgangsparameter für Funktionsblöcke oder als interne Variable innerhalb eines Funktionsblocks verwendet werden, um Gruppierungen von vier Bits zu verwalten.

## Zustandsübersicht
Nicht zutreffend für einen Datentyp. Ein Datentyp repräsentiert eine Datenstruktur, nicht einen Zustandsautomaten.

## Anwendungsszenarien
*   **Statusregister**: Abbildung eines kleinen Statusregisters oder einer Gruppe von Flags, bei denen jedes Bit einen bestimmten Zustand oder eine Eigenschaft anzeigt.
*   **Binäreingänge/-ausgänge**: Gruppierung von vier digitalen Ein- oder Ausgängen einer Hardware-Schnittstelle.
*   **Bitfelder**: Wenn eine kompakte Darstellung von vier unabhängigen binären Informationen erforderlich ist, z.B. bei der Verarbeitung von seriellen Datenprotokollen oder Gerätekonfigurationen.

## Vergleich mit ähnlichen Bausteinen
ST04X ist ein Datentyp und kann daher nicht direkt mit Funktionsblöcken (Bausteinen) verglichen werden.
Ein Vergleich wäre eher mit anderen Datentypen möglich, z.B.:
*   **BOOL**: Ein einzelner Boolescher Wert. ST04X bündelt vier davon.
*   **BYTE**: Ein 8-Bit-Integer. ST04X bietet eine strukturierte Sicht auf 4 Bits, während ein BYTE in der Regel als eine unstrukturierte 8-Bit-Zahl behandelt wird. Die einzelnen Bits eines BYTE müssten über Bitmasken oder Bit-Operationen angesprochen werden, während bei ST04X jedes Bit direkt über seinen Namen zugänglich ist (z.B. `myST04X.X_00`).
*   **Array von BOOL**: Ein Array von BOOLs (`ARRAY[0..3] OF BOOL`) bietet ebenfalls die Gruppierung, der Zugriff erfolgt jedoch über Indizes (`myArray[0]`), wohingegen ST04X den Zugriff über benannte Felder (`myST04X.X_00`) ermöglicht, was die Lesbarkeit verbessern kann.

## Fazit
ST04X ist ein nützlicher strukturierter Datentyp in 4diac, der die Verwaltung und Organisation von vier booleschen Werten vereinfacht. Obwohl er selbst keine aktive Funktionalität bietet, ist er ein wichtiges Werkzeug zur Verbesserung der Code-Strukturierung und -Lesbarkeit in komplexeren Steuerungsprogrammen, indem er zusammengehörige Bits logisch bündelt und einen direkten, benannten Zugriff auf jedes Bit ermöglicht.