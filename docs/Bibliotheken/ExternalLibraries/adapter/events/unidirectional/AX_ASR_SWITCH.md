# AX_ASR_SWITCH / AX_ASR_SWITCH_X

```{index} single: AX_ASR_SWITCH / AX_ASR_SWITCH_X
```

## Einleitung
Diese Funktionsbausteine dienen als Brücke zwischen der datenorientierten AX-Welt und der ereignisorientierten ASR-Welt (Set/Reset). Sie wandeln ein boolesches Signal (verpackt in einen AX-Adapter) in dedizierte `SET` und `RESET` Ereignisse um.

Da die Richtung der Ereignisse (welcher Zustand setzt, welcher löscht) fest im Adapter verdrahtet ist, stehen zwei Varianten zur Verfügung.

![AX_ASR_SWITCH](AX_ASR_SWITCH.svg)

## Varianten

### **AX_ASR_SWITCH** (1:1)
- Eingang `G = TRUE` (1)  ➜  Ausgang `SET`
- Eingang `G = FALSE` (0) ➜  Ausgang `RESET`

### **AX_ASR_SWITCH_X** (Gekreuzt)
- Eingang `G = TRUE` (1)  ➜  Ausgang `RESET`
- Eingang `G = FALSE` (0) ➜  Ausgang `SET`

## Schnittstellenstruktur

### **Adapter**
- **G** (Socket): Eingangsadapter vom Typ `AX`.
- **Q** (Plug): Ausgangsadapter vom Typ `ASR`.

## Funktionsweise
Die Bausteine nutzen intern einen `E_SWITCH`. Jedes Mal, wenn am Eingangsadapter `G` ein Ereignis (`E1`) eintrifft, wird der aktuelle Datenwert (`D1`) geprüft und das entsprechende Ereignis (`SET` oder `RESET`) am Ausgangsadapter `Q` ausgelöst.

## Anwendungsszenarien
- Ansteuerung von bistabilen Bausteinen (Flip-Flops), die einen `ASR`-Eingang besitzen, direkt aus einem `AX`-Signalfluss heraus.
- Vereinfachung von Logikschaltungen, in denen Ereignisse basierend auf einem statischen Signalzustand generiert werden müssen.