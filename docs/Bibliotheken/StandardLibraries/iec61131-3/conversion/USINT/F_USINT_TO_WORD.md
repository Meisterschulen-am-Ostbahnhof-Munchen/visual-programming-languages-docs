# F_USINT_TO_WORD

```{index} single: F_USINT_TO_WORD
```

<img width="1454" height="214" alt="F_USINT_TO_WORD" src="https://github.com/user-attachments/assets/a587789a-c16b-4b4c-a09f-643a2e300dcf" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_WORD` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen 16-Bit-Wort-Wert (WORD). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten unterschiedlicher Bitbreiten verarbeitet oder übertragen werden müssen.

![F_USINT_TO_WORD](F_USINT_TO_WORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (USINT): Der vorzeichenlose 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (WORD): Der resultierende 16-Bit-Wort-Wert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den USINT-Wert von `IN` nimmt und ihn in einen WORD-Wert umwandelt. Dies geschieht durch direkte Zuweisung unter Verwendung der Funktion `USINT_TO_WORD(IN)`. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und durch `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung ist verlustfrei, da ein USINT (0-255) problemlos in ein WORD (0-65535) umgewandelt werden kann.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung ist rein ereignisgesteuert:
1. Bei Empfang von `REQ` wird die Konvertierung durchgeführt.
2. Nach Abschluss wird `CNF` ausgelöst.

## Anwendungsszenarien
- Datenaufbereitung für Kommunikationsprotokolle, die WORD-Daten erwarten.
- Integration von Sensordaten, die als USINT vorliegen, in Systeme, die WORD verarbeiten.
- Allgemeine Typkonvertierung in Automatisierungsanwendungen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_USINT_TO_WORD` spezialisiert und optimiert für die spezifische Konvertierung von USINT zu WORD.
- Andere Blöcke könnten zusätzliche Funktionen wie Skalierung oder Fehlerbehandlung bieten, sind aber komplexer.

## Fazit
Der `F_USINT_TO_WORD` Funktionsblock ist ein einfacher und effizienter Baustein für die spezifische Konvertierung von USINT zu WORD. Seine Einfachheit und Determinismus machen ihn zu einer zuverlässigen Wahl in Szenarien, die diese Konvertierung erfordern.