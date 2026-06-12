# AUI_CTU


![AUI_CTU](./AUI_CTU.svg)

*Bild des Funktionsblocks nicht verfügbar*

* * * * * * * * * *
## Einleitung

Der AUI_CTU ist ein ereignisgesteuerter Aufwärtszähler mit Adapterschnittstelle. Er zählt bei jedem positiven Flankenereignis am Eingang `CU` hoch und gibt das Zählergebnis über den Adapter `CV` aus. Die Ausgabe `Q` signalisiert, ob der Zählerstand (`CV`) den eingestellten Grenzwert (`PV`) erreicht oder überschritten hat. Das Besondere an dieser Implementierung ist die „On-Change“-Triggerung: Das Ereignis am Adapter `Q.E1` wird nur dann ausgelöst, wenn sich der logische Zustand von `Q` tatsächlich ändert. Dies reduziert unnötige Ereignisse in der nachfolgenden Verarbeitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CU` | Event | Zähle hoch (Count Up) |
| `R`  | Event | Setze den Zähler zurück (Reset) |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CUO` | Event | Ausgabe nach erfolgreichem Hochzählen |
| `RO` | Event | Ausgabe nach erfolgreichem Rücksetzen |

### **Daten-Eingänge**

Direkte Daten-Eingänge sind nicht vorhanden. Der Grenzwert (`PV`) wird über einen Adapter-Socket bereitgestellt.

### **Daten-Ausgänge**

Direkte Daten-Ausgänge sind nicht vorhanden. Der aktuelle Zählerwert (`CV`) und der Vergleichsstatus (`Q`) werden über Adapter-Plugs ausgegeben.

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AX` | Plug (Ausgang) | `Q` | Gibt `TRUE` aus, wenn `CV >= PV`, sonst `FALSE`. Das Ereignis `Q.E1` wird nur bei Zustandsänderung gesendet. |
| `adapter::types::unidirectional::AUI` | Plug (Ausgang) | `CV` | Liefert den aktuellen Zählerwert (vorzeichenloser Ganzzahl). Das Ereignis `CV.E1` wird nach jedem Hochzählen oder Rücksetzen ausgelöst. |
| `adapter::types::unidirectional::AUI` | Socket (Eingang) | `PV` | Empfängt den Schwellwert (Grenzwert) vom Typ `UINT`. Eine Änderung dieses Wertes führt automatisch zur Neuberechnung von `Q`. |

## Funktionsweise

Der Baustein implementiert eine endliche Zustandsmaschine (ECC) mit folgenden Algorithmen:

- **`CU`**: Erhöht den internen Zähler `CV` um `1` und berechnet anschließend: `Q := (CV >= PV)`.
- **`R`**: Setzt `CV` auf `0` und berechnet `Q` erneut.
- **`UPDATE`**: Berechnet `Q` aus dem aktuellen `CV` und dem (geänderten) `PV`, ohne den Zähler zu verändern.
- **`SAVE_Q`**: Speichert den aktuellen Wert von `Q` in der internen Variable `Q_OLD` für die nächste Zustandsänderungserkennung.

Ablauf:

1. **Ereignis `CU`** (und `CV < 65535`): Übergang in Zustand `CU`. Es wird der Zähler inkrementiert, `Q` neu berechnet und `CV.E1` sowie das Ereignis `CUO` ausgegeben.  
   - Wenn sich `Q` gegenüber dem letztgespeicherten Wert (`Q_OLD`) geändert hat, wechselt der Zustand nach `EMIT_Q`.  
   - Andernfalls kehrt der Baustein in den Zustand `START` zurück.

2. **Ereignis `R`**: Übergang in Zustand `R`. Der Zähler wird zurückgesetzt, `Q` neu berechnet und `CV.E1` sowie `RO` ausgegeben. Anschließend wird analog zu `CU` entschieden, ob `EMIT_Q` erreicht wird oder zurück nach `START`.

3. **Ereignis des Adapters `PV.E1`** (Grenzwertänderung): Übergang in Zustand `UPDATE_PV`. Der Algorithmus `UPDATE` berechnet `Q` neu. Auch hier wird nur bei Änderung von `Q` der Zustand `EMIT_Q` durchlaufen.

4. **Zustand `EMIT_Q`**: Führt den Algorithmus `SAVE_Q` aus (speichert neuen `Q`-Wert in `Q_OLD`) und sendet das Ereignis `Q.E1`. Danach kehrt der Baustein immer in `START` zurück.

## Technische Besonderheiten

- **On-Change-Triggerung für Adapter `Q`**: Das Ereignis `Q.E1` wird nur dann ausgelöst, wenn sich der logische Wert von `Q` (wahr/falsch) ändert. Dies wird durch die interne Statusvariable `Q_OLD` realisiert. Dadurch entfallen unnötige Ereignisüberflutungen in der Applikation.
- **Automatische Reaktion auf Grenzwertänderung**: Ändert sich der über den Socket `PV` zugeführte Schwellwert, wird `Q` sofort neu berechnet und bei Änderung ausgegeben. Der Zähler selbst bleibt dabei unberührt.
- **Überlaufschutz**: Der Zähler wird nur inkrementiert, wenn `CV` kleiner als 65535 ist (maximaler Wert eines `UINT`). Ein weiteres Hochzählen über diesen Wert hinaus ist nicht möglich.
- **Adapterbasiert**: Statt klassischer direkter Ein-/Ausgänge werden alle Werte über standardisierte Adapter ausgetauscht. Dies ermöglicht eine einfache Integration in bestehende 4diac-Adapterkonzepte.

## Zustandsübersicht

| Zustand | Beschreibung | Aktionen | Ausgehende Transitionen |
|---------|--------------|----------|-------------------------|
| `START` | Ruhezustand, wartet auf Ereignisse | – | `CU` → `CU`, `R` → `R`, `PV.E1` → `UPDATE_PV` |
| `CU` | Hochzählen | `CU`-Algorithmus, sende `CV.E1` und `CUO` | `[Q != Q_OLD]` → `EMIT_Q`, `[Q == Q_OLD]` → `START` |
| `R` | Rücksetzen | `R`-Algorithmus, sende `CV.E1` und `RO` | `[Q != Q_OLD]` → `EMIT_Q`, `[Q == Q_OLD]` → `START` |
| `UPDATE_PV` | Neuberechnung nach PV-Änderung | `UPDATE`-Algorithmus | `[Q != Q_OLD]` → `EMIT_Q`, `[Q == Q_OLD]` → `START` |
| `EMIT_Q` | Emission des Q-Ereignisses | `SAVE_Q`-Algorithmus, sende `Q.E1` | 1 → `START` |

Die Transitionen sind durch Bedingungen ausgelöst:  
- `CU[CV.D1 < 65535]`: Ereignis CU, wenn Zähler nicht am Maximum.  
- `R`: Ereignis R, immer möglich.  
- `PV.E1`: Ereignis vom Adapter PV.  
- `[Q.D1 <> Q_OLD]` / `[Q.D1 = Q_OLD]`: Vergleich des aktuellen Q mit dem gespeicherten vorherigen Wert.

## Anwendungsszenarien

- **Ereigniszähler mit Schwellwertüberwachung**: Zählen von Impulsen (z. B. Werkstücke auf einem Förderband) und Auslösen einer Aktion, sobald ein bestimmter Grenzwert erreicht ist.
- **Pegelüberwachung**: Verwendung als Grenzwertschalter, der bei Überschreiten eines Sollwerts einen Status weitergibt.
- **Zustandsabhängige Steuerungen**: Z. B. in einer Batch-Verarbeitung, bei der nach einer bestimmten Anzahl von Schritten ein Prozessschritt ausgelöst werden soll.
- **Systeme mit dynamischem Grenzwert**: Der Grenzwert kann während des Betriebs über den Adapter `PV` geändert werden, der Baustein reagiert automatisch.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | `AUI_CTU` | Standard `CTU` (IEC 61131-3) | `CTUD` (Auf-/Abwärtszähler) |
|---------|-----------|------------------------------|------------------------------|
| Schnittstelle | Adapter-basiert | Direkte Ein-/Ausgänge | Direkte Ein-/Ausgänge |
| Ereignis bei Q-Änderung | Ja (On-Change) | Nein (immer bei Zählereignis) | Nein |
| Reaktion auf PV-Änderung | Automatisch | Nicht vorgesehen | Nicht vorgesehen |
| Überlaufschutz | Ja (max. 65535) | Ja, über Konfiguration | Ja |
| Abwärtszählen | Nein | Nein | Ja |

Der `AUI_CTU` ist speziell für ereignisgesteuerte Systeme mit Adapterkonzept optimiert. Die On-Change-Triggerung und die automatische PV-Neuberechnung sind markante Unterschiede zu klassischen Zählern.

## Fazit

Der `AUI_CTU` ist ein moderner, adapterbasierter Aufwärtszähler, der sich durch seine effiziente Ereignisbehandlung auszeichnet. Dank der On-Change-Triggerung für den Status `Q` werden unnötige Nachrichten im System vermieden. Die Unterstützung dynamischer Grenzwerte über den Adapter `PV` erhöht die Flexibilität in Steuerungsanwendungen. Der Baustein ist robust gegen Überläufe und bietet eine klare, zustandsgesteuerte Ablaufstruktur. Er eignet sich besonders für verteilte Automatisierungssysteme, bei denen lose Kopplung und ereignisgesteuerte Kommunikation im Vordergrund stehen.