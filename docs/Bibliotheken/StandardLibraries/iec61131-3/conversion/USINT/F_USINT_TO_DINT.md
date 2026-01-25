# F_USINT_TO_DINT

```{index} single: F_USINT_TO_DINT
```

<img width="1454" height="214" alt="F_USINT_TO_DINT" src="https://github.com/user-attachments/assets/94cb99ea-b608-4a9b-b390-02601460c14b" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock `F_USINT_TO_DINT` dient der Konvertierung eines `USINT`-Wertes (8-Bit unsigned integer) in einen `DINT`-Werte (32-Bit signed integer). Diese Konvertierung ist nützlich, wenn Werte zwischen verschiedenen Datentypen umgewandelt werden müssen, insbesondere wenn eine Erweiterung der Bitbreite erforderlich ist.

![F_USINT_TO_DINT](F_USINT_TO_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Auslösung dieses Ereignisses wird der Wert von `IN` in `OUT` umgewandelt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem aktualisierten Wert von `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (`USINT`): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`DINT`): Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingangswertes `IN` (vom Typ `USINT`) an den Ausgang `OUT` (vom Typ `DINT`) durch. Da `DINT` eine größere Bitbreite hat als `USINT`, wird der Wert ohne Datenverlust erweitert.

Der Algorithmus wird durch das `REQ`-Ereignis ausgelöst und gibt nach der Konvertierung das `CNF`-Ereignis aus.

## Technische Besonderheiten
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.
- Die Konvertierung ist verlustfrei, da `DINT` alle Werte von `USINT` darstellen kann.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar nach dem Auslösen des `REQ`-Ereignisses.

## Anwendungsszenarien
- Erweiterung von 8-Bit unsigned Werten auf 32-Bit signed Werte in Steuerungsanwendungen.
- Kompatibilität zwischen verschiedenen Teilen eines Steuerungssystems, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_SINT_TO_DINT` oder `F_INT_TO_DINT` behandelt dieser Baustein ausschließlich unsigned 8-Bit Werte.
- Ähnliche Konvertierungsbausteine existieren für andere Datentypen, wie z.B. `F_BOOL_TO_INT` oder `F_REAL_TO_LREAL`.

## Fazit
Der `F_USINT_TO_DINT`-Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von 8-Bit unsigned Integer-Werten in 32-Bit signed Integer-Werte. Er ist besonders nützlich in Szenarien, wo eine Typenerweiterung ohne Datenverlust erforderlich ist.