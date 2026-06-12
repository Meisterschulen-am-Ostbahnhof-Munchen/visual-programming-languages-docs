# AD_TO_AUS


![AD_TO_AUS](./AD_TO_AUS.svg)

* * * * * * * * * *
## Einleitung
Der **AD_TO_AUS** ist ein zusammengesetzter Funktionsblock (Composite FB), der einen DWORD-Adapter (AD) in einen USINT-Adapter (AUS) umwandelt. Er dient als unidirektionale Schnittstelle zur Konvertierung eines 32‑Bit‑Datenwerts in einen 8‑Bit‑Wert. Der Baustein kapselt die IEC‑61131‑Konvertierungsfunktion `F_DWORD_TO_USINT` und stellt die Adapter‑Schnittstellen bereit, sodass er nahtlos in eine Adapter‑basierte Kommunikationsstruktur eingebunden werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Über den Adapter-Eingang **AD_IN** wird das Ereignis **E1** empfangen. Es löst die Konvertierung des anliegenden DWORD-Werts aus.

### **Ereignis-Ausgänge**
Über den Adapter-Ausgang **AUS_OUT** wird das Ereignis **E1** gesendet, sobald die Konvertierung abgeschlossen ist und der umgewandelte USINT-Wert bereitsteht.

### **Daten-Eingänge**
Der Adapter-Eingang **AD_IN** liefert einen DWORD-Wert (32‑Bit) über die Datenleitung **D1**.

### **Daten-Ausgänge**
Der Adapter-Ausgang **AUS_OUT** stellt den konvertierten USINT-Wert (8‑Bit) über die Datenleitung **D1** zur Verfügung.

### **Adapter**
| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **AD_IN** | `adapter::types::unidirectional::AD` | Eingang (Socket) | Nimmt DWORD‑Daten und Steuerereignisse auf. |
| **AUS_OUT** | `adapter::types::unidirectional::AUS` | Ausgang (Plug) | Gibt USINT‑Daten und Bestätigungsereignisse aus. |

## Funktionsweise
1. Der FB wartet auf ein Ereignis am Adapter-Eingang **AD_IN** (Signal **E1**).
2. Mit Eintreffen des Ereignisses wird der über **AD_IN.D1** anliegende DWORD-Wert an den internen FB `F_DWORD_TO_USINT` weitergeleitet und dessen `REQ`-Eingang aktiviert.
3. Der integrierte Konvertierungsbaustein führt die Typumwandlung von DWORD nach USINT durch (Typkonvertierung gemäß IEC 61131‑3).
4. Nach Abschluss der Konvertierung signalisiert der interne FB das Ereignis `CNF`, welches an den Adapter-Ausgang **AUS_OUT** (Signal **E1**) weitergegeben wird. Gleichzeitig wird der konvertierte USINT-Wert über **AUS_OUT.D1** bereitgestellt.

## Technische Besonderheiten
- **Adapter‑Kopplung:** Der FB besitzt keine direkten Ereignis‑ oder Daten‑Ein‑/Ausgänge, sondern kommuniziert ausschließlich über Adapter-Schnittstellen. Dies ermöglicht eine lose Kopplung in einer modularen Steuerungsarchitektur.
- **Verwendete Bibliothek:** Die Konvertierung erfolgt mit dem standardisierten Baustein `iec61131::conversion::F_DWORD_TO_USINT`. Dadurch wird die IEC‑61131‑Konformität gewährleistet.
- **Paketname:** `adapter::conversion::unidirectional` (siehe CompilerInfo) ordnet den FB in eine spezifische Adapter‑Konvertierungs‑Bibliothek ein.

## Zustandsübersicht
Der **AD_TO_AUS** ist ein reiner Funktionsblock ohne eigenen Zustandsautomaten. Er arbeitet streng kausal: Jedes Eingangsereignis führt genau zu einem Ausgangsereignis. Die Latenz ergibt sich aus der Ausführungszeit des internen Konvertierungsbausteins.

## Anwendungsszenarien
- **Schnittstellenanpassung:** Wenn ein Sensor oder Aktor Daten im DWORD‑Format (32 Bit) liefert, die Steuerung aber nur USINT‑Werte (8 Bit) verarbeiten kann, wird der FB zwischengeschaltet.
- **Adapter‑basierte Systeme:** In einer 4diac‑Umgebung, die auf unidirektionale Adapter setzt, kann der FB nahtlos in Datenfluss‑Pfade eingefügt werden, ohne die Ereignis‑/Daten‑Struktur der umgebenden Komponenten zu ändern.
- **Datenreduktion:** Gezieltes Abschneiden von höherwertigen Bytes, wenn nur der niederwertige Teil eines DWORDs relevant ist (z. B. bei Zählern oder einfachen Analogwerten).

## Vergleich mit ähnlichen Bausteinen
- **AD_TO_AUS** ist spezifisch für die unidirektionale Umwandlung eines DWORD-Adapters in einen USINT-Adapter. Alternativ könnte man die IEC‑61131‑Funktion `F_DWORD_TO_USINT` direkt verwenden, müsste dann aber die Adapter‑Kopplung selbst vornehmen.
- Andere Adapter‑Konvertierungsbausteine (z. B. `AD_TO_BYTE` oder `AUS_TO_DWORD`) folgen dem gleichen Muster, arbeiten jedoch mit anderen Datentypen. Der vorliegende FB füllt die Lücke für die spezifische Kombination DWORD → USINT.

## Fazit
Der **AD_TO_AUS** ist ein einfacher, aber nützlicher Composite‑FB zur Typkonvertierung zwischen zwei unidirektionalen Adapter‑Schnittstellen. Er reduziert den Implementierungsaufwand, indem er die Standardkonvertierung kapselt und eine saubere, ereignisgesteuerte Adapter‑Kommunikation ermöglicht. Dank der klaren Struktur eignet er sich sowohl für den schnellen Entwurf als auch für den produktiven Einsatz in IEC‑61499‑basierten Steuerungen.