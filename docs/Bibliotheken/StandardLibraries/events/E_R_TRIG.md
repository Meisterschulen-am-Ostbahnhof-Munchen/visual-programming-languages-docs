# E_R_TRIG (Steigende Flankenerkennung)

![E_R_TRIG Funktionsbaustein](https://user-images.githubusercontent.com/113907528/204903134-9fbf33a3-4041-428e-9a9a-10a573c0b6f2.png)

* * * * * * * * * *

## Einleitung
Der **E_R_TRIG** (Rising Edge Trigger) ist ein grundlegender Funktionsbaustein nach IEC 61499 zur Erkennung steigender Flanken in digitalen Signalen. Basierend auf der XML-Spezifikation implementiert er eine zuverlässige Flankendetektion für industrielle Steuerungssysteme.

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

1. **Flankenerkennung**:
   - Bei jedem `EI`-Ereignis wird der aktuelle `QI`-Wert mit dem gespeicherten Zustand verglichen
   - Eine steigende Flanke liegt vor bei Wechsel von FALSE auf TRUE

2. **Ereignisgenerierung**:
   - Bei erkanntem Flankenwechsel wird `EO` ausgelöst
   - Der interne D-Flip-Flop speichert den neuen Zustand

3. **Signalverarbeitung**:
   - Die XML-Spezifikation zeigt die interne Verknüpfung von `E_D_FF` und `E_SWITCH`
   - `E_D_FF` speichert den Zustand, `E_SWITCH` leitet das Ereignis weiter

## Technische Besonderheiten

✔ **Präzise Flankendetektion** im Nanosekundenbereich  
✔ **Ereignisgesteuerte** Architektur (kein Polling)  
✔ **Zustandsspeicherung** zwischen den Aufrufen  
✔ **Echtzeitfähige** Verarbeitung  

## Anwendungsszenarien

- **Sensordatenauswertung**: Erkennung von Schaltvorgängen
- **Maschinensicherheit**: Detektion von Aktivierungssignalen
- **Prozesssteuerung**: Synchronisation von Zustandsübergängen
- **Taktgenerierung**: Erzeugung von Steuerimpulsen

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_R_TRIG | E_F_TRIG | E_D_FF |
|---------------|----------|----------|--------|
| Flankentyp    | Steigend | Fallend  | Taktflanke |
| Ereignisausgang | Ja     | Ja       | Ja     |
| Speicherverhalten | Nein  | Nein     | Ja     |

## Fazit

Der E_R_TRIG-Baustein bietet eine robuste Lösung für Flankendetektionsaufgaben in industriellen Steuerungssystemen. Seine wesentlichen Vorteile sind:

- Zuverlässige Erkennung steigender Flanken
- Hardwarenahe Abbildung der Logikfunktionen
- Standardkonforme Implementierung nach IEC 61499

Durch die klare interne Struktur und das deterministische Verhalten eignet er sich besonders für sicherheitskritische Anwendungen und präzise Steuerungsaufgaben. Die XML-Beschreibung ermöglicht zudem eine einfache Integration in verschiedene Entwicklungsumgebungen.