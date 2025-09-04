# F_UINT_TO_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_ULINT` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (`UINT`) in einen vorzeichenlosen 64-Bit-Integer-Wert (`ULINT`). Diese Konvertierung ist insbesondere dann notwendig, wenn Werte zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `UINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `ULINT`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Konvertierung des Eingangswerts `IN` vom Typ `UINT` in den Ausgangswert `OUT` vom Typ `ULINT` durch. Die Konvertierung erfolgt ohne Änderung des numerischen Werts, lediglich der Datentyp wird erweitert.

## Technische Besonderheiten
- Die Konvertierung ist verlustfrei, da der `ULINT`-Typ einen größeren Wertebereich als `UINT` abdeckt.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Integration von Systemen mit unterschiedlicher Wortbreite
- Datenverarbeitung in Steuerungen, die sowohl 16-Bit- als auch 64-Bit-Daten verarbeiten müssen
- Erweiterung von Daten für nachfolgende Berechnungen, die höhere Präzision erfordern

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_INT_TO_LINT` werden hier vorzeichenlose Datentypen verarbeitet
- Ähnliche Konvertierungsbausteine existieren für andere Datentypkombinationen (z.B. `F_BYTE_TO_WORD`)

## Fazit
Der `F_UINT_TO_ULINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 16-Bit vorzeichenlose Integer in 64-Bit vorzeichenlose Integer umzuwandeln. Seine einfache Struktur und deterministische Funktionsweise machen ihn zu einem zuverlässigen Baustein für Systeme mit gemischten Wortbreiten.