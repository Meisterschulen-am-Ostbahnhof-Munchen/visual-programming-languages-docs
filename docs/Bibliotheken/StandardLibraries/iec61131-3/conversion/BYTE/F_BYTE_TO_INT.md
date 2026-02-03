# F_BYTE_TO_INT

```{index} single: F_BYTE_TO_INT
```

<img width="1421" height="210" alt="F_BYTE_TO_INT" src="https://github.com/user-attachments/assets/776dfcd4-d0f2-4a7f-9ef6-b4d4a2df49d0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_INT` dient der Konvertierung eines `BYTE`-Wertes in einen `INT`-Wert. Er ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache und effiziente Typumwandlung zwischen diesen beiden Datentypen.

![F_BYTE_TO_INT](F_BYTE_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `BYTE`, der den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `INT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BYTE` zu `INT` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der integrierten Funktion `BYTE_TO_INT`. Nach erfolgreicher Umwandlung wird das Ergebnis über den Ausgang `OUT` ausgegeben und das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher FB ohne interne Zustandsverwaltung.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder komplexe Zustandslogik.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `BYTE`-Werte in `INT`-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die unterschiedliche Datentypen verarbeiten müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_INT` oder `F_DWORD_TO_INT` bieten Konvertierungen für andere Datentypen, jedoch mit demselben Grundprinzip.
- Im Gegensatz zu komplexeren Konvertierungsblöcken bietet `F_BYTE_TO_INT` eine einfache und direkte Lösung für die spezifische Umwandlung von `BYTE` zu `INT`.

## Fazit
Der `F_BYTE_TO_INT`-Funktionsblock ist ein effizientes und einfach zu verwendendes Werkzeug für die Konvertierung von `BYTE`- in `INT`-Werte. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, die schnelle und zuverlässige Typumwandlungen erfordern.