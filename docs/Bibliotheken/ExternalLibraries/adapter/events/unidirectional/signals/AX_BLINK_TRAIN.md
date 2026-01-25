# AX_BLINK_TRAIN

```{index} single: AX_BLINK_TRAIN
```

* * * * * * * * * *
## Einleitung
Der AX_BLINK_TRAIN ist ein Funktionsblock, der ein Zug-Blinksignal (abwechselnd zwei Lampen) über AX-Adapter ausgibt.

![AX_BLINK_TRAIN](AX_BLINK_TRAIN.svg)

## Schnittstellenstruktur

### **Daten-Eingänge**
- **DT** (TIME): Blinkperiode.

### **Adapter**
**Plugs (Ausgänge):**
- **OUT1** (adapter::types::unidirectional::AX)
- **OUT2** (adapter::types::unidirectional::AX)

## Funktionsweise
Der Baustein schaltet die Ausgänge OUT1 und OUT2 abwechselnd mit der Periode DT ein und aus.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter.

## Zustandsübersicht
Zustandsbasiert.

## Anwendungsszenarien
Bahnübergänge, Warnsignale.

## Vergleich mit ähnlichen Bausteinen
- Keine direkte Standard-Entsprechung.

## Fazit
Adapter-basierter Zug-Blink-Baustein.