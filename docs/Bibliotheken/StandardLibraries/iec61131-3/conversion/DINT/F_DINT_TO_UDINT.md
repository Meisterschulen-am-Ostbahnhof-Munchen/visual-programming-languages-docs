# F_DINT_TO_UDINT

```{index} single: F_DINT_TO_UDINT
```

<img width="1454" height="217" alt="F_DINT_TO_UDINT" src="https://github.com/user-attachments/assets/1f958f49-ab73-4ac0-a2dd-fd1379a3cc6e" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_DINT_TO_UDINT` dient der Konvertierung eines 32-Bit vorzeichenbehafteten Integer-Werts (DINT) in einen 32-Bit vorzeichenlosen Integer-Wert (UDINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende DINT-Wert (32-Bit vorzeichenbehafteter Integer).

### **Daten-Ausgänge**
- **OUT**: Der konvertierte UDINT-Wert (32-Bit vorzeichenloser Integer).

### **Adapter**
Es werden keine Adapter unterstützt.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus des Funktionsblocks ausgeführt. Dabei wird der Wert am Eingang `IN` vom Typ `DINT` in einen `UDINT`-Wert konvertiert und am Ausgang `OUT` ausgegeben. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch die Funktion `DINT_TO_UDINT`.
- Es gibt keine zusätzliche Fehlerbehandlung für Überläufe oder ungültige Werte.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Konvertierung von Sensorwerten, die als vorzeichenbehaftete Integer vorliegen, für Systeme, die vorzeichenlose Werte erwarten.
- Datenaufbereitung für Kommunikationsprotokolle, die vorzeichenlose Integer verwenden.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_UINT**: Konvertiert 16-Bit vorzeichenbehaftete Integer in vorzeichenlose Integer.
- **F_LINT_TO_ULINT**: Konvertiert 64-Bit vorzeichenbehaftete Integer in vorzeichenlose Integer.
- **F_SINT_TO_USINT**: Konvertiert 8-Bit vorzeichenbehaftete Integer in vorzeichenlose Integer.

## Fazit
Der Funktionsblock `F_DINT_TO_UDINT` bietet eine einfache und effiziente Möglichkeit, vorzeichenbehaftete 32-Bit Integer in vorzeichenlose 32-Bit Integer zu konvertieren. Er ist besonders nützlich in Szenarien, wo Daten zwischen Systemen mit unterschiedlichen Datentypanforderungen ausgetauscht werden müssen.