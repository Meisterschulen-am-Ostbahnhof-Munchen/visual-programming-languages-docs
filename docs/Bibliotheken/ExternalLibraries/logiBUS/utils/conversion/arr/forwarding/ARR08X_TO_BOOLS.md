# ARR08X_TO_BOOLS

```{index} single: ARR08X_TO_BOOLS
```

<img width="1076" height="362" alt="image" src="https://github.com/user-attachments/assets/d607edb8-cbf2-4776-a5f2-cc8022ad9574" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ARR08X_TO_BOOLS** dient der Umwandlung eines 8-elementigen BOOL-Arrays in acht einzelne BOOL-Signale. Er extrahiert jedes Bit aus dem Eingangsarray und stellt es über einen eigenen, benannten Datenausgang zur Verfügung. Dieser Baustein ist besonders nützlich, um kompakte Array-Daten aus übergeordneten Systemen oder Kommunikationsschnittstellen in einzelne, leicht zu verarbeitende logische Signale aufzuschlüsseln.

## Schnittstellenstruktur
Der Baustein besitzt eine einfache, unidirektionale Schnittstelle mit einem Anforderungs-/Bestätigungs-Ereignispaar.

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Verarbeitung aus. Bei seinem Eintreffen werden die Werte des Eingangsarrays `IN` gelesen und auf die einzelnen Ausgänge `OUT_00` bis `OUT_07` verteilt.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis wird ausgelöst, sobald die Extraktion der Booleschen Werte abgeschlossen ist. Es bestätigt die Ausführung des Bausteins und transportiert die neuen Werte aller acht Datenausgänge (`OUT_00` bis `OUT_07`).

### **Daten-Eingänge**
*   **IN** (ARRAY[0..7] OF BOOL): Das Eingangsarray, das die acht zu extrahierenden Booleschen Werte enthält. Der Index 0 entspricht dem niederwertigsten Bit (LSB) und wird auf `OUT_00` abgebildet.

### **Daten-Ausgänge**
*   **OUT_00** (BOOL): Extrahiertes Bit 0 (LSB) des Eingangsarrays `IN`.
*   **OUT_01** (BOOL): Extrahiertes Bit 1 des Eingangsarrays `IN`.
*   **OUT_02** (BOOL): Extrahiertes Bit 2 des Eingangsarrays `IN`.
*   **OUT_03** (BOOL): Extrahiertes Bit 3 des Eingangsarrays `IN`.
*   **OUT_04** (BOOL): Extrahiertes Bit 4 des Eingangsarrays `IN`.
*   **OUT_05** (BOOL): Extrahiertes Bit 5 des Eingangsarrays `IN`.
*   **OUT_06** (BOOL): Extrahiertes Bit 6 des Eingangsarrays `IN`.
*   **OUT_07** (BOOL): Extrahiertes Bit 7 (MSB) des Eingangsarrays `IN`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Die Funktionsweise ist deterministisch und nicht-zustandsbehaftet. Bei jedem Eintreffen des `REQ`-Ereignisses führt der Baustein eine direkte Zuweisung durch. Jedes Element des Eingangsarrays `IN` wird seinem entsprechenden, einzeln benannten Ausgangsvariable zugewiesen. Die Logik entspricht folgender ST-Zuweisung:
```iec61131-3
OUT_00 := IN[0];
OUT_01 := IN[1];
OUT_02 := IN[2];
OUT_03 := IN[3];
OUT_04 := IN[4];
OUT_05 := IN[5];
OUT_06 := IN[6];
OUT_07 := IN[7];
```
Unmittelbar nach Abschluss dieser Operation wird das `CNF`-Ereignis mit den neuen Werten generiert.

## Technische Besonderheiten
*   **Echtzeitverhalten:** Der Baustein führt nur Zuweisungen aus und verursacht keine nennenswerte Latenz. Die Ausführung ist in einem Zyklus abgeschlossen.
*   **Speicher:** Es wird kein interner Zustand zwischen den Aufrufen gespeichert. Die Ausgabe ist eine reine Funktion der aktuellen Eingabe.
*   **Array-Grenzen:** Der Baustein ist spezifisch für Arrays der festen Größe 8 (Indizes 0 bis 7) definiert. Die Verwendung eines Arrays anderer Größe führt zu einem Kompilierfehler.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (zustandslos). Sein Verhalten ist bei jedem Aufruf identisch und hängt ausschließlich von den aktuellen Werten am Daten-Eingang `IN` ab.

## Anwendungsszenarien
*   **Entpacken von Bus-Telegrammen:** Extraktion einzelner Status- oder Steuerbits aus einem Byte, das über Feldbusse (z.B. CAN, PROFIBUS) oder industrielle Netzwerke empfangen wurde.
*   **Schnittstelle zu Bit-orientierten Komponenten:** Aufbereitung von Array-Daten für die Ansteuerung von einzelnen Lampen, Ventilen oder Relais, die über diskrete BOOL-Ausgänge angesprochen werden.
*   **Vereinfachung der Visualisierung:** Bereitstellung von einzeln adressierbaren Signalen für HMIs oder Alarmierungsysteme, anstatt mit Array-Indizes arbeiten zu müssen.
*   **Dekodierung:** Umsetzung einer einfachen 8-Bit-Binärzahl in ihre logischen Einzelwerte.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **`SEL` / `MUX` Bausteine:** Diese wählen ein einzelnes Element aus einem Array basierend auf einem Index aus. `ARR08X_TO_BOOLS` hingegen extrahiert **alle** Elemente gleichzeitig und parallel.
*   **`BYTE_TO_BOOLS` / `WORD_TO_BOOLS`:** Diese Bausteine zerlegen ein Byte- oder Wort-Datenelement in seine einzelnen Bits. `ARR08X_TO_BOOLS` arbeitet direkt auf einem Array von BOOLs, was semantisch klarer ist, wenn die Quelle bereits ein BOOL-Array ist. Die funktionale Wirkung auf die Bits ist jedoch äquivalent.
*   **Manuelle Indexierung:** Statt dieses Bausteins zu verwenden, könnte man im umgebenden Algorithmus direkt auf `IN[0]`, `IN[1]` usw. zugreifen. Der Funktionsblock bietet jedoch eine klarere Schnittstellenbeschreibung, verbessert die Lesbarkeit des FBD-Netzwerks und kapselt die Funktionalität.




## 🛠️ Zugehörige Übungen

* [Uebung_054](../../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_054.md)

## Fazit
Der `ARR08X_TO_BOOLS` ist ein spezialisierter, aber sehr nützlicher Konvertierungsbaustein. Er stellt eine einfache und effiziente Methode dar, um ein kompaktes 8-Bit-BOOL-Array in acht diskrete Signale zu entpacken. Durch seine klare, zustandslose Funktionsweise und die explizite Benennung aller Ausgänge trägt er erheblich zur Verbesserung der Lesbarkeit und Wartbarkeit von Steuerungsapplikationen bei, in denen mit array-basierten Datenstrukturen gearbeitet wird.