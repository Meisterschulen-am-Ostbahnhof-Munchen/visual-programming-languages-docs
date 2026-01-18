# F_INT_TO_LREAL

```{index} single: F_INT_TO_LREAL
```

<img width="1232" height="182" alt="F_INT_TO_LREAL" src="https://github.com/user-attachments/assets/c99ad1d4-dafe-40fc-9bc4-7515768ec888" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_LREAL` dient der Konvertierung eines ganzzahligen Wertes (INT) in eine 64-Bit Gleitkommazahl (LREAL). Dieser Baustein ist besonders nützlich in Anwendungen, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `INT`, der in einen `LREAL`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `LREAL`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der ganzzahlige Eingangswert `IN` direkt dem Gleitkomma-Ausgangswert `OUT` zugewiesen wird. Die Konvertierung erfolgt automatisch beim Eintreffen eines Ereignisses am `REQ`-Eingang. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Baustein ist für die Verwendung in der 4diac-IDE optimiert und unterstützt die Echtzeitverarbeitung.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf ein `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Typumwandlung durch.
3. **Bestätigungszustand**: Sendet das `CNF`-Ereignis und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, bei denen Gleitkommaoperationen erforderlich sind.
- Integration in größere Steuerungssysteme, die gemischte Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_INT_TO_LREAL` spezialisiert auf die Umwandlung von `INT` zu `LREAL` und daher effizienter in dieser spezifischen Aufgabe.
- Andere Bausteine könnten zusätzliche Funktionen wie Skalierung oder Bereichsprüfung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_INT_TO_LREAL`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von ganzzahligen Werten in Gleitkommazahlen. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Wahl für grundlegende Typumwandlungen in der Automatisierungstechnik.