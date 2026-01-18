# F_STRING_AS_DWORD

```{index} single: F_STRING_AS_DWORD
```

<img width="1477" height="213" alt="F_STRING_AS_DWORD" src="https://github.com/user-attachments/assets/15d7b45e-4104-4052-a553-f9d43f45f903" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_DWORD` dient der Konvertierung eines `STRING`-Wertes in einen `DWORD`-Wert. Diese Funktionalität ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise für die weitere Verarbeitung in Steuerungsalgorithmen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (`STRING`): Der Eingabewert, der in einen `DWORD`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- `OUT` (`DWORD`): Der Ergebniswert der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des `STRING`-Eingabewertes `IN` in einen `DWORD`-Wert durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mithilfe der Funktion `STRING_AS_DWORD`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der Ergebniswert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und führt die Konvertierung in einem einzigen Algorithmus durch.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt direkt bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben oder Kommunikationsdaten in numerische Werte.
- Verwendung in Steuerungsalgorithmen, die numerische Werte anstelle von Zeichenketten erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_TO_INT` oder `F_STRING_TO_REAL` ist dieser Baustein speziell auf die Konvertierung in den `DWORD`-Datentyp ausgelegt.
- Die direkte Verwendung der `STRING_AS_DWORD`-Funktion ermöglicht eine effiziente und spezialisierte Konvertierung.

## Fazit
Der `F_STRING_AS_DWORD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeichenketten in `DWORD`-Werte umzuwandeln. Durch seine klare Schnittstellenstruktur und direkte Funktionsweise ist er ideal für Anwendungen geeignet, die eine schnelle und zuverlässige Konvertierung erfordern.
