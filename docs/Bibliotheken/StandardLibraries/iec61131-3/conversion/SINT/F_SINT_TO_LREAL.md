# F_SINT_TO_LREAL

```{index} single: F_SINT_TO_LREAL
```

<img width="1448" height="213" alt="F_SINT_TO_LREAL" src="https://github.com/user-attachments/assets/68877ca6-0d50-4534-9301-8bdead3b94f2" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_LREAL` dient der Konvertierung eines ganzzahligen Wertes vom Typ `SINT` (8-Bit Ganzzahl) in einen Fließkommawert vom Typ `LREAL` (64-Bit Fließkomma). Dieser Baustein ist besonders nützlich in Anwendungen, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingang für den zu konvertierenden `SINT`-Wert.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten `LREAL`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung durch. Bei Eintreffen eines `REQ`-Ereignisses wird der Wert von `IN` gelesen, in den Typ `LREAL` konvertiert und an `OUT` ausgegeben. Anschließend wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Skalierung oder Rundung.
- Der Baustein ist einfach und effizient implementiert, da er nur eine Zuweisung benötigt.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Er reagiert ausschließlich auf das `REQ`-Ereignis mit einer sofortigen Konvertierung und Ausgabe.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `SINT`-Werte in Berechnungen mit `LREAL`-Werten verwendet werden müssen.
- Datenaufbereitung für Visualisierung oder Protokollierung, wo höhere Genauigkeit erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_INT_TO_REAL` oder `F_DINT_TO_LREAL` bieten Konvertierungen zwischen anderen Datentypen, aber nicht spezifisch von `SINT` zu `LREAL`.
- Dieser Baustein ist spezialisiert auf die Konvertierung von 8-Bit Ganzzahlen zu 64-Bit Fließkommazahlen.

## Fazit
Der `F_SINT_TO_LREAL`-Funktionsblock ist ein einfaches und effizientes Werkzeug für die Typumwandlung in 4diac-IDE. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen.