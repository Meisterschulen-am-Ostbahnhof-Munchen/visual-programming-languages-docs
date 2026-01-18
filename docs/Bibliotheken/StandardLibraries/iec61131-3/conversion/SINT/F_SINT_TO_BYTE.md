# F_SINT_TO_BYTE

```{index} single: F_SINT_TO_BYTE
```

<img width="1439" height="213" alt="F_SINT_TO_BYTE" src="https://github.com/user-attachments/assets/af182d96-472c-4593-8202-182a67b19c5a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_BYTE` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (SINT) in einen vorzeichenlosen 8-Bit-Integer-Wert (BYTE). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Darstellungen für 8-Bit-Werte verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN** (SINT): Der vorzeichenbehaftete 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (BYTE): Der vorzeichenlose 8-Bit-Integer-Wert, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert am Eingang `IN` vom Typ SINT in einen BYTE-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Das Ereignis `CNF` signalisiert die erfolgreiche Beendigung der Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch die Funktion `SINT_TO_BYTE`.
- Der Block ist einfach und deterministisch, ohne interne Zustände oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach Auslösen von `REQ`, gefolgt von der Ausgabe des Ergebnisses und der Bestätigung durch `CNF`.

## Anwendungsszenarien
- Kommunikation zwischen Systemen, die vorzeichenbehaftete und vorzeichenlose 8-Bit-Werte verwenden.
- Datenverarbeitung in Steuerungssystemen, wo eine Typumwandlung erforderlich ist.
- Integration in größere Funktionsblocknetzwerke, die unterschiedliche Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_SINT_TO_BYTE` spezialisiert auf die Umwandlung von SINT zu BYTE und daher effizienter für diesen spezifischen Anwendungsfall.
- Andere Blöcke wie `F_INT_TO_BYTE` oder `F_DINT_TO_BYTE` sind für größere Integer-Typen ausgelegt.

## Fazit
Der `F_SINT_TO_BYTE` Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung zwischen vorzeichenbehafteten und vorzeichenlosen 8-Bit-Integern. Seine Einfachheit und Determinismus machen ihn zuverlässig für Anwendungen, die solche Typumwandlungen erfordern.
