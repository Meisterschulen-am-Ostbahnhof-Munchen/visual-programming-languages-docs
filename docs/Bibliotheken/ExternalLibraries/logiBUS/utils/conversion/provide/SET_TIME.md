# SET_TIME


![SET_TIME](./SET_TIME.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_TIME** dient dazu, einen über den Dateneingang `IN` bereitgestellten Zeitwert (Typ `TIME`) in eine als InOut-Parameter übergebene Variable `OUT` zu schreiben. Der Baustein ist als einfacher, ereignisgesteuerter Block realisiert und bestätigt die Ausführung über den Ereignisausgang `CNF`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `REQ` | Normaler Ausführungsrequest. Lösen den Algorithmus aus, der den Wert von `IN` nach `OUT` kopiert. Assoziierte Daten: `IN`, `OUT`. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `CNF` | Bestätigung der erfolgreichen Ausführung. Wird nach Abschluss des Algorithmus gesendet. Assoziierte Daten: `OUT`. |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| `IN` | `TIME` | `T#0s` | Der Zeitwert, der in die Zielvariable geschrieben werden soll. |

### **Daten-Ausgänge**
| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| `OUT` | `TIME` (InOut) | `T#0s` | Zielvariable, die beim Aufruf als InOut-Parameter übergeben wird. Der Wert von `IN` wird in diese Variable kopiert. |

> **Hinweis:** `OUT` ist ein **InOut**-Parameter, d.h. er dient gleichzeitig als Ein- und Ausgang. Der Aufrufer muss eine beschreibbare Variable bereitstellen.

### **Adapter**
Keine vorhanden.

## Funktionsweise
1. Der Funktionsblock wartet auf ein Ereignis am Eingang `REQ`.
2. Beim Eintreten von `REQ` wird der Algorithmus ausgeführt: Der aktuelle Wert des Dateneingangs `IN` wird der InOut-Variable `OUT` zugewiesen (`OUT := IN`).
3. Nach erfolgreicher Zuweisung wird das Ereignis `CNF` ausgelöst, um dem aufrufenden Baustein die Fertigstellung zu signalisieren.

Die Ausführung erfolgt in einem einzigen EC-Zustand (`REQ`), der den Algorithmus genau einmal durchläuft.

## Technische Besonderheiten
- **InOut-Parameter:** `OUT` ist ein InOut-Datenpunkt. Dies ermöglicht es dem Baustein, direkt in eine vom Aufrufer bereitgestellte Variable zu schreiben, ohne einen zusätzlichen Datenausgang zu benötigen. Der Aufrufer muss sicherstellen, dass die referenzierte Variable existiert und beschreibbar ist.
- **Einfache Logik:** Der Baustein besteht aus nur einem EC-Zustand und einem ST-Algorithmus. Es gibt keine Verzweigungen, Timer oder internen Zustandsmaschinen.
- **Typisierung:** Sowohl `IN` als auch `OUT` sind vom Typ `TIME`, sodass nur Zeitwerte verarbeitet werden.

## Zustandsübersicht
Der Funktionsblock besitzt genau einen Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| `REQ` | Startzustand bei Initialisierung. Wird beim Eintreten von `REQ` aktiviert. Führt den Algorithmus aus und sendet `CNF`. |

Es gibt keine weiteren Zustände. Der Baustein kehrt nach Abschluss des Algorithmus in den Startzustand zurück und wartet auf das nächste `REQ`-Ereignis.

## Anwendungsszenarien
- **Setzen von Timer-Parametern:** Ein übergeordneter Steuerungsbaustein übergibt eine konkrete Verzögerungszeit (z.B. für einen `TON`- oder `TOF`-Baustein) über einen InOut-Parameter.
- **Initialisierung von Zeitvariablen:** In einer Startsequenz werden vordefinierte Zeitwerte in globale oder instanzspezifische Variablen geschrieben.
- **Kopieren von Zeitwerten:** Einmaliges Überschreiben einer Zeitvariablen mit einem berechneten oder konfigurierten Wert.
- **Parameter-Updates in Echtzeit:** Dynamisches Ändern einer Zeitreferenz, die von mehreren Bausteinen gemeinsam genutzt wird.

## Vergleich mit ähnlichen Bausteinen
- **Einfache MOVE-Blöcke (z.B. `MOVE` für generische Typen):** SET_TIME ist speziell auf den Typ `TIME` optimiert und verwendet einen InOut-Parameter, was Speicherplatz spart und die Datenweitergabe effizienter macht.
- **Direkte Zuweisung über IEC-61499-Verbindungen:** Eine einfache Verbindung von einem `OUT`-Port eines anderen Bausteins zum `IN`-Port eines Zielbausteins könnte ebenfalls einen Wert setzen, erfordert aber oft zusätzliche Ereignis-Kopplung. SET_TIME vereinfacht dies durch die explizite `REQ`/`CNF`-Steuerung.
- **Setzen über globale Variablen:** Andere Bausteine schreiben über Dienstschnittstellen direkt in globale Variablen. SET_TIME hingegen arbeitet typischerweise auf instanzspezifischen InOut-Parametern, was die Kapselung verbessert.

## Fazit
Der Funktionsblock **SET_TIME** ist ein einfacher, aber nützlicher Baustein zum Schreiben eines TIME-Wertes in eine als InOut referenzierte Variable. Seine klare Ereignissteuerung, der minimale Ressourcenverbrauch und die direkte Kopplung von Ein- und Ausgang über den InOut-Mechanismus machen ihn ideal für zeitkritische Zuweisungsaufgaben in der Automatisierungstechnik. Die Verwendung von Standard-IEC-61499-Mechanismen gewährleistet Interoperabilität und einfache Integration in bestehende Steuerungsprojekte.