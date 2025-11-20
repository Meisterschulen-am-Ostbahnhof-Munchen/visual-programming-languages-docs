# ARR08B_TO_ST08B

![ARR08B_TO_ST08B](https://github.com/user-attachments/assets/dbb9cd01-8bc0-495c-a0d8-33dfdba71876)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARR08B_TO_ST08B` dient der Konvertierung eines 8-elementigen BOOL-Arrays (ARR08B) in eine ST08B-Datenstruktur. Dieser Baustein ist besonders nützlich in Szenarien, wo eine kompakte Array-Darstellung in eine strukturierte Form mit benannten Feldern umgewandelt werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Löst die Ausführung des Funktionsblocks aus. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (ARR08B Input): Ein Array von 8 BOOL-Werten (Index 0 bis 7), das konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (ST08B Output): Die resultierende ST08B-Datenstruktur, die die 8 BOOL-Werte als benannte Felder enthält (`B_00` bis `B_07`).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die 8 BOOL-Werte aus dem Eingangsarray `IN` und weist sie den entsprechenden Feldern der ST08B-Struktur `OUT` zu:
- `OUT.B_00` = `IN[0]`
- `OUT.B_01` = `IN[1]`
- ...
- `OUT.B_07` = `IN[7]`

Die Konvertierung erfolgt bei jedem `REQ`-Ereignis, und das Ergebnis wird mit dem `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert.
- Die Array-Indizierung beginnt bei 0 (typisch für IEC 61131-3).
- Die ST08B-Struktur muss im Projekt definiert sein und folgende Felder enthalten: `B_00` bis `B_07`.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf ein `REQ`-Ereignis.
2. **Ausführungszustand**: Bei `REQ` werden die Daten konvertiert.
3. **Bestätigungszustand**: Sendet `CNF` nach erfolgreicher Konvertierung.

## Anwendungsszenarien
- Umwandlung von kompakten Binärdaten (z.B. aus Kommunikationsprotokollen) in strukturierte Daten.
- Anbindung von Hardware-IOs, die Daten als Array liefern, an logische Strukturen im Steuerungsprogramm.
- Vereinfachung der Programmierung durch benannte Boolesche Variablen statt Array-Indizes.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Array-zu-Struct-Konvertern ist dieser Baustein spezialisiert auf 8 BOOL-Werte.
- Ähnliche Bausteine könnten andere Datenformate unterstützen (z.B. WORD zu Struct), aber dieser ist auf die spezifische ARR08B-zu-ST08B-Konvertierung optimiert.

## Fazit
Der `ARR08B_TO_ST08B`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, kompakte Boolesche Arrays in eine besser lesbare Struktur umzuwandeln. Seine spezialisierte Natur macht ihn besonders nützlich in Projekten, wo diese spezifische Konvertierung häufig benötigt wird.
