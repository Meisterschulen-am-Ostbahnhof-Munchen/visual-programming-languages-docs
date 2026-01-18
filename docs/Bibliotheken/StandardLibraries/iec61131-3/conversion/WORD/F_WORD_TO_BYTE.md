# F_WORD_TO_BYTE

```{index} single: F_WORD_TO_BYTE
```

<img width="1439" height="214" alt="F_WORD_TO_BYTE" src="https://github.com/user-attachments/assets/f145baeb-c930-43aa-803f-40e3e50a88fe" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_BYTE` dient zur Konvertierung eines `WORD`-Datentyps in einen `BYTE`-Datentyp. Er ist Teil des Pakets `iec61131::conversion` und eignet sich für Anwendungen, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`WORD`): Der Eingangswert, der von `WORD` in `BYTE` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`BYTE`): Der konvertierte Ausgangswert vom Typ `BYTE`.

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Dabei wird der Wert am Eingang `IN` vom Typ `WORD` mithilfe der Funktion `WORD_TO_BYTE` in einen `BYTE`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt und `CNF` ausgelöst.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, bei denen `WORD`-Daten in `BYTE`-Daten umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die eine kompatible Datentypkonvertierung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsfunktionen bietet dieser Funktionsblock eine spezialisierte und optimierte Lösung für die Umwandlung von `WORD` zu `BYTE`.
- Andere ähnliche Blöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder optionale Parameter bieten, was hier nicht der Fall ist.

## Fazit
Der `F_WORD_TO_BYTE`-Funktionsblock ist eine effiziente und einfache Lösung für die Konvertierung von `WORD`- zu `BYTE`-Daten. Er ist besonders geeignet für Anwendungen, bei denen eine schnelle und direkte Typumwandlung erforderlich ist.
