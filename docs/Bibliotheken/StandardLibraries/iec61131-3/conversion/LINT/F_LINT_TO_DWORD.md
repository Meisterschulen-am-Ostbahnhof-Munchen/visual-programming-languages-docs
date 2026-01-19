# F_LINT_TO_DWORD

```{index} single: F_LINT_TO_DWORD
```

<img width="1450" height="214" alt="F_LINT_TO_DWORD" src="https://github.com/user-attachments/assets/5fa35257-cfd0-4a6b-811f-9a752eec55bc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_DWORD` dient der Konvertierung eines LINT-Wertes (64-Bit Ganzzahl) in einen DWORD-Wert (32-Bit vorzeichenlose Ganzzahl). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `LINT`, der den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `DWORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `LINT`-Wert am Eingang `IN` mittels der Funktion `LINT_TO_DWORD` in einen `DWORD`-Wert umwandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben. Die Konvertierung wird durch das Ereignis `REQ` gestartet und durch `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung schneidet die höherwertigen 32 Bits des `LINT`-Wertes ab, da `DWORD` nur 32 Bits speichern kann.
- Es findet keine Überprüfung auf Überlauf statt, was bei großen `LINT`-Werten zu Datenverlust führen kann.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Sendet das `CNF`-Ereignis und gibt das Ergebnis aus.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Datenreduktion, wenn nur die unteren 32 Bits eines `LINT`-Wertes relevant sind.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_DINT` oder `F_DINT_TO_LINT` führen ähnliche Typumwandlungen durch, jedoch zwischen anderen Datentypen.
- `F_LINT_TO_DWORD` ist spezifisch für die Konvertierung von `LINT` zu `DWORD`.

## Fazit
Der `F_LINT_TO_DWORD` Funktionsblock bietet eine einfache und effiziente Möglichkeit, `LINT`-Werte in `DWORD`-Werte umzuwandeln. Seine Verwendung ist in Szenarien mit Typumwandlungsbedarf zwischen diesen spezifischen Datentypen empfehlenswert, wobei auf mögliche Datenverluste bei großen Werten geachtet werden sollte.