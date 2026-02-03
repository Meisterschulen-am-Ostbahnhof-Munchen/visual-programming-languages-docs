# F_LINT_TO_REAL

```{index} single: F_LINT_TO_REAL
```

<img width="1438" height="214" alt="F_LINT_TO_REAL" src="https://github.com/user-attachments/assets/0609cf87-5b1c-45c8-95bd-9cfaa561c08c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_REAL` konvertiert einen ganzzahligen Wert des Typs `LINT` (64-Bit Integer) in einen Fließkommawert des Typs `REAL`. Diese Konvertierung ist nützlich, wenn Daten aus einem ganzzahligen Format in ein Fließkommaformat umgewandelt werden müssen, beispielsweise für weitere Berechnungen oder Anzeigen.

![F_LINT_TO_REAL](F_LINT_TO_REAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Auslösung dieses Ereignisses wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `LINT`, der den zu konvertierenden ganzzahligen Wert bereitstellt.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `REAL`, der das Ergebnis der Konvertierung liefert.

### **Adapter**
- Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Der Algorithmus liest den Wert von `IN`, konvertiert ihn mit der Funktion `LINT_TO_REAL` und schreibt das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne Rundung oder Skalierung, da es sich um eine direkte Typumwandlung handelt.
- Der Funktionsblock ist für die Verwendung in Echtzeitsystemen geeignet, da er keine Verzögerungen oder komplexen Berechnungen beinhaltet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Umwandlung von Sensorwerten, die als `LINT` vorliegen, in `REAL` für weitere Verarbeitung.
- Integration in Systeme, die Fließkommaoperationen erfordern, aber Eingangsdaten als Ganzzahlen erhalten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_REAL` oder `F_DINT_TO_REAL` führen ähnliche Konvertierungen durch, jedoch mit kleineren Integer-Typen (`INT` oder `DINT`).
- `F_LINT_TO_REAL` ist speziell für 64-Bit Integer (`LINT`) optimiert.

## Fazit
Der `F_LINT_TO_REAL` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 64-Bit Integer-Werte in Fließkommazahlen umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine Typkonvertierung ohne zusätzliche Verarbeitung erfordern.