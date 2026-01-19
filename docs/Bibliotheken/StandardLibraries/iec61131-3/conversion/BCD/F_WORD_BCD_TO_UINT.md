# F_WORD_BCD_TO_UINT

```{index} single: F_WORD_BCD_TO_UINT
```

<img width="1281" height="182" alt="F_WORD_BCD_TO_UINT" src="https://github.com/user-attachments/assets/37d8f223-a93a-45ff-8ae6-a51b72d499a3" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_BCD_TO_UINT` dient der Konvertierung eines BCD-codierten WORD-Wertes in einen vorzeichenlosen Integer (UINT). Dies ist besonders nützlich in Anwendungen, bei denen Daten im BCD-Format verarbeitet oder angezeigt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- `IN` (WORD): Der BCD-codierte Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (UINT): Der konvertierte vorzeichenlose Integer-Wert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der BCD-codierte Wert am Eingang `IN` in einen vorzeichenlosen Integer-Wert konvertiert. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert den Abschluss der Konvertierung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und direkt, ohne komplexe Zustandslogik.
- Die Konvertierung erfolgt mittels der Funktion `WORD_BCD_TO_UINT`.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine komplexen Zustände. Der Block reagiert direkt auf das `REQ`-Ereignis mit einer Konvertierung und der Ausgabe des Ergebnisses.

## Anwendungsszenarien
- Konvertierung von BCD-codierten Daten aus externen Geräten oder Sensoren.
- Verwendung in Steuerungssystemen, die BCD-Daten verarbeiten müssen.
- Anzeige von BCD-Daten in einem für Menschen lesbaren Format.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_WORD_BCD_TO_UINT` spezialisiert auf die Konvertierung von BCD zu UINT.
- Andere Blöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder verschiedene Codierungsformate unterstützen, sind dafür aber komplexer.

## Fazit
Der `F_WORD_BCD_TO_UINT` Funktionsblock ist ein effizientes Werkzeug für die spezifische Aufgabe der BCD-zu-UINT-Konvertierung. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen schnelle und zuverlässige Konvertierungen benötigt werden.