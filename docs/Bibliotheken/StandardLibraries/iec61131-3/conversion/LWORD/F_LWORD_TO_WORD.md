# F_LWORD_TO_WORD

```{index} single: F_LWORD_TO_WORD
```

<img width="1454" height="214" alt="F_LWORD_TO_WORD" src="https://github.com/user-attachments/assets/eeb29887-0982-497c-bd0d-0bac534c0573" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_WORD` dient der Konvertierung eines 64-Bit-Wertes (LWORD) in einen 16-Bit-Wert (WORD). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht oder verarbeitet werden müssen.

![F_LWORD_TO_WORD](F_LWORD_TO_WORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Signalisiert den Beginn der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: LWORD (64-Bit) – Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: WORD (16-Bit) – Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von einem 64-Bit-Wert (LWORD) zu einem 16-Bit-Wert (WORD) durch. Bei der Konvertierung werden die unteren 16 Bit des Eingangswertes übernommen, während die oberen 48 Bit verworfen werden. Die Konvertierung erfolgt synchron zum `REQ`-Ereignis, und das Ergebnis wird mit dem `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne Rundung oder Skalierung, da es sich um eine direkte Bit-Übernahme handelt.
- Es findet keine Überprüfung auf möglichen Datenverlust durch die Verkürzung der Wortbreite statt. Der Anwender muss sicherstellen, dass der Eingangswert im zulässigen Bereich liegt.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Kommunikation zwischen Systemen mit unterschiedlicher Wortbreite.
- Verarbeitung von Daten, die aus 64-Bit-Quellen stammen, aber in 16-Bit-Systemen weiterverwendet werden sollen.
- Reduktion der Datenbreite zur Speicherplatzoptimierung, wenn die höherwertigen Bits nicht benötigt werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_LWORD_TO_DWORD**: Konvertiert LWORD zu DWORD (32-Bit), behält mehr Datenbits bei.
- **F_LWORD_TO_BYTE**: Konvertiert LWORD zu BYTE (8-Bit), reduziert die Datenbreite noch stärker.
- **F_LWORD_TO_<any>**: Ähnliche Bausteine für andere Ziel-Datentypen, jeweils mit unterschiedlicher Bit-Breite im Ergebnis.

## Fazit
Der `F_LWORD_TO_WORD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, 64-Bit-Daten auf 16-Bit-Daten zu reduzieren. Er ist besonders nützlich in heterogenen Systemumgebungen, in denen Daten zwischen Komponenten mit unterschiedlicher Wortbreite ausgetauscht werden müssen. Aufgrund der fehlenden Überprüfung auf Datenverlust sollte der Anwender jedoch sicherstellen, dass die Konvertierung sinnvoll und sicher ist.