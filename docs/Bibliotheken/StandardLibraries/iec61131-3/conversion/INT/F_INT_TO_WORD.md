# F_INT_TO_WORD

```{index} single: F_INT_TO_WORD
```

<img width="1221" height="183" alt="F_INT_TO_WORD" src="https://github.com/user-attachments/assets/0fd8962d-cbc1-47ea-828f-2286fc7e411b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_WORD` dient der Konvertierung eines ganzzahligen Wertes (INT) in einen 16-Bit-Wortwert (WORD). Diese Konvertierung ist besonders nützlich in Szenarien, wo Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen.

![F_INT_TO_WORD](F_INT_TO_WORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Gleichzeitig wird der konvertierte Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der Eingang für den ganzzahligen Wert (INT), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten 16-Bit-Wortwert (WORD).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert am Eingang `IN` gelesen und mit der Funktion `INT_TO_WORD` in einen WORD-Wert umgewandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und gleichzeitig das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient implementiert, ohne zusätzliche Zustände oder komplexe Logik.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Schnittstellen zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Protokollierung und Überwachung, wo Daten in einheitlichen Formaten benötigt werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_INT_TO_WORD` spezialisiert auf die Konvertierung von INT zu WORD und daher effizienter in dieser spezifischen Aufgabe.
- Andere Blöcke wie `F_DINT_TO_WORD` oder `F_SINT_TO_WORD` bieten ähnliche Funktionalität, aber für unterschiedliche Quell-Datentypen.

## Fazit
Der `F_INT_TO_WORD` Funktionsblock ist ein einfaches und effektives Werkzeug für die Konvertierung von ganzzahligen Werten in 16-Bit-Wortwerte. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungs- und Automatisierungssystemen.