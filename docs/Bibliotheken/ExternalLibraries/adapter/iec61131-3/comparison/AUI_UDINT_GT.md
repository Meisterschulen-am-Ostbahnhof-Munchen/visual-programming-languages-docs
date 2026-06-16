# AUI_UDINT_GT


![AUI_UDINT_GT](./AUI_UDINT_GT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUI_UDINT_GT` realisiert einen Vergleich zweier vorzeichenloser 32‑Bit‑Ganzzahlen (UDINT) auf „größer als“. Der Baustein gehört zur Familie der IEC‑61131‑3‑Vergleichsfunktionen und ist speziell für den Einsatz mit Adapter‑Schnittstellen (unidirektional) konzipiert. Die Verarbeitung wird durch ein eingehendes Ereignis ausgelöst.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `REQ` | Event | Service Request – löst die Vergleichsoperation aus. Erwartet einen gültigen Wert an `IN2`. |

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Das Ergebnis wird über den Adapter `OUT` ausgegeben.

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `IN2` | UDINT | Zweiter Eingangswert für den Vergleich (Wert 2). |

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Das Vergleichsergebnis wird über den Adapter `OUT` ausgegeben.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| `IN1` | `adapter::types::unidirectional::AUI` | Socket | Aufnehmender Adapter – liefert den ersten Eingangswert (Wert 1) und ein Auslöseereignis. |
| `OUT` | `adapter::types::unidirectional::AX` | Plug | Ausgebender Adapter – gibt das Vergleichsergebnis (Boolescher Wert) sowie ein Bestätigungsereignis aus. |

## Funktionsweise
Der Baustein vergleicht die beiden Eingangswerte `IN1` und `IN2` nach der **größer-als**‑Relation.

- Der Wert `IN1` wird über den Adapter `IN1` (Socket) bezogen.  
- Der Wert `IN2` wird direkt am Daten-Eingang `IN2` angelegt.  
- Ein Ereignis an `REQ` oder das über den Adapter kommende Ereignis löst die Verarbeitung aus.  
- Intern wird der eigentliche Vergleich durch den Funktionsblock `F_GT` durchgeführt.  
- Das Ergebnis (`TRUE` wenn `IN1 > IN2`, sonst `FALSE`) wird über den Adapter `OUT` (Plug) ausgegeben, begleitet von einem Ereignis an dessen E1‑Eingang.

## Technische Besonderheiten
- **Adapterbasierte Kommunikation:** Der Baustein kapselt die Ein‑ und Ausgabe in unidirektionalen Adaptern. Dadurch kann er leicht in komplexe Komponentennetzwerke eingebunden werden, ohne direkte Daten‑ oder Ereignisverbindungen auf jeder Ebene.
- **Interner Subbaustein:** Die Verarbeitungslogik wird nicht selbst implementiert, sondern durch den standardisierten `F_GT`-Baustein aus der IEC‑61131‑3‑Bibliothek realisiert.
- **Typisierung:** Alle Daten sind vom Typ `UDINT` – vorzeichenlose 32‑Bit‑Ganzzahlen nach IEC 61131‑3.
- **Parallele Auslösung:** Sowohl das Ereignis `REQ` als auch das vom Adapter `IN1` kommende Ereignis können die Operation starten; dies ermöglicht flexible Steuerungsmuster.

## Zustandsübersicht
Der Baustein besitzt keine eigene explizite Zustandsmaschine. Das Verhalten ist rein ereignisgesteuert:
- **Initial:** Warten auf ein Ereignis an `REQ` oder über `IN1.E1`.
- **Verarbeitung:** Nach Eintreffen eines Ereignisses und gültiger Daten wird der Vergleich ausgeführt.
- **Ausgabe:** Sofort nach Abschluss wird das Ergebnis über `OUT` zusammen mit einem Ereignis ausgegeben.

Ein- und Ausgangsdaten werden nicht zwischengespeichert; der Baustein arbeitet im reinen kombinatorischen Modus.

## Anwendungsszenarien
- **Grenzwertüberwachung:** Prüfen, ob ein Messwert (z. B. Drehzahl, Füllstand) einen vorgegebenen Schwellwert überschreitet.
- **Zustandssteuerung:** Auslösen einer Aktion, wenn eine Zählvariable größer als ein Limit ist.
- **Sequenzielle Ablaufsteuerung:** Ermitteln des übergeordneten Index oder der Priorität in einer Ablaufkette.
- **Adapter‑basierte Komponenten:** Einbinden dieses Bausteins in eine Komponentenbibliothek, die über genormte Adapter kommuniziert (z. B. nach dem 4diac‑IDE‑Ansatz).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Adaptertyp |
|----------|----------|------------|
| `AUI_UDINT_GT` | `IN1 > IN2` | AUI (Socket), AX (Plug) |
| `AUI_UDINT_LT` | `IN1 < IN2` | analog |
| `AUI_UDINT_EQ` | `IN1 = IN2` | analog |
| `AUI_UDINT_GE` | `IN1 >= IN2` | analog |
| `AUI_UDINT_LE` | `IN1 <= IN2` | analog |
| `AUI_UDINT_NE` | `IN1 != IN2` | analog |

Diese Bausteinserie bildet die vollständige Menge der sechs Vergleichsoperatoren ab und unterscheidet sich nur durch die ausgewählte Vergleichsfunktion. Die Schnittstelle ist identisch, sodass ein Austausch ohne Änderung der Verbindungen möglich ist.

## Fazit
`AUI_UDINT_GT` ist ein spezialisierter, aber flexibler Vergleichsbaustein für den industriellen Einsatz. Die Verwendung von Adaptern vereinfacht die Integration in modulare Automatisierungssysteme und macht die Schnittstelle wiederverwendbar. Dank der IEC‑61131‑3‑Konformität und der einfachen internen Struktur eignet er sich besonders für klare, wartbare Steuerungslogiken.