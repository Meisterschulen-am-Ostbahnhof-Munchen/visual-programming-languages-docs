# AS_D_FF_TMIN


![AS_D_FF_TMIN](./AS_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AS_D_FF_TMIN** realisiert ein datenverriegelndes D‑Flipflop, das einen über einen Adapter zugeführten Datenwert bei Eintreffen eines Ereignisses übernimmt und über einen weiteren Adapter ausgibt. Die Besonderheit liegt in einer konfigurierbaren Mindestzeit (`Tmin`) zwischen zwei aufeinanderfolgenden Übernahmeereignissen. Dadurch werden zu schnelle Ereignisfolgen unterdrückt, was z. B. zur Entprellung oder zur Einhaltung von Prozessbeschränkungen genutzt werden kann.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
| Ereignis | Typ   | Kommentar                                 |
|----------|-------|-------------------------------------------|
| INIT     | EInit | Initialisierungsanforderung (liest `Tmin`) |

### **Ereignis‑Ausgänge**
| Ereignis | Typ   | Kommentar                           |
|----------|-------|-------------------------------------|
| INITO    | EInit | Bestätigung der Initialisierung     |

### **Daten‑Eingänge**
| Name | Typ  | Kommentar                                                     |
|------|------|---------------------------------------------------------------|
| Tmin | TIME | Minimale Zeit zwischen zwei aufeinanderfolgenden CLK‑Ereignissen |

### **Daten‑Ausgänge**
Der Block besitzt keine expliziten Datenausgänge; die Ausgabe erfolgt ausschließlich über den Adapter **Q**.

### **Adapter**
| Richtung | Adapter | Typ                                                | Kommentar               |
|----------|---------|-----------------------------------------------------|-------------------------|
| Socket   | I       | adapter::types::unidirectional::AS                 | Eingangsdaten (D1) und Takt (E1) |
| Plug     | Q       | adapter::types::unidirectional::AS                 | Ausgangsdaten (D1) und Ereignis (E1) |

Die Adapter vom Typ `AS` bieten je einen Ereignis‑Ein‑/Ausgang (E1) und einen Daten‑Ein‑/Ausgang (D1).

## Funktionsweise
Nach einer erfolgreichen Initialisierung (INIT mit gültigem `Tmin`) arbeitet der Block wie ein getaktetes D‑Flipflop mit Zeitfilter:

* Ein Ereignis am Adaptereingang **I.E1** wird als Takt (CLK) interpretiert.
* Der Datenwert **I.D1** wird beim Eintreffen von I.E1 übernommen, **sofern der zeitliche Abstand zum letzten CLK‑Ereignis mindestens `Tmin` beträgt**. Andernfalls wird das Ereignis ignoriert.
* Bei erfolgreicher Übernahme wird der gespeicherte Wert am Datenausgang **Q.D1** ausgegeben und ein Ereignis **Q.E1** ausgelöst.

Die Zeitfilterung wird durch den intern verwendeten Baustein `E_D_FF_ANY_TMIN` realisiert, der das Taktereignis verzögert oder verwirft, falls die Mindestzeit nicht eingehalten wird.

## Technische Besonderheiten
- **Adapter‑basierte Ein‑/Ausgabe**: Daten und Ereignisse werden nicht als separate Variablen, sondern über unidirektionale Adapter (`AS`) ausgetauscht. Das erlaubt eine modulare Verbindung mit anderen Blöcken.
- **Parameterisierbare Mindestzeit**: Die Zeit `Tmin` wird zur Initialisierung gesetzt und kann im laufenden Betrieb nicht geändert werden (ein erneuter INIT‑Aufruf ist erforderlich).
- **Ereignis‑Unterdrückung**: Zu dicht aufeinanderfolgende Taktereignisse werden stillschweigend ignoriert – es gibt keine Fehlermeldung.

## Zustandsübersicht
Der Block besitzt keine expliziten Zustandsmaschinen im Sinne eines Statecharts. Das Verhalten lässt sich jedoch in zwei Phasen beschreiben:

1. **Initialisierungsphase**: Nach dem INIT‑Ereignis wird `Tmin` intern gesetzt. Erst danach ist der Block bereit, CLK‑Ereignisse zu verarbeiten.
2. **Betriebsphase**: Der Block wartet auf CLK‑Ereignisse. Trifft eines ein, wird geprüft, ob die Zeitsperre (seit dem letzten CLK) abgelaufen ist. Wenn ja, wird der Datenwert übernommen und ausgegeben. Wenn nein, wird das Ereignis verworfen.

## Anwendungsszenarien
- **Entprellung von digitalen Signalen**: Ein Sensor liefert schnelle, prellende Signale; mit `Tmin` wird die minimale Pulsbreite festgelegt.
- **Taktsynchronisation in zeitkritischen Systemen**: Vermeidung von Datenübernahmen schneller als eine vorgegebene Systemtaktgrenze.
- **Ratenbegrenzung für Kommunikationsschnittstellen**: Nur alle `Tmin` Sekunden wird ein neuer Wert akzeptiert (z. B. bei Bus‑Zugriffen).

## Vergleich mit ähnlichen Bausteinen
| Baustein         | Zeitfilterung                     | Zusätzliche Merkmale                      |
|------------------|-----------------------------------|-------------------------------------------|
| AS_D_FF          | Nein (sofortige Übernahme)        | Einfaches D‑Flipflop ohne Zeitbeschränkung |
| AS_D_FF_TMIN (dieser) | Ja, konfigurierbar über `Tmin` | Unterdrückt zu schnelle Taktfolgen        |
| AS_D_FF_TMAX     | Ja, maximale Zeit zwischen Takten | Erzwingt regelmäßige Übernahmen           |

## Fazit
Der Baustein **AS_D_FF_TMIN** erweitert ein einfaches D‑Flipflop um eine einstellbare Mindestzeit zwischen zwei Übernahmeereignissen. Durch die Adapter‑Schnittstelle und die klare Trennung von Initialisierung und Betrieb eignet er sich besonders für industrielle Steuerungen und zeitdiskrete Verarbeitungen, bei denen ein zu schnelles Schalten vermieden werden muss.