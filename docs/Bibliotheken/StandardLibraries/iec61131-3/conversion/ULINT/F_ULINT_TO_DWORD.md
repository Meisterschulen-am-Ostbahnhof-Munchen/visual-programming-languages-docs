# F_ULINT_TO_DWORD

```{index} single: F_ULINT_TO_DWORD
```

<img width="1465" height="214" alt="F_ULINT_TO_DWORD" src="https://github.com/user-attachments/assets/a6ee56d4-2343-4d88-8833-ac9e66579ade" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_DWORD` dient der Konvertierung eines `ULINT`-Wertes (64-Bit unsigned integer) in einen `DWORD`-Wert (32-Bit unsigned integer). Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache und effiziente Typumwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (`ULINT`): Der 64-Bit unsigned integer Wert, der in einen `DWORD` umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (`DWORD`): Der resultierende 32-Bit unsigned integer Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis empfangen wird. Dabei wird der `ULINT`-Wert am Eingang `IN` in einen `DWORD`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der `ULINT`-Wert größer als der maximale darstellbare Wert eines `DWORD` ist (2³² - 1).
- Der Funktionsblock ist als einfacher FB (`SimpleFB`) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierung**: Führt die Umwandlung durch und gibt das Ergebnis über `OUT` aus.
3. **Bestätigung**: Sendet das `CNF`-Ereignis und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo 64-Bit Werte in 32-Bit Werte konvertiert werden müssen.
- Datenverarbeitung in Systemen mit unterschiedlichen Wortbreiten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_DWORD` oder `F_LINT_TO_DWORD` bieten Konvertierungen zwischen anderen Datentypen, jedoch nicht speziell von `ULINT` zu `DWORD`.
- Im Gegensatz zu generischen Konvertierungsblöcken ist dieser spezialisiert und optimiert für die `ULINT`-zu-`DWORD`-Konvertierung.

## Fazit
Der `F_ULINT_TO_DWORD`-Funktionsblock bietet eine einfache und effiziente Lösung für die Konvertierung von 64-Bit unsigned integers in 32-Bit unsigned integers. Seine klare Schnittstellenstruktur und einfache Funktionsweise machen ihn ideal für Anwendungen, die solche Typumwandlungen erfordern. Beachten Sie jedoch die möglichen Datenverluste bei großen Eingabewerten.