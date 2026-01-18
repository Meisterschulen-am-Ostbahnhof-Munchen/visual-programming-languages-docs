# F_SINT_TO_REAL

```{index} single: F_SINT_TO_REAL
```

<img width="1439" height="213" alt="F_SINT_TO_REAL" src="https://github.com/user-attachments/assets/9477ea11-2b6e-441e-8fe2-16588d70cf27" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_REAL` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (`SINT`) in einen Fließkommawert (`REAL`). Diese Konvertierung ist insbesondere in Steuerungsanwendungen nützlich, wo unterschiedliche Datentypen verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`SINT`): Der vorzeichenbehaftete 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`REAL`): Der resultierende Fließkommawert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung durch. Bei Eintreffen eines Ereignisses am Eingang `REQ` wird der Wert von `IN` in den Datentyp `REAL` konvertiert und an `OUT` ausgegeben. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- **Einfache Konvertierung**: Die Umwandlung erfolgt ohne zusätzliche Berechnungen oder Skalierungen.
- **Keine Fehlerbehandlung**: Es gibt keine spezielle Behandlung von Überlauf- oder Unterlaufbedingungen.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Messwertverarbeitung**: Umwandlung von Sensordaten, die als `SINT` vorliegen, in `REAL` für weitere Berechnungen.
- **Steuerungsalgorithmen**: Integration in Regelkreise, wo Fließkommawerte benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_REAL**: Konvertiert einen 16-Bit-Integer (`INT`) in `REAL`.
- **F_DINT_TO_REAL**: Konvertiert einen 32-Bit-Integer (`DINT`) in `REAL`.
- **F_SINT_TO_REAL** ist spezifisch für 8-Bit-Integer und bietet damit eine schlankere Lösung für diesen Datentyp.

## Fazit
Der `F_SINT_TO_REAL`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 8-Bit-Integer-Werten in Fließkommazahlen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und unkomplizierte Typumwandlung erfordern.
