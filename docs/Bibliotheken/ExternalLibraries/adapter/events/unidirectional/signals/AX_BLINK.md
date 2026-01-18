# AX_BLINK

```{index} single: AX_BLINK
```

* * * * * * * * * *
## 🎧 Podcast

* [4diac IDE: Dein "Hello World" der Automatisierung – Das Blinking Tutorial Lokal](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)

## Einleitung
Der AX_BLINK ist ein Funktionsblock, der ein blinkendes Signal über einen AX-Adapter ausgibt.

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

## Fazit
Adapter-basierter Blink-Baustein.