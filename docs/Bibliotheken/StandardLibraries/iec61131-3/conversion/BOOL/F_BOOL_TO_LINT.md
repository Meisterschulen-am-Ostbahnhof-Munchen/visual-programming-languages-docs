# F_BOOL_TO_LINT

```{index} single: F_BOOL_TO_LINT
```

<img width="1234" height="182" alt="F_BOOL_TO_LINT" src="https://github.com/user-attachments/assets/4c333a4d-5021-4e63-8ee2-fdf1494dd38f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_LINT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen 64-Bit Integer-Wert (`LINT`). Dieser Block ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_BOOL_TO_LINT](F_BOOL_TO_LINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Ausführung des Funktionsblocks aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ausgang signalisiert die erfolgreiche Ausführung des Funktionsblocks. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang für den booleschen Wert (`BOOL`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten 64-Bit Integer-Wert (`LINT`).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `LINT` durch, wenn das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `BOOL_TO_LINT(IN)`, wobei der boolesche Wert `IN` in einen `LINT`-Wert umgewandelt wird. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst.

## Technische Besonderheiten
- Der Block ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung ist deterministisch und erfolgt ohne Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo boolesche Werte in numerische Werte umgewandelt werden müssen.
- Integration in größere Systeme, die eine einheitliche Datentypverarbeitung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsblöcken wie `F_BOOL_TO_INT` oder `F_BOOL_TO_DINT` bietet dieser Block eine höhere Präzision durch die Verwendung des `LINT`-Datentyps (64-Bit).

## Fazit
Der `F_BOOL_TO_LINT`-Funktionsblock ist ein effizientes Werkzeug für die Konvertierung von booleschen Werten in 64-Bit Integer-Werte. Seine einfache und deterministische Funktionsweise macht ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen.