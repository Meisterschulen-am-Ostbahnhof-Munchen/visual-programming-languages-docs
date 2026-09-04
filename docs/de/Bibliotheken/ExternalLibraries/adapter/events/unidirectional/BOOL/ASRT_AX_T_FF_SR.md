# ASRT_AX_T_FF_SR

![ASRT_AX_T_FF_SR](ASRT_AX_T_FF_SR.svg)

* * * * * * * * * *

## Einleitung

Der ASRT_AX_T_FF_SR ist ein ereignisgesteuerter bistabiler Funktionsblock mit Toggle-Funktionalität – die direkte Entsprechung von [AX_T_FF_SR](AX_T_FF_SR.md), bei der die drei Ereigniseingänge S/R/CLK zu einem einzigen unidirektionalen **ASRT-Socket** (Set/Reset/Toggle) zusammengefasst sind, statt als drei separate EventInputs geführt zu werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine direkten Ereigniseingänge vorhanden – Set/Reset/Toggle kommen gebündelt über den Adapter-Socket `S_R_T`

### **Ereignis-Ausgänge**

- Keine direkten Ereignisausgänge vorhanden

### **Daten-Eingänge**

- Keine Dateneingänge vorhanden

### **Daten-Ausgänge**

- Keine direkten Datenausgänge vorhanden

### **Adapter**

- **S_R_T**: Unidirektionaler Adapter-Socket vom Typ `adapter::types::unidirectional::ASRT` (Set/Reset/Toggle)
- **Q**: Unidirektionaler Adapter-Plug vom Typ `adapter::types::unidirectional::AX`, der den Wert des Flipflops bereitstellt

## Funktionsweise

Der ASRT_AX_T_FF_SR verfügt über drei Betriebszustände:

- **START**: Initialzustand
- **SET**: Ausgang Q ist TRUE
- **RESET**: Ausgang Q ist FALSE

Die Zustandsübergänge werden durch die am Socket `S_R_T` eintreffenden Adapterereignisse gesteuert:

- `S_R_T.SET` führt von jedem Zustand in den SET-Zustand
- `S_R_T.RESET` führt von jedem Zustand in den RESET-Zustand
- `S_R_T.TOGGLE` toggelt den aktuellen Zustand (SET → RESET bzw. RESET → SET, aus START heraus nach SET)

Bei jedem Zustandswechsel wird der entsprechende Algorithmus ausgeführt, der den Adapterwert `Q.D1` entsprechend setzt (`TRUE` im SET-, `FALSE` im RESET-Zustand).

## Technische Besonderheiten

- Kombiniert SR-Flipflop- und T-Flipflop-Funktionalität wie [AX_T_FF_SR](AX_T_FF_SR.md), jedoch mit gebündelter Adapter-Schnittstelle statt dreier einzelner EventInputs
- Verwendet die unidirektionale ASRT-Adapter-Schnittstelle für Set/Reset/Toggle und die AX-Adapter-Schnittstelle für die Datenausgabe
- Initialzustand ist START, von wo aus direkt in SET oder durch TOGGLE in SET gewechselt werden kann

## Zustandsübersicht

```
START (Initialzustand)
    │
    ├── S_R_T.SET ────→ SET (Q.D1 = TRUE)
    │
    └── S_R_T.TOGGLE ─→ SET (Q.D1 = TRUE)

SET (Q.D1 = TRUE)
    │
    ├── S_R_T.RESET ──→ RESET (Q.D1 = FALSE)
    │
    └── S_R_T.TOGGLE ─→ RESET (Q.D1 = FALSE)

RESET (Q.D1 = FALSE)
    │
    ├── S_R_T.SET ────→ SET (Q.D1 = TRUE)
    │
    └── S_R_T.TOGGLE ─→ SET (Q.D1 = TRUE)
```

## Anwendungsszenarien

- Zustandsspeicherung in Steuerungsanwendungen, bei denen Set/Reset/Toggle bereits gebündelt über einen ASRT-Adapter vorliegen (z. B. von [ASRT_CLIENT_0](../../../net/ASRT_CLIENT_0.md) oder [ASRT_3EVENTS_TO_SRT](../../../conversion/unidirectional/EVENT/ASRT_3EVENTS_TO_SRT.md))
- Taktteilung und Frequenzteilung
- Zustandsautomaten mit Speicherfunktion in durchgängig adapterbasierten Anwendungen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu [AX_T_FF_SR](AX_T_FF_SR.md) bietet der ASRT_AX_T_FF_SR dieselbe Funktionalität, jedoch mit einem einzigen ASRT-Adapter-Socket statt drei separaten EventInputs (S/R/CLK) – dadurch lässt er sich direkt an einen ASRT-liefernden Baustein anschließen, ohne die Ereignisse einzeln verdrahten zu müssen.

## Fazit

Der ASRT_AX_T_FF_SR ist die adapterbasierte Variante des bewährten SR/T-Flipflop-Musters aus [AX_T_FF_SR](AX_T_FF_SR.md). Durch die Bündelung von Set/Reset/Toggle in einem ASRT-Socket eignet er sich besonders für durchgängig adapterbasierte Steuerungsarchitekturen.
