# AUDI_UDINT_LT


![AUDI_UDINT_LT](./AUDI_UDINT_LT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_UDINT_LT** realisiert einen „Kleiner als“-Vergleich für zwei Werte vom Typ **UDINT** (Unsigned Double Integer). Er entspricht der IEC 61131‑3 Klassifikation „standard comparison function“. Der Baustein kapselt einen internen Vergleichsbaustein (F_LT) und stellt über Adapter eine standardisierte, ereignisgesteuerte Schnittstelle bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Service Request – löst den Vergleich aus |

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkten Ereignis-Ausgänge. Das Ergebnisereignis wird über den Adapter‑Plug **OUT** (Ereignis **E1**) bereitgestellt.

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| IN2  | UDINT | Input value 2 (zweiter Vergleichswert) |

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Daten-Ausgänge. Das Vergleichsergebnis wird über den Adapter‑Plug **OUT** (Daten **D1**, Typ BOOL) bereitgestellt.

### **Adapter**
| Rolle | Name | Typ | Kommentar |
|-------|------|-----|-----------|
| Socket | IN1  | adapter::types::unidirectional::AUDI | Input value 1 – liefert Ereignis (E1) und Daten (D1) |
| Plug   | OUT  | adapter::types::unidirectional::AX   | Vergleichsergebnis (D1 = TRUE wenn IN1 < IN2) und Bestätigungsereignis (E1) |

*Hinweis:* Die Adapter vom Typ **AUDI** und **AX** sind unidirektional und enthalten je ein Ereigniselement (E1) und ein Datenelement (D1).

## Funktionsweise
1. Ein **REQ**‑Ereignis startet die Verarbeitung.
2. Der Baustein liest **IN1** (über den Socket‑Adapter) und **IN2** (direkter Dateneingang).
3. Intern wird der Baustein `F_LT` („less than“ aus der IEC 61131‑3 Vergleichsbibliothek) ausgeführt:
   - **F_LT.IN1** erhält den Wert von **IN1.D1**
   - **F_LT.IN2** erhält den Wert von **IN2**
   - Das Ergebnis (BOOL) wird an **F_LT.OUT** ausgegeben.
4. Nach Abschluss des Vergleichs sendet **F_LT** ein Ereignis an **OUT.E1** und das Ergebnis wird auf **OUT.D1** ausgegeben.

Dadurch kann der aufrufende Kontext asynchron über den Adapter **OUT** den Vergleichswert und das Bestätigungsereignis empfangen.

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle:** Die Kopplung erfolgt über Sockets und Plugs, was eine lose Kopplung und Wiederverwendung in serviceorientierten Architekturen ermöglicht.
- **Kapselung eines Standard‑Vergleichsbausteins:** Der FB nutzt intern den etablierten `F_LT`‑Baustein, sodass keine eigene Vergleichslogik implementiert werden muss.
- **Keine Zustandsinformation:** Der Baustein ist zustandslos – jeder Aufruf von **REQ** führt zu einer sofortigen Berechnung.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine; die gesamte Logik ist ereignisgesteuert und zustandslos.

## Anwendungsszenarien
- **Grenzwertüberwachung:** Prüfen, ob ein Messwert (IN1) unter einem Schwellwert (IN2) liegt.
- **Steuerungsbedingungen:** Erzeugen eines Signals, wenn eine Zählervariable kleiner als ein vorgegebener Wert ist.
- **Adapterbasierte Datenflüsse:** Einbinden in komplexe Netzwerke, in denen Daten und Ereignisse über standardisierte Adapter ausgetauscht werden.

## Vergleich mit ähnlichen Bausteinen
- **AUDI_UDINT_GT** (größer als) und **AUDI_UDINT_EQ** (gleich) bieten analoge Vergleiche für UDINT.
- Im Unterschied zu direkten IEC‑Operatoren (z.B. `IN1 < IN2` in ST) ermöglicht der FB eine ereignisgesteuerte und komponentenorientierte Integration in 4diac‑Netzwerke.
- Andere Vergleichsbausteine ohne Adapter (z.B. `F_LT`) können direkt verwendet werden, bieten aber keine standardisierte Adapter‑Schnittstelle.

## Fazit
Der **AUDI_UDINT_LT** ist ein spezialisierter Vergleichsbaustein für den Datentyp UDINT, der sich durch seine adapterbasierte Ereignis‑ und Datenübertragung auszeichnet. Er eignet sich besonders für modulare Steuerungsanwendungen, die lose Kopplung und Wiederverwendbarkeit erfordern.