# AX_TOF

```{index} single: AX_TOF
```

<img width="962" height="255" alt="image" src="https://github.com/user-attachments/assets/b86d8399-ca0b-492c-b20c-52dde7069371" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

Der AX_TOF Funktionsblock ist ein standardmäßiger Timer-Baustein für Ausschaltverzögerungen (Off-Delay Timing). Er realisiert eine Zeitverzögerung beim Abschalten eines Signals und wird über Adapter-Schnittstellen angesteuert.

![AX_TOF](AX_TOF.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **R**: Reset-Ereignis zum Zurücksetzen des Timers

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
- **PT**: TIME - Prozesszeit für die Verzögerung

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden*

### **Adapter**
- **IN** (Socket): Eingangsadapter vom Typ `adapter::types::unidirectional::AX`
  - Ereignis: E1
  - Daten: D1
- **Q** (Plug): Ausgangsadapter vom Typ `adapter::types::unidirectional::AX`
  - Ereignis: E1
  - Daten: D1

## Funktionsweise
Der AX_TOF Block implementiert eine Ausschaltverzögerung (Off-Delay). Bei einem eingehenden Signal über den IN-Adapter wird die Ausgabe sofort aktiviert. Beim Abschalten des Eingangssignals startet der Timer und hält die Ausgabe für die eingestellte Zeit PT aktiv, bevor diese deaktiviert wird.

## Technische Besonderheiten
- Verwendet intern den E_TOF Standard-Timer-Baustein
- Unidirektionale Adapter-Schnittstellen für Ein- und Ausgang
- Reset-Funktionalität zum sofortigen Zurücksetzen des Timers
- Zeitbasis in TIME-Datentyp

## Zustandsübersicht
1. **Ruhezustand**: Kein aktives Signal
2. **Aktiviert**: Eingangssignal vorhanden, Ausgabe aktiv
3. **Verzögerung**: Eingangssignal abgeschaltet, Timer läuft, Ausgabe bleibt aktiv
4. **Abgelaufen**: Timer abgelaufen, Ausgabe deaktiviert

## Anwendungsszenarien
- Steuerung von Ausschaltverzögerungen in industriellen Prozessen
- Sicherheitsfunktionen mit Nachlaufzeiten
- Verzögerte Abschaltung von Motoren oder Aktoren
- Prozesssteuerung mit definierten Ausschaltsequenzen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Timer-Bausteinen bietet AX_TOF:
- Spezialisiert auf Ausschaltverzögerungen
- Adapter-basierte Schnittstelle für modularen Aufbau
- Integrierte Reset-Funktionalität
- Standardisierte TIME-Datentypen

Vergleich mit [E_TOF](../../../../../StandardLibraries/events/timer/E_TOF.md)






## 🛠️ Zugehörige Übungen

* [Uebung_020e_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020e_AX.md)

## Fazit
Der AX_TOF Funktionsblock bietet eine zuverlässige und standardisierte Lösung für Ausschaltverzögerungen in 4diac-basierten Steuerungssystemen. Durch die Verwendung von Adapter-Schnittstellen ermöglicht er eine flexible Integration in komplexere Funktionsbaustein-Netzwerke.