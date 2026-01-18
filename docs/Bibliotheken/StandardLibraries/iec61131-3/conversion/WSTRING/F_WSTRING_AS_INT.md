# F_WSTRING_AS_INT

```{index} single: F_WSTRING_AS_INT
```

<img width="1469" height="214" alt="F_WSTRING_AS_INT" src="https://github.com/user-attachments/assets/d83cc0b2-80c5-4d74-8885-958419a9091a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_INT` dient zur Konvertierung eines WSTRING-Wertes in einen INT-Wert. Dieser Block ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder der Interpretation von Textdaten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Dieser Ereigniseingang löst die Ausführung des Funktionsblocks aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ereignisausgang signalisiert die erfolgreiche Ausführung des Funktionsblocks. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Dieser Eingang erwartet einen WSTRING-Wert, der in einen INT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Dieser Ausgang liefert den konvertierten INT-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mithilfe der Funktion `WSTRING_AS_INT`, die den WSTRING-Wert von `IN` in einen INT-Wert umwandelt und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um die erfolgreiche Ausführung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Block ohne interne Zustände oder komplexe Logik.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als Zeichenketten vorliegen, aber als numerische Werte interpretiert werden müssen.
- Interpretation von Textdaten aus externen Quellen, die in numerische Werte umgewandelt werden sollen.
- Integration in Systeme, die Zeichenketten und numerische Werte verarbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsblöcken wie `F_STRING_AS_INT` oder `F_WSTRING_AS_REAL` ist dieser Block speziell auf die Konvertierung von WSTRING zu INT ausgelegt.
- Andere Blöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder Formatierung bieten, dieser Block ist jedoch auf die grundlegende Konvertierung beschränkt.

## Fazit
Der `F_WSTRING_AS_INT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von WSTRING-Werten in INT-Werte. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und unkomplizierte Konvertierung erforderlich ist.
