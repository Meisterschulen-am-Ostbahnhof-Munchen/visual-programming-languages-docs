# F_ULINT_TO_UINT

```{index} single: F_ULINT_TO_UINT
```

<img width="1453" height="214" alt="F_ULINT_TO_UINT" src="https://github.com/user-attachments/assets/398715a7-1e03-490c-83c0-41f0f4d745ed" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_UINT` dient zur Konvertierung eines 64-Bit unsigned integer Wertes (ULINT) in einen 16-Bit unsigned integer Wert (UINT). Der Baustein ist Teil des `iec61131::conversion` Pakets und implementiert eine einfache Typumwandlung.

![F_ULINT_TO_UINT](F_ULINT_TO_UINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: ULINT (64-Bit unsigned integer) - Der Eingabewert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: UINT (16-Bit unsigned integer) - Das Ergebnis der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von ULINT zu UINT durch, wenn das `REQ`-Ereignis eintrifft. Die Konvertierung wird mit der Funktion `ULINT_TO_UINT` durchgeführt. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Baustein führt eine direkte Typumwandlung durch, wobei die höherwertigen Bits des ULINT-Wertes abgeschnitten werden, falls der Wert außerhalb des UINT-Bereiches liegt.
- Der Baustein ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo ULINT-Werte auf UINT reduziert werden müssen.
- Datenverarbeitung in eingebetteten Systemen mit begrenzter Speicherkapazität.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_ULINT_TO_UINT` spezialisiert und optimiert für die spezifische Konvertierung von ULINT zu UINT.
- Andere Bausteine könnten zusätzliche Funktionalitäten wie Bereichsprüfungen oder Skalierungen bieten, was hier nicht der Fall ist.

## Fazit
Der `F_ULINT_TO_UINT` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von 64-Bit unsigned integer Werten in 16-Bit unsigned integer Werte. Er ist besonders nützlich in Anwendungen, wo eine direkte und schnelle Typumwandlung benötigt wird.