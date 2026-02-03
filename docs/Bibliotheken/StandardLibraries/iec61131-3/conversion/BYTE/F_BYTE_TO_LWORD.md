# F_BYTE_TO_LWORD

```{index} single: F_BYTE_TO_LWORD
```

<img width="1245" height="182" alt="F_BYTE_TO_LWORD" src="https://github.com/user-attachments/assets/c56c9f09-1174-475c-ad6f-123ba7f3aa49" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_LWORD` dient der Konvertierung eines `BYTE`-Wertes in einen `LWORD`-Wert. Er ist Teil der `iec61131::conversion`-Bibliothek und ermöglicht eine einfache und effiziente Typumwandlung.

![F_BYTE_TO_LWORD](F_BYTE_TO_LWORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `BYTE`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `LWORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt bei einem eingehenden `REQ`-Ereignis die Konvertierung des `BYTE`-Wertes am Eingang `IN` in einen `LWORD`-Wert durch. Das Ergebnis wird am Ausgang `OUT` ausgegeben und durch ein `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Funktionsblock verwendet die `BYTE_TO_LWORD`-Funktion zur Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsautomat.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge. Die Konvertierung erfolgt direkt bei einem `REQ`-Ereignis.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `BYTE`-Werte in `LWORD`-Werte umgewandelt werden müssen.
- Einsatz in Datenverarbeitungsketten, wo unterschiedliche Datentypen verarbeitet werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke sind `F_WORD_TO_LWORD` oder `F_DWORD_TO_LWORD`, die andere Datentypen konvertieren.
- Im Gegensatz zu komplexeren Konvertierungsblöcken bietet `F_BYTE_TO_LWORD` eine einfache und direkte Lösung für die spezifische Konvertierung von `BYTE` zu `LWORD`.

## Fazit
Der `F_BYTE_TO_LWORD`-Funktionsblock ist eine effiziente und einfache Lösung für die Konvertierung von `BYTE`- zu `LWORD`-Werten. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für den Einsatz in Steuerungsanwendungen.