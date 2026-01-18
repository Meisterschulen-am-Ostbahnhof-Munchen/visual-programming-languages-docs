# XOR_3_BOOL

```{index} single: XOR_3_BOOL
```

<img width="1186" height="241" alt="image" src="https://github.com/user-attachments/assets/a3d5273a-10df-4b36-b9ea-460635fa84fc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `XOR_3_BOOL` ist ein standardisierter Baustein zur Berechnung der logischen Exklusiv-ODER-Verknüpfung (XOR) für drei boolesche Eingangswerte. Er ist als generischer Baustein implementiert und führt seine Operation bei jedem eingehenden Ausführungsereignis durch.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Löst die Berechnung der XOR-Funktion aus. Die mit diesem Ereignis verbundenen Daten (`IN1`, `IN2`, `IN3`) werden gelesen und verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Wird nach Abschluss der Berechnung ausgelöst. Dieses Ereignis liefert das berechnete Ergebnis über die zugehörige Datenausgabe `OUT`.

### **Daten-Eingänge**
*   **IN1** (BOOL): Erster boolescher Operand für die XOR-Operation.
*   **IN2** (BOOL): Zweiter boolescher Operand für die XOR-Operation.
*   **IN3** (BOOL): Dritter boolescher Operand für die XOR-Operation.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Das Ergebnis der dreifachen XOR-Verknüpfung der Eingänge `IN1`, `IN2` und `IN3`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Der Block arbeitet ereignisgesteuert. Bei jedem Eintreffen des Ereignisses `REQ` werden die aktuellen Werte der drei booleschen Eingänge `IN1`, `IN2` und `IN3` gelesen. Anschließend wird die logische XOR-Verknüpfung für alle drei Eingänge berechnet. Das Ergebnis wird am Datenausgang `OUT` ausgegeben und gleichzeitig wird das Bestätigungsereignis `CNF` aktiviert, um den Abschluss der Operation zu signalisieren.

Die logische Funktion entspricht: `OUT = (IN1 XOR IN2) XOR IN3`. Für drei Eingänge ist das Ergebnis genau dann `TRUE` (1), wenn eine ungerade Anzahl der Eingänge `TRUE` ist (also 1 oder 3 Eingänge).

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist mit dem Attribut `eclipse4diac::core::GenericClassName` als generischer Baustein (`'GEN_XOR'`) gekennzeichnet. Dies ermöglicht eine potenzielle Wiederverwendung der Logik für andere Datentypen, die die XOR-Operation unterstützen.
*   **Standardkonformität:** Der Block ist gemäß der Norm IEC 61131-3 als "standard boolean function" klassifiziert.
*   **Paketzuordnung:** Der Baustein ist dem Paket `iec61131::bitwiseOperators` zugeordnet.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers. Sein Verhalten ist rein kombinatorisch und ausschließlich von den aktuellen Eingangswerten bei Eintreffen des `REQ`-Ereignisses abhängig. Der einzige "Zustand" ist der idle-Zustand, in dem der Block auf das nächste `REQ`-Ereignis wartet.

## Anwendungsszenarien
*   **Paritätsprüfung:** Erkennung, ob eine ungerade Anzahl von drei booleschen Signalen aktiv ist.
*   **Steuerungslogik:** In speziellen Steuerungsalgorithmen, die eine "entweder-oder"-Logik über mehr als zwei Bedingungen benötigen.
*   **Verschlüsselung und Codierung:** Als grundlegende Komponente in einfachen kryptografischen oder fehlererkennenden Schaltungen (z.B. für Paritätsbits).
*   **Signalvergleich:** Feststellen, ob sich ein drittes Signal von der Kombination zweier anderer Signale unterscheidet.

## Vergleich mit ähnlichen Bausteinen
*   **XOR (2 Eingänge):** Der Standard-XOR-Baustein mit nur zwei Eingängen. `XOR_3_BOOL` erweitert diese Funktion auf drei Operanden. Siehe: [XOR_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_3.md)
*   **ODER / UND (3 Eingänge):** Diese Blöcke berechnen die logische ODER- bzw. UND-Verknüpfung aller Eingänge. Die XOR-Logik ist spezieller und unterscheidet sich insbesondere im Fall, wenn alle drei Eingänge `TRUE` sind (bei ODER=TRUE, bei UND=TRUE, bei XOR=TRUE).
*   **GEN_XOR:** Dies ist die generische Basis, von der `XOR_3_BOOL` als spezifische Instanz für den Datentyp `BOOL` abgeleitet ist.

## Fazit
Der `XOR_3_BOOL` Funktionsblock ist ein spezialisierter, normkonformer Baustein zur zuverlässigen Berechnung der dreifachen Exklusiv-ODER-Verknüpfung. Seine klare, ereignisgesteuerte Schnittstelle und die deterministische Funktionsweise machen ihn ideal für den Einsatz in Steuerungsanwendungen, die diese spezielle boolesche Logik erfordern. Als Instanz eines generischen Bausteins profitiert er zudem von den Wartungs- und Konsistenzvorteilen eines generischen Designs.