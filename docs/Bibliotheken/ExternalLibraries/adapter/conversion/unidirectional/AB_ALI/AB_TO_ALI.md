# AB_TO_ALI


![AB_TO_ALI](./AB_TO_ALI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AB_TO_ALI` ist ein Composite-Baustein, der eine Konvertierung von einem BYTE-Adapter (`AB`) zu einem LINT-Adapter (`ALI`) realisiert. Er ermöglicht die nahtlose Integration zwischen Schnittstellen, die auf unterschiedlichen Datentypen basieren, und stellt die Datenübergabe über standardisierte Adapter bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge des Funktionsblocks. Ereignisse werden über den Socket-Adapter `AB_IN` empfangen.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge des Funktionsblocks. Ereignisse werden über den Plug-Adapter `ALI_OUT` ausgegeben.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge des Funktionsblocks. Daten werden über den Socket-Adapter `AB_IN` empfangen.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge des Funktionsblocks. Daten werden über den Plug-Adapter `ALI_OUT` ausgegeben.

### **Adapter**
- **Socket `AB_IN`** (Typ: `adapter::types::unidirectional::AB`)  
  Empfängt ein BYTE-Signal (über den Datenport `D1`) sowie ein Ereignis (über den Ereignisport `E1`).
- **Plug `ALI_OUT`** (Typ: `adapter::types::unidirectional::ALI`)  
  Sendet ein LINT-Signal (über den Datenport `D1`) sowie ein Ereignis (über den Ereignisport `E1`).

## Funktionsweise
Der Funktionsblock arbeitet als reine Datenkonvertierungsschleife:
1. Ein eingehendes Ereignis am Socket `AB_IN` (Port `E1`) triggert den internen Konvertierungsbaustein `F_BYTE_TO_LINT`.
2. Der ebenfalls am Socket anliegende BYTE-Wert (`D1`) wird an den Eingang `IN` des Konverters übergeben.
3. Der Konverter wandelt den BYTE-Wert in einen LINT-Wert um und stellt ihn an seinem Ausgang `OUT` bereit.
4. Das Bestätigungsereignis des Konverters (`CNF`) wird an den Plug `ALI_OUT` (Port `E1`) weitergeleitet, und der konvertierte LINT-Wert wird auf dem Datenport `D1` des Plugs ausgegeben.

## Technische Besonderheiten
- Es handelt sich um einen **Composite-Baustein**, der intern den Standard-Funktionsblock `iec61131::conversion::F_BYTE_TO_LINT` verwendet.
- Die Konvertierung erfolgt **ereignisgesteuert** – jede Änderung am Eingang löst eine Verarbeitung aus.
- Der Baustein ist für unidirektionale Adapter ausgelegt und unterstützt keine Rückwärtskonvertierung.
- Die Typinformationen der Adapter (`AB` und `ALI`) sind als unidirektionale Schnittstellen definiert und enthalten je einen Ereignis- und einen Datenport.

## Zustandsübersicht
Der Funktionsblock besitzt keinen eigenen Zustandsautomaten. Die Konvertierung erfolgt **stateless** – bei jedem eingehenden Ereignis wird der aktuelle Wert sofort umgesetzt und ausgegeben. Es gibt keine Verzögerung, Pufferung oder interne Zustände.

## Anwendungsszenarien
- **Integration von Feldbussystemen** oder Sensoren, die BYTE-Daten liefern, in eine Steuerungsumgebung, die LINT-Werte erwartet (z. B. zur weiteren Verarbeitung in Zählern oder langen Integer-Operationen).
- **Adapter-Konvertierung** in modularen Funktionsbaustein-Netzwerken, bei denen die Schnittstellen unterschiedliche Datentypen verwenden (z. B. in der Agrar- oder Automatisierungstechnik).
- **Brückenbildung** zwischen älteren BYTE-basierten Modulen und modernen LINT-basierten Komponenten.

## Vergleich mit ähnlichen Bausteinen
- `AB_TO_ALI` ist spezifisch für die Konvertierung von **BYTE** nach **LINT**. Es gibt analoge Bausteine für andere Datentyp-Kombinationen (z. B. `WORD_TO_DINT`, `BYTE_TO_INT`).
- Im Gegensatz zu generischen Konvertern oder Skalierungsbausteinen ist dieser FB auf eine feste Typumwandlung optimiert und benötigt keine Parametrierung.
- Der Einsatz von Adaptern anstelle direkter Ein-/Ausgangsports ermöglicht eine höhere Wiederverwendbarkeit und eine saubere Trennung der Schnittstellen.

## Fazit
Der `AB_TO_ALI`-Funktionsblock bietet eine einfache und zuverlässige Möglichkeit, BYTE-Daten über einen Adapter in LINT-Daten umzuwandeln. Durch die Verwendung von Standard-Konvertierungsbausteinen und einer klaren ereignisgesteuerten Architektur eignet er sich ideal für modulare Automatisierungssysteme, die eine konsistente Datenkonvertierung zwischen verschiedenen Adaptertypen erfordern.