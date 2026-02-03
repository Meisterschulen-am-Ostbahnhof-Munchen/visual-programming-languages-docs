# F_UINT_TO_INT

```{index} single: F_UINT_TO_INT
```

<img width="1421" height="216" alt="F_UINT_TO_INT" src="https://github.com/user-attachments/assets/52abb253-fd81-47d4-a4b4-ecb1fdf90656" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_INT` dient der Konvertierung eines vorzeichenlosen Integer-Werts (UINT) in einen vorzeichenbehafteten Integer-Wert (INT). Diese Funktionalität ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Integer-Formate verwenden.

![F_UINT_TO_INT](F_UINT_TO_INT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, liest der Funktionsblock den Wert am Daten-Eingang `IN` und führt die Konvertierung durch.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Gleichzeitig wird der konvertierte Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Hier wird der vorzeichenlose Integer-Wert (UINT) angelegt, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten vorzeichenbehafteten Integer-Wert (INT) aus.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus des Funktionsblocks aktiviert. Dieser liest den Wert am Eingang `IN`, konvertiert ihn von UINT nach INT und legt das Ergebnis am Ausgang `OUT` ab. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

Die Konvertierung erfolgt mittels der eingebauten Funktion `UINT_TO_INT()`.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus.
- Es werden keine zusätzlichen Bibliotheken oder Adapter benötigt.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem Auslösen von `REQ` neu durchgeführt.

## Anwendungsszenarien
- Datenkonvertierung zwischen Systemen, die unterschiedliche Integer-Formate verwenden.
- Vorverarbeitung von Sensordaten, die als UINT geliefert werden, aber als INT weiterverarbeitet werden sollen.
- Kompatibilitätsherstellung zwischen verschiedenen Protokollen oder Schnittstellen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_UINT_TO_INT` spezialisiert und daher effizienter.
- Ähnliche Blöcke wie `F_INT_TO_UINT` führen die umgekehrte Konvertierung durch.
- Universalblöcke wie `F_ANY_TO_ANY` bieten mehr Flexibilität, sind aber unter Umständen weniger performant.

## Fazit
Der `F_UINT_TO_INT` Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung zwischen vorzeichenlosen und vorzeichenbehafteten Integer-Werten. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für entsprechende Anwendungsfälle.