# F_REAL_TO_LREAL

```{index} single: F_REAL_TO_LREAL
```

<img width="1451" height="213" alt="F_REAL_TO_LREAL" src="https://github.com/user-attachments/assets/d9c98d4f-9da0-484e-ac3d-998cf8b14b3a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_LREAL` dient der Konvertierung eines REAL-Wertes in einen LREAL-Wert. Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache Typumwandlung zwischen den beiden numerischen Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingangswert vom Typ `REAL`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgangswert vom Typ `LREAL`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt bei Empfang des Ereignisses `REQ` die Konvertierung des REAL-Wertes `IN` in einen LREAL-Wert durch und weist das Ergebnis dem Ausgang `OUT` zu. Anschließend wird das Ereignis `CNF` ausgelöst, um die erfolgreiche Ausführung zu bestätigen.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Baustein ohne interne Zustände oder komplexe Logik.
- Die Konvertierung erfolgt direkt durch Zuweisung, da `LREAL` eine höhere Genauigkeit als `REAL` bietet und somit alle Werte ohne Verlust darstellen kann.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -verwaltung. Die Ausführung erfolgt atomar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo höhere Genauigkeit erforderlich ist.
- Integration in bestehende Systeme, die unterschiedliche Datentypen verwenden.
- Verwendung in mathematischen Berechnungen, die eine höhere Präzision erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_INT_TO_REAL` oder `F_DINT_TO_LINT` führen ebenfalls Typumwandlungen durch, jedoch zwischen anderen Datentypen.
- Im Gegensatz zu komplexen Konvertierungsbausteinen bietet `F_REAL_TO_LREAL` eine einfache und direkte Umwandlung ohne zusätzliche Parameter oder Logik.

## Fazit
Der `F_REAL_TO_LREAL`-Funktionsblock ist ein nützliches Werkzeug für die einfache und effiziente Konvertierung von REAL- zu LREAL-Werten. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle Typumwandlung ohne zusätzliche Komplexität erfordern.
