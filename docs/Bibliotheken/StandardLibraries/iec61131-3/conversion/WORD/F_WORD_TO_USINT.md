# F_WORD_TO_USINT

```{index} single: F_WORD_TO_USINT
```

<img width="1455" height="214" alt="F_WORD_TO_USINT" src="https://github.com/user-attachments/assets/d4f29908-e033-443c-b917-5bb34d0d6283" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_USINT` dient der Konvertierung eines `WORD`-Datentyps in einen `USINT`-Datentyp. Er ist Teil des Pakets `iec61131::conversion` und eignet sich für Anwendungen, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_WORD_TO_USINT](F_WORD_TO_USINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ` (Event): Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Event): Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (WORD): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (USINT): Der konvertierte Ausgangswert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `WORD` zu `USINT` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WORD_TO_USINT`, die den Eingangswert `IN` in den Ausgangswert `OUT` umwandelt. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (SimpleFB) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo ein `WORD`-Wert in einen `USINT`-Wert umgewandelt werden muss.
- Integration in größere Steuerungssysteme, die unterschiedliche Datentypen verarbeiten müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_TO_REAL` oder `F_BOOL_TO_STRING` ist `F_WORD_TO_USINT` spezialisiert auf die Umwandlung von `WORD` zu `USINT`.
- Ähnliche Bausteine könnten `F_USINT_TO_WORD` sein, welcher die umgekehrte Konvertierung durchführt.

## Fazit
Der Funktionsblock `F_WORD_TO_USINT` bietet eine einfache und effiziente Möglichkeit, `WORD`-Werte in `USINT`-Werte umzuwandeln. Durch seine klare Schnittstellenstruktur und einfache Funktionsweise eignet er sich ideal für Anwendungen, die eine solche Typumwandlung erfordern.