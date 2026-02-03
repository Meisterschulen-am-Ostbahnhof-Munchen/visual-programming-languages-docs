# F_UINT_TO_BCD_WORD

```{index} single: F_UINT_TO_BCD_WORD
```

<img width="1281" height="185" alt="F_UINT_TO_BCD_WORD" src="https://github.com/user-attachments/assets/8e1d0c92-d549-4131-a8b9-a7bbc0add010" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_BCD_WORD` dient der Konvertierung eines vorzeichenlosen Integer-Werts (UINT) in ein BCD-kodiertes Wort (WORD). BCD (Binary Coded Decimal) ist eine Methode zur Darstellung von Dezimalzahlen, bei der jede Ziffer durch 4 Bits kodiert wird. Dieser Baustein ist besonders nützlich in Anwendungen, bei denen numerische Werte in einem für Menschen lesbaren Format ausgegeben werden müssen, wie z.B. in Anzeigesystemen oder Druckern.

![F_UINT_TO_BCD_WORD](F_UINT_TO_BCD_WORD.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende vorzeichenlose Integer-Wert (UINT).

### **Daten-Ausgänge**
- **OUT**: Das Ergebnis der Konvertierung als BCD-kodiertes Wort (WORD).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` in ein BCD-kodiertes `WORD` umwandelt und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Baustein implementiert eine direkte Konvertierung von UINT zu WORD unter Verwendung der BCD-Kodierung.
- Die Konvertierung erfolgt in einem einzigen Algorithmusschritt, was eine hohe Effizienz gewährleistet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände außer der initialen Bereitschaft zur Verarbeitung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Anzeigesteuerungen, die numerische Werte in BCD-Format benötigen.
- Drucker und andere Ausgabegeräte, die BCD-kodierte Daten verarbeiten.
- Systeme, die eine Kompatibilität mit älteren BCD-basierten Komponenten erfordern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen Konvertierungsbausteinen bietet `F_UINT_TO_BCD_WORD` eine spezialisierte Lösung für die BCD-Kodierung, die effizienter und einfacher in der Handhabung sein kann als universelle Konvertierungsmethoden.

## Fazit
Der `F_UINT_TO_BCD_WORD` Funktionsblock ist ein spezialisiertes Werkzeug für die effiziente Konvertierung von vorzeichenlosen Integer-Werten in das BCD-Format. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige BCD-Kodierung erfordern.