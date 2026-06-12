# ASSEMBLE_AB_FROM_AQ


![ASSEMBLE_AB_FROM_AQ](./ASSEMBLE_AB_FROM_AQ.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASSEMBLE_AB_FROM_AQ** dient der Zusammenführung von vier **AQ**-Quartal-Adaptern (Quarter Byte) zu einem einzelnen **AB**-Byte-Adapter. Er kapselt die Logik, aus vier eingehenden 4-Bit-Werten ein vollständiges Byte zu assemblieren und über eine standardisierte Adapter-Schnittstelle bereitzustellen. Der Baustein ist speziell für die Verwendung in verteilten Automatisierungssystemen nach IEC 61499 ausgelegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine dedizierten Ereignis-Eingänge auf der obersten Ebene.  
Alle eingehenden Ereignisse werden über die **Adapter-Sockets** übertragen. Jeder Applikationsadapter vom Typ `AQ` verfügt über einen Ereignisausgang `E1`, der intern mit dem REQ-Eingang des Assemblierungsbausteins verbunden ist.

### **Ereignis-Ausgänge**

- **OUT.E1**: Ereignisausgang des Byte-Adapters. Wird aktiv, sobald ein neues Byte vollständig assembliert und über den internen Flipflop getaktet wurde.

### **Daten-Eingänge**

Die Daten werden über die **Adapter-Sockets** in Form von 4-Bit-Werten (Nibbles) eingelesen:
- **QUARTER_BYTE_00.D1**: Nibble für die niederwertigsten Bits (Bits 0..3)
- **QUARTER_BYTE_01.D1**: Nibble für Bits 4..7
- **QUARTER_BYTE_02.D1**: Nibble für Bits 8..11  
- **QUARTER_BYTE_03.D1**: Nibble für Bits 12..15  

(Hinweis: Die tatsächliche Bit-Reihenfolge kann je nach Implementierung des internen `ASSEMBLE_BYTE_FROM_QUARTERS`-Bausteins variieren; üblicherweise erfolgt die Zusammenführung in aufsteigender Reihenfolge.)

### **Daten-Ausgänge**

- **OUT.D1**: Ausgang des Byte-Adapters. Liefert das fertig zusammengesetzte Byte (8 Bit) als ganzzahligen Wert.

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AQ` | Socket (Eingang) | `QUARTER_BYTE_00` .. `QUARTER_BYTE_03` | Vier Quartal-Adapter, die jeweils ein Nibble und ein Ereignis liefern. |
| `adapter::types::unidirectional::AB` | Plug (Ausgang) | `OUT` | Byte-Adapter, der das zusammengesetzte Byte und ein Ereignis bereitstellt. |

## Funktionsweise

Der FB arbeitet vollständig ereignisgesteuert. Sobald eines der vier angeschlossenen AQ-Adapter ein Ereignis auf seinem `E1`-Ausgang sendet, wird dieses an den internen Baustein `ASSEMBLE_BYTE_FROM_QUARTERS` weitergeleitet (Ereignis `REQ`). Gleichzeitig werden die aktuellen Nibble-Werte von allen vier Quartal-Adapter-Eingängen über Data Connections an den Assemblierungsbaustein übergeben.

Der Assemblierungsbaustein setzt die vier Nibble intern zu einem 8-Bit-Wert zusammen. Nach erfolgreicher Verarbeitung sendet er ein Bestätigungsereignis `CNF` an den flankengesteuerten D-Flipflop (`E_D_FF_ANY`). Der Flipflop übernimmt den Datenwert (vom Assemblierungsausgang) bei steigender Flanke und gibt ihn an den Datenausgang `OUT.D1` weiter. Gleichzeitig wird das Ausgangsereignis `OUT.E1` generiert.

Somit erfolgt die Ausgabe immer taktsynchron: Erst wenn ein vollständiges Byte berechnet wurde, wird es durchgeschaltet. Mehrfache Ereignisse auf verschiedenen Quartal-Eingängen führen zu wiederholten Berechnungen, wobei jeweils alle vier aktuellen Nibble-Werte neu verarbeitet werden.

## Technische Besonderheiten

- **Interne Kaskadierung**: Der FB verwendet zwei interne Bausteine – `ASSEMBLE_BYTE_FROM_QUARTERS` für die Bit-Kombination und `E_D_FF_ANY` zur flankengesteuerten Ausgabe.
- **Ereignissynchronisation**: Jedes eingehende Ereignis triggert die Assemblierung; es ist nicht erforderlich, dass alle vier Adapter gleichzeitig ein Ereignis liefern – der Baustein arbeitet mit den jeweils aktuellen Daten.
- **Adapter-Schnittstelle**: Die Ein- und Ausgabe erfolgt ausschließlich über unidirektionale Adapter, was die Wiederverwendung in Applikationsnetzwerken vereinfacht.
- **Keine Zustandsspeicherung im FB selbst**: Der FB ist ein reiner Netzwerkbaustein, der Logik vollständig delegiert.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen Zustandsautomaten. Die interne Logik wird durch die Zustände von `ASSEMBLE_BYTE_FROM_QUARTERS` und `E_D_FF_ANY` bestimmt:

1. **Warten auf Eingangsereignis**: Nach Initialisierung oder nach einer Verarbeitung wartet der FB auf ein Ereignis von einem der AQ-Adapter.
2. **Assemblierung**: Bei `REQ` werden die Nibble zusammengesetzt; der D-Flipflop wartet auf das `CNF`-Ereignis.
3. **Ausgabe**: Nach Taktung des Flipflops wird das Ergebnis an den OUT-Adapter gesendet. Danach kehrt der FB in den Wartezustand zurück.

## Anwendungsszenarien

- **Zusammenführung von Busdaten**: Wenn vier getrennte 4-Bit-Leitungen (z. B. von Sensoren oder Datenquellen) zu einem Byte zusammengefasst werden müssen.
- **Adapter-basierte Datenintegration**: In Systemen, die auf IEC 61499-Adapterarchitektur setzen, kann dieser FB als generischer „Byte-Assembler“ in der Netzwerkebene dienen.
- **Protokollwandlung**: Von einem Viertel-Byte-Protokoll auf ein Byte-Protokoll, z. B. in der seriellen Kommunikation.
- **Test- und Simulationsumgebungen**: Zum einfachen Zusammenschalten von Testadaptern.

## Vergleich mit ähnlichen Bausteinen

- **ASSEMBLE_BYTE_FROM_QUARTERS** (direkt): Dieser Baustein arbeitet ohne Adapter – er erwartet vier separate Daten- und Ereigniseingänge. Der vorliegende FB kapselt diese Schnittstelle in Adapter, was die Modularität erhöht.
- **ARRAY_TO_BYTE** oder ähnliche Funktionsbausteine: Oft auf Basis von Arrays implementiert; hier spezifisch für genau vier Nibble und mit Adapterunterstützung.
- **Eigener Adapter-basierter Assembler**: Falls benötigt, kann `ASSEMBLE_AB_FROM_AQ` durch Anpassung der internen Bausteine leicht für andere Datenbreiten modifiziert werden.

## Fazit

Der Funktionsblock **ASSEMBLE_AB_FROM_AQ** bietet eine elegante, adapterbasierte Lösung zur Zusammenführung von vier Viertel-Byte-Datenströmen zu einem vollständigen Byte. Dank der internen Kaskadierung aus Assemblierungslogik und flankengesteuerter Ausgabe ist das Verhalten deterministisch und gut in ereignisgesteuerte Systeme integrierbar. Er eignet sich besonders für modulare Automatisierungsprojekte, die auf IEC 61499-Adapterarchitektur aufbauen und eine saubere Trennung von Daten- und Ereignisflüssen erfordern.