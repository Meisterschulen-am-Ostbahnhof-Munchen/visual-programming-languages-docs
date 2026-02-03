# AX_SPLIT_3

```{index} single: AX_SPLIT_3
```

<img width="711" height="299" alt="image" src="https://github.com/user-attachments/assets/79f5b696-e66f-481a-8642-b19ac2f35cb4" />

* * * * * * * * * *
## Einleitung
Der AX_SPLIT_3 ist ein generischer Funktionsblock, der einen AX-Adapter-Eingang auf drei separate AX-Adapter-Ausgänge aufteilt. Der Baustein ermöglicht die Verteilung eines eingehenden AX-Signals an drei verschiedene Empfänger innerhalb eines 4diac-Systems.

![AX_SPLIT_3](AX_SPLIT_3.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
**Eingangsadapter:**
- **IN** - AX-Adapter (Socket) - Empfängt das eingehende AX-Signal

**Ausgangsadapter:**
- **OUT1** - AX-Adapter (Plug) - Erster Ausgangskanal
- **OUT2** - AX-Adapter (Plug) - Zweiter Ausgangskanal
- **OUT3** - AX-Adapter (Plug) - Dritter Ausgangskanal

## Funktionsweise
Der Funktionsblock arbeitet als Signalverteiler für unidirektionale AX-Adapter. Jedes eingehende Signal am IN-Adapter wird parallel an alle drei Ausgangsadapter (OUT1, OUT2, OUT3) weitergeleitet. Die Verteilung erfolgt synchron, sodass alle Ausgänge gleichzeitig aktiviert werden.

## Technische Besonderheiten
- Verwendet unidirektionale AX-Adapter für die Kommunikation
- Implementiert als generischer Funktionsblock (GEN_AX_SPLIT)
- Keine Ereignis- oder Dateneingänge - arbeitet ausschließlich über Adapter
- Plug-and-Socket Architektur gemäß IEC 61499 Standard

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustand: Im Betriebszustand leitet er eingehende Signale unverändert an alle drei Ausgänge weiter. Es gibt keine internen Zustandsübergänge oder Verzögerungen.

## Anwendungsszenarien
- Verteilung von Steuersignalen an mehrere Aktoren
- Parallele Ansteuerung mehrerer Geräte mit demselben Signal
- Signalverzweigung in komplexen Steuerungsarchitekturen
- Redundante Signalverteilung für Sicherheitsanwendungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Verteilungsbausteinen zeichnet sich AX_SPLIT_3 durch seine spezifische Ausrichtung auf AX-Adapter aus. Während allgemeine Verteilungsbausteine verschiedene Adaptertypen unterstützen können, ist dieser Baustein speziell für AX-Adapter optimiert.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)






## 🛠️ Zugehörige Übungen

* [Uebung_002a5b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a5b_AX.md)
* [Uebung_006a3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006a3_AX.md)
* [Uebung_009_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_009_AX.md)

## Fazit
Der AX_SPLIT_3 bietet eine einfache und effiziente Lösung zur Signalverteilung in 4diac-Systemen. Seine generische Implementierung und standardkonforme Adapter-Schnittstelle machen ihn zu einem vielseitig einsetzbaren Baustein für verschiedene Automatisierungsanwendungen.