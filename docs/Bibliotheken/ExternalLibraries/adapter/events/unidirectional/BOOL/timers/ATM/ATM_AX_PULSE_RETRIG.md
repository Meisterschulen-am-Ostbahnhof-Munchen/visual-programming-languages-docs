# ATM_AX_PULSE_RETRIG


![ATM_AX_PULSE_RETRIG](./ATM_AX_PULSE_RETRIG.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **ATM_AX_PULSE_RETRIG** erzeugt einen Impuls (Puls) definierter Dauer an seinem Ausgang. Er ist als retriggerbare Version ausgelegt, d.h. ein erneuter Startbefehl während eines laufenden Impulses setzt die Impulsdauer zurück. Die Steuerung und Parameterübergabe erfolgt ausschließlich über zwei standardisierte Adapter-Schnittstellen (ATM / AX), sodass der Baustein ohne direkte Daten-Ein-/Ausgänge auskommt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar                                  |
|------|-------|--------------------------------------------|
| REQ  | Event | Startbefehl – löst einen neuen Impuls aus und startet die Timer-Zeit neu |
| R    | Event | Reset – beendet einen laufenden Impuls sofort |

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine. Die Impulsdauer wird über den Adapter **PT** (Socket) bereitgestellt.

### **Daten-Ausgänge**
Keine. Der Impulsstatus (aktiv/inaktiv) wird über den Adapter **Q** (Plug) ausgegeben.

### **Adapter**
| Rolle | Name | Typ   | Richtung | Beschreibung                                          |
|-------|------|-------|----------|-------------------------------------------------------|
| Input | PT   | ATM   | Socket   | Liefert die gewünschte Impulsdauer <small>(D1 → PT)</small> |
| Output| Q    | AX    | Plug     | Zeigt den Impulszustand an <small>(D1 = HIGH während des Impulses)</small> |

## Funktionsweise
Wird der Baustein mit einem **REQ**-Ereignis angestoßen, startet er einen Timer mit der Dauer, die über den Adapter **PT** (Datenwert D1) vorgegeben ist. Der Ausgang **Q** (D1) wird sofort auf **HIGH** gesetzt und bleibt für genau diese Zeit aktiv. Trifft während eines laufenden Impulses erneut ein **REQ** ein, wird der Timer zurückgesetzt und die Impulsdauer beginnt von vorn (retriggerbar). Ein **Reset**-Ereignis (**R**) beendet den Impuls vorzeitig und setzt **Q** auf **LOW**.

Der Baustein implementiert die interne Logik mittels des standardisierten IEC‑61499-Funktionsbausteins **E_PULSE_RETRIG**, der alle Zeitsteuerungen übernimmt. Die Kopplung der Adapter (PT → D1 an internen Timer, interner Ausgang Q → Q.D1) erfolgt im verborgenen Netzwerk.

## Technische Besonderheiten
- **Retriggerbares Verhalten**: Jeder neue **REQ** während eines aktiven Impulses verlängert die Impulsdauer auf den vollen Wert von PT.
- **Adapter-basierte Schnittstelle**: Der Baustein besitzt keine direkten Ereignis-Ausgänge oder Daten-Ports; die gesamte Kommunikation erfolgt über die standardisierten **ATM** (Parameter) und **AX** (Ausgang) Adapter.
- **Wiederverwendbarkeit**: Durch die strikte Trennung von Steuerung und Parametrierung eignet sich der Baustein besonders für modulare und wiederverwendbare Anwendungen.

## Zustandsübersicht
Der Baustein kennt zwei Zustände:
- **Inaktiv** (Q.D1 = FALSE): Kein Impuls aktiv, Timer läuft nicht.
- **Aktiv** (Q.D1 = TRUE): Impuls läuft; bei Eintritt durch REQ wird der Timer mit PT gestartet. Jeder weitere REQ setzt den Timer zurück. Ein R-Ereignis führt sofort zurück in den inaktiven Zustand.

## Anwendungsszenarien
- **Taktgeber für Signalleuchten**: Ein kontinuierliches Startsignal (z. B. Taster oder Sensor) erzeugt einen definierten Lichtimpuls. Durch die Retrigger-Funktion bleibt die Leuchte bei Dauersignal dauerhaft an.
- **Impulsverlängerung in Steuerungen**: Kurze Eingangsimpulse werden auf eine minimale bzw. definierte Dauer aufgeweitet.
- **Ansteuerung von Aktoren mit Mindesteinschaltzeit**: Ventile, Motoren oder Relais, die eine bestimmte Einschaltdauer benötigen, können zuverlässig angesteuert werden.

## Vergleich mit ähnlichen Bausteinen
| Baustein                | Retriggerbar | Schnittstelle        | Einsatzgebiet                     |
|-------------------------|--------------|----------------------|-----------------------------------|
| **ATM_AX_PULSE_RETRIG** | Ja           | Adapter (ATM/AX)     | Modulare Steuerungen mit Adapter-Konzept |
| ATM_AX_PULSE           | Nein         | Adapter (ATM/AX)     | Einmalige Impulse, keine Neuauslösung |
| Standard E_PULSE_RETRIG| Ja           | Direkte Ein-/Ausgänge | Flexibler, aber ohne Adapter-Kapselung |

Der vorliegende Baustein hebt sich durch die ausschließliche Verwendung von Adapter-Schnittstellen ab, was die Einbindung in bestehende Adapter-basierte Bibliotheken erleichtert.

## Fazit
**ATM_AX_PULSE_RETRIG** ist ein kompakter, retriggerbarer Impulsbaustein, der sich durch seine saubere Kapselung mittels ATM/AX-Adapter auszeichnet. Er eignet sich hervorragend für den Einsatz in verteilten Steuerungssystemen, die auf das IEC‑61499‑Adapterkonzept bauen. Durch die einfache Handhabung (zwei Ereignisse, zwei Adapter) und das bewährte Timer-Verhalten ist er eine verlässliche Komponente für zeitgesteuerte Ausgaben.