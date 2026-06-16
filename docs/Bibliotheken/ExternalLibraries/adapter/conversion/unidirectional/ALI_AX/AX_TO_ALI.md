# AX_TO_ALI


![AX_TO_ALI](./AX_TO_ALI.svg)

* * * * * * * * * *
## Einleitung
Der **AX_TO_ALI** ist ein zusammengesetzter Funktionsblock (Composite FB), der einen unidirektionalen AX‑Adapter (BOOL) in einen unidirektionalen ALI‑Adapter (LINT) umwandelt. Er wurde entwickelt, um BOOL-Werte, die über einen AX‑Socket empfangen werden, in LINT-Werte zu konvertieren und über einen ALI‑Plug auszugeben. Der Baustein nutzt intern die IEC‑61131‑Konvertierungsfunktion `F_BOOL_TO_LINT`.

## Schnittstellenstruktur
Der AX_TO_ALI besitzt keine direkten Ereignis- oder Dateneingänge/-ausgänge. Die gesamte Kommunikation erfolgt ausschließlich über Adapter.

### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge. Ereignisse werden indirekt über den AX‑Adapter-Socket empfangen.

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge. Ereignisse werden indirekt über den ALI‑Adapter-Plug ausgegeben.

### **Daten-Eingänge**
Keine separaten Daten-Eingänge. Daten werden indirekt über den AX‑Adapter-Socket empfangen.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge. Daten werden indirekt über den ALI‑Adapter-Plug ausgegeben.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `AX_IN` | Socket | `adapter::types::unidirectional::AX` | BOOL-Adapter-Eingang: Empfängt ein BOOL-Signal über den unidirektionalen AX‑Adapter. |
| `ALI_OUT` | Plug | `adapter::types::unidirectional::ALI` | LINT-Adapter-Ausgang: Gibt den konvertierten LINT-Wert über den unidirektionalen ALI‑Adapter aus. |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert und führt bei jedem empfangenen Ereignis über den AX‑Adapter‑Socket folgende Schritte aus:

1. **Ereignisempfang**: Ein Ereignis `E1` des AX‑Adapters wird an den internen Konvertierungsbaustein `F_BOOL_TO_LINT` übermittelt (Ereignis `REQ`).
2. **Datenübernahme**: Der aktuelle BOOL‑Wert `D1` des AX‑Adapters wird an den Eingang `IN` der Konvertierungsfunktion weitergegeben.
3. **Konvertierung**: Der interne Baustein wandelt den BOOL-Wert in einen LINT-Wert um (`FALSE` → `0`, `TRUE` → `1`).
4. **Datenausgabe**: Das konvertierte LINT‑Ergebnis wird über den Datenausgang `OUT` an den Daten-Eingang `D1` des ALI‑Adapters gelegt.
5. **Ereignisausgabe**: Nach erfolgreicher Konvertierung wird ein Bestätigungsereignis `CNF` an den ALI‑Adapter‑Ausgang `E1` gesendet.

Damit wird eine synchrone, ereignisgesteuerte Umsetzung von BOOL in LINT realisiert.

## Technische Besonderheiten
- **Lizenz**: Der Baustein ist unter der **Eclipse Public License 2.0 (EPL‑2.0)** veröffentlicht.  
  Copyright © 2026 HR Agrartechnik GmbH.
- **Autor & Version**: Entwickelt von Franz Höpfinger, Version 1.0, Stand 2026‑02‑17.
- **Adapter‑Paket**: Verwendet Adapter aus dem Paket `adapter::types::unidirectional`, die für eine einseitige Daten‑ und Ereignisübertragung ausgelegt sind.
- **Interne Realisierung**: Die Konvertierung erfolgt über den IEC‑61131‑Baustein `F_BOOL_TO_LINT` aus der Bibliothek `iec61131::conversion`. Dieser Baustein arbeitet deterministisch und benötigt keine Zwischenspeicher.
- **Hash‑Attribut**: Der Baustein enthält ein leeres Typ‑Hash‑Attribut (`eclipse4diac::core::TypeHash`).

## Zustandsübersicht
Der AX_TO_ALI besitzt keinen eigenen Zustandsautomaten. Er leitet Ereignisse und Daten direkt an den internen Konvertierungsbaustein weiter und gibt das Ergebnis ohne Verzögerung aus. Da der interne Baustein `F_BOOL_TO_LINT` eine reine Funktionslogik ohne Zustandshaltung ist, verhält sich der gesamte Composite FB stateless. Nach jedem Ereignis am AX‑Adapter wird sofort die entsprechende Ausgabe am ALI‑Adapter erzeugt.

## Anwendungsszenarien
- **Typkonvertierung in Adapterketten**: Wenn in einer IEC‑61499‑Applikation ein BOOL‑Wert über einen unidirektionalen AX‑Adapter ankommt, aber nachfolgende Bausteine einen LINT‑Wert erwarten (z. B. für Zählfunktionen oder Analogwertverarbeitung).
- **Schnittstellenanpassung**: Anbindung binärer Sensoren (BOOL) an Steuerungslogiken, die mit ganzzahligen LINT‑Werten arbeiten.
- **Ereignisgesteuerte Datenumsetzung**: Einfache und schnelle Umwandlung ohne Zwischenspeicher, ideal für zeitkritische Pfade.

## Vergleich mit ähnlichen Bausteinen
In der Bibliothek `iec61131::conversion` existieren zahlreiche Funktionsbausteine zur Typkonvertierung, z. B. `F_BOOL_TO_DINT`, `F_BOOL_TO_INT` oder `F_BOOL_TO_USINT`. Der AX_TO_ALI unterscheidet sich dadurch, dass er bereits vollständig in eine Adapterhülle eingebettet ist und die Konvertierung zwischen den unidirektionalen Adaptern AX und ALI ermöglicht. Er erspart dem Entwickler die manuelle Verschaltung von Socket/Plug mit einem separaten Konvertierungsbaustein und sorgt für eine saubere, wiederverwendbare Kapselung.

## Fazit
Der AX_TO_ALI ist ein kompakter, lizenzkonformer Composite‑FB zur zuverlässigen Umwandlung eines BOOL‑ in einen LINT‑Wert über unidirektionale Adapter. Durch seine einfache Ereignissteuerung und die Verwendung eines etablierten IEC‑Bausteins bietet er eine robuste Lösung für typische Konvertierungsaufgaben in IEC‑61499‑Systemen. Die saubere Trennung von Ein‑ und Ausgang über Adapter erleichtert die Integration in modulare Steuerungsarchitekturen.