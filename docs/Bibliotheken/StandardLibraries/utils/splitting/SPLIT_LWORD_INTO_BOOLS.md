# SPLIT_LWORD_INTO_BOOLS

```{index} single: SPLIT_LWORD_INTO_BOOLS
```

![SPLIT_LWORD_INTO_BOOLS](https://github.com/user-attachments/assets/1049fa17-3495-4ca5-8e03-ae09e81b47d5)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_LWORD_INTO_BOOLS` dient zur Zerlegung eines 64-Bit-LWORD-Datentyps in seine einzelnen Bits. Jedes Bit wird als separater BOOL-Ausgang bereitgestellt. Dieser Block ist besonders nützlich, wenn einzelne Bits eines langen Wortes ausgewertet oder verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Event): Startet die Zerlegung des LWORD in einzelne Bits. Wird mit dem Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Event): Bestätigt die erfolgreiche Zerlegung des LWORD. Wird mit allen 64 BOOL-Ausgängen verknüpft.

### **Daten-Eingänge**
- `IN` (LWORD): Das 64-Bit-Wort, das in einzelne Bits zerlegt werden soll.

### **Daten-Ausgänge**
- `BIT_00` bis `BIT_63` (BOOL): Die einzelnen Bits des Eingangs-LWORD, wobei `BIT_00` das niederwertigste Bit (LSB) und `BIT_63` das höchstwertige Bit (MSB) darstellt.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert jedes Bit des Eingangs-LWORD (`IN`) und weist es den entsprechenden BOOL-Ausgängen zu. Die Extraktion erfolgt über direkte Bit-Zugriffe (`IN.%X0` bis `IN.%X63`). Bei Auslösung des `REQ`-Ereignisses werden alle Bits aktualisiert und das `CNF`-Ereignis bestätigt die erfolgreiche Verarbeitung.

## Technische Besonderheiten
- Verarbeitet 64-Bit-Daten (LWORD).
- Jedes Bit wird einzeln als BOOL ausgegeben.
- Keine zusätzliche Logik oder Filterung – direkte Bit-Zuordnung.

## Zustandsübersicht
Der Block hat keinen internen Zustand. Die Zerlegung erfolgt bei jedem `REQ`-Ereignis neu.

## Anwendungsszenarien
- Auswertung von Bitmasken oder Statusregistern.
- Verarbeitung von digitalen Signalen, die als LWORD kodiert sind.
- Debugging oder Monitoring von einzelnen Bits in langen Datenwörtern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Blöcke wie `SPLIT_WORD_INTO_BOOLS` oder `SPLIT_DWORD_INTO_BOOLS` arbeiten mit kürzeren Datentypen (WORD bzw. DWORD).
- Dieser Block ist speziell für 64-Bit-Daten optimiert.

## Fazit
Der `SPLIT_LWORD_INTO_BOOLS`-Block ist ein effizientes Werkzeug zur Zerlegung von 64-Bit-Daten in einzelne Bits. Seine einfache und direkte Funktionsweise macht ihn ideal für Anwendungen, bei denen eine detaillierte Bit-Analyse erforderlich ist.