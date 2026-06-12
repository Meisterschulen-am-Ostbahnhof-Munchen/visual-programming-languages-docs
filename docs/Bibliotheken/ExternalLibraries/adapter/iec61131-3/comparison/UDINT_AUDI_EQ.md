# UDINT_AUDI_EQ


![UDINT_AUDI_EQ](./UDINT_AUDI_EQ.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `UDINT_AUDI_EQ` führt einen Vergleich zweier Werte auf Gleichheit durch. Der erste Wert wird über den Dateneingang `IN1` bereitgestellt, der zweite Wert wird über einen Adapter-Socket (`IN2`) empfangen. Das Ergebnis des Vergleichs (wahr, wenn beide Werte gleich sind) wird über einen Adapter-Plug (`OUT`) ausgegeben. Der Baustein löst die Vergleichsoperation aus, sobald ein Ereignis am Eingang `REQ` oder am Adapter-Socket `IN2` anliegt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar         |
|------|-------|-------------------|
| REQ  | Event | Service Request   |

### **Ereignis-Ausgänge**

Keine direkten Ereignisausgänge. Das Ergebnis-Event wird über den Adapter-Plug `OUT` bereitgestellt.

### **Daten-Eingänge**

| Name | Typ              | Kommentar        |
|------|------------------|------------------|
| IN1  | ANY_ELEMENTARY   | Input value 1    |

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Das Ergebnis wird über den Adapter-Plug `OUT` als Datum bereitgestellt.

### **Adapter**

| Name | Typ                                                    | Richtung | Kommentar                                      |
|------|--------------------------------------------------------|----------|------------------------------------------------|
| IN2  | adapter::types::unidirectional::AUDI                   | Socket   | Input value 2                                  |
| OUT  | adapter::types::unidirectional::AX                     | Plug     | value 1 = value2 = true                        |

- **IN2** (Socket): Über diesen Adapter wird der zweite Vergleichswert (sowohl Ereignis als auch Datum) von außen an den Baustein übergeben. Das Ereignis `IN2.E1` triggert den Vergleich, das Datum `IN2.D1` enthält den Wert.
- **OUT** (Plug): Über diesen Adapter gibt der Baustein das Vergleichsergebnis nach außen. Das Ereignis `OUT.E1` signalisiert die Fertigstellung, das Datum `OUT.D1` enthält das Ergebnis (vom Typ BOOL).

## Funktionsweise

Der Baustein führt einen Gleichheitsvergleich durch. Intern wird der Standard-Funktionsblock `F_EQ` (`iec61131::comparison::F_EQ`) verwendet.

1. **Auslösung**: Der Vergleich wird gestartet, sobald ein Ereignis am Eingang `REQ` oder am Adapter-Socket `IN2.E1` eintrifft.
2. **Operation**: Das Ereignis triggert den internen `F_EQ`-Baustein, der die Werte an `IN1` und `IN2.D1` vergleicht.
3. **Ergebnis**: Nach Abschluss des Vergleichs sendet `F_EQ` ein Ereignis an seinem Ausgang `CNF`. Dieses Ereignis wird an den Adapter-Plug `OUT.E1` weitergeleitet. Gleichzeitig wird das Vergleichsergebnis (BOOL) von `F_EQ.OUT` an den Datenausgang `OUT.D1` übergeben.

Der Baustein arbeitet asynchron: Sobald ein entsprechendes Ereignis anliegt, wird der Vergleich durchgeführt und das Ergebnis über den Plug ausgegeben.

## Technische Besonderheiten

- **Adapterbasierte Ein-/Ausgabe**: Sowohl der zweite Eingangswert als auch das Ergebnis werden über Adapter-Schnittstellen kommuniziert, was eine flexible Anbindung an andere Komponenten oder Systeme ermöglicht.
- **Generischer Datentyp**: `IN1` ist als `ANY_ELEMENTARY` deklariert, sodass der Baustein mit verschiedenen elementaren Datentypen (z. B. INT, REAL, BOOL) arbeiten kann. Der Adapter `IN2` muss denselben Datentyp liefern.
- **Interner Standardbaustein**: Die Vergleichsfunktion wird durch den standardisierten IEC 61131-Funktionsblock `F_EQ` realisiert, was Korrektheit und Wiederverwendbarkeit sicherstellt.
- **Keine Zustandsautomaten**: Der Baustein ist rein funktional und besitzt kein eigenes Zustandsmodell – die Logik wird ausschließlich über das interne FBNetzwerk abgebildet.

## Zustandsübersicht

Der Baustein besitzt keine expliziten Zustände oder ein Zustandsdiagramm. Das Verhalten wird rein durch die Ereignis- und Datenflüsse im internen Netzwerk bestimmt. Nach jedem eingehenden Ereignis erfolgt eine unmittelbare Verarbeitung.

## Anwendungsszenarien

- **Vergleich von Messwerten**: Ein Sensorwert (`IN1`) wird mit einem Referenzwert verglichen, der über eine Adapterverbindung von einem anderen System bereitgestellt wird.
- **Rückmeldung von Schwellwerten**: Der Baustein kann in Steuerungsanwendungen eingesetzt werden, um zu prüfen, ob ein Prozesswert einen Sollwert erreicht hat, und das Ergebnis als Bool-Signal an eine nachgelagerte Logik weiterzugeben.
- **Verteilte Systeme**: Dank der Adapter eignet sich der Baustein für den Einsatz in Systemen, die eine lose Kopplung zwischen Komponenten erfordern, z. B. in der Fertigungsautomatisierung oder Gebäudesteuerung.

## Vergleich mit ähnlichen Bausteinen

- **Standard-Vergleichsbausteine** (z. B. `F_EQ`, `F_NE`, `F_GT`): Diese haben direkte Daten-Eingänge und -Ausgänge. Der `UDINT_AUDI_EQ` hingegen verwendet Adapter für den zweiten Eingang und den Ausgang. Dies erhöht die Flexibilität für modulare und vernetzte Architekturen.
- **Adapterbasierte Bausteine**: Im Gegensatz zu einfachen Vergleichsbausteinen mit festen Schnittstellen erlaubt dieser Baustein eine dynamische Anbindung des zweiten Vergleichswerts über einen Socket, was in hierarchischen oder wiederverwendbaren Komponenten vorteilhaft ist.

## Fazit

Der `UDINT_AUDI_EQ` ist ein vielseitiger Funktionsblock zum Vergleichen zweier Werte auf Gleichheit. Durch die Verwendung von Adaptern für Eingang und Ausgang wird eine entkoppelte Kommunikation ermöglicht, die besonders in komplexen Automatisierungssystemen oder verteilten Umgebungen Vorteile bietet. Der Baustein ist einfach zu integrieren und verlässt sich auf bewährte Standardfunktionen für die Vergleichslogik.