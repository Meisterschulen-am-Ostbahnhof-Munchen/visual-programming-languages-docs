# SPLIT_AB_INTO_AX


![SPLIT_AB_INTO_AX](./SPLIT_AB_INTO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SPLIT_AB_INTO_AX** dient dazu, ein Byte, das über einen unidirektionalen AB-Adapter empfangen wird, in seine acht einzelnen Bits aufzuspalten und diese über jeweils separate AX-Adapter bereitzustellen. Dabei erfolgt eine taktgesteuerte Übernahme der Bits mittels D-Flipflops, sodass die Ausgangswerte stabil bleiben, bis ein neues Byte verarbeitet wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine expliziten Ereignis-Eingänge auf der obersten Ebene. Die Verarbeitung wird durch das Ereignis ausgelöst, das über den Socket‑Adapter **IN** (Typ AB) eintrifft. Der Adapter **IN** stellt einen Ereignis-Eingang (`E1`) und einen Daten-Eingang (`D1`) bereit.

### **Ereignis-Ausgänge**
Der Baustein besitzt keine expliziten Ereignis-Ausgänge auf der obersten Ebene. Die Ergebnisausgabe erfolgt über die Plug‑Adapter **BIT_00** bis **BIT_07** (Typ AX), die ebenfalls einen Ereignis-Ausgang (`E1`) enthalten.

### **Daten-Eingänge**
- **IN.D1** – über den Socket‑Adapter **IN** (Typ AB) wird das zu verarbeitende Byte (BYTE) empfangen.

### **Daten-Ausgänge**
- **BIT_00.D1 … BIT_07.D1** – über die Plug‑Adapter **BIT_00** bis **BIT_07** (Typ AX) werden die einzelnen booleschen Werte der Bits (Bit 0 bis Bit 7) ausgegeben.

### **Adapter**
| Adapter | Typ                          | Richtung | Beschreibung                               |
|---------|------------------------------|----------|--------------------------------------------|
| IN      | adapter::types::unidirectional::AB | Socket (Eingang) | BYTE‑Wert, wird in Einzelbits zerlegt     |
| BIT_00  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 0 (LSB)           |
| BIT_01  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 1                 |
| BIT_02  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 2                 |
| BIT_03  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 3                 |
| BIT_04  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 4                 |
| BIT_05  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 5                 |
| BIT_06  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 6                 |
| BIT_07  | adapter::types::unidirectional::AX | Plug (Ausgang)   | Boolescher Wert von Bit 7 (MSB)           |

## Funktionsweise
1. Ein eingehendes Byte wird über den Socket‑Adapter **IN** empfangen. Das Ereignis `E1` löst die Verarbeitung aus.
2. Der interne Funktionsblock `SPLIT_BYTE_INTO_BOOLS` zerlegt das Byte in acht boolesche Signale (`BIT_00` … `BIT_07`). Gleichzeitig wird das Ereignis `CNF` erzeugt.
3. Dieses Ereignis wird auf die Takteingänge (`CLK`) von acht **E_D_FF**‑Flipflops verteilt. Jedes Flipflop übernimmt beim Takt den zugehörigen booleschen Wert an seinem Dateneingang `D`.
4. Die Ausgänge `Q` der Flipflops liefern die stabilisierten Bits. Sie werden über die Datenverbindungen an die Plug‑Adapter **BIT_00** … **BIT_07** weitergegeben.
5. Das Ereignis `EO` jedes Flipflops wird auf den Ereignis-Ausgang des jeweiligen Plug‑Adapters gelegt, sodass nachgeschaltete Bausteine über die neue Bit‑Information benachrichtigt werden.

## Technische Besonderheiten
- **Zustandsspeicherung**: Die Verwendung von D-Flipflops (E_D_FF) sorgt dafür, dass die Ausgangswerte auch nach dem Verarbeitungsereignis erhalten bleiben, bis ein neues Byte verarbeitet wird.
- **Parallele Ausgabe**: Alle acht Bits werden gleichzeitig aktualisiert, sobald das gemeinsam getaktete Ereignis `CNF` von `SPLIT_BYTE_INTO_BOOLS` anliegt.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch die Ausgangsadapter sind unidirektional (von der Applikation zur Ressource), daher eignet sich der Baustein für Senderichtungen, in denen nur eine Seite die Datenflüsse steuert.

## Zustandsübersicht
Der Baustein selbst besitzt keinen expliziten Zustandsautomaten. Das Verhalten ergibt sich aus der internen Kombination von:
- **SPLIT_BYTE_INTO_BOOLS**: Einzelschritt – erzeugt aus einem BYTE acht BOOL‑Werte und ein Bestätigungsereignis.
- **E_D_FF**: Jeder Flipflop speichert einen booleschen Wert bei steigender Taktflanke und hält ihn bis zum nächsten Takt.

Somit lässt sich der Baustein als **reiner kombinatorischer Splitter mit nachgeschalteten Haltegliedern** beschreiben.

## Anwendungsszenarien
- **Digitale Ausgabeansteuerung**: Ein Byte (z. B. von einem Kommunikationsadapter) wird in einzelne digitale Ausgänge aufgeteilt, die jeweils über AX‑Getter-Adapter mit Aktoren verbunden werden.
- **Zustandsüberwachung**: Ein Byte‑Signal (z. B. von einem Feldbus) wird in einzelne Statusbits zerlegt, die getrennt voneinander weiterverarbeitet oder visualisiert werden können.
- **Bitleveldatenvorbereitung**: Vor der Übergabe an bausteininterne Verarbeitungen, die einzelne boolesche Signale erwarten.

## Vergleich mit ähnlichen Bausteinen
- **SPLIT_BYTE_INTO_BOOLS**: Zerlegt ein Byte ebenfalls in boolesche Werte, gibt diese aber direkt als Datenausgänge weiter und erzeugt ein einziges Ereignis.  
  **SPLIT_AB_INTO_AX** erweitert dies um eine taktgesteuerte Zwischenspeicherung und die Ausgabe über AX‑Adapter, was eine saubere Ereignis‑Synchronisation mit nachfolgenden Bausteinen erlaubt.
- **Einfache Data‑Array‑Splitter**: Manche Bibliotheken bieten Bausteine, die Arrays in Einzelelemente aufteilen, jedoch ohne die zusätzliche Speicherung und Adapter‑Schnittstelle.

## Fazit
**SPLIT_AB_INTO_AX** ist ein spezialisierter Baustein für die Aufteilung eines BYTE‑Werts in acht stabil gehaltene boolesche Ausgänge über AX‑Adapter. Durch die Kombination von Splitter und Flipflops eignet er sich besonders für Szenarien, in denen die einzelnen Bits asynchron oder zeitlich versetzt abgegriffen werden müssen, ohne dass sich der Wert während der Verarbeitung ändert. Seine klare, adapterbasierte Schnittstelle erleichtert die Einbindung in modulare IEC 61499‑Anwendungen.