# ST64B

* * * * * * * * * *
## Einleitung
Der Datentyp `ST64B` ist ein strukturierter Datentyp, der zur Kapselung von 64 einzelnen Byte-Werten dient. Er wurde entwickelt, um eine feste Datenstruktur von 64 Bytes bereitzustellen, die für verschiedene Anwendungsfälle genutzt werden kann, bei denen eine exakt definierte Größe und direkter Zugriff auf einzelne Bytes erforderlich ist. Die ursprüngliche XML-Definition enthielt einen Kommentar, der fälschlicherweise 16 Bytes angab; korrekt sind 64 Bytes.

## Strukturdefinition
Der Datentyp `ST64B` ist eine zusammengesetzte Struktur, die ausschließlich aus einzelnen Byte-Variablen besteht. Er besitzt keine ereignis- oder adapterbasierten Schnittstellen, da es sich um eine reine Datenstruktur handelt.

### **Ereignis-Eingänge**
Nicht zutreffend, da `ST64B` ein Datentyp und kein Funktionsblock ist.

### **Ereignis-Ausgänge**
Nicht zutreffend, da `ST64B` ein Datentyp und kein Funktionsblock ist.

### **Daten-Bestandteile**
Die Struktur `ST64B` setzt sich aus den folgenden 64 Byte-Variablen zusammen:

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| B\_00 | BYTE | BYTE 00 |
| B\_01 | BYTE | BYTE 01 |
| B\_02 | BYTE | BYTE 02 |
| B\_03 | BYTE | BYTE 03 |
| B\_04 | BYTE | BYTE 04 |
| B\_05 | BYTE | BYTE 05 |
| B\_06 | BYTE | BYTE 06 |
| B\_07 | BYTE | BYTE 07 |
| B\_08 | BYTE | BYTE 08 |
| B\_09 | BYTE | BYTE 09 |
| B\_10 | BYTE | BYTE 10 |
| B\_11 | BYTE | BYTE 11 |
| B\_12 | BYTE | BYTE 12 |
| B\_13 | BYTE | BYTE 13 |
| B\_14 | BYTE | BYTE 14 |
| B\_15 | BYTE | BYTE 15 |
| B\_16 | BYTE | BYTE 16 |
| B\_17 | BYTE | BYTE 17 |
| B\_18 | BYTE | BYTE 18 |
| B\_19 | BYTE | BYTE 19 |
| B\_20 | BYTE | BYTE 20 |
| B\_21 | BYTE | BYTE 21 |
| B\_22 | BYTE | BYTE 22 |
| B\_23 | BYTE | BYTE 23 |
| B\_24 | BYTE | BYTE 24 |
| B\_25 | BYTE | BYTE 25 |
| B\_26 | BYTE | BYTE 26 |
| B\_27 | BYTE | BYTE 27 |
| B\_28 | BYTE | BYTE 28 |
| B\_29 | BYTE | BYTE 29 |
| B\_30 | BYTE | BYTE 30 |
| B\_31 | BYTE | BYTE 31 |
| B\_32 | BYTE | BYTE 32 |
| B\_33 | BYTE | BYTE 33 |
| B\_34 | BYTE | BYTE 34 |
| B\_35 | BYTE | BYTE 35 |
| B\_36 | BYTE | BYTE 36 |
| B\_37 | BYTE | BYTE 37 |
| B\_38 | BYTE | BYTE 38 |
| B\_39 | BYTE | BYTE 39 |
| B\_40 | BYTE | BYTE 40 |
| B\_41 | BYTE | BYTE 41 |
| B\_42 | BYTE | BYTE 42 |
| B\_43 | BYTE | BYTE 43 |
| B\_44 | BYTE | BYTE 44 |
| B\_45 | BYTE | BYTE 45 |
| B\_46 | BYTE | BYTE 46 |
| B\_47 | BYTE | BYTE 47 |
| B\_48 | BYTE | BYTE 48 |
| B\_49 | BYTE | BYTE 49 |
| B\_50 | BYTE | BYTE 50 |
| B\_51 | BYTE | BYTE 51 |
| B\_52 | BYTE | BYTE 52 |
| B\_53 | BYTE | BYTE 53 |
| B\_54 | BYTE | BYTE 54 |
| B\_55 | BYTE | BYTE 55 |
| B\_56 | BYTE | BYTE 56 |
| B\_57 | BYTE | BYTE 57 |
| B\_58 | BYTE | BYTE 58 |
| B\_59 | BYTE | BYTE 59 |
| B\_60 | BYTE | BYTE 60 |
| B\_61 | BYTE | BYTE 61 |
| B\_62 | BYTE | BYTE 62 |
| B\_63 | BYTE | BYTE 63 |

### **Daten-Ausgänge**
Nicht zutreffend, da `ST64B` ein Datentyp ist und seine Bestandteile nicht als "Ausgänge" im Sinne eines Funktionsblocks fungieren.

### **Adapter**
Nicht zutreffend, da `ST64B` ein Datentyp und kein Funktionsblock ist.

## Funktionsweise
Als strukturierter Datentyp hat `ST64B` keine eigene "Funktionsweise" im Sinne eines aktiven Verhaltens oder einer Logik. Seine primäre Funktion ist es, einen Speicherbereich von 64 Bytes zu definieren und diesen in einer organisierten Form zugänglich zu machen. Dies ermöglicht die Adressierung einzelner Bytes innerhalb der Struktur über ihre benannten Variablen (z.B. `ST64B.B_00`, `ST64B.B_15`). Es dient als passiver Datencontainer.

## Technische Besonderheiten
Die Hauptbesonderheit von `ST64B` ist seine feste Größe von exakt 64 Bytes. Jedes Byte ist einzeln über einen eindeutigen Variablennamen ansprechbar. Dies macht ihn ideal für Situationen, in denen eine strikte Datengröße und eine byteweise Manipulation des Inhalts erforderlich sind, wie z.B. bei der Verarbeitung von Kommunikationsprotokollen oder Hardware-Registern. Die sequentielle Benennung der Variablen vereinfacht die Zuordnung zu einem durchgehenden Speicherbereich.

## Zustandsübersicht
Als reiner Datentyp besitzt `ST64B` keine Zustände im Sinne einer Zustandsmaschine oder eines Funktionsblocks. Der "Zustand" eines `ST64B`-Instanz wird ausschließlich durch die aktuellen Werte der 64 enthaltenen Byte-Variablen definiert. Jede Kombination dieser Werte stellt einen gültigen Datenzustand der Struktur dar.

## Anwendungsszenarien
`ST64B` eignet sich hervorragend für folgende Anwendungsszenarien:
*   **Kommunikationspuffer:** Als Standardpuffer für Nachrichten oder Pakete mit einer festen Größe von 64 Bytes, z.B. in CAN-Bus-Nachrichten (wenn mehrere Frames benötigt werden), serieller Kommunikation oder anderen Protokollen.
*   **Hardware-Registerabbild:** Abbildung eines 64 Byte großen Bereichs von Hardware-Registern, bei dem jeder Byte-Variable einem spezifischen Register entspricht.
*   **Daten-Serialisierung:** Speicherung von Rohdaten vor der Serialisierung oder nach der Deserialisierung, insbesondere wenn Daten ohne explizite Typinformationen übertragen werden.
*   **Generische Datenblöcke:** Handhabung von generischen Datenblöcken fester Größe, die flexibel interpretiert werden können, z.B. als Teil größerer Protokolle oder Datenstrukturen.

## Vergleich mit ähnlichen Bausteinen
`ST64B` ist ein grundlegender Datentyp und kann nicht direkt mit Funktionsblöcken verglichen werden. Innerhalb der Datentypen ist er vergleichbar mit:
*   **Anderen strukturierten Datentypen:** `ST64B` ist eine spezifische Instanz eines `StructuredType`. Es gibt ähnliche Strukturen mit unterschiedlicher Anzahl oder Art von Elementen (z.B. Strukturen mit 8, 16, 32 Bytes oder solche, die Integers, Booleans usw. enthalten). `ST64B` zeichnet sich durch seine rein byteweise Aufteilung aus.
*   **Arrays von BYTE:** Ein Array vom Typ `ARRAY[0..63] OF BYTE` würde ebenfalls 64 Bytes speichern. Der Unterschied besteht in der Zugriffsweise: Bei `ST64B` erfolgt der Zugriff über benannte Member (z.B. `myST64B.B_10`), während bei einem Array der Zugriff über einen Index erfolgt (z.B. `myArray[10]`). Die benannten Member können in bestimmten Kontexten für eine klarere Lesbarkeit des Codes oder für die direkte Adressierung spezifischer Byte-Positionen vorteilhaft sein.

## Fazit
`ST64B` ist ein einfacher, aber mächtiger strukturierter Datentyp, der eine feste Datenmenge von 64 Bytes bereitstellt. Seine Stärke liegt in der klaren Definition und der direkten Zugänglichkeit jedes einzelnen Bytes, was ihn zu einer ausgezeichneten Wahl für Anwendungen macht, die eine präzise Steuerung und Interpretation von Rohdatenblöcken erfordern, insbesondere im Bereich der Kommunikation und Hardware-Interaktion.