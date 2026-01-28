# AX_PULSE

```{index} single: AX_PULSE
```

* * * * * * * * * *
## Einleitung
**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

Der AX_PULSE ist ein Funktionsblock, der einen Impuls über einen AX-Adapter ausgibt.

![AX_PULSE](AX_PULSE.svg)

## Schnittstellenstruktur

### **Adapter**
**Sockets (Eingänge):**
- **REQ** (adapter::types::unidirectional::AX): Trigger.

**Plugs (Ausgänge):**
- **PULSE** (adapter::types::unidirectional::AX): Impulsausgang.

## Funktionsweise
Bei REQ wird PULSE kurzzeitig aktiv.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter.

## Zustandsübersicht
Impuls.

## Anwendungsszenarien
Signalisierung.

## Vergleich mit ähnlichen Bausteinen
- **E_PULSE**



## Zugehörige Übungen

* [Uebung_020h_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020h_AX.md)
* [Uebung_020i_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020i_AX.md)

## Fazit
Adapter-basierter Impuls-Baustein.