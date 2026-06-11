# AI_TO_AUS


![AI_TO_AUS](./AI_TO_AUS.svg)

*Bild des Funktionsblocks – nicht in der XML enthalten, daher kein automatisch generiertes Bild vorhanden.*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AI_TO_AUS** ist ein Composite-Baustein, der einen **AI-Adapter** (Datenstrom vom Typ `INT`) in einen **AUS-Adapter** (Datenstrom vom Typ `USINT`) umwandelt. Er dient als Brücke zwischen Komponenten, die unterschiedliche Datentypen für analoge Ein- und Ausgangssignale verwenden. Die Implementierung nutzt den internen Baustein `F_INT_TO_USINT` aus der Bibliothek `iec61131::conversion`.

## Schnittstellenstruktur

Der Baustein besitzt keine eigenen separaten Ereignis- oder Datenports, sondern kommuniziert ausschließlich über Adapter.

### **Ereignis-Eingänge**
- Keine direkten Ereigniseingänge. Die Ereignissteuerung erfolgt indirekt über den Adapter `AI_IN` (Socket) – hierüber wird das Ereignis `E1` empfangen.

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge. Das konvertierte Ereignis wird über den Adapter `AUS_OUT` (Plug) als `E1` ausgegeben.

### **Daten-Eingänge**
- Keine direkten Dateneingänge. Der zu konvertierende Datenwert (`INT`) wird über den Adapter `AI_IN` (Socket) als `D1` bezogen.

### **Daten-Ausgänge**
- Keine direkten Datenausgänge. Der konvertierte Wert (`USINT`) wird über den Adapter `AUS_OUT` (Plug) als `D1` bereitgestellt.

### **Adapter**
- **`AI_IN`** (Socket)  
  Typ: `adapter::types::unidirectional::AI`  
  Beschreibung: Nimmt einen `INT`-Wert und ein zugehöriges Ereignis auf.
- **`AUS_OUT`** (Plug)  
  Typ: `adapter::types::unidirectional::AUS`  
  Beschreibung: Gibt den konvertierten `USINT`-Wert mit einem Ereignis aus.

## Funktionsweise

1. Ein eingehendes Ereignis am Adapter `AI_IN.E1` triggert den internen Funktionsblock `Convert` (`F_INT_TO_USINT`) über dessen Ereigniseingang `REQ`.
2. Gleichzeitig wird der Datenwert `AI_IN.D1` (Typ `INT`) an den Eingang `IN` des Konvertierungsbausteins übergeben.
3. Der Baustein `F_INT_TO_USINT` führt die Typkonvertierung von `INT` nach `USINT` durch.
4. Nach Abschluss der Konvertierung sendet `Convert` ein Bestätigungsereignis (`CNF`) an den Ausgangsadapter, und der konvertierte Wert (`OUT`) wird an `AUS_OUT.D1` weitergeleitet.
5. Das Ereignis `AUS_OUT.E1` signalisiert der nachfolgenden Komponente, dass ein neuer Datenwert am Adapter anliegt.

## Technische Besonderheiten

- **Verwendete Bibliothek:** Der Baustein greift auf den IEC‑61131‑Standardbaustein `F_INT_TO_USINT` zurück, der eine typische Konvertierung mit möglicher Bereichsbegrenzung oder Überlaufverhalten implementiert.
- **Adapter‑Kapselung:** Der Composite-Baustein abstrahiert die Konvertierung auf Adapterebene, sodass in der Netzwerkkonfiguration nur die beiden passenden Adapter verbunden werden müssen.
- **Datenbereichskonflikt:** `INT` umfasst Werte von −32.768 bis +32.767, während `USINT` nur 0…255 darstellen kann. Bei Eingabewerten außerhalb des USINT-Bereichs hängt das Verhalten vom `F_INT_TO_USINT` ab (z. B. Sättigung auf 0 oder 255, oder modularer Überlauf). Die genaue Abbildungsvorschrift ist im konkreten Zielsystem zu prüfen.

## Zustandsübersicht

Da der Baustein ausschließlich aus einer sequenziellen Datenverarbeitung besteht (wiederholte Konvertierung bei jedem Ereignis), besitzt er keine eigenen Zustandsautomaten. Die Zustände des internen Bausteins `F_INT_TO_USINT` sind für die Funktion nicht sichtbar; der Composite-Baustein arbeitet ereignisgesteuert und ohne interne Zustandsspeicherung.

## Anwendungsszenarien

- **Sensor‑Aktor‑Kopplung:** Ein Sensor liefert Messwerte als `INT` (z. B. Temperatur −10…50 °C skaliert auf Ganzzahlen), während ein nachgeschalteter Aktor eine Steuergröße als `USINT` (z. B. 0…100 %) erwartet. Der Baustein übernimmt die erforderliche Typumwandlung.
- **Adapter‑Kompatibilisierung:** In einer 4diac‑Applikation sind zwei Module über unterschiedliche Adapter (`AI` und `AUS`) definiert. Der Composite‑FB ermöglicht die direkte Verbindung ohne zusätzliche Konvertierungslogik im Hauptnetzwerk.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Konverter (`F_INT_TO_USINT`):** Stellt die reine Typkonvertierung auf Datenebene bereit, erfordert aber separate Ereignis- und Datenverbindungen. `AI_TO_AUS` erweitert diesen um die Adapter‑Anbindung und vereinfacht so den Netzwerkentwurf.
- **Andere Adapter‑Konverter (`AI_TO_...`, `..._TO_AUS`):** Je nach benötigten Adaptertypen sind entsprechende Composite-Bausteine denkbar. `AI_TO_AUS` deckt die spezifische Kombination `INT` → `USINT` ab.

## Fazit

Der Funktionsblock **AI_TO_AUS** ist ein kompakter Composite-Baustein zur einfachen Adapter‑Konvertierung von `INT` nach `USINT`. Er kapselt den IEC‑61131‑Konverter und stellt die Daten- und Ereignisflüsse über standardisierte Adapter bereit. Dadurch wird die Integration von Komponenten mit unterschiedlichen analogen Schnittstellen in 4diac‑Applikationen erheblich erleichtert. Bei der Verwendung sollte der mögliche Datentypüberlauf beachtet werden.