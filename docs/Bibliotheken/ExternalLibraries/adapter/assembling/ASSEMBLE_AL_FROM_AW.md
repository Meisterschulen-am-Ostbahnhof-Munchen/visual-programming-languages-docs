# ASSEMBLE_AL_FROM_AW


![ASSEMBLE_AL_FROM_AW](./ASSEMBLE_AL_FROM_AW.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ASSEMBLE_AL_FROM_AW` kombiniert die Daten von vier **AW (WORD)**-Adapter-Schnittstellen zu einem **AL (LWORD)**-Ausgangswert. Er dient dazu, mehrere 16‑Bit‑Wörter zu einem 64‑Bit‑Wort zusammenzusetzen und über eine getaktete Ausgabe bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine – die Ereignissteuerung erfolgt ausschließlich über die angeschlossenen Adapter (siehe Abschnitt Adapter).

### **Ereignis-Ausgänge**

Keine – die Ereignisausgabe erfolgt über den OUT-Adapter (`OUT.E1`).

### **Daten-Eingänge**

Keine direkten Daten-Eingänge – die zu verarbeitenden Daten werden über die vier AW-Sockets bezogen.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge – das Ergebnis wird über den OUT-Adapter ausgegeben.

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| **Sockets** | | |
| `WORD_00` | `adapter::types::unidirectional::AW` | Word 0 (niederwertigstes 16‑Bit‑Wort) |
| `WORD_01` | `adapter::types::unidirectional::AW` | Word 1 |
| `WORD_02` | `adapter::types::unidirectional::AW` | Word 2 |
| `WORD_03` | `adapter::types::unidirectional::AW` | Word 3 (höchstwertiges 16‑Bit‑Wort) |
| **Plugs** | | |
| `OUT` | `adapter::types::unidirectional::AL` | LWORD‑Ausgang (64‑Bit) |

## Funktionsweise

Der Baustein nutzt ein internes Netzwerk aus zwei Funktionsbausteinen:

1. **`ASSEMBLE_LWORD_FROM_WORDS`** – übernimmt die logische Kombination der vier 16‑Bit‑Wörter (`WORD_00` bis `WORD_03`) zu einem 64‑Bit‑LWORD.  
2. **`E_D_FF_ANY`** – ein taktflankengesteuertes D‑Flip‑Flop, das den zusammengesetzten Wert nur dann auf den Ausgangsadapter `OUT` überträgt, wenn eine steigende Flanke am Takteingang anliegt.

Die Ereignisse der vier Eingangsadapter (`WORD_00.E1` … `WORD_03.E1`) sind alle mit dem `REQ`-Ereigniseingang von `ASSEMBLE_LWORD_FROM_WORDS` verbunden. Sobald ein Ereignis an einem der Eingangsadapter eintrifft, wird die Kombination neu berechnet. Nach Abschluss (`CNF`) wird der `E_D_FF_ANY` getaktet, der den berechneten Wert in seinen internen Zustand übernimmt und über `OUT.D1` ausgibt. Das Ereignis am Ausgangsadapter (`OUT.E1`) signalisiert die Verfügbarkeit des neuen Werts.

## Technische Besonderheiten

- **Taktflankengesteuerte Ausgabe** – Die Verwendung des `E_D_FF_ANY` verhindert ungewollte Zwischenwerte und stellt sicher, dass nur vollständig zusammengesetzte LWORDs nach außen gegeben werden.
- **Beliebige Reihenfolge der Eingangsereignisse** – Da alle vier Sockets auf denselben `REQ`-Eingang zusammengeführt sind, löst jedes eingehende Ereignis eine Neuberechnung aus. Der Baustein reagiert also auf jedes Teilwort, aktualisiert aber den Ausgang erst nach der vollständigen Zusammensetzung.
- **Adapterbasierte Schnittstelle** – Die Verwendung von unidirektionalen Adaptern (AW und AL) ermöglicht eine lose Kopplung und Wiederverwendung in verschiedenen Kontexten.

## Zustandsübersicht

Der Baustein besitzt kein eigenes ECC (Execution Control Chart), sondern besteht aus einer kombinatorischen Schaltung mit einem nachgeschalteten Flip‑Flop. Die interne Zustandslogik wird vollständig durch die beiden Unterbausteine `ASSEMBLE_LWORD_FROM_WORDS` und `E_D_FF_ANY` realisiert.

## Anwendungsszenarien

- **Industrielle Datenerfassung** – Zusammenführen von vier 16‑Bit‑Sensorwerten (z. B. Temperatur, Druck, Durchfluss, Füllstand) zu einem einzigen 64‑Bit‑Datenpaket.
- **Kommunikationsschnittstellen** – Aufbereitung von getrennt eintreffenden 16‑Bit‑Datenblöcken für eine 64‑Bit‑Schnittstelle (z. B. Modbus‑Register → OPC UA).
- **Bit‑parallele Verarbeitung** – Kombinieren von vier Registern eines Mikrocontrollers zu einem Großregister für erweiterte Logikanwendungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung |
|----------|-------------|
| `ASSEMBLE_AL_FROM_BYTES` | Setzt mehrere 8‑Bit‑Werte zu einem LWORD zusammen |
| `ASSEMBLE_AL_FROM_DWORDS` | Kombiniert zwei 32‑Bit‑Doppelwörter zu einem 64‑Bit‑Wort |
| `ASSEMBLE_AL_FROM_AW` (dieser) | Kombiniert vier 16‑Bit‑Wörter zu einem LWORD |

Alle diese Bausteine folgen dem gleichen Prinzip, unterscheiden sich jedoch in der Wortbreite der Eingangsdaten und der Anzahl der benötigten Sockets.

## Fazit

`ASSEMBLE_AL_FROM_AW` ist ein spezialisierter Funktionsbaustein zum Zusammenfügen von vier 16‑Bit‑Wörtern zu einem 64‑Bit‑Wort. Die getaktete Ausgabe über ein D‑Flip‑Flop sorgt für konsistente Datenweitergabe. Dank der adapterbasierten Schnittstelle fügt er sich nahtlos in modulare 4diac‑Projekte ein und erleichtert die Handhabung von Wort‑zu‑Langwort‑Konvertierungen.