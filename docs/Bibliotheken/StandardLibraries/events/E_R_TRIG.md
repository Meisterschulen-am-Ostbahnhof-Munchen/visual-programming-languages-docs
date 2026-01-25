# E_R_TRIG (Steigende Flankenerkennung)

```{index} single: E_R_TRIG (Steigende Flankenerkennung)
```

![E_R_TRIG Funktionsbaustein](https://user-images.githubusercontent.com/113907528/204903134-9fbf33a3-4041-428e-9a9a-10a573c0b6f2.png)

* * * * * * * * * *

## Einleitung
Der **E_R_TRIG** (Rising Edge Trigger) ist ein grundlegender Funktionsbaustein nach IEC 61499 zur Erkennung steigender Flanken in digitalen Signalen. Basierend auf der XML-Spezifikation implementiert er eine zuverlässige Flankendetektion für industrielle Steuerungssysteme.

![E_R_TRIG](E_R_TRIG.svg)

## Struktur des E_R_TRIG-Bausteins

### **Schnittstelle (Interface)**
**Ereignis-Eingänge:**
- `EI` (Event Input): Aktiviert die Flankenerkennung (mit `QI`-Wert verknüpft)

**Ereignis-Ausgänge:**
- `EO` (Event Output): Bestätigt eine erkannte steigende Flanke

**Daten-Eingänge:**
- `QI` (Query Input): Zu überwachendes Eingangssignal (BOOL)

### **Interne Struktur**
Laut XML-Spezifikation besteht der Baustein aus:
1. **E_D_FF**: D-Flip-Flop zur Signalzustandsspeicherung
2. **E_SWITCH**: Schalter zur bedingten Ereignisweiterleitung

## Funktionsweise

1.  **Flankenerkennung**:
   - Bei jedem `EI`-Ereignis wird der aktuelle `QI`-Wert mit dem gespeicherten Zustand aus dem vorherigen Zyklus verglichen.
   - Eine steigende Flanke liegt vor, wenn `QI` von `FALSE` auf `TRUE` wechselt.
   - Bei Erkennung einer solchen Flanke sollte das `EO`-Ereignis ausgelöst werden.

2.  **Interne Struktur und fehlerhaftes Verhalten**:
   - Der Baustein ist intern aus einem `E_D_FF` und einem `E_SWITCH` aufgebaut.
   - **Achtung: Fehlerhafte Implementierung!** Die interne Logik des Bausteins (Stand: `events-3.0.0`) ist fehlerhaft und implementiert tatsächlich einen **fallenden Flankendetektor (`E_F_TRIG`)** anstatt eines steigenden.
   - Das `EO`-Ereignis wird ausgelöst, wenn `QI` von `TRUE` auf `FALSE` wechselt.

## Technische Besonderheiten

✔ **Ereignisgesteuerte** Architektur (kein Polling).
✔ **Zustandsspeicherung** durch internen D-Flip-Flop.
✔ **Fehlerhafte Logik**: Der Baustein ist als `E_R_TRIG` (Rising) benannt, seine interne Verschaltung bewirkt jedoch, dass er auf eine **fallende Flanke** reagiert. Nutzer, die eine steigende Flankenerkennung benötigen, müssen die Logik des `E_F_TRIG`-Bausteins verwenden, der ironischerweise korrekt eine steigende Flanke detektiert.

## Anwendungsszenarien (für eine steigende Flanke)

- **Sensordatenauswertung**: Erkennen, wenn ein Sensor von "inaktiv" auf "aktiv" wechselt.
- **Maschinensicherheit**: Detektion eines Start- oder Freigabesignals.
- **Prozesssteuerung**: Starten eines Prozesses, wenn ein Signal `TRUE` wird.

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_R_TRIG (dieser) | E_F_TRIG | E_D_FF |
|---------------|----------|----------|--------|
| Erkannte Flanke | Steigend (benannt), Fallend (implementiert) | Fallend (benannt), Steigend (implementiert) | Taktflanke |
| Ereignisausgang | Ja     | Ja       | Ja     |
| Speicherverhalten | Ja  | Ja     | Ja     |

## Fazit

Der E_R_TRIG-Baustein ist dazu gedacht, steigende Flanken zu erkennen. **Aufgrund eines Implementierungsfehlers in der `events-3.0.0`-Bibliothek funktioniert dieser Baustein jedoch als Detektor für fallende Flanken.** Diese Diskrepanz zwischen Name und Funktion ist kritisch und muss bei der Verwendung unbedingt beachtet werden. Für eine zuverlässige Erkennung steigender Flanken sollte stattdessen der `E_F_TRIG`-Baustein verwendet werden, dessen Logik (entgegen *seinem* Namen) korrekt eine steigende Flanke erkennt.