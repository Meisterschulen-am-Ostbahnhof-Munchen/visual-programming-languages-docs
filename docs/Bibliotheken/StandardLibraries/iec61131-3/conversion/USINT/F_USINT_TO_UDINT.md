# F_USINT_TO_UDINT

```{index} single: F_USINT_TO_UDINT
```

<img width="1464" height="214" alt="F_USINT_TO_UDINT" src="https://github.com/user-attachments/assets/270403b0-17c3-4974-9d94-16d82c7ec576" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_UDINT` dient der Konvertierung eines `USINT`-Wertes (8-Bit unsigned integer) in einen `UDINT`-Wert (32-Bit unsigned integer). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung ohne Datenverlust erforderlich ist.

![F_USINT_TO_UDINT](F_USINT_TO_UDINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (`USINT`): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`UDINT`): Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingangswertes `IN` vom Typ `USINT` zum Ausgangswert `OUT` vom Typ `UDINT` durch. Da `UDINT` einen größeren Wertebereich als `USINT` abdeckt, erfolgt die Konvertierung ohne Datenverlust.

## Technische Besonderheiten
- **Algorithmus**: Der Algorithmus `REQ` führt die Zuweisung `OUT := IN` aus.
- **Datenintegrität**: Durch die Konvertierung in einen größeren Datentyp bleibt der ursprüngliche Wert erhalten.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Typumwandlung**: In Steuerungssystemen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- **Datenverarbeitung**: Bei der Kommunikation zwischen Komponenten, die unterschiedliche Datentypen verwenden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_USINT_TO_INT**: Konvertiert `USINT` zu `INT`, jedoch mit potenziellem Vorzeichenwechsel.
- **F_USINT_TO_UINT**: Konvertiert `USINT` zu `UINT` (16-Bit), was einen kleineren Wertebereich als `UDINT` bietet.




## 🛠️ Zugehörige Übungen

* [Uebung_111](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_111.md)

## Fazit
Der `F_USINT_TO_UDINT`-Funktionsblock ist ein einfacher und effizienter Baustein zur sicheren Konvertierung von `USINT` nach `UDINT`. Durch seine direkte Zuweisung und den größeren Wertebereich des Ausgangstyps ist er ideal für Anwendungen, bei denen Datenintegrität gewährleistet sein muss.