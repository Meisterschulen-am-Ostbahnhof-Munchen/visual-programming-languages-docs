# AX_MERGE_2

* * * * * * * * * *
## Einleitung
Der AX_MERGE_2 ist ein Funktionsblock, der zwei unidirektionale AX-Adapter-Eingänge zu einem AX-Adapter-Ausgang zusammenführt.

## Schnittstellenstruktur

### **Adapter**
**Sockets (Eingänge):**
- **IN1** (adapter::types::unidirectional::AX)
- **IN2** (adapter::types::unidirectional::AX)

**Plugs (Ausgänge):**
- **OUT** (adapter::types::unidirectional::AX)

## Funktionsweise
Ereignisse und Daten von beiden Eingängen (IN1 und IN2) werden an den Ausgang (OUT) weitergeleitet.

## Technische Besonderheiten
- Verwendet unidirektionale Adapter.

## Zustandsübersicht
Kombinatorisch.

## Anwendungsszenarien
Zusammenführung von Signalen.

## Vergleich mit ähnlichen Bausteinen
- **E_MERGE**: Standard Ereignis-Merge ohne Adapter.

## Fazit
Adapter-basierter Merge-Baustein.
