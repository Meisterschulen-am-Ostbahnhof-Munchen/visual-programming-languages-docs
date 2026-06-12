# SPLIT_AD_INTO_AB


![SPLIT_AD_INTO_AB](./SPLIT_AD_INTO_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SPLIT_AD_INTO_AB** dient der Aufteilung eines 32‑Bit-Datenworts (AD‑Adapter) in vier einzelne Bytes. Die vier Bytes werden über jeweils separate unidirektionale AB‑Adapter ausgegeben. Der Baustein ist als Composite‑FB realisiert und nutzt dazu einen SPLIT_DWORD_INTO_BYTES sowie mehrere flankengesteuerte D‑Flipflops (E_D_FF_ANY).

## Schnittstellenstruktur
Der FB besitzt keine klassischen Ereignis‑ oder Datenschnittstellen. Die gesamte Kommunikation erfolgt über Adapter:

### **Adapter (Sockets)**
| Adapter | Typ | Kommentar |
|---------|-----|------------|
| IN | `adapter::types::unidirectional::AD` | DWORD‑Eingang (32‑Bit) |

### **Adapter (Plugs)**
| Adapter | Typ | Kommentar |
|---------|-----|------------|
| BYTE_00 | `adapter::types::unidirectional::AB` | Byte 0 (niederwertigstes Byte) |
| BYTE_01 | `adapter::types::unidirectional::AB` | Byte 1 |
| BYTE_02 | `adapter::types::unidirectional::AB` | Byte 2 |
| BYTE_03 | `adapter::types::unidirectional::AB` | Byte 3 (höchstwertiges Byte) |

Jeder AB‑Adapter besitzt mindestens einen Ereignisausgang (E1) und einen Datenausgang (D1), die mit den internen Flipflops verbunden sind.

## Funktionsweise
1. Ein Ereignis am **IN**‑Adapter (E1) triggert den internen Baustein `SPLIT_DWORD_INTO_BYTES`.
2. `SPLIT_DWORD_INTO_BYTES` zerlegt den am **IN.D1** anliegenden DWORD in vier einzelne Bytes (BYTE_00 bis BYTE_03) und gibt sie als Daten aus.
3. Gleichzeitig erzeugt `SPLIT_DWORD_INTO_BYTES` ein Bestätigungsereignis (CNF), das an die Takteingänge (CLK) aller vier `E_D_FF_ANY`‑Flipflops weitergeleitet wird.
4. Jedes Flipflop speichert das ihm zugewiesene Byte (D‑Eingang) bei der steigenden Flanke des Taktes und gibt es an seinem Ausgang (Q) aus.
5. Die Ausgänge der Flipflops sind mit den Datenausgängen der AB‑Adapter (D1) verbunden. Gleichzeitig wird das Ereignis (EO) jedes Flipflops an den Ereigniseingang (E1) des entsprechenden Adapters gesendet, sodass der angeschlossene Consumer über die neuen Daten informiert wird.

## Technische Besonderheiten
- **Synchrone Ausgabe**: Alle vier Bytes werden gleichzeitig mit demselben Ereignis (CNF von `SPLIT_DWORD_INTO_BYTES`) ausgegeben. Dadurch bleiben die Konsumenten der einzelnen Bytes stets synchron.
- **Verwendung von E_D_FF_ANY**: Diese flankengesteuerten Flipflops sorgen dafür, dass die Daten erst bei einem neuen Ereignis übernommen werden und bis dahin stabil am Ausgang anliegen.
- **Adapter‑Basierte Schnittstelle**: Der Baustein arbeitet vollständig über Adapter, wodurch er sich nahtlos in eine adapterorientierte Architektur einfügt (z.B. bei Verwendung von `adapter::types::unidirectional::AB` und `AD`).

## Zustandsübersicht
Der FB selbst besitzt keinen expliziten Zustandsautomaten – er ist ein Composite aus Standard‑Funktionsblöcken. Die interne Ablaufsteuerung erfolgt durch die Ereignis‑ und Datenflüsse:
- **Warten**: Kein Eingangsereignis → Ausgabe bleibt unverändert.
- **Aufteilen**: Bei einem Ereignis am IN‑Adapter wird einmalig der DWORD aufgeteilt und alle vier Bytes ausgegeben.

## Anwendungsszenarien
- **Zerlegung von 32‑Bit‑Sensordaten** (z.B. Encoder‑Werte, AD‑Wandler) in einzelne Bytes für die Übertragung über Byte‑orientierte Protokolle.
- **Ansteuerung von Peripherie**, die einzelne Bytes als Adress‑ oder Datenwörter erwartet (z.B. Registerzugriffe).
- **Datensammlung in verteilten Systemen**, bei der ein 32‑Bit‑Wert auf mehrere unabhängige Verarbeiter aufgeteilt werden muss.

## Vergleich mit ähnlichen Bausteinen
- **SPLIT_DWORD_INTO_BYTES**: Zerlegt einen DWORD ebenfalls in Bytes, gibt diese jedoch direkt als Daten‑Ausgänge (BYTE_00..BYTE_03) aus, ohne die Daten über Adapter zu leiten.
- **SPLIT_AD_INTO_AB**: Bietet die gleiche Funktionalität, kapselt die Ausgabe jedoch in unidirektionale AB‑Adapter. Dies ermöglicht eine saubere Trennung der Schnittstellen und erleichtert die Wiederverwendung in verschiedenen Kontexten.
- **AT** (Adapter‑Typ‑basierte Bausteine): Andere Adapter‑Splitter könnten z.B. WORDs in Nibbles aufteilen, während dieser FB speziell auf DWORD → 4×BYTE ausgelegt ist.

## Fazit
Der **SPLIT_AD_INTO_AB** ist ein nützlicher Composite‑FB, der einen 32‑Bit‑Datenwert synchron und adapterbasiert in vier einzelne Bytes aufspaltet. Durch die Verwendung flankengesteuerter Flipflops bleiben die Ausgänge stabil, bis das nächste Eingangsereignis eintrifft. Die Adapter‑Schnittstellen integrieren sich nahtlos in modulare Echtzeitsysteme nach IEC 61499 und erleichtern die strukturierte Datenweitergabe.