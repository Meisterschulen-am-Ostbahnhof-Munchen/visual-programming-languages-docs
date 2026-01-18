# F_SINT_TO_UDINT

```{index} single: F_SINT_TO_UDINT
```

<img width="1450" height="213" alt="F_SINT_TO_UDINT" src="https://github.com/user-attachments/assets/a5b8dca8-4533-4578-b402-729f15415b91" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_SINT_TO_UDINT` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (SINT) in einen vorzeichenlosen 32-Bit-Integer-Wert (UDINT). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `SINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `UDINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `SINT`-Wert am Eingang `IN` in einen `UDINT`-Wert umwandelt und das Ergebnis am Ausgang `OUT` bereitstellt. Die Konvertierung wird durch ein Ereignis am Eingang `REQ` ausgelöst und durch ein Ereignis am Ausgang `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `SINT_TO_UDINT`.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf ein Ereignis am Eingang `REQ`.
2. **Aktiv-Zustand**: Führt die Konvertierung durch und signalisiert den Abschluss mit einem Ereignis am Ausgang `CNF`.

## Anwendungsszenarien
- Konvertierung von Sensorwerten, die als `SINT` vorliegen, in einen `UDINT`-Wert für weitere Verarbeitung.
- Datenaufbereitung für Systeme, die vorzeichenlose Integer-Werte erwarten.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_UDINT**: Konvertiert einen vorzeichenbehafteten 16-Bit-Integer (`INT`) in einen vorzeichenlosen 32-Bit-Integer (`UDINT`).
- **F_DINT_TO_UDINT**: Konvertiert einen vorzeichenbehafteten 32-Bit-Integer (`DINT`) in einen vorzeichenlosen 32-Bit-Integer (`UDINT`).

## Fazit
Der Funktionsblock `F_SINT_TO_UDINT` bietet eine einfache und effiziente Möglichkeit, `SINT`-Werte in `UDINT`-Werte umzuwandeln. Durch seine klare Schnittstellenstruktur und einfache Funktionsweise ist er ideal für Anwendungen, die eine solche Konvertierung erfordern.