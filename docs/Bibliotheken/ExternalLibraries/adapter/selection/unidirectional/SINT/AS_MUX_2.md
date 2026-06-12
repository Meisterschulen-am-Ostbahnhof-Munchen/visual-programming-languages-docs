# AS_MUX_2


![AS_MUX_2](./AS_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der AS_MUX_2 ist ein generischer Multiplexer-Funktionsblock, der es ermöglicht, zwischen zwei Eingangsadaptern (IN1 und IN2) auszuwählen und den gewählten Adapter auf den Ausgangsadapter (OUT) zu schalten. Die Auswahl erfolgt über eine ganzzahlige Indexvariable K. Der Baustein wird typischerweise eingesetzt, um verschiedene Signalquellen oder Datenpfade dynamisch umzuschalten, ohne die Verbindungen zur Laufzeit neu konfigurieren zu müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Mit Variablen | Beschreibung |
|----------|----------|---------------|--------------|
| `REQ`    | Event    | `K`           | Startet die Auswahl des Eingangs. Der Wert von `K` bestimmt, welcher Adapter durchgeschaltet wird. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Mit Variablen | Beschreibung |
|----------|----------|---------------|--------------|
| `CNF`    | Event    | –             | Bestätigt, dass die Umschaltung abgeschlossen ist und der gewählte Adapter aktiv ist. |

### **Daten-Eingänge**
| Variable | Datentyp | Beschreibung |
|----------|----------|--------------|
| `K`      | UINT     | Index für die Auswahl: `0` → IN1, `1` → IN2. Andere Werte sind ungültig und führen zu keiner Umschaltung. |

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**
| Typ       | Name | Richtung | Beschreibung |
|-----------|------|----------|--------------|
| Plug      | OUT  | Ausgang  | Ausgangsadapter, der mit dem gewählten Eingang verbunden wird. |
| Socket (Eingang) | IN1  | Eingang  | Erster Eingangsadapter, der bei `K = 0` ausgewählt wird. |
| Socket (Eingang) | IN2  | Eingang  | Zweiter Eingangsadapter, der bei `K = 1` ausgewählt wird. |

Alle Adapter sind vom Typ **`adapter::types::unidirectional::AS`**, einem unidirektionalen Adapter, der Daten in eine Richtung transportiert.

## Funktionsweise
Der Funktionsblock arbeitet als **1‑aus‑2‑Multiplexer** auf Adapterebene.  
Bei einem Ereignis am Eingang `REQ` wird der aktuelle Wert von `K` ausgewertet:

- **K = 0**: Der Adapter `IN1` wird intern mit dem Ausgangsadapter `OUT` verbunden.  
- **K = 1**: Der Adapter `IN2` wird mit `OUT` verbunden.  
- **K ≠ 0 und ≠ 1**: Es erfolgt keine Umschaltung; der zuvor gewählte Adapter bleibt aktiv.

Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben. Während der Verarbeitung eines `REQ`-Ereignisses wird keine weitere Anfrage angenommen (der Baustein ist bis zur Ausgabe von `CNF` blockiert).

## Technische Besonderheiten
- **Generischer Baustein**: Der AS_MUX_2 ist als generischer Funktionsblock (`eclipse4diac::core::GenericClassName = 'GEN_AS_MUX'`) implementiert. Dadurch kann er mit verschiedenen Adaptertypen instanziiert werden, solange alle drei Adapter (IN1, IN2, OUT) denselben Typ besitzen.
- **Unidirektionale Adapter**: Die verwendeten Adapter sind unidirektional, d.h. Daten fließen nur in eine Richtung – vom Eingang zum Ausgang.
- **Indexbereich**: Der Eingang `K` ist als `UINT` definiert, es werden jedoch nur die Werte 0 und 1 sinnvoll verarbeitet. Höhere Werte führen zu keiner Reaktion.

## Zustandsübersicht
Der Baustein besitzt einen einfachen internen Zustandsautomaten:

| Zustand | Beschreibung |
|---------|--------------|
| **IDLE** | Warten auf ein `REQ`-Ereignis. |
| **SELECT** | Auswerten von `K` und Durchschalten des entsprechenden Adapters (IN1 oder IN2). |
| **DONE** | Senden von `CNF` und Rückkehr in den IDLE-Zustand. |

Während sich der Baustein im Zustand `SELECT` befindet, wird kein weiteres `REQ`-Ereignis akzeptiert.

## Anwendungsszenarien
- **Sensorumschaltung**: Auswahl zwischen zwei verschiedenen Sensoren (z.B. Temperatur- und Drucksensor), je nach Anforderung.
- **Signalpfadauswahl**: Umschalten zwischen zwei verschiedenen Datenquellen in einer Steuerung.
- **Test- und Diagnose**: Temporäres Umleiten von Signalen zu Testzwecken ohne Änderung der Verdrahtung.

## Vergleich mit ähnlichen Bausteinen
- **MUX (Daten-Multiplexer)**: Wählt auf Datenebene (z.B. `INT`, `REAL`) zwischen mehreren Werten aus. AS_MUX_2 arbeitet dagegen auf Adapterebene und schaltet komplette Verbindungen um.
- **SEL (Selector)**: Einfache Fallunterscheidung mit Daten-Ein-/Ausgängen. AS_MUX_2 nutzt Adapter, was flexiblere und strukturiertere Verbindungen ermöglicht.
- **Adapter-basierte Multiplexer anderer Bibliotheken**: Oft auf mehrere Kanäle erweitert (z.B. 4‑fach); der AS_MUX_2 fokussiert auf die 2‑fach-Auswahl.

## Fazit
Der AS_MUX_2 ist ein kompakter und generischer Baustein zur Umschaltung zwischen zwei Adaptern. Dank der Adaptertechnik lassen sich komplexe Signalpfade sauber modellieren und zur Laufzeit dynamisch umschalten. Die einfache Handhabung (ein Ereigniseingang, ein Index) macht ihn besonders geeignet für Anwendungen, die eine schnelle und zuverlässige Quellenauswahl erfordern.