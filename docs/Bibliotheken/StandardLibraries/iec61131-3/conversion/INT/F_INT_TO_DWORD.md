# F_INT_TO_DWORD

```{index} single: F_INT_TO_DWORD
```

<img width="1233" height="182" alt="F_INT_TO_DWORD" src="https://github.com/user-attachments/assets/2e21163c-54a9-4408-b67f-b1a8a5dc7dee" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_DWORD` dient der Konvertierung eines Integer-Werts (INT) in einen Double-Word-Wert (DWORD). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

![F_INT_TO_DWORD](F_INT_TO_DWORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (INT): Der Integer-Wert, der in einen DWORD-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (DWORD): Der resultierende DWORD-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von INT zu DWORD durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `INT_TO_DWORD`, die den Eingabewert `IN` in den Ausgabewert `OUT` umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (SimpleFB) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Datentypen verwenden.
- Integration von Systemen, die INT-Werte erzeugen, aber DWORD-Werte benötigen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_TO_REAL` oder `F_DWORD_TO_INT` ist dieser Funktionsblock spezialisiert auf die Konvertierung von INT zu DWORD.
- Einfacher und direkter als universelle Konvertierungsbausteine, die mehrere Datentypen unterstützen.

## Fazit
Der `F_INT_TO_DWORD` Funktionsblock ist ein effizientes und einfaches Werkzeug für die Konvertierung von Integer- zu Double-Word-Werten. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Datentypkonvertierung erfordern.