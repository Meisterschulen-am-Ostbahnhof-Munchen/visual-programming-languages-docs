# ASSEMBLE_AD_FROM_AW


![ASSEMBLE_AD_FROM_AW](./ASSEMBLE_AD_FROM_AW.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ASSEMBLE_AD_FROM_AW** dient der Kombination zweier Wort-Werte (WORD) aus je einem unidirektionalen AW‑Adapter zu einem Doppelwort (DWORD), das über einen unidirektionalen AD‑Adapter ausgegeben wird. Der Baustein kapselt die logische Verknüpfung von zwei 16‑Bit‑Eingängen zu einem 32‑Bit‑Ausgang und speichert das Ergebnis über ein flankengesteuertes D‑Flipflop zwischen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine direkt sichtbaren Ereignis-Eingänge. Die Ereignissteuerung erfolgt indirekt über die eingehenden Adapter **WORD_00** und **WORD_01**: Jeder dieser Adapter liefert über seinen impliziten Ereignisausgang (`E1`) ein Signal, das den internen Verarbeitungsablauf anstößt.

### **Ereignis-Ausgänge**
Auch hier existieren keine direkten Ereignis-Ausgänge. Der Ausgangsadapter **OUT** stellt über seinen impliziten Ereigniseingang (`E1`) das Ausgangsereignis zur Verfügung, das nach Abschluss der Verarbeitung und Übernahme des Datenwertes ausgelöst wird.

### **Daten-Eingänge**
Die Daten werden über die beiden Socket-Adapter eingelesen:
| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| `WORD_00` | `adapter::types::unidirectional::AW` | Erstes 16‑Bit‑Wort (niederwertiger Anteil des Doppelworts) |
| `WORD_01` | `adapter::types::unidirectional::AW` | Zweites 16‑Bit‑Wort (höherwertiger Anteil des Doppelworts) |

Jeder dieser Adapter stellt einen Datenausgang (`D1`) mit dem eigentlichen WORD‑Wert bereit.

### **Daten-Ausgänge**
Der Ausgang erfolgt über einen Plug-Adapter:
| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| `OUT` | `adapter::types::unidirectional::AD` | Zusammengesetztes 32‑Bit‑Doppelwort (DWORD) |

Der Adapter `OUT` besitzt einen Dateneingang (`D1`), der intern mit dem gespeicherten Ergebnis verbunden ist.

### **Adapter**
Der FB stellt zwei eingehende Adapter (Socket) und einen ausgehenden Adapter (Plug) zur Verfügung, die alle vom Typ *unidirectional* sind:
- **WORD_00**, **WORD_01**: Liefern jeweils ein WORD und ein zugehöriges Ereignis.
- **OUT**: Nimmt ein DWORD entgegen und gibt es mit einem Ereignis weiter.

## Funktionsweise
1. Sobald eines der beiden Eingangsereignisse (`WORD_00.E1` oder `WORD_01.E1`) eintrifft, wird der interne Funktionsblock `ASSEMBLE_DWORD_FROM_WORDS` über seinen Ereigniseingang `REQ` aktiviert.
2. Dieser interne Baustein setzt aus den beiden eingehenden 16‑Bit‑Werten (`WORD_00.D1` und `WORD_01.D1`) das 32‑Bit‑Doppelwort zusammen. Dabei wird `WORD_00` als niederwertiges und `WORD_01` als höherwertiges Wort interpretiert.
3. Nach Abschluss der Berechnung signalisiert `ASSEMBLE_DWORD_FROM_WORDS` mit dem Ereignis `CNF` den Takt eines flankengesteuerten D‑Flipflops (`E_D_FF_ANY`).
4. Das Flipflop übernimmt den berechneten DWORD‑Wert an seinem Dateneingang `D` und gibt ihn an seinem Ausgang `Q` weiter.
5. Der gespeicherte Wert wird über die Datenverbindung an den Adapter `OUT.D1` geleitet. Gleichzeitig wird über das Ausgangsereignis des Flipflops (`EO`) der Adapter‑Ereigniseingang `OUT.E1` bedient.

Auf diese Weise wird sichergestellt, dass der Ausgangswert nur bei tatsächlichen Änderungen oder gültigen neuen Eingängen aktualisiert wird und bis zum nächsten Ereignis stabil bleibt.

## Technische Besonderheiten
- Der Baustein verwendet einen internen Funktionsblock (`ASSEMBLE_DWORD_FROM_WORDS`) zur reinen Wort‑Kombination und ein flankengesteuertes D‑Flipflop (`E_D_FF_ANY`) zur Ausgangsspeicherung.
- Die Ereignisverarbeitung erfolgt asynchron: Jedes eingehende Ereignis an einem der beiden AW‑Adapter löst eine neue Berechnung und eine anschließende Ausgabe aus. Es wird kein Zustand der Eingangsereignisse gespeichert – das Flipflop übernimmt immer den zuletzt berechneten DWORD.
- Die Zusammensetzung der Wörter erfolgt hardwarenah: WORD_00 = niederwertiges 16‑Bit‑Wort (Bits 0‑15), WORD_01 = höherwertiges 16‑Bit‑Wort (Bits 16‑31).

## Zustandsübersicht
Der FB selbst besitzt keinen expliziten Zustandsautomaten. Der interne Ablauf lässt sich aber durch die Zustände des D‑Flipflops charakterisieren:
| Zustand | Beschreibung |
|---------|--------------|
| **Warten auf Ereignis** | Das Flipflop hält den zuletzt berechneten Wert; es liegt kein neues Eingangsereignis an. |
| **Berechnung aktiv** | Ein Ereignis von WORD_00 oder WORD_01 triggert die Zusammenführung und das Flipflop wird getaktet. |
| **Ausgabe aktiv** | Nach dem Takt wird der neue Wert an `OUT` weitergegeben und das Ausgangsereignis wird gesendet. |

Der Wechsel der Zustände erfolgt streng durch die Ereigniskette.

## Anwendungsszenarien
- **Datenformat‑Wandlung**: Zusammenführen zweier 16‑Bit‑Sensorwerte (z. B. aus zwei getrennten Analog‑Eingabemodulen) zu einem 32‑Bit‑Datenwort für eine übergeordnete Steuerung.
- **Adapter‑Integration**: Einbinden von AW‑basierten Komponenten (z. B. Wort‑Adapter von Bussystemen) in Systeme, die einen AD‑Adapter (DWORD) erwarten.
- **Schnittstellenanpassung**: Vereinfachung der Verdrahtung, wenn zwei logisch zusammengehörige 16‑Bit‑Kanäle zu einem Doppelwort zusammengefasst werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **ASSEMBLE_DWORD_FROM_WORDS** (interner FB): Bietet die gleiche Datenzusammenführung, jedoch ohne Adapter‑Schnittstellen und ohne Ausgangsspeicherung. `ASSEMBLE_AD_FROM_AW` erweitert diesen um die Adapter‑Kapselung und das D‑Flipflop.
- **SPLIT_AD_TO_AW**: Führt die umgekehrte Operation (Aufteilen eines DWORD in zwei Wörter) aus und stellt die Werte über AW‑Adapter bereit.
- **MUX_WORDS_TO_DWORD**: Ein alternativer Baustein zur Wort‑Kombination, der meist ohne Adapter und ohne flankengesteuerte Speicherung auskommt.

## Fazit
`ASSEMBLE_AD_FROM_AW` ist ein spezialisierter Funktionsblock zur sauberen Kapselung der Wort‑zu‑Doppelwort‑Konvertierung in einer Adapter‑basierten Umgebung. Die Kombination aus reinem Rechenwerk und flankengesteuerter Speicherung gewährleistet stabile Ausgangswerte bei wechselnden Eingangsereignissen. Der Baustein eignet sich besonders für modulare Automatisierungslösungen, die auf unidirektionale Adapter‑Schnittstellen setzen.