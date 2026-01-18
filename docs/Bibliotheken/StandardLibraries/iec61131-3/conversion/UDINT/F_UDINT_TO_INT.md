# F_UDINT_TO_INT

```{index} single: F_UDINT_TO_INT
```

<img width="1446" height="212" alt="F_UDINT_TO_INT" src="https://github.com/user-attachments/assets/e374f818-7a4c-400e-8da2-7b27a801baf9" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_INT` dient der Konvertierung eines `UDINT`-Wertes (32-Bit vorzeichenlose Ganzzahl) in einen `INT`-Wert (16-Bit vorzeichenbehaftete Ganzzahl). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen oder Komponenten ausgetauscht werden müssen, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN** (`UDINT`): Der Eingabewert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`INT`): Der konvertierte Ausgabewert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `UDINT` zu `INT` durch, wenn das `REQ`-Ereignis empfangen wird. Der Algorithmus nutzt die eingebaute Funktion `UDINT_TO_INT`, um die Konvertierung durchzuführen. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am `OUT`-Ausgang zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung kann zu Datenverlust führen, wenn der `UDINT`-Wert außerhalb des darstellbaren Bereichs von `INT` liegt (d.h., größer als 32767 oder kleiner als -32768).
- Der Funktionsblock ist einfach und hat keine internen Zustände oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Er reagiert ausschließlich auf das `REQ`-Ereignis und führt die Konvertierung unmittelbar durch.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datentypen verwendet werden.
- Integration von Komponenten, die unterschiedliche Datentypen erwarten oder liefern.
- Protokollierung oder Anzeige von Daten, die ursprünglich als `UDINT` gespeichert sind, aber als `INT` dargestellt werden sollen.

## Vergleich mit ähnlichen Bausteinen
- **F_DINT_TO_INT**: Konvertiert `DINT` (32-Bit vorzeichenbehaftet) zu `INT`.
- **F_UDINT_TO_DINT`: Konvertiert `UDINT` zu `DINT` (32-Bit vorzeichenbehaftet), ohne Datenverlust, da der Wertebereich von `DINT` größer ist.
- **F_INT_TO_UDINT**: Führt die umgekehrte Konvertierung durch (`INT` zu `UDINT`).

## Fazit
Der `F_UDINT_TO_INT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `UDINT`- zu `INT`-Werten. Er ist besonders nützlich in Szenarien, wo eine solche Typumwandlung erforderlich ist, jedoch sollte auf möglichen Datenverlust bei großen Werten geachtet werden.