# AX_SPLIT_2

```{index} single: AX_SPLIT_2
```

<img width="711" height="266" alt="image" src="https://github.com/user-attachments/assets/35bdbc21-637d-4e15-9327-20c28f43b4b5" />

* * * * * * * * * *
## Einleitung
Der AX_SPLIT_2 Funktionsblock dient als generischer Baustein zur Verteilung eines AX-Signals auf zwei separate Ausgänge. Der Block ermöglicht die Aufteilung eines eingehenden AX-Signals auf zwei unabhängige Ausgabekanäle.

![AX_SPLIT_2](AX_SPLIT_2.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
**Eingangsadapter:**
- **IN**: AX-Adapter (unidirectional) - Empfängt das eingehende AX-Signal

**Ausgangsadapter:**
- **OUT1**: AX-Adapter (unidirectional) - Erster Ausgangskanal für das verteilte Signal
- **OUT2**: AX-Adapter (unidirectional) - Zweiter Ausgangskanal für das verteilte Signal

## Funktionsweise
Der AX_SPLIT_2 Funktionsblock empfängt ein AX-Signal über den IN-Adapter und verteilt dieses Signal gleichzeitig auf beide Ausgangsadapter OUT1 und OUT2. Es handelt sich um eine 1:2-Verteilung, bei der das eingehende Signal ohne Änderung an beide Ausgänge weitergeleitet wird.

## Technische Besonderheiten
- Generische Implementierung für AX-Signale
- Unidirektionale Signalübertragung
- Keine Signalverzögerung zwischen Ein- und Ausgang
- Gleichzeitige Aktivierung beider Ausgänge

## Zustandsübersicht
Der Funktionsblock arbeitet zustandslos - bei jedem eingehenden Signal über den IN-Adapter werden sofort beide Ausgangsadapter aktiviert.

## Anwendungsszenarien
- Signalverteilung in Steuerungssystemen
- Parallele Versorgung mehrerer Komponenten mit demselben Signal
- Verzweigung von AX-Kommunikationspfaden
- Redundante Signalweiterleitung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Verteilungsbausteinen bietet AX_SPLIT_2 eine spezifische 1:2-Aufteilung für AX-Signale. Andere Splitter-Bausteine könnten unterschiedliche Anzahlen von Ausgängen oder andere Signaltypen unterstützen.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)




## Zugehörige Übungen

* [Uebung_002_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002_AX.md)
* [Uebung_004b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_004b_AX.md)
* [Uebung_004b_AX_ASR](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_004b_AX_ASR.md)
* [Uebung_004b_AX_ASR_X](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_004b_AX_ASR_X.md)
* [Uebung_006a3_sub_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006a3_sub_AX.md)
* [Uebung_007a3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_007a3_AX.md)
* [Uebung_008_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_008_AX.md)
* [Uebung_010c2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c2_AX.md)
* [Uebung_010c3_sub_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c3_sub_AX.md)
* [Uebung_010c4_sub_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c4_sub_AX.md)
* [Uebung_010c_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_010c_AX.md)
* [Uebung_020c3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020c3_AX.md)
* [Uebung_020e2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020e2_AX.md)
* [Uebung_020f2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f2_AX.md)
* [Uebung_020j2_AX_sub](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j2_AX_sub.md)
* [Uebung_020j_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020j_AX.md)
* [Uebung_035a2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_094a_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_094a_AX.md)
* [Uebung_160_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Uebung_160b2_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Uebung_160b_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Fazit
Der AX_SPLIT_2 Funktionsblock stellt eine einfache und effiziente Lösung zur Verteilung von AX-Signalen auf zwei Ausgänge dar. Seine generische Natur und die unidirektionale Architektur machen ihn zu einem vielseitig einsetzbaren Baustein in verteilten Automatisierungssystemen.