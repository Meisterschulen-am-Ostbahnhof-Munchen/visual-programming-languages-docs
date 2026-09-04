# ASR_AX_SR_2

![ASR_AX_SR_2](ASR_AX_SR_2.svg)

* * * * * * * * * *

## Einleitung

Der ASR_AX_SR_2 ist ein ereignisgesteuertes bistabiles Flipflop (Set/Reset) mit einem einzigen bidirektionalen `ASR_AX`-Socket: Set- und Reset-Ereignis kommen am selben Adapter an, über den auch der neue Zustand zurückgemeldet wird – im Gegensatz zu [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md), das einen unidirektionalen ASR-Socket und einen separaten AX-Plug für den Zustand verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden – Set/Reset kommen über den Adapter-Socket `S_R`*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**

*Keine Dateneingänge vorhanden*

### **Daten-Ausgänge**

*Keine Datenausgänge vorhanden*

### **Adapter**

- **S_R**: Bidirektionaler Adapter-Socket vom Typ `adapter::types::bidirectional::ASR_AX` – Set/Reset (Eingang), Zustand (Ausgang) über denselben Adapter

## Funktionsweise

Der ASR_AX_SR_2 verfügt über drei Betriebszustände:

- **START**: Initialzustand
- **SET**: Zustand TRUE
- **RESET**: Zustand FALSE

Die Zustandsübergänge werden durch die am Socket `S_R` eintreffenden Adapterereignisse gesteuert:

- `S_R.SET` führt von START oder RESET in den SET-Zustand
- `S_R.RESET` führt vom SET-Zustand in den RESET-Zustand

Bei jedem Zustandswechsel wird der entsprechende Algorithmus ausgeführt, der `S_R.DI1` setzt (`TRUE` im SET-, `FALSE` im RESET-Zustand) und damit über `S_R.EI1` den Zustand zurück über denselben Adapter meldet.

## Technische Besonderheiten

- Bidirektionale Kommunikation über einen einzigen Adapter-Socket statt getrenntem ASR-Socket + AX-Plug
- Kein Toggle-Eingang – reines Set/Reset-Flipflop (im Unterschied zu [ASRT_AX_T_FF_SR_2](ASRT_AX_T_FF_SR_2.md))
- Direkter Ersatz für [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md) in durchgängig adapterbasierten (ASR_AX-)Anwendungen

## Zustandsübersicht

```
START (Initialzustand)
    │
    └── S_R.SET ───→ SET (S_R.DI1 = TRUE)

SET (S_R.DI1 = TRUE)
    │
    └── S_R.RESET ─→ RESET (S_R.DI1 = FALSE)

RESET (S_R.DI1 = FALSE)
    │
    └── S_R.SET ───→ SET (S_R.DI1 = TRUE)
```

## Anwendungsszenarien

- Zustandsspeicherung (Set/Reset) über eine einzige bidirektionale Adapterverbindung, ohne separaten Zustandsausgang verdrahten zu müssen
- Ersatz für [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md) in Netzwerken, die durchgängig ASR_AX-Adapter verwenden

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md), das einen unidirektionalen ASR-Socket und einen separaten AX-Plug für den Zustand nutzt, bündelt ASR_AX_SR_2 beide Richtungen in einem einzigen ASR_AX-Socket. [ASRT_AX_T_FF_SR_2](ASRT_AX_T_FF_SR_2.md) erweitert dasselbe Muster um einen zusätzlichen Toggle-Eingang.

## Fazit

Der ASR_AX_SR_2 überträgt das bewährte Set/Reset-Flipflop-Muster in die bidirektionale Adapterwelt: Set/Reset-Eingang und Zustands-Rückmeldung teilen sich denselben ASR_AX-Socket, was die Verdrahtung in adapterbasierten Netzwerken vereinfacht.
