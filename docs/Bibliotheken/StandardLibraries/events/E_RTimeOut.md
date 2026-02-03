# E_RTimeOut (Resettable Timeout Service)

```{index} single: E_RTimeOut (Resettable Timeout Service)
```

![IEC 61499 Timeout Symbol](https://user-images.githubusercontent.com/113907528/204902807-7fadcd7d-d6e1-47c0-812e-f5c2d80f79e0.png)

* * * * * * * * * *

## Einleitung
Der **E_RTimeOut** ist ein spezieller Funktionsbaustein nach IEC 61499-2. Er implementiert einen resettablen Timeout-Service durch interne Verwendung eines E_RDELAY-Bausteins.

![E_RTimeOut](E_RTimeOut.svg)

## Struktur und Schnittstellen

### **Adapter-Schnittstelle (Socket-Perspektive)**
Der Baustein verwendet einen **Socket** (Buchse) vom Typ `ARTimeOut`. Da es sich um einen Socket handelt, sind die Signalrichtungen gegenüber der Adapter-Definition (Plug) invertiert:

- **Eingänge (vom Socket empfangen)**:
  - `START`: Startet oder resetet den internen Timer.
  - `STOP`: Stoppt den internen Timer.
  - `DT` (TIME): Die zu verwendende Verzögerungszeit.
- **Ausgang (an den Socket gesendet)**:
  - `TimeOut`: Wird nach Ablauf der Zeit an den verbundenen Plug signalisiert.

### **Interne Komponenten**
- `DLY` (E_RDELAY): Kernkomponente für die Zeitsteuerung

## Funktionsweise

1. **Timeout-Initialisierung**:
   - Bei `START`-Ereignis am Socket beginnt der Timer
   - Verwendet den konfigurierten `DT`-Wert

2. **Timeout-Reset**:
   - Neues `START`-Ereignis resetet den laufenden Timer
   - Verwendet den neuen `DT`-Wert

3. **Timeout-Abbruch**:
   - `STOP`-Ereignis bricht aktiven Timer ab

4. **Timeout-Auslösung**:
   - Nach Ablauf von `DT` wird `TimeOut`-Ereignis generiert
   - Signalisiert über den Adapter-Socket

## Technische Besonderheiten

✔ **Resettbare Timeout-Funktion**
✔ **Adapter-basierte Schnittstelle** (ARTimeOut)
✔ **Interne E_RDELAY-Implementierung**
✔ **IEC 61499-2 konform**

## Anwendungsszenarien

- **Netzwerkkommunikation**: Antwort-Timeout-Überwachung
- **Maschinensicherheit**: Überwachung von Bewegungszeiträumen
- **Prozesssteuerung**: Zeitbegrenzte Operationskontrolle
- **Gerätesteuerung**: Watchdog-Funktionalität

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | E_RTimeOut | E_DELAY | E_TABLE |
|---------------|------------|---------|---------|
| Reset-Funktion | ✔️        | ❌      | ❌      |
| Schnittstelle | Adapter    | Direkt  | Direkt  |
| Standard      | 61499-2    | 61499-1 | 61499-1 |




## 🛠️ Zugehörige Übungen

* [Uebung_035b](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035b.md)
* [Uebung_170](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_170.md)

## Fazit

Der E_RTimeOut-Baustein bietet eine elegante Lösung für Timeout-Anforderungen in verteilten Steuerungssystemen:

- Wiederverwendbare Adapter-Schnittstelle
- Flexible Timeout-Konfiguration
- Zuverlässige Reset-Funktionalität

Durch die interne Nutzung des E_RDELAY-Bausteins kombiniert er präzise Zeitsteuerung mit robuster Architektur. Die standardisierte Implementierung nach IEC 61499-2 macht ihn besonders geeignet für interoperable Automatisierungslösungen.