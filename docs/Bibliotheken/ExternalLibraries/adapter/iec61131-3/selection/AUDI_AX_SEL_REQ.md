# AUDI_AX_SEL_REQ


![AUDI_AX_SEL_REQ](./AUDI_AX_SEL_REQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_AX_SEL_REQ** realisiert eine binäre Auswahl zwischen zwei Eingangswerten. Er wird über einen Ereigniseingang oder einen Adapter getriggert und gibt den selektierten Wert sowie eine Bestätigung aus. Der FB ist speziell für die Verwendung mit einem unidirektionalen Adapter des Typs `AX` ausgelegt und eignet sich für Anwendungen, bei denen die Auswahl von einer externen Komponente gesteuert wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Service Request; löst die Auswahl aus |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Confirmation; wird nach erfolgter Auswahl ausgegeben |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN0` | UDINT | Erster auswählbarer Wert |
| `IN1` | UDINT | Zweiter auswählbarer Wert |

### **Daten-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `OUT` | UDINT | Selektierter Wert (entspricht entweder IN0 oder IN1) |

### **Adapter**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `G` | Socket: `adapter::types::unidirectional::AX` | Selector; liefert das Auswahlsignal (über Datenausgang `D1`) und ein Ereignis `E1` |

## Funktionsweise
Der FB enthält intern einen Baustein vom Typ `iec61131::selection::F_SEL`. Dieser führt die eigentliche Auswahl durch:  
- Der Datenausgang `G.D1` des Adapters wird mit dem Selektor-Eingang von `F_SEL` verbunden.  
- Der Wert von `F_SEL.OUT` ist gleich `IN0`, wenn `G.D1 = FALSE` ist, andernfalls gleich `IN1`.  

Das Ereignis `REQ` sowie das Adapter-Ereignis `G.E1` werden auf den `REQ`-Eingang von `F_SEL` geführt. Da die Ereignisverknüpfung als ODER-Verknüpfung implementiert ist, wird die Auswahl ausgelöst, sobald eines der beiden Ereignisse eintritt. Nach der Verarbeitung gibt `F_SEL` das Bestätigungsereignis `CNF` und den ausgewählten Wert `OUT` aus.

Die interne Verbindung stellt sicher, dass `OUT` stets den aktuell gültigen Wert (IN0 oder IN1) zum Zeitpunkt des auslösenden Ereignisses repräsentiert.

## Technische Besonderheiten
- **Adapterbasierte Selektion**: Der Auswahlwert wird nicht direkt als BOOL, sondern über einen Adapter bereitgestellt. Dies ermöglicht eine lose Kopplung und Wiederverwendung des Adaptertyps `AX`.  
- **Doppelte Triggerung**: Die Auswahl kann entweder durch ein externes `REQ`-Ereignis oder durch ein Ereignis vom Adapter (`G.E1`) angestoßen werden – oder durch beide gleichzeitig.  
- **Integrität**: Da der interne `F_SEL` auf IEC 61131 basiert, sind deterministische Auswahl- und Übertragungszeiten gewährleistet.  
- **Typstabilität**: Alle Datenports sind als `UDINT` (vorzeichenloser 32‑Bit‑Integer) definiert, sodass auch große Werte ohne Überlauf verarbeitet werden können.

## Zustandsübersicht
Der FB besitzt keine eigene Zustandsmaschine. Das Verhalten ergibt sich vollständig aus dem internen `F_SEL`-Baustein:  
- **Warten**: Kein ausstehendes Ereignis – keine Ausgabe.  
- **Auswahl**: Nach Eintreffen von `REQ` oder `G.E1` wird `OUT` gesetzt und `CNF` ausgegeben.

## Anwendungsszenarien
- **Umschaltung von Betriebsarten**: Auswahl zwischen zwei Sollwerten (z. B. Geschwindigkeit, Druck) in Abhängigkeit eines externen Selektors.  
- **Quellenumschaltung**: Wahl zwischen zwei Signalquellen (z. B. Messdaten von unterschiedlichen Sensoren) und Ausgabe des aktuell gültigen Werts.  
- **Sicherheitslogik**: Trennung von Normalbetrieb und Notbetrieb durch binäre Auswahl kritischer Parameter.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑MUX (IEC 61131 MUX)**: Ein MUX wählt aus mehr als zwei Eingängen aus und benötigt einen Index. Der `AUDI_AX_SEL_REQ` ist auf zwei Eingänge beschränkt und verwendet einen Adapter statt eines direkten BOOL-Eingangs.  
- **BOOL‑SEL‑Bausteine**: Einfache Selektoren mit BOOL‑Eingabe haben oft nur einen Ereigniseingang. Dieser FB erlaubt zusätzlich die Triggerung über den Adapter, was eine flexible Ansteuerung ermöglicht.  
- **Adapterbasierte Lösungen**: Im Vergleich zu fest verdrahteten Selektoren bietet der Adapter eine höhere Modularität – der auslösende Adapter kann je nach Kontext ausgetauscht werden.

## Fazit
Der `AUDI_AX_SEL_REQ` ist ein kompakter, aber flexibler Binärselektor, der sich durch die Kombination von Adapteranbindung und doppelter Triggerung von einfachen Selektoren abhebt. Er eignet sich besonders für modulare Automatisierungslösungen, bei denen das Auswahlsignal von einer externen Komponente bereitgestellt wird und eine zuverlässige, sofortige Weiterleitung des Ergebnisses erforderlich ist. Die Verwendung standardisierter IEC‑Typen und klarer Schnittstellen erleichtert die Integration in bestehende Steuerungsarchitekturen.