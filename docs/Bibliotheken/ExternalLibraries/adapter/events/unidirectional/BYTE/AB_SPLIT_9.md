# AB_SPLIT_9


![AB_SPLIT_9](./AB_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AB_SPLIT_9** dient dazu, einen einzelnen eingehenden Adapter vom Typ **AB** auf neun identische ausgehende Adapter (**OUT1** bis **OUT9**) aufzuteilen. Er ist als generischer Baustein (GenericClassName = `'GEN_AB_SPLIT'`) implementiert und kann in beliebigen 4diac‑Projekten eingesetzt werden, um eine Punkt‑zu‑Mehrpunkt‑Verbindung über das Adapter‑Interface zu realisieren.

Der Baustein besitzt keine ereignisgesteuerten oder datengetriebenen Ein‑/Ausgänge – die gesamte Kommunikation erfolgt ausschließlich über die Adapter‑Schnittstellen. Dies ermöglicht eine saubere, aufgabenorientierte Kopplung von Modulen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine vorhanden.

### **Ereignis-Ausgänge**
Keine vorhanden.

### **Daten-Eingänge**
Keine vorhanden.

### **Daten-Ausgänge**
Keine vorhanden.

### **Adapter**
| Schnittstelle | Richtung | Typ | Beschreibung |
|--------------|----------|-----|--------------|
| IN | Socket | `adapter::types::unidirectional::AB` | Eingehender Adapter (Quelle) |
| OUT1 – OUT9 | Plug | `adapter::types::unidirectional::AB` | Neun identische ausgehende Adapter (Senken) |

## Funktionsweise
Der Baustein kopiert den gesamten Daten‑ und Ereignis‑Durchgriff des eingehenden Adapters **IN** auf die neun Ausgangs‑Adapter **OUT1** bis **OUT9**. Jeder Ausgang erhält exakt dieselbe Information wie der Eingang – es findet keine Filterung, Umformung oder Verzögerung statt.

Der Baustein verhält sich somit wie ein **passiver Verteiler** (Splitting‑Knoten) auf der Adapter‑Ebene. Änderungen am Eingangs‑Adapter (z. B. neue Werte oder Events) werden sofort an alle Ausgänge weitergereicht, sofern die angeschlossenen Module dies zulassen.

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein ist als generischer FB deklariert (`GenericClassName = 'GEN_AB_SPLIT'`). Dadurch kann er in verschiedenen Kontexten wiederverwendet werden, solange der Adapter‑Typ `unidirectional::AB` kompatibel ist.
- **Keine Zustandslogik**: Es gibt kein ECC (Execution Control Chart) – der Baustein ist vollständig deklarativ und benötigt keine sequentielle Verarbeitung.
- **Einfache Erweiterbarkeit**: Das Prinzip lässt sich auf andere Anzahlen von Ausgängen übertragen (z. B. `AB_SPLIT_4`, `AB_SPLIT_16`), indem die XML‑Struktur entsprechend angepasst wird.

## Zustandsübersicht
Der Baustein besitzt **keine** eigenen Zustände. Das Verhalten ist rein kombinatorisch – die Verteilung erfolgt kontinuierlich und ohne Verzögerung. Eine Zustandsmaschine ist daher nicht erforderlich.

## Anwendungsszenarien
- **Steuerung von mehreren parallelen Aktoren**: Ein Sensor (z. B. ein Drucksensor) liefert über einen AB‑Adapter seinen Messwert. Dieser Wert soll gleichzeitig an mehrere Stellglieder (Ventile, Motoren) weitergegeben werden – der Split‑Baustein verteilt die Information an alle.
- **Signalkopplung in modularen Anlagen**: In einer verteilten Automatisierungslösung können mehrere Subsysteme denselben Datenstrom empfangen, ohne dass jedes Subsystem eine separate Verbindung zur Quelle aufbauen muss.
- **Test‑ und Simulationsumgebungen**: Ein eingehender Datenstrom kann auf mehrere Überwachungs‑ oder Logging‑Module aufgeteilt werden, ohne die ursprüngliche Verbindung zu beeinträchtigen.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Ausgänge | Besonderheit |
|----------|----------|--------------|
| `AB_SPLIT_9` | 9 | Standard‑Split für 1→9, generisch |
| `AB_SPLIT_4` | 4 | Gleiche Funktionsweise, geringere Anzahl |
| `AB_MERGE` | – | Fasst mehrere Eingänge zu einem Ausgang zusammen (entgegengesetzte Richtung) |

Während `AB_SPLIT_9` eine Quelle auf viele Senken verteilt, realisiert `AB_MERGE` eine Zusammenführung mehrerer Quellen in einen Ausgang. `AB_SPLIT_9` ist daher die ideale Wahl, wenn ein Signal an viele Verbraucher weitergeleitet werden muss.

## Fazit
Der **AB_SPLIT_9** bietet eine einfache, aber leistungsfähige Möglichkeit, einen einzelnen Adapter‑basierten Datenstrom auf neun parallele Pfade aufzuteilen. Durch seine generische Natur ist er in beliebigen 4diac‑Projekten einsetzbar, erfordert keine Zustandsprogrammierung und ermöglicht eine saubere, modulare Architektur. Er ist ein grundlegender Baustein für die serielle oder parallele Verteilung von Adapter‑Signalen in der Automatisierungstechnik.