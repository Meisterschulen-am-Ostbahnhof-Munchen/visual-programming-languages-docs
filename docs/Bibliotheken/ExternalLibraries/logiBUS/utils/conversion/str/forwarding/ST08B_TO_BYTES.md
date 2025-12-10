# ST08B_TO_BYTES

<img width="1031" height="423" alt="image" src="https://github.com/user-attachments/assets/d97ce166-0caf-452f-8aa8-52ba1b60245d" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock dient dazu, die einzelnen 8 Bytes einer speziellen 8-Byte-Struktur (`ST08B`) zu extrahieren und als separate Byte-Ausgänge bereitzustellen. Er ermöglicht eine detaillierte Aufteilung und Weiterverarbeitung von strukturierten 8-Byte-Daten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Löst die Funktion aus und initiiert die Extraktion der Bytes aus dem Daten-Eingang `IN`.

### **Ereignis-Ausgänge**
*   **CNF**: Wird nach erfolgreicher Ausführung und Aktualisierung aller Ausgangs-Bytes gesendet. Dieses Ereignis ist mit allen `OUT_xx` Daten-Ausgängen verknüpft.

### **Daten-Eingänge**
*   **IN** (`logiBUS::utils::conversion::types::ST08B`): Der Eingang, der die 8-Byte-Struktur enthält, deren Bytes extrahiert werden sollen.

### **Daten-Ausgänge**
*   **OUT_00** (`BYTE`): Das erste extrahierte Byte (Byte 00).
*   **OUT_01** (`BYTE`): Das zweite extrahierte Byte (Byte 01).
*   **OUT_02** (`BYTE`): Das dritte extrahierte Byte (Byte 02).
*   **OUT_03** (`BYTE`): Das vierte extrahierte Byte (Byte 03).
*   **OUT_04** (`BYTE`): Das fünfte extrahierte Byte (Byte 04).
*   **OUT_05** (`BYTE`): Das sechste extrahierte Byte (Byte 05).
*   **OUT_06** (`BYTE`): Das siebte extrahierte Byte (Byte 06).
*   **OUT_07** (`BYTE`): Das achte extrahierte Byte (Byte 07).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Sobald ein `REQ`-Ereignis empfangen wird, liest der Funktionsblock die Eingangsstruktur `IN`. Er extrahiert jedes einzelne Byte der Struktur (`IN.B_00` bis `IN.B_07`) und weist es dem entsprechenden Ausgangsparameter (`OUT_00` bis `OUT_07`) zu. Nach Abschluss dieser Zuweisungen wird das `CNF`-Ereignis ausgegeben, um die erfolgreiche Operation zu signalisieren. Die interne Logik ist direkt und transparent:

```iecst
OUT_00 := IN.B_00;
OUT_01 := IN.B_01;
OUT_02 := IN.B_02;
OUT_03 := IN.B_03;
OUT_04 := IN.B_04;
OUT_05 := IN.B_05;
OUT_06 := IN.B_06;
OUT_07 := IN.B_07;
```

## Technische Besonderheiten
Dieser Funktionsblock ist spezialisiert auf die Zerlegung der benutzerdefinierten Struktur `ST08B`. Die Typzuweisung erfolgt direkt und ohne zusätzliche Konvertierungslogik, da die Quell- und Zieltypen (Member der Struktur und Ausgänge) beide vom Typ `BYTE` sind. Dies gewährleistet eine effiziente und verlustfreie Aufteilung der Daten. Der Baustein ist deterministisch und stateless, da er keine internen Zustände speichert, die das Ergebnis zukünftiger Ausführungen beeinflussen könnten.

## Zustandsübersicht
Der Funktionsblock `ST08B_TO_BYTES` ist ein reiner Konverter ohne internen Zustand. Jede Ausführung ist unabhängig von vorherigen Ausführungen und liefert stets das gleiche Ergebnis für identische Eingangsdaten.

## Anwendungsszenarien
*   **Datenprotokollierung und -analyse**: Wenn eine 8-Byte-Struktur empfangen wird, können die einzelnen Bytes extrahiert werden, um sie separat zu protokollieren, zu überwachen oder für spezifische Analysen zu verwenden.
*   **Schnittstellenanpassung**: Anpassung von Datenformaten, wenn eine externe Schnittstelle eine 8-Byte-Struktur liefert, aber nachfolgende Bausteine einzelne Bytes erwarten.
*   **Bit-Level-Manipulation**: Vorbereitung von Daten für Bit-Level-Operationen, bei denen jedes Byte einzeln adressiert werden muss.
*   **Debugging**: Vereinfacht das Debugging von Daten in 8-Byte-Strukturen, indem die Inhalte der einzelnen Bytes sichtbar gemacht werden.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Funktionalität könnte in anderen Systemen durch explizite Typumwandlungen oder Zeigeroperationen erreicht werden. Im 4diac-Kontext stellt dieser Baustein eine ereignisgesteuerte, klar definierte und wiederverwendbare Lösung für diese spezifische Struktur-zu-Byte-Aufteilung dar. Der Vorteil liegt in der direkten Anbindung an das 4diac-Ereignismodell und der expliziten Deklaration der Schnittstelle, was die Lesbarkeit und Wartbarkeit verbessert. Alternativ müssten die Zuweisungen direkt im `ST`-Code eines Composite Function Blocks erfolgen, was die Wiederverwendbarkeit einschränken würde.

## Fazit
Der `ST08B_TO_BYTES`-Funktionsblock ist ein nützliches Hilfsmittel zur Zerlegung einer spezifischen 8-Byte-Struktur in ihre einzelnen Byte-Bestandteile. Seine Einfachheit, klare Schnittstelle und deterministische Funktionsweise machen ihn zu einem zuverlässigen Baustein für Anwendungen, die eine präzise Kontrolle und Analyse von 8-Byte-Daten erfordern. Er fördert die Modularität und Wiederverwendbarkeit in 4diac-Anwendungen.
