# F_BYTE_TO_UDINT

```{index} single: F_BYTE_TO_UDINT
```

<img width="1245" height="183" alt="F_BYTE_TO_UDINT" src="https://github.com/user-attachments/assets/34a2230f-154d-4bae-ac66-db0481be7d57" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_UDINT` dient zur Konvertierung eines BYTE-Wertes in einen UDINT-Wert. Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_BYTE_TO_UDINT](F_BYTE_TO_UDINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Ereigniseingang löst die Konvertierung aus. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ereignisausgang signalisiert die erfolgreiche Beendigung der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `BYTE`, der den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `UDINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert am Eingang `IN` vom Typ `BYTE` in einen `UDINT`-Wert konvertiert und das Ergebnis am Ausgang `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um die erfolgreiche Beendigung der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock verwendet die eingebaute Funktion `BYTE_TO_UDINT` zur Konvertierung.
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, bei denen BYTE-Werte in UDINT-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die eine einheitliche Datenverarbeitung erfordern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_WORD_TO_UDINT` oder `F_DWORD_TO_UDINT` ist dieser Baustein speziell für die Konvertierung von `BYTE` zu `UDINT` optimiert.
- Ähnliche Bausteine können unterschiedliche Eingangsdatentypen verarbeiten, sind aber ansonsten in ihrer Funktionsweise vergleichbar.




## 🛠️ Zugehörige Übungen

* [Uebung_011a](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_011a.md)

## Fazit
Der `F_BYTE_TO_UDINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, BYTE-Werte in UDINT-Werte umzuwandeln. Durch seine klare Schnittstellenstruktur und direkte Funktionsweise eignet er sich ideal für Anwendungen, die eine schnelle und zuverlässige Typumwandlung erfordern.