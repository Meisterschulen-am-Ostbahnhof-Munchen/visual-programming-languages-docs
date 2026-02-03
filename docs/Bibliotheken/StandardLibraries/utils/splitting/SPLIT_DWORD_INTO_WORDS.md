# SPLIT_DWORD_INTO_WORDS

```{index} single: SPLIT_DWORD_INTO_WORDS
```

![SPLIT_DWORD_INTO_WORDS](https://github.com/user-attachments/assets/393aad99-3222-4c5f-981b-4795868b5052)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_DWORD_INTO_WORDS` dient dazu, ein 32-Bit DWORD in zwei 16-Bit WORDS aufzuteilen. Diese Funktionalität ist besonders nützlich, wenn mit Daten gearbeitet wird, die als DWORD vorliegen, aber in einzelnen WORD-Teilen weiterverarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Wird mit den Daten-Ausgängen `WORD_00` und `WORD_01` verknüpft.

### **Daten-Eingänge**
- **IN**: DWORD (32-Bit), das in zwei WORDS aufgeteilt werden soll.

### **Daten-Ausgänge**
- **WORD_00**: Erstes WORD (16-Bit) des DWORD.
- **WORD_01**: Zweites WORD (16-Bit) des DWORD.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock nimmt ein DWORD als Eingabe und teilt es in zwei WORDS auf:
- `WORD_00` enthält die unteren 16 Bits des DWORD (`IN.%W0`).
- `WORD_01` enthält die oberen 16 Bits des DWORD (`IN.%X1`).

Die Aufteilung erfolgt bei jedem `REQ`-Ereignis, und das Ergebnis wird mit dem `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Die Implementierung erfolgt in Structured Text (ST).
- Der Funktionsblock ist Teil des Pakets `eclipse4diac::utils::splitting`.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Verarbeitung erfolgt bei jedem `REQ`-Ereignis unmittelbar.

## Anwendungsszenarien
- Verarbeitung von DWORD-Daten, die aus Hardware-Registern oder Kommunikationsprotokollen stammen.
- Aufteilung von 32-Bit Werten für die weitere Verarbeitung in 16-Bit Systemen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Bit-Manipulationsblöcken ist `SPLIT_DWORD_INTO_WORDS` spezialisiert auf die Aufteilung von DWORD in WORDS.
- Ähnliche Blöcke könnten zusätzliche Flexibilität bieten, wie z.B. die Auswahl der zu extrahierenden Bits, sind aber oft komplexer in der Handhabung.

## Fazit
Der `SPLIT_DWORD_INTO_WORDS`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, DWORD-Daten in ihre WORD-Komponenten aufzuteilen. Seine spezialisierte Funktionalität macht ihn besonders nützlich für Anwendungen, die regelmäßig mit solchen Datenumwandlungen arbeiten müssen.