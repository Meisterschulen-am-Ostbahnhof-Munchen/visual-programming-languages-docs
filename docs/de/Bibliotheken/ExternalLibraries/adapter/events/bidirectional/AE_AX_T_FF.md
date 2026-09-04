# AE_AX_T_FF

![AE_AX_T_FF](AE_AX_T_FF.svg)

* * * * * * * * * *

## Einleitung

Der AE_AX_T_FF ist ein ereignisgesteuertes Toggle-Flipflop mit einem einzigen bidirektionalen `AE_AX`-Socket: Das Takt-Ereignis kommt am selben Adapter an, über den auch der neue Zustand zurückgemeldet wird – im Gegensatz zu [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md), der einen separaten CLK-EventInput und einen eigenen AX-Plug für den Zustand verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden – das Takt-Ereignis kommt über den Adapter-Socket `CLK`*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**

*Keine Dateneingänge vorhanden*

### **Daten-Ausgänge**

*Keine Datenausgänge vorhanden*

### **Adapter**

- **CLK**: Bidirektionaler Adapter-Socket vom Typ `adapter::types::bidirectional::AE_AX` – Takt (Eingang), Zustand (Ausgang) über denselben Adapter

## Funktionsweise

Der AE_AX_T_FF verfügt über zwei Betriebszustände:

- **START**: Initialzustand
- **SET**: Zustand nach dem Toggeln

Bei jedem an `CLK.E1` eintreffenden Ereignis wechselt der Funktionsblock von START nach SET und feuert dabei den Algorithmus `TOGGLE`, der `CLK.DI1 := NOT CLK.DI1` ausführt und damit über `CLK.EI1` den invertierten Zustand zurück über denselben Adapter meldet. Aus dem SET-Zustand kehrt der Baustein unbedingt (Bedingung `1`) sofort wieder nach START zurück, sodass jedes weitere `CLK.E1`-Ereignis erneut denselben TOGGLE-Übergang auslöst.

## Technische Besonderheiten

- Bidirektionale Kommunikation über einen einzigen Adapter-Socket statt getrennter EventInput + AX-Plug
- Der ECC-Zustand SET ist nur ein Durchgangszustand für die Initialisierung des Ausgabe-Ereignisses; die eigentliche Toggle-Semantik steckt in der Algorithmuszuweisung `CLK.DI1 := NOT CLK.DI1`
- Direkter Ersatz für [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md) in durchgängig adapterbasierten (AE_AX-)Anwendungen

## Zustandsübersicht

```
START (Initialzustand)
    │
    └── CLK.E1 ─→ SET (CLK.DI1 := NOT CLK.DI1, meldet Zustand über CLK.EI1)
                       │
                       └── (unbedingt) ─→ START
```

## Anwendungsszenarien

- Umschalten eines Zustands (z. B. Ein/Aus) über eine einzige bidirektionale Adapterverbindung, ohne separaten Zustandsausgang verdrahten zu müssen
- Ersatz für [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md) in Netzwerken, die durchgängig AE_AX-Adapter verwenden

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md), das einen separaten `CLK`-EventInput und einen eigenen AX-Plug für den Zustand nutzt, bündelt AE_AX_T_FF beide Richtungen in einem einzigen AE_AX-Socket.

## Fazit

Der AE_AX_T_FF überträgt das bewährte Toggle-Flipflop-Muster in die bidirektionale Adapterwelt: Takt-Eingang und Zustands-Rückmeldung teilen sich denselben AE_AX-Socket, was die Verdrahtung in adapterbasierten Netzwerken vereinfacht.
