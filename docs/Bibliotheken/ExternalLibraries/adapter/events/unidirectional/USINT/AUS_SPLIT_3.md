# AUS_SPLIT_3


![AUS_SPLIT_3](./AUS_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUS_SPLIT_3** dient als universeller Verteiler für eingehende Adapter-Signale vom Typ `adapter::types::unidirectional::AUS`. Er nimmt ein solches Signal entgegen und leitet es unverändert an drei baugleiche Ausgangsadapter weiter. Dadurch lassen sich Steuerungs-, Alarm- oder Statusinformationen einfach auf mehrere nachfolgende Bausteine aufteilen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine – die Signalweitergabe erfolgt über den Adapter-IN.

### **Ereignis-Ausgänge**
Keine – die Ausgabe erfolgt über die Adapter-OUTs.

### **Daten-Eingänge**
Keine – der Baustein besitzt keine dedizierten Dateneingänge; alle Daten werden über den Adapter `IN` transportiert.

### **Daten-Ausgänge**
Keine – die Daten werden über die Adapter `OUT1`, `OUT2`, `OUT3` ausgegeben.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::AUS` | Socket (eingehend) | Empfängt ein AUS-Signal. |
| `OUT1` | `adapter::types::unidirectional::AUS` | Plug (ausgehend) | Erste Ausgabe des eingehenden Signals. |
| `OUT2` | `adapter::types::unidirectional::AUS` | Plug (ausgehend) | Zweite Ausgabe des eingehenden Signals. |
| `OUT3` | `adapter::types::unidirectional::AUS` | Plug (ausgehend) | Dritte Ausgabe des eingehenden Signals. |

## Funktionsweise
Der FB arbeitet als reiner Signalverteiler. Sobald ein am Socket `IN` anliegendes AUS-Signal (bestehend aus Ereignis und zugehörigen Daten) aktiv wird, wird es ohne Verzögerung oder Umformung identisch an alle drei Plugs `OUT1`, `OUT2` und `OUT3` weitergegeben. Jeder Ausgang empfängt dabei dasselbe Ereignis und dieselben Daten. Es findet keine Pufferung, Filterung oder logische Verarbeitung statt.

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein ist als generischer FB deklariert (`eclipse4diac::core::GenericClassName` = `'GEN_AUS_SPLIT'`). Dadurch kann er an unterschiedliche AUS-Adapter-Typen angepasst werden, sofern diese die gleiche Schnittstellenstruktur aufweisen.
- **Zustandslos**: Der FB besitzt kein internes Zustandsdiagramm (ECC). Seine Reaktion ist rein datenflussgetrieben und benötigt keine Initialisierung oder Resetlogik.
- **Lizenzhinweis**: Der Baustein wird unter der Eclipse Public License 2.0 bereitgestellt.

## Zustandsübersicht
Da **AUS_SPLIT_3** über keine Ablaufsteuerung oder explizite Zustände verfügt, entfällt eine Zustandsmaschine. Das Verhalten ist deterministisch und sofort: Ein Eingangssignal erzeugt synchron drei identische Ausgangssignale.

## Anwendungsszenarien
- **Verteilung von Alarmsignalen** an mehrere Anzeige‑ oder Logikeinheiten.
- **Mehrfachnutzung eines Sensorsignals** in verschiedenen Automatisierungszweigen.
- **Aufteilung eines Steuerbefehls** (z. B. „Stillsetzen“) auf mehrere Aktoren oder Subsysteme.
- **Signalkaskadierung** in modularen 4diac-Applikationen.

## Vergleich mit ähnlichen Bausteinen
- **EVENT_SPLIT**: Verteilt nur Ereignisse (ohne Daten). **AUS_SPLIT_3** verteilt dagegen komplette Adapter-Signale inklusive aller assoziierten Daten.
- **DATA_SPLIT**: Verteilt reine Datenkanäle, erfordert separate Ereignissteuerung. Der AUS-Splitter kapselt Ereignis und Daten gemeinsam im Adapter.
- **Manuelle Implementierung**: Ohne diesen Baustein müsste jeder Ausgang mit einer eigenen Kopie des Quelladapters verbunden werden. **AUS_SPLIT_3** vereinfacht die Verdrahtung und erhöht die Übersichtlichkeit.

## Fazit
Der **AUS_SPLIT_3** ist ein einfacher aber nützlicher Funktionsblock zur Vervielfachung von AUS‑Adapter-Signalen. Aufgrund seiner generischen Auslegung und Zustandslosigkeit eignet er sich hervorragend für die modulare und wartungsfreundliche Strukturierung von 4diac-Anwendungen.