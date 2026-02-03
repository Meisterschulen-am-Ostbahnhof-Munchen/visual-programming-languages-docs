# E_TimeOut

```{index} single: E_TimeOut
```

![E_TimeOut](https://user-images.githubusercontent.com/116869307/214142822-3b167702-112f-454a-a42f-62c5f7454561.png)

* * * * * * * * * *

## Einleitung
Der **E_TimeOut** ist ein standardkonformer Funktionsbaustein (IEC 61499-1) zur Implementierung von Timeout-Services. Version 1.0 bietet eine einfache, aber effektive Timeout-Funktionalität durch interne Nutzung eines E_DELAY-Bausteins. Der **E\_TimeOut** ist ein zusammengesetzter Funktionsblock. Innerhalb des Netzwerks eines zusammengesetzten Funktionsblocks wird jeder Adapter, der zu seiner Schnittstelle hinzugefügt wird, durch einen Adapterblock repräsentiert, der wie ein Funktionsblock aussieht. Die Schnittstellenelemente dieses Adapterblocks sind wie ein Funktionsblock verbunden.

![E_TimeOut](E_TimeOut.svg)

## Schnittstellenstruktur

### **Adapter-Schnittstelle (Socket-Perspektive)**
Der Baustein verwendet einen **Socket** (Buchse) vom Typ `ATimeOut`. Da es sich um einen Socket handelt, sind die Signalrichtungen gegenüber der Adapter-Definition (Plug) invertiert:

- **Eingänge (vom Socket empfangen)**:
  - `START`: Startet den internen Timer.
  - `STOP`: Stoppt den internen Timer.
  - `DT` (TIME): Die zu verwendende Verzögerungszeit.
- **Ausgang (an den Socket gesendet)**:
  - `TimeOut`: Wird nach Ablauf der Zeit an den verbundenen Plug signalisiert.

### **Interne Komponenten**
- `DLY` (E_DELAY): Kernkomponente für die Zeitsteuerung

## Funktionsweise

1. **Timeout-Initialisierung**:
   - Bei `START`-Ereignis am Socket beginnt der Timer mit dem konfigurierten `DT`-Wert.
   - Ein weiteres `START`-Ereignis während der Timer läuft, wird ignoriert.

2. **Timeout-Abbruch**:
   - Ein `STOP`-Ereignis bricht den aktiven Timer sofort ab. Es wird kein `TimeOut`-Ereignis generiert.

3. **Timeout-Auslösung**:
   - Nach Ablauf von `DT` wird das `TimeOut`-Ereignis einmalig generiert.

## Technische Besonderheiten

✔ **Adapter-basierte** Schnittstelle (`ATimeOut`).
✔ **Einfache, nicht-nachtriggerbare Timeout-Logik**.
✔ **Deterministisches** Zeitverhalten.

## Anwendungsszenarien

- **Netzwerkkommunikation**: Überwachung auf eine Antwort innerhalb einer festen Frist. Wenn die Antwort kommt, wird der Timer per `STOP` abgebrochen.
- **Gerätesteuerung**: Einfache Watchdog-Funktionen, die nicht zurückgesetzt werden müssen.
- **Prozessüberwachung**: Sicherstellen, dass ein Prozessschritt eine maximale Dauer nicht überschreitet.

## ⚖️ Vergleich mit E_RTimeOut

| Feature        | E_TimeOut (dieser) | E_RTimeOut |
|---------------|-----------|----------|
| Interner Baustein | E_DELAY | E_RDELAY |
| `START` bei lfd. Timer | Ignoriert | Startet Timer neu |
| Adaptertyp    | ATimeOut  | ARTimeOut |




## 🛠️ Zugehörige Übungen

* [Uebung_035](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035.md)
* [Uebung_035a](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a.md)
* [Uebung_035a1_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a1_AX.md)
* [Uebung_035a2](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_035a2_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a3.md)
* [Uebung_035a3_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_035c](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035c.md)
* [Uebung_036](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_036.md)
* [Uebung_037](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_037.md)
* [Uebung_038](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_038.md)
* [Uebung_038_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_038_AX.md)
* [Uebung_039](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039.md)
* [Uebung_039a](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039a.md)

## Fazit

Der E_TimeOut-Baustein bietet eine robuste Grundimplementierung für nicht-nachtriggerbare Timeout-Anforderungen. Er ist ideal für Fälle, in denen ein Zeitablauf gestartet und entweder bis zum Ende durchlaufen oder explizit abgebrochen werden soll. Für Szenarien, die ein "Nachtriggern" oder Zurücksetzen des Timers erfordern (wie bei einem Watchdog, der periodisch "getreten" wird), ist der `E_RTimeOut`-Baustein die bessere Wahl.