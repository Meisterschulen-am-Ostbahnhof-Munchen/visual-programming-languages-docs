# F_STRING_AS_SINT

```{index} single: F_STRING_AS_SINT
```

<img width="1467" height="213" alt="F_STRING_AS_SINT" src="https://github.com/user-attachments/assets/13cacff9-d6b7-49e3-93b4-b4ca9c36ab3b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_SINT` dient der Konvertierung eines `STRING`-Wertes in einen `SINT`-Wert (8-Bit Ganzzahl mit Vorzeichen). Dieser Baustein ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, z.B. bei der Verarbeitung von Benutzereingaben oder der Interpretation von Textdaten.

![F_STRING_AS_SINT](F_STRING_AS_SINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Löst die Ausführung der Konvertierung aus. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (`STRING`): Die Zeichenkette, die in eine `SINT`-Zahl umgewandelt werden soll.

### **Daten-Ausgänge**
- `OUT` (`SINT`): Das Ergebnis der Konvertierung als 8-Bit Ganzzahl mit Vorzeichen.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird die Funktion `STRING_AS_SINT` auf den Wert des `IN`-Eingangs angewendet. Das Ergebnis wird im `OUT`-Ausgang gespeichert und das `CNF`-Ereignis signalisiert den erfolgreichen Abschluss der Operation.

## Technische Besonderheiten
- Die Konvertierung erfolgt gemäß der IEC 61131-3 Spezifikation für die Umwandlung von Zeichenketten in numerische Werte.
- Der Baustein ist Teil des `iec61131::conversion`-Pakets.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Signalisiert den Abschluss mit `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Interpretation von Benutzereingaben in numerische Steuerbefehle.
- Verarbeitung von Textdaten aus externen Quellen (z.B. Dateien oder Netzwerkkommunikation).
- Konvertierung von Konfigurationswerten in Steuerungsparameter.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_STRING_AS_SINT` spezialisiert auf die Umwandlung in 8-Bit Ganzzahlen.
- Ähnliche Blöcke wie `F_STRING_AS_INT` oder `F_STRING_AS_DINT` bieten Konvertierungen in größere Ganzzahltypen.

## Fazit
`F_STRING_AS_SINT` ist ein effizienter und spezialisierter Funktionsblock für die Konvertierung von Zeichenketten in 8-Bit Ganzzahlen. Seine einfache Schnittstelle und klare Funktionsweise machen ihn ideal für Steuerungsanwendungen, die mit textbasierten Eingaben arbeiten.