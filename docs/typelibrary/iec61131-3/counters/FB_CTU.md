# FB_CTU

* * * * * * * * * *
## Einleitung
Der FB_CTU (Up Counter) ist ein Funktionsblock, der als Aufwärtszähler fungiert. Er zählt Ereignisse hoch und kann zurückgesetzt werden. Der Zählerwert wird mit einem vordefinierten Wert (PV) verglichen, und ein Ausgangssignal (Q) wird aktiviert, sobald der Zählerwert den vordefinierten Wert erreicht oder überschreitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Wird verwendet, um den Zählvorgang auszulösen. Verknüpft mit den Daten-Eingängen `CU` und `R`.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird ausgelöst, nachdem der Zählvorgang abgeschlossen ist. Verknüpft mit den Daten-Ausgängen `Q` und `CV`.

### **Daten-Eingänge**
- **CU** (BOOL): Zählt hoch, wenn `TRUE`. Wird nur ausgewertet, wenn `R` `FALSE` ist.
- **R** (BOOL): Setzt den Zählerwert (`CV`) auf 0 zurück, wenn `TRUE`.
- **PV** (INT): Vordefinierter Wert, mit dem der Zählerwert (`CV`) verglichen wird.

### **Daten-Ausgänge**
- **Q** (BOOL): Wird `TRUE`, wenn der Zählerwert (`CV`) den vordefinierten Wert (`PV`) erreicht oder überschreitet.
- **CV** (INT): Aktueller Zählerwert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der FB_CTU führt folgende Schritte aus, wenn das Ereignis `REQ` eintritt:
1. Wenn `R` `TRUE` ist, wird der Zählerwert (`CV`) auf 0 zurückgesetzt.
2. Wenn `CU` `TRUE` ist und der Zählerwert (`CV`) kleiner als 32767 ist, wird `CV` um 1 erhöht.
3. Der Ausgang `Q` wird auf `TRUE` gesetzt, wenn `CV` größer oder gleich `PV` ist.

## Technische Besonderheiten
- Der Zählerwert (`CV`) ist auf einen maximalen Wert von 32767 begrenzt.
- Der FB_CTU ist ein einfacher Funktionsblock ohne interne Zustandsverwaltung zwischen den Aufrufen.

## Zustandsübersicht
Der FB_CTU hat keine internen Zustände. Die Logik wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Zählen von Ereignissen, z.B. Produktionsschritte in einer Fertigungslinie.
- Überwachung von Prozessen, bei denen eine bestimmte Anzahl von Schritten erreicht werden muss.
- Steuerung von Abläufen, die nach einer bestimmten Anzahl von Wiederholungen eine Aktion auslösen sollen.

## Vergleich mit ähnlichen Bausteinen
- **FB_CTD**: Ein Abwärtszähler, der im Gegensatz zum FB_CTU herunterzählt.
- **FB_CTUD**: Ein kombiniertes Auf- und Abwärtszähler, der sowohl hoch- als auch herunterzählen kann.

## Fazit
Der FB_CTU ist ein einfacher und effektiver Funktionsblock für Aufwärtszählvorgänge. Er eignet sich besonders für Anwendungen, bei denen Ereignisse gezählt und bei Erreichen eines bestimmten Werts eine Aktion ausgelöst werden soll. Die klare Schnittstellenstruktur und die einfache Funktionsweise machen ihn zu einem nützlichen Baustein in der Steuerungstechnik.