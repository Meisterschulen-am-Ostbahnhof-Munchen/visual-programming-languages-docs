# ARR08B_TO_ST08B

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/6f2c370a-b183-4202-8424-1b736a6424dd" />

* * * * * * * * * *
## Einleitung
Diese Funktion wandelt ein 8-Byte-Array in eine 8-Byte-Struktur um. Sie dient dazu, lineare Byte-Daten in ein strukturiertes Format zu überführen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Ein steigendes Ereignis an diesem Eingang triggert die Konvertierung der Daten vom Eingang `IN` zum Ausgang `OUT`.
    *   Verbunden mit: `IN`

### **Ereignis-Ausgänge**
*   **CNF**: Ein Ereignis an diesem Ausgang signalisiert den Abschluss der Konvertierung und dass die Ausgangsdaten an `OUT` aktualisiert wurden.
    *   Verbunden mit: `OUT`

### **Daten-Eingänge**
*   **IN** (Typ: `BYTE`, Arraygröße: `[0..7]`): Der Eingangsdaten-Array, der die 8 Bytes enthält, die konvertiert werden sollen.
    *   Kommentar: `ARR08B Input`

### **Daten-Ausgänge**
*   **OUT** (Typ: `logiBUS::utils::conversion::types::ST08B`): Die Ausgangsstruktur, die die konvertierten 8 Bytes enthält.
    *   Kommentar: `ST08B Output`

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock `ARR08B_TO_ST08B` führt eine direkte Byte-für-Byte-Zuweisung durch. Wenn ein `REQ`-Ereignis empfangen wird, werden die einzelnen Elemente des Eingangs-Arrays `IN` den entsprechenden Komponenten der Ausgangsstruktur `OUT` zugewiesen:
*   `OUT.B_00` wird `IN[0]` zugewiesen.
*   `OUT.B_01` wird `IN[1]` zugewiesen.
*   ...
*   `OUT.B_07` wird `IN[7]` zugewiesen.

Nach Abschluss dieser Zuweisungen wird ein `CNF`-Ereignis ausgelöst, um anzuzeigen, dass die Konvertierung abgeschlossen ist und die neuen Daten am `OUT`-Ausgang verfügbar sind.

## Technische Besonderheiten
*   **Datentypen:** Der Eingangs-Array ist vom Typ `BYTE`, die Ausgangsstruktur `ST08B` ist ein benutzerdefinierter Typ, der aus 8 einzelnen `BYTE`-Komponenten besteht (z.B. `B_00` bis `B_07`).
*   **Direkte Zuweisung:** Es findet keine Datenmanipulation oder Umrechnung statt; die Bytes werden direkt von der Array-Position zur Struktur-Komponente kopiert.
*   **Stateless:** Der Funktionsblock hat keinen internen Zustand und produziert immer das gleiche Ergebnis für die gleiche Eingabe.

## Zustandsübersicht
Der `ARR08B_TO_ST08B`-Funktionsblock ist **zustandslos**. Er führt eine rein funktionale Transformation durch: Bei jedem Trigger-Ereignis (`REQ`) wird die Umwandlung der aktuellen Eingabewerte (`IN`) vorgenommen, und das Ergebnis (`OUT`) wird ausgegeben. Es werden keine Werte zwischen den Aufrufen gespeichert.

## Anwendungsszenarien
Dieser Funktionsblock ist nützlich in Szenarien, in denen:
*   Rohdaten, die als Byte-Array empfangen werden (z.B. über Kommunikationsschnittstellen wie CAN, SPI, UART), in ein strukturiertes Format umgewandelt werden müssen, um die Lesbarkeit und weitere Verarbeitung zu erleichtern.
*   Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Repräsentationen für denselben 8-Byte-Datensatz verwenden (Array vs. Struktur).
*   Eine klare und explizite Typumwandlung von einer linearen in eine benannte Struktur erforderlich ist, um die Programmlogik zu verbessern.

## Vergleich mit ähnlichen Bausteinen
*   **Generische Kopierfunktionen (z.B. `MEMCPY`):** Im Gegensatz zu einer generischen Speicher-Kopierfunktion, die Speicherbereiche byteweise kopiert, bietet `ARR08B_TO_ST08B` eine typensichere und explizite Zuweisung von Array-Elementen zu strukturierten Feldern. Dies kann helfen, Fehler bei der Größen- oder Typanpassung zu vermeiden und die Lesbarkeit des Codes zu verbessern.
*   **Manuelle Zuweisungen:** Die Funktionalität könnte auch durch acht einzelne Zuweisungszeilen im ST-Code erreicht werden. Dieser Funktionsblock kapselt diese Logik jedoch in einer wiederverwendbaren und leicht integrierbaren Einheit, was die Modularität und Wartbarkeit fördert.
*   **Type Casting:** Während in einigen Sprachen ein Type Cast eine ähnliche Umwandlung ermöglichen könnte, bietet dieser Funktionsblock eine explizite, ereignisgesteuerte Schnittstelle, die gut in das 4diac-Modell passt und eine klare Triggerung der Konvertierung ermöglicht.

## Fazit
Der `ARR08B_TO_ST08B`-Funktionsblock ist ein spezialisierter und effizienter Baustein zur Umwandlung eines 8-Byte-Arrays in eine vordefinierte 8-Byte-Struktur. Er trägt zur Verbesserung der Code-Struktur, Lesbarkeit und Wartbarkeit bei, indem er eine häufig benötigte Konvertierungsaufgabe in einer klaren und wiederverwendbaren Einheit kapselt. Seine zustandslose Natur gewährleistet eine vorhersehbare und zuverlässige Funktion.
