# AD_D_FF_TMIN


![AD_D_FF_TMIN](./AD_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AD_D_FF_TMIN** realisiert ein datenrückhaltendes Flip-Flop (D‑Latch) auf Basis von Adaptern mit unidirektionaler Schnittstelle. Er zeichnet sich durch eine konfigurierbare Mindestverweilzeit (*Minimum inter-disposal Time*) zwischen zwei aufeinanderfolgenden Ereignissen aus und eignet sich damit für zeitkritische Signalverarbeitungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INIT | EInit | Initialisierungsanforderung (Übergabe der Mindestzeit) |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INITO | EInit | Initialisierungsbestätigung |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| Tmin | TIME | Minimale Zeit zwischen zwei aufeinanderfolgenden Ereignissen am Socket *I* |

### **Daten-Ausgänge**

Keine direkten Datenausgänge vorhanden; die Ausgabe erfolgt ausschließlich über den Adapter *Q*.

### **Adapter**

| Typ | Richtung | Name | Kommentar |
|-----|----------|------|-----------|
| adapter::types::unidirectional::AD | **Plug** (Ausgang) | Q | Liefert den gelatchten Wert |
| adapter::types::unidirectional::AD | **Socket** (Eingang) | I | Empfängt den zu latchnden Wert sowie das Taktereignis |

## Funktionsweise

Der Baustein kapselt eine interne Instanz des Funktionsblocks `iec61499::events::E_D_FF_ANY_TMIN`. Der Socket *I* liefert sowohl das Taktereignis (über den Adapter‑Ereignisausgang `E1`) als auch den Datenwert (über den Adapter‑Datenausgang `D1`). Das interne Flip‑Flop übernimmt bei jedem Takt den aktuellen Wert von `I.D1` an seinen Ausgang `Q`. Dieses Signal wird über den Plug *Q* (Ereignis `E1` und Daten `D1`) nach außen gegeben.

Die Mindestverweilzeit `Tmin` wird dem internen Baustein bei der Initialisierung übergeben und begrenzt die Frequenz der Taktereignisse: Ereignisse, die vor Ablauf von `Tmin` seit dem letzten Takt eintreffen, werden unterdrückt.

## Technische Besonderheiten

- **Adapter‑basierte Ein‑/Ausgabe**: Der Baustein verwendet unidirektionale Adapter (Typ `adapter::types::unidirectional::AD`), die Ereignis und Daten in einer strukturierten Schnittstelle zusammenfassen.
- **Ereignis‑gesteuerte Mindestzeit**: Die parametrierbare Zeit `Tmin` verhindert eine zu schnelle Taktfolge und schützt nachgeschaltete Logik vor Überlastung.
- **Wiederverwendung**: Die innere Logik ist als eigener FB (`E_D_FF_ANY_TMIN`) realisiert, was eine modulare Wartung und Tests erleichtert.

## Zustandsübersicht

Der Baustein selbst besitzt keinen expliziten Zustandsautomaten (keine ECC‑Definition). Sein Verhalten wird vollständig durch den eingebetteten FB `E_D_FF_ANY_TMIN` bestimmt. Dieser arbeitet als **D‑Flip‑Flop mit Zeitfilter**:

- **Ruhezustand**: Warten auf das nächste Taktereignis.
- **Taktverarbeitung**: Prüfen, ob seit dem letzten Takt die Zeitspanne `Tmin` vergangen ist. Falls ja → Datenübernahme und Erzeugung eines Ausgangsereignisses. Falls nein → Ereignis ignorieren.
- **Initialisierungszustand**: Nur durch `INIT` wird `Tmin` gesetzt und der interne Timer zurückgesetzt.

## Anwendungsszenarien

- **Datenerfassung mit Mindestabstand**:
  Sensordaten sollen nur dann übernommen werden, wenn ein bestimmter zeitlicher Abstand zum vorherigen Wert eingehalten wird (z. B. Entprellung oder Abtastratenbegrenzung).
- **Pulsformung / Triggermanagement**:
  Der Baustein kann als „entprellter“ Flip‑Flop in Steuerungen eingesetzt werden, um Signalflanken zu glätten und Störimpulse auszufiltern.
- **Adapter‑orientierte Busarchitekturen**:
  Dank der Adapter‑Schnittstelle lässt sich der FB nahtlos in bestehende unidirektionale Datenflüsse einbinden, z. B. in Sensor‑Aktor‑Netzwerken.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft | Unterschied |
|----------|-------------|-------------|
| **E_D_FF** | Standard‑D‑Flip‑Flop | Keine zeitliche Einschränkung; jedes Taktereignis wird verarbeitet. |
| **E_CTD** / **E_CTU** | Zähler | Andere Grundfunktion; zählt Ereignisse. |
| **AD_D_FF_TMIN** | D‑Flip‑Flop mit *Minimum inter‑disposal Time* | Verhindert zu schnelle Taktfolgen durch parametrierbare Sperrzeit. |

## Fazit

Der **AD_D_FF_TMIN** erweitert das klassische D‑Flip‑Flop um eine zeitliche Filterfunktion, die über den Parameter `Tmin` konfiguriert wird. Seine Adapter‑Schnittstelle erlaubt eine saubere Kapselung von Ereignis und Daten in einem Stecker, was die Integration in komplexe Automatisierungssysteme vereinfacht. Der Baustein ist ideal für Anwendungen, bei denen eine minimale Ereignisdistanz sichergestellt werden muss.