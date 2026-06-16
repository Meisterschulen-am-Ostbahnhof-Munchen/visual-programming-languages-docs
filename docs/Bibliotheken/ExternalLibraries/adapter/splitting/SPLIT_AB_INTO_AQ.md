# SPLIT_AB_INTO_AQ


![SPLIT_AB_INTO_AQ](./SPLIT_AB_INTO_AQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_AB_INTO_AQ` dient dazu, ein über einen `AB`‑Adapter (Byte) eingehendes Datenbyte in vier einzelne 2‑Bit‑Quartette aufzuteilen und diese jeweils über `AQ`‑Adapter (Quarter) auszugeben. Er kapselt die Zerlegung eines Bytes in handhabbare Teilwerte und stellt sie über standardisierte unidirektionale Adapter‑Schnittstellen für die weitere Verarbeitung zur Verfügung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name    | Beschreibung |
|---------|--------------|
| `IN.E1` | Ereignis am Socket löst die Zerlegung und Ausgabe der Quartette aus. |

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge; die Ausgabe erfolgt über die Ereignisse der angeschlossenen Adapter (`QUARTER_BYTE_xx.E1`).

### **Daten-Eingänge**

| Name    | Beschreibung |
|---------|--------------|
| `IN.D1` | Das eingehende Datenbyte (Typ: BYTE), das in vier Quartette aufgeteilt wird. |

### **Daten-Ausgänge**
Keine direkten Datenausgänge; die Quartette werden über die Daten‑Schnittstellen der Ausgangs‑Adapter (`QUARTER_BYTE_xx.D1`) bereitgestellt.

### **Adapter**

| Name               | Typ | Richtung | Beschreibung |
|--------------------|-----|----------|--------------|
| `IN`               | `adapter::types::unidirectional::AB` | Socket (Eingang) | Empfängt das zu zerlegende Byte inkl. Ereignis. |
| `QUARTER_BYTE_00`  | `adapter::types::unidirectional::AQ` | Plug (Ausgang) | Gibt das Quartett 0 (niederwertigste 2 Bits) aus. |
| `QUARTER_BYTE_01`  | `adapter::types::unidirectional::AQ` | Plug (Ausgang) | Gibt das Quartett 1 aus. |
| `QUARTER_BYTE_02`  | `adapter::types::unidirectional::AQ` | Plug (Ausgang) | Gibt das Quartett 2 aus. |
| `QUARTER_BYTE_03`  | `adapter::types::unidirectional::AQ` | Plug (Ausgang) | Gibt das Quartett 3 (höchstwertigste 2 Bits) aus. |

## Funktionsweise
1. Ein Ereignis am Socket `IN.E1` aktiviert die Verarbeitung.
2. Das am Socket anliegende Byte (`IN.D1`) wird an den internen Baustein `SPLIT_BYTE_INTO_QUARTERS` weitergeleitet. Dieser zerlegt das Byte in vier 2‑Bit‑Teile (Quartette).
3. Die vier Quartette werden parallel an die Daten‑Eingänge von `E_D_FF_ANY`‑Flip‑Flops gegeben.
4. Gleichzeitig wird das Bestätigungsereignis (`CNF`) des Splitters an die Takt‑Eingänge (`CLK`) aller vier Flip‑Flops verteilt.
5. Mit der positiven Flanke dieses Ereignisses übernehmen die Flip‑Flops die Quartette und geben sie an den jeweiligen Ausgang (`Q`) weiter.
6. Die Ausgänge der Flip‑Flops sind direkt mit den Daten‑Eingängen der Ausgangs‑Adapter `QUARTER_BYTE_00` … `QUARTER_BYTE_03` verbunden. Gleichzeitig wird das Flip‑Flop‑Ausgangsereignis (`EO`) an den Ereigniseingang (`E1`) des jeweiligen Adapters gesendet, sodass die Daten auf der Adapter‑Schnittstelle ausgegeben werden.

Somit wird mit jeder Aktivierung des Sockets ein gesamtes Byte in vier Quartette aufgeteilt und synchron an alle vier Ausgangs‑Adapter übermittelt.

## Technische Besonderheiten
- **Interne Flip‑Flops:** Die Verwendung von `E_D_FF_ANY` stellt sicher, dass die Zerlegung nur einmal pro Ereignis erfolgt und die Werte zwischengespeichert werden, bis ein neues Ereignis eintrifft.
- **Adapter‑Kopplung:** Statt direkter Ein‑/Ausgänge werden ausschließlich unidirektionale Adapter verwendet, was eine lose Kopplung und Wiederverwendbarkeit in komplexen Adapter‑Netzwerken ermöglicht.
- **Synchronisation:** Die Taktung der Flip‑Flops erfolgt über das gemeinsame `CNF`‑Ereignis, sodass alle Quartette zeitgleich anliegen.
- **Keine Zustandsmaschine:** Der FB arbeitet rein ereignisgesteuert ohne eigenen sequenziellen Zustand – die Logik ist vollständig durch die vernetzten internen Bausteine realisiert.

## Zustandsübersicht
Da `SPLIT_AB_INTO_AQ` ein zusammengesetzter FB ohne eigene Zustandsmaschine ist, wird sein Verhalten durch die internen Bausteine bestimmt. Im Wesentlichen existieren zwei Phasen:
1. **Idle:** Es liegt kein Ereignis am Socket an; die Ausgangs‑Adapter halten die zuletzt übernommenen Werte.
2. **Verarbeitung:** Ein Ereignis am Socket löst das Zerlegen und Aktualisieren aller Ausgänge aus. Nach Abschluss geht der FB wieder in den Ruhezustand über.

## Anwendungsszenarien
- **Steuerung von vier Aktoren:** Ein Byte (z. B. von einem Master‑Steuerbus) wird in vier 2‑Bit‑Werte zerlegt, um separate Stellgrößen für unabhängige Aktuatoren zu liefern.
- **Datenreduktion:** Aufteilung eines Bytes in vier einzelne Signale zur Übergabe an parallele, einfachere Verarbeitungseinheiten.
- **Adapter‑basierte Architekturen:** Einsatz in Systemen, die durchgängig mit unidirektionalen Adaptern arbeiten, um die Modularität zu erhöhen.

## Vergleich mit ähnlichen Bausteinen
- **`SPLIT_BYTE_INTO_QUARTERS`:** Leistet die reine Zerlegung eines Bytes in vier Quartette, jedoch über direkte Daten‑ und Ereignis‑Ein‑/Ausgänge. `SPLIT_AB_INTO_AQ` kapselt diese Logik in einer Adapter‑Schnittstelle und fügt Flip‑Flops zur stabilen Ausgabe hinzu.
- **`SPLIT_WORD_INTO_BYTES`:** Zerlegt ein 16‑Bit‑Wort in zwei Bytes – analoges Prinzip, aber für andere Datenbreiten und andere Adaptertypen.
- **Einfache Multiplexer/Demultiplexer:** Während diese Signale umschalten, konzentriert sich `SPLIT_AB_INTO_AQ` auf die feste, parallele Aufteilung eines zusammengesetzten Datentyps.

## Fazit
`SPLIT_AB_INTO_AQ` ist ein spezialisierter zusammengesetzter Funktionsblock zur Aufteilung eines Byte‑Adapter‑Eingangs in vier separate Quarter‑Adapter‑Ausgänge. Er vereinfacht den Entwurf von Adapter‑Netzwerken, indem er die komplexe Bit‑Manipulation verbirgt und eine zuverlässige, ereignisgesteuerte Ausgabe der Quartette gewährleistet. Durch die Verwendung von Flip‑Flops wird eine stabile Datenhaltung zwischen den Ereignissen erreicht. Der Baustein eignet sich besonders für modulare Automatisierungslösungen, die mit unidirektionalen Adaptern arbeiten.