# FB_CTU_UDINT

<img width="1411" height="277" alt="FB_CTU_UDINT" src="https://github.com/user-attachments/assets/f36dc7f5-bd23-4af7-8a8a-fc038435ca79" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_CTU_UDINT` ist ein Aufwärtszähler (Counter Up) für den Datentyp `UDINT` (unsigned double integer). Er zählt bei jedem Ereignis `REQ` hoch, solange der Eingang `CU` aktiv ist, und kann über den Eingang `R` zurückgesetzt werden. Der Zähler vergleicht den aktuellen Zählerstand mit einem vorgegebenen Sollwert (`PV`) und gibt über den Ausgang `Q` ein Signal aus, wenn dieser erreicht oder überschritten wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird mit den Daten-Eingängen `CU` und `R` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung des Funktionsblocks. Wird mit den Daten-Ausgängen `Q` und `CV` verknüpft.

### **Daten-Eingänge**
- **CU** (`BOOL`): Signal zum Hochzählen. Bei `TRUE` wird der Zählerstand erhöht.
- **R** (`BOOL`): Signal zum Zurücksetzen des Zählers. Bei `TRUE` wird der Zählerstand auf `0` gesetzt.
- **PV** (`UDINT`): Sollwert (Preset Value), mit dem der aktuelle Zählerstand verglichen wird.

### **Daten-Ausgänge**
- **Q** (`BOOL`): Signal, das `TRUE` wird, wenn der Zählerstand (`CV`) den Sollwert (`PV`) erreicht oder überschreitet.
- **CV** (`UDINT`): Aktueller Zählerstand (Count Value).

## Funktionsweise
Der Funktionsblock führt bei jedem `REQ`-Ereignis folgende Schritte aus:
1. Wenn `R` aktiv ist (`TRUE`), wird der Zählerstand (`CV`) auf `0` zurückgesetzt.
2. Wenn `CU` aktiv ist (`TRUE`) und der Zählerstand (`CV`) kleiner als der Maximalwert (`4294967295`) ist, wird der Zählerstand um `1` erhöht.
3. Der Ausgang `Q` wird auf `TRUE` gesetzt, wenn der Zählerstand (`CV`) den Sollwert (`PV`) erreicht oder überschreitet.

## Technische Besonderheiten
- Der Zählerstand (`CV`) ist vom Typ `UDINT` und kann Werte zwischen `0` und `4294967295` annehmen.
- Der Funktionsblock ist deterministisch und führt die Zähloperation bei jedem `REQ`-Ereignis aus.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände außer dem aktuellen Zählerstand (`CV`). Die Logik wird bei jedem `REQ`-Ereignis neu ausgewertet.

## Anwendungsszenarien
- Zählen von Ereignissen in Steuerungsanwendungen (z. B. Produktionszähler).
- Überwachung von Prozessen, bei denen eine bestimmte Anzahl von Schritten erreicht werden muss.
- Als Teil einer größeren Steuerungslogik, die auf Zählerstände reagiert.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Zählern (z. B. `FB_CTU_INT`) arbeitet dieser Funktionsblock mit dem Datentyp `UDINT`, was einen größeren Wertebereich ermöglicht.
- Ähnliche Funktionsblöcke könnten zusätzliche Funktionen wie Abwärtszählen oder eine kombinierte Auf-/Abwärtszählung bieten.

## Fazit
Der `FB_CTU_UDINT` ist ein einfacher und effizienter Aufwärtszähler für Anwendungen, die einen großen Wertebereich benötigen. Seine klare Schnittstelle und deterministische Funktionsweise machen ihn zu einem zuverlässigen Baustein in Steuerungsanwendungen.
