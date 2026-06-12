# AL_D_FF


![AL_D_FF](./AL_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AL_D_FF** realisiert ein Data-Latch-Flipflop (D-Flipflop). Er dient dazu, einen digitalen Datenwert bei jedem eingehenden Ereignis zu speichern und den gespeicherten Wert über einen Adapterausgang zur Verfügung zu stellen. Der Baustein kapselt die wiederkehrende Aufgabe eines D-Flipflops und bietet über Adapter eine saubere, typisierte Schnittstelle für Ereignis- und Datenaustausch.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge. Das Ereignis zum Übernehmen des Datenwertes wird über den Adapter-Socket **I** (E1) bereitgestellt.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Das Ausgangsereignis wird über den Adapter-Plug **Q** (E1) zur Verfügung gestellt.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der zu speichernde Datenwert wird über den Adapter-Socket **I** (D1) geliefert.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der gespeicherte Datenwert wird über den Adapter-Plug **Q** (D1) ausgegeben.

### **Adapter**
| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| I | `adapter::types::unidirectional::AL` | Socket | Wert, der gelatcht werden soll |
| Q | `adapter::types::unidirectional::AL` | Plug | Gelatchter Wert |

Die Adapter sind unidirektional und vom Typ `AL`. Jeder Adapter enthält einen Ereigniseingang/-ausgang (E1) und einen Dateneingang/-ausgang (D1). Der Socket **I** dient als Eingangsschnittstelle, der Plug **Q** als Ausgangsschnittstelle.

## Funktionsweise
Der Baustein verwendet intern den Standard-Funktionsblock `iec61499::events::E_D_FF_ANY`.  
Bei jedem Ereignis am Adaptereingang **I** (E1) wird der Datenwert von **I.D1** übernommen und am Adapterausgang **Q.D1** gespeichert. Gleichzeitig wird ein Ereignis am Ausgang **Q.E1** erzeugt, um der nachgeschalteten Logik die Verfügbarkeit des neuen Werts zu signalisieren.

Die Übernahme erfolgt flankengesteuert (steigende Flanke) – das Verhalten entspricht einem getakteten D-Latch oder D-Flipflop, je nach Definition des intern verwendeten FB.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Statt einzelner Ein-/Ausgänge wird die gesamte Signalgruppe (Ereignis + Daten) über einen Adapter zusammengefasst. Dies vereinfacht die Verbindung in der Applikation und sorgt für eine klare semantische Kapselung.
- **Wiederverwendung vorhandener Logik**: Der Baustein delegiert die Kernfunktion an den IEC‑61499‑Standard-FB `E_D_FF_ANY`, sodass eine erprobte und portable Implementierung zum Einsatz kommt.
- **Typsicherheit**: Durch die Verwendung eines festgelegten Adaptertyps (`AL`) wird sichergestellt, dass nur kompatible Signale angeschlossen werden können.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen ECC‑Zustandsautomaten. Sein internes Verhalten wird vollständig durch den eingebetteten FB `E_D_FF_ANY` bestimmt. Dieser realisiert einen D‑Flipflop mit zwei logischen Zuständen:

- **Zustand 0**: Gespeicherter Wert ist `false` (bzw. der Datenwert des Adapters ist 0).
- **Zustand 1**: Gespeicherter Wert ist `true` (bzw. der Datenwert des Adapters ist 1).

Ein Zustandswechsel erfolgt nur bei einem Ereignis an **I.E1**; dabei wird der an **I.D1** anliegende Wert übernommen.

## Anwendungsszenarien
- **Signalverzögerung und Synchronisation**: Ein Datenwert soll erst bei einem definierten Ereignis (z. B. Taktflanke) weitergegeben werden.
- **Speicherung eines binären Zustands**: z. B. als Teil eines Schieberegisters, eines Zustandsregisters oder einer Merkerlogik.
- **Kopplung mit Adapter-basierten Komponenten**: Einfache Integration in Applikationen, die bereits den Adaptertyp `adapter::types::unidirectional::AL` verwenden.

## Vergleich mit ähnlichen Bausteinen
- **E_D_FF_ANY**: Standard‑D‑Flipflop mit einzelnen Ereignis‑ und Dateneingängen. `AL_D_FF` kapselt diesen Baustein und bietet eine Adapterschnittstelle.
- **SR_FF oder JK_FF**: Andere Flipflop‑Typen mit mehreren Steuereingängen. Der `AL_D_FF` beschränkt sich auf die einfache D‑Funktionalität.
- **AL_D_LATCH**: Ein reiner Latch ohne Ereignissteuerung? (Nicht vorhanden). Der `AL_D_FF` arbeitet flankengesteuert und eignet sich daher für taktsynchrone Systeme.

## Fazit
Der Funktionsblock `AL_D_FF` bietet eine gekapselte, adapterbasierte Lösung für die grundlegende D‑Flipflop‑Funktionalität. Er vereinfacht die Handhabung von Signal‑ und Ereignisgruppen in IEC‑61499‑Applikationen, erhöht die Wiederverwendbarkeit und bleibt durch die Rückführung auf einen standardisierten Kernbaustein zuverlässig und nachvollziehbar.