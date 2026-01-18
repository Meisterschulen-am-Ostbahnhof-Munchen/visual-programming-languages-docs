# F_ULINT_TO_WORD

```{index} single: F_ULINT_TO_WORD
```

<img width="1448" height="214" alt="F_ULINT_TO_WORD" src="https://github.com/user-attachments/assets/8be2ddee-0d88-4c60-98ec-e97dc61f329c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_WORD` dient der Konvertierung eines 64-Bit unsigned integer Wertes (ULINT) in einen 16-Bit unsigned integer Wert (WORD). Der Block ist Teil des `iec61131::conversion` Pakets und implementiert eine einfache Typumwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: ULINT (64-Bit unsigned integer) - Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: WORD (16-Bit unsigned integer) - Das Ergebnis der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von ULINT zu WORD durch, wenn das `REQ`-Ereignis eintrifft. Die Konvertierung erfolgt mittels der eingebauten Funktion `ULINT_TO_WORD`. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Block unterstützt keine Fehlerbehandlung bei Überlauf (da ULINT einen größeren Wertebereich als WORD hat).
- Die Konvertierung ist direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Block hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo ULINT-Werte in WORD-Werte umgewandelt werden müssen.
- Datenreduktion, wenn nur die unteren 16 Bit eines ULINT-Wertes relevant sind.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Blöcke wie `F_DINT_TO_WORD` oder `F_LINT_TO_WORD` bieten Konvertierungen von anderen Integer-Typen zu WORD, jedoch mit unterschiedlichen Wertebereichen und Genauigkeiten.

## Fazit
Der `F_ULINT_TO_WORD` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von ULINT zu WORD Werten. Er ist besonders nützlich in Szenarien, wo eine Reduktion der Datenbreite erforderlich ist. Beachten Sie jedoch die möglichen Datenverluste bei der Konvertierung von größeren zu kleineren Datentypen.
