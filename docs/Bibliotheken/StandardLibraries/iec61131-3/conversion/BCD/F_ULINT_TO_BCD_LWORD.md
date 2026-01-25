# F_ULINT_TO_BCD_LWORD

```{index} single: F_ULINT_TO_BCD_LWORD
```

<img width="1302" height="181" alt="F_ULINT_TO_BCD_LWORD" src="https://github.com/user-attachments/assets/e52c2e4c-a8aa-4dc5-bb01-ce013aadd734" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_BCD_LWORD` dient der Konvertierung eines `ULINT`-Wertes (64-Bit unsigned integer) in einen `LWORD`-Wertyp im BCD-Format (Binary Coded Decimal). Dieser Block ist besonders nützlich in Anwendungen, bei denen numerische Werte in ein für BCD-Systeme kompatibles Format umgewandelt werden müssen.

![F_ULINT_TO_BCD_LWORD](F_ULINT_TO_BCD_LWORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der zu konvertierende Wert wird über den Daten-Eingang `IN` übergeben.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert wird über den Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der Eingang für den `ULINT`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten `LWORD`-Wertyp im BCD-Format.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `ULINT` zu `LWORD` im BCD-Format durch, sobald das `REQ`-Ereignis ausgelöst wird. Die Konvertierung erfolgt über die integrierte Funktion `ULINT_TO_BCD_LWORD`. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am `OUT`-Ausgang zur Verfügung.

## Technische Besonderheiten
- Unterstützt die Konvertierung von 64-Bit unsigned integer (`ULINT`) zu 64-Bit BCD (`LWORD`).
- Keine zusätzlichen Parameter oder Einstellungen erforderlich.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierung**: Führt die Konvertierung durch, sobald `REQ` aktiviert wird.
3. **Abschluss**: Sendet das `CNF`-Ereignis und gibt den konvertierten Wert aus.

## Anwendungsszenarien
- Industrielle Steuerungssysteme, die BCD-kodierte Daten verarbeiten.
- Kommunikation mit Peripheriegeräten, die BCD-Daten erwarten.
- Datenkonvertierung in Automatisierungsanwendungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken bietet `F_ULINT_TO_BCD_LWORD` eine spezialisierte Lösung für die Umwandlung in das BCD-Format.
- Andere Blöcke könnten zusätzliche Konvertierungsoptionen bieten, sind jedoch möglicherweise weniger effizient für diesen spezifischen Anwendungsfall.

## Fazit
Der `F_ULINT_TO_BCD_LWORD`-Funktionsblock ist eine effiziente und spezialisierte Lösung für die Konvertierung von `ULINT` zu `LWORD` im BCD-Format. Seine einfache Handhabung und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Datenumwandlung erfordern.