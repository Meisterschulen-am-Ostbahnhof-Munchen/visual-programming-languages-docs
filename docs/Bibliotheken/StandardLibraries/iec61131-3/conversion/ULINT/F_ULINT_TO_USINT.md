# F_ULINT_TO_USINT

```{index} single: F_ULINT_TO_USINT
```

<img width="1462" height="214" alt="F_ULINT_TO_USINT" src="https://github.com/user-attachments/assets/317d59b5-d0e5-42d1-9ad1-3b37c6c9f91d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_USINT` dient der Konvertierung eines 64-Bit unsigned integer Wertes (`ULINT`) in einen 8-Bit unsigned integer Wert (`USINT`). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_ULINT_TO_USINT](F_ULINT_TO_USINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Verbunden mit dem Daten-Eingang `IN`.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Verbunden mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `ULINT` (64-Bit unsigned integer), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `USINT` (8-Bit unsigned integer), der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` vom Typ `ULINT` in den Typ `USINT` konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um die erfolgreiche Beendigung der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung schneidet den Wert von `ULINT` auf die Größe von `USINT` zu. Es ist wichtig sicherzustellen, dass der Eingangswert innerhalb des Bereichs von `USINT` (0 bis 255) liegt, um unerwartete Ergebnisse zu vermeiden.
- Der Algorithmus ist in Structured Text (ST) implementiert.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Zustandsautomaten:
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch und löst `CNF` aus.

## Anwendungsszenarien
- Typumwandlung in Steuerungssystemen, wo Daten in unterschiedlichen Formaten vorliegen.
- Reduzierung der Speichergröße von Daten, wenn nur kleine Wertebereiche benötigt werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_INT` oder `F_LREAL_TO_REAL` führen ähnliche Typumwandlungen durch, jedoch für andere Datentypen.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_ULINT_TO_USINT` spezialisiert und optimiert für die Konvertierung zwischen `ULINT` und `USINT`.

## Fazit
Der `F_ULINT_TO_USINT` Funktionsblock bietet eine effiziente und einfache Möglichkeit, Werte von `ULINT` nach `USINT` zu konvertieren. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einem nützlichen Baustein in der IEC 61131-Programmierung.