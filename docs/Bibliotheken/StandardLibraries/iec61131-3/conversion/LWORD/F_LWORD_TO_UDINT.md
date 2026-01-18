# F_LWORD_TO_UDINT

```{index} single: F_LWORD_TO_UDINT
```

<img width="1466" height="216" alt="F_LWORD_TO_UDINT" src="https://github.com/user-attachments/assets/dc4619b7-62b1-4a3b-b1d5-90a09aeeb2e5" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_LWORD_TO_UDINT` dient der Konvertierung eines `LWORD`-Wertes (64-Bit unsigned integer) in einen `UDINT`-Wert (32-Bit unsigned integer). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten übertragen oder verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- `IN` (LWORD): Der zu konvertierende 64-Bit unsigned integer Wert.

### **Daten-Ausgänge**
- `OUT` (UDINT): Der resultierende 32-Bit unsigned integer Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert von `IN` von `LWORD` in `UDINT` konvertiert und das Ergebnis an `OUT` ausgegeben. Das `CNF`-Ereignis signalisiert die erfolgreiche Beendigung der Konvertierung.

Die Konvertierung erfolgt durch die Funktion `LWORD_TO_UDINT`, welche die unteren 32 Bit des `LWORD`-Wertes als `UDINT` zurückgibt.

## Technische Besonderheiten
- Der Funktionsblock ist für die Verwendung in Echtzeitsystemen geeignet.
- Die Konvertierung ist deterministisch und hat eine konstante Ausführungszeit.
- Bei Werten größer als der maximale `UDINT`-Wert (2^32 - 1) wird der Wert abgeschnitten.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Kommunikation zwischen Systemen mit unterschiedlichen Wortbreiten.
- Verarbeitung von Daten aus externen Quellen, die 64-Bit Werte liefern, aber nur 32-Bit Werte benötigt werden.
- Reduzierung der Speichernutzung bei bekannten kleinen Wertebereichen.

## Vergleich mit ähnlichen Bausteinen
- `F_LWORD_TO_DINT`: Konvertiert in einen 32-Bit signed integer.
- `F_LWORD_TO_UINT`: Konvertiert in einen 16-Bit unsigned integer.
- `F_LWORD_TO_WORD`: Konvertiert in einen 16-Bit Wert ohne Vorzeichen.

## Fazit
Der `F_LWORD_TO_UDINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 64-Bit Werte in 32-Bit Werte zu konvertieren. Er ist besonders nützlich in Systemen, die mit unterschiedlichen Wortbreiten arbeiten müssen.