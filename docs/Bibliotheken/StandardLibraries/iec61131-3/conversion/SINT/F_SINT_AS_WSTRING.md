# F_SINT_AS_WSTRING

```{index} single: F_SINT_AS_WSTRING
```

<img width="1477" height="213" alt="F_SINT_AS_WSTRING" src="https://github.com/user-attachments/assets/ee583877-c052-4a47-bc14-58fe834f43b7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_AS_WSTRING` dient zur Konvertierung eines SINT-Wertes (8-Bit Ganzzahl mit Vorzeichen) in einen WSTRING (Wide-String). Dieser Baustein ist besonders nützlich, wenn numerische Werte in eine für die Anzeige oder Weiterverarbeitung geeignete Textform umgewandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der SINT-Wert (8-Bit Ganzzahl mit Vorzeichen), der in einen WSTRING konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende WSTRING nach der Konvertierung des SINT-Wertes.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des SINT-Wertes (`IN`) in einen WSTRING (`OUT`) durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der integrierten Funktion `SINT_AS_WSTRING`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus zur Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter oder komplexe Logik.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Konvertierung durch und gibt das Ergebnis über `OUT` aus.
3. **Bestätigungszustand**: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textform.
- Weiterverarbeitung von numerischen Werten in Text-basierten Systemen.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_AS_WSTRING**: Konvertiert einen INT-Wert (16-Bit) in einen WSTRING.
- **F_DINT_AS_WSTRING**: Konvertiert einen DINT-Wert (32-Bit) in einen WSTRING.
- **F_LINT_AS_WSTRING**: Konvertiert einen LINT-Wert (64-Bit) in einen WSTRING.

## Fazit
Der `F_SINT_AS_WSTRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, SINT-Werte in WSTRINGs zu konvertieren. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einem nützlichen Baustein in verschiedenen Anwendungen, insbesondere dort, wo numerische Werte in Textform dargestellt oder verarbeitet werden müssen.