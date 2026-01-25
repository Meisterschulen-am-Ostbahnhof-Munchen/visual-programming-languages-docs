# F_STRING_AS_ULINT

```{index} single: F_STRING_AS_ULINT
```

<img width="1480" height="212" alt="F_STRING_AS_ULINT" src="https://github.com/user-attachments/assets/42f8c0fa-f5ad-4f51-9d6b-3c35653b6782" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_ULINT` dient der Konvertierung eines `STRING`-Wertes in einen `ULINT`-Wert (unsigned 64-bit integer). Dieser Baustein ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder beim Parsen von Daten aus externen Quellen.

![F_STRING_AS_ULINT](F_STRING_AS_ULINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `STRING`, der die zu konvertierende Zeichenkette enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `ULINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird die eingebaute Funktion `STRING_AS_ULINT` verwendet, um den `STRING`-Eingang `IN` in einen `ULINT`-Wert umzuwandeln. Das Ergebnis wird am Ausgang `OUT` ausgegeben, und das Ereignis `CNF` signalisiert die erfolgreiche Beendigung der Operation.

## Technische Besonderheiten
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter oder Einstellungen.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- **Datenverarbeitung**: Umwandlung von Zeichenketten in numerische Werte für Berechnungen oder Speicherung.
- **Benutzereingaben**: Verarbeitung von Eingaben, die als Zeichenketten vorliegen, aber als Zahlen interpretiert werden sollen.
- **Protokollierung**: Konvertierung von logischen oder textuellen Daten in numerische Formate für die weitere Analyse.

## Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_INT**: Konvertiert einen `STRING` in einen `INT` (signed 32-bit integer). Im Gegensatz dazu arbeitet `F_STRING_AS_ULINT` mit einem größeren Wertebereich und ohne Vorzeichen.
- **F_STRING_AS_LINT**: Ähnlich, aber für `LINT` (signed 64-bit integer). `F_STRING_AS_ULINT` ist für vorzeichenlose Werte optimiert.

## Fazit
Der Funktionsblock `F_STRING_AS_ULINT` bietet eine einfache und effiziente Möglichkeit, Zeichenketten in vorzeichenlose 64-bit Integer-Werte umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine schnelle und zuverlässige Konvertierung erfordern.