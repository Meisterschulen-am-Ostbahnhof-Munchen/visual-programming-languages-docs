# F_DWORD_TO_REAL

```{index} single: F_DWORD_TO_REAL
```

<img width="1248" height="181" alt="F_DWORD_TO_REAL" src="https://github.com/user-attachments/assets/0ae16249-44e5-4ae0-8d75-1705e8beef34" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_REAL` dient der Konvertierung eines DWORD-Wertes (32-Bit-Ganzzahl ohne Vorzeichen) in einen REAL-Wert (32-Bit-Gleitkommazahl). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang wird aktiviert, sobald die Umwandlung abgeschlossen ist und der Ergebniswert am Daten-Ausgang `OUT` verfügbar ist.

### **Daten-Eingänge**
- **IN**: DWORD-Wert, der in einen REAL-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte REAL-Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert am Eingang `IN` mittels der Funktion `DWORD_TO_REAL` in einen REAL-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Abschließend wird das Ereignis `CNF` aktiviert, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Es werden keine speziellen Fehlerbehandlungen durchgeführt, z.B. bei ungültigen Eingabewerten.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungs-Zustand**: Führt die Umwandlung durch und setzt den Ausgang `OUT`.
3. **Bestätigungs-Zustand**: Aktiviert `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo DWORD-Daten in Gleitkommazahlen umgewandelt werden müssen.
- Integration in größere Funktionsblöcke, die eine Typkonvertierung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_REAL` oder `F_INT_TO_REAL` bieten ähnliche Funktionalitäten, jedoch für andere Eingabetypen.
- `F_DWORD_TO_REAL` ist spezifisch für die Umwandlung von DWORD zu REAL optimiert.

## Fazit
Der `F_DWORD_TO_REAL` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von DWORD- in REAL-Werte. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen.