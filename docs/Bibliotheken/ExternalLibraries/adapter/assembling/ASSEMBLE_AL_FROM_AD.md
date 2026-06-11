# ASSEMBLE_AL_FROM_AD


![ASSEMBLE_AL_FROM_AD](./ASSEMBLE_AL_FROM_AD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ASSEMBLE_AL_FROM_AD** dient dazu, zwei über AD-Adapter (DWORD) bereitgestellte 32‑Bit-Werte zu einem 64‑Bit-LWORD zusammenzuführen und diesen über einen AL-Adapter auszugeben. Er kapselt die Kombinationslogik und stellt eine gepufferte, ereignisgesteuerte Schnittstelle für 64‑Bit-Daten bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **DWORD_00.E1** – Ereignis vom ersten AD‑Adapter, das die Kombination anstößt.
- **DWORD_01.E1** – Ereignis vom zweiten AD‑Adapter, das ebenfalls die Kombination anstößt.

### **Ereignis-Ausgänge**

- **OUT.E1** – Ereignis am AL‑Adapter, das signalisiert, dass ein neuer LWORD‑Wert am Ausgang anliegt.

### **Daten-Eingänge**

- **DWORD_00.D1** – Erster 32‑Bit-DWORD (niederwertiger Teil).
- **DWORD_01.D1** – Zweiter 32‑Bit-DWORD (höherwertiger Teil).

### **Daten-Ausgänge**

- **OUT.D1** – Zusammengesetzter 64‑Bit-LWORD.

### **Adapter**

- **DWORD_00** (Socket, Typ `adapter::types::unidirectional::AD`) – Eingangsadapter für den ersten DWORD.
- **DWORD_01** (Socket, Typ `adapter::types::unidirectional::AD`) – Eingangsadapter für den zweiten DWORD.
- **OUT** (Plug, Typ `adapter::types::unidirectional::AL`) – Ausgangsadapter für den resultierenden LWORD.

## Funktionsweise

Der FB arbeitet intern als FBNetzwerk aus zwei Unterbausteinen:

1. **ASSEMBLE_LWORD_FROM_DWORDS** – Kombiniert die beiden DWORD‑Eingänge `DWORD_00` und `DWORD_01` zu einem LWORD. Der Baustein wird durch das Ereignis `REQ` getriggert, das von **beiden** AD‑Adaptern (über `DWORD_00.E1` und `DWORD_01.E1`) gesendet werden kann. Nach Abschluss der Kombination wird das Ereignis `CNF` ausgegeben.

2. **E_D_FF_ANY** – Ein beliebiger D‑Flipflop, der den kombinierten LWORD puffert. Das `CNF`-Ereignis taktet den Flipflop (`CLK`), wobei der kombinierte Wert am Dateneingang `D` anliegt. Der gespeicherte Wert erscheint am Ausgang `Q` und wird über `OUT.D1` weitergegeben. Gleichzeitig wird das Flipflop-Ausgangsereignis `EO` als `OUT.E1` ausgelöst.

Somit wird der LWORD nur dann aktualisiert, wenn einer der beiden AD‑Adapter ein Ereignis sendet – das Flipflop verhindert mehrfache oder ungewollte Ausgaben bei unveränderten Eingängen.

## Technische Besonderheiten

- **Ereignisgesteuerte Verarbeitung** – Die Kombination wird nur bei eingehenden Ereignissen der AD‑Adapter ausgelöst, was unnötige Rechenlast vermeidet.
- **Gepufferter Ausgang** – Der D‑Flipflop stellt sicher, dass ein einmal berechneter LWORD bis zur nächsten Aktualisierung stabil am Ausgang anliegt.
- **Unabhängigkeit der Eingänge** – Jeder der beiden DWORD‑Adapter kann jederzeit ein Ereignis senden; die Kombination wird dann mit den aktuell anliegenden Werten durchgeführt.
- **Keine eigenen Ereignis-Eingänge auf oberster Ebene** – Der FB reagiert ausschließlich über die Adapter‑Schnittstellen.

## Zustandsübersicht

Der Baustein verwendet keinen expliziten ECC, sondern ein internes FBNetzwerk. Der funktionale Ablauf ist:

1. **Warten** auf ein Ereignis von `DWORD_00.E1` oder `DWORD_01.E1`.
2. **Kombinieren** – ASSEMBLE_LWORD_FROM_DWORDS verarbeitet die aktuellen DWORD‑Werte und erzeugt den LWORD.
3. **Puffern** – Der Flipflop übernimmt den LWORD und gibt ihn über `OUT.D1` aus.
4. **Signalisieren** – Das Ereignis `OUT.E1` wird ausgelöst.
5. Zurück zum Wartezustand.

Eine gleichzeitige Anforderung beider Eingänge führt nur zu einer Verarbeitung, da beide Ereignisse denselben `REQ` des Kombinationsbausteins triggern.

## Anwendungsszenarien

- **64‑Bit‑Datenverarbeitung** – Wenn ein System mit 32‑Bit‑Schnittstellen arbeitet und große Werte (z. B. hochauflösende Zeitstempel, Zählerstände, physikalische Messwerte) in einem LWORD zusammengefasst werden müssen.
- **Protokollumsetzung** – In Feldbussen oder Steuerungen, die Daten in separaten DWORD‑Segmenten liefern und eine 64‑Bit‑Weiterverarbeitung erfordern.
- **Sichere Datenkombination** – Der gepufferte Ausgang verhindert Zwischenwerte bei asynchron ankommenden DWORDs.

## Vergleich mit ähnlichen Bausteinen

- **ASSEMBLE_DWORD_FROM_WORDS** – Kombiniert zwei WORDs zu einem DWORD; analoges Prinzip, aber für andere Wortbreiten.
- **ASSEMBLE_LWORD_FROM_DWORDS** – Der interne Baustein, der die reine Kombination ohne Pufferung durchführt; ASSEMBLE_AL_FROM_AD fügt die ereignisgesteuerte Pufferung und die Adapter‑Schnittstelle hinzu.
- **Direkte Verwendung eines Typkonverters** – Wäre möglich, aber ohne Ereignissynchronisation; der vorliegende FB bietet eine saubere, industrialisierte Lösung mit Adaptern.

## Fazit

Der **ASSEMBLE_AL_FROM_AD** Funktionsblock ist ein spezialisierter, aber nützlicher Baustein für die Zusammenführung zweier DWORDs zu einem LWORD. Er kombiniert ereignisgesteuerte Verarbeitung mit einer stabilen Ausgangspufferung und ist ideal für Steuerungssysteme, die 64‑Bit‑Daten über standardisierte Adapter austauschen. Die Verwendung von Adaptern ermöglicht eine einfache Einbindung in existierende Modellstrukturen.