# F_WSTRING_AS_DWORD

```{index} single: F_WSTRING_AS_DWORD
```

<img width="1490" height="214" alt="F_WSTRING_AS_DWORD" src="https://github.com/user-attachments/assets/0a7a9611-fec8-4a92-8bfd-ea8b545785de" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_DWORD` dient zur Konvertierung eines WSTRING-Wertes in einen DWORD-Wert. Diese Funktionalität ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise für die weitere Verarbeitung in Steuerungsalgorithmen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingabe vom Typ WSTRING. Die Zeichenkette, die in einen DWORD-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgabe vom Typ DWORD. Der konvertierte numerische Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WSTRING_AS_DWORD`, die den WSTRING-Eingabewert in einen DWORD-Wert umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (SimpleFB) und verfügt über einen einzigen Algorithmus, der bei Auslösung von `REQ` ausgeführt wird.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben (z.B. über HMI) in numerische Werte für die Steuerung.
- Verarbeitung von Zeichenketten, die numerische Informationen enthalten, in Steuerungsalgorithmen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_AS_DWORD` ist dieser speziell für WSTRING-Eingaben ausgelegt.
- Ähnliche Bausteine könnten zusätzliche Parameter oder Fehlerbehandlung bieten, dieser Funktionsblock ist jedoch auf die grundlegende Konvertierung beschränkt.

## Fazit
Der `F_WSTRING_AS_DWORD` Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Werte in DWORD-Werte umzuwandeln. Seine Einfachheit macht ihn besonders geeignet für Anwendungen, bei denen eine direkte Konvertierung ohne zusätzliche Komplexität erforderlich ist.
