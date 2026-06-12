# AUDI_UDINT_EQ


![AUDI_UDINT_EQ](./AUDI_UDINT_EQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_UDINT_EQ** führt einen Vergleich zweier Werte vom Typ `UDINT` auf Gleichheit durch. Der erste Wert wird über einen Socket-Adapter (`IN1`) bezogen, der zweite über den direkten Dateneingang `IN2`. Das Ergebnis wird als boolescher Wert über einen Plug-Adapter (`OUT`) ausgegeben. Der Vergleich wird durch ein Ereignis ausgelöst – entweder durch das externe Event `REQ` oder durch ein Ereignis vom Socket-Adapter `IN1`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Event | Beschreibung |
|-------|--------------|
| `REQ` | Service-Request: Startet den Vergleich. Der Wert von `IN2` wird mit dem aktuellen Wert des Adapters `IN1` verglichen. |

Hinweis: Zusätzlich kann der Vergleich auch durch ein Ereignis vom Socket-Adapter `IN1` (dessen Event `E1`) gestartet werden. Dies ist intern im FB-Netzwerk verdrahtet und erlaubt eine ereignisgesteuerte Aktualisierung bei Änderung des Eingabewertes.

### **Ereignis-Ausgänge**
Der FB besitzt keine direkten Event-Ausgänge. Das Ergebnis des Vergleichs wird jedoch über den Plug-Adapter `OUT` ausgegeben, welcher den Event `E1` führt (siehe Adapter). Der Ausgangs-Event wird nach Abschluss des Vergleichs generiert.

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| `IN2` | `UDINT` | Zweiter Vergleichswert (direkter Eingang). |

Hinweis: Der erste Vergleichswert wird über den Socket-Adapter `IN1` bezogen (dessen Dateneingang `D1`).

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Das Vergleichsergebnis (BOOL) wird über den Plug-Adapter `OUT` ausgegeben (dessen Datenausgang `D1`).

### **Adapter**
| Typ | Richtung | Beschreibung |
|-----|----------|--------------|
| `IN1` – Socket | Eingang | Adapter vom Typ `adapter::types::unidirectional::AUDI`. Liefert den ersten Vergleichswert (Dateneingang `D1`) und kann ein Ereignis (`E1`) zum Starten des Vergleichs senden. |
| `OUT` – Plug | Ausgang | Adapter vom Typ `adapter::types::unidirectional::AX`. Gibt das Vergleichsergebnis als Booleschen Wert (`D1`) aus und erzeugt ein Ereignis (`E1`) nach Abschluss. |

## Funktionsweise
1. Der FB wartet auf ein Start-Ereignis – entweder am externen Event-Eingang `REQ` oder am Event `E1` des Socket-Adapters `IN1`.
2. Bei Ereigniseingang werden die Werte `IN1.D1` (vom Adapter) und `IN2` (vom direkten Eingang) an den internen Vergleichsbaustein `F_EQ` (vom Typ `iec61131::comparison::F_EQ`) übergeben.
3. Der Datenausgang von `F_EQ` ist `true`, wenn beide Werte gleich sind, andernfalls `false`.
4. Dieses Ergebnis wird an den Datenausgang `OUT.D1` des Plug-Adapters übergeben.
5. Gleichzeitig wird das Event `OUT.E1` ausgelöst, um die Ausgangsseite über das abgeschlossene Ergebnis zu informieren.

## Technische Besonderheiten
- **Adapterbasierte Ein-/Ausgabe**: Statt direkter Datenports werden Adapter für die erste Eingangsgröße und die Ausgangsgröße verwendet. Dies ermöglicht eine lose Kopplung und eine einfache Wiederverwendung in verschiedenen Kontexten (z.B. Bus-Systeme oder gekapselte Werte).
- **Doppelte Auslösemöglichkeit**: Der Vergleich kann sowohl über das externe Event `REQ` als auch über ein Ereignis des Eingangs-Adapters `IN1` gestartet werden. Dadurch kann der Baustein entweder zyklisch oder änderungsgesteuert arbeiten.
- **Unidirektionale Adapter**: Sowohl der Socket (`IN1`) als auch der Plug (`OUT`) sind als unidirektionale Adapter deklariert, was eine klare Daten- und Ereignisflussrichtung vorgibt.
- **Interne Nutzung von `F_EQ`**: Der eigentliche Vergleich wird durch den IEC 61131-3 Standard-Baustein `F_EQ` realisiert, der speziell für 64‑Bit-Vergleiche ausgelegt ist (hier jedoch auf `UDINT` angewendet).

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine. Er arbeitet rein ereignisgesteuert:
- **Idle**: Warten auf ein Ereignis (`REQ` oder `IN1.E1`).
- **Berechnung**: Sobald ein Ereignis eintrifft, wird der Vergleich ausgeführt und das Ergebnis an `OUT` übergeben.
- **Abschluss**: Nach Ausgabe des Ergebnisses und des Folge-Events kehrt der FB sofort in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Überwachung zweier Messwerte**: Ein Sensorwert (z.B. Drehzahl) wird über den Adapter `IN1` eingelesen, ein Sollwert über `IN2`. Bei Gleichheit wird ein Signal erzeugt.
- **Modulare Kopplung**: Der Baustein kann in größeren Netzwerken eingebettet werden, wo Adapter als standardisierte Schnittstellen zwischen Komponenten dienen.
- **Ereignisgesteuerte Prozesse**: Wenn der Eingangswert `IN1` sich ändert, kann automatisch ein Vergleich ausgelöst werden, ohne dass ein externer Takt benötigt wird.

## Vergleich mit ähnlichen Bausteinen
- **`F_EQ` (direkt)**: Der Standard-Vergleichsbaustein erwartet zwei skalare Eingänge und liefert einen Bool-Ausgang. Der `AUDI_UDINT_EQ` kapselt diesen und erweitert ihn um Adapter für eine flexiblere Einbindung.
- **`AUDI_UDINT_NE` (Ungleich)**: Ein analoger Baustein für den Ungleich-Vergleich; die Schnittstelle und Funktionsweise sind identisch, nur die Vergleichslogik unterscheidet sich.
- **Bausteine mit direktem Dateneingang**: Herkömmliche Vergleichsbausteine (z.B. `EQ`, `NE`) nutzen oft nur direkte Datenports; der Adapter-Ansatz erhöht die Wiederverwendbarkeit in heterogenen Systemen.

## Fazit
Der `AUDI_UDINT_EQ` ist ein ereignisgesteuerter Vergleichsbaustein für `UDINT`-Werte, der die Flexibilität von Adaptern nutzt. Durch die doppelte Auslösemöglichkeit und die standardisierte Adapter-Schnittstelle eignet er sich besonders für modulare und erweiterbare Automatisierungslösungen. Die interne Verwendung des bewährten `F_EQ`-Bausteins garantiert eine zuverlässige, normgerechte Vergleichslogik.