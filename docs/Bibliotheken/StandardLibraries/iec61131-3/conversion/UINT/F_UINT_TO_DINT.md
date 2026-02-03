# F_UINT_TO_DINT

```{index} single: F_UINT_TO_DINT
```

<img width="1438" height="216" alt="F_UINT_TO_DINT" src="https://github.com/user-attachments/assets/ace89eda-70cf-4dc2-bcac-b1e3365ef7df" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_DINT` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (UINT) in einen vorzeichenbehafteten 32-Bit-Integer-Wert (DINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

![F_UINT_TO_DINT](F_UINT_TO_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `UINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `DINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Empfang eines Ereignisses am Eingang `REQ` wird der Wert von `IN` gelesen und direkt in den Datentyp `DINT` konvertiert. Das Ergebnis wird an `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock führt eine direkte Typumwandlung durch, ohne zusätzliche Berechnungen oder Skalierungen.
- Die Konvertierung ist verlustfrei, da der `DINT`-Typ einen größeren Wertebereich als `UINT` abdeckt.

## Zustandsübersicht
1. **Idle**: Wartet auf ein Ereignis am Eingang `REQ`.
2. **Converting**: Führt die Konvertierung durch und gibt das Ergebnis aus.
3. **Completed**: Signalisiert den Abschluss der Konvertierung mit dem Ereignis `CNF`.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Datentypen verwenden.
- Integration von Sensordaten, die als `UINT` vorliegen, in Systeme, die `DINT` erwarten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_UINT_TO_DINT` spezialisiert und effizient für die Konvertierung von `UINT` zu `DINT`.
- Andere Blöcke könnten zusätzliche Funktionen wie Skalierung oder Bereichsprüfung bieten, was hier nicht erforderlich ist.

## Fazit
Der `F_UINT_TO_DINT`-Funktionsblock ist ein einfacher und effizienter Baustein für die direkte Konvertierung von `UINT` zu `DINT`. Er ist besonders nützlich in Szenarien, wo eine verlustfreie Typumwandlung benötigt wird.