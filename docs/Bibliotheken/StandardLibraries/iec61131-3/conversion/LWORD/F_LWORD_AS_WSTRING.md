# F_LWORD_AS_WSTRING

```{index} single: F_LWORD_AS_WSTRING
```

<img width="1279" height="183" alt="F_LWORD_AS_WSTRING" src="https://github.com/user-attachments/assets/98e37fb6-7c6a-4646-bda8-685187f8d75b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_AS_WSTRING` dient zur Konvertierung eines LWORD-Datentyps in einen WSTRING-Datentyp. Diese Funktionalität ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden müssen, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Ereigniseingang löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieses Ereignis wird ausgegeben, sobald die Konvertierung abgeschlossen ist.

### **Daten-Eingänge**
- **IN**: Eingangsvariable vom Typ LWORD, die den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Ausgangsvariable vom Typ WSTRING, die den konvertierten Wert enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von LWORD zu WSTRING durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der integrierten Funktion `LWORD_AS_WSTRING`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgegeben.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher FB (SimpleFB) und enthält einen einzigen Algorithmus.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in industriellen Steuerungssystemen.
- Austausch von Daten zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Integration in größere Steuerungsanwendungen, wo eine Typumwandlung erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist `F_LWORD_AS_WSTRING` spezialisiert auf die Umwandlung von LWORD zu WSTRING.
- Andere Bausteine könnten allgemeinere Konvertierungen unterstützen, sind aber möglicherweise weniger effizient für diesen spezifischen Anwendungsfall.

## Fazit
Der Funktionsblock `F_LWORD_AS_WSTRING` bietet eine effiziente und direkte Methode zur Konvertierung von LWORD zu WSTRING. Seine einfache Struktur und klare Funktionsweise machen ihn zu einem zuverlässigen Werkzeug in Steuerungsanwendungen.