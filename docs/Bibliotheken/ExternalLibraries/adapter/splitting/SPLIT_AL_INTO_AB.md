# SPLIT_AL_INTO_AB


![SPLIT_AL_INTO_AB](./SPLIT_AL_INTO_AB.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **SPLIT_AL_INTO_AB** dient dazu, einen über einen **AL-Adapter** (Long Word) eingehenden 64-Bit-Wert (LWORD) in seine acht einzelnen Bytes aufzuteilen und diese über acht separate **AB-Adapter** (Byte) bereitzustellen. Die Aufteilung erfolgt synchron zu einem Ereignis am Eingangsadapter, und jedes Byte wird über ein eigenes Flipflop (E_D_FF_ANY) zwischengespeichert, bevor es am entsprechenden Ausgangsadapter anliegt. Der Baustein ist als **Adapter-Splitting-Komponente** konzipiert und eignet sich besonders für die strukturierte Datenzerlegung in IEC 61499-Systemen.

## Schnittstellenstruktur

### Ereignis-Eingänge
- **IN** (Socket, Typ: `adapter::types::unidirectional::AL`):  
  Der integrierte Ereignis-Ausgang **E1** des AL-Adapters löst die Verarbeitung aus. Ein eingehendes Ereignis am Adapter IN startet die Zerlegung des gleichzeitig anliegenden Datenwertes.

### Ereignis-Ausgänge
Die Ausgangsadapter **BYTE_00** bis **BYTE_07** (Plugs, Typ: `adapter::types::unidirectional::AB`) verfügen jeweils über einen Ereignis-Eingang **E1**, der nach erfolgter Datenübernahme ausgelöst wird. Diese Ereignisse werden vom internen Netzwerk generiert und signalisieren, dass das zugehörige Byte gültig am Datenausgang des Adapters anliegt.

### Daten-Eingänge
- **IN** (Socket, Typ: `adapter::types::unidirectional::AL`):  
  Liefert den zu zerlegenden 64-Bit-Datenwert über den Daten-Eingang **D1** des Adapters (Typ LWORD).

### Daten-Ausgänge
- **BYTE_00** bis **BYTE_07** (Plugs, Typ: `adapter::types::unidirectional::AB`):  
  Jeder dieser Adapter stellt über seinen Daten-Ausgang **D1** ein einzelnes Byte (BYTE) zur Verfügung. Die Zuordnung ist:
  - BYTE_00: niederwertigstes Byte (Bit 0…7)
  - BYTE_01: nächstes Byte (Bit 8…15)
  - …
  - BYTE_07: höchstwertigstes Byte (Bit 56…63)

### Adapter
- **IN**: Socket (AL – Adapter Long Word) – aufnehmender Adapter  
- **BYTE_00 … BYTE_07**: Plugs (AB – Adapter Byte) – abgebende Adapter

## Funktionsweise

1. Ein Ereignis am Eingangsadapter **IN** (E1) triggert den internen Funktionsblock **SPLIT_LWORD_INTO_BYTES** (Typ: `eclipse4diac::utils::splitting::SPLIT_LWORD_INTO_BYTES`).  
2. Gleichzeitig wird der vom Adapter IN bereitgestellte LWORD-Wert (D1) an den Eingang **IN** dieses internen Bausteins weitergeleitet.  
3. Der interne Splitter zerlegt den LWORD in acht separate Bytes (**BYTE_00** … **BYTE_07**) und legt diese an seinen Datenausgängen an.  
4. Das Abschlussereignis **CNF** des Splitters wird parallel an acht **E_D_FF_ANY**-Flipflops gesendet. Jedes Flipflop übernimmt mit diesem Takt das ihm zugeordnete Byte und gibt es an seinem Ausgang **Q** aus.  
5. Die Flipflops erzeugen ihrerseits ein Ausgangsereignis **EO**, das direkt mit dem Ereigniseingang **E1** des entsprechenden **BYTE_XX**-Adapters verbunden ist.  
6. Dadurch werden die einzelnen Bytes zeitgleich über die acht AB-Adapter nach außen gegeben – sowohl als Datenwert (Q → D1) als auch als Bestätigungsereignis (EO → E1).

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Der Baustein verwendet ausschließlich Adapter (AL und AB) und keine herkömmlichen Ereignis-/Datenports. Dies ermöglicht eine modulare Kapselung und Wiederverwendung in Adapter-basierten Architekturen.  
- **Gleichzeitige Ausgabe**: Die acht Bytes werden durch die parallele Taktung aller Flipflops gleichzeitig ausgegeben, was für zeitkritische Anwendungen vorteilhaft ist.  
- **Zwischenspeicherung**: Jedes Byte wird in einem eigenen Flipflop (E_D_FF_ANY) zwischengespeichert, sodass der Ausgangswert auch dann erhalten bleibt, wenn der Eingangswert wechselt oder ein neuer Zerlegungszyklus beginnt.  
- **Unidirektionale Datenfluss**: Die Adapter sind als unidirektional (IN: AL, OUT: AB) ausgelegt – der Datenfluss erfolgt nur vom Eingang zu den Ausgängen.  
- **Keine Zustandsautomaten im FB selbst**: Der FB delegiert die Zustandshaltung an die internen Flipflops; er selbst ist rein kombinatorisch mit einer getakteten Übernahme.

## Zustandsübersicht

Der Baustein selbst besitzt keinen eigenen, sichtbaren Zustandsautomaten. Die internen Flipflops **E_D_FF_ANY** besitzen jedoch einen Zweizustand (Q = 0 oder 1). Der gesamte Ablauf folgt einem festen Schema:

- **Idle**: Kein Ereignis am Eingang – Ausgänge behalten ihre letzten Werte.  
- **Processing**: Ein Ereignis am IN-Adapter wird verarbeitet.  
- **Output**: Nach der Taktung der Flipflops stehen alle acht Bytes gleichzeitig an den Ausgangsadaptern an und werden durch die jeweiligen Ereignisse bestätigt.

## Anwendungsszenarien

- **Dekomposition von Kommunikationsdaten**: Zerlegung eines empfangenen LWORD-Pakets (z. B. aus einem Feldbus oder einer seriellen Schnittstelle) in einzelne Byte-Signale für die weitere Verarbeitung in der Steuerung.  
- **Parallele Ausgabe von Diagnose-/Statusbytes**: Aufteilung eines zusammengesetzten 64-Bit-Statuswortes auf acht getrennte Byte-Ausgänge zur Anzeige oder Weiterleitung.  
- **Adapterorientierte Datenverarbeitung**: Einbindung in Architekturen, die auf Adaptern basieren, um eine strikte Trennung von Daten- und Ereignisschnittstellen zu gewährleisten.  
- **Schnittstelle zu Unterbausteinen**: Versorgung mehrerer FB, die jeweils ein Byte benötigen (z. B. für sieben Segmentanzeigen, Schrittmotoransteuerung oder D/A-Wandler).

## Vergleich mit ähnlichen Bausteinen

- **SPLIT_LWORD_INTO_BYTES**: Dieser interne FB führt die reine Aufteilung ohne Adapter aus und gibt einfache Datenausgänge (BYTE) sowie ein Ereignis (CNF) aus. Im Gegensatz dazu bietet **SPLIT_AL_INTO_AB** eine vollständige Adapterkapselung inklusive Zwischenspeicherung und synchronisierter Ereignisausgabe.  
- **SPLIT_DWORD_INTO_BYTES** (analog, falls vorhanden): Zerlegt einen 32-Bit-Wert in vier Bytes. SPLIT_AL_INTO_AB ist auf 64 Bit ausgelegt und liefert acht Bytes.  
- **Einfache MOVE-FBs**: Mehrere MOVE-Bausteine mit Bitmasken müssten einzeln konfiguriert werden, während dieser Baustein eine fertige, integrierte Lösung bietet.  
- **Adapterbasierte Alternativen**: Andere Splitting-Adapter könnten symetrische oder andere Adaptertypen verwenden; dieser FB ist auf AL→AB spezialisiert.

## Fazit

**SPLIT_AL_INTO_AB** ist ein nützlicher und effizienter Funktionsblock zum Aufteilen eines 64-Bit-Datenwortes in acht einzelne Bytes, der speziell für den Einsatz mit IEC 61499-Adaptern (AL/AB) entwickelt wurde. Die Kombination aus internem Splitter und Flipflops gewährleistet eine gleichzeitige, puffergestützte Ausgabe aller Bytes. Dank der adapterbasierten Schnittstelle lässt sich der Baustein nahtlos in modulare Steuerungsarchitekturen integrieren, bei denen eine saubere Trennung von Ereignis- und Datenkanälen gewünscht ist. Er eignet sich besonders für Anwendungen, die eine parallele, strukturierte Datenweitergabe erfordern.