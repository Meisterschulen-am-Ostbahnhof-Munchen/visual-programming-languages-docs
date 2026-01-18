# AX_ASR_SWITCH / AX_ASR_SWITCH_X

```{index} single: AX_ASR_SWITCH / AX_ASR_SWITCH_X
```

## 🎧 Podcast

* [E_SWITCH: Die Weiche der Automatisierung – Warum Einfachheit IEC 61499 revolutioniert](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_SWITCH-Die-Weiche-der-Automatisierung--Warum-Einfachheit-IEC-61499-revolutioniert-e3681fl)
* [E_SWITCH: The Unsung Hero of Industrial Automation's Modular Design](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/E_SWITCH-The-Unsung-Hero-of-Industrial-Automations-Modular-Design-e367npq)
* [Unpacking E_T_FF_SR: The Secret Toggle Switch of Industrial Control Systems](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Unpacking-E_T_FF_SR-The-Secret-Toggle-Switch-of-Industrial-Control-Systems-e367ntv)

## 📺 Video

* [Ereignisschalter E_SWITCH aus der IEC 61499 (Übung 86)](https://www.youtube.com/watch?v=Gev-kGR4-Tc)

## Einleitung
Diese Funktionsbausteine dienen als Brücke zwischen der datenorientierten AX-Welt und der ereignisorientierten ASR-Welt (Set/Reset). Sie wandeln ein boolesches Signal (verpackt in einen AX-Adapter) in dedizierte `SET` und `RESET` Ereignisse um.

Da die Richtung der Ereignisse (welcher Zustand setzt, welcher löscht) fest im Adapter verdrahtet ist, stehen zwei Varianten zur Verfügung.

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