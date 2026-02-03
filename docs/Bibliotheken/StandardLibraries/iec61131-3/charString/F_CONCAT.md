# F_CONCAT

```{index} single: F_CONCAT
```

<img width="1436" height="240" alt="F_CONCAT" src="https://github.com/user-attachments/assets/5f43c8b8-b683-4d0d-83c8-16dc8e4e987d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_CONCAT` dient der Verkettung (Konkatenation) von zwei Zeichenketten (Strings). Er ist Teil der Standard-Bibliothek für Zeichen- und String-Operationen gemäß IEC 61131-3.

![F_CONCAT](F_CONCAT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Service Request): Startet die Verkettungsoperation. Der Block benötigt beide Eingabestrings (`IN1` und `IN2`), um die Operation auszuführen.

### **Ereignis-Ausgänge**
- `CNF` (Confirmation of Requested Service): Signalisiert die erfolgreiche Beendigung der Verkettungsoperation. Das Ergebnis wird über den Datenausgang `OUT` bereitgestellt.

### **Daten-Eingänge**
- `IN1` (input string 1): Erster Eingabestring vom Typ `ANY_STRING`.
- `IN2` (input string 2): Zweiter Eingabestring vom Typ `ANY_STRING`.

### **Daten-Ausgänge**
- `OUT` (string 1 + string 2): Ergebnis der Verkettung von `IN1` und `IN2` als `ANY_STRING`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` werden die beiden Eingabestrings `IN1` und `IN2` verkettet. Das Ergebnis wird über den Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Beendigung der Operation.

## Technische Besonderheiten
- Unterstützt den Datentyp `ANY_STRING`, was eine flexible Verwendung mit verschiedenen String-Typen ermöglicht.
- Einfache und direkte Implementierung ohne zusätzliche Parameter oder komplexe Zustandslogik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Kombination von Textteilen in automatisierten Nachrichtensystemen.
- Erstellung dynamischer Strings in Steuerungslogiken, z.B. für Protokollierung oder Benachrichtigungen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_STRING_TO_*`-Blöcken, die Strings konvertieren, führt `F_CONCAT` keine Typumwandlung durch.
- Einfacher als Blöcke mit zusätzlichen Formatierungsoptionen wie `F_STRING_FORMAT`.

## Fazit
`F_CONCAT` ist ein grundlegender und effizienter Baustein für die String-Verarbeitung in IEC 61131-3-Umgebungen. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für grundlegende Verkettungsaufgaben.