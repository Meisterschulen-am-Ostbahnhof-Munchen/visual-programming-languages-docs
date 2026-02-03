# F_REAL_TO_INT

```{index} single: F_REAL_TO_INT
```

<img width="1423" height="216" alt="F_REAL_TO_INT" src="https://github.com/user-attachments/assets/35987aee-ae88-4b7f-9f53-776f056c104e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_INT` dient der Konvertierung eines REAL-Wertes (Fließkommazahl) in einen INT-Wert (Ganzzahl). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden müssen, die unterschiedliche Datentypen verwenden.

![F_REAL_TO_INT](F_REAL_TO_INT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang für den REAL-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten INT-Wert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den REAL-Wert am Eingang `IN` in einen INT-Wert umwandelt und das Ergebnis am Ausgang `OUT` ausgibt. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `REAL_TO_INT`, die den REAL-Wert in einen INT-Wert umwandelt.
- Der Funktionsblock ist einfach und effizient, da er keine komplexen Algorithmen oder Zustandsmaschinen verwendet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach dem Auslösen des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Datenkonvertierung**: Umwandlung von Sensorwerten (Fließkommazahlen) in Ganzzahlen für weitere Verarbeitung.
- **Schnittstellenkompatibilität**: Anpassung von Daten zwischen Systemen, die unterschiedliche Datentypen erwarten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_TRUNC**: Konvertiert REAL zu INT durch Abschneiden der Nachkommastellen, während `F_REAL_TO_INT` eine standardmäßige Rundung durchführt.
- **F_ROUND**: Rundet REAL zu INT, ähnlich wie `F_REAL_TO_INT`, aber mit spezifischen Rundungsregeln.

## Fazit
Der `F_REAL_TO_INT`-Funktionsblock ist ein einfaches und effektives Werkzeug zur Konvertierung von Fließkommazahlen in Ganzzahlen. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und unkomplizierte Datentypumwandlung erforderlich ist.