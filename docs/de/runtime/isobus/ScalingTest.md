# Scaling-Test (SCALING-TEST)

## Zweck

Der **SCALING-TEST** ist ein Test-Feature im VT-Client (`App_VTClient.c`), mit dem sich die [Skalierung](Scaling.md) der Object Pools, die [Softkey-Reduktion](SoftKeyReduction.md) und der [CCI-Farbfallback](#cci-farbfallback-farbindizes-232-255) gezielt durchtesten lassen, **ohne den Quellcode zu ändern oder neu zu kompilieren**.

Normalerweise werden folgende Werte beim Verbindungsaufbau live vom angeschlossenen Virtual Terminal (VT) abgefragt:

- der **Data-Mask-Skalierungsfaktor** (`PoolDataMaskScalFaktor`)
- der **Softkey-Mask-Skalierungsfaktor** (`PoolSoftKeyMaskScalFaktor`)
- die **Anzahl der physischen Softkeys** (`VT_PHYSICALSOFTKEYS`)
- der **Manufacturer Code** des VT (NAME-Feld aus dem ISO 11783-5-Adressclaim), der entscheidet, ob Farbindizes 232-255 unverändert durchgereicht oder umgemappt werden

Um das Verhalten für unterschiedliche VT-Bildschirmgrößen, Skalierungsfaktoren, Softkey-Anzahlen oder VT-Hersteller zu testen, müsste man bisher einen echten VT mit den entsprechenden Eigenschaften anschließen. Mit dem SCALING-TEST können diese Werte stattdessen über eine Einstellung in `settings.ini` überschrieben werden.

!!! warning "Nur für Testzwecke"
    Der SCALING-TEST ist ein Entwickler-/Testwerkzeug. Er ist standardmäßig **deaktiviert** und darf in Produktivgeräten nicht dauerhaft aktiviert bleiben, da er absichtlich die normale Sicherheitsgrenze für die Skalierung (siehe unten) umgeht.

## Konfiguration über `settings.ini`

Die Datei `settings.ini` liegt je nach Plattform unter:

- `/data/settings.ini` (ESP32-Zielsystem)
- `./settings.ini` (Linux-/Host-Build)

Um den Test zu aktivieren, folgende Sektion einfügen:

```ini
[ScalingTest]
enable = 1
skmScal = 15000
dmScal = 12000
softkeys = 8
```

### Schlüssel

| Schlüssel  | Bedeutung                                              | Gültige Werte                          | Default (wenn nicht gesetzt)          |
|------------|----------------------------------------------------------|-----------------------------------------|----------------------------------------|
| `enable`   | Master-Schalter für den SCALING-TEST                     | `0` = aus, `1` = an                     | `0` (aus, Normalverhalten)              |
| `skmScal`  | Überschreibt den Softkey-Mask-Skalierungsfaktor            | ganzzahliger Faktor, Einheit 1/10000 (`10000` = 100 %, `15000` = 150 %) | der live vom VT gelesene Wert          |
| `dmScal`   | Überschreibt den Data-Mask-Skalierungsfaktor               | wie `skmScal`                            | der live vom VT gelesene Wert          |
| `softkeys` | Überschreibt die Anzahl der physischen Softkeys (`sknu`)  | `6` bis `11`                              | der live vom VT gelesene Wert          |

`skmScal`, `dmScal` und `softkeys` werden **nur ausgewertet, wenn `enable = 1` gesetzt ist**. Fehlt die Sektion `[ScalingTest]` komplett oder ist `enable = 0`, verhält sich der VT-Client exakt wie ohne dieses Feature.

## Besonderheiten

- **111 %-Klemme wird übersprungen**: Im Normalbetrieb wird ein Softkey-Mask-Skalierungsfaktor zwischen 90 % und 111,11 % auf 100 % zurückgesetzt (damit z. B. 80×80- und 72×72-Softkeys nicht unnötig skaliert werden, siehe [Scaling](Scaling.md)). Ist der SCALING-TEST aktiv, wird dieser Schutz bewusst **nicht** angewendet, damit der gesetzte Testwert exakt wie konfiguriert sichtbar wird.
- **Ungültige Softkey-Anzahl wird verworfen**: Die Softkey-Reduktion (siehe [SoftKey Reduction](SoftKeyReduction.md)) unterstützt nur die Werte 6 bis 11. Wird `softkeys` außerhalb dieses Bereichs gesetzt (z. B. `20` oder `3`), wird der Override ignoriert, eine Debug-Meldung ausgegeben und stattdessen der live vom VT abgefragte Wert verwendet.
- **Kein Neustart des Geräts nötig, aber ein VT-Reconnect**: Die Werte werden bei jedem Laden des Object Pools ausgewertet (VT-Verbindungsaufbau bzw. Reconnect). Nach einer Änderung von `settings.ini` muss also die Verbindung zum VT neu aufgebaut werden (oder das Gerät neu gestartet werden), damit die neuen Werte greifen.

## Verifikation / erwartete Debug-Ausgabe

Ist der SCALING-TEST aktiv, erscheint in den Debug-Logs beim Pool-Laden zusätzlich folgende Zeile:

```text
SCALING-TEST active: SKM_Scal=15000 DM_Scal=12000 (111% clamp skipped)
```

gefolgt von den bestehenden Zeilen mit den (nun überschriebenen) Werten:

```text
PoolDataMaskScalFaktor    =  12000
PoolSoftKeyMaskScalFaktor =  15000
```

Wird ein ungültiger Softkey-Override gesetzt (z. B. `softkeys = 20`), erscheint stattdessen:

```text
SCALING-TEST: ignoring out-of-range softkeys override=20 (valid 6..11), using live value=12
```

### Beispielablauf

1. `settings.ini` wie oben beschrieben anpassen.
2. VT-Verbindung neu aufbauen (Gerät neu starten oder VT trennen/verbinden).
3. Debug-Log prüfen (siehe oben).
4. Am angeschlossenen VT visuell prüfen: Data-Mask-Objekte erscheinen mit dem Faktor `dmScal`, Softkey-Mask-Objekte mit dem Faktor `skmScal` skaliert bzw. zentriert; bei `softkeys = 8` werden aus einem für 12 Softkeys ausgelegten Pool nur noch 8 Softkeys angezeigt.
5. Zum Abschluss `enable = 0` setzen (oder die Sektion entfernen), um wieder das normale, live vom VT abgeleitete Verhalten zu erhalten.

## CCI-Farbfallback (Farbindizes 232-255)

### Hintergrund

Nach ISO 11783-6 Annex A ("VT standard colour palette", Table A.4) sind nur die Farbindizes **0-231** als einheitliche Standardpalette garantiert - jedes ISOBUS-VT muss sie identisch rendern. Die Indizes **232-255** sind laut Norm ausdrücklich **"Proprietary"**: wie ein bestimmtes VT sie darstellt, ist herstellerabhängig und nicht festgelegt.

Der Object Pool nutzt an einigen Stellen Farbindizes aus diesem Bereich (z. B. für ein dezentes Zeilen-Grau in Tabellen). Auf einem **CCI-VT** (Competence Center ISOBUS e.V., Manufacturer Code `339`) ist das Aussehen bereits geprüft und gewünscht - dort werden diese Farbwerte **unverändert durchgereicht**. Auf **allen anderen VTs** (z. B. FENDT/AGCO - im Hardware-Test bestätigt abweichend) werden die Farbindizes 232-255 stattdessen über eine **Lookup-Tabelle** auf den jeweils nächstliegenden Standardfarbindex (0-231) umgemappt, bevor der Pool gesendet wird.

Die Erkennung, ob ein CCI-VT angeschlossen ist, läuft automatisch über den Manufacturer Code im NAME-Feld des VT (ISO 11783-5-Adressclaim) - **kein manuelles Eingreifen im Normalbetrieb nötig**. Der SCALING-TEST erlaubt es, dieses Verhalten gezielt zu erzwingen bzw. zu simulieren.

### Umrechnungstabelle (Farbindizes 232-255 → 0-231)

Die Indizes 232-255 bilden im Object Pool eine 24-stufige Graustufen-Rampe (verifiziert in Bucher ISO Designer sowie auf echter CCI- und Bucher-VT-Hardware). Auf einem Nicht-CCI-VT (`forceCCI = 2`, oder automatisch erkannt) wird jeder dieser Werte fest auf den nächstliegenden Standardfarbindex (0-231, per euklidischem RGB-Abstand nach ISO 11783-6 Annex A, Table A.4) abgebildet:

| Farbindex (Pool) | → Standard-Index | Standardfarbe                    |
|-------------------|--------------------|------------------------------------|
| 232, 233           | `0`                | Schwarz (`#000000`)                |
| 234–238             | `59`               | Dunkelgrau (`#333333`)              |
| 239–243             | `102`              | Grau (`#666666`)                    |
| 244–247             | `8`                | Grau (`#999999`)                    |
| 248–252             | `7`                | Silber (`#CCCCCC`)                  |
| 253–255             | `1`                | Weiß (`#FFFFFF`)                    |

Diese Zuordnung gilt für die aktuell im Object Pool tatsächlich genutzten Farbindizes (u. a. das Zeilen-Grau in Tabellen). Wird künftig ein Pool-Objekt mit einer **nicht-grauen** Farbe aus 232-255 angelegt, muss die Zuordnung um diesen Index erweitert werden - sonst erscheint auf Nicht-CCI-VTs stattdessen ein Grauton.

### Schlüssel

| Schlüssel        | Bedeutung                                                                 | Gültige Werte                                                                                                  | Default (wenn nicht gesetzt)     |
|-------------------|----------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|------------------------------------|
| `forceCCI`        | Überschreibt das Ergebnis der CCI-Erkennung                                | `0` = Auto (echte Erkennung über Manufacturer Code), `1` = CCI erzwingen (Farben unverändert), `2` = Nicht-CCI erzwingen (Lookup-Tabelle), `3` = FENDT/AGCO-Simulation (jeder Farbindex 232-255 wird durch `forceCCIColor` ersetzt) | `0` (Auto)                         |
| `manufCode`       | Überschreibt den ausgelesenen Manufacturer Code des VT                     | beliebiger Manufacturer Code, z. B. `339` (CCI) oder `102` (AGCO)                                                  | der live vom VT gelesene Wert      |
| `forceCCIColor`   | Testfarbe für den Modus `forceCCI = 3`                                    | Farbindex `0`-`231`                                                                                                | `0` (Schwarz)                      |

`forceCCI`, `manufCode` und `forceCCIColor` werden **nur ausgewertet, wenn `enable = 1` gesetzt ist** (dieselbe Sektion, derselbe Master-Schalter wie bei den Skalierungs-Optionen oben).

### Beispiel: Nicht-CCI-VT simulieren

```ini
[ScalingTest]
enable = 1
forceCCI = 2
```

### Beispiel: FENDT/AGCO-Simulation mit Signalfarbe

Zeigt jedes Objekt, das eigentlich einen Farbindex 232-255 nutzt, in einer festen Testfarbe an - so lassen sich alle betroffenen Objekte auf einen Blick am Bildschirm erkennen:

```ini
[ScalingTest]
enable = 1
forceCCI = 3
forceCCIColor = 12
```

(Farbindex `12` = Rot; siehe die Standard-Farbtabelle nach ISO 11783-6 Annex A.)

### Verifikation / erwartete Debug-Ausgabe

```text
CCI-Colour: manufCode=339 forceCCI=2 passthrough=0 solidTest=0/0
```

`passthrough=1` bedeutet, dass Farben unverändert durchgereicht werden (CCI erkannt oder `forceCCI = 1`); `passthrough=0`, dass die Lookup-Tabelle angewendet wird.

## Siehe auch

- [Scaling](Scaling.md) — Hintergrund zur Skalierungslogik nach ISO 11783-6
- [SoftKey Reduction](SoftKeyReduction.md) — Hintergrund zur Softkey-Reduktion
