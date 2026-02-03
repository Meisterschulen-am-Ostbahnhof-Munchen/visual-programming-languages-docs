# ASSEMBLE_DWORD_FROM_WORDS

```{index} single: ASSEMBLE_DWORD_FROM_WORDS
```

![ASSEMBLE_DWORD_FROM_WORDS](https://github.com/user-attachments/assets/6e0070a6-ac74-4370-9657-7d0fdd5e02cf)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_DWORD_FROM_WORDS` kombiniert zwei 16-Bit-Wörter (WORD) zu einem 32-Bit-Doppelwort (DWORD). Diese Funktionalität ist besonders nützlich, wenn Daten aus zwei separaten Quellen zusammengeführt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung des Funktionsblocks. Muss mit den Daten-Eingängen `WORD_00` und `WORD_01` verknüpft sein.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Verarbeitung und Ausgabe des kombinierten DWORD.

### **Daten-Eingänge**
- `WORD_00`: Erstes 16-Bit-Wort (WORD), das in das resultierende DWORD eingefügt wird.
- `WORD_01`: Zweites 16-Bit-Wort (WORD), das in das resultierende DWORD eingefügt wird.

### **Daten-Ausgänge**
- (kein Name): Das kombinierte 32-Bit-Doppelwort (DWORD), das aus den beiden Eingabewörtern besteht.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock nimmt die beiden 16-Bit-Eingabewörter (`WORD_00` und `WORD_01`) entgegen und kombiniert sie zu einem einzigen 32-Bit-Doppelwort (DWORD). Dabei wird `WORD_00` in die unteren 16 Bits und `WORD_01` in die oberen 16 Bits des resultierenden DWORD platziert.

## Technische Besonderheiten
- Die Implementierung erfolgt in Structured Text (ST).
- Der Funktionsblock ist Teil des Pakets `eclipse4diac::utils::assembling`.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Verarbeitet die Eingabewörter und erzeugt das DWORD.
3. **Complete**: Sendet das `CNF`-Ereignis mit dem kombinierten DWORD.

## Anwendungsszenarien
- Kombination von zwei 16-Bit-Sensordaten zu einem 32-Bit-Wert.
- Verarbeitung von Daten aus zwei separaten Kommunikationskanälen.
- Erweiterung von 16-Bit-Daten auf 32-Bit für weitere Verarbeitung.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen Bit-Operationen bietet dieser Funktionsblock eine klar definierte Schnittstelle und ist in 4diac-IDE integriert.
- Ähnliche Funktionalität könnte mit Basisoperationen erreicht werden, dieser Baustein vereinfacht jedoch die Handhabung.

## Fazit
Der `ASSEMBLE_DWORD_FROM_WORDS` Funktionsblock bietet eine einfache und effiziente Möglichkeit, zwei 16-Bit-Wörter zu einem 32-Bit-Doppelwort zu kombinieren. Seine klare Schnittstelle und direkte Integration in 4diac machen ihn besonders nützlich für Anwendungen, die mit der Kombination von Wortdaten arbeiten.