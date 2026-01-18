# AX_CYCLE

```{index} single: AX_CYCLE
```

* * * * * * * * * *
## Einleitung
Der AX_CYCLE ist ein Funktionsblock, der ein zyklisches Ereignis über einen AX-Adapter ausgibt.

## Schnittstellenstruktur

### **Daten-Eingänge**
- **DT** (TIME): Zykluszeit.

### **Adapter**
**Sockets (Eingänge):**
- **START** (adapter::types::unidirectional::AX): Start-Signal.
- **STOP** (adapter::types::unidirectional::AX): Stop-Signal.

**Plugs (Ausgänge):**
- **EO** (adapter::types::unidirectional::AX): Zyklisches Ausgangsereignis.

## Funktionsweise
Solange START aktiv ist, wird EO mit der Periode DT ausgegeben. STOP beendet den Zyklus.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter.

## Zustandsübersicht
Zustandsbasiert.

## Anwendungsszenarien
Taktgenerierung.

## Vergleich mit ähnlichen Bausteinen
- **E_CYCLE**: Standard Zyklus-Baustein.

## Fazit
Adapter-basierter Zyklus-Baustein.
