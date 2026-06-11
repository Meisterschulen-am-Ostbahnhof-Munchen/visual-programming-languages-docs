# AUDI_TO_AW


![AUDI_TO_AW](./AUDI_TO_AW.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_TO_AW** ist ein Composite-Funktionsblock zur Konvertierung eines **AUDI-Adapter** (UDINT) in einen **AW-Adapter** (WORD). Er dient als unidirektionale Brücke zwischen unterschiedlichen Datentypen und ermöglicht die nahtlose Integration von Komponenten, die auf unterschiedlichen Adapter-Schnittstellen basieren.

Der Baustein kapselt die Konvertierungslogik und wird typischerweise in Automatisierungsprojekten nach IEC 61499 eingesetzt, die eine Anpassung von Datentypen zwischen Adaptern erfordern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| (über AUDI_IN.E1) | EVENT | Ereignis, das die Konvertierung anstößt (bereitgestellt durch den angeschlossenen AUDI-Adapter) |

### **Ereignis-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| (über AW_OUT.E1) | EVENT | Ausgangsereignis nach erfolgreicher Konvertierung (bereitgestellt durch den AW-Adapter) |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| (über AUDI_IN.D1) | UDINT | 32-Bit unsigned Integer, der konvertiert werden soll (bereitgestellt durch den AUDI-Adapter) |

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| (über AW_OUT.D1) | WORD | 16-Bit unsigned Integer (Ergebnis der Konvertierung, bereitgestellt durch den AW-Adapter) |

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| AUDI_IN | adaper::types::unidirectional::AUDI | Socket (Eingang) | Empfängt das UDINT-Signal und das zugehörige Ereignis |
| AW_OUT | adaper::types::unidirectional::AW | Plug (Ausgang) | Gibt das konvertierte WORD-Signal und das Ausgangsereignis weiter |

## Funktionsweise
Der Funktionsblock arbeitet als **Composite FB**, der einen einzelnen IEC 61131-Konvertierungsbaustein `F_UDINT_TO_WORD` enthält. Die Verarbeitung erfolgt nach folgendem Ablauf:

1. Der Socket `AUDI_IN` empfängt ein Ereignis an seinem Ereigniseingang `E1` und den dazugehörigen Datenwert `D1` (UDINT).
2. Dieses Ereignis wird intern an den `REQ`-Eingang des Konvertierungsbausteins weitergeleitet, während der UDINT-Wert an den `IN`-Eingang übergeben wird.
3. Der Konvertierungsbaustein wandelt den UDINT-Wert in ein WORD um und meldet die Fertigstellung über seinen `CNF`-Ausgang.
4. Das `CNF`-Ereignis wird an den Ereignisausgang `E1` des Plug `AW_OUT` weitergegeben, und das konvertierte WORD wird an dessen Datenausgang `D1` ausgegeben.

Der gesamte Vorgang ist **ereignisgesteuert** und erfolgt innerhalb eines einzigen Ausführungsschrittes.

## Technische Besonderheiten
- **Unidirektionaler Datenfluss**: Der FB konvertiert ausschließlich von AUDI (UDINT) zu AW (WORD); eine Rückwärtskonvertierung ist nicht vorgesehen.
- **Composite-Architektur**: Die interne Logik ist vollständig durch einen einzelnen Standard-Konvertierungsbaustein realisiert, wodurch der FB leicht nachvollziehbar und wartbar ist.
- **Verwendung von IEC 61131-Bibliotheken**: Der Baustein `F_UDINT_TO_WORD` stammt aus der `iec61131::conversion`-Bibliothek, was eine hohe Portabilität und Standardkonformität gewährleistet.
- **Keine eigene Zustandsmaschine**: Der FB besitzt keinen ECC (Execution Control Chart) und arbeitet rein datenflussorientiert.

## Zustandsübersicht
Der Funktionsblock besitzt **keinen Zustandsautomaten**. Die Verarbeitung erfolgt ereignisgesteuert und deterministisch gemäß der internen Verdrahtung. Es gibt keine internen Zustände oder Latenzen.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Ein System liefert Daten über einen AUDI-Adapter (UDINT), ein nachfolgender Funktionsblock erwartet jedoch einen AW-Adapter (WORD). Der AUDI_TO_AW wandelt die Daten ohne manuelle Programmierarbeit an.
- **Datenkonsolidierung**: In einer Steuerung müssen mehrere Sensordaten mit unterschiedlichen Adaptertypen zusammengeführt werden. Der Baustein dient als Konvertierungsglied.
- **Legacy-Integration**: Ältere Komponenten, die auf UDINT basieren, sollen in eine moderne WORD-basierte Architektur eingebunden werden.

## Vergleich mit ähnlichen Bausteinen
- **F_WORD_TO_UDINT** (analog, aber in umgekehrter Richtung): Konvertiert WORD nach UDINT und erwartet einen AW-Eingang sowie einen AUDI-Ausgang.
- **Allgemeine Konvertierungsbausteine** wie `F_UDINT_TO_DINT` oder `F_UDINT_TO_REAL` bieten ähnliche Funktionalität, arbeiten jedoch mit anderen Datentypen und ohne Adapter-Anbindung.
- **Eigene Adapter-Konverter** können durch Kombination mehrerer Konvertierungsbausteine und Adapter realisiert werden, sind jedoch weniger gekapselt als dieser Composite-FB.

## Fazit
Der **AUDI_TO_AW** ist ein spezialisierter, aber essenzieller Baustein für die Adapter-basierte Kommunikation in IEC 61499-Systemen. Durch die Verwendung eines standardisierten Konvertierungsbausteins und die Kapselung in einem Composite-FB bietet er eine saubere, wiederverwendbare und testbare Lösung für die Umsetzung von UDINT- auf WORD-Daten innerhalb eines unidirektionalen Adapterpfades.