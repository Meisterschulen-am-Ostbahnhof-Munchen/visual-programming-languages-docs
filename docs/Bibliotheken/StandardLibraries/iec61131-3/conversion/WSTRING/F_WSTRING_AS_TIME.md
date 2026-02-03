# F_WSTRING_AS_TIME

```{index} single: F_WSTRING_AS_TIME
```

<img width="1481" height="214" alt="F_WSTRING_AS_TIME" src="https://github.com/user-attachments/assets/508ad921-2d01-48fe-b8ef-0c57d37b7f10" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_TIME` dient zur Konvertierung einer Zeichenkette im WSTRING-Format in einen TIME-Wert. Dieser Baustein ist besonders nützlich, wenn Zeitwerte als Zeichenketten vorliegen und in das TIME-Format umgewandelt werden müssen, um sie in weiteren Berechnungen oder Steuerungslogiken verwenden zu können.

![F_WSTRING_AS_TIME](F_WSTRING_AS_TIME.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Ereigniseingang ausgelöst, wird der im Daten-Eingang `IN` enthaltene WSTRING-Wert in einen TIME-Wert umgewandelt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten TIME-Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (WSTRING): Die Zeichenkette, die in einen TIME-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (TIME): Der konvertierte TIME-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der im Daten-Eingang `IN` enthaltene WSTRING-Wert mithilfe der Funktion `WSTRING_AS_TIME` in einen TIME-Wert konvertiert. Das Ergebnis wird am Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Beendigung der Konvertierung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus, der die Konvertierung durchführt.
- Es gibt keine zusätzlichen Zustände oder komplexe Logiken, da die Konvertierung direkt und ohne Zwischenschritte erfolgt.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine expliziten Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Datenkonvertierung**: Wenn Zeitwerte als Zeichenketten vorliegen (z.B. aus einer Benutzereingabe oder einer externen Datenquelle) und in das TIME-Format umgewandelt werden müssen.
- **Schnittstellenkommunikation**: Bei der Kommunikation mit Systemen, die Zeitwerte als Zeichenketten übermitteln.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_TIME**: Ähnlicher Funktionsblock, der jedoch mit STRING anstelle von WSTRING arbeitet. `F_WSTRING_AS_TIME` ist für Unicode-Zeichenketten geeignet.
- **F_TIME_AS_WSTRING**: Führt die umgekehrte Konvertierung durch (TIME zu WSTRING).

## Fazit
Der Funktionsblock `F_WSTRING_AS_TIME` ist ein einfaches und effektives Werkzeug zur Konvertierung von WSTRING-Zeichenketten in TIME-Werte. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für entsprechende Anwendungsfälle.