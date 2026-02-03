# AX_TP

```{index} single: AX_TP
```

<img width="915" height="258" alt="image" src="https://github.com/user-attachments/assets/650ebf90-0b85-464b-a6bb-79536b7a5119" />

* * * * * * * * * *
## Einleitung
**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

Der AX_TP ist ein standardisierter Timer-Funktionsblock vom Typ "Pulse" (Impuls), der in 4diac-IDE Anwendungen verwendet wird. Dieser Baustein erzeugt einen zeitgesteuerten Impulsausgang basierend auf einem konfigurierbaren Zeitintervall.

![AX_TP](AX_TP.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **R**: Reset-Ereignis - Setzt den Timer zurück

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **PT**: TIME - Pulszeit (Impulsdauer)

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **IN**: Eingangsadapter (Socket) - Empfängt Eingangsereignisse und -daten
- **Q**: Ausgangsadapter (Plug) - Sendet Ausgangsereignisse und -daten

## Funktionsweise
Der AX_TP-Funktionsblock arbeitet als Impulsgeber (Pulse Timer). Bei Empfang eines Ereignisses über den IN-Adapter wird ein zeitgesteuerter Impuls generiert, dessen Dauer durch den PT-Eingang definiert wird. Der Reset-Eingang (R) ermöglicht das vorzeitige Zurücksetzen des Timers. Der interne E_TP-Funktionsblock übernimmt die eigentliche Timer-Funktionalität.

## Technische Besonderheiten
- Verwendet den standardisierten E_TP-Timerbaustein als Kernkomponente
- Implementiert über Adapter-Schnittstellen für modulare Anbindung
- Unterstützt TIME-Datentyp für Pulszeitkonfiguration
- Bietet separate Reset-Funktionalität

## Zustandsübersicht
Der Funktionsblock verfügt über folgende Betriebszustände:
- **Inaktiv**: Kein aktiver Timer
- **Aktiv**: Timer läuft mit konfigurierter Pulszeit
- **Reset**: Timer wurde zurückgesetzt

## Anwendungsszenarien
- Zeitgesteuerte Steuerungsabläufe
- Impulserzeugung für Aktoren
- Verzögerungsschaltungen
- Prozesssteuerung mit definierten Zeitintervallen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Timer-Bausteinen bietet AX_TP:
- Adapter-basierte Schnittstelle für bessere Modularität
- Explizite Reset-Funktionalität
- Standardisierte Puls-Timer-Implementierung

Vergleich mit [E_TP](../../../../../StandardLibraries/events/timer/E_TP.md)






## 🛠️ Zugehörige Übungen

* [Uebung_020f_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f_AX.md)
* [Uebung_020j2_AX_sub](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j2_AX_sub.md)
* [Uebung_020j_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j_AX.md)
* [Uebung_177_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_177_AX.md)
* [Uebung_178_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_178_AX.md)

## Fazit
Der AX_TP ist ein robuster und standardkonformer Timer-Funktionsblock, der sich ideal für zeitgesteuerte Anwendungen in verteilten Automatisierungssystemen eignet. Seine Adapter-basierte Architektur ermöglicht flexible Integration in komplexere Steuerungsstrukturen.