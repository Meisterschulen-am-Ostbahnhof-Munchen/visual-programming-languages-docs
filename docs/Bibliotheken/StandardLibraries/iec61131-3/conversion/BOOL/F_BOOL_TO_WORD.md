# F_BOOL_TO_WORD

```{index} single: F_BOOL_TO_WORD
```

<img width="1434" height="212" alt="F_BOOL_TO_WORD" src="https://github.com/user-attachments/assets/2108fbdb-57b2-48c1-9549-416c9024f862" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_WORD` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen 16-Bit-Wortwert (`WORD`). Diese Konvertierung ist insbesondere in Szenarien nützlich, in denen boolesche Signale in Wort-Datenstrukturen eingebettet oder weiterverarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `BOOL`, der in ein `WORD` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `WORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `WORD` durch, wenn das Ereignis `REQ` empfangen wird. Der boolesche Wert `IN` wird in ein 16-Bit-Wort umgewandelt, wobei `FALSE` als `0` und `TRUE` als `1` interpretiert wird. Das Ergebnis wird über den Ausgang `OUT` ausgegeben, und das Ereignis `CNF` wird ausgelöst, um die erfolgreiche Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt durch die Funktion `BOOL_TO_WORD(IN)`.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Einbettung boolescher Signale in Wort-Datenstrukturen für die Kommunikation mit anderen Systemen.
- Verwendung in Steuerungslogik, wo boolesche Werte als Teil größerer Datenwörter verarbeitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_BOOL_TO_BYTE` oder `F_BOOL_TO_DWORD` bieten Konvertierungen in andere Datentypen (`BYTE` oder `DWORD`). `F_BOOL_TO_WORD` ist spezifisch für 16-Bit-Wortwerte.

## Fazit
Der Funktionsblock `F_BOOL_TO_WORD` bietet eine einfache und effiziente Möglichkeit, boolesche Werte in Wortwerte zu konvertieren. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für Anwendungen, die solche Konvertierungen erfordern.
