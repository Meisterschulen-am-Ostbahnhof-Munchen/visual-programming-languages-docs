# AX_BLINK_TRAIN

```{index} single: AX_BLINK_TRAIN
```

* * * * * * * * * *
## 🎧 Podcast

* [4diac IDE: Dein "Hello World" der Automatisierung – Das Blinking Tutorial Lokal](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)

## 📺 Video

* [2025-12-14 19-53-53 Installation Eclipse 4diac™ IDE 3.0.0 und Import des Training1 Projektes](https://www.youtube.com/watch?v=O3S1o_NUyvc)
* [2025-12-14 20-03-27 Aufspielen Training 1 Übung 1 auf das Hutschienenmoped.](https://www.youtube.com/watch?v=6iog7-DZvW0)

## Einleitung
Der AX_BLINK_TRAIN ist ein Funktionsblock, der ein Zug-Blinksignal (abwechselnd zwei Lampen) über AX-Adapter ausgibt.

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