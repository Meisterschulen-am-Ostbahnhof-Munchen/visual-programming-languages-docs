# ATM


![ATM](./ATM.svg)

* * * * * * * * * *

## Einleitung

Der **ATM-Adapter** (Abkürzung für „Adapter Time Message“) ist ein unidirektionaler Typ nach IEC 61499-1, der eine ereignisgesteuerte Schnittstelle zur Übertragung eines Zeitwertes bereitstellt. Er wird als Adapter verwendet, um zwischen Funktionsbausteinen (FBs) eine standardisierte, lose gekoppelte Kommunikation zu ermöglichen. Entwickelt wurde dieser Adapter von der HR Agrartechnik GmbH und ist unter der Eclipse Public License 2.0 (EPL-2.0) verfügbar.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Adapter besitzt keine Ereignis-Eingänge.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| E1   | Event | Indikation (oder Anforderung) – wird zusammen mit dem Datenwert D1 gesendet |

### **Daten-Eingänge**

Der Adapter besitzt keine Daten-Eingänge.

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| D1   | TIME | Indikations-/Anforderungsdaten vom Plug |

### **Adapter**

Der Baustein selbst ist vom Typ `AdapterType`. Es sind keine weiteren Adapter-Schnittstellen enthalten.

## Funktionsweise

Der ATM-Adapter arbeitet ausschließlich als unidirektionale Schnittstelle. Er wird in einen Funktionsbaustein als **Plug** (oder als **Socket**) eingebunden und überträgt bei Auftreten des Ereignisses **E1** den zugehörigen Zeitwert **D1** (Typ `TIME`) an die verbundene Gegenstelle. Die Übertragung erfolgt in einer Richtung: Vom sendenden zum empfangenden Baustein. Die Kopplung wird automatisch durch die 4diac-IDE-Umgebung aufgelöst.

## Technische Besonderheiten

- **Unidirektionaler Adapter**: Nur eine Daten- und Ereignisrichtung (Plug → Socket).
- **Einfachste Ausprägung**: Genau ein Ereignis und eine Variable – minimaler Overhead.
- **Typisierung**: Die übertragene Variable ist vom elementaren Typ `TIME`, geeignet für Zeitstempel, Verzögerungen oder Zeitmessungen.
- **Lizenz**: Veröffentlicht unter EPL-2.0, somit frei nutzbar und erweiterbar.
- Keine Zustandsmaschine oder interne Logik – reines Schnittstelleninterface.

## Zustandsübersicht

Da der ATM-Adapter keine interne Zustandsmaschine besitzt (zustandsloser Adapter), ist keine Zustandsübersicht erforderlich. Die Funktionalität beschränkt sich auf die reine Ereignis-Daten-Weitergabe.

## Anwendungsszenarien

- **Übermittlung von Zeitstempeln** zwischen verschiedenen Funktionsbausteinen (z. B. Protokollierung, Steuerung mit Zeitbezug).
- **Signal für zeitgesteuerte Aktionen**: Ein Baustein sendet über den Adapter eine Zeitinformation, die von einem anderen Baustein ausgewertet wird.
- **Testumgebungen**: Einfaches, klar definiertes Interface für Unit-Tests von Bausteinen, die Zeitwerte verarbeiten.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | ATM (dieser Adapter) | Andere unidirektionale Adapter (z. B. mit mehreren Events/Daten) |
|---------|----------------------|----------------------------------------------------------------|
| Ereignisse | 1 (E1) | meist mehrere (z. B. INIT, REQ, IND, RSP) |
| Daten | 1 (TIME) | oft mehrere Daten oder verschiedene Typen |
| Komplexität | gering | mittel bis hoch |
| Einsatz | einfache Zeitübertragung | komplexe Prozessschriftstellen |

Gegenüber allgemeineren Adaptern beschränkt sich ATM auf das Nötigste – ideal, wenn nur ein Ereignis mit einem einzigen Zeitwert ausgetauscht werden muss.

## Fazit

Der ATM-Adapter ist ein minimaler, aber praxisrelevanter Baustein zur unidirektionalen Übertragung von Zeitwerten in IEC 61499-Systemen. Seine klare Schnittstelle und einfache Handhabung machen ihn besonders geeignet für Anwendungen, die einen Fokus auf zeitbezogene Kommunikation legen. Durch die offene Lizenzierung kann der Adapter ohne Einschränkungen in eigene Projekte integriert oder erweitert werden.