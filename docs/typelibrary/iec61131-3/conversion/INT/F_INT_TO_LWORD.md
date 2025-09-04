# F_INT_TO_LWORD

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_LWORD` dient der Konvertierung eines Integer-Werts (`INT`) in einen 64-Bit langen vorzeichenlosen Integer-Wert (`LWORD`). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Löst die Ausführung des Funktionsblocks aus. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (`INT`): Der Eingangswert, der in einen `LWORD`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`LWORD`): Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt bei einem eingehenden `REQ`-Ereignis die Konvertierung des `INT`-Werts am Eingang `IN` in einen `LWORD`-Wert durch. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Ausführung.

Der Algorithmus ist wie folgt definiert:
```ST
ALGORITHM REQ
OUT := INT_TO_LWORD(IN);
END_ALGORITHM
```

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient, da er direkt die eingebaute `INT_TO_LWORD`-Funktion nutzt.
- Keine zusätzlichen Zustände oder komplexe Logik erforderlich.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `INT`-Werte in `LWORD`-Werte konvertiert werden müssen.
- Integration in größere Systeme, die unterschiedliche Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_LWORD` oder `F_SINT_TO_LWORD` bieten Konvertierungen von anderen Integer-Typen zu `LWORD`.
- `F_INT_TO_LWORD` ist spezifisch für die Konvertierung von `INT` zu `LWORD` optimiert.

## Fazit
Der `F_INT_TO_LWORD`-Funktionsblock bietet eine einfache und effiziente Lösung für die Konvertierung von `INT`- zu `LWORD`-Werten. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für den Einsatz in Steuerungsanwendungen.