# AR_ADD_2


![AR_ADD_2](./AR_ADD_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AR_ADD_2** dient der Berechnung der arithmetischen Addition zweier Werte. Er ist als generischer FB ausgelegt und realisiert die grundlegende Rechenoperation über Adapter-Schnittstellen. Der Baustein ist plattformunabhängig und folgt dem IEC‑61499‑Standard.

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
|-------------|----------|-----|-----------|
| `IN1` | Socket | `adapter::types::unidirectional::AR` | ADD input 1 |
| `IN2` | Socket | `adapter::types::unidirectional::AR` | ADD input 2 |
| `OUT` | Plug | `adapter::types::unidirectional::AR` | ADD result |

Die Adapter sind vom Typ `unidirectional::AR` und ermöglichen die typsichere Verbindung mit anderen Bausteinen, die denselben Adaptertyp unterstützen.

## Funktionsweise

Der FB führt die Addition der beiden über die Adapter `IN1` und `IN2` anliegenden Werte durch. Das Ergebnis wird am Adapter `OUT` bereitgestellt. Die genaue Dateninterpretation (Datentyp, Wertebereich) wird durch den verwendeten Adaptertyp bestimmt; der Baustein selbst arbeitet generisch und delegiert die Typinformation an das zugrundeliegende Framework.

Die eigentliche Berechnung erfolgt im Hintergrund über die konfigurierten Laufzeitumgebungen – der FB definiert lediglich die Schnittstellen und die Semantik der Addition.

## Technische Besonderheiten

- **Generischer Aufbau** – Der FB verwendet zur Laufzeit einen generischen Klassennamen (`GEN_AR_ADD`), der durch das Attribut `eclipse4diac::core::GenericClassName` festgelegt wird. Dies ermöglicht eine spätere Spezialisierung auf konkrete Datentypen (z. B. Ganzzahlen oder Gleitkommazahlen).
- **Adapterbasiert** – Statt einzelner Daten-Ein- und Ausgänge werden alle Signale über unidirektionale Adapter geführt. Das vereinfacht die Kapselung und Wiederverwendung in komplexen Systemen.
- **Paketangabe** – Der FB ist im Paket `adapter::iec61131::arithmetic` organisiert, was auf eine Herkunft aus einer IEC‑61131‑Adapterbibliothek hindeutet.
- **Keine Zustandslogik** – Die Addition erfolgt zustandslos; es existiert kein interner Zustandsautomat.

## Zustandsübersicht

Der Baustein besitzt keinen Zustandsautomaten. Die Berechnung wird rein datengetrieben durchgeführt – bei Änderung der Eingangsadapter wird das Ergebnis neu berechnet.

## Anwendungsspezifische Szenarien

- **Signalverarbeitung** – Kombination zweier analoger oder digitaler Messwerte zu einer Summe.
- **Steuerungstechnik** – Aufsummieren von Zählerständen oder Zeitwerten.
- **Generische Bibliotheksbausteine** – Einsatz als Basis für anwendungsspezifische, getypte Additionsbausteine (z. B. `AR_ADD_INT`, `AR_ADD_REAL`).

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu klassischen, Daten-eingabebasierten Additionsbausteinen (z. B. `ADD`) zeichnet sich `AR_ADD_2` durch seine Adapterschnittstellen aus. Während Standard-Addierer oft mit einzelnen Eingängen (`IN1`, `IN2`) und einem Ausgang (`OUT`) arbeiten, ermöglichen Adapter die direkte Verbindung zu komplexeren Datenstrukturen und eine höhere Wiederverwendbarkeit durch Typsicherheit. Der Baustein ist bewusst generisch gehalten, was eine dynamische Typanpassung zur Laufzeit erlaubt.

## Fazit

`AR_ADD_2` ist ein kompakter, generischer Funktionsbaustein für die Addition von zwei Werten mittels Adapter-Schnittstellen. Er eignet sich besonders für systemübergreifende Anwendungen, bei denen Typflexibilität und lose Kopplung durch Adapter gefragt sind. Die einfache, zustandslose Architektur macht ihn robust und leicht in bestehende Automatisierungsprojekte integrierbar.