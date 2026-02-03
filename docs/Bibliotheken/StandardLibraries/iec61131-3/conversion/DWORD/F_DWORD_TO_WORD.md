# F_DWORD_TO_WORD

```{index} single: F_DWORD_TO_WORD
```

<img width="1244" height="182" alt="F_DWORD_TO_WORD" src="https://github.com/user-attachments/assets/eeb53dda-9cf9-4235-91ac-ad7b17de8da7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_WORD` dient der Konvertierung eines 32-Bit-DWORD-Wertes in einen 16-Bit-WORD-Wert. Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht werden müssen oder wenn Speicherplatz optimiert werden soll.

![F_DWORD_TO_WORD](F_DWORD_TO_WORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (DWORD): Der 32-Bit-Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (WORD): Der konvertierte 16-Bit-Ausgangswert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den DWORD-Wert am Eingang `IN` in einen WORD-Wert konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch Abschneiden der höherwertigen 16 Bit des DWORD-Wertes.
- Es findet keine Überprüfung auf möglichen Datenverlust durch diese Konvertierung statt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Kommunikation zwischen Systemen mit unterschiedlichen Wortbreiten
- Speicheroptimierung in eingebetteten Systemen
- Datenvorverarbeitung in Steuerungssystemen

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_DWORD_TO_BYTE` konvertiert dieser Baustein in einen WORD-Wert statt in ein BYTE.
- Ähnlich wie `F_WORD_TO_BYTE`, aber mit anderen Datentypen.

## Fazit
Der `F_DWORD_TO_WORD` Funktionsblock bietet eine einfache und effiziente Möglichkeit, DWORD-Werte in WORD-Werte zu konvertieren. Er ist besonders nützlich in Systemen, die mit verschiedenen Wortbreiten arbeiten müssen. Beachten Sie jedoch den möglichen Datenverlust bei der Konvertierung.