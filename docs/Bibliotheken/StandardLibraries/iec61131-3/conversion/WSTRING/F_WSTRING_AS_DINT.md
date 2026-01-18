# F_WSTRING_AS_DINT

```{index} single: F_WSTRING_AS_DINT
```

<img width="1480" height="214" alt="F_WSTRING_AS_DINT" src="https://github.com/user-attachments/assets/364137ca-5b73-4be9-b4dd-475b9e5b8768" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_DINT` dient der Konvertierung eines WSTRING-Wertes in einen DINT-Wert. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht die einfache Umwandlung von breiten Zeichenketten in ganzzahlige Werte.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingangsvariable vom Typ `WSTRING`. Enthält die zu konvertierende Zeichenkette.

### **Daten-Ausgänge**
- **OUT**: Ausgangsvariable vom Typ `DINT`. Enthält das Ergebnis der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock konvertiert den Wert der Eingangsvariable `IN` vom Typ `WSTRING` in einen Wert vom Typ `DINT` und speichert das Ergebnis in der Ausgangsvariable `OUT`. Die Konvertierung erfolgt durch den Aufruf der Funktion `WSTRING_AS_DINT` im Algorithmus `REQ`.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt über die eingebaute Funktion `WSTRING_AS_DINT`.
- Der Funktionsblock ist einfach und hat keine zusätzlichen Zustände oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt direkt bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Benutzereingaben in numerische Werte.
- Verarbeitung von Zeichenketten, die numerische Daten enthalten, in Steuerungssystemen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_STRING_AS_DINT` konvertieren einfache Zeichenketten (`STRING`) in `DINT`, während dieser Block breite Zeichenketten (`WSTRING`) verarbeitet.
- Im Vergleich zu generischen Konvertierungsblöcken ist dieser spezialisiert auf die Umwandlung von `WSTRING` zu `DINT`.

## Fazit
Der `F_WSTRING_AS_DINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, breite Zeichenketten in ganzzahlige Werte umzuwandeln. Er ist besonders nützlich in Szenarien, wo breite Zeichenketten verarbeitet werden müssen.
