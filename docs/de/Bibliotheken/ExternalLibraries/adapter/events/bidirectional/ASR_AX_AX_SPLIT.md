# ASR_AX_AX_SPLIT

![ASR_AX_AX_SPLIT](ASR_AX_AX_SPLIT.svg)

* * * * * * * * * *

## Einleitung

Der ASR_AX_AX_SPLIT ist ein Composite-Funktionsblock, der zwei eingehende ASR_AX-Ereignisse (Set/Reset) unverändert von seinem Socket `IN` an den Plug `OUT` durchreicht und zusätzlich den auf dem Rückkanal von `OUT` gemeldeten Zustand (Event + Bool) über einen dritten, unidirektionalen `AX_OUT`-Plug nach außen spiegelt. Er ist die um Set/Reset erweiterte Variante von [AE_AX_AX_SPLIT](AE_AX_AX_SPLIT.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden – Ereignisse kommen über die Adapter-Sockets/-Plugs*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**

*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**

*Keine Daten-Ausgänge vorhanden*

### **Adapter**

- **IN**: Bidirektionaler Adapter-Socket vom Typ `adapter::types::bidirectional::ASR_AX` (Eingang)
- **OUT**: Bidirektionaler Adapter-Plug vom Typ `adapter::types::bidirectional::ASR_AX` (Ausgang)
- **AX_OUT**: Unidirektionaler Adapter-Plug vom Typ `adapter::types::unidirectional::AX`, spiegelt den Rückkanal (Zustand) von ASR_AX

## Funktionsweise

1. `IN.SET` und `IN.RESET` werden unverändert an `OUT.SET` bzw. `OUT.RESET` weitergeleitet – die Vorwärtsrichtung wird 1:1 durchgeschleift.
2. Das Rückkanal-Ereignis `OUT.EI1` (samt zugehörigem Datum `OUT.DI1`) wird sowohl an `IN.EI1`/`IN.DI1` zurückgemeldet als auch gleichzeitig an `AX_OUT.E1`/`AX_OUT.D1` weitergegeben.
3. Dadurch ist der über `OUT` gemeldete Zustand an zwei Stellen sichtbar: am ursprünglichen Socket `IN` und zusätzlich isoliert am `AX_OUT`-Plug.

## Technische Besonderheiten

- Reine Ereignis-/Datenverbindungen (`FBNetwork`), keine eigene Logik oder Zustandsverwaltung
- Vorwärtsrichtung (Socket → Plug) ist ein einfacher 1:1-Passthrough für Set und Reset
- Rückkanal wird verdoppelt statt aufgeteilt: beide Ziele (`IN` und `AX_OUT`) erhalten dieselbe Information

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustand und arbeitet stateless. Jedes eingehende Ereignis wird sofort weitergeleitet bzw. gespiegelt.

## Anwendungsszenarien

- Zusätzliches, isoliertes Abgreifen des ASR_AX-Rückkanals (z. B. für eine separate Anzeige oder Protokollierung) ohne die eigentliche Verbindung zwischen `IN` und `OUT` zu verändern
- Aufbau von Diagnose-/Monitoring-Pfaden in ASR_AX-basierten Steuerungsnetzwerken

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AE_AX_AX_SPLIT](AE_AX_AX_SPLIT.md) folgt demselben Muster mit nur einem Vorwärts-Ereignis; [ASRT_AX_AX_SPLIT](ASRT_AX_AX_SPLIT.md) erweitert es um ein drittes Vorwärts-Ereignis (Toggle).

## Fazit

Der ASR_AX_AX_SPLIT ermöglicht es, den AX-Rückkanal eines ASR_AX-Adapterpaares zusätzlich an einer zweiten Stelle im Netzwerk verfügbar zu machen, ohne die eigentliche Signalkette zu unterbrechen oder zu verändern.
