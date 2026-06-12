# AQ_D_FF_TMIN


![AQ_D_FF_TMIN](./AQ_D_FF_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AQ_D_FF_TMIN** realisiert ein datenverriegelndes D-Flipflop mit einer minimalen Zwischenzeit (Minimum inter‑disposal Time) zwischen zwei aufeinanderfolgenden Ausgangsereignissen (EO). Er dient als Erweiterung eines einfachen D-Flipflops um eine zeitliche Entprellung oder Mindestabstandssteuerung und wird über Adapter mit dem Signalgeber und dem Signalempfänger verbunden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Mit Variable | Kommentar |
|----------|-----|-------------|-----------|
| INIT | EInit | Tmin | Initialisierungsanfrage, setzt die minimale Zwischenzeit. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INITO | EInit | Initialisierungsbestätigung. |

### **Daten-Eingänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| Tmin | TIME | Minimale Wartezeit zwischen zwei Ausgangsereignissen (EO). |

### **Daten-Ausgänge**

Keine eigenen Datenausgänge, das latched Signal wird über den Adapter `Q` ausgegeben.

### **Adapter**

| Typ | Bezeichnung | Richtung | Kommentar |
|-----|-------------|----------|-----------|
| `adapter::types::unidirectional::AQ` | I | Socket (Eingang) | Wert zum latchen, enthält je ein Daten‑ (D1) und Ereignissignal (E1). |
| `adapter::types::unidirectional::AQ` | Q | Plug (Ausgang) | Gelatchter Wert, enthält je ein Daten- (D1) und Ereignissignal (E1). |

## Funktionsweise

Der Baustein kapselt einen internen FB vom Typ `iec61499::events::E_D_FF_ANY_TMIN`. Dieser arbeitet wie ein flankengesteuertes D‑Flipflop, bei dem das Ereignis `I.E1` als Takt und `I.D1` als Dateneingang dient. Das Ausgangsereignis `EO` wird nur dann am Adapter `Q.E1` ausgegeben, wenn seit dem letzten ausgegebenen Ereignis mindestens die in `Tmin` festgelegte Zeit vergangen ist. Der Datenwert am Ausgang `Q.D1` entspricht dem zum Zeitpunkt der steigenden Flanke an `I.E1` anliegenden Wert `I.D1`.

Die Initialisierung (`INIT`) übergibt den Parameter `Tmin` an den internen FB, sodass die zeitliche Bedingung festgelegt wird.

## Technische Besonderheiten

- **Minimale Zwischenzeit (Tmin):** Verhindert zu schnelle aufeinanderfolgende Ausgangsereignisse, z. B. zum Entprellen oder zur Begrenzung der Aktualisierungsrate.
- **Adapterbasierte Kommunikation:** Der FB verwendet unidirektionale Adapter (`AQ`), die sowohl Daten als auch Ereignisse bündeln und eine lose Kopplung zwischen Signalquelle und -senke ermöglichen.
- **IEC 61499-konform:** Entspricht dem Standard 61499‑1 Annex A und nutzt die Ereignis-/Datenflüsse der Norm.

## Zustandsübersicht

Der FB besitzt keinen expliziten öffentlichen Zustandsautomaten. Sein Verhalten wird durch den internen FB `E_D_FF_ANY_TMIN` bestimmt, der als Zustand den letzten gelatchten Wert und eine Wartezeitlogik aufweist. Vereinfacht dargestellt:

| Zustand | Bedeutung |
|---------|-----------|
| Initialisiert | Nach INIT bereit, Tmin ist gesetzt |
| Bereit | Wartet auf Takt (I.E1) |
| Gelatcht | Datenwert wurde übernommen, Ausgangsereignis wird nach Ablauf von Tmin ausgegeben |
| Wartend | Tmin läuft – Ausgangsereignis wird blockiert |

Eine detaillierte Zustandsdarstellung ist im Quellcode des internen FBs ersichtlich.

## Anwendungsszenarien

- **Signalglättung/Entprellung:** Vermeiden von Mehrfachauslösungen bei mechanischen Tastern oder schnellen Signalwechseln.
- **Datenratenbegrenzung:** Begrenzen der Ausgabehäufigkeit von Messwerten in Überwachungssystemen.
- **Synchronisation asynchroner Signale:** Weiterleitung eines Datenwerts mit definiertem zeitlichem Mindestabstand.
- **Steuerung langsamer Aktoren:** Sicherstellen, dass Aktoren nicht schneller angesteuert werden als ihre mechanische Reaktionszeit zulässt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Besonderheit |
|----------|--------------|
| `AQ_D_FF` / `E_D_FF` | Einfaches D‑Flipflop ohne zeitliche Einschränkung des Ausgangs. |
| `AQ_D_FF_TMIN` (dieser FB) | Erweitert um minimale Zwischenzeit Tmin zwischen Ausgangsereignissen. |
| `AQ_D_FF_TMAX` (hypothetisch) | Begrenzung der maximalen Zeit zwischen zwei Ausgangsereignissen. |

Gegenüber einem Standard-D‑Flipflop bietet `AQ_D_FF_TMIN` zusätzlichen Schutz vor zu rascher Folge von Ausgangsereignissen, was in der Praxis häufig erforderlich ist.

## Fazit

Der Funktionsblock `AQ_D_FF_TMIN` kombiniert die Funktion eines D‑Flipflops mit einer einstellbaren minimalen Verzögerung am Ausgang. Durch die Adapter‑Schnittstellen und die IEC‑61499‑Konformität lässt er sich einfach in industrielle Steuerungsanwendungen integrieren, bei denen sowohl Datenübernahme als auch zeitliche Entkopplung der Ereignisse erforderlich sind. Er bietet eine robuste Lösung für Signalverarbeitung und Aktorsteuerung mit definierten zeitlichen Randbedingungen.