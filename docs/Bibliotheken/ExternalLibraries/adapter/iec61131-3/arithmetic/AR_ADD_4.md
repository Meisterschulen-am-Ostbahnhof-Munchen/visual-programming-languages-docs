# AR_ADD_4


![AR_ADD_4](./AR_ADD_4.svg)

*Hinweis: Ein grafisches Symbol des Funktionsblocks liegt nicht vor.*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AR_ADD_4** ist ein generischer Baustein zur arithmetischen Addition mehrerer Werte. Er ist nach dem Standard IEC 61499-2 ausgelegt und erlaubt die flexible Verarbeitung von bis zu vier additiven Operanden über Adapter-Schnittstellen. Der Baustein wird typischerweise in Automatisierungssystemen eingesetzt, in denen eine numerische Summenbildung mehrerer Signale erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine (Der Baustein arbeitet ohne explizite Ereignissteuerung.)

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine (Alle Eingabeoperanden werden über Adapter bereitgestellt.)

### **Daten-Ausgänge**
- Keine (Das Ergebnis wird über einen Adapter ausgegeben.)

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **IN1** | `adapter::types::unidirectional::AR` | Socket (Eingang) | Erster Summand der Addition |
| **IN2** | `adapter::types::unidirectional::AR` | Socket (Eingang) | Zweiter Summand |
| **IN3** | `adapter::types::unidirectional::AR` | Socket (Eingang) | Dritter Summand |
| **IN4** | `adapter::types::unidirectional::AR` | Socket (Eingang) | Vierter Summand |
| **OUT** | `adapter::types::unidirectional::AR` | Plug (Ausgang) | Ergebnis der Addition (Summe der Eingänge) |

Die Adapter sind vom Typ `unidirectional::AR`, was darauf hindeutet, dass sie einen arithmetischen Wert (z. B. einen Zahlenwert) als gerichtete Verbindung bereitstellen oder verarbeiten.

## Funktionsweise

Der Baustein **AR_ADD_4** führt die Summenbildung der vier an den Eingangsadaptern anliegenden Werte durch und gibt das Ergebnis am Ausgangsadapter **OUT** aus. Die Berechnung erfolgt nach der allgemeinen Formel:

\[
\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}
\]

Da der Baustein als generischer Typ deklariert ist (`eclipse4diac::core::GenericClassName = 'GEN_AR_ADD'`), wird der zugrunde liegende Datentyp (z. B. Integer, Real oder benutzerdefinierte arithmetische Typen) erst zur Laufzeit durch die konkrete Konfiguration festgelegt. Die Verarbeitung erfolgt datengesteuert – sobald an allen vier Eingängen valide Werte anliegen, wird die Summe berechnet und am Ausgang aktualisiert.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generisch markiert (`eclipse4diac::core::GenericClassName`). Dadurch kann der konkrete arithmetische Datentyp erst beim Einsatz im Projekt festgelegt werden, was eine hohe Wiederverwendbarkeit ermöglicht.
- **Adapterbasierte Kommunikation**: Statt klassischer Daten-Ein-/Ausgänge werden alle Werte über Adapter ausgetauscht. Dies erlaubt eine lose Kopplung mit anderen Bausteinen und fördert modulare Strukturen.
- **Keine Ereignissteuerung**: Der Baustein besitzt keine Ereigniseingänge oder -ausgänge. Die Berechnung und Datenweitergabe erfolgt automatisch, sobald alle Eingangswerte vorliegen (ähnlich einer kontinuierlichen Funktion).
- **Typische Paketstruktur**: Der Baustein ist im Paket `adapter::iec61131::arithmetic` organisiert, was auf eine IEC 61131-nahe Adapterimplementierung hinweist.

## Zustandsübersicht

Aufgrund der rein datengetriebenen und ereignislosen Arbeitsweise besitzt der Baustein **keine internen Zustände**. Es gibt keine sequenziellen Abläufe oder Zustandsmaschinen. Die Ausgabe ist immer der aktuelle Summenwert der vier Eingänge.

## Anwendungsszenarien

1. **Bildung einer Summe mehrerer Prozesswerte** (z. B. Addition von Durchflusssignalen mehrerer Sensoren).
2. **Skalierung und Summation** – in Kombination mit skalierenden Adaptern kann der Baustein zur gewichteten Summenbildung eingesetzt werden.
3. **Berechnung von Gesamtverbrauch oder Gesamtenergie** aus mehreren Teilmessungen.
4. **Generische Summenbildung in modularen Automatisierungslösungen**, bei denen die Anzahl der Summanden fest, aber der Datentyp variabel ist.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Eingänge | Besonderheit |
|----------|----------------|--------------|
| **AR_ADD_4** | 4 | Adapterbasiert, generisch, keine Ereignisse |
| **AR_ADD_2** (hypothetisch) | 2 | Reduzierte Eingänge, gleiche Konzeption |
| **F_ADD** (aus IEC 61131) | 2 | Standard-Datentypen, ereignisgesteuert (via ENABLE/ENO) |
| **AR_SUM** (hypothetisch) | variabel | Flexiblere Anzahl, aber aufwändiger |

Der Baustein **AR_ADD_4** hebt sich durch die reine Adapter-Kommunikation und die generische Auslegung von klassischen IEC 61499-Arithmetikbausteinen ab. Er eignet sich besonders für Systeme, die bereits auf Adapter-Technologie setzen und keine explizite Ereignissteuerung benötigen.

## Fazit

Der **AR_ADD_4** ist ein kompakter, generischer Funktionsblock zur Addition von vier Werten über Adapter-Schnittstellen. Seine einfache und robuste datengetriebene Funktionsweise macht ihn zu einem nützlichen Grundbaustein für modulare Automatisierungsanwendungen. Die Abwesenheit von Ereignissen und die generische Typisierung ermöglichen eine flexible Integration in heterogene Systeme. Für Anwendungen mit mehr oder weniger als vier Summanden muss auf angepasste Varianten oder erweiterte Bausteine zurückgegriffen werden.