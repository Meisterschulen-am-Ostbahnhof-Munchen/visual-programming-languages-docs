# SPLIT_AW_INTO_AQ



![SPLIT_AW_INTO_AQ](./SPLIT_AW_INTO_AQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SPLIT_AW_INTO_AQ** teilt die acht Quarter-Adapter (AQ) eines Word-Adapters (AW) auf. Das eingehende Word (16 Bit) wird in acht Quarter-Einheiten (je 2 Bit) zerlegt und über die entsprechenden AQ-Plugs ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `IN.E1` (über Socket IN) – Lösen die Aufteilung eines neuen Word-Wertes aus.

### **Ereignis-Ausgänge**
- `QUARTER_BYTE_00.E1` bis `QUARTER_BYTE_07.E1` – Signalisiert die Bereitstellung des jeweiligen Quarter-Ergebnisses.

### **Daten-Eingänge**
- `IN.D1` – Empfängt das eingehende Word (16 Bit, Typ passend zum AW-Adapter).

### **Daten-Ausgänge**
- `QUARTER_BYTE_00.D1` bis `QUARTER_BYTE_07.D1` – Liefern die acht aufgeteilten Quarter-Werte (jeweils 2 Bit).

### **Adapter**
- **Socket:** `IN`  – Adapter vom Typ `adapter::types::unidirectional::AW`
- **Plugs:** `QUARTER_BYTE_00` … `QUARTER_BYTE_07` – Adapter vom Typ `adapter::types::unidirectional::AQ`

## Funktionsweise
1. Ein Ereignis am Eingang `IN.E1` aktiviert den internen Baustein `SPLIT_WORD_INTO_QUARTERS`.
2. `SPLIT_WORD_INTO_QUARTERS` zerlegt das über `IN.D1` anliegende 16‑Bit‑Wort in acht separate 2‑Bit‑Quarter-Werte.
3. Die aufgeteilten Werte werden parallel in acht `E_D_FF_ANY`‑Flip‑Flops zwischengespeichert (`D`‑Eingänge).
4. Nach Abschluss der Verarbeitung (CNF-Ereignis von `SPLIT_WORD_INTO_QUARTERS`) erhalten alle Flip‑Flops gleichzeitig einen Taktimpuls (`CLK`).
5. Die Ausgänge `Q` der Flip‑Flops werden auf die entsprechenden `QUARTER_BYTE_xx.D1`-Ausgänge gelegt.
6. Gleichzeitig wird jeweils das Ereignis `QUARTER_BYTE_xx.E1` ausgelöst, um die Datenweitergabe an nachgeschaltete Bausteine zu signalisieren.

## Technische Besonderheiten
- **Synchronisation durch Flip‑Flops:** Alle acht Quarter-Werte werden taktsynchron aus dem internen Splitter übernommen.
- **Keine persistente Zustandshaltung:** Der Baustein puffert die Quarter-Werte nur bis zum nächsten Verarbeitungsdurchlauf.
- **Einheitliche Schnittstellen:** Die Adapter folgen dem unidirektionalen AW/AQ‑Protokoll und ermöglichen eine einfache Kopplung in der 4diac‑IDE.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Die internen `E_D_FF_ANY`‑Flip‑Flops können sich in zwei Zuständen befinden:
- **Speichert vorherigen Wert** – Bis ein neues Ereignis eintrifft.
- **Aktualisierter Wert** – Nach einem Taktimpuls durch das CNF-Ereignis.

## Anwendungsszenarien
- **Datenaufbereitung:** Zerlegen eines 16‑Bit‑Wortes aus einem Kommunikations‑Adapter in acht 2‑Bit‑Quarter‑Signale, z.B. für parallele Verarbeitung in Steuerungslogiken.
- **Multiplexing/Demultiplexing:** Trennen von Wort‑Datenströmen in separate Quarter‑Kanäle.
- **Erweiterung von Busstrukturen:** Einfaches Aufteilen von Adress‑ oder Steuerwörtern auf mehrere nachfolgende Bausteine.

## Vergleich mit ähnlichen Bausteinen
- **SPLIT_BYTE_INTO_NIBBLES** – Teilt ein Byte in zwei 4‑Bit‑Nibbles.
- **SPLIT_WORD_INTO_BYTES** – Zerlegt ein 16‑Bit‑Wort in zwei 8‑Bit‑Bytes.
- **SPLIT_AW_INTO_AQ** ist speziell für die Aufteilung eines AW‑Adapters (Word) in acht AQ‑Adapter (Quarter) ausgelegt – die Schnittstellen sind direkt auf die Adapter‑Typen abgestimmt und erfordern keine manuelle Konfiguration.

## Fazit
Der Baustein **SPLIT_AW_INTO_AQ** bietet eine kompakte und zuverlässige Möglichkeit, ein einkommendes Word in acht Quarter‑Signale aufzuteilen. Durch die integrierte Taktsynchronisation und die standardisierten Adapter‑Schnittstellen eignet er sich hervorragend für modulare IEC 61499‑Anwendungen, die eine gleichzeitige Datenaufbereitung für mehrere Teilnehmer erfordern.