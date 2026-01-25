# E_RDELAY

```{index} single: E_RDELAY
```

![E_RDELAY Symbol](https://user-images.githubusercontent.com/113907528/204900519-829582bd-d9f3-4bee-934a-15dc393b4c34.png)
* * * * * * * * * *

## Einleitung
Der **E_RDELAY** (Reloadable Delay) ist ein erweiterter Verzögerungsbaustein nach IEC 61499, der im Gegensatz zum einfachen E_DELAY eine nachladbare und abbrechbare Ereignisverzögerung ermöglicht. Entwickelt unter EPL-2.0 Lizenz.

![E_RDELAY](E_RDELAY.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START`: Beginnt/Resetet die Verzögerung (mit DT-Parameter)
- `STOP`: Bricht die aktive Verzögerung ab

### **Ereignis-Ausgänge**
- `EO`: Verzögertes Ausgangsereignis

### **Daten-Eingänge**
- `DT` (Delay Time): Verzögerungsdauer (TIME-Datentyp)

## Funktionsprinzip

1. **Verzögerungsstart**:
   - Bei `START`-Ereignis beginnt Timer mit konfigurierter `DT`-Zeit
   - Neues `START` während aktiver Verzögerung resetet den Timer

2. **Verzögerungsabbruch**:
   - `STOP` bricht aktive Verzögerung sofort ab
   - Kein `EO`-Ereignis wird generiert

3. **Verzögerungsabschluss**:
   - Nach exakt `DT` wird `EO` einmalig ausgelöst
   - Bei DT ≤ T#0s sofortige Auslösung

## Service-Sequenzen (laut XML-Spezifikation)

1. **event_delay**:
   - Normale Verzögerung mit START → EO

2. **delay_canceled**:
   - START gefolgt von STOP (kein EO)

3. **no_multiple_delay**:
   - Mehrfaches START löst nur ein EO aus

## Technische Besonderheiten

✔ **Nachladbare Verzögerung** (Reset-Funktion)
✔ **Abbruchfähig** während der Laufzeit
✔ **Deterministisches Zeitverhalten**
✔ **Echtzeitfähige** Implementierung

## Anwendungsszenarien

- **Maschinensicherheit**: Verzögerte Abschaltsequenzen
- **Prozesssteuerung**: Zeitgesteuerte Zustandsübergänge
- **Alarmsysteme**: Störmeldungsverzögerung
- **Robotersteuerung**: Bewegungsablauf-Timing

## Vergleich mit E_DELAY

| Feature        | E_RDELAY | E_DELAY |
|---------------|----------|---------|
| Reset-Funktion | ✔️ (durch START) | ❌ |
| Mehrfach-Trigger | Nur 1 EO | Nur 1 EO |
| Service-Sequenzen | 3 definiert | 1 definiert |

## Fazit

Der E_RDELAY-Baustein erweitert die klassische Verzögerungsfunktion um wesentliche industrietaugliche Features:

- Flexible Neukonfiguration während des Betriebs
- Sichere Abbruchmöglichkeit von Zeitabläufen
- Standardisierte Service-Schnittstellen

Durch die XML-basierte Spezifikation ist der Baustein besonders gut für den Einsatz in verteilten Steuerungssystemen geeignet. Die implementierte Version bietet zuverlässige Zeitsteuerung für kritische Automatisierungsprozesse.