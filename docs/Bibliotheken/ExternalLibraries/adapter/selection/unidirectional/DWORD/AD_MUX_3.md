# AD_MUX_3


![AD_MUX_3](./AD_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AD_MUX_3** dient als generischer 3‑Kanal‑Multiplexer für den analogen Datentransport über Adapter des Typs `adapter::types::unidirectional::AD`. Er wählt auf Basis eines Indexwertes `K` einen der drei Eingangsadapter (`IN1`/`IN2`/`IN3`) aus und leitet dessen Daten an den Ausgangsadapter `OUT` weiter. Der Baustein eignet sich für die dynamische Umschaltung zwischen verschiedenen analogen Signalquellen in Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index (0, 1 oder 2) |

### **Daten-Ausgänge**
Keine Datenausgänge definiert (die Datenweitergabe erfolgt über den Adapter `OUT`).

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (Ausgang) | OUT | adapter::types::unidirectional::AD | Ausgang, liefert die Daten des ausgewählten Eingangs |
| Socket (Eingang) | IN1 | adapter::types::unidirectional::AD | Eingangswert 1 (bei K=0 aktiv) |
| Socket (Eingang) | IN2 | adapter::types::unidirectional::AD | Eingangswert 2 (bei K=1 aktiv) |
| Socket (Eingang) | IN3 | adapter::types::unidirectional::AD | Eingangswert 3 (bei K=2 aktiv) |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein Ereignis am Eingang `REQ` triggert die Verarbeitung.
2. Der aktuelle Wert des Dateneingangs `K` (0, 1 oder 2) bestimmt, welcher der drei Eingangsadapter auf den Ausgangsadapter `OUT` durchgeschaltet wird:
   - `K = 0` → `IN1` wird auf `OUT` verbunden.
   - `K = 1` → `IN2` wird auf `OUT` verbunden.
   - `K = 2` → `IN3` wird auf `OUT` verbunden.
3. Nach erfolgreicher Umschaltung wird die Bestätigung über den Ereignisausgang `CNF` gesendet.

Der Adapter `OUT` stellt nach der Verarbeitung die Daten des ausgewählten Eingangs bereit. Die Umschaltung erfolgt unverzögert innerhalb eines einzigen Durchlaufs.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Funktionsbaustein implementiert (`GenericClassName = 'GEN_AD_MUX'`), was eine flexible Wiederverwendung mit unterschiedlichen Adaptertypen ermöglicht, sofern diese vom gleichen unidirektionalen AD‑Typ sind.
- **Keine Datenpufferung**: Die Übergabe der Daten erfolgt direkt über die Adapter, ohne Zwischenspeicherung.
- **Eingabeschutz**: Für Werte von `K` außerhalb des gültigen Bereichs (0–2) ist das Verhalten nicht spezifiziert – in einer konkreten Implementierung sollte dies durch zusätzliche Maßnahmen abgefangen werden.

## Zustandsübersicht
Der Baustein besitzt keine expliziten Zustände im Sinne einer State‑Machine. Er reagiert auf jedes `REQ`‑Ereignis und führt sofort die Umschaltung aus. Nach Ausgabe von `CNF` ist der Baustein wieder bereit für das nächste Ereignis.

## Anwendungsszenarien
- **Umschaltung zwischen mehreren analogen Sensoren** (z. B. Temperatur‑, Druck‑ oder Füllstandssensoren) in einer Steuerung.
- **Aufruf verschiedener Konfigurationen** in Abhängigkeit von Betriebsmodi oder Produktvarianten.
- **Test‑ und Prüfstände**, bei denen wechselnde Signalquellen auf eine gemeinsame Auswerteeinheit geschaltet werden.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem einfachen analogen Schalter (z. B. `MUX_2` mit zwei Kanälen) erweitert `AD_MUX_3` die Auswahl auf drei Kanäle. Multichannel‑Multiplexer mit mehr als drei Kanälen (z. B. `AD_MUX_4_`) sind denkbar, indem der Adapter‑Typ und die Anzahl der Sockets entsprechend angepasst werden. Der vorliegende Baustein bietet eine gute Balance zwischen Flexibilität und Einfachheit.

## Fazit
Der **AD_MUX_3** ist ein kompakter, generischer Multiplexer‑Baustein für unidirektionale analoge Daten. Durch seine klare ereignisgesteuerte Schnittstelle und die Verwendung von IEC 61499‑Adaptern eignet er sich hervorragend für den modularen Aufbau von Automatisierungsanwendungen, die eine dynamische Signalauswahl erfordern.