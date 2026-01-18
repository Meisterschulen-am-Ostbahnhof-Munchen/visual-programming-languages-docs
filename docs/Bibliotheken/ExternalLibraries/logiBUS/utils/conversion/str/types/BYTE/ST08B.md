# ST08B

```{index} single: ST08B
```

* * * * * * * * * *
## Einleitung
Der Datentyp `ST08B` ist eine strukturierte Datenstruktur, die genau acht Byte (BYTE) sequenziell zusammenfasst. Er dient primär als Container für die effiziente Gruppierung und den Transport von acht einzelnen Byte-Werten innerhalb eines IEC 61499-basierten Steuerungssystems. Dieser Datentyp ist besonders nützlich für die Handhabung von Rohdaten, Protokollrahmen oder für die strukturierte Übergabe von parametrisierten Datenblöcken zwischen Funktionsblöcken.

## Schnittstellenstruktur
`ST08B` ist ein Datentyp und besitzt als solcher keine ereignisgesteuerten Ein- oder Ausgänge im Sinne eines Funktionsblocks. Seine Struktur wird ausschließlich durch seine Datenmitglieder definiert.

### **Daten-Eingänge**
Nicht zutreffend. Dieser Abschnitt ist für Funktionsblöcke vorgesehen.

### **Daten-Ausgänge**
Nicht zutreffend. Dieser Abschnitt ist für Funktionsblöcke vorgesehen.

### **Ereignis-Eingänge**
Nicht zutreffend. Dieser Abschnitt ist für Funktionsblöcke vorgesehen.

### **Ereignis-Ausgänge**
Nicht zutreffend. Dieser Abschnitt ist für Funktionsblöcke vorgesehen.

### **Adapter**
Nicht zutreffend. Dieser Abschnitt ist für Funktionsblöcke vorgesehen.

## Funktionsweise
Als strukturierter Datentyp (STRUCT) fungiert `ST08B` als zusammengesetzter Behälter. Er bündelt acht unabhängige Variablen des Typs `BYTE` unter einem gemeinsamen Namen. Jedes Byte innerhalb der Struktur ist über seinen eindeutigen Member-Namen (`B_00` bis `B_07`) direkt adressierbar. Funktionsblöcke können Variablen vom Typ `ST08B` deklarieren, um alle acht Bytes als eine Einheit zu übergeben, zu speichern oder zu verarbeiten. Der Zugriff auf einzelne Bytes erfolgt durch die Punktnotation (z.B. `MyST08BInstance.B_04`).

## Technische Besonderheiten
*   **Feste Größe:** Die Struktur hat eine fest definierte und vorhersehbare Größe von genau 8 Bytes, was für Speicherallokation und Kommunikationsprotokolle vorteilhaft ist.
*   **Sequenzielle Anordnung:** Die Bytes sind in der Reihenfolge `B_00` bis `B_07` angeordnet. Diese Reihenfolge ist für die Interpretation der Daten, z.B. bei der Konvertierung in größere Datentypen wie `WORD`, `DWORD` oder `LWORD`, entscheidend.
*   **TypeHash-Attribut:** Der Datentyp enthält das Attribut `eclipse4diac::core::TypeHash` mit einem leeren Wert (`''`). Dies weist darauf hin, dass für diesen benutzerdefinierten Typ (noch) keine typsichere Prüfung via Hash-Wert konfiguriert wurde.

## Zustandsübersicht
Da es sich um einen passiven Datentyp und nicht um einen aktiven Funktionsblock handelt, existiert keine Zustandsmaschine. Der "Zustand" einer Instanz von `ST08B` ist einfach der aktuelle Wert jedes seiner acht Byte-Member.

## Anwendungsszenarien
1.  **Datenpaketierung:** Zusammenfassen von acht konfigurierbaren Parametern oder Statuswerten, die gemeinsam von einem Funktionsblock an einen anderen gesendet werden sollen.
2.  **Protokollhandling:** Darstellung eines festen Datenrahmenheaders oder -segments in einer seriellen oder Netzwerkkommunikation.
3.  **Rohdatenpuffer:** Temporäre Speicherung eines 8-Byte-blocks aus einem Sensor oder einem Kommunikationsinterface vor der weiteren Verarbeitung oder Interpretation.
4.  **Konvertierungsbasis:** Nutzung als Quelle oder Ziel für Konvertierungs-Funktionsblöcke, die `ST08B` in andere Datentypen wie `LWORD` (64-Bit) umwandeln oder daraus generieren.

## Vergleich mit ähnlichen Bausteinen
*   **Einfache BYTE-Array:** Ein Array von 8 `BYTE` (`ARRAY[0..7] OF BYTE`) könnte eine ähnliche Funktion erfüllen. `ST08B` bietet jedoch den Vorteil der benannten Zugriffspfade (`B_01`), die im Gegensatz zu Index-basiertem Zugriff (`Array[1]`) die Code-Lesbarkeit und Wartbarkeit verbessern.
*   **LWORD:** Der Datentyp `LWORD` repräsentiert ebenfalls 8 Bytes (64 Bit), jedoch als einen einzigen, ununterteilten numerischen Wert. `ST08B` erlaubt den gezielten Zugriff auf jedes einzelne Byte innerhalb dieser 64 Bit.
*   **Andere STRUCT-Typen:** Ähnliche strukturierte Typen wie `ST04B` (4 Bytes) oder `ST16B` (16 Bytes) dienen demselben Zweck, aber für unterschiedliche Datenmengen. `ST08B` füllt die Lücke für 8-Byte-strukturierte Daten.

## Fazit
Der `ST08B` ist ein einfacher, aber äußerst nützlicher strukturierter Datentyp für die IEC 61499-Programmierung. Er bietet eine klare und strukturierte Methode, um acht Byte Daten zu gruppieren, und fördert damit die Lesbarkeit, Wartbarkeit und Typsicherheit in Anwendungen, die mit festen Datenblöcken oder parametrisierten Datensätzen arbeiten. Seine feste Größe und sequenzielle Anordnung machen ihn zu einem verlässlichen Baustein für Datenkommunikation und -konvertierung.
