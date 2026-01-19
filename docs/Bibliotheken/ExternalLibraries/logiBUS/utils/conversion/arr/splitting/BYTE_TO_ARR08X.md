# BYTE_TO_ARR08X

```{index} single: BYTE_TO_ARR08X
```

<img width="1315" height="219" alt="image" src="https://github.com/user-attachments/assets/9af3b849-ed33-437d-9688-1de0bee2a1f9" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BYTE_TO_ARR08X` dient der Konvertierung eines einzelnen Byte-Wertes in ein Array von acht booleschen Werten (BOOL). Jedes Bit des Eingangsbytes wird einem separaten Element im Ausgangsarray zugeordnet. Dieser Baustein ist besonders nützlich, um kompakte digitale Informationen, die in einem Byte gespeichert sind, für die individuelle Verarbeitung oder Visualisierung aufzuschlüsseln.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   `REQ` (Request): Dieses Ereignis löst die Konvertierungsfunktion aus. Bei seinem Eintreffen wird der aktuelle Wert am Dateneingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
*   `CNF` (Confirm): Dieses Ereignis signalisiert den Abschluss der Konvertierung. Es wird zusammen mit den berechneten Daten am Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
*   `IN` (BYTE): Der Eingang für den Byte-Wert, der in boolesche Bits zerlegt werden soll.

### **Daten-Ausgänge**
*   `OUT` (ARRAY[0..7] OF BOOL): Das Ausgangsarray mit acht BOOL-Elementen. Das Element `OUT[0]` entspricht dem niederwertigsten Bit (LSB, Bit 0) des Eingangsbytes, `OUT[7]` entspricht dem höchstwertigen Bit (MSB, Bit 7).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Auslösung durch das `REQ`-Ereignis liest der Baustein den Wert am Eingang `IN`. Anschließend wird jedes einzelne Bit (0 bis 7) des BYTE-Datentyps extrahiert und dem entsprechenden Index im BOOL-Array `OUT` zugewiesen. Die Zuordnung erfolgt direkt:
*   `OUT[0]` erhält den Wert von `IN.0` (Bit 0)
*   `OUT[1]` erhält den Wert von `IN.1` (Bit 1)
*   ...
*   `OUT[7]` erhält den Wert von `IN.7` (Bit 7)

Nach Abschluss dieser Zuweisungen wird das `CNF`-Ereignis zusammen mit dem gefüllten Array `OUT` ausgegeben.

## Technische Besonderheiten
*   **Direkte Bit-Zugriffe:** Die Implementierung verwendet die in der IEC 61131-3 ST (Structured Text) Syntax übliche direkte Bit-Adressierung (z.B. `IN.0`), was eine effiziente und lesbare Operation ermöglicht.
*   **Feste Array-Größe:** Das Ausgangsarray ist mit der festen Größe `[0..7]` definiert, was exakt der Bit-Länge eines Bytes (8 Bit) entspricht.
*   **Echtzeitfähig:** Der Block führt eine deterministische, zustandslose Operation durch und ist damit für Echtzeitanwendungen geeignet.

## Zustandsübersicht
Der Funktionsblock ist zustandslos (stateless). Sein Verhalten ist bei jedem `REQ`-Ereignis identisch und hängt ausschließlich vom aktuellen Wert am Dateneingang `IN` ab. Es gibt keine internen Variablen, die zwischen den Aufrufen gespeichert werden.

## Anwendungsszenarien
*   **Entpacken von Steuerbytes:** Verarbeitung eines Status- oder Steuerbytes, das von einem Feldgerät oder einer übergeordneten Steuerung empfangen wurde, um einzelne Statusbits (z.B. "Motor ein", "Ventil offen", "Störung aktiv") separat auszuwerten.
*   **Visualisierung:** Aufbereitung von Daten für Visualisierungssysteme (HMIs), die einzelne Schaltzustände oft als separate boolesche Lampen oder Indikatoren darstellen.
*   **Schnittstelle zu Bit-orientierter Logik:** Bereitstellung einzelner Bits für nachfolgende Funktionsblöcke, die mit boolescher Logik arbeiten (AND, OR, NOT, FlipFlops), anstatt mit ganzen Bytes.

## Vergleich mit ähnlichen Bausteinen
*   **`BYTE_TO_BOOL` (oder ähnlich benannte Blöcke):** Viele Bibliotheken bieten Blöcke an, die ein Byte in acht separate BOOL-Ausgänge konvertieren. `BYTE_TO_ARR08X` unterscheidet sich dadurch, dass es die Bits in einem strukturierten **Array** ausgibt, was die Verkabelung in der 4diac IDE vereinfacht, da nur ein Datenausgang benötigt wird. Die Handhabung in ST-Code ist ebenfalls kompakter.
*   **Bitweises Auslesen mittels `AND` & Vergleichen:** Die gleiche Funktionalität könnte durch eine Reihe von Vergleichen (`(IN AND 16#01) = 1` etc.) erreicht werden. Der `BYTE_TO_ARR08X`-Block kapselt diese Logik in einem wiederverwendbaren, leicht verständlichen Baustein.
*   **Gegenstück `ARR08X_TO_BYTE`:** Ein komplementärer Baustein, der ein Array von acht BOOLs zu einem Byte zusammenfasst, würde die umgekehrte Operation durchführen.

## Fazit
Der `BYTE_TO_ARR08X` Funktionsblock ist ein einfacher, spezialisierter und äußerst praktischer Konvertierungsbaustein. Er löst ein häufiges Problem in der Automatisierungstechnik auf elegante Weise, indem er die Bit-Extraktion aus einem Byte abstrahiert und die Ergebnisse in einem gut handhabbaren Array bereitstellt. Seine deterministische und zustandslose Natur macht ihn zu einem zuverlässigen und performanten Bestandteil für Anwendungen, in denen digitale Bit-Informationen kompakt übertragen und dann dezentral verarbeitet werden müssen.