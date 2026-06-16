# AUS_SPLIT_7


![AUS_SPLIT_7](./AUS_SPLIT_7.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUS_SPLIT_7** ist ein generischer Baustein zur Verteilung eines einzelnen AUS-Adapter-Signals auf sieben identische AUS-Ausgänge. Er dient als Signalvervielfacher in Steuerungsanwendungen, die auf der IEC 61499-Norm basieren. Der Baustein besitzt keine ereignis- oder datenbasierten Schnittstellen, sondern kommuniziert ausschließlich über Adapter des Typs `adapter::types::unidirectional::AUS`. Die eigentliche Typisierung des Signals wird erst zur Laufzeit über das generische Attribut `GenericClassName` festgelegt.

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

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AUS` | Einheitliches AUS-Eingangssignal |
| **Plug** (Ausgang) | `OUT1` – `OUT7` | `adapter::types::unidirectional::AUS` | Sieben parallel ausgegebene AUS-Signale |

## Funktionsweise
Der Baustein empfängt über den Adapter-Socket `IN` ein AUS-Signal. Dieses Signal wird unverändert und ohne Verzögerung an alle sieben Adapter-Plugs `OUT1` bis `OUT7` weitergeleitet. Da der Baustein als generischer Funktionsblock deklariert ist (`GenericClassName = 'GEN_AUS_SPLIT'`), kann der konkrete Typ des AUS-Adapters zur Entwurfszeit oder während der Systemkonfiguration überschrieben werden. Das Verhalten bleibt dabei stets dasselbe: 1-zu-n-Verteilung.

## Technische Besonderheiten
- **Generischer Baustein**: Der tatsächliche Adaptertyp wird über das Attribut `eclipse4diac::core::GenericClassName` definiert. Standardmäßig ist `'GEN_AUS_SPLIT'` gesetzt.
- **Keine ECC / Zustandsmaschine**: Aufgrund des Fehlens von Ereigniseingängen besitzt der Baustein keinen internen Zustandsautomaten. Die Ausgänge folgen direkt dem Eingangssignal (kombinatorisches Verhalten).
- **Reine Adapterkommunikation**: Es werden keine IEC 61499-Datentypen (BOOL, INT, etc.) verwendet; die gesamte Datenübertragung erfolgt über unidirektionale AUS-Adapter.
- **Kompatibilität**: Der Baustein ist für den Einsatz in 4diac-IDE und Laufzeitumgebungen vorgesehen, die Adapter des Typs `adapter::types::unidirectional::AUS` unterstützen.

## Zustandsübersicht
Der Funktionsblock verfügt über keinen Zustandsautomaten. Das Ausgangssignal jeder der sieben OUT-Adapter entspricht stets dem aktuellen Wert des IN-Adapters. Eine zeitliche Verzögerung oder Zustandsspeicherung findet nicht statt.

## Anwendungsszenarien
- **Signalverteilung in redundanten Systemen**: Ein zentrales AUS-Steuersignal (z. B. „Not-Aus“) soll an mehrere dezentrale Aktoren oder Subsysteme weitergeleitet werden.
- **Modulare Automatisierungsstrukturen**: Ein von einer übergeordneten Steuerung empfangenes AUS-Signal wird auf sieben parallele Pfade aufgeteilt, die unabhängige Maschinenmodule steuern.
- **Test- und Simulationsumgebungen**: Zur einfachen Vervielfachung eines Testsignals ohne Änderung der Logik.

## Vergleich mit ähnlichen Bausteinen
- **AUS_SPLIT_N** (z. B. für 2, 4, 8 Ausgänge) existieren als Varianten mit unterschiedlicher Ausgangsanzahl. AUS_SPLIT_7 ist eine spezifische Ausprägung für genau sieben Ausgänge.
- Im Gegensatz zu Daten-Splittern (z. B. `SPLIT_INT`, `SPLIT_BOOL`) arbeitet dieser Baustein ausschließlich mit Adaptern und nicht mit elementaren Datentypen. Dadurch eignet er sich besonders für protokollbasierte oder typsichere Verbindungen.
- Bausteine mit Ereignis-Schnittstellen (z. B. `E_SPLIT`) verteilen Ereignisse, nicht Signale. AUS_SPLIT_7 verteilt dagegen einen kontinuierlichen Signalwert.

## Fazit
Der **AUS_SPLIT_7** ist ein einfacher, aber effektiver generischer Funktionsblock zur unidirektionalen Verteilung eines AUS-Adapter-Signals auf sieben parallele Ausgänge. Durch seine reine Adapter-basierte Schnittstelle und die fehlende Ereignislogik eignet er sich für alle Anwendungen, bei denen ein Signal ohne Verzögerung oder Zustandsspeicherung vervielfacht werden muss. Er bietet eine saubere, modulare Lösung für die Signalverteilung in IEC 61499-basierten Automatisierungssystemen.