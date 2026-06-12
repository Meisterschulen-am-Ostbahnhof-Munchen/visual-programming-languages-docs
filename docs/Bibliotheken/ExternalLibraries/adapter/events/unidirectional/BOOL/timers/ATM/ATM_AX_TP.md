# ATM_AX_TP


![ATM_AX_TP](./ATM_AX_TP.svg)

* * * * * * * * * *
## Einleitung

Der **ATM_AX_TP** ist ein spezieller Timer-Funktionsblock, der aus einem Eingangssignal einen zeitlich begrenzten Impuls erzeugt. Er implementiert die Funktionalität eines **nicht-nachtriggerbaren Impulsformers** (non‑retriggerable pulse). Der Baustein wird über einen AX‑Adapter angesteuert und gibt das Ergebnis ebenfalls über einen AX‑Adapter aus; die Impulsdauer wird über einen separaten ATM‑Adapter vorgegeben. Durch die Adapter‑Schnittstellen lässt er sich besonders einfach in modular aufgebaute Automatisierungssysteme integrieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                    |
|------|-------|------------------------------|
| R    | Event | Setzt den Timer zurück       |

### **Ereignis-Ausgänge**

Keine eigenen Ereignisausgänge – die Ausgabe des Impulses erfolgt über den Adapter **Q** (siehe Adapter-Sektion).

### **Daten-Eingänge**

Keine direkten Dateneingänge. Die Eingangswerte (IN und PT) werden über die entsprechenden Adapter-Sockets bereitgestellt.

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Der Ausgangswert (Q) wird über den Adapter **Q** ausgegeben.

### **Adapter**

| Bezeichnung | Typ    | Richtung | Beschreibung                                     |
|-------------|--------|----------|--------------------------------------------------|
| **Q**       | AX     | Plug     | Ausgang: liefert das Impulssignal                |
| **IN**      | AX     | Socket   | Eingang: Empfängt das auslösende Signal          |
| **PT**      | ATM    | Socket   | Eingang: Stellt die Impulsdauer (Pulszeit) bereit |

**Hinweis:** Die Adapter sind vom Typ *adapter::types::unidirectional::AX* (bzw. *ATM*) und übertragen ein Ereignis zusammen mit einem Datenwert.

## Funktionsweise

Der **ATM_AX_TP** arbeitet auf Basis des standardisierten IEC 61499‑Funktionsbausteins **E_TP**, der im Inneren des Netzwerks instanziiert ist.

- **Auslösung:** Eine steigende Flanke am Eingang **IN** (Ereignis IN.E1 und Datenwert IN.D1 = TRUE) startet die Zeitmessung.
- **Impulserzeugung:** Der Ausgang **Q** wird unverzüglich auf TRUE gesetzt und bleibt für die Dauer **PT** aktiv. Nach Ablauf der Zeit kehrt Q auf FALSE zurück.
- **Nicht-nachtriggerbar:** Während eines laufenden Impulses wird eine erneute steigende Flanke von IN ignoriert – der Impuls läuft in der ursprünglichen Länge weiter.
- **Reset:** Ein Ereignis am Eingang **R** beendet den aktuellen Impuls sofort (Q = FALSE) und setzt den Timer zurück. Danach kann ein neuer Impuls gestartet werden.

Die Verdrahtung intern:  
`IN.E1 → E_TP.REQ`  
`IN.D1 → E_TP.IN`  
`PT.D1 → E_TP.PT`  
`E_TP.CNF → Q.E1` (Ereignisausgabe bei Impulsende)  
`E_TP.Q   → Q.D1` (Ausgangsdatenwert)  
`R       → E_TP.R`

## Technische Besonderheiten

- **Adapter‑basierte Anbindung:** Anders als ein direkter E_TP arbeitet ATM_AX_TP ausschließlich über Adapter (AX und ATM). Dies erlaubt eine lose Kopplung in verteilten Systemen und vereinfacht den Austausch von Signaltypen.
- **Kompatibilität:** Der Baustein ist für die Verwendung mit dem Eclipse 4diac‑Framework optimiert (erkennbar am Package‑Attribut `adapter::events::unidirectional::timers`).
- **Versionierung:** Mehrere Versionen dokumentieren die Evolution (Rücksetzfunktion, Paketänderung).
- **Lizenz:** Eclipse Public License 2.0 – der Quellcode darf verwendet, geändert und weitergegeben werden.

## Zustandsübersicht

Der FB besitzt keine expliziten Zustandsautomaten auf der oberen Ebene – die Zustandslogik wird vollständig durch den internen **E_TP** realisiert. Dieser durchläuft folgende Zustände:

- **IDLE** – warten auf steigende Flanke von IN
- **ACTIVE** – Impuls läuft (Q = TRUE, Timer läuft)
- **RESET** – durch Ereignis R in IDLE zurück (Impuls vorzeitig beendet)

Nach Ablauf der Timer‑Zeit wechselt E_TP selbstständig von ACTIVE nach IDLE.

## Anwendungsszenarien

- **Steuerung kurzzeitiger Aktoren:** Ventile, Leuchten, Signalgeber, die nur für eine bestimmte Dauer eingeschaltet werden sollen.
- **Entprellung / Impulsformung:** Ein eingehendes Signal (z. B. Taster) wird in einen exakt definierten Impuls gewandelt.
- **Modulare Automatisierung:** Durch die Adapter‑Schnittstellen eignet sich der Baustein für den Einsatz in verteilten Systemen, bei denen Signale über verschiedene Komponenten ausgetauscht werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein        | Eigenschaften                                                                 | Unterschied zum ATM_AX_TP                            |
|-----------------|-------------------------------------------------------------------------------|------------------------------------------------------|
| **E_TP** (Standard) | Direkte Ereignis‑/Datenanschlüsse, kein Adapter.                           | ATM_AX_TP kapselt E_TP und stellt Adapter bereit.   |
| **E_R_TRIG**    | Flankenerkennung ohne Impulsverlängerung.                                     | Erzeugt nur einen sehr kurzen Impuls, keine Zeitsteuerung. |
| **E_CYCLE**     | Zyklischer Timer, wiederholt Impulse.                                        | Einmaliger Impuls (pulse).                           |

## Fazit

Der **ATM_AX_TP** ist ein nützlicher Funktionsbaustein zur Erzeugung eines nicht‑nachtriggerbaren Impulses mit einstellbarer Dauer. Seine Besonderheit liegt in der Adapter‑basierten Schnittstelle, die eine flexible und lose Kopplung in IEC 61499‑Systemen ermöglicht. Durch den eingebetteten Standard‑Timer E_TP bleibt die Funktionsweise robust und bewährt. Ein praktischer Baustein für alle Anwendungen, bei denen ein definiertes Zeitfenster auf ein externes Signal hin geschaltet werden muss.