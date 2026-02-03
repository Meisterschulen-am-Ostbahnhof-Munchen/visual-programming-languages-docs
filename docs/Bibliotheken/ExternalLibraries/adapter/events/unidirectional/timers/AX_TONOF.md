# AX_TONOF

```{index} single: AX_TONOF
```

<img width="1154" height="290" alt="image" src="https://github.com/user-attachments/assets/eecdf987-773b-4d5a-9da7-7ba858235b94" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

Der AX_TONOF ist ein standardisierter Timer-Funktionsblock, der sowohl Ein- als auch Ausschaltverzögerungen realisiert. Dieser Baustein kombiniert die Funktionalitäten eines Einschaltverzögerungs- und Ausschaltverzögerungs-Timers in einer kompakten Lösung.

![AX_TONOF](AX_TONOF.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **R**: Reset-Ereignis zum Zurücksetzen des Timers

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
- **PT_ON**: TIME - Prozesszeit für die Einschaltverzögerung
- **PT_OFF**: TIME - Prozesszeit für die Ausschaltverzögerung

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden*

### **Adapter**
- **IN**: Eingangsadapter (Socket) für Steuersignale
- **Q**: Ausgangsadapter (Plug) für Statusausgaben

## Funktionsweise
Der AX_TONOF-Funktionsblock verarbeitet Eingangssignale über den IN-Adapter und wendet je nach Signalzustand die konfigurierten Verzögerungszeiten an. Bei aktivem Eingangssignal wird die PT_ON-Verzögerung berücksichtigt, bei inaktivem Signal die PT_OFF-Verzögerung. Das Ergebnis wird über den Q-Adapter ausgegeben.

## Technische Besonderheiten
- Unterstützt bidirektionale Zeitverzögerungen (Ein- und Ausschaltverzögerung)
- Integrierte Reset-Funktionalität
- Verwendet Adapter für Ein- und Ausgänge statt direkter Schnittstellen
- Basierend auf dem E_TONOF-Kernbaustein

## Zustandsübersicht
Der Funktionsblock kann folgende Zustände annehmen:
- **Ruhezustand**: Keine aktive Zeitmessung
- **Einschaltverzögerung**: Zeitmessung für PT_ON aktiv
- **Ausschaltverzögerung**: Zeitmessung für PT_OFF aktiv
- **Reset-Zustand**: Alle aktiven Zeitmessungen werden abgebrochen

## Anwendungsszenarien
- Motorsteuerungen mit Anlauf- und Stoppverzögerung
- Beleuchtungssteuerung mit Ein-/Ausschaltverzögerung
- Prozesssteuerungen mit zeitlich gestaffelten Schaltvorgängen
- Sicherheitsrelevante Anwendungen mit verzögerten Reaktionen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Timer-Bausteinen wie TON oder TOF bietet AX_TONOF die kombinierte Funktionalität beider Timer-Typen in einem Baustein. Die Verwendung von Adaptern anstelle direkter Ein-/Ausgänge ermöglicht eine flexiblere Integration in komplexere Steuerungsstrukturen.

Vergleich mit [E_TONOF](../../../../../StandardLibraries/events/timer/E_TONOF.md)






## Zugehörige Übungen

* [Uebung_020g_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020g_AX.md)

## Fazit
Der AX_TONOF stellt einen vielseitigen Timer-Baustein dar, der durch seine kombinierte Ein-/Ausschaltverzögerungsfunktionalität und die Adapter-basierte Schnittstellengestaltung besonders für modulare Steuerungsarchitekturen geeignet ist. Die integrierte Reset-Funktion erhöht die Flexibilität in praktischen Anwendungen.