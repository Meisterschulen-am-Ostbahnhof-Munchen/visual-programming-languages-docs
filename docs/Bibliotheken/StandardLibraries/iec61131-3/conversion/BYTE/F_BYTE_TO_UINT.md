# F_BYTE_TO_UINT

```{index} single: F_BYTE_TO_UINT
```

<img width="1436" height="212" alt="F_BYTE_TO_UINT" src="https://github.com/user-attachments/assets/8cb462ae-eb4e-4fd2-8556-33ab2b4fa9f3" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_UINT` dient der Konvertierung eines `BYTE`-Wertes in einen `UINT`-Wert. Dies ist besonders nützlich, wenn Daten unterschiedlicher Typen in einem System verarbeitet werden müssen und eine Typumwandlung erforderlich ist.

![F_BYTE_TO_UINT](F_BYTE_TO_UINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `BYTE`, der in einen `UINT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `UINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des `BYTE`-Wertes am Eingang `IN` in einen `UINT`-Wert durch, sobald das Ereignis `REQ` ausgelöst wird. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus, der die Konvertierung durchführt.
- Die Konvertierung erfolgt mittels der Funktion `BYTE_TO_UINT`, die den `BYTE`-Wert in einen `UINT`-Wert umwandelt.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungs- und Automatisierungssystemen.
- Datenverarbeitung in Systemen, die unterschiedliche Datentypen verwenden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_UINT` oder `F_DWORD_TO_UINT` führen ähnliche Konvertierungen durch, jedoch mit anderen Eingangstypen.
- `F_BYTE_TO_UINT` ist spezialisiert auf die Konvertierung von `BYTE` zu `UINT` und daher effizienter für diesen spezifischen Anwendungsfall.




## 🛠️ Zugehörige Übungen

* [Uebung_006c](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006c.md)

## Fazit
Der Funktionsblock `F_BYTE_TO_UINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von `BYTE`-Werten in `UINT`-Werte. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen solche Typumwandlungen erforderlich sind.