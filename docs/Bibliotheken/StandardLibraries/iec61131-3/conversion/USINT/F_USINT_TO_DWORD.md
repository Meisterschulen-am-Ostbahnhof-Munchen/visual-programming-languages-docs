# F_USINT_TO_DWORD

```{index} single: F_USINT_TO_DWORD
```

<img width="1464" height="214" alt="F_USINT_TO_DWORD" src="https://github.com/user-attachments/assets/b8d67a72-e0b2-46fb-ac98-031aa3054888" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_DWORD` dient der Konvertierung eines `USINT`-Wertes (8-Bit unsigned integer) in einen `DWORD`-Wert (32-Bit unsigned integer). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht oder verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- `IN` (USINT): Der Eingangswert, der konvertiert werden soll. Der Datentyp ist `USINT` (8-Bit unsigned integer).

### **Daten-Ausgänge**
- `OUT` (DWORD): Der konvertierte Ausgangswert. Der Datentyp ist `DWORD` (32-Bit unsigned integer).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `USINT` nach `DWORD` durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus `REQ` nutzt die Funktion `USINT_TO_DWORD`, um den Eingabewert `IN` in den Ausgabewert `OUT` umzuwandeln. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus.
- Die Konvertierung erfolgt ohne Datenverlust, da der `DWORD`-Datentyp einen größeren Wertebereich als `USINT` abdeckt.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Führt die Konvertierung durch.
3. **Bestätigungszustand**: Löst das Ereignis `CNF` aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Wortbreiten verwenden.
- Integration von Peripheriegeräten, die Daten in unterschiedlichen Formaten liefern.
- Datenverarbeitung in industriellen Automatisierungslösungen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_BYTE_TO_DWORD` oder `F_WORD_TO_DWORD` bieten Konvertierungen zwischen anderen Datentypen an.
- `F_USINT_TO_DWORD` ist spezialisiert auf die Konvertierung von 8-Bit unsigned integer zu 32-Bit unsigned integer.

## Fazit
Der Funktionsblock `F_USINT_TO_DWORD` ist ein einfaches und effizientes Werkzeug zur Konvertierung von `USINT`-Werten in `DWORD`-Werte. Seine klare Schnittstellenstruktur und einfache Funktionsweise machen ihn zu einer zuverlässigen Lösung für Datenkonvertierungsaufgaben in industriellen Automatisierungssystemen.