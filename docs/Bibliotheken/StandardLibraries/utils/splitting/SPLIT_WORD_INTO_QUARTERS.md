# SPLIT_WORD_INTO_QUARTERS

```{index} single: SPLIT_WORD_INTO_QUARTERS
```

![SPLIT_WORD_INTO_QUARTERS](https://github.com/user-attachments/assets/f26e7474-c9bf-4fb4-923f-d8c2ad4ac48e)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_WORD_INTO_QUARTERS` dient dazu, ein 16-Bit-Wort in acht 2-Bit-Quarter-Bytes aufzuteilen. Dies ist besonders nützlich, wenn komprimierte Daten verarbeitet oder bestimmte Bitmuster extrahiert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung des Eingangsworts. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Verarbeitung. Wird mit allen acht Quarter-Byte-Ausgängen verknüpft.

### **Daten-Eingänge**
- `IN` (WORD): Das 16-Bit-Eingangswort, das in Quarter-Bytes aufgeteilt wird.

### **Daten-Ausgänge**
- `QUARTER_BYTE_00` bis `QUARTER_BYTE_07` (BYTE): Die acht extrahierten 2-Bit-Quarter-Bytes. Jeder Ausgang enthält eines der Quarter-Bytes des Eingangsworts.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt Bitmasken und Schiebeoperationen, um die einzelnen 2-Bit-Abschnitte aus dem Eingangswort zu extrahieren. Jedes Quarter-Byte wird durch eine bitweise UND-Verknüpfung mit einer spezifischen Maske isoliert und dann an die entsprechende Position geschoben, um es als BYTE auszugeben.

## Technische Besonderheiten
- Verwendet Konstanten (`quarterconst::WORD_QUARTER_XX` und `quarterconst::SHIFT_QUARTER_XX`) für die Masken und Schiebepositionen.
- Die Extraktion erfolgt durch Kombination von UND-Verknüpfungen und Rechts-Schiebeoperationen.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Extrahiert die Quarter-Bytes aus dem Eingangswort.
3. **Completion**: Sendet das `CNF`-Ereignis und gibt die Quarter-Bytes aus.

## Anwendungsszenarien
- Dekodierung von komprimierten Daten.
- Extraktion von Steuerbits aus einem Statuswort.
- Verarbeitung von kodierten Sensordaten.

## Vergleich mit ähnlichen Bausteinen
- **SPLIT_WORD_INTO_BYTES**: Teilt ein Wort in zwei Bytes auf, nicht in acht Quarter-Bytes.
- **BIT_EXTRACT**: Extrahiert einzelne Bits oder Bitgruppen, ist aber weniger spezialisiert für Quarter-Bytes.

## Fazit
Der `SPLIT_WORD_INTO_QUARTERS`-Funktionsblock ist ein spezialisiertes Werkzeug zur effizienten Extraktion von 2-Bit-Daten aus einem 16-Bit-Wort. Seine klare Schnittstelle und effiziente Implementierung machen ihn ideal für Anwendungen, die mit komprimierten oder bitkodierten Daten arbeiten.
