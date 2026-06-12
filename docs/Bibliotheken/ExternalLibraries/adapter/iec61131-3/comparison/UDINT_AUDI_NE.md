# UDINT_AUDI_NE


![UDINT_AUDI_NE](./UDINT_AUDI_NE.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **UDINT_AUDI_NE** dient dem Vergleich zweier Werte auf Ungleichheit („not equal“). Er ist als zusammengesetzter Baustein (Composite) realisiert und nutzt Adapter für den zweiten Eingang und den Ausgang, um eine flexible Kopplung mit anderen Komponenten zu ermöglichen. Der Baustein ist für den Einsatz in Automatisierungssystemen konzipiert, die auf der 4diac-IDE basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar        |
|------|-------|------------------|
| REQ  | Event | Service Request  |

Der Ereignis-Eingang **REQ** löst den Vergleichsprozess aus.

### **Ereignis-Ausgänge**

Keine expliziten Ereignis-Ausgänge. Die Ergebnisweitergabe erfolgt über den Adapter **OUT** (siehe Abschnitt Adapter).

### **Daten-Eingänge**

| Name | Typ             | Kommentar        |
|------|-----------------|------------------|
| IN1  | ANY_ELEMENTARY  | Eingangswert 1   |

Der Daten-Eingang **IN1** nimmt den ersten zu vergleichenden Wert entgegen. Der zweite Wert wird über den Socket **IN2** bereitgestellt.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Das Vergleichsergebnis (Boolescher Wert: TRUE bei Ungleichheit, FALSE bei Gleichheit) wird über den Adapter **OUT** ausgegeben.

### **Adapter**

| Richtung | Name | Typ                          | Kommentar                          |
|----------|------|------------------------------|------------------------------------|
| Plug     | OUT  | `adapter::types::unidirectional::AX`   | Ausgabe: TRUE, wenn IN1 != Wert von IN2 |
| Socket   | IN2  | `adapter::types::unidirectional::AUDI` | Eingang für den zweiten Wert       |

- **OUT** (Plug) überträgt das Ergebnis als Booleschen Wert über das Datenfeld `D1` und wird durch das Ereignis `E1` gesteuert.
- **IN2** (Socket) liefert den zweiten Vergleichswert über das Datenfeld `D1` und das Ereignis `E1` (z. B. zum Triggern des Vergleichs).

## Funktionsweise

Der Baustein führt einen Ungleichheitsvergleich zwischen zwei Werten durch:

1. Der **REQ**-Ereignis-Eingang oder das Ereignis **IN2.E1** starten den Vergleich.
2. Intern wird der Funktionsbaustein **F_NE** (Typ `iec61131::comparison::F_NE`) verwendet, der die beiden Werte **IN1** und **IN2.D1** auf Ungleichheit prüft.
3. Das Ergebnis (Boolescher Wert) wird über **OUT.D1** ausgegeben.
4. Der Ausgangsadapter **OUT** signalisiert über sein Ereignis **E1**, dass das Ergebnis gültig ist.

Die Steuerung erfolgt ereignisgesteuert: Der Vergleich wird entweder durch das externe Ereignis **REQ** oder durch das vom Adapter kommende Ereignis **IN2.E1** ausgelöst (ODER-Verknüpfung). Dadurch kann der Baustein sowohl zyklisch als auch datengetrieben arbeiten.

## Technische Besonderheiten

- **Adapterbasierte Ein-/Ausgabe:** Der zweite Eingang und der Ausgang sind als Adapter realisiert. Dies ermöglicht eine lose Kopplung und Wiederverwendbarkeit in verschiedenen Kontexten.
- **Unterstützung beliebiger elementarer Datentypen:** Der Daten-Eingang **IN1** ist vom Typ `ANY_ELEMENTARY`, sodass der Baustein mit allen IEC-61131-3-elementaren Datentypen (z. B. INT, REAL, BOOL) arbeiten kann. Der Adapter **IN2** sollte einen kompatiblen Datentyp bereitstellen.
- **Wiederverwendbarkeit:** Der Baustein ist als Composite definiert und verwendet intern den standardisierten Vergleichsbaustein **F_NE**. Eine Modifikation der Vergleichslogik ist durch Austausch des internen Bausteins möglich.
- **Copyright:** Der Baustein unterliegt der Eclipse Public License 2.0.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Er verhält sich wie eine funktionale Einheit:

- **Warten:** Der Baustein wartet auf ein Ereignis an **REQ** oder **IN2.E1**.
- **Vergleichen:** Sobald ein Ereignis eintrifft, wird der Vergleich ausgeführt.
- **Ausgeben:** Das Ergebnis wird über **OUT** ausgegeben und das Ereignis **OUT.E1** ausgelöst.

Danach kehrt der Baustein in den Wartezustand zurück.

## Anwendungsszenarien

- **Ungleichheitsprüfung in Steuerungslogiken:** Überwachung, ob ein Prozesswert von einem Sollwert abweicht.
- **Signalvergleich in Kommunikationsschnittstellen:** Vergleich zweier von unterschiedlichen Quellen stammender Messwerte.
- **Freigabebedingungen:** Auslösen einer Aktion, wenn zwei Eingangssignale nicht identisch sind (z. B. in Sicherheitsanwendungen).
- **Adaptergekoppelte Systeme:** Integration in modulare Automatisierungsprojekte, die auf Adaptern zur Signalweiterleitung setzen.

## Vergleich mit ähnlichen Bausteinen

| Baustein           | Funktion                       | Unterschied zu UDINT_AUDI_NE                                    |
|--------------------|--------------------------------|-----------------------------------------------------------------|
| `F_EQ`             | Gleichheitsvergleich           | Prüft auf Gleichheit, nicht auf Ungleichheit                    |
| `F_LT`, `F_GT`     | Kleiner-/Größer-Vergleich      | Führen Ordnungsvergleiche durch, keine Ungleichheitsprüfung     |
| `UDINT_AUDI_EQ`    | Gleichheit mit Adaptern        | Gleiche Adapterschnittstelle, aber Vergleich auf Gleichheit      |

Der **UDINT_AUDI_NE** ist speziell für den Ungleichheitsvergleich mit Adapter-Schnittstellen ausgelegt und ergänzt die Familie der adapterbasierten Vergleichsbausteine.

## Fazit

**UDINT_AUDI_NE** ist ein flexibler und wiederverwendbarer Funktionsbaustein für den Ungleichheitsvergleich. Durch die Verwendung von Adaptern für den zweiten Eingang und den Ausgang lässt er sich einfach in komplexe Automatisierungsnetzwerke integrieren. Die Unterstützung beliebiger elementarer Datentypen und die ereignisgesteuerte Ausführung machen ihn zu einem vielseitigen Werkzeug für unterschiedlichste Anwendungen. Seine Composite-Struktur erlaubt zudem eine einfache Anpassung der Vergleichslogik bei Bedarf.