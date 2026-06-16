# AUS_SPLIT_6


![AUS_SPLIT_6](./AUS_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AUS_SPLIT_6** ist ein generischer Baustein, der ein eingehendes AUS-Signal (z. B. ein einheitliches Steuersignal oder Ereignis) auf sechs identische Ausgänge verteilt. Er dient als Splitter in der IEC 61499–Kommunikation über Adapter und ermöglicht eine einfache Mehrfachnutzung eines Signals ohne zusätzliche Logik.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- Keine eigenständigen Ereigniseingänge vorhanden. Die gesamte Kommunikation erfolgt über den integrierten Adapter‑Socket.

### **Ereignis-Ausgänge**
- Keine eigenständigen Ereignisausgänge vorhanden. Die Ausgaben werden ausschließlich über die Adapter‑Plugs bereitgestellt.

### **Daten-Eingänge**
- Keine direkten Dateneingänge. Die Datenübergabe wird indirekt über den Adapter‑Socket realisiert.

### **Daten-Ausgänge**
- Keine direkten Datenausgänge. Die Ausgabedaten werden über die Adapter‑Plugs zur Verfügung gestellt.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AUS` | **IN** | Socket | Eingehendes AUS-Signal, das auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AUS` | **OUT1** | Plug | Erster Ausgang – identisch zu **IN**. |
| `adapter::types::unidirectional::AUS` | **OUT2** | Plug | Zweiter Ausgang – identisch zu **IN**. |
| `adapter::types::unidirectional::AUS` | **OUT3** | Plug | Dritter Ausgang – identisch zu **IN**. |
| `adapter::types::unidirectional::AUS` | **OUT4** | Plug | Vierter Ausgang – identisch zu **IN**. |
| `adapter::types::unidirectional::AUS** | **OUT5** | Plug | Fünfter Ausgang – identisch zu **IN**. |
| `adapter::types::unidirectional::AUS` | **OUT6** | Plug | Sechster Ausgang – identisch zu **IN**. |

*Hinweis: Der Adapter‑Typ „AUS“ ist ein unidirektionaler Adapter, der ein Signal (Ereignis + ggf. Daten) in einer Richtung weitergibt.*

## Funktionsweise
Der Baustein fungiert als passiver Verteiler. Das Signal, das am Socket **IN** anliegt, wird unverändert und ohne zeitliche Verzögerung auf alle sechs Plugs **OUT1** bis **OUT6** kopiert. Es findet keine Filterung, Transformation oder Pufferung statt. Der Baustein verhält sich wie ein „Fan‑Out“‑Knoten für AUS‑Adapterverbindungen.

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein ist als generischer Funktionsbaustein (GenericClassName = `'GEN_AUS_SPLIT'`) realisiert. In der 4diac‑IDE kann er je nach konkretem AUS‑Adaptertyp instanziiert werden.
- **Abhängigkeiten**: Erfordert den Adapter `adapter::types::unidirectional::AUS` aus dem Paket `adaper::events::unidirectional`. Die Implementierung importiert die Eclipse 4diac‑Basistypen `GenericClassName` und `TypeHash`.
- **Kein Zustand**: Der Baustein besitzt keinen internen Zustandsautomaten (keine ECC). Er arbeitet rein kombinatorisch – jede Änderung am Eingang wird sofort auf alle Ausgänge durchgereicht.
- **Unidirektional**: Die Adapter sind ausschließlich für eine Signalrichtung ausgelegt. Rückwirkungen von den Ausgängen auf den Eingang sind nicht möglich.

## Zustandsübersicht
Der Baustein besitzt **keine expliziten Zustände**. Sein Verhalten ergibt sich ausschließlich aus der aktuellen Belegung des Eingangs‑Adapters. Eine Zustandsänderung im Sinne eines Automaten findet nicht statt.

## Anwendungsszenarien
- **Verteilen eines „AUS“‑Steuersignals**: In einer Anlage soll ein einzelnes Stopp‑ oder Ausschaltsignal gleichzeitig an mehrere Aktoren (Motoren, Ventile, etc.) weitergeleitet werden.
- **Redundante Signalpfade**: Ein Signal wird auf mehrere parallele Pfade aufgeteilt, um in späteren Verarbeitungsschritten verschiedene Aktionen auszulösen.
- **Test‑ und Simulationsumgebungen**: Ein generiertes Testsignal wird unverändert an verschiedene Überwachungs‑ oder Logikbausteine gesendet.

## Vergleich mit ähnlichen Bausteinen
- **Ereignis‑Splitter (z. B. `E_SPLIT`)**: Verarbeitet diskrete Ereignisse an eigenen Eingangs‑/Ausgangs‑Events. Der `AUS_SPLIT_6` arbeitet dagegen auf Adapterebene und verteilt sowohl Ereignis als auch zugehörige Daten in einem Zug.
- **Datensplitter**: Reine Datenverteiler (z. B. `F_MUX`, `F_DIST`) erfordern separate Datentypen. Der vorliegende Baustein ist spezifisch für den Adaptertyp `AUS` und kapselt die Signalstruktur.
- **Generic‑Fähigkeit**: Dank der generischen Deklaration kann der Baustein in verschiedenen Kontexten mit unterschiedlichen AUS‑Adapterimplementierungen wiederverwendet werden.

## Fazit
Der **AUS_SPLIT_6** ist ein einfacher, aber nützlicher generischer Funktionsbaustein zur Signalverteilung in IEC 61499‑Anwendungen. Er reduziert den Verdrahtungsaufwand, indem er ein einzelnes AUS‑Signal auf sechs parallele Ausgänge bringt. Seine generische Natur macht ihn flexibel einsetzbar, solange der verwendete AUS‑Adapter den unidirektionalen Vertrag einhält.