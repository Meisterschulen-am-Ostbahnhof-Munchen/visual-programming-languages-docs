# F_WSTRING_AS_BOOL

```{index} single: F_WSTRING_AS_BOOL
```

<img width="1480" height="214" alt="image" src="https://github.com/user-attachments/assets/fba2dd5d-7fa7-4291-b6c5-c59d389db81c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_BOOL` dient der Konvertierung eines WSTRING-Wertes in einen BOOL-Wert. Dies ist besonders in Szenarien nützlich, in denen Zeichenketten in boolesche Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder der Interpretation von Konfigurationsdaten.

![F_WSTRING_AS_BOOL](F_WSTRING_AS_BOOL.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: WSTRING. Der Eingabewert, der in einen BOOL-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: BOOL. Der Ergebniswert der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WSTRING_AS_BOOL`, die den WSTRING-Eingabewert `IN` in einen BOOL-Wert `OUT` umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Funktionsblock ist als einfacher Funktionsblock (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Löst das Ereignis `CNF` aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als Zeichenketten vorliegen.
- Interpretation von Konfigurationsdateien, die boolesche Werte als Zeichenketten speichern.
- Schnittstellen zwischen Systemen, die unterschiedliche Datentypen verwenden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_BOOL**: Konvertiert STRING statt WSTRING in BOOL.
- **F_BOOL_AS_WSTRING**: Führt die umgekehrte Konvertierung durch (BOOL zu WSTRING).

## Fazit
Der `F_WSTRING_AS_BOOL` Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Werte in BOOL-Werte umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem nützlichen Werkzeug in verschiedenen Anwendungsszenarien.