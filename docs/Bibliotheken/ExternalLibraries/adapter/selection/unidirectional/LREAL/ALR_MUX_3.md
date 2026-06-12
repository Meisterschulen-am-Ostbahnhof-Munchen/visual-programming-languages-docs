# ALR_MUX_3


![ALR_MUX_3](./ALR_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_MUX_3** ist ein generischer Multiplexer für ALR‑Adapterverbindungen. Er wählt anhand eines Indexwertes `K` einen von drei ALR‑Eingängen (`IN1`, `IN2`, `IN3`) aus und leitet dessen Daten an den Ausgang `OUT` weiter. Der Baustein wird über das Ereignis `REQ` gesteuert und quittiert die Verarbeitung mit `CNF`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `REQ`    | Event    | Startet die Auswahl des Index `K` und aktualisiert den Ausgang `OUT`. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `CNF`    | Event    | Bestätigt die erfolgreiche Durchführung der Indexauswahl. |

### **Daten-Eingänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `K`  | `UINT`   | Index zur Auswahl des aktiven Eingangs (Werte 0, 1 oder 2). |

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden.*  
Die Ausgabe erfolgt ausschließlich über den Adapter `OUT`.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| **Plug** | `OUT`  | `adapter::types::unidirectional::ALR` | Ausgang des Multiplexers – enthält die Daten des ausgewählten Eingangs. |
| **Socket** | `IN1`  | `adapter::types::unidirectional::ALR` | Erster Eingang (Auswahl bei `K = 0`). |
| **Socket** | `IN2`  | `adapter::types::unidirectional::ALR` | Zweiter Eingang (Auswahl bei `K = 1`). |
| **Socket** | `IN3`  | `adapter::types::unidirectional::ALR` | Dritter Eingang (Auswahl bei `K = 2`). |

## Funktionsweise
Der Baustein arbeitet streng ereignisgesteuert:
1. Ein Impuls am Ereigniseingang `REQ` löst die Verarbeitung aus.
2. Der aktuelle Wert des Daten‑Eingangs `K` wird ausgewertet.
3. Abhängig von `K` wird der entsprechende Adapter‑Socket (`IN1`, `IN2` oder `IN3`) auf den Ausgangs‑Plug `OUT` durchgeschaltet.
4. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben.

Wird ein ungültiger Indexwert (z. B. größer als 2) angelegt, ist das Verhalten nicht spezifiziert – in der Praxis sollte ein sicherer Fehlerzustand vermieden werden.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Klassenbaustein (`GenericClassName = 'GEN_ALR_MUX'`) implementiert, was erlaubt, den inneren Aufbau an verschiedene ALR‑Adaptervarianten anzupassen.
- **ALR‑Adapter**: Alle Ein‑ und Ausgänge sind als unidirektionale ALR‑Adapter ausgeführt. Dadurch werden komplexe Datenstrukturen oder Signale in einer standardisierten Schnittstelle gekapselt.
- **Keine Daten‑Ausgänge**: Die Ausgabe erfolgt rein über den Adapter‑Plug, was die Integration in bestehende Komponentennetzwerke vereinfacht.

## Zustandsübersicht
Der FB besitzt keine expliziten Zustandsautomaten im XML. Das Verhalten ist rein durch die Ereignissteuerung definiert:
- **Warten** auf `REQ`
- Nach `REQ`: Auswerten von `K`, Durchschalten des entsprechenden Eingangs
- Ausgabe von `CNF`

Eine detaillierte Zustandsmaschine wird vom generischen Framework beim Kompilieren des FB‑Instanz bereitgestellt.

## Anwendungsszenarien
- **Quellenumschaltung**: In einer Steuerung können drei verschiedene ALR‑Datenquellen (z. B. Sensoren, Berechnungen) über einen Index ausgewählt werden.
- **Modulare Konfiguration**: Der Baustein eignet sich, um während des Betriebs zwischen verschiedenen Betriebsmodi zu wechseln.
- **Test‑ und Simulationsumgebungen**: Zum Einspielen unterschiedlicher Testdaten in ein ALR‑basiertes System.

## Vergleich mit ähnlichen Bausteinen
- **ALR_MUX_3**: Speziell für zwei Eingänge (Kanal 0 und 1) – hier werden alle drei Eingänge genutzt.
- **Allgemeine Multiplexer‑FB** (z. B. `MUX` aus IEC‑61499‑Standardbibliotheken): Diese arbeiten meist mit skalaren Datentypen (BOOL, INT) und nicht mit Adaptern. Der **ALR_MUX_3** ist auf die ALR‑Adapter‑Schnittstelle optimiert.
- Im Gegensatz zu einem analogen Schalter oder Datenverteiler liegt der Fokus auf der Ereignis‑gesteuerten Übergabe vollständiger ALR‑Pakete.

## Fazit
Der **ALR_MUX_3** ist ein kompakter, generischer Multiplexer für die ALR‑Adapter‑Schnittstelle. Er ermöglicht die flexible Umschaltung zwischen drei Datenquellen auf Basis eines Indexwerts. Dank seiner Adapter‑basierten Ein‑/Ausgabe und der generischen Typisierung lässt er sich einfach in IEC‑61499‑Projekte integrieren und erweitern.