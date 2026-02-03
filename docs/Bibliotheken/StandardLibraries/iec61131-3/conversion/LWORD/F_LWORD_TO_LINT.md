# F_LWORD_TO_LINT

```{index} single: F_LWORD_TO_LINT
```

<img width="1450" height="211" alt="F_LWORD_TO_LINT" src="https://github.com/user-attachments/assets/af814d4f-020f-4276-840f-113fb63e2f16" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_LINT` dient der Konvertierung eines `LWORD`-Wertes (64-Bit unsigned) in einen `LINT`-Wert (64-Bit signed). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_LWORD_TO_LINT](F_LWORD_TO_LINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingang für den `LWORD`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten `LINT`-Wert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `LWORD` zu `LINT` durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `LWORD_TO_LINT(IN)`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher FB (SimpleFB) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine komplexen Zustandsübergänge. Der Block reagiert auf `REQ` mit der Ausführung des Algorithmus und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `LWORD`-Daten in `LINT` umgewandelt werden müssen.
- Integration in größere Systeme, die mit unterschiedlichen Datentypen arbeiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine könnten `F_DWORD_TO_DINT` oder `F_WORD_TO_INT` sein, die jedoch für kleinere Datentypen ausgelegt sind.
- Im Gegensatz zu generischen Konvertierungsblöcken ist dieser speziell für die Umwandlung von `LWORD` zu `LINT` optimiert.

## Fazit
Der `F_LWORD_TO_LINT`-Funktionsblock bietet eine effiziente und direkte Methode zur Konvertierung von `LWORD` zu `LINT`. Seine Einfachheit und Spezialisierung machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen.