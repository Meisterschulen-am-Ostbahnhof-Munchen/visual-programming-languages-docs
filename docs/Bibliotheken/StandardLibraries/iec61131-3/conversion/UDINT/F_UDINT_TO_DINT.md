# F_UDINT_TO_DINT

```{index} single: F_UDINT_TO_DINT
```

<img width="1454" height="212" alt="F_UDINT_TO_DINT" src="https://github.com/user-attachments/assets/c47b354a-12d3-401a-b4b6-b6e8f6493ba0" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_DINT` dient der Konvertierung eines vorzeichenlosen 32-Bit-Integer-Werts (UDINT) in einen vorzeichenbehafteten 32-Bit-Integer-Wert (DINT). Diese Konvertierung ist in Szenarien nützlich, in denen Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (UDINT): Der vorzeichenlose 32-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (DINT): Der resultierende vorzeichenbehaftete 32-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den Wert des Eingangs `IN` vom Typ `UDINT` in den Typ `DINT` umwandelt. Die Konvertierung erfolgt synchron bei Auslösung des Ereignisses `REQ`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verarbeitung.
- Der Funktionsblock ist für den Einsatz in Echtzeitsystemen geeignet.
- Die Implementierung erfolgt in Structured Text (ST).

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Führt die Konvertierung durch, wenn `REQ` ausgelöst wird.
3. **Bestätigungszustand**: Löst `CNF` aus, sobald die Konvertierung abgeschlossen ist.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen.
- Schnittstellen zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Echtzeit-Datenverarbeitung, bei der Typkonvertierungen erforderlich sind.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_UDINT_TO_DINT` spezialisiert auf die Konvertierung zwischen `UDINT` und `DINT`.
- Andere Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Fehlerbehandlung bieten, was hier nicht der Fall ist.

## Fazit
Der Funktionsblock `F_UDINT_TO_DINT` ist ein einfacher und effizienter Baustein für die Konvertierung zwischen vorzeichenlosen und vorzeichenbehafteten 32-Bit-Integern. Er ist besonders in Szenarien nützlich, in denen eine schnelle und direkte Typumwandlung erforderlich ist.