# AI_TO_AUI


![AI_TO_AUI](./AI_TO_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_TO_AUI** ist ein Composite-Baustein, der einen INT-Adapter (AI) in einen UINT-Adapter (AUI) umwandelt. Er dient als Schnittstellenkonverter in Systemen, die auf unidirektionale Adapter-Kommunikation setzen. Im Inneren nutzt er den Baustein `F_INT_TO_UINT` aus der IEC 61131‑Bibliothek, um den Integer-Wert von `AI_IN` in einen vorzeichenlosen Integer zu konvertieren und über `AUI_OUT` bereitzustellen.

## Schnittstellenstruktur
### Ereignis-Eingänge
Keine separaten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt ausschließlich über die Adapter (`AI_IN.E1` für Anforderung, `AUI_OUT.E1` für Bestätigung).

### Ereignis-Ausgänge
Keine separaten Ereignis-Ausgänge vorhanden. Die Ereignisrückmeldung wird über den Adapter `AUI_OUT.E1` bereitgestellt.

### Daten-Eingänge
Keine separaten Daten-Eingänge vorhanden. Der zu konvertierende Wert wird über den Adapter `AI_IN.D1` (Typ INT) angenommen.

### Daten-Ausgänge
Keine separaten Daten-Ausgänge vorhanden. Der konvertierte Wert wird über den Adapter `AUI_OUT.D1` (Typ UINT) bereitgestellt.

### Adapter

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `AI_IN` | `adapter::types::unidirectional::AI` | INT‑Adapter‑Eingang. Liefert das Ereignis `E1` und den Datenwert `D1` (INT). |
| Plug (Ausgang) | `AUI_OUT` | `adapter::types::unidirectional::AUI` | UINT‑Adapter‑Ausgang. Stellt das Ereignis `E1` und den Datenwert `D1` (UINT) bereit. |

## Funktionsweise
Der FB arbeitet als einfache Pipeline:
1. Ein Ereignis wird über `AI_IN.E1` empfangen.
2. Dieses Ereignis triggert den internen Konvertier-Baustein `F_INT_TO_UINT` über dessen `REQ`‑Eingang.
3. Der Wert von `AI_IN.D1` (INT) wird an `Convert.IN` weitergeleitet.
4. Nach Abschluss der Konvertierung wird über `Convert.CNF` ein Ereignis an `AUI_OUT.E1` gesendet.
5. Der konvertierte Wert (UINT) steht an `AUI_OUT.D1` zur Verfügung.

Der Baustein ist rein kausal – er reagiert auf ein eingehendes Ereignis und gibt nach der Umwandlung ein ausgehendes Ereignis aus.

## Technische Besonderheiten
- **Adapter‑basierte Kommunikation**: Statt klassischer Ein‑/Ausgangspins werden die Schnittstellen über Adapter (`AI` und `AUI`) realisiert. Dies ermöglicht eine lose Kopplung in modularen Systemen.
- **Unidirektionaler Datenfluss**: Beide Adapter sind unidirektional, d. h. sie transportieren Daten und Ereignisse nur in eine Richtung (Ein‑ oder Ausgang).
- **Paketierung**: Der Baustein befindet sich im Paket `adapter::conversion::unidirectional`, was seine Rolle als Konverter zwischen Adapter‑Typen kennzeichnet.
- **Typumwandlung**: Die Konvertierung von `INT` in `UINT` erfolgt mittels des IEC‑61131‑Bausteins `F_INT_TO_UINT`, der eine Wert‑Erhaltung bei positiven Zahlen gewährleistet. Negative Werte werden in den entsprechenden UINT‑Raum (z. B. Zweierkomplement) umgesetzt.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Er durchläuft intern nur den Ablauf: Ereignis empfangen → Konvertierung auslösen → Ereignis senden. Es gibt keine verzögerten Reaktionen oder dauerhaften Zustände.

## Anwendungsszenarien
- **Sensor‑Schnittstellenanpassung**: Ein Sensor liefert Messwerte als `INT` (z. B. Temperatur oder Druck) über einen AI‑Adapter; die nachfolgende Steuerung erwartet `UINT` über einen AUI‑Adapter.
- **Systemintegration**: In heterogenen Systemen, in denen unterschiedliche Adapter‑Typen verwendet werden, ermöglicht `AI_TO_AUI` die nahtlose Verbindung von Komponenten.
- **Datenaufbereitung**: Vor der Weiterverarbeitung in einer SPS, die nur vorzeichenlose Werte unterstützt (z. B. für Zähler oder Skalierung).

## Vergleich mit ähnlichen Bausteinen
- **`AI_TO_AUI` vs. direkte Konvertierung mit `F_INT_TO_UINT`**: Der Composite-Baustein kapselt die Adapter‑Schnittstellen und macht die Anwendung für den Entwickler einfacher – es müssen keine einzelnen FBs mit Signalverbindungen verdrahtet werden.
- **Ähnliche Adapter‑Konverter**: In der Bibliothek existieren ggf. weitere Bausteine wie `AUI_TO_AI` (Rückkonvertierung) oder Konverter für andere Datentypen (z. B. `REAL_TO_INT`). `AI_TO_AUI` ist speziell auf die Kombination von INT‑ und UINT‑Adapter zugeschnitten.

## Fazit
Der Baustein `AI_TO_AUI` bietet eine kompakte, wiederverwendbare Lösung zur Umwandlung eines INT‑Adapter‑Datenstroms in einen UINT‑Adapter‑Datenstrom. Er reduziert die Komplexität der Verschaltung und stellt sicher, dass die Datenkonvertierung korrekt und ereignisgesteuert erfolgt. Dank der Adapter‑Schnittstellen fügt er sich nahtlos in modulare, unidirektionale Architekturen ein.