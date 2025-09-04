# F_UDINT_TO_SINT

* * * * * * * * * *

## Einleitung
Der Funktionsblock `F_UDINT_TO_SINT` dient der Konvertierung eines 32-Bit vorzeichenlosen Integer-Werts (UDINT) in einen 8-Bit vorzeichenbehafteten Integer-Wert (SINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen oder Komponenten ausgetauscht werden müssen, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (UDINT): Der vorzeichenlose 32-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (SINT): Der resultierende vorzeichenbehaftete 8-Bit Integer-Wert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den Wert von `IN` (UDINT) in einen SINT-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und deterministisch, da er nur eine direkte Typumwandlung durchführt.
- Es gibt keine zusätzliche Logik oder Fehlerbehandlung für Werte, die außerhalb des darstellbaren Bereichs von SINT liegen.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datentypen verwendet werden.
- Schnittstellen zwischen Systemen, die unterschiedliche Integer-Formate erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_SINT` oder `F_INT_TO_SINT` führen ähnliche Konvertierungen durch, jedoch mit anderen Ausgangs- oder Eingangsdatentypen.
- `F_UDINT_TO_SINT` ist spezifisch für die Konvertierung von UDINT zu SINT.

## Fazit
Der `F_UDINT_TO_SINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von vorzeichenlosen 32-Bit Integern in vorzeichenbehaftete 8-Bit Integer. Er ist besonders nützlich in Szenarien, wo solche Typumwandlungen regelmäßig benötigt werden.