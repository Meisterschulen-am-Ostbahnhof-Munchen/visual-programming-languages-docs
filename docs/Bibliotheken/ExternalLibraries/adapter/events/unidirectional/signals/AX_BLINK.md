# AX_BLINK

```{index} single: AX_BLINK
```

* * * * * * * * * *
## Einleitung
Der AX_BLINK ist ein Funktionsblock, der ein blinkendes Signal über einen AX-Adapter ausgibt.

![AX_BLINK](AX_BLINK.svg)

## Schnittstellenstruktur

### **Daten-Eingänge**
- **DT** (TIME): Blinkperiode.

### **Adapter**
**Plugs (Ausgänge):**
- **OUT** (adapter::types::unidirectional::AX)

## Funktionsweise
Der Baustein schaltet den Ausgang OUT mit der Periode DT abwechselnd ein und aus.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter.

## Zustandsübersicht
Zustandsbasiert (Blinken).

## Anwendungsszenarien
Blinkende Anzeigen.

## Vergleich mit ähnlichen Bausteinen
- **E_BLINK**: Standard Blink-Baustein.




## Zugehörige Übungen

* [Uebung_020f3_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f3_AX.md)

## Fazit
Adapter-basierter Blink-Baustein.