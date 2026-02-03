# F_STRING_AS_USINT

```{index} single: F_STRING_AS_USINT
```

<img width="1480" height="212" alt="F_STRING_AS_USINT" src="https://github.com/user-attachments/assets/70362b16-1ffa-4281-8a03-3acb4f428c33" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_USINT` dient der Konvertierung eines `STRING`-Wertes in einen `USINT`-Wert (Unsigned Short Integer). Der Block ist Teil des `iec61131::conversion`-Pakets und ermöglicht die einfache Umwandlung von Zeichenketten in numerische Werte.

![F_STRING_AS_USINT](F_STRING_AS_USINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `STRING`-Wert, der in einen `USINT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten `USINT`-Wert aus.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `STRING`-Wert am Eingang `IN` in einen `USINT`-Wert umwandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert den Abschluss der Konvertierung.

## Technische Besonderheiten
- Der Block verwendet die Funktion `STRING_AS_USINT` zur Konvertierung.
- Die Konvertierung erfolgt synchron mit dem Auslösen des `REQ`-Ereignisses.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Benutzereingaben oder Kommunikationsdaten in numerische Werte.
- Verwendung in Steuerungslogik, wo Zeichenketten in numerische Werte umgewandelt werden müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsblöcken wie `F_STRING_AS_INT` oder `F_STRING_AS_UINT` ist dieser Block speziell für die Umwandlung in `USINT`-Werte optimiert.

## Fazit
Der `F_STRING_AS_USINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `STRING`-Werte in `USINT`-Werte umzuwandeln. Er ist besonders nützlich in Anwendungen, wo Zeichenketten in numerische Werte konvertiert werden müssen.