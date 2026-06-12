# SPLIT_AL_INTO_AW


![SPLIT_AL_INTO_AW](./SPLIT_AL_INTO_AW.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **SPLIT_AL_INTO_AW** dient dazu, eine über einen AL-Adapter (LWORD) eingehende 64‑Bit‑Ganzzahl in vier separate 16‑Bit‑Werte aufzuteilen und diese über vier einzelne AW-Adapter auszugeben. Er realisiert eine festverdrahtete Aufteilung, die durch ein eingehendes Ereignis ausgelöst wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **IN.E1** (Ereignis) – Wird über den Socket **IN** empfangen und startet den Aufteilungsvorgang.

### **Ereignis-Ausgänge**
- **WORD_00.E1** – Wird über den Plug **WORD_00** ausgegeben.  
- **WORD_01.E1** – Wird über den Plug **WORD_01** ausgegeben.  
- **WORD_02.E1** – Wird über den Plug **WORD_02** ausgegeben.  
- **WORD_03.E1** – Wird über den Plug **WORD_03** ausgegeben.  

Jeder Ereignisausgang wird parallel aktiviert, sobald die Aufteilung abgeschlossen ist.

### **Daten-Eingänge**
- **IN.D1** (LWORD) – Die 64‑Bit‑Eingangsgröße, die aufgeteilt werden soll. Bereitgestellt über den Socket **IN**.

### **Daten-Ausgänge**
- **WORD_00.D1** (WORD) – Das niederwertigste Wort (Bits 0–15).  
- **WORD_01.D1** (WORD) – Das zweite Wort (Bits 16–31).  
- **WORD_02.D1** (WORD) – Das dritte Wort (Bits 32–47).  
- **WORD_03.D1** (WORD) – Das höchstwertige Wort (Bits 48–63).  

Jeder Ausgang wird durch einen flankengesteuerten Speicher (E_D_FF_ANY) bereitgestellt und bleibt bis zum nächsten Aufteilungsvorgang stabil.

### **Adapter**
- **Socket IN** – Typ: `adapter::types::unidirectional::AL` (LWORD)  
- **Plugs WORD_00 … WORD_03** – Typ: `adapter::types::unidirectional::AW` (WORD)

## Funktionsweise

1. Ein eingehendes Ereignis an **IN.E1** aktiviert den internen Baustein **SPLIT_LWORD_INTO_WORDS** über dessen Ereigniseingang **REQ**.
2. Gleichzeitig wird das Datum **IN.D1** an den Dateneingang **IN** des Split‑Bausteins übergeben.
3. **SPLIT_LWORD_INTO_WORDS** teilt die LWORD in die vier Wortteile (**WORD_00**…**WORD_03**) auf und erzeugt ein Abschlussereignis an **CNF**.
4. Dieses Abschlussereignis wird an alle vier flankengesteuerten Flip‑Flops (**E_D_FF_ANY**) weitergeleitet. Jeder Flip‑Flop übernimmt das ihm zugeordnete Teilwort an seinem Dateneingang **D** und legt es an seinem Ausgang **Q** an.
5. Gleichzeitig werden die Ereignisausgänge **WORD_00.E1** … **WORD_03.E1** aktiviert, sodass die nachgeschalteten Adapter die neuen Daten gemeinsam übernehmen können.

## Technische Besonderheiten

- **Verwendung von E_D_FF_ANY**: Jeder Teilwert wird in einem flankengesteuerten Flip‑Flop zwischengespeichert. Dadurch bleibt der Ausgangswert auch dann erhalten, wenn am Eingang kein neues Ereignis anliegt. Erst der nächste Aufteilungsvorgang aktualisiert die Werte.
- **Parallelausgabe**: Alle vier Ausgangsereignisse werden gleichzeitig ausgelöst – die Daten stehen zum gleichen Zeitpunkt an allen Plugs an.
- **Adapterbasierte Schnittstelle**: Der Baustein arbeitet ausschließlich mit Adaptern, was eine saubere Kapselung und Wiederverwendbarkeit in modularen Applikationen ermöglicht.

## Zustandsübersicht

Der Baustein selbst besitzt keinen expliziten Zustandsautomaten. Die internen Flip‑Flops (E_D_FF_ANY) können folgende Zustände annehmen:

- **Idle**: Kein Ereignis anliegend – die Ausgangsplugs halten den zuletzt gespeicherten Wert.
- **Busy**: Während der Verarbeitung (zwischen **IN.E1** und dem Erscheinen der Ausgangsereignisse) ist der Baustein kurzzeitig belegt.
- **Ausgabe aktiv**: Nach Abschluss werden die neuen Daten an den Plugs ausgegeben und die Ereignisse gesendet.

## Anwendungsszenarien

- **De‑Serialisierung**: Auftrennen einer 64‑Bit‑Telegrammkomponente in einzelne 16‑Bit‑Registerwerte für die Weiterverarbeitung.
- **Steuerungstechnik**: Aufteilen einer langen Bitmaske in mehrere Teilmasken, die an verschiedene Aktoren oder Anzeigeeinheiten gesendet werden.
- **Datenvorbereitung**: Zerlegen eines LWORD‑Messwerts (z. B. aus einem Encoder oder einer Analog‑Digital‑Wandlerkarte) in nutzbare Wort‑Kanalwerte.

## Vergleich mit ähnlichen Bausteinen

- **SPLIT_LWORD_INTO_WORDS** (nicht adapterbasiert): Arbeitet mit reinen Daten‑ und Ereignisports. **SPLIT_AL_INTO_AW** kapselt diesen Baustein und fügt die Adapterschnittstellen sowie die flankengesteuerte Speicherung hinzu.
- **MUX** oder **DEMUX** (IEC 61499‑Standard): Diese trennen oder kombinieren Datenströme meist auf Bit‑ oder Bitebene, während **SPLIT_AL_INTO_AW** speziell für die feste 64‑Bit‑Aufteilung ausgelegt ist.

## Fazit

**SPLIT_AL_INTO_AW** bietet eine einfache, robuste Lösung, um eine LWORD über Adapter in vier WORTe aufzuteilen. Durch die integrierte flankengesteuerte Zwischenspeicherung ist der Baustein besonders für ereignisgesteuerte Systeme geeignet, bei denen die Daten parallel und stabil an verschiedenen Ausgängen anliegen müssen. Die adapterbasierte Schnittstelle vereinfacht die Integration in bestehende Komponentenbibliotheken.