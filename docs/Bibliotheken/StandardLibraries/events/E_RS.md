# E_RS

```{index} single: E_RS
```
## Einleitung
Der `E_RS` (Event-driven RS Flip-Flop) ist ein ereignisgesteuerter, bistabiler Funktionsbaustein nach IEC 61499. Er dient als grundlegendes Speicherelement, das durch separate "Set"- und "Reset"-Ereignisse gesteuert wird. Sein Ausgang `Q` behält seinen Zustand bei, bis ein entgegengesetztes Ereignis eintrifft.

![E_RS](E_RS.svg)

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
Der `E_RS`-Baustein funktioniert als einfacher Speicher (Latch):
1.  **Setzen**: Wenn ein Ereignis am Eingang `S` eintrifft, wird der Ausgang `Q` auf `TRUE` gesetzt. Wenn `Q` vorher `FALSE` war, wird das `EO`-Ereignis ausgelöst.
2.  **Zurücksetzen**: Wenn ein Ereignis am Eingang `R` eintrifft, wird der Ausgang `Q` auf `FALSE` gesetzt. Wenn `Q` vorher `TRUE` war, wird das `EO`-Ereignis ausgelöst.
3.  **Speichern**: Zwischen den Ereignissen behält `Q` seinen zuletzt gesetzten Zustand bei.

## Technische Besonderheiten und Normenvergleich

Laut **DIN EN 61499-1 (Tabelle A.1, Anmerkung 8)** ist die Implementierung dieses Funktionsbausteins identisch zum [E_SR](E_SR.md). Beide Bausteine (`E_RS` und `E_SR`) existieren zur Wahrung der Konsistenz mit den Typen der IEC 61131-3, obwohl es in der IEC 61499 keine inhärente "Dominanz" von Ereignissen gibt, wie es bei den pegelgesteuerten Eingängen der klassischen SPS-Programmierung der Fall ist.

- **Vergleich zur IEC 61131-3**: Siehe [RS (Bistabil, vorrangig rücksetzen)](../../Vergleich/IEC61131_3/RS_ALT.md). Während in der IEC 61131-3 der `RS`-Baustein eine definierte "Rücksetz-Dominanz" hat (wenn R und S gleichzeitig TRUE sind, gewinnt R), hängt das Verhalten in der IEC 61499 bei kurz aufeinanderfolgenden Ereignissen von der Abarbeitungsreihenfolge der Laufzeitumgebung (ECC) ab. Da Ereignisse flüchtig sind, gibt es keinen dauerhaften Konflikt zweier statischer Signale.
- **Funktionale Identität**: `E_RS` und `E_SR` unterscheiden sich technisch nicht. Die grafische Darstellung und Benennung lehnt sich lediglich an die Konventionen an, um Entwicklern die Orientierung zu erleichtern.
- **Änderungserkennung**: Der `EO`-Ausgang wird nur bei einer tatsächlichen Zustandsänderung ausgelöst.

## Anwendungsszenarien
- **Start/Stopp-Logik**: Ein "Start"-Taster ist mit `S` verbunden, ein "Stopp"-Taster mit `R`, um den Zustand einer Maschine zu steuern.
- **Fehlerspeicherung**: Ein Fehlerereignis setzt den Baustein (`S`), der den Fehlerzustand speichert, bis er von einem Bediener oder einem anderen Prozess explizit quittiert (`R`) wird.
- **Modus-Speicher**: Speichern des aktuellen Betriebsmodus einer Anlage (z.B. "Hand" vs. "Automatik").

## Verwandte Bausteine
- **[E_SR](E_SR.md)**: Funktional identisch zum `E_RS`, mit vertauschten Eingängen im Symbol.
- **`E_D_FF`**: Taktbasierter Speicher (Data Latch). `E_D_FF` übernimmt den Wert am `D`-Eingang bei einem `CLK`-Ereignis.



## Zugehörige Übungen

* [Uebung_006b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006b.md)
* [Uebung_020a](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020a.md)
* [Uebung_020b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020b.md)
* [Uebung_020d](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020d.md)

## Fazit
Der `E_RS`-Baustein ist ein fundamentaler Speicherbaustein in der IEC 61499. Er ist ideal für einfache Zustandspeicherungen, bei denen ein Zustand durch ein Ereignis gesetzt und durch ein anderes explizit zurückgesetzt wird. Das Fehlen einer garantierten Set- oder Reset-Dominanz bei gleichzeitigen Ereignissen muss in kritischen Anwendungen beachtet werden.