# F_USINT_TO_UINT

```{index} single: F_USINT_TO_UINT
```

<img width="1453" height="214" alt="F_USINT_TO_UINT" src="https://github.com/user-attachments/assets/50a399dd-73aa-4f6f-aff9-6b747efe0874" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_UINT` dient der Konvertierung eines `USINT`-Wertes (Unsigned Short Integer) in einen `UINT`-Wert (Unsigned Integer). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung ohne Datenverlust erforderlich ist.

![F_USINT_TO_UINT](F_USINT_TO_UINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `USINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `UINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingangswertes `IN` vom Typ `USINT` zum Ausgangswert `OUT` vom Typ `UINT` durch. Da `USINT` einen kleineren Wertebereich als `UINT` hat, erfolgt die Konvertierung ohne Datenverlust.

Der Algorithmus wird durch das Ereignis `REQ` ausgelöst und gibt das Ergebnis über das Ereignis `CNF` aus.

## Technische Besonderheiten
- Der Funktionsblock ist in der Programmiersprache ST (Structured Text) implementiert.
- Die Konvertierung erfolgt ohne zusätzliche Berechnungen oder Prüfungen, da `USINT` automatisch in `UINT` umgewandelt werden kann.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `USINT`-Werte in `UINT` umgewandelt werden müssen.
- Verwendung in Datenverarbeitungsketten, wo verschiedene Datentypen kompatibel gemacht werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_TO_REAL` oder `F_BOOL_TO_STRING` ist dieser Baustein spezifisch für die Umwandlung zwischen zwei vorzeichenlosen Ganzzahltypen.
- Ähnliche Bausteine könnten zusätzliche Prüfungen oder Skalierungen durchführen, was hier nicht notwendig ist.

## Fazit
Der `F_USINT_TO_UINT`-Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von `USINT` nach `UINT`. Er eignet sich ideal für Anwendungen, bei denen eine schnelle und verlustfreie Typumwandlung erforderlich ist.