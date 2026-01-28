# F_WORD_AS_STRING

```{index} single: F_WORD_AS_STRING
```

<img width="1466" height="214" alt="F_WORD_AS_STRING" src="https://github.com/user-attachments/assets/d08aada6-dc95-4b9f-9089-6933a20a8560" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_AS_STRING` dient der Konvertierung eines `WORD`-Datentyps in einen `STRING`. Dies ist besonders nützlich, wenn numerische Werte in einer für Menschen lesbaren Form ausgegeben oder weiterverarbeitet werden sollen.

![F_WORD_AS_STRING](F_WORD_AS_STRING.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Auslösung dieses Ereignisses wird der Wert des Daten-Eingangs `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Erwartet einen Eingabewert vom Typ `WORD`, der in einen `STRING` umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Wert als `STRING` aus.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt den Algorithmus `REQ`, um den `WORD`-Wert am Eingang `IN` in einen `STRING` umzuwandeln. Die Konvertierung erfolgt durch die Funktion `WORD_AS_STRING(IN)`. Nach erfolgreicher Umwandlung wird das Ereignis `CNF` ausgelöst und der konvertierte Wert am Ausgang `OUT` bereitgestellt.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und benötigt keine zusätzlichen Parameter oder komplexe Logik.
- Die Konvertierung erfolgt direkt und ohne Zwischenschritte.

## Zustandsübersicht
1. **Initialisierung**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Verarbeitung**: Bei Empfang von `REQ` wird der Wert von `IN` konvertiert.
3. **Abschluss**: Nach der Konvertierung wird `CNF` ausgelöst und der Wert an `OUT` ausgegeben.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von `WORD`-Werten in lesbarer Form.
- Weiterverarbeitung von numerischen Werten in Systemen, die `STRING`-Daten erwarten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_WORD_AS_STRING` spezialisiert auf die Umwandlung von `WORD` zu `STRING` und daher effizienter für diesen spezifischen Anwendungsfall.
- Andere Blöcke könnten zusätzliche Parameter oder komplexere Logik beinhalten, was hier nicht notwendig ist.

## Fazit
Der `F_WORD_AS_STRING`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `WORD`-Werten in `STRING`. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und unkomplizierte Umwandlung benötigt wird.