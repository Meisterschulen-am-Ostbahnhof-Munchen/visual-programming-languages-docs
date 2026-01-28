# F_BYTE_TO_USINT

```{index} single: F_BYTE_TO_USINT
```

<img width="1244" height="181" alt="F_BYTE_TO_USINT" src="https://github.com/user-attachments/assets/a6df83fd-735f-4694-b3c4-f581d43eac55" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_USINT` dient der Konvertierung eines `BYTE`-Wertes in einen `USINT`-Wert (Unsigned Short Integer). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist, z.B. bei der Kommunikation zwischen verschiedenen Systemen oder bei der Datenverarbeitung.

![F_BYTE_TO_USINT](F_BYTE_TO_USINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `BYTE`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `USINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `BYTE`-Wert am Eingang `IN` in einen `USINT`-Wert umwandelt und das Ergebnis am Ausgang `OUT` bereitstellt. Die Konvertierung erfolgt synchron mit dem Auslösen des `REQ`-Ereignisses und wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Funktionsblock verwendet die eingebaute Funktion `BYTE_TO_USINT` zur Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsmaschine oder komplexe Logik.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -verwaltung. Die Operation ist atomar und wird bei jedem `REQ`-Ereignis ausgeführt.

## Anwendungsszenarien
- Typumwandlung in Kommunikationsprotokollen, wo verschiedene Systeme unterschiedliche Datentypen verwenden.
- Datenverarbeitung in Steuerungssystemen, wo eine Konvertierung zwischen `BYTE` und `USINT` erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_UINT` oder `F_DWORD_TO_UDINT` führen ähnliche Konvertierungen durch, jedoch mit anderen Datentypen.
- `F_BYTE_TO_USINT` ist spezifisch für die Konvertierung von `BYTE` zu `USINT` optimiert und daher effizienter für diesen Anwendungsfall.

## Fazit
Der `F_BYTE_TO_USINT` Funktionsblock ist ein einfacher, aber effektiver Baustein für die Konvertierung zwischen `BYTE` und `USINT`. Seine Einfachheit und Effizienz machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Typumwandlung erfordern.