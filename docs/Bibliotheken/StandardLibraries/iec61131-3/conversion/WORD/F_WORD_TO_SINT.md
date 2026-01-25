# F_WORD_TO_SINT

```{index} single: F_WORD_TO_SINT
```

<img width="1442" height="214" alt="F_WORD_TO_SINT" src="https://github.com/user-attachments/assets/4194432e-902f-48f5-a898-c817d09cae5f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_SINT` dient der Konvertierung eines `WORD`-Datentyps in einen `SINT`-Datentyp. Er ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache und effiziente Typumwandlung innerhalb von 4diac-IDE-Anwendungen.

![F_WORD_TO_SINT](F_WORD_TO_SINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`WORD`): Der Eingangswert, der von `WORD` zu `SINT` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`SINT`): Der konvertierte Ausgangswert vom Typ `SINT`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `WORD`-Wert am Eingang `IN` in einen `SINT`-Wert konvertiert und das Ergebnis am Ausgang `OUT` ausgibt. Anschließend wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und führt die Konvertierung in einem einzigen Algorithmusschritt durch.
- Die Konvertierung erfolgt mittels der eingebauten Funktion `WORD_TO_SINT`.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt direkt bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `WORD`-Daten in `SINT`-Daten umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die unterschiedliche Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_SINT` oder `F_DWORD_TO_SINT` bieten Konvertierungen zwischen anderen Datentypen, sind aber in ihrer Funktionsweise vergleichbar.

## Fazit
Der `F_WORD_TO_SINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `WORD`-Daten in `SINT`-Daten umzuwandeln. Durch seine klare Schnittstellenstruktur und direkte Funktionsweise ist er ideal für Anwendungen, die eine schnelle und zuverlässige Typumwandlung erfordern.