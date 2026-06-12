# ALR_TO_AULI


![ALR_TO_AULI](./ALR_TO_AULI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_TO_AULI** ist ein **Composite FB** zur unidirektionalen Umwandlung eines **LREAL-Adapter-Signals** (Typ `ALR`) in ein **ULINT-Adapter-Signal** (Typ `AULI`). Durch die interne Verwendung des IEC‑61131‑Standard-FBs `F_LREAL_TO_ULINT` wird die Gleitkommazahl (LREAL) in eine vorzeichenlose Ganzzahl (ULINT) konvertiert und über einen Ausgangsadapter bereitgestellt. Der Baustein eignet sich besonders für die Integration von Gleitkomma-Datenquellen in Systeme, die eine ganzzahlige Adapter-Schnittstelle erwarten.

## Schnittstellenstruktur
Der FB besitzt **keine direkten** Ereignis‑ oder Datenein-/-ausgänge. Die Kommunikation erfolgt ausschließlich über die beiden **Adapter** (Socket & Plug). Die nachfolgenden Tabellen beschreiben die über die Adapter bereitgestellten Signale.

### **Ereignis-Eingänge**
| Signal | Quelle | Datentyp | Beschreibung |
|--------|--------|----------|--------------|
| E1 | über Socket `ALR_IN` | (Ereignis) | Startet die Konvertierung eines eingehenden LREAL-Wertes. |

### **Ereignis-Ausgänge**
| Signal | Ziel | Datentyp | Beschreibung |
|--------|------|----------|--------------|
| E1 | über Plug `AULI_OUT` | (Ereignis) | Signalisiert, dass der konvertierte ULINT-Wert am Ausgang anliegt. |

### **Daten-Eingänge**
| Signal | Quelle | Datentyp | Beschreibung |
|--------|--------|----------|--------------|
| D1 | über Socket `ALR_IN` | LREAL | Der umzuwandelnde Gleitkomma‑Wert. |

### **Daten-Ausgänge**
| Signal | Ziel | Datentyp | Beschreibung |
|--------|------|----------|--------------|
| D1 | über Plug `AULI_OUT` | ULINT | Der konvertierte ganzzahlige Wert ohne Vorzeichen. |

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `ALR_IN` | `adapter::types::unidirectional::ALR` | Socket (Eingang) | Nimmt den LREAL‑Wert sowie das dazugehörige Ereignis entgegen. |
| `AULI_OUT` | `adapter::types::unidirectional::AULI` | Plug (Ausgang) | Gibt den konvertierten ULINT‑Wert mit einem Bestätigungsereignis aus. |

## Funktionsweise
Der FB arbeitet nach dem **Getriebe‑Prinzip** eines Composite-Bausteins:
1. Ein eingehendes **Ereignis E1** am Socket `ALR_IN` aktiviert den internen FB `F_LREAL_TO_ULINT` (Typ `iec61131::conversion::F_LREAL_TO_ULINT`).
2. Gleichzeitig wird der am Socket `ALR_IN` anliegende **Datenwert D1** (LREAL) an den Eingang `IN` des internen FBs weitergeleitet.
3. Der interne FB führt sofort die Konvertierung von LREAL nach ULINT durch und gibt das Ergebnis an seinem Ausgang `OUT` aus.
4. Das Ereignis `CNF` des internen FBs triggert das **Ausgangsereignis E1** am Plug `AULI_OUT`.
5. Der konvertierte ULINT‑Wert wird parallel an den Datenausgang `D1` des Plug `AULI_OUT` gelegt.

Die gesamte Wandlung erfolgt **ereignisgesteuert** und ohne eigene Zustandslogik.

## Technische Besonderheiten
- **Lizenz**: Der FB wird unter der **Eclipse Public License 2.0** bereitgestellt (siehe Copyright‑Hinweis).
- **Standardkonformität**: Der intern verwendete Konvertierungsbaustein `F_LREAL_TO_ULINT` entspricht der IEC‑61131‑3‑Norm.
- **Keine Zustandsmaschine**: Als Composite FB besitzt der Baustein keine eigene Zustandslogik – die Konvertierung ist rein kombinatorisch.
- **Unidirektionale Adapter**: Ein‑ und Ausgang sind getrennte Adaptertypen, die eine klare Signalrichtung vorgeben.

## Zustandsübersicht
Da es sich um einen **Composite FB ohne eigene Zustandsmaschine** handelt, existiert keine explizite Zustandsübersicht. Die Funktionalität ist ereignisgetriggert und verhält sich wie eine **kombinatorische Funktion**: Ein Ereignis am Eingang führt nach einer internen Verarbeitung genau zu einem Ereignis am Ausgang.

## Anwendungsszenarien
- **Anbindung von Gleitkomma‑Sensoren** an eine Steuerung, die nur ganzzahlige Adapter-Signale verarbeitet (z. B. in der Agrartechnik).
- **Datenaufbereitung** in einer Adapter‑basierten Kommunikationskette, wenn die Quelle LREAL liefert, das Ziel aber ULINT erwartet.
- **Ersatz von manuellen Typumwandlungen** in Systemen, die auf die standardisierten IEC‑61131‑Funktionen setzen.

## Vergleich mit ähnlichen Bausteinen
Andere Konvertierungsadapter (z. B. `REAL_TO_DINT`, `LREAL_TO_LINT`) folgen demselben Muster: Sie nutzen einen internen IEC‑Funktionsbaustein und kapseln die Typumwandlung in einer Adapter‑Schnittstelle. Der Vorteil des `ALR_TO_AULI` liegt in der **zielgerichteten Kombination aus LREAL und ULINT** – eine Typkombination, die in vielen Standard‑Bibliotheken nicht als fertiger Adapter angeboten wird.

## Fazit
`ALR_TO_AULI` ist ein spezialisierter **Composite‑Adapter‑Baustein** zur verlustbehafteten Umwandlung von Gleitkomma‑ in Ganzzahlen. Dank der Verwendung eines normierten IEC‑Bausteins ist die Konvertierung deterministisch und gut testbar. Der FB eignet sich hervorragend, um in heterogenen Automatisierungssystemen eine saubere Adapter‑Schnittstelle zwischen LREAL‑ und ULINT‑Domänen zu schaffen.