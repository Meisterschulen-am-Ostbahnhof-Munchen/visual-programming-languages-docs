# F_SINT_TO_ULINT

```{index} single: F_SINT_TO_ULINT
```

<img width="1450" height="213" alt="F_SINT_TO_ULINT" src="https://github.com/user-attachments/assets/e86a91a2-2770-46c2-8677-2d3c90a6111a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_ULINT` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (`SINT`) in einen vorzeichenlosen 64-Bit-Integer-Wert (`ULINT`). Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_SINT_TO_ULINT](F_SINT_TO_ULINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `SINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `ULINT`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Dabei wird der Wert am Eingang `IN` vom Typ `SINT` in einen `ULINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die erfolgreiche Konvertierung wird durch das Ereignis `CNF` signalisiert.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die eingebaute Funktion `SINT_TO_ULINT`.
- Der Baustein ist einfach und deterministisch, da er keine internen Zustände speichert.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `SINT`-Werte in größere vorzeichenlose Integer-Typen umgewandelt werden müssen.
- Datenverarbeitung in Systemen, die mit unterschiedlichen Integer-Formaten arbeiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_INT_TO_ULINT` oder `F_DINT_TO_ULINT` führen ähnliche Konvertierungen durch, jedoch mit anderen Eingangstypen.
- `F_SINT_TO_ULINT` ist spezifisch für die Konvertierung von `SINT` zu `ULINT` optimiert.

## Fazit
Der `F_SINT_TO_ULINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `SINT`-Werte in `ULINT` umzuwandeln. Er ist besonders in Anwendungen nützlich, bei denen eine sichere und schnelle Typumwandlung erforderlich ist.