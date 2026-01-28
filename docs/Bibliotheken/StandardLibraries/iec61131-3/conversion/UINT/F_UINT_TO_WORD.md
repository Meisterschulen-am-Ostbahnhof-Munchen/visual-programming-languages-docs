# F_UINT_TO_WORD

```{index} single: F_UINT_TO_WORD
```

<img width="1436" height="216" alt="F_UINT_TO_WORD" src="https://github.com/user-attachments/assets/6e3b2752-57b0-41a0-b681-16c58d50879f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_WORD` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (UINT) in ein 16-Bit-Wort (WORD). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten zwischen unterschiedlichen Darstellungsformen oder Systemen ausgetauscht werden müssen.

![F_UINT_TO_WORD](F_UINT_TO_WORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende UINT-Wert.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte WORD-Wert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den UINT-Wert von `IN` mittels der Funktion `UINT_TO_WORD` in ein WORD umwandelt und das Ergebnis an `OUT` ausgibt. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und durch `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verarbeitung.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen.
- Kommunikation zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Integration von Legacy-Systemen, die WORD-Datentypen erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_TO_WORD` oder `F_BYTE_TO_WORD` ist `F_UINT_TO_WORD` speziell auf die Konvertierung von vorzeichenlosen 16-Bit-Integern ausgelegt.
- Der Baustein ist einfacher aufgebaut als generische Konvertierungsbausteine, die mehrere Datentypen unterstützen.

## Fazit
Der `F_UINT_TO_WORD`-Funktionsblock bietet eine effiziente und direkte Lösung für die Konvertierung von UINT- zu WORD-Werten. Seine Einfachheit und Determinismus machen ihn zu einer zuverlässigen Wahl in Steuerungs- und Kommunikationsanwendungen.