# F_DWORD_TO_UDINT

```{index} single: F_DWORD_TO_UDINT
```

<img width="1253" height="181" alt="F_DWORD_TO_UDINT" src="https://github.com/user-attachments/assets/0b023d3e-49d2-41d3-a6b3-db4d5f1970f8" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_DWORD_TO_UDINT` dient der Konvertierung eines `DWORD`-Werts in einen `UDINT`-Wert. Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache und effiziente Typumwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `DWORD`, der den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `UDINT`, der das Ergebnis der Konvertierung liefert.

### **Adapter**
- Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DWORD` zu `UDINT` durch, sobald das `REQ`-Ereignis ausgelöst wird. Die Umwandlung erfolgt mithilfe der integrierten Funktion `DWORD_TO_UDINT`. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus (`REQ`), der die Konvertierung durchführt.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, bei denen `DWORD`-Werte in `UDINT`-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die eine Typkompatibilität zwischen verschiedenen Datenformaten erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_UINT` oder `F_BYTE_TO_USINT` führen ähnliche Typumwandlungen durch, jedoch für andere Datentypen.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_DWORD_TO_UDINT` spezialisiert und optimiert für die Umwandlung von `DWORD` zu `UDINT`.

## Fazit
Der `F_DWORD_TO_UDINT`-Funktionsblock bietet eine einfache und effiziente Lösung für die Konvertierung von `DWORD`-Werten in `UDINT`-Werte. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem zuverlässigen Baustein in Steuerungsanwendungen.