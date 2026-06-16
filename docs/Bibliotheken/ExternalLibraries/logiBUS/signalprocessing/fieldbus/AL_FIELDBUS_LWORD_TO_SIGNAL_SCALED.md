# AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED


![AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED](./AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED` dient der Umwandlung eines Feldbus-Signals (LWORD) in einen skalierten und mit Offset versehenen Wert. Dabei wird nur dann ein gültiges Ausgangssignal erzeugt, wenn das Eingangssignal als gültig markiert ist. Die Gültigkeit wird über ein internes D-Flipflop stabil gehalten und als boolesches Signal ausgegeben.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ   | Kommentar |
|------|-------|-----------|
| INIT | EInit | Init-Anforderung |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar |
|-------|-------|-----------|
| INITO | EInit | Init-Bestätigung |

### **Daten-Eingänge**

| Name   | Typ   | Anfangswert | Kommentar                    |
|--------|-------|-------------|------------------------------|
| SCALE  | LREAL | 1.0         | Skalierungsfaktor            |
| OFFSET | DINT  | 0           | Nach der Skalierung addierter Offset |

### **Adapter**

| Typ  | Richtung | Name  | Kommentar                |
|------|----------|-------|--------------------------|
| AL   | Socket   | IN    | Eingangssignal (LWORD)   |
| ALR  | Plug     | OUT   | Ausgangssignal (skaliert)|
| AX   | Plug     | VALID | Signal gültig (TRUE/FALSE)|

## Funktionsweise
Der FB enthält intern zwei Komponenten:
- **FIELDBUS_LWORD_TO_SIGNAL_SCALED**: Führt die eigentliche Umrechnung des LWORD-Eingangs mithilfe der Parameter SCALE und OFFSET durch. Bei einem Ereignis an `IN.E1` (verbunden mit `REQ`) wird der verarbeitete Wert auf `OUT` und das Gültigkeitssignal auf `VALID` gesetzt.
- **E_D_FF**: Ein flankengesteuertes D-Flipflop, das das Gültigkeitssignal aus dem vorherigen Baustein übernimmt. Der Takt (`CLK`) wird durch das Bestätigungsereignis (`CNF`) des ersten Bausteins ausgelöst. Der Ausgang `Q` wird auf den Adapter `VALID.D1` geschrieben.

Somit ergibt sich folgende Ablaufkette:
1. Ein eingehendes Ereignis an `IN.E1` startet die Verarbeitung.
2. Der interne Baustein berechnet den skalierten Wert und gibt das Gültigkeitssignal aus.
3. Das Flipflop stabilisiert dieses Signal und gibt es an den `VALID`-Adapter weiter.
4. Gleichzeitig wird der skalierte Wert über den `OUT`-Adapter ausgegeben.

Die INIT-Schnittstelle dient der Initialisierung und wird direkt durchgeschliffen.

## Technische Besonderheiten
- Die INIT- und INITO-Verbindungen sind im Netzwerk als unsichtbar markiert, sie existieren jedoch für eine saubere Initialisierungskaskade.
- Skalierung und Offset werden intern an den unterlagerten FB weitergeleitet und sind direkt konfigurierbar.
- Das D-Flipflop verhindert unerwünschte Flanken oder kurzzeitige Invaliditätsänderungen am Ausgang.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine (ECC). Sein Verhalten wird durch die Ereignisverarbeitung gesteuert:
- **Nach INIT**: Der FB ist bereit, Ereignisse an `IN.E1` zu empfangen.
- **Nach jedem REQ/CNF-Zyklus**: Ein neuer skalierten Wert und ein aktualisiertes Gültigkeitssignal liegen an den Adaptern an.

## Anwendungsszenarien
Typische Einsatzbereiche sind:
- Umwandlung von Feldbus-Rohdaten (z. B. LWORD aus PROFIBUS, CAN etc.) in physikalische Größen (Temperatur, Druck, Drehzahl) mit benutzerdefinierter Skalierung.
- Weiterleitung von Sensordaten, bei denen nur als gültig markierte Werte an die nachfolgende Logik übergeben werden sollen.
- Integration in Anlagensteuerungen, die eine saubere Initialisierungsreihenfolge (über INIT) erfordern.

## Vergleich mit ähnlichen Bausteinen
Einfachere Bausteine zur LWORD-Konvertierung bieten oft keine integrierte Gültigkeitsprüfung und geben das Signal direkt aus. `AL_FIELDBUS_LWORD_TO_SIGNAL_SCALED` ergänzt diese Funktionalität um:
- Ein separates Gültigkeitssignal, flankengesteuert über D-Flipflop.
- Explizite Initialisierungsschnittstelle.
Die Kombination von Skalierung, Offset und Gültigkeitslatch hebt ihn von reinen Umrechnungsbausteinen ab.

## Fazit
Dieser Funktionsblock stellt eine robuste Lösung für die Aufbereitung von Feldbus-Signalen dar. Er kombiniert Skalierung, Offset-Verschiebung und eine zuverlässige Gültigkeitsanzeige in einem kompakten, initialisierbaren Baustein. Durch die Verwendung eines D-Flipflops wird die Signalqualität stabilisiert, was insbesondere in sicherheitskritischen oder rauschbehafteten Umgebungen von Vorteil ist.