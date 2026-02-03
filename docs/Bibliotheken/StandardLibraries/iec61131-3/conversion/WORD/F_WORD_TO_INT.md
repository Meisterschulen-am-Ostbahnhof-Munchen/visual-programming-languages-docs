# F_WORD_TO_INT

```{index} single: F_WORD_TO_INT
```

<img width="1423" height="214" alt="F_WORD_TO_INT" src="https://github.com/user-attachments/assets/49dc7b5b-d691-45f0-963a-7e6af1509e72" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_INT` dient der Konvertierung eines `WORD`-Datentyps in einen `INT`-Datentyp. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht eine einfache und effiziente Typumwandlung innerhalb von IEC 61131-3-basierten Steuerungssystemen.

![F_WORD_TO_INT](F_WORD_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `WORD`, der in einen `INT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `INT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung aus, sobald das Ereignis `REQ` ausgelöst wird. Die Umwandlung erfolgt mithilfe der Funktion `WORD_TO_INT`, die den Wert des Eingangs `IN` in einen `INT`-Wert konvertiert und das Ergebnis an den Ausgang `OUT` weitergibt. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `WORD`-Daten in `INT`-Daten umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die eine Typkompatibilität erfordern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke könnten `F_BYTE_TO_INT` oder `F_DWORD_TO_INT` sein, die jedoch andere Datentypen konvertieren.
- Im Gegensatz zu komplexeren Konvertierungsblöcken bietet `F_WORD_TO_INT` eine einfache und direkte Lösung für die spezifische Umwandlung von `WORD` zu `INT`.

## Fazit
Der `F_WORD_TO_INT`-Funktionsblock ist ein effizientes und einfach zu verwendendes Werkzeug für die Typumwandlung in IEC 61131-3-basierten Systemen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Konvertierung erfordern.