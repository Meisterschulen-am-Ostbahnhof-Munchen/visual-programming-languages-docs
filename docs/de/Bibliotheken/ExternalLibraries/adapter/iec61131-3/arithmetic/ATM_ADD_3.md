# ATM_ADD_3

![ATM_ADD_3](./ATM_ADD_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **ATM_ADD_3** dient der Berechnung der arithmetischen Addition zweier Zeitwerte (Typ `TIME`). Er ist als generischer FB ausgelegt und realisiert die grundlegende Rechenoperation über Adapter-Schnittstellen. Der Baustein ist plattformunabhängig und folgt dem IEC‑61499‑Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine

### **Daten-Ausgänge**

Keine

### **Adapter**

| Bezeichnung | Richtung | Typ | Kommentar |
| ------------- | ---------- | ----- | ----------- |
| `IN1` | Socket | `adapter::types::unidirectional::ATM` | ADD input 1 |
| `IN2` | Socket | `adapter::types::unidirectional::ATM` | ADD input 2 |
| `IN3` | Socket | `adapter::types::unidirectional::ATM` | ADD input 3 |
| `OUT` | Plug | `adapter::types::unidirectional::ATM` | ADD result |

Die Adapter sind vom Typ `unidirectional::ATM` und ermöglichen die typsichere Verbindung mit anderen Bausteinen, die denselben Adaptertyp unterstützen.

## Funktionsweise

Der FB summiert die über die Adapter `IN1` und `IN2` anliegenden Zeitwerte auf und stellt das Ergebnis am Adapter `OUT` bereit. Ausgangspunkt der Summation ist der neutrale Wert `TIME#0s`, sodass bei nur einem tatsächlich angeschlossenen Eingang dessen Wert unverändert durchgereicht wird. Der Baustein arbeitet generisch – die Berechnung wird bei jedem Ereignis an einem der Eingangsadapter neu ausgeführt.

## Technische Besonderheiten

- **Generischer Aufbau** – Der FB verwendet zur Laufzeit einen generischen Klassennamen (`GEN_ATM_ADD`), der durch das Attribut `eclipse4diac::core::GenericClassName` festgelegt wird. Dieselbe Klasse deckt über den GenericClassName-Mechanismus die Aritäten `ATM_ADD_3`, `ATM_ADD_3` und `ATM_ADD_4` ab.
- **Adapterbasiert** – Statt einzelner Daten-Ein- und Ausgänge werden alle Signale über unidirektionale Adapter geführt.
- **Paketangabe** – Der FB ist im Paket `adapter::iec61131::arithmetic` organisiert.
- **Keine Zustandslogik** – Die Addition erfolgt zustandslos; es existiert kein interner Zustandsautomat.

## Zustandsübersicht

Der Baustein besitzt keinen Zustandsautomaten. Die Berechnung wird rein ereignisgetrieben durchgeführt – bei einem Ereignis an einem der Eingangsadapter wird die Summe neu berechnet.

## Anwendungsspezifische Szenarien

- **Zeitakkumulation** – Aufsummieren mehrerer Verzögerungs- oder Laufzeitwerte zu einer Gesamtdauer.
- **Steuerungstechnik** – Kombination zweier dynamisch ermittelter Zeitwerte, z. B. Basiszeit plus Zuschlag.
- **Generische Bibliotheksbausteine** – Einsatz als adapterbasiertes Pendant zur klassischen `ADD`-Funktion, spezialisiert auf `TIME`.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu `AR_ADD_2` (Addition zweier `REAL`-Werte über Adapter) ist `ATM_ADD_3` auf den Datentyp `TIME` spezialisiert. Anders als `AR_MULTIME`/`ATM_AR_MULTIME`, die einen Zeitwert mit einem numerischen Faktor multiplizieren, addiert `ATM_ADD_3` zwei gleichartige Zeitwerte.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

`ATM_ADD_3` ist ein kompakter, generischer Funktionsbaustein für die Addition von zwei Zeitwerten mittels Adapter-Schnittstellen. Er eignet sich besonders für Anwendungen, in denen mehrere Zeitdauern zu einer Gesamtdauer zusammengeführt werden müssen.
