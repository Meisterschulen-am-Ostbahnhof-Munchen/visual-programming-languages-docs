# F_BOOL_TO_LWORD

```{index} single: F_BOOL_TO_LWORD
```

<img width="1242" height="182" alt="F_BOOL_TO_LWORD" src="https://github.com/user-attachments/assets/eed96580-b3cb-4354-91df-bc8b33c8a966" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_LWORD` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen 64-Bit langen vorzeichenlosen Integerwert (`LWORD`). Diese Konvertierung ist insbesondere in Szenarien nützlich, in denen boolesche Werte in größere Datenstrukturen eingebettet oder mit anderen langen Integerwerten verarbeitet werden müssen.

![F_BOOL_TO_LWORD](F_BOOL_TO_LWORD.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der boolesche Wert (`BOOL`), der in einen `LWORD` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte 64-Bit lange vorzeichenlose Integerwert (`LWORD`).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `LWORD` durch, wenn das `REQ`-Ereignis eintritt. Der boolesche Wert `IN` wird in einen `LWORD` umgewandelt, wobei `FALSE` zu `0` und `TRUE` zu `1` konvertiert wird. Das Ergebnis wird am Daten-Ausgang `OUT` ausgegeben, und das `CNF`-Ereignis wird ausgelöst, um die erfolgreiche Ausführung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `BOOL_TO_LWORD`, die den booleschen Wert in einen 64-Bit-Wert umwandelt.
- Der Funktionsblock ist einfach und deterministisch, da er keine internen Zustände speichert.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock ohne interne Zustände handelt, gibt es keine Zustandsübergänge oder -verwaltung.

## Anwendungsszenarien
- Einbettung boolescher Werte in größere Datenstrukturen, die `LWORD` verwenden.
- Verwendung in Systemen, die boolesche Werte als lange Integerwerte verarbeiten müssen, z.B. bei der Kommunikation mit externen Systemen oder bei der Speicherung in Datenbanken.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_BOOL_TO_<TYPE>**: Ähnliche Funktionsblöcke existieren für andere Datentypen (z.B. `F_BOOL_TO_BYTE`, `F_BOOL_TO_WORD`). Diese konvertieren boolesche Werte in andere Integer-Datentypen mit unterschiedlicher Bitbreite.
- **F_<TYPE>_TO_LWORD**: Andere Konvertierungsblöcke wandeln verschiedene Datentypen (z.B. `INT`, `DINT`) in `LWORD` um, aber `F_BOOL_TO_LWORD` ist spezifisch für boolesche Werte.

## Fazit
Der `F_BOOL_TO_LWORD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, boolesche Werte in 64-Bit lange Integerwerte umzuwandeln. Seine deterministische Funktionsweise und klare Schnittstellenstruktur machen ihn zu einem nützlichen Baustein in Steuerungs- und Automatisierungssystemen, insbesondere dort, wo boolesche Werte in größere Datenstrukturen integriert werden müssen.