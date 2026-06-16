# ASSEMBLE_AW_FROM_AB


![ASSEMBLE_AW_FROM_AB](./ASSEMBLE_AW_FROM_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **ASSEMBLE_AW_FROM_AB** dient dazu, zwei unidirektionale Byte‑Adapter (Typ `AB`) zu einem unidirektionalen Word‑Adapter (Typ `AW`) zusammenzufügen. Er kombiniert die Daten zweier BYTE‑Eingänge zu einem WORD‑Ausgang, wobei die Ereignislogik sicherstellt, dass die Ausgabe nur bei aktualisierter Information erfolgt.

## Schnittstellenstruktur

Der FB besitzt keine direkten Ereignis- oder Datenein-/ausgänge, sondern kommuniziert ausschließlich über Adapter‑Schnittstellen:

### **Adapter (Plugs – Ausgang)**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| OUT | `adapter::types::unidirectional::AW` | Plug | WORD‑Ausgabe (16 Bit) |

### **Adapter (Sockets – Eingänge)**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| BYTE_00 | `adapter::types::unidirectional::AB` | Socket | Byte 0 (niedrigwertiges Byte) |
| BYTE_01 | `adapter::types::unidirectional::AB` | Socket | Byte 1 (höherwertiges Byte) |

**Hinweis:** Die Adapter vom Typ `AB` und `AW` sind unidirektional ausgeführt. Jeder Adapter enthält die Signale `E1` (Event‑Ausgang des Sockets/Plug – intern verbunden) und `D1` (Datensignal).

## Funktionsweise

Der FB setzt intern auf zwei Subbausteinen auf:

1. **`ASSEMBLE_WORD_FROM_BYTES`** – ein vordefinierter Assembler, der zwei Eingangsbytes zu einem WORD zusammenfasst.
2. **`E_D_FF_ANY`** – ein D‑Flipflop, das den kombinierten Wert zwischenspeichert und bei einem Taktereignis weitergibt.

**Ablauf:**

- Jeder eingehende Event (`E1`) eines BYTE‑Adapters (BYTE_00 oder BYTE_01) triggert den Assembler (`REQ`).
- Der Assembler kombiniert die aktuellen Daten beider BYTE‑Eingänge zu einem WORD.  
  Dabei gilt:  
  `OUT.WORD = (BYTE_01.D1 << 8) | BYTE_00.D1`
- Nach erfolgreicher Kombination sendet der Assembler einen Bestätigungs‑Event (`CNF`).
- Dieser Event taktet das D‑Flipflop (`CLK`), das den aktuellen WORD‑Wert übernimmt.
- Der Flipflop‑Ausgang (`Q`) wird kontinuierlich an den OUT‑Adapter (`D1`) weitergegeben.
- Der Ausgangs‑Event (`EO`) des Flipflops aktiviert `OUT.E1`, sodass der empfangende Baustein über die aktualisierte WORD‑Ausgabe informiert wird.

**Wichtige Eigenschaft:**  
Da beide BYTE‑Events auf den gleichen `REQ` des Assemblers führen, wird bei jedem Ereignis eines der beiden Eingänge die Assemblierung neu durchgeführt. Der Ausgangswert wird also stets aus den gerade anliegenden Byte‑Werten gebildet. Das D‑Flipflop sorgt für einen stabilen Ausgang, bis der nächste Assemblierungs‑Event eintrifft.

## Technische Besonderheiten

- **Reine Adapter‑Kommunikation:** Der FB besitzt keine herkömmlichen Ein‑/Ausgangsvariablen; die gesamte Daten- und Ereignisübertragung erfolgt über unidirektionale Adapter.
- **Ereignis‑Synchronisation:** Der einschrittige Assemblierungsprozess vermeidet Wettlaufsituationen, da das Flipflop die Ausgabe erst nach erfolgreicher Berechnung aktualisiert.
- **Wiederverwendbarkeit:** Der FB kann in jede Umgebung eingebettet werden, die unidirektionale `AB`/`AW`-Adapter unterstützt.

## Zustandsübersicht

Der FB besitzt kein explizites Zustandsdiagramm, da die interne Logik rein ereignisgesteuert arbeitet. Im Wesentlichen lassen sich folgende Betriebszustände unterscheiden:

- **Bereit:** Es liegt kein Ereignis an; der Ausgang hält den zuletzt gespeicherten WORD‑Wert.
- **Assemblieren:** Ein eingehender Event eines BYTE‑Adapters startet die Berechnung.
- **Ausgeben:** Nach erfolgreicher Assemblierung wird der neue WORD‑Wert durch das Flipflop übernommen und der Ausgangs‑Event ausgelöst.

## Anwendungsszenarien

- **Protokoll‑Konvertierung:** Zusammenführen zweier serieller Byte‑Ströme zu einem WORD‑Datenwort für einen nachfolgenden Verarbeitungsbaustein.
- **Sensorfusion:** Kombination von zwei 8‑Bit‑Sensordaten (z. B. Temperatur und Luftfeuchte) zu einem 16‑Bit‑Wert.
- **Hardware‑Ansteuerung:** Erzeugen eines 16‑Bit‑Ausgangssignals aus zwei getrennten 8‑Bit‑Registerwerten.

## Vergleich mit ähnlichen Bausteinen

- **`ASSEMBLE_WORD_FROM_BYTES`** – reiner Assembler ohne Speicher. Er erwartet diskrete Daten‑Eingänge und gibt das Ergebnis sofort aus (vorausgesetzt, Ereignis und Daten werden synchron bereitgestellt).
- **`SPLIT_BYTE_FROM_WORD`** – inverse Funktion (WORD -> zwei BYTEs); symmetrisch aufgebaut, nutzt ebenfalls unidirektionale Adapter.
- **Eigener FB mit Speicher:** Der vorliegende Baustein integriert das Flipflop, sodass die Ausgabe stabil bleibt, bis neue Daten anliegen – im Gegensatz zu Bausteinen, die bei jedem Event neu berechnen, aber keine Zwischenspeicherung bieten.

## Fazit

Der FB **ASSEMBLE_AW_FROM_AB** bietet eine zuverlässige und elegante Möglichkeit, zwei unidirektionale BYTE‑Adapter zu einem WORD‑Ausgang zu kombinieren. Durch die Kombination aus Assemble‑ und Flipflop‑Logik entsteht ein stabiler Ausgang, der nur bei tatsächlicher Datenänderung aktualisiert wird. Seine reine Adapter‑Schnittstelle macht ihn flexibel einsetzbar in modularen Steuerungsarchitekturen nach IEC 61499.