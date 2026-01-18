# F_INT_TO_DINT

```{index} single: F_INT_TO_DINT
```

<img width="1222" height="182" alt="F_INT_TO_DINT" src="https://github.com/user-attachments/assets/0ef12508-b16b-40c8-87b4-378ff5776647" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_DINT` dient zur Konvertierung eines 16-Bit Integer-Werts (`INT`) in einen 32-Bit Integer-Wert (`DINT`). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen oder Komponenten ausgetauscht werden sollen, die unterschiedliche Integer-Formate verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`INT`): Der 16-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`DINT`): Der resultierende 32-Bit Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung durch. Wenn das `REQ`-Ereignis eintrifft, wird der Wert von `IN` nach `OUT` kopiert. Dabei wird der 16-Bit `INT`-Wert automatisch in einen 32-Bit `DINT`-Wert erweitert. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Die Konvertierung ist verlustfrei, da ein `INT`-Wert problemlos in einen `DINT`-Wert umgewandelt werden kann.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Er reagiert ausschließlich auf das `REQ`-Ereignis mit einer sofortigen Konvertierung und der Ausgabe des `CNF`-Ereignisses.

## Anwendungsszenarien
- Datenkommunikation zwischen Systemen, die unterschiedliche Integer-Formate verwenden.
- Erweiterung von Integer-Werten für weitere Berechnungen oder Speicherung.
- Kompatibilität mit Bibliotheken oder Funktionen, die `DINT`-Werte erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_INT_TO_DINT` spezialisiert und optimiert für die Umwandlung von `INT` nach `DINT`.
- Andere Konvertierungsblöcke könnten zusätzliche Funktionen wie Überlaufprüfungen oder Skalierungen bieten, was hier nicht notwendig ist.

## Fazit
Der `F_INT_TO_DINT`-Funktionsblock ist ein einfacher und effizienter Baustein zur verlustfreien Konvertierung von 16-Bit zu 32-Bit Integer-Werten. Er ist besonders nützlich in Szenarien, wo eine Typanpassung ohne zusätzliche Berechnungen erforderlich ist.
