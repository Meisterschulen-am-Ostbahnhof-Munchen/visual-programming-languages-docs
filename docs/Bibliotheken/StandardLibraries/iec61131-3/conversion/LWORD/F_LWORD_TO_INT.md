# F_LWORD_TO_INT

```{index} single: F_LWORD_TO_INT
```

<img width="1434" height="211" alt="F_LWORD_TO_INT" src="https://github.com/user-attachments/assets/1edfb2cc-ce64-4ed3-9668-580b531f4b11" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_INT` dient der Konvertierung eines `LWORD`-Wertes (64-Bit unsigned integer) in einen `INT`-Wert (16-Bit signed integer). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht oder verarbeitet werden müssen.

![F_LWORD_TO_INT](F_LWORD_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `LWORD` (64-Bit unsigned integer), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `INT` (16-Bit signed integer), der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der `LWORD`-Wert am Eingang `IN` in einen `INT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben wird. Die Konvertierung erfolgt bei einem Ereignis am Eingang `REQ` und wird durch ein Ereignis am Ausgang `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung von einem 64-Bit-Wert in einen 16-Bit-Wert kann zu einem Datenverlust führen, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs von `INT` liegt.
- Der Funktionsblock ist als einfacher Funktionsblock (`SimpleFB`) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei einem Ereignis am Eingang `REQ`.

## Anwendungsszenarien
- Konvertierung von 64-Bit-Datenwerten für Systeme, die nur 16-Bit-Daten verarbeiten können.
- Datenreduktion, wenn nur der untere 16-Bit-Teil eines 64-Bit-Werts relevant ist.

## Vergleich mit ähnlichen Bausteinen
- `F_DWORD_TO_INT`: Konvertiert einen 32-Bit-Wert in einen 16-Bit-Wert.
- `F_LWORD_TO_DINT`: Konvertiert einen 64-Bit-Wert in einen 32-Bit-Wert.
- `F_LWORD_TO_SINT`: Konvertiert einen 64-Bit-Wert in einen 8-Bit-Wert.

## Fazit
Der Funktionsblock `F_LWORD_TO_INT` bietet eine einfache und effiziente Möglichkeit, 64-Bit-Datenwerte in 16-Bit-Datenwerte zu konvertieren. Bei der Verwendung ist jedoch auf den möglichen Datenverlust zu achten, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs von `INT` liegt.