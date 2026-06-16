# AR2_X_TO_REAL


![AR2_X_TO_REAL](./AR2_X_TO_REAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR2_X_TO_REAL** ist ein Composite-Baustein, der als Brücke zwischen einer AR2‑Adapter‑Schnittstelle und REAL‑Werten dient. Er ermöglicht die bidirektionale Datenübertragung und Konvertierung, wobei die eigentliche Umwandlung durch einen externen Adapter vom Typ `adapter::types::bidirectional::AR2` realisiert wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Startet die Datenübertragung an den Adapter. Der Datenwert `OUT` wird gesendet. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Quittiert die Rückmeldung des Adapters. Der konvertierte Wert liegt als `IN` an. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `OUT`    | REAL  | Datenwert, der an den Adapter übergeben wird. |

### **Daten-Ausgänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `IN`     | REAL  | Vom Adapter zurückgelieferter konvertierter Wert. |

### **Adapter**

| Name      | Typ                                      | Richtung | Beschreibung |
|-----------|------------------------------------------|----------|--------------|
| `AR2_IN`  | `adapter::types::bidirectional::AR2`     | Socket   | Bidirektionaler Adapter für die AR2‑Kommunikation und Konvertierung. |

## Funktionsweise
Der Baustein fungiert als reine Vermittlungsschicht:
1. Ein eingehendes Ereignis `REQ` löst die Übergabe des Wertes `OUT` (REAL) an den verbundenen Adapter aus (über `AR2_IN.DI1`).
2. Der Adapter führt die erforderliche Konvertierung durch (z. B. AR2 ↔ REAL) und sendet ein Bestätigungsereignis an seinen Ausgang `EO1`.
3. Dieses Ereignis wird als `CNF` nach außen geleitet, und der konvertierte Wert wird über `AR2_IN.DO1` als `IN` (REAL) bereitgestellt.

Die tatsächliche Konvertierungsrichtung wird durch die Implementierung des angeschlossenen Adapters bestimmt. Der Name des Bausteins deutet auf eine primäre Umwandlung von AR2 nach REAL hin, die bidirektionale Adapter‑Schnittstelle erlaubt jedoch auch die umgekehrte Richtung.

## Technische Besonderheiten
- **Composite‑Baustein**: Enthält keine eigene Logik, sondern kombiniert lediglich einen Adapter‑Socket mit Ereignis‑ und Datenverbindungen.
- **Bidirektionaler Adapter**: Die Schnittstelle `AR2_IN` muss einen Adapter vom Typ `adapter::types::bidirectional::AR2` bereitstellen, der die eigentliche Konvertierung implementiert.
- **Einfache Kopplung**: Der Baustein trennt die REAL‑Welt von der AR2‑Welt und ermöglicht so eine modulare Integration.

## Zustandsübersicht
Der Funktionsblock besitzt keine eigenen internen Zustände. Sein Verhalten wird vollständig durch die externen Ereignisse `REQ` und die Rückmeldung des Adapters gesteuert.

## Anwendungsszenarien
- **Anbindung von AR2‑basierten Sensoren/Aktoren** an ein Steuerungssystem, das mit REAL‑Werten arbeitet.
- **Bidirektionale Datenbrücke** in gemischten Automatisierungsumgebungen, in denen AR2‑ und REAL‑Protokolle aufeinandertreffen.
- **Test‑ und Simulationsaufbauten**, in denen AR2‑Daten durch einfach handhabbare REAL‑Werte ersetzt werden sollen.

## Vergleich mit ähnlichen Bausteinen
Während direkte Konvertierungsbausteine (z. B. AR2_TO_REAL) die Umwandlung fest verdrahten, erlaubt dieser Composite‑Baustein die flexible Ankopplung eines externen Adapters. Dadurch wird die Konvertierungslogik entkoppelt und kann je nach Anwendungsfall ausgetauscht werden, ohne die restliche Konfiguration zu ändern.

## Fazit
Der **AR2_X_TO_REAL** ist ein nützlicher Brückenbaustein für Systeme, die sowohl AR2‑ als auch REAL‑Daten verarbeiten müssen. Durch die Nutzung eines bidirektionalen Adapters wird eine klare Trennung zwischen Schnittstelle und Konvertierungslogik erreicht, was Wiederverwendbarkeit und Wartbarkeit verbessert.