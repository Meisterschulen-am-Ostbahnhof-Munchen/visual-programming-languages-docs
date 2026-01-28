# F_LWORD_AS_STRING

```{index} single: F_LWORD_AS_STRING
```

<img width="1478" height="214" alt="F_LWORD_AS_STRING" src="https://github.com/user-attachments/assets/29fc831d-b4b3-4e7c-8264-93a698db1ab6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_AS_STRING` dient der Konvertierung eines `LWORD`-Datentyps in einen `STRING`-Datentyp. Dieser Baustein ist besonders nützlich, wenn große binäre Daten (64-Bit) in eine lesbare Zeichenkette umgewandelt werden müssen.

![F_LWORD_AS_STRING](F_LWORD_AS_STRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (LWORD): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (STRING): Das Ergebnis der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis ausgelöst wird. Dabei wird der `LWORD`-Wert am Eingang `IN` in einen `STRING` umgewandelt und am Ausgang `OUT` ausgegeben. Die erfolgreiche Konvertierung wird durch das `CNF`-Ereignis signalisiert.

## Technische Besonderheiten
- Der Funktionsblock verwendet den Standardalgorithmus `LWORD_AS_STRING` zur Konvertierung.
- Der Baustein ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt.
3. **Abschlusszustand**: Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Anwendungsszenarien
- Konvertierung von großen binären Daten in lesbare Zeichenketten.
- Verwendung in Systemen, die mit binären und textuellen Daten arbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu anderen Konvertierungsbausteinen, die möglicherweise andere Datentypen verarbeiten, ist dieser speziell für die Umwandlung von `LWORD` zu `STRING` optimiert.

## Fazit
Der `F_LWORD_AS_STRING`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, große binäre Daten in Zeichenketten umzuwandeln. Seine klare Schnittstellenstruktur und einfache Funktionsweise machen ihn zu einem wertvollen Baustein in der Automatisierungstechnik.