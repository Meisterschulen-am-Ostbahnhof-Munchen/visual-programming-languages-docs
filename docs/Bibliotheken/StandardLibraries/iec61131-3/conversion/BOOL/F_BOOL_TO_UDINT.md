# F_BOOL_TO_UDINT

```{index} single: F_BOOL_TO_UDINT
```

<img width="1447" height="213" alt="F_BOOL_TO_UDINT" src="https://github.com/user-attachments/assets/2efcda08-ff53-40f4-ba50-1a4fa948991e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_UDINT` dient der Konvertierung eines `BOOL`-Wertes in einen `UDINT`-Wert. Diese Konvertierung ist nützlich, wenn boolesche Werte in Berechnungen oder Speicherungen verwendet werden sollen, die einen größeren numerischen Datentyp erfordern.

![F_BOOL_TO_UDINT](F_BOOL_TO_UDINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `BOOL`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `UDINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Es werden keine Adapter unterstützt.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `UDINT` durch, wenn das Ereignis `REQ` ausgelöst wird. Der boolesche Wert `TRUE` wird in `1` und `FALSE` in `0` umgewandelt. Das Ergebnis wird am Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne Verzögerung.
- Der Funktionsblock ist für den Einsatz in Echtzeitsystemen geeignet.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von booleschen Schaltzuständen für numerische Berechnungen.
- Integration von booleschen Signalen in Systeme, die nur numerische Werte verarbeiten können.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_BOOL_TO_INT` oder `F_BOOL_TO_DINT` bietet dieser Baustein eine Konvertierung in einen vorzeichenlosen 32-Bit-Integer.

## Fazit
Der `F_BOOL_TO_UDINT` Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von booleschen Werten in vorzeichenlose 32-Bit-Integer. Er ist besonders nützlich in Szenarien, wo boolesche Signale in numerische Prozesse integriert werden müssen.