# ST32B

```{index} single: ST32B
```

* * * * * * * * * *
## Einleitung
Der Datentyp `ST32B` ist ein strukturierter Datentyp (Structured Type) innerhalb der 4diac-IDE, der für die Aggregation von 32 einzelnen Bytes konzipiert ist. Er dient als Vorlage für Datenstrukturen, die eine feste Länge von 32 Byte benötigen und direkten Zugriff auf einzelne Bytes ermöglichen. Dieser Typ ist in der 4diac-IDE unter dem Paket `logiBUS::utils::conversion::types` registriert.

## Schnittstellenstruktur
Da `ST32B` ein strukturierter Datentyp und kein Funktionsbaustein ist, besitzt er keine externen Ereignis- oder Datenschnittstellen im herkömmlichen Sinne. Stattdessen definiert er eine interne Struktur von Elementen, auf die in einem Programm zugegriffen werden kann.

### **Ereignis-Eingänge**
Für strukturierte Datentypen nicht zutreffend. `ST32B` besitzt keine Ereignis-Eingänge.

### **Ereignis-Ausgänge**
Für strukturierte Datentypen nicht zutreffend. `ST32B` besitzt keine Ereignis-Ausgänge.

### **Daten-Eingänge**
Für strukturierte Datentypen nicht zutreffend. `ST32B` besitzt keine Daten-Eingänge; seine Elemente sind direkt über den Typnamen zugänglich.

### **Daten-Ausgänge**
Für strukturierte Datentypen nicht zutreffend. `ST32B` besitzt keine Daten-Ausgänge; seine Elemente sind direkt über den Typnamen zugänglich.

### **Adapter**
Für strukturierte Datentypen nicht zutreffend. `ST32B` besitzt keine Adapter.

## Funktionsweise
`ST32B` ist ein passiver Datentyp und implementiert keine aktive "Funktionsweise" oder Logik. Er dient lediglich als Bauplan (Schema) für die Organisation und Speicherung von 32 Byte-Werten unter einem einzigen logischen Namen. Instanzen dieses Datentyps können in anderen Funktionsbausteinen oder Datentypen deklariert und genutzt werden, um Daten strukturiert abzulegen oder zu übergeben.

Die einzelnen Bytes sind wie folgt benannt und können direkt angesprochen werden:
- `B_00`: Byte 00
- `B_01`: Byte 01
- ...
- `B_30`: Byte 30
- `B_31`: Byte 31

## Technische Besonderheiten
*   **Feste Größe:** Der Datentyp `ST32B` ist auf eine exakte Größe von 32 Bytes festgelegt.
*   **Direkter Byte-Zugriff:** Jedes der 32 Bytes ist individuell über seinen Namen ansprechbar (`B_00` bis `B_31`).
*   **Grundlegender Typ:** Er besteht ausschließlich aus dem primitiven Datentyp `BYTE`, was ihn für Low-Level-Datenoperationen oder die Darstellung von Rohdaten prädestiniert.
*   **Einfachheit:** Die Struktur ist bewusst einfach gehalten, um eine effiziente Nutzung und klare Datenorganisation zu gewährleisten.

## Zustandsübersicht
Als passiver Datentyp hat `ST32B` keine internen Zustände im Sinne eines Zustandsautomaten. Der "Zustand" einer Instanz dieses Typs wird ausschließlich durch die aktuellen Werte der 32 enthaltenen Bytes definiert.

## Anwendungsszenarien
*   **Rohdatentransport:** Ideal zum Übertragen von fix langen Rohdatenpaketen, beispielsweise von Sensoren oder über Kommunikationsschnittstellen wie SPI, I2C, UART oder Ethernet, wenn die Nutzlast eine feste Länge von 32 Byte hat.
*   **Nachrichtenstrukturen:** Kann als Grundlage für einfache Nachrichtenformate dienen, bei denen ein Teil des Nachrichtenrahmens eine definierte Länge von 32 Bytes einnimmt.
*   **Speicherabbild:** Zur Abbildung eines kleinen, festen Speicherbereichs oder Registersatzes in einer Steuerung.
*   **Konfigurationsdaten:** Speicherung von 32 Byte umfassenden Konfigurationsparametern.

## Vergleich mit ähnlichen Bausteinen
Ein vergleichbarer Ansatz wäre die Verwendung eines Arrays vom Typ `ARRAY[0..31] OF BYTE`.
Der Unterschied liegt hauptsächlich in der Art des Zugriffs und der Semantik:
*   **`ST32B` (Struktur):** Ermöglicht den Zugriff auf Bytes über symbolische Namen (`B_00`, `B_01`, ...), was die Lesbarkeit und Wartbarkeit des Codes verbessern kann, insbesondere wenn die einzelnen Bytes eine spezifische Bedeutung haben.
*   **`ARRAY[0..31] OF BYTE` (Array):** Ermöglicht den Zugriff über einen numerischen Index (`[0]`, `[1]`, ...), was für Schleifen und generische Operationen vorteilhaft ist.

Während ein Array flexibler in der Dimensionierung sein kann, bietet `ST32B` eine klar definierte, benannte Struktur, die die Absicht hinter jedem Byte expliziter macht, auch wenn die Namen hier generisch sind.

## Fazit
Der Datentyp `ST32B` ist ein fundamentaler strukturierter Datentyp in 4diac, der eine einfache und effiziente Möglichkeit bietet, 32 Bytes als eine Einheit zu behandeln. Seine Stärke liegt in der Bereitstellung einer festen, gut definierten Struktur für Rohdaten, was ihn zu einem nützlichen Werkzeug in Anwendungen macht, die präzise Kontrolle über Byte-Sequenzen erfordern. Obwohl er selbst keine aktive Funktionalität besitzt, ist er eine wichtige Grundlage für datenorientierte Architekturen innerhalb von 4diac-Anwendungen.
