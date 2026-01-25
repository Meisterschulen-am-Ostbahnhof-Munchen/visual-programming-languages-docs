# F_STRING_AS_BOOL

```{index} single: F_STRING_AS_BOOL
```

<img width="1462" height="213" alt="F_STRING_AS_BOOL" src="https://github.com/user-attachments/assets/493e97a2-4fe1-488e-b506-d4a41641a727" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_BOOL` dient der Konvertierung eines `STRING`-Werts in einen `BOOL`-Wert. Dieser Baustein ist besonders nützlich, wenn Zeichenketten in boolesche Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder der Interpretation von Textdaten.

![F_STRING_AS_BOOL](F_STRING_AS_BOOL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Eingang löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieser Ausgang signalisiert die erfolgreiche Beendigung der Konvertierung.

### **Daten-Eingänge**
- **IN** (`STRING`): Der Eingabe-String, der in einen booleschen Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`BOOL`): Der resultierende boolesche Wert nach der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt die Funktion `STRING_AS_BOOL`, um den Eingabe-String `IN` in einen booleschen Wert `OUT` umzuwandeln. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst, und nach Abschluss der Operation wird das Ereignis `CNF` ausgegeben.

## Technische Besonderheiten
- Die Konvertierung erfolgt gemäß der IEC 61131-3 Spezifikation für die Umwandlung von Strings in boolesche Werte.
- Der Baustein ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
1. **Initialisierung**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Ausführung**: Bei Empfang von `REQ` wird der String `IN` in einen booleschen Wert konvertiert und das Ergebnis an `OUT` ausgegeben.
3. **Bestätigung**: Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgegeben.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als String vorliegen (z.B. "true" oder "false").
- Interpretation von Textdaten aus externen Quellen (z.B. Konfigurationsdateien oder Netzwerkkommunikation).
- Integration in Systeme, die boolesche Werte als Strings speichern oder übertragen.

## Vergleich mit ähnlichen Bausteinen
- **F_STRING_TO_BOOL**: Ein ähnlicher Baustein, der möglicherweise zusätzliche Optionen für die String-Interpretation bietet.
- **F_STRING_AS_***: Andere Konvertierungsbausteine für verschiedene Datentypen (z.B. `F_STRING_AS_INT`).

## Fazit
Der `F_STRING_AS_BOOL` Funktionsblock bietet eine einfache und effiziente Möglichkeit, String-Werte in boolesche Werte umzuwandeln. Durch seine klare Schnittstellenstruktur und Zuverlässigkeit ist er ideal für Anwendungen, die eine solche Konvertierung erfordern.