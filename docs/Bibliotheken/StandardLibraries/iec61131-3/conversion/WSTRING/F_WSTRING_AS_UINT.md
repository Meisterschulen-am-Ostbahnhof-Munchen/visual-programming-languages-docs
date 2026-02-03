# F_WSTRING_AS_UINT

```{index} single: F_WSTRING_AS_UINT
```

<img width="1481" height="214" alt="F_WSTRING_AS_UINT" src="https://github.com/user-attachments/assets/4ea92136-06dd-4514-be80-70cc9b719213" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_UINT` dient der Konvertierung eines WSTRING-Wertes in einen UINT-Wert. Diese Funktion ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise für weitere Berechnungen oder Steuerungsaufgaben.

![F_WSTRING_AS_UINT](F_WSTRING_AS_UINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Eingang löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieser Ausgang signalisiert den Abschluss der Konvertierung.

### **Daten-Eingänge**
- **IN**: WSTRING-Wert, der in einen UINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: UINT-Wert, der aus der Konvertierung des WSTRING-Eingangs resultiert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des WSTRING-Eingangs `IN` in einen UINT-Wert `OUT` durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mithilfe der integrierten Funktion `WSTRING_AS_UINT`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (SimpleFB) und führt die Konvertierung in einem einzigen Algorithmus durch.
- Die Konvertierung ist direkt und erfolgt ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine komplexen Zustandsübergänge. Der Block reagiert auf das `REQ`-Ereignis, führt die Konvertierung durch und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben in numerische Werte.
- Verarbeitung von Zeichenketten, die numerische Daten enthalten, für Steuerungszwecke.
- Integration in größere Steuerungssysteme, die sowohl Zeichenketten als auch numerische Werte verarbeiten müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_AS_INT` oder `F_WSTRING_AS_INT` konvertiert dieser Block speziell in einen UINT-Wert, was für nicht-negative Zahlen geeignet ist.
- Die Verwendung von WSTRING ermöglicht die Verarbeitung von Unicode-Zeichenketten, was im Vergleich zu einfachen STRING-Konvertierungen flexibler ist.

## Fazit
Der `F_WSTRING_AS_UINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Werte in UINT-Werte zu konvertieren. Seine direkte Funktionsweise und klare Schnittstelle machen ihn zu einem nützlichen Baustein in Steuerungsanwendungen, die mit Zeichenketten und numerischen Werten arbeiten.