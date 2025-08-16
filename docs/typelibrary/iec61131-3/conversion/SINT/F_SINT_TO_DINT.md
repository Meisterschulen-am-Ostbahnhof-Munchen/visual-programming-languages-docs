# F_SINT_TO_DINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_DINT` dient der Konvertierung eines `SINT`-Wertes (8-Bit Ganzahl mit Vorzeichen) in einen `DINT`-Wert (32-Bit Ganzahl mit Vorzeichen). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung erforderlich ist, um Daten für weitere Verarbeitungsschritte vorzubereiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `SINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `DINT`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Wert am Daten-Eingang `IN` gelesen und in den Typ `DINT` konvertiert. Das Ergebnis wird am Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert den erfolgreichen Abschluss der Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch Zuweisung (`OUT := IN`), da `SINT` automatisch in `DINT` umgewandelt wird.
- Der Baustein ist einfach und effizient, da er keine komplexen Berechnungen durchführt.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt und `CNF` ausgelöst.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `SINT`-Daten in `DINT` umgewandelt werden müssen.
- Vorbereitung von Daten für weitere Verarbeitungsschritte, die `DINT` erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_INT_TO_DINT` oder `F_USINT_TO_UDINT` führen ähnliche Konvertierungen durch, aber mit anderen Ausgangs- bzw. Eingangstypen.
- `F_SINT_TO_DINT` ist spezifisch für die Konvertierung von `SINT` zu `DINT`.

## Fazit
Der `F_SINT_TO_DINT` Funktionsblock ist ein einfacher und effizienter Baustein für die Typumwandlung von `SINT` zu `DINT`. Seine klare Schnittstellenstruktur und einfache Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen.