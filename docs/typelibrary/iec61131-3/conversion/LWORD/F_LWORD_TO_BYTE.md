# F_LWORD_TO_BYTE

<img width="1451" height="216" alt="F_LWORD_TO_BYTE" src="https://github.com/user-attachments/assets/c3044b5b-615a-4431-aacc-9746dab23af0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_BYTE` dient der Konvertierung eines 64-Bit-Wertes (LWORD) in einen 8-Bit-Wert (BYTE). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht oder verarbeitet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Der Eingang für den 64-Bit-Wert (LWORD), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten 8-Bit-Wert (BYTE).

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert am Eingang `IN` gelesen und mit der Funktion `LWORD_TO_BYTE` in einen BYTE-Wert umgewandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert den Abschluss der Operation.

## Technische Besonderheiten
- Die Konvertierung kann zu Datenverlust führen, da ein 64-Bit-Wert in einen 8-Bit-Wert umgewandelt wird. Es ist wichtig sicherzustellen, dass der ursprüngliche Wert innerhalb des darstellbaren Bereichs eines BYTE (0 bis 255) liegt.
- Der Funktionsblock ist als einfacher Funktionsblock (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Aktiv-Zustand**: Führt die Konvertierung durch und gibt das Ergebnis aus.
3. **Abschluss-Zustand**: Signalisiert den Abschluss mit `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenreduktion: Wenn nur die unteren 8 Bit eines 64-Bit-Wertes relevant sind.
- Kommunikation mit Geräten, die nur BYTE-Daten verarbeiten können.
- Speicheroptimierung in Systemen mit begrenzten Ressourcen.

## Vergleich mit ähnlichen Bausteinen
- **F_WORD_TO_BYTE**: Konvertiert einen 16-Bit-Wert (WORD) in einen BYTE.
- **F_DWORD_TO_BYTE**: Konvertiert einen 32-Bit-Wert (DWORD) in einen BYTE.
- **F_LWORD_TO_WORD**: Konvertiert einen 64-Bit-Wert in einen 16-Bit-Wert.

## Fazit
Der Funktionsblock `F_LWORD_TO_BYTE` bietet eine einfache und effiziente Möglichkeit, 64-Bit-Daten in 8-Bit-Daten umzuwandeln. Er ist besonders nützlich in Szenarien, wo nur ein Teil der Daten benötigt wird oder die Zielplattform nur begrenzte Datentypen unterstützt. Beachten Sie jedoch die möglichen Datenverluste bei der Konvertierung.
