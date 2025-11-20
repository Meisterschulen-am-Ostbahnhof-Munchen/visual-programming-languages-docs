# F_SINT_TO_DWORD

<img width="1450" height="213" alt="F_SINT_TO_DWORD" src="https://github.com/user-attachments/assets/10f7168f-01f0-46a7-9a2e-ca0c754a294b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_DWORD` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (SINT) in einen vorzeichenlosen 32-Bit-Integer-Wert (DWORD). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `SINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `DWORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den `SINT`-Wert am Eingang `IN` in einen `DWORD`-Wert um und legt das Ergebnis am Ausgang `OUT` ab. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch die Funktion `SINT_TO_DWORD(IN)`.
- Der Baustein ist als einfacher Funktionsblock (SimpleFB) implementiert, was eine schnelle und effiziente Ausführung ermöglicht.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Konvertierung durch und setzt den Ausgang `OUT`.
3. **Bestätigungszustand**: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `SINT`-Werte in `DWORD`-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die unterschiedliche Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_DINT` oder `F_BYTE_TO_WORD` bieten Konvertierungen zwischen anderen Datentypen, jedoch nicht speziell zwischen `SINT` und `DWORD`.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_SINT_TO_DWORD` spezialisiert und daher effizienter für diesen spezifischen Anwendungsfall.

## Fazit
Der `F_SINT_TO_DWORD`-Funktionsblock ist ein spezialisiertes und effizientes Werkzeug zur Konvertierung von `SINT`- in `DWORD`-Werte. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Typumwandlung erfordern.
