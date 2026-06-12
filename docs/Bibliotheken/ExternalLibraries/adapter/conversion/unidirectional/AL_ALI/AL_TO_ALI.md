# AL_TO_ALI


![AL_TO_ALI](./AL_TO_ALI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AL_TO_ALI` ist ein zusammengesetzter Baustein (Composite FB) zur Umwandlung eines AL-Adapters (LWORD) in einen ALI-Adapter (LINT). Er dient als Schnittstelle zwischen einer LWORD-basierten und einer LINT-basierten Datenkommunikation innerhalb der Steuerungslogik. Der Baustein nutzt intern den Konvertierungsbaustein `F_LWORD_TO_LINT`, um die eigentliche Typumwandlung durchzuführen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Der Baustein besitzt keine eigenständigen Ereignis-Eingänge. Die Ereignissteuerung erfolgt über die angeschlossenen Adapter.*

### **Ereignis-Ausgänge**
*Der Baustein besitzt keine eigenständigen Ereignis-Ausgänge. Die Ereignissteuerung erfolgt über die angeschlossenen Adapter.*

### **Daten-Eingänge**
*Der Baustein besitzt keine eigenständigen Daten-Eingänge. Die Eingangsdaten werden über den Socket `AL_IN` bereitgestellt.*

### **Daten-Ausgänge**
*Der Baustein besitzt keine eigenständigen Daten-Ausgänge. Die Ausgangsdaten werden über den Plug `ALI_OUT` bereitgestellt.*

### **Adapter**

| Typ | Name | Richtung | Datentyp | Beschreibung |
|-----|------|----------|----------|--------------|
| `adapter::types::unidirectional::AL` | `AL_IN` | Socket (Eingang) | LWORD | LWORD-Adapter als Eingangsschnittstelle. Stellt die zu konvertierenden Daten bereit. |
| `adapter::types::unidirectional::ALI` | `ALI_OUT` | Plug (Ausgang) | LINT | LINT-Adapter als Ausgangsschnittstelle. Liefert die konvertierten Daten. |

## Funktionsweise

1. **Ereignisauslösung:** Der `AL_IN`-Adapter gibt über seinen Ereignisausgang `E1` ein Signal, sobald neue Daten anstehen.
2. **Konvertierung:** Dieses Ereignis triggert den internen FB `Convert` (`F_LWORD_TO_LINT`) an seinem Ereigniseingang `REQ`. Gleichzeitig wird der aktuelle Datenwert von `AL_IN.D1` (LWORD) an den Dateneingang `IN` des Konvertierungsbausteins übergeben.
3. **Ausgabe:** Nach erfolgreicher Umwandlung sendet `Convert` eine Bestätigung über seinen Ereignisausgang `CNF` an den `ALI_OUT`-Adapter (Ereigniseingang `E1`). Parallel dazu wird der konvertierte LINT-Wert am Ausgang `OUT` an den Dateneingang `ALI_OUT.D1` weitergeleitet.
4. **Ergebnis:** Der `ALI_OUT`-Adapter gibt nun die neuen LINT-Daten an den angeschlossenen FB weiter.

## Technische Besonderheiten

- **Typkonvertierung:** Der Baustein wandelt einen LWORD (64‑Bit‑Bitfolge) in einen LINT (64‑Bit‑Ganzzahl mit Vorzeichen) um. Die Umwandlung erfolgt bit‑identisch, d.h. die Binärdarstellung wird als vorzeichenbehaftete Ganzzahl interpretiert.
- **Komposition:** Es handelt sich um einen Composite-FB, der keine eigene Logik enthält, sondern auf den standardisierten Konvertierungsbaustein `iec61131::conversion::F_LWORD_TO_LINT` zurückgreift.
- **Adapterbasierte Schnittstelle:** Die Ein‑ und Ausgabe erfolgt ausschließlich über unidirektionale Adapter (`AL` und `ALI`), was eine modulare und typengeprüfte Verbindung in der 4diac‑IDE ermöglicht.
- **Paketstruktur:** Der FB ist im Paket `adapter::conversion::unidirectional` abgelegt.

## Zustandsübersicht

Da es sich um einen Composite‑FB handelt, existiert kein eigener Zustandsautomat. Die Zustandslogik wird vollständig durch den intern genutzten Baustein `F_LWORD_TO_LINT` bestimmt. Dieser arbeitet ereignisgesteuert:

- **IDLE:** Warten auf ein Ereignis am `REQ`-Eingang.
- **PROCESSING:** Umwandlung des LWORD in LINT (dauert einen Schritt).
- **FINISHED:** Ausgabe des konvertierten Werts und Senden des `CNF`-Ereignisses.

## Anwendungsszenarien

- **SPS‑Datenkonvertierung:** Wenn ein Steuerungsprogramm LINT‑Werte (z. B. Zählerstände oder Zeiten) über einen LWORD‑basierten Adapter erhält und eine LINT‑Schnittstelle benötigt wird.
- **Kommunikations‑Adapter:** Einsatz als Zwischenglied in einer Adapterkette, um unterschiedliche Datentypen zwischen verschiedenen Hardware‑ oder Softwaremodulen zu übersetzen.
- **Protokollanpassung:** Beispielsweise Umwandlung von LWORD‑rohdaten (z. B. aus einem Bussystem) in eine LINT‑Repräsentation zur weiteren Verarbeitung in der Steuerungslogik.

## Vergleich mit ähnlichen Bausteinen

- **AL_TO_AL (LWORD ↔ LWORD):** Reine Durchleitung ohne Konvertierung.
- **ALI_TO_AL (LINT ↔ LWORD):** Führt die umgekehrte Konvertierung durch.
- **F_LWORD_TO_LINT (direkter Konvertierungsbaustein):** Bietet die gleiche Funktionalität, jedoch ohne Adapter‑Schnittstelle. `AL_TO_ALI` kapselt diesen Baustein und fügt die Adapter‑Anbindung hinzu.

## Fazit

Der `AL_TO_ALI`-Funktionsblock ist ein einfacher, aber wichtiger Konverter, der die Lücke zwischen LWORD‑basierten und LINT‑basierten Adapter‑Schnittstellen schließt. Durch seine composite‑Struktur bleibt er übersichtlich und kann flexibel in bestehende 4diac‑Projekte integriert werden. Die Verwendung von Standard‑Konvertierungsbausteinen gewährleistet eine korrekte und effiziente Typumwandlung.