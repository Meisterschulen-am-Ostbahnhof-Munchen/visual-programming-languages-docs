# E_F_TRIG

```{index} single: E_F_TRIG
```

![E_F_TRIG Diagram](https://user-images.githubusercontent.com/113907528/204898671-3eb058ff-7481-4fc8-a2d4-8cf50f349cee.png)

* * * * * * * * * *

## Einleitung
Der **E_F_TRIG** (Falling Edge Trigger) ist ein grundlegender Funktionsbaustein der IEC 61499 Norm zur Erkennung von fallenden Signalflanken. Dieser Baustein spielt eine wichtige Rolle in der Ereignisdetektion und Signalverarbeitung industrieller Steuerungssysteme.

![E_F_TRIG](E_F_TRIG.svg)

## Struktur des E_F_TRIG-Bausteins

### Schnittstelle (Interface)

**Ereignis-Eingänge:**
- **EI (Event Input)**: Löst die Prüfung auf eine Flanke aus.
    - **Verbundene Daten**: `QI`

**Ereignis-Ausgänge:**
- **EO (Event Output)**: Wird ausgelöst, wenn eine Flanke erkannt wurde.

**Daten-Eingänge:**
- **QI (Qualifier Input)**: Das zu überwachende boolesche Signal (Datentyp: `BOOL`).

## Funktionsweise
Der `E_F_TRIG` soll eine fallende Flanke am `QI`-Eingang erkennen. Eine fallende Flanke tritt auf, wenn `QI` beim letzten `EI`-Ereignis `TRUE` war und beim aktuellen `EI`-Ereignis `FALSE` ist.

Bei jedem `EI`-Ereignis wird der aktuelle Zustand von `QI` mit dem Zustand aus dem vorherigen Zyklus verglichen. Wenn eine fallende Flanke erkannt wird, sollte das `EO`-Ereignis ausgelöst werden.

**Achtung: Fehlerhafte Implementierung**
Die interne Logik des Bausteins (Stand: `events-3.0.0`) ist fehlerhaft und implementiert tatsächlich einen **steigenden Flankendetektor (`E_R_TRIG`)** anstatt eines fallenden. Das `EO`-Ereignis wird ausgelöst, wenn `QI` von `FALSE` auf `TRUE` wechselt.

## Technische Besonderheiten

✔ **Ereignisgesteuert**: Die Prüfung erfolgt nur, wenn ein `EI`-Ereignis eintritt.
✔ **Fehlerhafte Logik**: Der Baustein ist als `E_F_TRIG` benannt, seine interne Verschaltung eines `E_D_FF` und `E_SWITCH` bewirkt jedoch, dass er auf eine **steigende Flanke** reagiert. Nutzer, die eine fallende Flankenerkennung benötigen, müssen stattdessen den `E_R_TRIG`-Baustein verwenden und dessen Eingang negieren oder auf eine Korrektur des Bausteins warten.

## Anwendungsszenarien (für eine fallende Flanke)

- **Sensordatenauswertung**: Erkennen, wenn ein Sensor von "aktiv" auf "inaktiv" wechselt.
- **Maschinensicherheit**: Detektion, wenn ein Schutzkontakt von "geschlossen" (TRUE) auf "offen" (FALSE) geht.
- **Prozessüberwachung**: Erkennen des Endes eines Signals oder Prozesses.

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | E_F_TRIG (dieser) | E_R_TRIG | E_SWITCH |
|---------------|------------------|----------|----------|
| Erkannte Flanke | Fallend (benannt), Steigend (implementiert) | Steigend | - |
| Ereignissteuerung | Ja     | Ja       | Ja       |
| Prinzip | Flankendetektor | Flankendetektor | Ereignisweiche |






## 🛠️ Zugehörige Übungen

* [Uebung_088](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_088.md)

## Fazit

Der E_F_TRIG-Baustein ist dazu gedacht, fallende Flanken zu erkennen, was ein häufiger Anwendungsfall in der Steuerungstechnik ist. **Aufgrund eines Implementierungsfehlers in der `events-3.0.0`-Bibliothek funktioniert dieser Baustein jedoch als Detektor für steigende Flanken.** Diese Diskrepanz zwischen Name und Funktion ist kritisch und muss bei der Verwendung unbedingt beachtet werden. Für eine zuverlässige Erkennung fallender Flanken sollte auf alternative Logiken zurückgegriffen werden.