# BOOLS_TO_ST08X

```{index} single: BOOLS_TO_ST08X
```

<img width="1032" height="423" alt="image" src="https://github.com/user-attachments/assets/6ba52e2e-b4e7-4f80-ac9f-c05e7c05956f" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock (FB) dient dazu, acht einzelne BOOL-Werte zu einer Struktur vom Typ `ST08X` zusammenzufassen. Er ermöglicht eine übersichtliche Gruppierung und Weitergabe von acht binären Informationen als eine einzige strukturierte Variable.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Event): Dieses Ereignis löst die Konvertierung und Zuweisung der Eingangswerte an den Ausgang aus. Alle Daten-Eingänge sind mit diesem Ereignis verbunden und werden bei dessen Eintreffen gelesen.

### **Ereignis-Ausgänge**
*   **CNF** (Event): Dieses Bestätigungsereignis wird ausgelöst, nachdem die Konvertierung erfolgreich abgeschlossen und der Ausgang `OUT` aktualisiert wurde. Der Daten-Ausgang `OUT` ist mit diesem Ereignis verbunden.

### **Daten-Eingänge**
*   **IN_00** (BOOL): Der Wert für Bit 0 der Ausgangsstruktur.
*   **IN_01** (BOOL): Der Wert für Bit 1 der Ausgangsstruktur.
*   **IN_02** (BOOL): Der Wert für Bit 2 der Ausgangsstruktur.
*   **IN_03** (BOOL): Der Wert für Bit 3 der Ausgangsstruktur.
*   **IN_04** (BOOL): Der Wert für Bit 4 der Ausgangsstruktur.
*   **IN_05** (BOOL): Der Wert für Bit 5 der Ausgangsstruktur.
*   **IN_06** (BOOL): Der Wert für Bit 6 der Ausgangsstruktur.
*   **IN_07** (BOOL): Der Wert für Bit 7 der Ausgangsstruktur.

### **Daten-Ausgänge**
*   **OUT** (logiBUS::utils::conversion::types::ST08X): Die resultierende Struktur, welche die Werte der acht binären Eingänge in ihren jeweiligen Feldern (`X_00` bis `X_07`) enthält.

### **Adapter**
Dieser Funktionsblock besitzt keine Adapter.

## Funktionsweise
Der Funktionsblock `BOOLS_TO_ST08X` wird durch ein eingehendes `REQ`-Ereignis aktiviert. Bei jeder Aktivierung werden die aktuellen Werte der acht Daten-Eingänge (`IN_00` bis `IN_07`) direkt den entsprechenden Feldern (`X_00` bis `X_07`) der Ausgangsstruktur `OUT` zugewiesen. Nach der erfolgreichen Zuweisung wird das `CNF`-Ereignis am Ausgang ausgelöst, um den Abschluss der Operation zu signalisieren und den aktualisierten `OUT`-Wert verfügbar zu machen. Die Zuweisung erfolgt 1:1, wobei `IN_00` dem Feld `X_00` entspricht, `IN_01` dem Feld `X_01` usw., bis `IN_07` dem Feld `X_07` zugewiesen wird.

## Technische Besonderheiten
*   **Direkte Zuweisung:** Die Logik besteht aus einer direkten 1:1-Zuweisung der Bool-Eingänge zu den Feldern der `ST08X`-Struktur.
*   **Typisierung:** Der `ST08X`-Typ ist eine benutzerdefinierte Struktur, die speziell für die Aggregation von acht Bool-Werten konzipiert ist und typensicher verwendet werden kann.
*   **Effizienz:** Der Baustein ist aufgrund seiner einfachen Implementierung sehr effizient und ressourcenschonend.
*   **Zustandslos:** Der Funktionsblock speichert keine internen Zustände und verarbeitet jede Anforderung unabhängig von vorherigen Aufrufen.

## Zustandsübersicht
Der Funktionsblock `BOOLS_TO_ST08X` ist ein zustandsloser Baustein. Dies bedeutet, dass er keine Informationen über vorherige Ausführungen speichert, die das aktuelle Verhalten beeinflussen könnten. Jede Aktivierung durch das `REQ`-Ereignis führt zu einer Neuberechnung des Ausgangs `OUT` basierend auf den zu diesem Zeitpunkt gültigen Werten der Daten-Eingänge.

## Anwendungsszenarien
*   **Sensordatenerfassung:** Zusammenfassen von acht einzelnen digitalen Sensorzuständen (z.B. Endschalter, Lichtschranken) in eine einzige Struktur für eine kompaktere Datenverarbeitung oder Visualisierung.
*   **Statusregister:** Erstellen eines Statusbytes oder -registers aus individuellen Bool-Flags, die verschiedene Betriebszustände oder Fehler anzeigen.
*   **Schnittstellenkommunikation:** Vorbereitung von binären Daten für die Übertragung über serielle Schnittstellen oder Kommunikationsprotokolle, die Daten in strukturierten Formaten erwarten.
*   **Programmierlogik:** Vereinfachung der Logik in komplexeren Funktionsblöcken, indem acht separate Signale zu einer einzelnen, handlicheren Variablen gebündelt werden.

## Vergleich mit ähnlichen Bausteinen
Dieser Funktionsblock ist spezialisiert auf die Umwandlung von acht BOOL-Werten in den benutzerdefinierten `ST08X`-Typ. Im Vergleich zu:
*   **`BOOLS_TO_BYTE` oder `BOOL_TO_WORD`:** Diese Bausteine wandeln einzelne BOOLs in einen primitiven Integer-Typ (Byte, Word) um, bei dem die einzelnen Bits über bitweise Operationen angesprochen werden müssen. `BOOLS_TO_ST08X` bietet hingegen eine strukturierte Variable, deren Felder direkt über Namen (`OUT.X_00`, `OUT.X_01`, etc.) zugänglich sind, was die Lesbarkeit des Codes verbessert.
*   **Logische Operatoren (AND, OR, XOR):** Diese Operatoren kombinieren Bool-Werte, aber nicht zu einer Struktur, sondern zu einem einzelnen Bool-Ergebnis. `BOOLS_TO_ST08X` dient der Aggregation, nicht der logischen Verknüpfung.

Der Hauptvorteil von `BOOLS_TO_ST08X` liegt in der Verwendung eines spezifischen Strukturtyps, der eine höhere Typsicherheit und bessere Code-Organisation im Vergleich zu generischen Integer-Typen bietet.

## Fazit
Der `BOOLS_TO_ST08X` Funktionsblock ist ein einfacher, aber äußerst nützlicher Baustein, um acht einzelne BOOL-Signale in eine standardisierte `ST08X`-Struktur zu überführen. Er fördert die Modularität und Lesbarkeit von 4diac-Applikationen, indem er eine saubere und typensichere Methode zur Bündelung von Bit-Informationen bereitstellt. Dies vereinfacht die Datenhandhabung und -weitergabe in komplexen Steuerungssystemen.
