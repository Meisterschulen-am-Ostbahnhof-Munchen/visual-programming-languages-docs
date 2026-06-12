# AI_D_FF_TMIN


![AI_D_FF_TMIN](./AI_D_FF_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Baustein **AI_D_FF_TMIN** realisiert ein D‑Flip‑Flop (Data Latch) mit einer minimalen zeitlichen Sperre zwischen aufeinanderfolgenden Ausgabeereignissen (inter‑disposal time). Er dient als Adapter‑gekapselte Komponente, die einen asynchron eingehenden Datenwert über einen Socket entgegennimmt, bei einem aktiven Ereignis zwischenspeichert und über einen Plug weitergibt. Die Ausgabe wird dabei erst dann wieder freigegeben, wenn die konfigurierte Mindestzeit \( T_{\text{min}} \) seit der letzten Ausgabe verstrichen ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Typ   | Mit Variable | Kommentar                          |
|-------------|-------|--------------|------------------------------------|
| `INIT`      | EInit | `Tmin`       | Initialisierungsanforderung        |

### **Ereignis-Ausgänge**

| Bezeichnung | Typ   | Mit Variable | Kommentar                             |
|-------------|-------|--------------|---------------------------------------|
| `INITO`     | EInit | –            | Bestätigung der Initialisierung       |

### **Daten-Eingänge**

| Bezeichnung | Typ  | Kommentar                                    |
|-------------|------|----------------------------------------------|
| `Tmin`      | TIME | Minimale Zeitspanne zwischen zwei EO‑Ereignissen |

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenständigen Daten-Ausgänge; die Ausgabe erfolgt ausschließlich über den Adapter `Q`.

### **Adapter**

| Bezeichnung | Typ (Adapter)                      | Richtung | Kommentar                    |
|-------------|------------------------------------|----------|------------------------------|
| `I`         | `adapter::types::unidirectional::AI` | Socket   | Eingangsdaten zum Latchen         |
| `Q`         | `adapter::types::unidirectional::AI` | Plug     | Gelatchter Ausgabewert           |

## Funktionsweise

Der Baustein kapselt den internen Funktionsblock `E_D_FF_ANY_TMIN`, der das eigentliche D‑Flip‑Flop mit Zeitsteuerung implementiert. Die Verschaltung erfolgt wie folgt:

- Das Initialisierungsereignis `INIT` wird zusammen mit dem Parameter `Tmin` an den internen FB übergeben.
- Ein Daten‑Latch wird durch ein Ereignis auf dem Socket `I` ausgelöst (Adapterereignis `I.E1`). Dieses Ereignis dient als Takt (`CLK`) für das Flip‑Flop.
- Der aktuelle Datenwert von `I.D1` wird bei jedem Takt übernommen und am Ausgang des internen FBs bereitgestellt.
- Der interne FB erzeugt am Ausgang `EO` ein Ereignis, das über den Adapter `Q` als `Q.E1` weitergegeben wird.
- Zwischen zwei aufeinanderfolgenden `EO`‑Ereignissen muss mindestens die Zeit `Tmin` liegen. Geht während dieser Sperrzeit ein weiterer Takt ein, wird der Datenwert zwar gelatcht, die Ausgabe jedoch erst nach Ablauf der Sperrzeit freigegeben.
- Das Ereignis `INITO` bestätigt den abgeschlossenen Initialisierungsvorgang.

## Technische Besonderheiten

- **Adapter‑Schnittstelle:** Die Ein‑ und Ausgabe erfolgen über unidirektionale Adapter vom Typ `AI`. Diese ermöglichen eine lose Kopplung und einfache Wiederverwendung des Bausteins in unterschiedlichen Umgebungen.
- **Minimale Ausgabezeit:** Der Parameter `Tmin` ermöglicht eine gezielte Begrenzung der Ereignisrate am Ausgang. Damit wird vermieden, dass nachgeschaltete Komponenten durch zu schnelle Ereignisfolgen überlastet werden.
- **Initialisierungspflicht:** Vor der ersten Nutzung muss der Baustein über `INIT` initialisiert werden, da während dieser Phase der interne Zustand gesetzt und `Tmin` übernommen wird.

## Zustandsübersicht

Der Baustein besitzt keinen explizit sichtbaren Zustandsautomaten; das Zeitverhalten wird vollständig durch den internen FB `E_D_FF_ANY_TMIN` gesteuert. Im Wesentlichen durchläuft der Baustein folgende Phasen:

1. **Initialisierung** – Nach Erhalt von `INIT` wird der interne FB konfiguriert.
2. **Warten auf Takt** – Der Baustein wartet auf ein Ereignis am Socket `I`.
3. **Latchen** – Bei Takt wird der Datenwert übernommen und ein Ausgabeereignis erzeugt.
4. **Sperrphase** – Nach der Ausgabe wird für die Dauer von `Tmin` jedes weitere Ausgabeereignis verzögert.
5. **Bereit** – Nach Ablauf der Sperrzeit kann erneut ein Takt verarbeitet werden.

## Anwendungsszenarien

- **Sensor‑Datenübernahme:** Ein asynchron arbeitender Sensor liefert Messwerte, die nur in einem definierten Mindestabstand an ein Steuerungssystem weitergegeben werden sollen (z. B. Temperaturerfassung mit Entprellung).
- **Pufferung zeitkritischer Signale:** In Automatisierungsanwendungen, bei denen nachgeschaltete Verarbeitungsbausteine eine begrenzte Ereignisrate tolerieren, wird der Baustein als „Rate Limiter“ eingesetzt.
- **Synchronisation:** Der FB kann verwendet werden, um zyklische Abläufe zu synchronisieren, indem er die maximale Aktualisierungsrate eines Ausgangssignals begrenzt.

## Vergleich mit ähnlichen Bausteinen

| Baustein        | Beschreibung                                    | Unterschied zu AI_D_FF_TMIN                     |
|-----------------|------------------------------------------------|-------------------------------------------------|
| `E_D_FF`        | Einfaches D‑Flip‑Flop ohne Zeitbegrenzung      | Keine Mindestzeit zwischen Ausgabeereignissen   |
| `E_D_FF_ANY`    | D‑Flip‑Flop für beliebige Datentypen           | Ebenfalls ohne zeitliche Steuerung              |
| `AI_D_FF`       | D‑Flip‑Flop mit Adapter‑Schnittstelle          | Fehlende `Tmin`‑Option                          |
| `E_CYCLE`       | Takterzeuger mit einstellbarer Periode          | Erzeugt periodische Ereignisse, kein Latch      |

Der `AI_D_FF_TMIN` vereint die Funktionalität eines Adapter‑gekapselten Flip‑Flops mit einer frei konfigurierbaren Ausgabesperre – eine Kombination, die in Standard‑Flip‑Flops nicht enthalten ist.

## Fazit

`AI_D_FF_TMIN` bietet eine kompakte Lösung für das Zwischenspeichern und zeitlich kontrollierte Weitergeben von Daten über Adapterschnittstellen. Die integrierte Mindest‑Ausgabezeit schützt nachgelagerte Bausteine vor Überlastung und erlaubt eine robuste Signalverarbeitung in industriellen Steuerungssystemen. Durch die modulare Adapter‑Schnittstelle ist der Baustein flexibel in verschiedenste 4diac‑Netzwerke integrierbar.