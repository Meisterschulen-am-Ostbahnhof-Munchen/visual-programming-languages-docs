# FB_CTU_ULINT

<img width="1408" height="271" alt="FB_CTU_ULINT" src="https://github.com/user-attachments/assets/fb1bdbf1-e57f-4efd-8953-c3e697ae3f39" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_CTU_ULINT` ist ein Aufwärtszähler (Counter Up) für den Datentyp `ULINT` (Unsigned Long Integer). Er zählt bei jedem Zählereignis hoch und kann auf einen vordefinierten Wert zurückgesetzt werden. Der Block ist besonders für Anwendungen geeignet, die große Zählbereiche erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Wird verwendet, um den Zählvorgang auszulösen. Verknüpft mit den Daten `CU` und `R`.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach der Verarbeitung des Zählvorgangs ausgelöst. Verknüpft mit den Daten `Q` und `CV`.

### **Daten-Eingänge**
- **CU** (BOOL): Zählaufforderung. Bei `TRUE` wird der Zähler erhöht, sofern nicht `R` aktiv ist.
- **R** (BOOL): Reset. Setzt den Zählerwert (`CV`) auf `0` zurück, wenn `TRUE`.
- **PV** (ULINT): Voreingestellter Wert. Definiert den Schwellwert, bei dem der Ausgang `Q` aktiviert wird.

### **Daten-Ausgänge**
- **Q** (BOOL): Ausgang. Wird `TRUE`, wenn der Zählerwert (`CV`) den voreingestellten Wert (`PV`) erreicht oder überschreitet.
- **CV** (ULINT): Aktueller Zählerwert. Gibt den aktuellen Stand des Zählers zurück.

## Funktionsweise
Der Funktionsblock erhöht den Zählerwert (`CV`) um 1, wenn der Eingang `CU` aktiviert ist (`TRUE`) und der Zählerwert nicht den Maximalwert (`18446744073709551615`) erreicht hat. Wenn der Eingang `R` aktiviert ist (`TRUE`), wird der Zählerwert auf `0` zurückgesetzt. Der Ausgang `Q` wird auf `TRUE` gesetzt, sobald der Zählerwert (`CV`) den voreingestellten Wert (`PV`) erreicht oder überschreitet.

## Technische Besonderheiten
- Der Zählerwert (`CV`) ist vom Typ `ULINT`, was einen sehr großen Zählbereich ermöglicht (0 bis 18446744073709551615).
- Der Block ist deterministisch und eignet sich für Echtzeitanwendungen.

## Zustandsübersicht
- **Reset-Zustand**: `CV = 0` (wenn `R = TRUE`).
- **Zählzustand**: `CV` wird um 1 erhöht (wenn `CU = TRUE` und `R = FALSE`).
- **Schwellwert erreicht**: `Q = TRUE` (wenn `CV >= PV`).

## Anwendungsszenarien
- Zählung von Produktionsstücken in Hochgeschwindigkeitsanlagen.
- Überwachung von Ereignissen in lang laufenden Systemen.
- Steuerung von Prozessen mit großen Zählbereichen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `FB_CTU_INT` oder `FB_CTU_DINT` bietet `FB_CTU_ULINT` einen deutlich größeren Zählbereich.
- Ähnlich zu `FB_CTU`, aber spezialisiert auf den `ULINT`-Datentyp.

## Fazit
Der `FB_CTU_ULINT` ist ein leistungsstarker Aufwärtszähler für Anwendungen, die große Zählbereiche erfordern. Seine einfache Handhabung und deterministische Funktionsweise machen ihn zu einer zuverlässigen Wahl für industrielle Steuerungsanwendungen.
