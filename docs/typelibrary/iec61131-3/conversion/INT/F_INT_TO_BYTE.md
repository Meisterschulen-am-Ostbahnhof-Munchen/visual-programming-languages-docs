# F_INT_TO_BYTE

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_BYTE` dient zur Konvertierung eines Integer-Werts (`INT`) in einen Byte-Wert (`BYTE`). Er ist Teil des Pakets `iec61131::conversion` und bietet eine einfache und effiziente Möglichkeit, Datentypen innerhalb von IEC 61499-Systemen umzuwandeln.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Integer-Wert (`INT`), der in einen Byte-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende Byte-Wert (`BYTE`) nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Empfang eines Ereignisses am Eingang `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` von `INT` zu `BYTE` konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

Der Algorithmus ist wie folgt definiert:
```ST
ALGORITHM REQ
OUT := INT_TO_BYTE(IN);
END_ALGORITHM
```

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient implementiert, ohne zusätzliche Zustände oder komplexe Logik.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine expliziten Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typkonvertierung in Steuerungsanwendungen, wo Integer-Werte in Byte-Werte umgewandelt werden müssen.
- Integration in größere Systeme, die eine strenge Typenkontrolle erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_BYTE` oder `F_WORD_TO_BYTE` bieten Konvertierungen zwischen anderen Datentypen, sind aber für unterschiedliche Quelltypen ausgelegt.
- `F_INT_TO_BYTE` ist spezifisch für die Konvertierung von `INT` zu `BYTE` optimiert.

## Fazit
Der Funktionsblock `F_INT_TO_BYTE` ist ein nützliches Werkzeug für die Typkonvertierung in IEC 61499-basierten Systemen. Seine einfache und effiziente Implementierung macht ihn ideal für Anwendungen, die schnelle und zuverlässige Konvertierungen erfordern.