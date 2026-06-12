# ASSEMBLE_AD_FROM_AQ


![ASSEMBLE_AD_FROM_AQ](./ASSEMBLE_AD_FROM_AQ.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ASSEMBLE_AD_FROM_AQ` dient dazu, sechzehn separate `AQ`-Adapter (Quarter) zu einem einzigen `AD`-Ausgangsadapter (DWORD) zusammenzusetzen. Die Bezeichnung "Quarter" deutet darauf hin, dass jeder `AQ`-Adapter einen Teil eines 32‑Bit-Wortes repräsentiert – konkret ein Byte (8 Bit). Der Baustein fasst diese 16 Bytes zu einem vollständigen DWORD zusammen und stellt es über einen `AD`-Plug bereit. Er eignet sich vor allem für Anwendungen, bei denen Daten in kleineren Einheiten eintreffen und erst auf der Empfängerseite zu einem größeren Datentyp vereinigt werden müssen.

## Schnittstellenstruktur

Der Funktionsblock besitzt keine eigenständigen Ereignis- oder Dateneingänge/-ausgänge. Die gesamte Ein- und Ausgabe erfolgt ausschließlich über Adapter.

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|------|-------------|
| **Sockets** (Eingänge) | QUARTER_BYTE_00 … QUARTER_BYTE_15 | `adapter::types::unidirectional::AQ` | 16 identische Adapter, die jeweils einen 8‑Bit-Datenwert (Quarter/Byte) sowie ein zugehöriges Ereignis (`E1`) liefern. |
| **Plug** (Ausgang) | OUT | `adapter::types::unidirectional::AD` | Ausgangsadapter, der das aus den 16 Quarter-Werten zusammengesetzte DWORD (`D1`) und ein Ereignis (`E1`) bereitstellt. |

## Funktionsweise

Der Baustein arbeitet vollständig ereignisgesteuert:

1. Sobald einer der 16 `QUARTER_BYTE`-Sockets ein Ereignis (`E1`) empfängt, wird dieses an den internen Funktionsblock `ASSEMBLE_DWORD_FROM_QUARTERS` (Typ `eclipse4diac::utils::assembling::ASSEMBLE_DWORD_FROM_QUARTERS`) weitergeleitet.
2. Der interne Baustein kombiniert die aktuellen Daten aller 16 Quarter-Werte zu einem 32‑Bit-DWORD (bit‑0…7 = Quarter 0, bit‑8…15 = Quarter 1, … bit‑120…127 = Quarter 15).
3. Das Ergebnis wird einem flankengesteuerten D‑Flip‑Flop (`E_D_FF_ANY`) übergeben.
4. Der Flip‑Flop gibt bei der nächsten steigenden Flanke seines Takteingangs (`CLK`) das zusammengesetzte DWORD an den `OUT`-Adapter aus und erzeugt ein Ereignis (`EO`), das wiederum das Ausgangsereignis `E1` des `OUT`-Adapters auslöst.

Durch die Zwischenschaltung des Flip‑Flops wird sichergestellt, dass der Ausgang nur dann aktualisiert wird, wenn die Daten vollständig zusammengesetzt und stabil sind – selbst wenn mehrere Quarter‑Ereignisse quasi gleichzeitig eintreffen.

## Technische Besonderheiten

- **Keine eigenen Ein-/Ausgänge:** Der Baustein kommuniziert ausschließlich über Adapter, was eine saubere Kapselung und Wiederverwendbarkeit in unterschiedlichen Projektkontexten ermöglicht.
- **Synchrone Aktualisierung:** Der D‑Flip‑Flop verhindert Dateninkonsistenzen, falls mehrere Quarter ihre Werte nahezu zeitgleich ändern. Der Ausgang ändert sich erst, nachdem alle Eingänge ausgewertet wurden.
- **Autonome Triggerung:** Jedes Quarter‑Ereignis (egal von welchem Socket) löst eine Neuberechnung aus. Der Baustein arbeitet immer mit den aktuell anliegenden Werten aller 16 Quarter‑Daten.
- **Interne Indirektion:** Die tatsächliche Assemblierung erfolgt durch einen spezialisierten Unterbaustein (`ASSEMBLE_DWORD_FROM_QUARTERS`), was den Entwurf modular und wartbar hält.

## Zustandsübersicht

Der Funktionsblock selbst besitzt keinen eigenen Zustandsautomaten. Er verhält sich wie eine kombinatorische Logik mit nachgeschalteter Synchronisation. Der innere Flip‑Flop `E_D_FF_ANY` verfügt jedoch über einen internen Zustand (den gespeicherten DWORD‑Wert). Dieser Zustand wird nur beim Eintreffen eines Ereignisses an `CLK` geändert.

Im Ruhezustand (kein Ereignis an einem Quarter‑Socket) bleibt der Ausgangswert des `OUT`-Adapters unverändert.

## Anwendungsszenarien

- **Verteiltes Messsystem:** Mehrere Sensoren liefern je ein Byte; diese werden in einer Zentraleinheit zum Gesamt‑DWORD kombiniert.
- **Datenpaket‑Rekonstruktion:** Zerlegte Kommunikationsframes (z. B. 16‑Byte‑Nutzdaten) werden wieder zusammengesetzt.
- **Mediatorenstrukturen:** Als Bestandteil einer Adapter‑Kette zur Umwandlung von Datenbreiten in IEC 61499‑Anwendungen.
- **Synthese von Steuerwörtern:** Mehrere 8‑Bit‑Steuerkanäle werden zu einem 32‑Bit‑Befehlswort vereinigt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Eingänge | Ausgang | Synchronisation | Eigenschaften |
|----------|-----------------|---------|----------------|--------------|
| `ASSEMBLE_AD_FROM_AQ` | 16 (AQ‑Adapter) | 1 (AD‑Adapter) | Ja (Flip‑Flop) | Für ereignisgesteuerte Byte‑Sammlung. |
| `ASSEMBLE_DWORD_FROM_QUARTERS` (intern) | 16 Daten‑Eingänge (keine Adapter) | 1 DWORD‑Ausgang | Nein | Reine Daten‑Assemblierung ohne Ereignissynchronisation. |
| Einfacher `MERGE`‑Baustein (fiktiv) | 2 … n Daten‑Eingänge | 1 Daten‑Ausgang | Oft nein | Nur Daten‑Verknüpfung, keine Adapter‑Struktur. |

Der vorliegende Baustein zeichnet sich durch die Kapselung der Adapter‑Schnittstellen und die integrierte Synchronisation aus, wodurch er besonders für heterogene, ereignisgetriebene Umgebungen geeignet ist.

## Fazit

`ASSEMBLE_AD_FROM_AQ` ist ein spezialisierter Adapter‑Baustein zur Zusammenführung von 16 Byte‑breiten Quarter‑Daten in ein DWORD. Seine rein adapterbasierte Schnittstelle macht ihn flexibel einsetzbar, während die interne Synchronisation durch einen Flip‑Flop die Datenkonsistenz bei asynchronen Ereignissen gewährleistet. Er eignet sich hervorragend für den Einsatz in modularen IEC 61499‑Anwendungen, bei denen Daten in kleineren Einheiten ankommen und erst auf Empfängerseite zu einem vollständigen Wort zusammengesetzt werden müssen.