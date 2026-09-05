# Scaling-Test (SCALING-TEST)

## Zweck

Der **SCALING-TEST** ist ein Test-Feature im VT-Client (`App_VTClient.c`), mit dem sich die [Skalierung](Scaling.md) der Object Pools und die [Softkey-Reduktion](SoftKeyReduction.md) gezielt durchtesten lassen, **ohne den Quellcode zu ändern oder neu zu kompilieren**.

Normalerweise werden folgende Werte beim Verbindungsaufbau live vom angeschlossenen Virtual Terminal (VT) abgefragt:

- der **Data-Mask-Skalierungsfaktor** (`PoolDataMaskScalFaktor`)
- der **Softkey-Mask-Skalierungsfaktor** (`PoolSoftKeyMaskScalFaktor`)
- die **Anzahl der physischen Softkeys** (`VT_PHYSICALSOFTKEYS`)

Um das Verhalten für unterschiedliche VT-Bildschirmgrößen, Skalierungsfaktoren oder Softkey-Anzahlen zu testen, müsste man bisher einen echten VT mit den entsprechenden Eigenschaften anschließen. Mit dem SCALING-TEST können diese drei Werte stattdessen über eine Einstellung in `settings.ini` überschrieben werden.

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

## Siehe auch

- [Scaling](Scaling.md) — Hintergrund zur Skalierungslogik nach ISO 11783-6
- [SoftKey Reduction](SoftKeyReduction.md) — Hintergrund zur Softkey-Reduktion
