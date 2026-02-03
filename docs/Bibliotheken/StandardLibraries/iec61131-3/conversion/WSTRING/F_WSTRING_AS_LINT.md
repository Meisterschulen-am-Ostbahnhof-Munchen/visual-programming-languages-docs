# F_WSTRING_AS_LINT

```{index} single: F_WSTRING_AS_LINT
```

<img width="1480" height="214" alt="F_WSTRING_AS_LINT" src="https://github.com/user-attachments/assets/a8ed434d-17fa-45f9-8839-16517ab7d6b0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_LINT` dient der Konvertierung eines WSTRING-Wertes in einen LINT-Wert. Dieser Baustein ist besonders nützlich in Szenarien, wo Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder der Interpretation von Textdaten.

![F_WSTRING_AS_LINT](F_WSTRING_AS_LINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Ereigniseingang löst die Konvertierung aus. Er ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieses Ereignis wird nach erfolgreicher Konvertierung ausgegeben und ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (WSTRING): Der Eingang für die Zeichenkette, die in einen LINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (LINT): Der Ausgang für den konvertierten LINT-Wert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock konvertiert den WSTRING-Wert am Eingang `IN` in einen LINT-Wert am Ausgang `OUT`, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mithilfe der Funktion `WSTRING_AS_LINT`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgegeben.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus zur Konvertierung.
- Die Konvertierung kann fehlschlagen, wenn die Zeichenkette keine gültige numerische Repräsentation enthält. In diesem Fall wird das Ereignis `CNF` nicht ausgegeben.

## Zustandsübersicht
1. **Idle**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Processing**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt.
3. **Confirmation**: Nach erfolgreicher Konvertierung wird `CNF` ausgegeben, und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als Zeichenketten vorliegen, aber als numerische Werte interpretiert werden sollen.
- Interpretation von Textdaten aus externen Quellen, die numerische Informationen enthalten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_LINT**: Ähnlicher Funktionsblock, aber für den Datentyp STRING statt WSTRING.
- **F_WSTRING_AS_INT**: Konvertiert WSTRING in INT, bietet jedoch eine geringere Wertebereich als LINT.

## Fazit
Der Funktionsblock `F_WSTRING_AS_LINT` ist ein einfaches und effektives Werkzeug zur Konvertierung von Zeichenketten in große numerische Werte. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einer zuverlässigen Lösung für entsprechende Anwendungsfälle.