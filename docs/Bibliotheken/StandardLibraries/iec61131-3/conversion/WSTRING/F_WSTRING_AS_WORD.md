# F_WSTRING_AS_WORD

```{index} single: F_WSTRING_AS_WORD
```

<img width="1482" height="214" alt="F_WSTRING_AS_WORD" src="https://github.com/user-attachments/assets/a3b2eb5b-24e3-4685-bc76-b8864d468811" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_WORD` dient der Konvertierung eines WSTRING-Datentyps in einen WORD-Datentyp. Diese Funktionalität ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise für die weitere Verarbeitung in Steuerungsalgorithmen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Erwartet eine Eingabe vom Typ `WSTRING`, die in einen `WORD`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt das Ergebnis der Konvertierung als `WORD` zurück.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Die Umwandlung erfolgt mithilfe der Funktion `WSTRING_AS_WORD`, die den `WSTRING`-Eingang `IN` in einen `WORD`-Wert konvertiert und das Ergebnis über den Ausgang `OUT` ausgibt. Die erfolgreiche Ausführung wird durch das Ereignis `CNF` signalisiert.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist für die Verwendung in IEC 61131-konformen Umgebungen optimiert.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Zeichenketten in numerische Werte für Steuerungsbefehle.
- Verarbeitung von Texteingaben in numerische Steuerungssysteme.
- Integration in Systeme, die eine Konvertierung zwischen unterschiedlichen Datentypen erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_WSTRING_AS_WORD` spezialisiert auf die Umwandlung von `WSTRING` zu `WORD`.
- Andere Bausteine könnten zusätzliche Parameter oder Fehlerbehandlungen bieten, dieser Funktionsblock ist jedoch auf Einfachheit und Effizienz ausgelegt.

## Fazit
Der `F_WSTRING_AS_WORD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `WSTRING`-Daten in `WORD`-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die schnelle und zuverlässige Konvertierungen erfordern.
