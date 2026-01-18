# F_UDINT_TO_USINT

```{index} single: F_UDINT_TO_USINT
```

<img width="1470" height="216" alt="F_UDINT_TO_USINT" src="https://github.com/user-attachments/assets/1e0f089e-de96-4e75-91cb-739ff8cf6842" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_USINT` dient der Konvertierung eines 32-Bit unsigned integer Wertes (UDINT) in einen 8-Bit unsigned integer Wert (USINT). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen unterschiedlich großen numerischen Werten erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen 32-Bit unsigned integer Wert (UDINT), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten 8-Bit unsigned integer Wert (USINT).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Der Algorithmus wandelt den Wert von `IN` (UDINT) in den entsprechenden `OUT` (USINT) Wert um. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die eingebaute Funktion `UDINT_TO_USINT`.
- Es wird keine Bereichsprüfung durchgeführt. Bei Werten außerhalb des USINT-Bereichs (0 bis 255) kann es zu unerwarteten Ergebnissen kommen.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ` Ereignis neu durchgeführt.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo Speicherplatz optimiert werden muss.
- Kommunikation zwischen Systemen, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_UDINT_TO_USINT` spezialisiert und daher effizienter in der Ausführung.
- Andere Bausteine könnten zusätzliche Funktionalitäten wie Bereichsprüfungen bieten, was hier nicht der Fall ist.

## Fazit
Der `F_UDINT_TO_USINT` Funktionsblock ist ein einfacher und effizienter Baustein für die spezifische Konvertierung von UDINT zu USINT Werten. Er eignet sich besonders für Anwendungen, wo eine schnelle und direkte Typumwandlung benötigt wird.