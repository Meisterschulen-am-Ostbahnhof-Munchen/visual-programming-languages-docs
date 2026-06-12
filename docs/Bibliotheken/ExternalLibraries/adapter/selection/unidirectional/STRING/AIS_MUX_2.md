# AIS_MUX_2


![AIS_MUX_2](./AIS_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AIS_MUX_2` realisiert einen generischen Multiplexer für den Adaptertyp `adapter::types::unidirectional::AIS`. Er wählt anhand eines Index (K) einen von zwei Eingangsadaptern (IN1, IN2) aus und leitet dessen Signale auf den Ausgangsadapter (OUT) weiter. Der Baustein ist für die Verwendung in IEC 61499 konzipiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Setzt den Index K und löst die Umschaltung aus. |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigt die Übernahme des neuen Index K. |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | UINT | Index für die Auswahl des aktiven Eingangs (0 = IN1, 1 = IN2). |

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden. Die Weiterleitung der Adaptersignale erfolgt über die Adapter-Schnittstellen.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (Ausgang) | `OUT` | `adapter::types::unidirectional::AIS` | Ausgangsadapter, der den ausgewählten Eingang widerspiegelt. |
| Socket (Eingang) | `IN1` | `adapter::types::unidirectional::AIS` | Erster Eingangsadapter (wird bei K = 0 durchgeschaltet). |
| Socket (Eingang) | `IN2` | `adapter::types::unidirectional::AIS` | Zweiter Eingangsadapter (wird bei K = 1 durchgeschaltet). |

## Funktionsweise
Der Baustein arbeitet als einfacher 2‑zu‑1‑Multiplexer auf Adapterebene. Sobald das Ereignis `REQ` eintritt, wird der Wert von `K` ausgewertet:
- Ist `K = 0`, werden die Signale des Adapters `IN1` auf den Ausgangsadapter `OUT` gelegt.
- Ist `K = 1`, werden die Signale von `IN2` auf `OUT` gelegt.
Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben.

Der Umschaltvorgang erfolgt innerhalb einer einzigen Ausführungssequenz, sodass keine Zwischenzustände auftreten.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GenericClassName = 'GEN_AIS_MUX'`) deklariert und kann für beliebige Ausprägungen des `AIS`-Adaptertyps verwendet werden.
- **Keine Datenausgänge**: Die gesamte Datenweiterleitung erfolgt über die Adapter-Schnittstellen, es werden keine separaten Werte (z. B. als `ANY`) ausgegeben.
- **TypHash**: Ein Attribut `TypeHash` ist vorhanden, wird aber standardmäßig leer gelassen. Es ermöglicht kryptografische Prüfsummen zur Laufzeitidentifikation, falls benötigt.
- **Ereignisgesteuert**: Die Umschaltung erfolgt nur auf ein explizites `REQ`‑Signal; ohne dieses bleibt der letzte aktive Ausgang bestehen.

## Zustandsübersicht
Der Baustein besitzt implizit zwei Zustände, die durch das Ereignis `REQ` durchlaufen werden:

| Zustand | Beschreibung |
|---------|--------------|
| **IDLE** | Warten auf ein `REQ`-Ereignis. Der Ausgang `OUT` ist mit dem zuletzt ausgewählten Eingang verbunden. |
| **SWITCH** | Bei Eintreffen von `REQ` wird der Index `K` gelesen, die Verbindung zu `IN1` oder `IN2` hergestellt und `CNF` ausgegeben. Danach kehrt der Baustein in den **IDLE**-Zustand zurück. |

Eine grafische Zustandsmaschine ist nicht Bestandteil der XML‑Definition; das Verhalten wird durch die Ereignislogik der Ausführungsumgebung abgebildet.

## Anwendungsszenarien
- **Quellenumschaltung**: Wechsel zwischen zwei AIS‑Datenquellen, z. B. unterschiedliche Sensoren oder Kommunikationskanäle.
- **Redundanz**: Umschaltung auf einen Ersatz‑Eingang, falls der primäre Kanal ausfällt (gesteuert durch eine übergeordnete Logik).
- **Test & Diagnose**: Temporäre Verbindung eines Prüfadapters anstelle des normalen Datenstroms.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑Multiplexer (z. B. MUX)**: Diese arbeiten meist auf einfachen Datentypen (INT, BOOL) und geben einen Datenwert aus. Der `AIS_MUX_2` arbeitet hingegen auf dem gesamten Adapter‑Interface, sodass mehrere zusammengehörige Signale gleichzeitig umgeschaltet werden.
- **Adapter‑Selektoren (z. B. SELECT)**: Vergleichbare Bausteine existieren für andere Adaptertypen; der vorliegende ist speziell auf den `AIS`‑Typ zugeschnitten.

## Fazit
Der `AIS_MUX_2` ist ein kompakter und effizienter Funktionsblock zur Auswahl zwischen zwei AIS‑Adaptereingängen. Seine generische Deklaration erlaubt den Einsatz in verschiedenen Kontexten, während die reine Adapter‑Schnittstelle die Integration in bestehende IEC 61499‑Systeme vereinfacht. Die einfache Ereignissteuerung macht ihn gut vorhersagbar und leicht in übergeordnete Steuerungslogiken einbindbar.