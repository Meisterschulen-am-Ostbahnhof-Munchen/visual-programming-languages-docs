# E_SR

```{index} single: E_SR
```
## 🎧 Podcast

* [IEC 61499: Der E_SR-Baustein entschlüsselt – Einfachheit trifft Ereignissteuerung](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/IEC-61499-Der-E_SR-Baustein-entschlsselt--Einfachheit-trifft-Ereignissteuerung-e3682bo)
* [Decoding the E_SR Function Block: The Unsung Hero of Industrial Automation](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Decoding-the-E_SR-Function-Block-The-Unsung-Hero-of-Industrial-Automation-e3681qo)

## Einleitung
Der `E_SR` (Event-driven SR Flip-Flop) ist ein ereignisgesteuerter, bistabiler Funktionsbaustein nach IEC 61499. Er dient als grundlegendes Speicherelement, das durch separate "Set"- und "Reset"-Ereignisse gesteuert wird. Sein Ausgang `Q` behält seinen Zustand bei, bis ein entgegengesetztes Ereignis eintrifft.

![E_SR](E_SR.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge:**
- **S (Set)**: Setzt den Ausgang `Q` auf `TRUE`.
- **R (Reset)**: Setzt den Ausgang `Q` auf `FALSE`.

### **Ereignis-Ausgänge:**
- **EO (Event Output)**: Wird ausgelöst, wenn sich der Zustand von `Q` ändert.
    - **Verbundene Daten**: `Q`

### **Daten-Ausgänge:**
- **Q**: Der aktuelle Zustand des Flip-Flops (Datentyp: `BOOL`).

## Funktionsweise
Der `E_SR`-Baustein funktioniert als einfacher Speicher (Latch):
1.  **Setzen**: Wenn ein Ereignis am Eingang `S` eintrifft, wird der Ausgang `Q` auf `TRUE` gesetzt. Wenn `Q` vorher `FALSE` war, wird das `EO`-Ereignis ausgelöst.
2.  **Zurücksetzen**: Wenn ein Ereignis am Eingang `R` eintrifft, wird der Ausgang `Q` auf `FALSE` gesetzt. Wenn `Q` vorher `TRUE` war, wird das `EO`-Ereignis ausgelöst.
3.  **Speichern**: Zwischen den Ereignissen behält `Q` seinen zuletzt gesetzten Zustand bei.

## Technische Besonderheiten und Normenvergleich

Laut **DIN EN 61499-1 (Tabelle A.1, Anmerkung 8)** ist die Implementierung dieses Funktionsbausteins identisch zum [E_RS](E_RS.md). Beide Bausteine (`E_SR` und `E_RS`) existieren zur Wahrung der Konsistenz mit den Typen der IEC 61131-3, obwohl es in der IEC 61499 keine inhärente "Dominanz" von Ereignissen gibt, wie es bei den pegelgesteuerten Eingängen der klassischen SPS-Programmierung der Fall ist.

- **Vergleich zur IEC 61131-3**: Siehe [SR (Bistabil, vorrangig setzen)](../../Vergleich/IEC61131_3/SR_ALT.md). Während in der IEC 61131-3 der `SR`-Baustein eine definierte "Setz-Dominanz" hat (wenn S und R gleichzeitig TRUE sind, gewinnt S), hängt das Verhalten in der IEC 61499 bei kurz aufeinanderfolgenden Ereignissen von der Abarbeitungsreihenfolge der Laufzeitumgebung (ECC) ab. Da Ereignisse flüchtig sind, gibt es keinen dauerhaften Konflikt zweier statischer Signale.
- **Funktionale Identität**: `E_SR` und `E_RS` unterscheiden sich technisch nicht. Die grafische Darstellung und Benennung lehnt sich lediglich an die Konventionen an, um Entwicklern die Orientierung zu erleichtern.
- **Änderungserkennung**: Der `EO`-Ausgang wird nur bei einer tatsächlichen Zustandsänderung ausgelöst.

## Anwendungsszenarien
- **Start/Stopp-Logik**: Ein "Start"-Taster ist mit `S` verbunden, ein "Stopp"-Taster mit `R`, um den Zustand einer Maschine zu steuern.
- **Fehlerspeicherung**: Ein Fehlerereignis setzt den Baustein (`S`), der den Fehlerzustand speichert, bis er von einem Bediener oder einem anderen Prozess explizit quittiert (`R`) wird.
- **Modus-Speicher**: Speichern des aktuellen Betriebsmodus einer Anlage (z.B. "Hand" vs. "Automatik").

## Verwandte Bausteine
- **[E_RS](E_RS.md)**: Funktional identisch zum `E_SR`. Der einzige Unterschied liegt in der grafischen Anordnung der `S`- und `R`-Anschlüsse am Symbol.
- **`E_D_FF`**: Speichert ebenfalls einen Zustand, aber taktbasiert. `E_D_FF` übernimmt den Wert am `D`-Eingang bei einem `CLK`-Ereignis.






## Zugehörige Übungen

* [Uebung_004b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_004b.md)
* [Uebung_004b2](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_004b2.md)
* [Uebung_004b3](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_004b3.md)
* [Uebung_006](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006.md)
* [Uebung_006c](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006c.md)
* [Uebung_006d](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006d.md)
* [Uebung_007a3](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_007a3.md)
* [Uebung_008](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_008.md)
* [Uebung_009](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_009.md)
* [Uebung_013](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_013.md)
* [Uebung_014](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_014.md)
* [Uebung_015](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_015.md)
* [Uebung_016](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_016.md)
* [Uebung_019b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_019b.md)
* [Uebung_019c](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_019c.md)
* [Uebung_021](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_021.md)
* [Uebung_022](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_022.md)
* [Uebung_023](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_023.md)
* [Uebung_024](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_024.md)
* [Uebung_025](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_025.md)
* [Uebung_026_sub](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_026_sub.md)
* [Uebung_039a_sub_Outputs](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)
* [Uebung_160b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_160b.md)

## Fazit
Der `E_SR`-Baustein ist ein fundamentaler Speicherbaustein in der IEC 61499. Er ist ideal für einfache Zustandspeicherungen, bei denen ein Zustand durch ein Ereignis gesetzt und durch ein anderes explizit zurückgesetzt wird. Das Fehlen einer garantierten Set- oder Reset-Dominanz bei gleichzeitigen Ereignissen muss in kritischen Anwendungen beachtet werden.